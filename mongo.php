<?php

class loginMDB
{
	private $db;
	private $ini;

	public function __construct($inifile)
	{
		$this->ini = parse_ini_file($inifile, true);
		$host = $this->ini['loginMDB']['host'];
		$this->db = new MongoClient($host);
		
	
		if($this->db->connect_errno > 0)
		{
			echo __FILE__.":".__LINE__.": failed to connect to database, re: ".$this->db->connect_error.PHP_EOL;
                        exit(0);
		}
		else { echo "Connection to database successfully";}

	}
	

	public function __destruct()
	{
		$this->db-close();
	}

	public function DBfind()
	{
		$collection = $this->db->login;
                echo "Collection has been selected".PHP_EOL;

                $cursor = $collection->find();


                foreach ($cursor as $document)
                {
                        echo $document["title"] . "\n";
                }

	}


}

$test = new loginMDB();

$test->DBfind();


?>
