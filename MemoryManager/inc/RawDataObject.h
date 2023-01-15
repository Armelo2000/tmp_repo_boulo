/*
 * RawDataObject.h
 *
 *  Created on: 24.11.2022
 *      Author: tsa
 */

#ifndef RAWDATAOBJECT_H_
#define RAWDATAOBJECT_H_

#include "Common.h"

class RawDataObject{

public:
	//RawDataObject(){};
	RawDataObject(uint16_t blockId, uint16_t size, uint16_t dataId = 0): m_blockId(blockId), m_dataId(dataId), m_size(size), m_prevSize(size){

	}
	uint32_t m_startAddrr1;
	uint32_t m_startAddrr2;

	uint16_t m_size;
	uint16_t m_prevSize;
	uint8_t* m_data;

	uint16_t getBlockID(){
		return m_blockId;
	}
	uint16_t getDataID(){
		return m_dataId;
	}

private:
	uint16_t m_blockId{0};
	uint16_t m_dataId{0};


};





#endif /* RAWDATAOBJECT_H_ */
