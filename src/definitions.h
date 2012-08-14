/*
 * definitions.h
 *
 *  Created on: Mar 9, 2012
 *      Author: ernad
 */

#ifndef DEFINITIONS_H_
#define DEFINITIONS_H_

//////////////////////////////////////////////////////////////
///////////    		DEBUG MESSAGES        ////////////////////
//////////////////////////////////////////////////////////////

//#define NORMAL_DEBUG

#ifdef NORMAL_DEBUG
	#define DEBUG_SENT_ACK
#else // manual choice of debug messages
	#define DEBUG_SENT_ACK
#endif

//////////////////////////////////////////////////////////////
///////////     END DEBUG MESSAGES        ////////////////////
//////////////////////////////////////////////////////////////


///////////////////////////////////////////////
#define MAIN_CONFIG_DIR							"/opt/conf"
#define MAIN_CONFIG_FILE						"mainConfig.txt"
#define TRANSCEIVER_CONFIG_DIR					"/opt/conf/trans"
#define SD_CARD_DIR									"tmp/myTest" // "/media/mySD"
#define NEW_CONFIG_FILE							"newConfig.txt"
///////////////////////////////////////////////


#define CONFIG_COMMENT_VERSION "** Do not edit this line. That is version of ....\n"
#define CONFIG_COMMENT_IP      "** IP address of Multi Box. E.g. 10.31.1.130\n"

#define CONFIG_COMMENT_GAIN		"** GAIN [%]. Min: 0, Max: 100\n"
#define CONFIG_COMMENT_TVG		"** TVG [%].  Min: 0, Max: 100\n"
#define CONFIG_COMMENT_FREQ		"** FREQUENCY [%].  Min: 0, Max: 100\n"
#define CONFIG_COMMENT_POW		"** POWER [%].  Min: 0, Max: 100\n"
#define CONFIG_COMMENT_ALARML		"** ALARML [%].  Min: 0, Max: 100\n"
#define CONFIG_COMMENT_ALARMH		"** ALARMH [%].  Min: 0, Max: 100\n"
#define CONFIG_COMMENT_RANGE		"** RANGE [%].  Min: 0, Max: 100\n"

#define DEFAULT_CONFIG_VERSION  "1.0.1"
#define DEFAULT_MULTIBOX_IP 	"10.31.1.130"
#define DEFAULT_GAIN 			10
#define DEFAULT_TVG 			10
#define DEFAULT_FREQ 			10
#define DEFAULT_POW 			10
#define DEFAULT_ALARML 			2
#define DEFAULT_ALARMH 			1500
#define DEFAULT_RANGE 			1

#define DEFAULT_BAUD_RATE_INDEX 			0 // 4800

//'chEnabled' : 0,'transPos': 1,'freq1' : 3000,'dualEnabled' : 0,'freq2' : 4000

#define DEFAULT_TRANSCEIVER_CH_ENAB 	0
#define DEFAULT_TRANSCEIVER_POS 		0
#define DEFAULT_TRANSCEIVER_FREQ 		50
#define DEFAULT_TRANSCEIVER_DUAL_ENAB 	0

/*
enum msgType {
	GET_FILE_QUEUE = 0x01, SEND_SHORT_QUEUE, // 0x02
	SEND_SHORT_COMP_QUEUE, // 0x03
	SEND_LONG_QUEUE, // 0x04
	SEND_LONG_QUEUE_END, // 0x05
	SEND_FILE = 0x10,
	SEND_FILE_END, // 0x11
	GET_FILE, // 0x12
	DELETE_FILE, // 0x13
	REJECT_FILE, // 0x14
	ACK = 0x80,
	RESEND_PACKAGE, // 0x81
	ACK_QUERY, // 0x82
	RESEND_PACKAGES, // 0x83
	SEND_PROXY_SHORT = 0xA0,
	SEND_PROXY_SHORT_COMPR, // 0xA1
	SEND_PROXY_LONG, // 0xA2
	RESEND_ACK, // 0xA3
	RESUME_SENDING, // 0xA4
	ACK_SEQ,
	SEND_FILE_MSG, // !!! NOT Virtek type, used internt
};
*/

#endif /* DEFINITIONS_H_ */
