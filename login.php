<?php

require_once("logindb.php.inc");

function print_help()
{
  echo "usage: ".PHP_EOL;
  echo __FILE__." -u <username> -p <password> -l <privilegeLevel> -c <command arguments...>".PHP_EOL;
}

if ($argc < 2)
{
   print_help();
   exit(0);
}

$cArgs = array();

for ($i = 0; $i < $argc;$i++)
{
  if (($argv[$i] === "-h") ||
      ($argv[$i] === "--help"))
  {
      print_help();
      exit(0);
  }
// -u is to specify the user that will log on
  if ($argv[$i] === '-u')
  {
    $username = $argv[$i + 1];
    $i++;
    continue;
  }

// -p is to specify the users password that will be entered
  if ($argv[$i] === '-p')
  {
    $password = $argv[$i + 1];
    $i++;
    continue;
  }
  
// -pl is to specify the privilege level of user
  if ($argv[$i] === '-pl')
  {
    $privilegeLevel = $argv[$i + 1];
    $i++;
    continue;
  }
  
// -c is to specify the command/function that will be executed from php script
  if ($argv[$i] === '-c')
  {
    $command = $argv[$i + 1];
    $i++;
    continue;
  }
  
// -tu is to specify the target user that you are editing
  if ($argv[$i] === '-tu')
  {
    $targetuser = $argv[$i + 1];
    $i++;
    continue;
  }

// -tid is to specify a ticket by ID number field  
  if ($argv[$i] === '-tid')
  {
	$TicketID = $argv[$i + 1];
	$i++;
	continue;
  }

// -nu is to specify the name of a new user
  if ($argv[$i] === '-nu')
  {
	$newusername = $argv[$i +1];
	$i++;
	continue;
  }

// -np is to specify the password of a new user
  if ($argv[$i] === '-np')
  {
	$newpassword = $argv[$i + 1];
	$i++;
	continue;
  }

// -rt is to specify who the new user will report to
  if ($argv[$i] === '-rt')
  {
	$reportsto = $argv[$i + 1];
	$i++;
	continue;
  }

// -ti is to specify the title of ticket
  if ($argv[$i] === '-ti')
  {
	$title = $argv[$i + 1];
	$i++;
	continue;
  }
 
// -ct is to specify the category of the ticket ie. Hardware, Software
  if($argv[$i] === '-ct')
  {	
	$category = $argv[$i + 1];
	$i++;
	continue;
  }

// -sl is to specify the severity level
  if ($argv[$i] === '-sl')
  {
	$severity = $argv[$i + 1];
	$i++;
	continue;
  }

// -des is to specify the description of the issue
  if ($argv[$i] === '-des')
  {
	$description = $argv[$i + 1];
	$i++;
	continue;
  }

// -st is to specify the status of the ticket
  if($argv[$i] === '-st')
  {
	$status = $argv[$i + 1];
	$i++;
	continue;
  }

// -at is to assign the ticket to a user
  if($argv[$i] === '-at')
  {
	$assignedto = $argv[$i + 1];
	$i++;
	continue;
  }

// -ac is to add a comment to a ticket
  if ($argv[$i] === '-ac')
  {
	$addcomment = $argv[$i + 1];
	$i++;
	continue;
  }

// -fn is to specify fieldname when editing ticket
  if($argv[$i] === '-fn')
  {
	$fieldname = $argv[$i + 1];
	$i++;
	continue;
  }

// -in is to specify input that will be entered in field
  if($argv[$i] === '-in')
  {
	$input = $argv[$i + 1];
	$i++;
	continue;
  }
  $cArgs[] = $argv[$i];  
}

if (!isset($command))
{
   echo "no command specified".PHP_EOL;
   print_help();
   exit(0);
}

switch ($command)
{
  case 'validatePW':
   $login = new loginDB("login.ini");
   if ($login->validateUser($username,$password))
   {
      echo "password validated!!!".PHP_EOL;
   }
   else
   {
      echo "password does not validate!".PHP_EOL;
   }
   break;
 
 case 'addNewUser':
   $login = new loginDB("login.ini");
   $login->addNewUser($username,$password,$privilegeLevel,$newusername,$newpassword, $reportsto,$cArgs[0]);
    break;

  case 'ModifyUserRole':
  $login = new loginDB("login.ini");
  $login->ModifyUserRole($username, $password, $targetuser, $privilegeLevel, $cArgs[0]);
  break;

  case 'ValidateUserPrivilege':
  $login = new loginDB("login.ini");
  $login->validateUserPrivilege($username, $cArgs[0]);
  break;
 
  case 'ViewTickets':
  $login = new loginDB("login.ini");
  $login->ViewTickets($username, $password, $cArgs[0]);
  break;

  case 'DeleteTicket':
  $login = new loginDB("login.ini");
  $login->DeleteTicket($username, $password, $TicketID, $cArgs[0]);
  break;

  case 'ManagerReportUser':
  $login = new loginDB("login.ini");
  $login->ManagerReportUser($username, $password, $cArgs[0]);
  break;	 

  case 'CreateTicket':
  $login = new loginDB("login.ini");
  $login->CreateTicket($username, $title, $category, $severity, $description, $status, $assignedto, $cArgs[0]);
  break;

  case 'AssignTicket':
  $login = new loginDB("login.ini");
  $login->ManagerAssign($username, $password, $TicketID, $targetuser, $cArgs[0]);
  break;

  case 'ViewOwnedTickets':
  $login = new loginDB("login.ini");
  $login->ViewOwnedTickets($username,$password,$cArgs[0]);
  break;

  case 'AddComment':
  $login = new loginDB("login.ini");
  $login->AddComment($username, $password, $TicketID, $addcomment,$cArgs[0]);
  break;

  case 'ChangeStatus':
  $login = new loginDB("login.ini");
  $login->ChangeStatus($username, $password, $status, $TicketID,$cArgs[0]);
  break;

  case 'AssignTicketToSelf':
  $login = new loginDB("login.ini");
  $login->AssignTicketToSelf($username, $password, $TicketID, $cArgs[0]);
  break;

  case 'ManagerTeamReport':
  $login = new loginDB("login.ini");
  $login->ManagerTeamReport($username, $password,$cArgs[0]);
  break;

  case 'EditTicket':
  $login = new loginDB("login.ini");
  $login->EditTicket($username,$password,$fieldname,$input,$TicketID,$cArgs[0]);
  break;
}

?>
