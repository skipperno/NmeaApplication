/*
 * MimeTypes.h
 *
 *  Created on: Sep 26, 2011
 *      Author: ernad
 */

#ifndef MIMETYPES_H_
#define MIMETYPES_H_

class MimeTypes {
public:
	MimeTypes();
	virtual ~MimeTypes();

	static bool getMimeType(const char* fileName, char* returnMimeType);
};

#endif /* MIMETYPES_H_ */
