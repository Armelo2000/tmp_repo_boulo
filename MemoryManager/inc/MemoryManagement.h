/*
 * MemoryManagement.h
 *
 *  Created on: 07.01.2023
 *      Author: melah
 */

#ifndef MEMORYMANAGER_INC_MEMORYMANAGEMENT_H_
#define MEMORYMANAGER_INC_MEMORYMANAGEMENT_H_


#include "Memory.h"
#include "Persistable.h"

enum class EBlockID{
	infoBlock = 0x0001,
	paraBlock = 0x0002,
	defaultParaBlock = 0x0003,
	messageBlock = 0x0004

};
class MemoryManagement{

public:
	vector<Memory*> m_memoryList;
	uint32_t m_memoryCount;

	MemoryManagement();
	~MemoryManagement();


	bool requestMemory(Persistable* persistObject);
	Memory* getMemoryById(uint32_t id);
	void readData();
	void writeData();

	void readMemory(Memory* memory);
	void readMemory(uint8_t* dst, Memory* memory, uint32_t addr, uint32_t size);
	uint32_t readMemory4Bytes(Memory* memory, uint32_t addr);
	uint16_t readMemory2Bytes(Memory* memory, uint32_t addr);
	uint8_t readMemory1Byte(Memory* memory, uint32_t addr);
	void readBlock(Memory* memory, MemoryNode* node);
	void writeBlock(Memory* memory, MemoryNode* node);


private:
	void registerMemory(Memory* memory);


};






#endif /* MEMORYMANAGER_INC_MEMORYMANAGEMENT_H_ */
