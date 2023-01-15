/*
 * Memory.h
 *
 *  Created on: 07.01.2023
 *      Author: melah
 */

#ifndef MEMORYMANAGER_INC_MEMORY_H_
#define MEMORYMANAGER_INC_MEMORY_H_

#include "MemoryNode.h"

class Memory{
public:
	enum class EMemoryType{
		Eeprom = 0x01,
		Flash = 0x02,
		SD = 0x03
	};

	class ShadowMemory{
	public:
		/***************************************************************
		 * Start adresse für den Speicher im Sector 1
		 ***************************************************************/
		uint32_t startAddrSector1;

		/***************************************************************
		 * Start adresse für den Speicher im Sector 2
		 ***************************************************************/
		uint32_t startAddrSector2;

		/***************************************************************
		 * Freie Speicherplatz im Sector 1
		 ***************************************************************/
		uint32_t freeSpaceSector1;

		/***************************************************************
		 * Freie Speicherplatz im Sector 2
		 ***************************************************************/
		uint32_t freeSpaceSector2;

		/***************************************************************
		 * verwendete Speicherplatz im Sector 1
		 ***************************************************************/
		uint32_t usedSpaceSector1;

		/***************************************************************
		 * verwendete Speicherplatz im Sector 2
		 ***************************************************************/
		uint32_t usedSpaceSector2;

		/***************************************************************
		 * nächste freie Speicherplatz im Sector 1
		 ***************************************************************/
		uint32_t nextfreeSpaceSector1;

		/***************************************************************
		 * nächste freie Speicherplatz im Sector 2
		 ***************************************************************/
		uint32_t nextfreeSpaceSector2;

		ShadowMemory(uint32_t startSector2):
			startAddrSector1(0), startAddrSector2(startSector2),
			freeSpaceSector1(startSector2), freeSpaceSector2(startSector2),
			usedSpaceSector1(0), usedSpaceSector2(0),
			nextfreeSpaceSector1(0), nextfreeSpaceSector2(startSector2){

		}

	};

	/******************************************************************
	 * Start Kennung für die Datensicherung
	 ******************************************************************/
	const uint32_t SK = 0xCACACACA;

	// the list can be used like in Parameter
	vector<MemoryNode*> m_memoryNodeList;
	ShadowMemory* m_shadow{nullptr};

private:
	/***************************************************
	 * Diese variable ist der SpeicherId
	 ***************************************************/
	uint32_t m_memoryId;

	/*******************************************************
	 * Diese variable ist die gesamte Speichergröße
	 *******************************************************/
	uint32_t m_memorySize;

	/**********************************************************************
	 * Diese member variable ist die gesamte Anzahl von registrierte Node
	 * im Speicher
	 *********************************************************************/
	uint32_t m_memoryNodeCount;

	/*********************************************************************
	 * Der Speicher typ wird hier gesichert. Es kann:
	 * 		- Eeprom
	 * 		- Flash
	 * 		- SD
	 * sein.
	 *********************************************************************/
	EMemoryType m_type;


public:

	Memory(EMemoryType type, uint32_t memoryId, uint32_t size);
	~Memory();

	uint32_t getMemoryId();
	uint32_t getMemorySize();
	uint32_t getMemoryNodeCount();
	EMemoryType getMemoryType();

	/*******************************************************************
	 * Diese Routine sucht ein registriert MemoryNode in Speicher mit
	 * dem gegebenen DatenId. Falls die MemoryNode nicht gefunden ist,
	 * soll nullptr zurückgegeben werden.
	 ******************************************************************/
	MemoryNode* findNodeInMemory(uint32_t dataid);

	/******************************************************************
	 * Function um neue Node im Speicher hinzufügen.
	 ******************************************************************/
	void addMemoryNode(MemoryNode* node, uint16_t blockId, uint32_t size, uint16_t numberOfObj);

	void registerMemoryNode(MemoryNode* memoryNode);


private:
	//void registerMemoryNode(MemoryNode* memoryNode);





};






#endif /* MEMORYMANAGER_INC_MEMORY_H_ */
