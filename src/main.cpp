#include <Windows.h>
#include <iostream>
#include <thread>
#include "../include/ComponentManager.h"
#include "../include/EntityManager.h"
#include "../include/ErrorHandling.h"
/*


typedef struct _Pos{
    int x;
    int y;
    static ComponentID id;
}Pos;

typedef struct _LevelData{
    int width, height;
    char * mapData;
    static ComponentID id;
}LevelData;

typedef struct _Tail {
    std::vector<Pos> tailSegments;
    static ComponentID id;
}Tail;


ComponentID Pos::id = ComponentManager::registerComp(sizeof(Pos));
ComponentID LevelData::id = ComponentManager::registerComp(sizeof(LevelData));
ComponentID Tail::id = ComponentManager::registerComp(sizeof(Tail));

static EntityID snakeEntID = EntityManager::registerEntity();
static EntityID LevelEntID = EntityManager::registerEntity();


class System {
   
public:
    ~System()
    {
        
        if(levelDataptr != INVALID_ENTITY_OBJ)delete[] levelDataptr->mapData;
    }

    static bool initSnake(const EntityObj& snake) {

        System::snakeHeadptr = reinterpret_cast<Pos*>(EntityCreator::getComponent(snake, Pos::id));
        System::snakeTailSegmentsptr = reinterpret_cast<Tail*>(EntityCreator::getComponent(snake, Tail::id));

        if (snakeHeadptr == nullptr || snakeTailSegmentsptr == nullptr)return false;
        std::cout << "initSnake address: " << levelDataptr << '\n';
        snakeHeadptr->x = levelDataptr->width / 2;
        snakeHeadptr->y = levelDataptr->height / 2;

        if (snakeHeadptr->x <= 0 || snakeHeadptr->y) {
            ECS::ErrorHandling::logError("Invalid x and y", "System", "static bool initSnake", 56);
            std::cout << "width: " << levelDataptr->width << " height: "  << levelDataptr->height << '\n';
            return false;
        }

        snakeTailSegmentsptr->tailSegments.reserve(50);
        return true;
    }

    static bool initMap(int width, int height, const EntityObj& level) {

        levelDataptr = reinterpret_cast<LevelData*>(EntityCreator::getComponent(level, LevelData::id));
        if (levelDataptr == nullptr) {
            return false;
        }

        levelDataptr->height = height;
        levelDataptr->width = width;
        levelDataptr->mapData = new char[width * height];
        
        std::cout << "initMap address: " << levelDataptr << '\n';
        std::cout << "width: " << levelDataptr->width << " height: " << levelDataptr->height << '\n';
        if (levelDataptr->height <= 0 || levelDataptr->width <= 0)return false;

        return true;

    }

    static bool drawMap() {
        
        if (INVALID_ENTITY_OBJ == levelDataptr) {
            return false;
        }
        if (levelDataptr->height <= 0 || levelDataptr->width <= 0) {
            std::cout << "drawMap fail!\n";
            return false;
        }

        int width = levelDataptr->width, height = levelDataptr->height;
        int snakeX = snakeHeadptr->x, snakeY = snakeHeadptr->y;
        std::vector<Pos>* snakeSegment = &snakeTailSegmentsptr->tailSegments;
        char* mapData = levelDataptr->mapData;
        DWORD lpByteWritten;
        for (size_t y = 0; y < height; y++) {
            for (size_t x = 0; x < width; x++){

                if (x == 0 || x == width - 1 || (y == 0 || y == height - 1)) {
                    mapData[x + y * width] = '#';
                }
                else if (x == snakeX && y == snakeY) {
                    mapData[x + y * width] = '@';
                }
                else {
                    mapData[x + y * width] = ' ';
                }



            }
            WriteConsoleOutputCharacterA(GetStdHandle(STD_OUTPUT_HANDLE), &mapData[y * width], width, {0, (SHORT)y}, &lpByteWritten);
        }
        return true;
    }

private:
    static LevelData* levelDataptr;
    static Pos* snakeHeadptr;
    static Tail* snakeTailSegmentsptr;
};
LevelData* System::levelDataptr = nullptr;
Pos* System::snakeHeadptr = nullptr;
Tail* System::snakeTailSegmentsptr = nullptr;

class SnakeGame{

public:
    SnakeGame(){
        EntityManager::BindComponentToEnt(snakeEntID, Pos::id);
        EntityManager::BindComponentToEnt(snakeEntID, Tail::id);
        EntityManager::BindComponentToEnt(LevelEntID, LevelData::id);
       

        snake = EntityCreator::createEntity(snakeEntID);
        level = EntityCreator::createEntity(LevelEntID);
        if (!System::initMap(35, 25, level)) {
            std::cout << "Map initialization fail\n";
            isRunning = false;
        }

        if (!System::initSnake(snake)) {
            std::cout << "Snake initialization fail\n";
            isRunning = false;
        }

       
       
    }

    static void Run() {
        
        while (isRunning){
            
            isRunning = System::drawMap();

        }

    }
    ~SnakeGame()
    {
      
    }

private:
    static bool isRunning;
    
    EntityObj snake;
    EntityObj level;


};

bool SnakeGame::isRunning = true;

*/


//debug
typedef struct _vector2 {
    int x, y;
    static ComponentID id;
}vector2;

typedef struct _vectorArray {
    std::vector<vector2> arrayObj;
    static ComponentID id;
}vectorArray;

ComponentID vector2::id = ComponentManager::registerComp(sizeof(vector2));
ComponentID vectorArray::id = ComponentManager::registerComp(sizeof(vectorArray));
int main(){

    EntityID ent1 = EntityManager::registerEntity();
    EntityManager::BindComponentToEnt(ent1, vector2::id);
    EntityManager::BindComponentToEnt(ent1, vectorArray::id);

    EntityObj obj = EntityCreator::createEntity(ent1);
    vector2* vec2 = reinterpret_cast<vector2*>(EntityCreator::getComponent(obj, vector2::id));
    vectorArray* verArr = reinterpret_cast<vectorArray*>(EntityCreator::getComponent(obj, vectorArray::id));
    vec2->x = 5;
    vec2->y = 10;



    std::cout << vec2->x << " " << vec2->y;
    verArr->arrayObj.push_back(vector2());
    std::cout << vec2->x << " " << vec2->y;
    /*SnakeGame game;
    game.Run();
    
    ECS::ErrorHandling::displayAllErrors();*/


    return 0;
}
