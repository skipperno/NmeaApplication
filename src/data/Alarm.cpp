/*
 * Alarm.cpp
 *
 *  Created on: Jan 23, 2012
 *      Author: ernad
 */

#include "Alarm.h"
#include "Data.h"
#include "../comm/GpioCortex.h"

int currentAlarmState = 0;
int alarmUnconfirmed = 0;

int alarmSenderId = 1;

#define  HYSERESIS  5 // [m]

// const char* RELAY_OUT_GPIO = "48"; // used for PXA310
const char* RELAY_OUT_GPIO = "58";    // used for PXA320
GpioCortex gpioCortexReleyOut;

Alarm::Alarm() {
	// TODO Auto-generated constructor stub

}

Alarm::~Alarm() {
	// TODO Auto-generated destructor stub
}

int Alarm::initAlarm(){
	gpioCortexReleyOut.setOutputHigh(false);
	gpioCortexReleyOut.configureGpioAsOutput(RELAY_OUT_GPIO);
	return 0;
}

int Alarm::updateAlarmState(int nBottom) {
	const Number Al_L  = Data::getInstance()->getAlarmL();
	const Number Al_H  = Data::getInstance()->getAlarmH();
	int nBottomMeter = nBottom/10;

	if (currentAlarmState == 0) {
		if(nBottomMeter <= Al_L.Value()) {
			currentAlarmState = 1; 	// state: alarm SHALLOW
			alarmUnconfirmed = 1;  	// unconfirmed SHALLOW
			gpioCortexReleyOut.setOutputHigh(true);
		} else if(nBottomMeter >= Al_H.Value()) {
			currentAlarmState = 2; 	// state: alarm DEEP
			alarmUnconfirmed = 2; 	// unconfirmed DEEP
			gpioCortexReleyOut.setOutputHigh(true);
		}
	} else if ((nBottomMeter > Al_L.Value() + HYSERESIS) && (nBottomMeter < Al_H.Value() - HYSERESIS)) {
		currentAlarmState = 0; // alarm end
	//			showAlarmMsg(false);
	}

	return currentAlarmState + (alarmUnconfirmed << 2); // first 2 bytes are alarm state. Bit No. 3 and 4 are "alarm confirmed"
}

void Alarm::confirmAlarm(){
	alarmUnconfirmed = 0;
	gpioCortexReleyOut.setOutputHigh(false);
}

bool Alarm::isAlarmState() {
	return (currentAlarmState > 0);
}

bool Alarm::isConfirmed() {
	return (alarmUnconfirmed > 0);
}

void Alarm::setAlarmSenderId(int alarmId){
	alarmSenderId = alarmId;
}


int Alarm::getAlarmSenderId(){
	return alarmSenderId;
}

