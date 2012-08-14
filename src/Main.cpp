/*
 * Main.cpp
 *
 *  Created on: 2. mai 2011
 *      Author: Ernad Secic
 */

#include <iostream>
#include <stdio.h>

#include "comm/TcpServer.h"
#include "comm/AD7997.h"
#include "MsgInHandler.h"
#include "data/Alarm.h"
#include "data/GpioInputEvent.h"

#include "data/Data.h"
#include "data/DataProvider.h"

#include "json/reader.h"
#include "json/writer.h"
#include "json/elements.h"

#include "webserver/Webserver.h"

#include <sstream>
#include <pthread.h>

#include "utility/CheckSum.h"
#include "utility/Log.h"

#include "definitions.h"

#include "InitMultiBox.h"
#include "data/DataTransceiver.h"

void * runMsgInHandlerThread(void *ptr);


int nEchoSounderPort = 2004;
int nDataPort = 2005;

DataProvider dataProvider;
pthread_t threadMsgInHandler;


int main(int argc, char **argv) {
	AD7997 ad7997;

	InitMultiBox initMultiBox;
	if (!initMultiBox.searchNewConfiguration())
		initMultiBox.setDefaultConfiguration();
	initMultiBox.setConfiguration();


	Alarm::initAlarm();
	ad7997.startMeasuringAD7997();


	/*using namespace json;

	string* jsonText = new std::string("asdf");
	Object obj;
	char * posts = "{\"posts\":[{\"contentName\":\"Jm\",\"contentName2\":\"Jm2\",\"contentLength\":\"00:00:31\"}]}";

	jsonText->clear();
	jsonText->append(posts);

	jsonText->append("\0");
	std::istringstream stdi(*jsonText);

	try {
		json::Reader::Read(obj, stdi);
		const String& strName0 = obj["posts"][0]["contentName2"];
		//std::cout << "First beer name: " << strName0.Value() << std::endl;

		printf("11111 %s", strName0.Value().c_str()); //"Value" is "std::basic_string"
		delete jsonText;
		printf("2222222222222222222222222\n");
	} catch (json::Exception& e) {
		printf("exception parsing JSON: %s", e.what());
		delete jsonText;
		//return;
	}
*/
	//TEST TEST
	printf("Version 1.5 (with integrated server and websocket)\n");
	//cout << "Hei 2 !!!" << endl; // prints !!!Hello World!!!

	/*TcpServer tcpServerEcho;
	tcpServerEcho.serverSocket_start(nEchoSounderPort);

	TcpServer tcpServerData;
	tcpServerData.serverSocket_start(nDataPort);*/

	dataProvider.startDataProvider();

	MsgInHandler msgInHandler;

	pthread_create(&threadMsgInHandler,   NULL, runMsgInHandlerThread, (void*) &msgInHandler);

	GpioInputEvent gpioInputEvent; // CREATE THREAD FOR WAITING ON EVENTS
	//DataTransceiver abc;
	//abc.setTransceiver(1, "0 1 3000 0 4000");
	Webserver webServer;
	webServer.mainLoop();
}

void * runMsgInHandlerThread(void *ptr) {

	((MsgInHandler*)ptr)->runHandler(); // !!! Blocking function
	return 0;
}
