<?php

class loginDB
{
	private $db;
	private $ini;

	public function __construct($inifile)
	{
		$this->ini = parse_ini_file($inifile, true);
		$host = $this->ini['loginDB']['host'];
		$user = $this->ini['loginDB']['user'];
		$password = $this->ini['loginDB']['password'];
		$database = $this->ini['loginDB']['database'];
		
		$this->db = new mysqli($host,$user,$password,$database);

		if ($this->db->connect_errno > 0)
		{
			echo __FILE__.":".__LINE__.": failed to connect to database, re: ".$this->db->connect_error.PHP_EOL;
			exit(0);
		}
	}

	public function __destruct()
	{
		$this->db->close();
	}

	public function checkIfUserExists($username)
   	{
		$username = $this->db->real_escape_string($username);
		$query = "select username from login where username = '$username';";
        	$results = $this->db->query($query);
		$row = $results->fetch_assoc();
		
		if ($row['username'] === $username)
        	{
			return true;
		}
        	
		return false;
   	}


	public function validateUser($username, $password)
	{
		$username = $this->db->real_escape_string($username);
		$password = $this->db->real_escape_string($this->saltPassword($password));
		$query = "select username, password from login where username = '$username';";
		$results = $this->db->query($query);
		$row = $results->fetch_assoc();

		if ($row['password'] === $password)
		{
			return true;
		}
		
		return false;
	}

 	public function validateAdminPrivilege($username)
   	{
		$username = $this->db->real_escape_string($username);		
		$query = "select privilegeLevel from login where username = '$username';";
        	$results = $this->db->query($query);
		$row = $results->fetch_assoc();
		
		if ($row['privilegeLevel'] === 'admin')
		{
			echo "".PHP_EOL;
			echo "Admin Access granted! Your command has been processed...  ".PHP_EOL;
			echo "".PHP_EOL;
			return true;
		}

		return false;
   	}

	 public function validateManagerPrivilege($username)
        {
                $username = $this->db->real_escape_string($username);
                $query = "select privilegeLevel from login where username = '$username';";
                $results = $this->db->query($query);
                $row = $results->fetch_assoc();

                if ($row['privilegeLevel'] === 'manager')
                {
                        echo "".PHP_EOL;
                        echo "Manager Access granted! Your command has been processed...  ".PHP_EOL;
                        echo "".PHP_EOL;
                        return true;
                }
                
                return false;
        }

	public function validateOwnerPrivilege($username)
	{
		$username = $this->db->real_escape_string($username);
		$query = "select Createdby from Tickets where Createdby = '$username';";
                $results = $this->db->query($query);
                $row = $results->fetch_assoc();

                if ($row['Createdby'] === "$username")
                {
                        echo "".PHP_EOL;
                        echo "Ticket Owner Access granted! Your command has been processed...  ".PHP_EOL;
                        echo "".PHP_EOL;
                        return true;
                }
                echo "false".PHP_EOL;
                return false;
	}

	private function saltPassword($password)
 	{
		$salt = $this->ini['loginDB']['salt'];
		return substr(sha1($password.$salt),10,-10);
 	}	

	public function addNewUser($username, $password, $privilegeLevel, $newusername, $newpassword, $reportsto)
	{
		if ($this->checkIfUserExists($newusername) == true)
		{
			echo "Not able to create new user $newusername, this user already exists in database!".PHP_EOL;
			return;
		}
		
		$username = $this->db->real_escape_string($username);
		$reportsto = $this->db->real_escape_string($reportsto);
		$newpassword = $this->db->real_escape_string($this->saltPassword($newpassword));
		$privilegeLevel = $this->db->real_escape_string($privilegeLevel);
			
		if ($this->db->errno > 0)
        	{
			echo "DB error: ".$this->db->error.PHP_EOL;
			return;
        	}
		
		if(!$this->validateUser($username, $password))
		{
			echo "Incorrect password".PHP_EOL;
			$response = array(
				"message"=>"Incorrect",
				"result"=>"false"
			);
			return $response;
		}
		else if(!$this->validateAdminPrivilege($username))
		{
			echo "User ". $username . "does not have admin access.".PHP_EOL;
			$response = array(
				"message"=>"User" . $username . "does not have admin access",
				"result"=>"false");
			return $response;
		}
		else
		{
			 $query = "insert into login (username,password,privilegeLevel,reportsto) values('$newusername','$newpassword','$privilegeLevel','$reportsto');";
               		 $results = $this->db->query($query);
			 echo $this->ViewLastUserCreated($username).PHP_EOL;
		}
	}

