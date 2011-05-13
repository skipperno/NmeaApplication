<? 

//**!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! 
//**TCP_CLIENT_CLASS_DEFINITION*********************************************** 
//** The TcpClient class encapsulates most networking communication details 
//** into an easy-to-use wrapper. Connections are not persistant. 

class TcpClient 
{ 
//** (Integer) the internal underlying socket identifier. 

var $Socket = TcpClientNoConnection; 

//** (String) the name/IP of the remote host 

var $Host; 

//** (Integer) the port number to connect to remote host. 

var $Port = 0; 

//** (String) the last error that occurred (NULL if no error). 

var $LastError = null; 

//** (String) the newline character to be used when sending data. 

var $NewLine = TcpClientNewLine; 

//** (Integer) the size of the buffer used to receive data. 

var $ReceiveBufferSize = TcpClientMinBufferSize; 

//** (Integer) the number of milliseconds to wait before aborting a connect, 
//** read, or write operation for the client. 

var $Timeout = TcpClientDefaultTimeout; 

//** creates a new TcpClient instance based on the hostname and port given. 

function TcpClient($remoteHost=null, $portNum=0) 
{ 
$this->Host = strval($remoteHost); 
$this->Port = intval(max(0, $portNum)); //** ensure port >= than zero. 
} 
//** Returns: Boolean 
//** Determine whether or not a connection to the remote host has been 
//** established. 

function isOpen() 
{ 
return ($this->Socket ? true : false); 
} 
//** Returns: String 
//** Get the last recorded error that occurred. If no error previously 
//** occurred NULL is returned. The last error is cleared. 

function GetError() 
{ 
$theerror = $this->LastError; 
$this->ClearError(); 
return $theerror; 
} 
//** Returns: None 
//** Clear the last error stored for this client. 

function ClearError() 
{ 
$this->LastError = null; 
} 
//** Returns: Boolean 
//** Attemept to connect to the client remote host on the port number given. 
//** If no host is available FALSE is returned and no connection is made. 
//** If FALSE is returned the last error is available from the 'GetError()' 
//** method. 

function Connect() 
{ 
$this->ClearError(); //** clear any existing error messages. 

//** no host name/IP has been set for this client, no connection can be made. 
//** Store the appropriate error. 

if(strlen(trim($this->Host)) == 0) 
{ 
$this->LastError = "No remote host was provided"; 
return false; 
} 
//** attempt to connect to the host on the port given. Record any error number 
//** and error message generated. 

$errorNum = 0; 
$this->Socket = fsockopen($this->Host, $this->Port, &$errorNum, 
&$this->LastError, ($this->Timeout / 1000)); 

//** if there is no error given and the socket is valid connection is okay. 

return ($this->isOpen() && strlen(trim($this->LastError)) == 0); 
} 
//** Returns: Boolean 
//** Attempt to close the open client connection. 

function Close() 
{ 
//** no open cobnnection is available. Set error appropriately. 

if(!$this->isOpen()) 
$this->LastError = "No connection available to close"; 

//** an open connection is available to close. Close underlying socket. 

else 
{ 
fclose($this->Socket); //** clsoe the connection. 
$this->Socket = TcpClientNoConnection; //** no connection now. 
} 
return !$this->isOpen(); //** return the close operation success. 
} 
//** Returns: Integer 
//** Attempt to write the data given to the underlying socket. The number of 
//** bytes successfully written to the stream is returned. If no connection 
//** is available 0 is returned, as no bytes were written. 

function Write($data=null) 
{ 
//** no connection is available, zero bytes can be sent. 

if(!$this->isOpen()) 
{ 
$this->LastError = "No connection available for writing"; 
return 0; 
} 
$data = strval($data); //** ensure that data is available. 
if(strlen($data) == 0) //** no data to be sent. 
return 0; //** zero bytes were sent. 
else //** connection and data, set timeout and send. 
{ 
//$this->_SetTimeout(); //** set timeout. 
return fwrite($this->Socket, $data, strlen($data)); //** write data. 
} 
} 
//** Returns: Integer 
//** Attempt to write the data given to the underlying socket, followed by a 
//** newline. The newline is defined by the '$this->NewLine' property. The 
//** number of bytes actually written is returned. 

function WriteLine($data=null) 
{ 
return $this->Write($data . $this->NewLine); 
} 
//** Returns: String 
//** Attempt to read the number of bytes given (or one by default) from the 
//** connection. If no connection is available, the length given is zero or 
//** negative, or an error occurs NULL is returned. 

function Read($length=1) 
{ 
if(intval($length) <= 0) 
{ 
$this->LastError = "Cannot read zero or less bytes"; 
return null; 
} 
//** no connection is available to read from, no data can be read. 

else if(!$this->isOpen()) 
{ 
$this->LastError = "No connection available for reading"; 
return null; 
} 
else //** a valid connection identifier is available. 
{ 
$this->_SetTimeout(); //** ensure timeout is set. 
return fread($this->Socket, $length); //** attempt to read n-bytes. 
} 
} 
//** Returns: String 
//** Attempt to read one full line from the underlying stream. If no 
//** connection is available NULL is returned. Any newline characters 
//** are included in the string returned. 

function ReadLine() 
{ 
//** no connection is available to read from, no data can be read. 

if(!$this->isOpen()) 
{ 
$this->LastError = "No connection available for reading"; 
return null; 
} 
//** continue to read in data until a line ends with the newline character(s). 
//** This is safe as the 'fgets()' function will not read past a newline 
//** character. Ensure that the read buffer is at least the minumum size. If 
//** one iteration is complete and no data was read in the socket blocking 
//** expired. Stop reading at that point. 

$streamdata = ""; //** no data to start with. 
$sockethasexpired = false; //** initially no timeout experienced. 

while(!$this->_EndsWithNewLine($streamdata) && !$sockethasexpired) 
{ 
$this->_SetTimeout(); //** ensure socket timeout is set. 

$streamdata .= fgets($this->Socket, 23); // max(TcpClientMinBufferSize, 
//$this->ReceiveBufferSize)); 

//** if ever at the point where reading has occurred and no data is available 
//** a socket timeout has occurred. Exit the loop and set the error. 

if(strlen($streamdata) == 0) 
{ 
$sockethasexpired = true; 
return "The read took longer than $this->Timeout ms"; 
//$this->LastError = "The read took longer than $this->Timeout ms"; 
} 
} 
return $streamdata; //** return the data received, including newline. 
} 
//** Returns: Boolean 
//** Determine whether or not the string given ends with a newline character. 
//** If no data is given FALSE is returned. 

function _EndsWithNewLine($data=null) 
{ 
$data = strval($data); //** ensure that data is a string. 
if(strlen($data) == 0) //** no date given to test. 
return false; //** does not end with newline. 

//** get the position of the last newline character. If the value returned 
//** is not numeric it is a boolean, indicating no match. Considered to end 
//** with newline if it ends with either a '\n' or '\r' character. 

$creturnpos = strrpos($data, "\r"); //** position of '\n'. 
$newlinepos = strrpos($data, "\n"); //** position of '\r'. 

return (is_int($newlinepos) || is_int($creturnpos)); 
} 
//** Returns: None 
//** Set the underlying socket timeout to the 'Timeout' value for this 
//** instance. If not connected nothing is done. 

function _SetTimeout() 
{ 
//** if a connection is available set the socket timeout. Get the number of 
//** seconds and microseconds form the instance 'Timeout' property. 

if($this->isOpen()) 
{ 
stream_set_timeout($this->Socket, intval($this->Timeout / 1000), 
intval(($this->Timeout % 1000) * 1000)); 
} 
} 
} 
?> 
