/*
 * Memory.cpp
 *
 *  Created on: 07.01.2023
 *      Author: melah
 */

#include "Memory.h"

Memory::Memory(EMemoryType type, uint32_t memoryId, uint32_t size):
				m_memoryId(memoryId), m_memorySize(size),
				m_type(type){
	this->m_memoryNodeCount = 0;
	if(type == Memory::EMemoryType::Eeprom){
		m_shadow = new ShadowMemory(size/2);

	}
}
Memory::~Memory(){

}

void Memory::registerMemoryNode(MemoryNode* memoryNode){
	if(memoryNode == nullptr) return;

	this->m_memoryNodeList.push_back(memoryNode);
}

uint32_t Memory::getMemoryId(){
	return this->m_memoryId;
}
uint32_t Memory::getMemorySize(){
	return this->m_memorySize;
}
uint32_t Memory::getMemoryNodeCount(){
	return this->m_memoryNodeCount;
}
Memory::EMemoryType Memory::getMemoryType(){
	return this->m_type;
}

MemoryNode* Memory::findNodeInMemory(uint32_t dataid){
	for(MemoryNode* node : this->m_memoryNodeList){
		if(node->m_ptRawdata != nullptr){
			if(node->m_ptRawdata->getDataID() == dataid)
				return node;
		}
	}
	// Keine passende Memory wurde gefunden
	return nullptr;
}

void Memory::addMemoryNode(MemoryNode* node, uint16_t blockId, uint32_t size, uint16_t numberOfObj){
	if(node == nullptr) return;

	if(node->m_ptRawdata != nullptr){
		//node->
	}
}
