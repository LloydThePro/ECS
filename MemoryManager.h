#pragma once




#include "Types.h"
#include <unordered_map>
#include <queue>
#include <exception>
#include "ComponentMemory.h"


namespace becs {
	
	class MemoryManager {

	public:




		void initEntityMemory();
		void initComponentMemory(size_t compSize);
		void addComponentInstance(becs::ComponentID compID, becs::EntityID entID);
		unsigned char* getComponent(EntityID entID, ComponentID compID);
		bool hasComponent(EntityID entID, ComponentID compID);
		

		void freeAllCompMemFromEnt(EntityID entID,const std::vector<ComponentID>& compIDs);
		size_t getCompMemoryAllocSize(ComponentID compID);

	private:
		
		std::vector<std::unordered_map<becs::ComponentID, uint32_t>> m_indexTable;
		std::vector<becs::ComponentMemory> m_componentMemory;
		std::vector<std::queue<uint32_t>> m_freeMemory;



	};



}

