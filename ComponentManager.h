#pragma once
#include "Types.h"
class ComponentManager {

public:

	becs::ComponentID registerComponent();
	becs::ComponentID getLastIndex();

private:
	uint32_t m_counter = 0;




};

