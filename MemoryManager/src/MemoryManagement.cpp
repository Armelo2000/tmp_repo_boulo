/*
 * MemoryManagement.cpp
 *
 *  Created on: 07.01.2023
 *      Author: melah
 */

#include "MemoryManagement.h"

MemoryManagement::MemoryManagement(){
	m_memoryCount = 0;
}
MemoryManagement::~MemoryManagement(){

}

bool MemoryManagement::requestMemory(Persistable* persistObject){
	bool ret = false;
	if(persistObject == nullptr) return ret;

	for(auto memory : m_memoryList){
		if(persistObject->bufferId == memory->getMemoryId()){
			//The memory where the persistObject belong to is found
			for(auto memoryNode : memory->m_memoryNodeList){
				if(memoryNode->getBufferId() == persistObject->bufferId){

				}
			}

			break;
		}
	}


	return ret;
}
void MemoryManagement::registerMemory(Memory* memory){
	if(memory == nullptr) return;

	m_memoryCount++;
	m_memoryList.push_back(memory);
}

void MemoryManagement::readMemory(Memory* memory){

	if(memory == nullptr) return;

	if(memory->getMemoryType() == Memory::EMemoryType::Eeprom){
		if(memory->m_shadow != nullptr){

			//read all blocks in memory sector 1
			//Byte 0..3 for StartAddress Sector 1
			//Byte 4..7 for StartAddress Sector 2
			//Byte 8 and 9 for CRC
			// Blocks with data start at Byte 10
			for(uint32_t addr=memory->m_shadow->nextfreeSpaceSector1; addr<memory->m_shadow->startAddrSector2; ){
				//read 8 Bytes
				// 	- 4 Bytes for the start symbol (ss)
				auto ss = readMemory4Bytes(memory, addr);
				//addr += 4;
				if(memory->SK == ss){
					auto blockIdAndLength = readMemory4Bytes(memory, addr+4);
					//addr += 4;
					// 	- 2 Bytes for the Block Id
					uint16_t blockId = (blockIdAndLength >> 16) & 0xFFFF;
					// 	- 2 Bytes for the length
					uint16_t length = blockIdAndLength & 0xFFFF;
					auto dataId = readMemory4Bytes(memory, addr+8);
					addr = length;
					memory->m_shadow->nextfreeSpaceSector1 += length;

					//suchen ob die node schon registriert wurden.
					auto node = memory->findNodeInMemory(dataId);

					if(node != nullptr){
						//node existiert schon in der Liste. Daten wiederherstellen



					}else{
						//node existiert noch nicht in der Liste. Neue Node erstellen
						// und registrieren.

						MemoryNode* nodeNew = new MemoryNode(blockId, length, dataId, 1);
						memory->registerMemoryNode(nodeNew);
						//nodeNew->m_ptRawdata->

					}

					if((blockId == 0x0005) || (blockId == 0x0006)){
						//parameter - 0x0005
						//default parameter - 0x0006
						//read

					}


				}else{
					break;
				}
			}

		}
	}

}

uint32_t MemoryManagement::readMemory4Bytes(Memory* memory, uint32_t addr){


	return 0;
}
uint16_t MemoryManagement::readMemory2Bytes(Memory* memory, uint32_t addr){

	return 0;
}
uint8_t MemoryManagement::readMemory1Byte(Memory* memory, uint32_t addr){

	return 0;
}

void MemoryManagement::readBlock(Memory* memory, MemoryNode* node){

}
void MemoryManagement::writeBlock(Memory* memory, MemoryNode* node){

}
void MemoryManagement::readMemory(uint8_t* dst, Memory* memory, uint32_t addr, uint32_t size){

}
