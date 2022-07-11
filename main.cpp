#include <iostream>
#include "../becs.h"


typedef struct Pos {
	int x, y;
};
typedef struct Health {
	int currentHealth;
	int maxHealth;
};
typedef struct Vel {
	int x, y;
};

typedef struct PlayerTag {
	bool isPlayer = true;
};

typedef struct MerchantTag {
	bool isMerchant = true;
};

typedef struct Damage {
	int critChance;
	int damage;
	int multiplyer;
};

void physics(BECS * ecs, ComponentID posID, ComponentID velID) {
	int posSize, velSize;
	QueryComponent posQuery = ecs->getComponent(posID);
	QueryComponent velQuery = ecs->getComponent(velID);
	

	std::cout << "Positons: ComponentID: " << posQuery.m_ID << '\n';
	for (int i = 0; i < posQuery.m_arryCount; i++) {

		MemCell* pos = &posQuery.m_compArry[i];
		Pos* posPtr = reinterpret_cast<Pos*>(pos->m_comp);
		if (pos->isValid)
		std::cout << "EntityID: " << pos->m_entOwner << " X: " << posPtr->x << " Y: " << posPtr->y << '\n';

	}
	std::cout << "Velocity: ComponentID: " << velQuery.m_ID << '\n';
	for (int i = 0; i < velQuery.m_arryCount; i++) {

		MemCell* vel = &velQuery.m_compArry[i];

		Vel* velPtr = reinterpret_cast<Vel*>(vel->m_comp);
		if(vel->isValid)
		std::cout << "EntityID: " << vel->m_entOwner << " X: " << velPtr->x << " Y: " << velPtr->y << '\n';
	}


}

void initPhyiscs(BECS* ecs, ComponentID posID, ComponentID velID) {
	int posSize, velSize;
	QueryComponent posQuery = ecs->getComponent(posID);
	QueryComponent velQuery = ecs->getComponent(velID);

	

	for (int i = 0; i < posQuery.m_arryCount; i++) {

		MemCell* pos = &posQuery.m_compArry[i];
		if (pos->isValid) {
			Pos* posPtr = reinterpret_cast<Pos*>(pos->m_comp);
			posPtr->x = 2;
			posPtr->y = 3;
		}
		
		
	}
	for (int i = 0; i < velQuery.m_arryCount; i++) {

		MemCell* vel = &velQuery.m_compArry[i];

		Vel* velPtr = reinterpret_cast<Vel*>(vel->m_comp);
		if (vel->isValid) {
			velPtr->x = 1;
			velPtr->y = 0;
		}
		
	}

}


void displayComponentBind(BECS* ecs, EntityID id, const char* name) {
	unsigned int size;
	ComponentID* arry = ecs->getComponentBinded(id, &size);
	std::cout << "Entity Name: " << name << " Entity ID: " << id << '\n';
	std::cout << "ComponentID: ";
	for (int i = 0; i < size; i++) {
		std::cout << " " << arry[i];
	}
	std::cout << '\n';
}


int main() {

	BECS ecs;
	ComponentID PosID = ecs.registerComponent(sizeof(Pos));
	ComponentID HealthID = ecs.registerComponent(sizeof(Health));
	ComponentID VelID = ecs.registerComponent(sizeof(Vel));
	ComponentID PlayerTagID = ecs.registerComponent(sizeof(PlayerTag));
	ComponentID MerchantTagID = ecs.registerComponent(sizeof(MerchantTag));
	ComponentID DamageID = ecs.registerComponent(sizeof(Damage));

	EntityID person = ecs.createEntity();
	EntityID rock = ecs.createEntity();
	EntityID merchant = ecs.createEntity();

	


	ecs.addComponent(person, PosID);
	ecs.addComponent(person, HealthID);
	ecs.addComponent(person, VelID);
	ecs.addComponent(person, PlayerTagID);


	ecs.addComponent(rock, PosID);
	ecs.addComponent(rock, VelID);

	ecs.addComponent(merchant, PosID);
	ecs.addComponent(merchant, HealthID);
	ecs.addComponent(merchant, MerchantTagID);
	
	displayComponentBind(&ecs, person, "Person");
	displayComponentBind(&ecs, rock, "Rock");
	displayComponentBind(&ecs, merchant, "Merchant");
	std::cout << "\n\n";
	initPhyiscs(&ecs, PosID, VelID);
	physics(&ecs, PosID, VelID);
	std::cout << "\n\n";

	ecs.removeComponent(person, VelID);

	displayComponentBind(&ecs, person, "Person");
	displayComponentBind(&ecs, rock, "Rock");
	displayComponentBind(&ecs, merchant, "Merchant");
	std::cout << "\n\n";
	initPhyiscs(&ecs, PosID, VelID);
	physics(&ecs, PosID, VelID);
	std::cout << "\n\n";

	ecs.addComponent(person, DamageID);
	ecs.addComponent(person, VelID);
	
	displayComponentBind(&ecs, person, "Person");
	displayComponentBind(&ecs, rock, "Rock");
	displayComponentBind(&ecs, merchant, "Merchant");
	std::cout << "\n\n";
	initPhyiscs(&ecs, PosID, VelID);
	physics(&ecs, PosID, VelID);
	std::cout << "\n\n";

	return 0;
}