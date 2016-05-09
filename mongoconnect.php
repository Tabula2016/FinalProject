<?php

$uri = "mongodb://mohmmad1:test123@ds011872.mlab.com:11872/ticketingsystem1";



try {
	$m = new MongoClient($uri);
	echo "Sucessfull";
	
	echo "Collection Selected sucessfully";

       $collection = $m->ticketingsystem1->login;
       	
	echo "collection Login selected sucessfully";
	$Users = array('username' => 'mohmmad');
	$cursor = $collection->find($Users);
       	foreach ($cursor as $id => $value) {
                echo "$id: ";
	       var_dump( $value );	
       	}

}
catch (MongoConnectionException $e) {
	die('Error connecting to MongoDB server');
} catch (MongoConnectionException $e) { 
	die('Error: ' . $e->getMessage());

}

// close the connection
$m->close();
?>
