function TestInputType(elem, strRegExp, strError) {
                var ret = elem.value;

                var charpos = elem.value.search(strRegExp);
                if (elem.value.length == 0 || charpos >= 0) {
                               elem.style.backgroundColor = 'lightblue';
                               alert(strError);
                               if (charpos >= 0)
                                               ret = setCharAt(ret, charpos,'?');
                }
                return ret;
}

function setCharAt(str,index,chr) {
                if(index > str.length-1) return str;
                return str.substr(0,index) + chr + str.substr(index+1);
}


function vT(elem) { // validate text
                elem.style.backgroundColor = '#ffc';
                //\w inneholder 0-9 og "_"
                elem.value = TestInputType(elem, "[^A-Za-z,-9: ]", "Alphabetic chars, space, comma, dot and semicolon only");
                //elem.value = TestInputType(elem, "[^A-Za-z,-9: æåøÆÅØ]", "Alphabetic chars, space, comma, dot and semicolon only");
}

function vN(elem, max) { // validate number
                vN2(elem, 0, max);
}

function vN2(elem, min, max) { // validate number
                elem.style.backgroundColor = '#ffc';
                if (elem.value < min || elem.value > max) {
                               elem.style.backgroundColor = 'lightblue';
                               alert("Permitted between " + min + " and " + max);
                               elem.value = max;
                }
                
                if(isNaN(elem.value)) {
                               alert("Only numbers permited");
                               elem.value = max;
                }
                //TestInputType(elem, "[^0-9]", "Only numbers permited");
}

function vP(elem) { // validate password (4 chars)
                elem.style.backgroundColor = '#ffc';
                if (elem.value.length != 4) {
                               elem.style.backgroundColor = 'lightblue';
                               alert("Format: 4 characters");
                               elem.value = "----";
                }
                vT(elem);
}

function vD(elem) { // validate date
                var temp;
                var intTemp;
                
                elem.style.backgroundColor = '#ffc';
                if (elem.value.length != 10) {
                               elem.style.backgroundColor = 'lightblue';
                               alert("Format: dd-mm-yyyy");
                }
                
                if(elem.value.charAt(2) != '-' || elem.value.charAt(5) != '-')
                               alert("Format: dd-mm-yyyy");
                
                temp = elem.value.substring(0, 2);
                intTemp = parseInt(temp, 10);
                
                if(intTemp < 1 || intTemp > 31)
                               alert("Format: dd-mm-yyyy");
                
                temp = elem.value.substring(3, 5);
                intTemp = parseInt(temp, 10);
                
                if(intTemp < 1 || intTemp > 12)
                               alert("Format: dd-mm-yyyy");
                               
                temp = elem.value.substring(6, 10);
                intTemp = parseInt(temp, 10);
                
                if(intTemp < 1000 || intTemp > 3000)
                               alert("Format: dd-mm-yyyy");
}


function vTi(elem) { // validate time
                var temp;
                var intTemp;
                
                elem.style.backgroundColor = '#ffc';
                if (elem.value.length != 8) {
                               elem.style.backgroundColor = 'lightblue';
                               alert("Format: hh:mm:ss");
                }
                
                if(elem.value.charAt(2) != ':' || elem.value.charAt(5) != ':')
                               alert("Use \":\" as seperator");
                
                temp = elem.value.substring(0, 2);
                intTemp = parseInt(temp, 10);
                
                if(intTemp == "NaN"|| intTemp < 1 || intTemp > 24) // isNaN(temp) 
                               alert("Format: hh:mm:ss");
                
                temp = elem.value.substring(3, 5);
                intTemp = parseInt(temp, 10);
                
                if(intTemp == "NaN" || intTemp < 1 || intTemp > 59)
                               alert("Format: hh:mm:ss");
                               
                temp = elem.value.substring(6, 8);
                intTemp = parseInt(temp, 10);
                
                if(intTemp == "NaN" || intTemp < 1 || intTemp > 59) {
                	alert("Format: hh:mm:ss");
                }
}

function verifyMask(element) {
                if (element.value.length > 0){
                               verifyIP (element, "");
                }
}

function verifyIP (elem, defaultIP) {
                var IPvalue = elem.value;
errorString = "";
theName = "IPaddress";
elem.style.backgroundColor = '#ffc';

var ipPattern = /^(\d{1,3})\.(\d{1,3})\.(\d{1,3})\.(\d{1,3})$/;
var ipArray = IPvalue.match(ipPattern);

if (IPvalue == "0.0.0.0") {
                errorString = errorString + theName + ': '+IPvalue+' is a special IP address and cannot be used here.';
                elem.style.backgroundColor = 'lightblue';
                elem.value = defaultIP;
}
else if (IPvalue == "255.255.255.255") {
                errorString = errorString + theName + ': '+IPvalue+' is a special IP address and cannot be used here.';
                elem.style.backgroundColor = 'lightblue';
                elem.value = defaultIP;
}

if (ipArray == null) {
                errorString = errorString + theName + ': '+IPvalue+' is not a valid IP address.';
                elem.style.backgroundColor = 'lightblue';
                elem.value = defaultIP;
}
else {
for (i = 0; i < 4; i++) {
thisSegment = ipArray[i];
if (thisSegment > 255) {
errorString = errorString + theName + ': '+IPvalue+' is not a valid IP address.';
elem.style.backgroundColor = 'lightblue';
elem.value = defaultIP;
i = 4;
}
if ((i == 0) && (thisSegment > 255)) {
errorString = errorString + theName + ': '+IPvalue+' is a special IP address and cannot be used here.';
elem.style.backgroundColor = 'lightblue';
elem.value = defaultIP;
i = 4;
      }
   }
}
extensionLength = 3;
if (errorString != "")
alert (errorString);
}


