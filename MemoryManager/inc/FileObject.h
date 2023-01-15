/*
 * FileObject.h
 *
 *  Created on: 24.11.2022
 *      Author: tsa
 */

#ifndef FILESYSOBJECT_H_
#define FILESYSOBJECT_H_

#include "Common.h"


class FileObject{

public:

	FileObject(){
		m_fileName = "log";
		m_extension = "txt";
		m_maxFileSize = 2048;  // 2KB
		m_numberOfFile = 1;
		m_isRingBuffer = false;
	}
	FileObject(string folder, string filename, string ext, uint32_t filesize /* in KB */, uint16_t numberofFile):
		m_folder(folder), m_fileName(filename),
		m_extension(ext), m_maxFileSize(filesize*1024), m_numberOfFile(numberofFile){
		if(numberofFile > 1) m_isRingBuffer = true;
	}

	void save(FileObject* file);
	void restore(FileObject* file);


	void init();


//protected:
	uint32_t m_index{1};
	string m_log;			//data to log

//protected:
	string m_folder;
	string m_fileName;
	string m_extension;
	uint32_t m_maxFileSize;		// in Byte

	/*
	 * Information for the ring buffer
	 */
	uint16_t m_numberOfFile{1};
	bool m_isRingBuffer{false};

};





#endif /* FILESYSOBJECT_H_ */