	 public function ViewLastUserCreated($username)
        {
                $username = $this->db->real_escape_string($username);

                        $query = "Select * from login WHERE LoginID =(SELECT MAX(LoginID) from login);";
                        $results = $this->db->query($query);

                        if($results->num_rows > 0)
                        {
                                while($row = $results->fetch_assoc())
                                {
                                        echo " - LoginID: " . $row['LoginID'] . " - Username: " . $row['username'] . " - PrivilegeLevel: " . $row['privilegeLevel'].PHP_EOL;
					echo " - Reportsto: " . $row['reportsto'].PHP_EOL;
                                }

                }
                        else
                        {
                                echo "0 results for specified results...";
                        }




        }
	

	public function ModifyUserRole($username, $password, $targetuser, $privilegeLevel)
	{
		$username = $this->db->real_escape_string($username);
		$privilegeLevel = $this->db->real_escape_string($privilegeLevel);

		 if(!$this->validateUser($username, $password))
                {
                        echo "Incorrect password".PHP_EOL;
                        $response = array(
                                "message"=>"Incorrect",
                                "result"=>"false"
                        );
                        return $response;
                }
                else if(!$this->validateAdminPrivilege($username))
                {
                        echo "User ". $username . "does not have admin access.".PHP_EOL;
                        $response = array(
                                "message"=>"User" . $username . "does not have admin access",
                                "result"=>"false");
                        return $response;
                }
			
		else 
		{
			$query = "UPDATE login SET privilegeLevel = '$privilegeLevel' WHERE username = '$targetuser';";
			$results = $this->db->query($query);
			echo "User " . "$targetuser" . " has been granted " . $privilegeLevel . " access.".PHP_EOL;
		}
	}

	public function ViewTickets($username, $password)
	{
		$username = $this->db->real_escape_string($username);
		$password = $this->db->real_escape_string($password);

		 if(!$this->validateUser($username, $password))
                {
                        echo "Incorrect password".PHP_EOL;
                        $response = array(
                                "message"=>"Incorrect",
                                "result"=>"false"
                        );
                        return $response;
                }
                else if(!$this->validateAdminPrivilege($username))
                {
                        echo "User ". $username . "does not have admin access.".PHP_EOL;
                        $response = array(
                                "message"=>"User" . $username . "does not have admin access",
                                "result"=>"false");
                        return $response;
                }
		
		else
		{
			$query = "Select * from Tickets;";
               		$results = $this->db->query($query);

			if($results->num_rows > 0)
                	{
                        	while($row = $results->fetch_assoc())
                        	{	
                                	echo " - ID: " . $row["TicketID"] . " - title: " . $row["title"] . " - Category: " . $row["Category"] . " - Severity: " . $row["Severity"].PHP_EOL;
                                	echo  " - Created by: " . $row["Createdby"].PHP_EOL;
					echo " - description: " . $row["description"].PHP_EOL;
                                	echo  " - status: " . $row["status"].PHP_EOL;
                                	echo "".PHP_EOL;
                        	}

                }
                	else
                	{
                        	echo "0 results for specified results...";
                	}
	
		}


	}

	public function DeleteTicket($username, $password, $TicketID)
	{
		$username = $this->db->real_escape_string($username);
                $password = $this->db->real_escape_string($password);
		if(!$this->validateUser($username, $password))
                {
                        echo "Incorrect password".PHP_EOL;
                        $response = array(
                                "message"=>"Incorrect",
                                "result"=>"false"
                        );
                        return $response;
                }
                else if(!$this->validateAdminPrivilege($username))
                {
                        echo "User ". $username . "does not have admin access.".PHP_EOL;
                        $response = array(
                                "message"=>"User" . $username . "does not have admin access",
                                "result"=>"false");
                        return $response;
                }

                else
                {
			$query = "DELETE FROM Tickets WHERE TicketID = '$TicketID' ;";
                        $results = $this->db->query($query);
			echo $this->ViewTickets($username, $password);
		}
	}

