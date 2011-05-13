<?php

//functions to srip out variables from JS -> PHP		 
	function curPageURL($pageURL) {
	//funciton to strip out which line of the echo gram were on
		$search=strpos($pageURL,"?line=");
		$searchEnd=strpos($pageURL,"?colour=");
			if($search===false){
				$pageURLextension="home";
			}else{
				$search = $search+6;
				$length=$searchEnd-$search;
				$pageURLextension=substr($pageURL,$search,$length);
			}
		 return $pageURLextension;
	}
	
	function curPageURLcolour($pageURL) {
	//function to strip out how meny colours the user wants to be displayed
		$search=strpos($pageURL,"?colour=");
		$searchEnd=strpos($pageURL,"?gain=");
			if($search===false){
				$pageURLextension="home";
			}else{
				$search = $search+8;
				$length=$searchEnd-$search;
				$pageURLextension=substr($pageURL,$search,$length);
			}
		 return $pageURLextension;
	}
	function curPageURLGain($pageURL) {
	//function to strip out grate the gain is
		$search=strpos($pageURL,"?gain=");
			if($search===false){
				$pageURLextension="home";
			}else{
				$search = $search+6;
				$length=strlen($pageURL);
				$pageURLextension=substr($pageURL,$search,$length);
			}
		 return $pageURLextension;
	}
	

function myTest($lineID){
$lineID = $lineID % 129;
	$file = file_get_contents("NMEA_testdata_echosounder.csv", true);
	$searchID = '$PSKPES,400,'; //thing which we want from the file
	$dataStreamLine = explode($searchID, $file); //substring line from file
	return $dataStreamLine[$lineID];
	//$dataValuesArray = explode(",",$dataStreamLine[$curPageURL]); //puls all data from  dataStreamLine for line 130
}	

function makeTable($dataValuesArray, $curPageURLcolour){
	//makes output to return to JavaScript table 
	//256 RGB values givven maths provides lower ranges from
	 
	foreach($dataValuesArray as $key => $value){ 
		//for each line of the Array from the $file take each, as $value and use the $key as its location on screen
		$value = ($value/200)*256; //for colour bit calculations
		//$value = ($value/$curPageURLcolour)*256; //for colour bit calculations
		$value = round($value); // makes the colour value a whole number - makes it easier to assign RGB value
		
		echo '<div style="height:1px; top:'.$key.'; background-color:rgb(0,'.$value.','.$value.')"> </div> ';
	}
}

?>
