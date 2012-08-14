/*
 * FileAccess.h
 *
 *  Created on: Feb 8, 2012
 *      Author: ernad
 */

#ifndef FILEACCESS_H_
#define FILEACCESS_H_

class FileAccess {
public:
	FileAccess();
	virtual ~FileAccess();

	bool addBottomMsg(int nBottom);
	bool addMsg(const char* mainDirectory,
			const char* fileName, const char* msg, int nMsgLength);

	static void notifySettingsChanged();
	static bool createDirectoryIfNotExist(const char* newDirectory);
private:
	void getSettingsAsString(char* msg);
};

#endif /* FILEACCESS_H_ */
