#include "ComponentMemory.h"
#include <memory>

using namespace becs;

ComponentMemory::ComponentMemory(uint32_t compSize) {

    m_compSize = compSize;
    m_capacity = 1;
    m_count = 0;

    m_rawMemory = new unsigned char[m_compSize * m_capacity];
    
}

becs::ComponentMemory::ComponentMemory(ComponentMemory&& move) {

    m_rawMemory = move.m_rawMemory;
    m_capacity = move.m_capacity;
    m_compSize = move.m_compSize;
    m_count = move.m_count;
    move.m_rawMemory = nullptr;
    move.m_capacity = 0;
    move.m_compSize = 0;
    move.m_count = 0;
}

unsigned char* ComponentMemory::get(uint32_t index) {
    if (index >= m_count)return nullptr;

    return &m_rawMemory[index * m_compSize];

}

void ComponentMemory::set(uint32_t index, void* raw) {
    if (index >= m_count)return;
    
    memcpy_s(&m_rawMemory[index * m_compSize], m_compSize, raw, m_compSize);

}

void ComponentMemory::reserved(uint32_t count) {
    if (count <= m_capacity)return;
    
    
    m_capacity = count;
    size_t newCapacitySize = m_capacity * m_compSize;
    unsigned char* temp = new unsigned char[newCapacitySize];
    memcpy_s(m_rawMemory, newCapacitySize, m_rawMemory, m_compSize * m_count);
   
    if(m_rawMemory != nullptr)
    delete[] m_rawMemory;
    
  
    m_rawMemory = temp;

}

void ComponentMemory::push_back(void* raw) {

    m_count++;
    if (m_capacity <= m_count)resize();
    uint32_t index = m_count - 1;
    if (raw != nullptr)
        memcpy_s(&m_rawMemory[index * m_compSize], m_compSize, raw, m_compSize);
    
}

size_t ComponentMemory::getComponentSize()
{
    return m_compSize;
}

size_t ComponentMemory::getComponentCount()
{
    return m_count;
}

size_t becs::ComponentMemory::getAllocatedMemory() {
    return m_capacity * m_compSize;
}

void ComponentMemory::resize() {
    
    m_capacity += 5;
    size_t newCapacitySize = m_capacity * m_compSize;
    unsigned char* temp = new unsigned char[newCapacitySize];
    
    if (m_rawMemory != nullptr) {

        memcpy_s(temp, newCapacitySize, m_rawMemory, m_compSize * m_count);
        delete[] m_rawMemory;
    }
  
    m_rawMemory = temp;
}