	public function EditTicket($username, $password, $fieldname, $input, $TicketID)
	{
		 $username = $this->db->real_escape_string($username);
                $password = $this->db->real_escape_string($password);

                 if(!$this->validateUser($username, $password))
                {
                        echo "Incorrect password".PHP_EOL;
                        $response = array(
                                "message"=>"Incorrect",
                                "result"=>"false"
                        );
                        return $response;
                }

		else if(!$this->validateAdminPrivilege($username))
                {
                        echo "User ". $username . "does not have admin access.".PHP_EOL;
                        $response = array(
                                "message"=>"User" . $username . "does not have admin access",
                                "result"=>"false");
                        return $response;
                }
		
		else 
		{
			$query = "UPDATE Tickets SET ". $fieldname . " = '$input' where TicketID = '$TicketID';";
			$results = $this->db->query($query);
			echo "The following changes have been made to: " . $fieldname . "..... information that was entered: " . $input.PHP_EOL;
					
		}

	}

	public function ManagerReportUser($username, $password)
	{
		$username = $this->db->real_escape_string($username);
                $password = $this->db->real_escape_string($password);

		 if(!$this->validateUser($username, $password))
                {
                        echo "Incorrect password".PHP_EOL;
                        $response = array(
                                "message"=>"Incorrect",
                                "result"=>"false"
                        );
                        return $response;
                }
                else if(!$this->validateManagerPrivilege($username))
                {
                        echo "User ". $username . "does not have Manager access.".PHP_EOL;
                        $response = array(
                                "message"=>"User" . $username . "does not have Manager access",
                                "result"=>"false");
                        return $response;
                }
		
		else
		{
			$query = "Select username, reportsto from login where reportsto = '$username' ;";
                        $results = $this->db->query($query);

			 if($results->num_rows > 0)
                        {
				echo "Direct Reports: ".PHP_EOL;
                                while($row = $results->fetch_assoc())
                                {
					echo "".PHP_EOL;
					echo " - Username: " . $row["username"] . " - Manager: " . $row["reportsto"].PHP_EOL;
	                                echo "".PHP_EOL;
                                }

                	}
                        else
                        {
                                echo "0 results for specified results...";
                        }

                }
			
	}
	
	public function CreateTicket($username,$title,$category,$severity,$description,$status)
	{
		$username = $this->db->real_escape_string($username);
		$query= "Insert into Tickets (title, category, Severity, Createdby, description, status) values('$title','$category','$severity','$username','$description','$status');";
		$query.= "Insert into Assignment(TicketID_FK) values (LAST_INSERT_ID());";
		$results = $this->db->multi_query($query);
		echo "Ticket has been created!  ".PHP_EOL;
			

	
	}

	public function AssignTicketToSelf($username, $password, $TicketID)
	{
		$username = $this->db->real_escape_string($username);
                $password = $this->db->real_escape_string($password);
		
		 if(!$this->validateUser($username, $password))
                 {
                        echo "Incorrect password".PHP_EOL;
                        $response = array(
                                "message"=>"Incorrect",
                                "result"=>"false"
                        );
                        return $response;
                 }

		 else
                {
                        $query = "UPDATE login, Assignment SET Assignment.AssignedUser_FK = login.LoginID, login.AssignedTickets = login.AssignedTickets+1 where Assignment.TicketID_FK = '$TicketID' and login.username = '$username';";
                        $results = $this->db->query($query);
                        echo "Ticket ID: " . $TicketID . " has been assigned to " . $username.PHP_EOL;
                }


	}

