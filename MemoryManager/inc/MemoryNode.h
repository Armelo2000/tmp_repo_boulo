/*
 * MemoryNode.h
 *
 *  Created on: 07.01.2023
 *      Author: melah
 */

#ifndef MEMORYMANAGER_INC_MEMORYNODE_H_
#define MEMORYMANAGER_INC_MEMORYNODE_H_



//#include "GPFCommon/Common.h"
#include <FileObject.h>
#include "RawDataObject.h"

class MemoryNode{

public:
	enum class ELocation{
		Eeprom = 0x01,
		Flash = 0x02,
		SD = 0x03
	};

	class CircularBuffer{
	private:
		/*****************************************************
		 * Anzahl der aktuelle Einträge im Ring
		 *****************************************************/
		uint16_t m_size;

		/****************************************************
		 * Maximal Anzahl der Einträge, was der Ring haben
		 * kann.
		 ***************************************************/
		uint16_t m_maxElement;

		/****************************************************
		 * Index für die Lese-position
		 ***************************************************/
		uint16_t m_readPos;

		/****************************************************
		 * Index für die Schreib-position
		 ***************************************************/
		uint16_t m_writePos;

		/******************************************************
		 * Anzahl von Einträge die noch gelesen werden müssen
		 *****************************************************/
		uint16_t m_remainingToRead;

		/******************************************************
		 * Flag für den Status von Ringspeicher (leer oder voll)
		 *****************************************************/
		bool m_isEmpty;

	public:

		CircularBuffer(uint16_t maxElement);

		/****************************************************************
		 * Diese Routine gibt an, die aktuelle Anzahl von Einträge im
		 * Ringspeicher.
		 *
		 * @return uint16_t, aktuelle Anzahl von Einträge
		 *
		 ***************************************************************/
		uint16_t capacity();

		/****************************************************************
		 * Diese Routine gibt an, ob der ring leer oder voll ist
		 *
		 * @return bool, true heißt dass, der Ringspeicher leer ist und
		 * 				 false heißt dass, der Ringspeicher voll ist.
		 ***************************************************************/
		bool isEmpty();


		/*********************************************************
		 * Diese Routine setzt den Schreibzeiger auf den nächste
		 * Schreib-bereich
		 *********************************************************/
		void goToNextWritePointer();

		/*********************************************************
		 * Diese Routine setzt den Lesezeiger auf den nächste
		 * Lese-bereich
		 *********************************************************/
		void goToNextReadPointer();

		/*********************************************************
		 * Diese Routine gibt die maximale Anzahl von Ring puffer
		 * @return uint32_t, max. Anzahl von Einträge was der Ring-
		 * 					 puffer kann
		 *********************************************************/
		uint32_t getMaxEntry();

	};

	FileObject* m_ptFile{nullptr};
	RawDataObject* m_ptRawdata{nullptr};

	MemoryNode();

	MemoryNode(uint16_t blockId, uint32_t size, uint16_t dataId, uint16_t numberOfObj);

	MemoryNode(string folder, string filename,
				   string ext, uint32_t filesize, uint16_t numberOfobject);

	uint32_t getBufferId();
	ELocation getLocation();

	void write();
	void read();

	~MemoryNode() {};

protected:
	uint16_t m_numberOfObjectInRing{1};
	bool m_isRingBuffer{false};

private:
	ELocation m_location;
	uint32_t m_bufferId;
	uint32_t m_memoryNodeId;
	CircularBuffer* m_circular;

};







#endif /* MEMORYMANAGER_INC_MEMORYNODE_H_ */
