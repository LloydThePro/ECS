#pragma once

#include <cstdint>




namespace becs {


	class ComponentMemory {

	public:

		ComponentMemory(uint32_t compSize);
		ComponentMemory(ComponentMemory&& move);
		ComponentMemory(const ComponentMemory&) = delete;
		ComponentMemory(ComponentMemory&) = delete;
		ComponentMemory& operator=(ComponentMemory&) = delete;
		ComponentMemory& operator=(const ComponentMemory&) = delete;
		ComponentMemory& operator=(ComponentMemory&&) = delete;


		unsigned char* get(uint32_t index);
		void set(uint32_t index, void* raw);
		void reserved(uint32_t size);
		void push_back(void* raw);
		size_t getComponentSize();
		size_t getComponentCount();
		size_t getAllocatedMemory();


	private:
		void resize();



	private:

		unsigned char* m_rawMemory;
		uint32_t m_compSize;
		uint32_t m_capacity;
		uint32_t m_count;





	};


}

