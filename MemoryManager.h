#pragma once




#include "Types.h"
#include <unordered_map>
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
		template<typename T> const T& getComponentByEntID(becs::EntityID entID, becs::ComponentID compID);

#define _ENABLE_DEBUG
#ifdef  _ENABLE_DEBUG
		void debug();
#endif //  _ENABLE_DEBUG

		
		

	private:
		std::vector<std::unordered_map<becs::ComponentID, uint32_t>> m_indexTable;
		std::vector<becs::ComponentMemory> m_componentMemory;
		



	};



}

template<typename T>const T& becs::MemoryManager::getComponentByEntID(becs::EntityID entID, becs::ComponentID compID) {

	if (m_indexTable[entID].find(compID) == m_indexTable[entID].end()) {
		
		throw std::exception("Error");
		return T();
	}
	uint32_t index = m_indexTable[entID].at(compID);
	return reinterpret_cast<const T&>(*m_componentMemory[compID].get(index));
}