	public function ManagerAssign($username, $password, $TicketID, $targetuser)
	{
		$username = $this->db->real_escape_string($username);
		$password = $this->db->real_escape_string($password);
		
		 if(!$this->validateUser($username, $password))
                {
                        echo "Incorrect password".PHP_EOL;
                        $response = array(
                                "message"=>"Incorrect",
                                "result"=>"false"
                        );
                        return $response;
                }
                else if(!$this->validateManagerPrivilege($username))
                {
                        echo "User ". $username . "does not have Manager access.".PHP_EOL;
                        $response = array(
                                "message"=>"User" . $username . "does not have Manager access",
                                "result"=>"false");
                        return $response;
                }
		
		else
		{
			$query = "UPDATE login, Assignment SET Assignment.AssignedUser_FK = login.LoginID, login.AssignedTickets = login.AssignedTickets+1 where Assignment.TicketID_FK =     '$TicketID' and login.username = '$targetuser' and login.reportsto = '$username';";
			$results = $this->db->query($query);
			echo "Ticket ID: " . $TicketID . " has been assigned to " . $targetuser.PHP_EOL;
		}
		
	}
		
	
	public function ViewOwnedTickets($username, $password)
	{
		$username = $this->db->real_escape_string($username);
                $password = $this->db->real_escape_string($password);

		if(!$this->validateUser($username, $password))
                {
                        echo "Incorrect password".PHP_EOL;
                        $response = array(
                                "message"=>"Incorrect",
                                "result"=>"false"
                        );
                        return $response;
                }
		
		else
		{
			 $query = "Select * from Tickets where createdby = '$username';";
			
                        $results = $this->db->query($query);

                        if($results->num_rows > 0)
                        {
                                while($row = $results->fetch_assoc())
                                {
                                        echo " - ID: " . $row["TicketID"] . " - title: " . $row["title"] . " - Category: " . $row["Category"] . " - Severity: " . $row["Severity"].PHP_EOL;
                                        echo " - description: " . $row["description"].PHP_EOL;
                                        echo  " - status: " . $row["status"].PHP_EOL;
                                        echo "".PHP_EOL;
                                }

			}
			else
			{
				echo "0 results found.".PHP_EOL;
			}
		}
	}

	public function ViewTicketComment()
	{
		try
		{
			$uri ="mongodb://mohmmad1:test123@ds011872.mlab.com:11872/ticketingsystem1";
			$m = new MongoClient($uri);
			echo "\n" . "Connected to Database sucessfully" . "\n".PHP_EOL;
			$collection = $m->ticketingsystem1->Comments;
			echo "Connected to Collection sucessfully" . "\n".PHP_EOL;

			$cursor = $collection->find();
			foreach($cursor as $id => $value)
			{
				echo "Displaying Result for Comments:" . "\n".PHP_EOL;
				echo "TicketID: " . $value['TicketID_FK_1'] . "  ";
				echo "Comment: " . $value['comments'].PHP_EOL; 
			}
		}

		catch (MongoConnectionException $e) {die("Error connecting to mongodb"); }
		catch (MongoConnectionException $e) {die('Error: ' . $e->getMessage());}
	}
	
