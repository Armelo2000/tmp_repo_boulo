/*
 * Persistable.h
 *
 *  Created on: 07.01.2023
 *      Author: melah
 */

#ifndef MEMORYMANAGER_INC_PERSISTABLE_H_
#define MEMORYMANAGER_INC_PERSISTABLE_H_

#include <stdint.h>

class Persistable{

public:
	/*
	 * This is the type of object to persist
	 * This could be:
	 * 		- ParamObject
	 * 		- MessageObject
	 *
	 */
	enum class ObjectType{
		ParamObject,
		MessageObject,
		InfoObject,
	};

	ObjectType m_objectType;
	uint32_t bufferId;
	uint32_t size;
	uint8_t* data;

};






#endif /* MEMORYMANAGER_INC_PERSISTABLE_H_ */
