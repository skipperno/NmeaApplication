<?php
include('TcpClient.php');
$index = 1;
$myTest = 1;

//////////////////////////////
// parse received parameter
//////////////////////////////
if( $_REQUEST["index"] )
{
   $index = $_REQUEST['index'];
   //echo "Msg type: ". $type;
}

// don't remove this yet:
//url finder from the server - used in AJAX call to server - to pass variables to the server from the JavaScript
/*	$pageURL = 'http';
	if ($_SERVER["HTTPS"] == "on") {$pageURL .= "s";}
		$pageURL .= "://";
	if ($_SERVER["SERVER_PORT"] != "80") {
		$pageURL .= $_SERVER["SERVER_NAME"].":".$_SERVER["SERVER_PORT"].$_SERVER["REQUEST_URI"];
	} else {
		$pageURL .= $_SERVER["SERVER_NAME"].$_SERVER["REQUEST_URI"];
	}
*/
//echo myTest($index);
/*
$curPageURL = curPageURL($pageURL);
	$curPageURLcolour = curPageURLcolour($pageURL);
	$curPageURLGain = curPageURLGain($pageURL);

//function fileLoader($lineID){
	$file = file_get_contents("NMEA_testdata_echosounder.csv", true);
	$searchID = '$PSKPES,400,'; //thing which we want from the file
	$dataStreamLine = explode($searchID, $file); //substring line from file
	$dataValuesArray = explode(",",$dataStreamLine[$curPageURL]); //puls all data from  dataStreamLine for line 130

//makeTable($dataValuesArray, $curPageURLcolour);
*/


//////////////////////////////
// connect to main program
//////////////////////////////
$client = new TcpClient("127.0.0.1", 2004); 
$client->Timeout = 2000; 
$client->NewLine = "\r\n"; 
$client->ReceiveBufferSize = 17000;

$client->Connect();

//////////////////////////////
// send and recevie to main program
//////////////////////////////
$client->WriteLine("Hei");
$line = $client->ReadLine();
$client->Close();

//////////////////////////////
// send back to browser
//////////////////////////////
print($line);
//print("<b> From target: " . $line . "</b><br>");

?>