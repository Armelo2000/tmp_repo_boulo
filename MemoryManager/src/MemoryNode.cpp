/*
 * MemoryNode.cpp
 *
 *  Created on: 07.01.2023
 *      Author: melah
 */

#include "MemoryNode.h"

MemoryNode::MemoryNode(){
	m_ptFile = nullptr;
	m_ptRawdata = nullptr;
	this->m_circular = nullptr;
}

MemoryNode::MemoryNode(uint16_t blockId, uint32_t size, uint16_t dataId, uint16_t numberOfObj){
	// The nodeId is generate each time the request memory is called
	//m_location = location;
	//m_bufferId = bufferId;
	m_numberOfObjectInRing = numberOfObj;
	if(numberOfObj > 1) {
		m_isRingBuffer = true;
		this->m_circular = new MemoryNode::CircularBuffer(numberOfObj);
	}

	//if(location == ELocation::Eeprom){
		m_ptRawdata = new RawDataObject(blockId, size, dataId);
		m_ptFile = nullptr;
	//}
}

MemoryNode::MemoryNode(string folder, string filename,
			   string ext, uint32_t filesize, uint16_t numberOfobject){
	// The nodeId is generate each time the request memory is called
	//m_location = location;
	//m_bufferId = bufferId;
	m_numberOfObjectInRing = numberOfobject;
	if(numberOfobject > 1){
		m_isRingBuffer = true;
		this->m_circular = new MemoryNode::CircularBuffer(numberOfobject);
	}

	//if((location == ELocation::Flash) || (location == ELocation::SD)){
		m_ptRawdata = nullptr;
		if(1 /* check if there is enough space to log data */){
			//there is enough space
			m_ptFile = new FileObject(folder, filename, ext, filesize, numberOfobject);
		} else{
			//not enough space to log data
			m_ptFile = nullptr;
		}
	//}
}


uint32_t MemoryNode::getBufferId(){
	return m_bufferId;
}
MemoryNode::ELocation MemoryNode::getLocation(){
	return m_location;
}
/**********************************************************************
 * 							Ringspeicher
 *********************************************************************/

MemoryNode::CircularBuffer::CircularBuffer(uint16_t maxElement): m_size(0), m_readPos(0), m_writePos(0),
		  m_remainingToRead(0), m_isEmpty(true), m_maxElement(maxElement){
}

uint16_t MemoryNode::CircularBuffer::capacity(){
	return this->m_size;
}

bool MemoryNode::CircularBuffer::isEmpty(){
	return this->m_isEmpty;
}

void MemoryNode::CircularBuffer::goToNextWritePointer(){
	//Anzahl von Einträge die gelesen werden können erhöt sich
	//um 1 falls diese noch nicht die maximale Anzahl erreicht hat.
	if(this->m_remainingToRead < this->m_maxElement)
		this->m_remainingToRead++;

	this->m_writePos++;

	if(this->m_writePos >= this->m_maxElement){
		this->m_writePos = 0;
		if(this->m_isEmpty == true)
			this->m_isEmpty = false;
	}

}

void MemoryNode::CircularBuffer::goToNextReadPointer(){
	//Anzahl von Einträge die gelesen werden können verringern sich um 1
	//falls es noch mindesten ein ungelesene Eintrag im Ringspeicher gibt.
	if(this->m_remainingToRead > 0){
		this->m_remainingToRead--;

		this->m_readPos++;

		if(this->m_readPos >= this->m_maxElement){
			this->m_readPos = 0;
		}
	}

}

uint32_t MemoryNode::CircularBuffer::getMaxEntry(){
	return this->m_maxElement;
}