	public function sendToMongo()
	{
  		 try 
    		{
      			//Connect to Mongo 
      			$connection = new MongoClient( "mongodb://mohmmad1:test123@ds011872.mlab.com:11872/ticketingsystem1");
      			$mongodb = $connection->selectDB('Comments');
      			echo "collection Login selected sucessfully" . "\n".PHP_EOL;
      			//Connect to MySQL
      			$con=mysqli_connect("localhost","mohmmad","test123","TicketingSystem");
      			//Convert table to PHP Array
      			$query = "select * from CommentsTable;";
      			$result = mysqli_query($con,$query);
      			$rows = array();
      
     			 //Encode to JSON
      			while($r = mysqli_fetch_array($result)) 
      			{
				$rows[] = $r;
      			}
      			//echo json_encode($rows).PHP_EOL;
      			$file = file_get_contents('data.json');
      			$data = json_decode($file);
      			unset($file);
      			file_put_contents('data.json', json_encode($rows));
      			unset($rows);
      			exec("mongoimport -h ds011872.mlab.com:11872 -d ticketingsystem1 -c Comments -u mohmmad1 -p test123 --quiet --jsonArray --drop --file data.json");
      			mysqli_close($con);
		}
		catch (MongoConnectionException $e) 
    		{
      		die('Error connecting to MongoDB server');
    		} 
    		catch (MongoConnectionException $e) 
    		{ 
      		die('Error: ' . $e->getMessage());
    		}

	}
	public function AddComment($username, $password, $TicketID, $addcomment)
	{
		$username = $this->db->real_escape_string($username);
                $password = $this->db->real_escape_string($password);
		if(!$this->validateUser($username, $password))
                {
                        echo "Incorrect password".PHP_EOL;
                        $response = array(
                                "message"=>"Incorrect",
                                "result"=>"false"
                        );
                        return $response;
                }
		
		 else if(!$this->validateManagerPrivilege($username) & !$this->validateOwnerPrivilege($username))
                {
                        echo "User ". $username . "does not have proper access.".PHP_EOL;
                        $response = array(
                                "message"=>"User" . $username . "does not have proper access",
                                "result"=>"false");
                        return $response;
                }

		
		else
		{
			$query = "insert into CommentsTable(comments, TicketID_FK_1) values('$addcomment',(select TicketID from Tickets where TicketID = '$TicketID'));";
                        $results = $this->db->query($query);
			echo "You have add the following comment: " . $addcomment . " to ticket ID: " . $TicketID.PHP_EOL;
			$this->sendToMongo();
			echo $this->ViewTicketComment();
		}
	}

	public function ChangeStatus($username, $password, $status, $TicketID)
	{
		 $username = $this->db->real_escape_string($username);
                $password = $this->db->real_escape_string($password);
                if(!$this->validateUser($username, $password))
                {
                        echo "Incorrect password".PHP_EOL;
                        $response = array(
                                "message"=>"Incorrect",
                                "result"=>"false"
                        );
                        return $response;
                }

                 else if(!$this->validateManagerPrivilege($username) & !$this->validateOwnerPrivilege($username))
                {
                        echo "User ". $username . "does not have proper access.".PHP_EOL;
                        $response = array(
                                "message"=>"User" . $username . "does not have proper access",
                                "result"=>"false");
                        return $response;
                }
		
		else
		{
			$query = "Update Tickets SET status = '$status' where TicketID = '$TicketID';";
                        $results = $this->db->query($query);
			echo "Ticket ID: " . $TicketID . " status has been changed to: " . $status.PHP_EOL;
		}

	}


	public function ManagerTeamReport($username, $password)
	{
		 $username = $this->db->real_escape_string($username);
                $password = $this->db->real_escape_string($password);
                if(!$this->validateUser($username, $password))
                {
                        echo "Incorrect password".PHP_EOL;
                        $response = array(
                                "message"=>"Incorrect",
                                "result"=>"false"
                        );
                        return $response;
                }

                 else if(!$this->validateManagerPrivilege($username) & !$this->validateOwnerPrivilege($username))
                {
                        echo "User ". $username . "does not have proper access.".PHP_EOL;
                        $response = array(
                                "message"=>"User" . $username . "does not have proper access",
                                "result"=>"false");
                        return $response;
                }
		
		else
		{
			$query = "Select * from Tickets INNER JOIN Assignment on Assignment.AssignedUser_FK = login.LoginID;";
			$results = $this->db->query($query);
			echo $this->ManagerReportUser($username, $password);

			if($results->num_rows > 0)
                        {
				echo "Tickets that team owns: ".PHP_EOL;
                                while($row = $results->fetch_assoc())
                                {
                                        echo " - ID: " . $row["TicketID"] . " - title: " . $row["title"] . " - Category: " . $row["Category"] . " - Severity: " . $row["Severity"].PHP_EOL;
                                        echo  " - Created by: " . $row["Createdby"].PHP_EOL;
                                        echo " - description: " . $row["description"].PHP_EOL;
                                        echo  " - status: " . $row["status"].PHP_EOL;
                                        echo "".PHP_EOL;
                                }

                        }
                        else
                        {
                                echo "0 results found.".PHP_EOL;
                        }

		}
	}


}
?>
