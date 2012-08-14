/*
 * MimeTypes.cpp
 *
 *  Created on: Sep 26, 2011
 *      Author: ernad
 */

#include "MimeTypes.h"
#include <string.h>

const char * extension[] = { "html", "js", "css", "png", "ico"}; //, "sh"};
const char * mimeType[] = { "text/html", "application/x-javascript",
		"text/css", "image/png", "image/x-icon"};//, "/usr/bin/php-cgi"};

MimeTypes::MimeTypes() {
	// TODO Auto-generated constructor stub

}

MimeTypes::~MimeTypes() {
	// TODO Auto-generated destructor stub
}

bool MimeTypes::getMimeType(const char* fileName, char* returnMimeType) {
	char* recExtension;
	const char* nDotPointer= strstr(fileName, ".");
	if (nDotPointer == NULL)
		return false;

	if (strlen(nDotPointer)< 3)
		return false;

	recExtension = (char*)(nDotPointer + 1);

		switch (recExtension[0]) { //TODO: only first char is checked !!!!!!!!
		case 'h':
			strcpy(returnMimeType, mimeType[0]);
			return true;
			break;
		case 'j':
			strcpy(returnMimeType, mimeType[1]);
			return true;
			break;
		case 'c':
			strcpy(returnMimeType, mimeType[2]);
			return true;
			break;
		case 'p':
			strcpy(returnMimeType, mimeType[3]);
			return true;
			break;
		case 'i':
			strcpy(returnMimeType, mimeType[4]);
			return true;
			break;
		/*case 's':
			strcpy(returnMimeType, mimeType[5]);
						return true;
						break;*/
		default:

			break;
		}


	return false;
}
