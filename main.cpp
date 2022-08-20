#include <iostream>
#include <GLSimp2DGraphics.h>
#include <chrono>
#define _DEBUG_MODE_ENABLED

#include "BECS.h"




struct Rect {
	float x, y, w, h;
	static becs::ComponentID id;
};


struct Velocity {
	float x, y;
	static becs::ComponentID id;
};

struct Color {
	s2d::S2D_COLOR color;
	static becs::ComponentID id;
};

becs::ComponentID Velocity::id;
becs::ComponentID Color::id;
becs::ComponentID Rect::id;
class MyApp {

public:

	MyApp() {

		srand(time(0));

		m_window = new s2d::S2DWindow(m_width, m_height, m_title, S2D_NO_RESIZE);

		m_graphics = new s2d::S2DGraphics(*m_window);
		m_graphics->setVSYNC(true);
		Velocity::id = m_ecs.registerComponent(sizeof(Velocity));
		Color::id = m_ecs.registerComponent(sizeof(Color));
		Rect::id = m_ecs.registerComponent(sizeof(Rect));


		m_drawFilter = m_ecs.createFilter();
		m_moveFilter = m_ecs.createFilter();
		m_coloredFilter = m_ecs.createFilter();
		m_noColorFilter = m_ecs.createFilter();

		

		m_ecs.addComponentToFilter(m_drawFilter, Rect::id);
		m_ecs.addComponentToFilter(m_drawFilter, Color::id);

		m_ecs.addComponentToFilter(m_moveFilter, Rect::id);
		m_ecs.addComponentToFilter(m_moveFilter, Velocity::id);


		m_ecs.addComponentToFilter(m_coloredFilter, Rect::id);
		m_ecs.addComponentToFilter(m_coloredFilter, Color::id);
		m_ecs.addComponentToFilter(m_coloredFilter, Velocity::id);

		m_ecs.addComponentToFilter(m_noColorFilter, Rect::id);
		m_ecs.addComponentToFilter(m_noColorFilter, Velocity::id);

		m_queries = new becs::QueryComponent[MAX_QUERIES];
		
		for (uint32_t i = 0; i < 1000; i++) {
			spawnColoredEntitySystem();
		}
	}


	void spawnColoredEntitySystem() {
		
		becs::EntityID id = m_ecs.createEntity();

		m_ecs.bindComponentToEnt(id, Rect::id);
		m_ecs.bindComponentToEnt(id, Color::id);
		m_ecs.bindComponentToEnt(id, Velocity::id);

		m_ecs.addEntToFilter(m_coloredFilter,id);
		m_ecs.addEntToFilter(m_moveFilter, id);
		m_ecs.addEntToFilter(m_drawFilter, id);
		m_entities.push_back(id);

		initColored();

	}

	void spawnNonColoredEntitySystem() {

		becs::EntityID id = m_ecs.createEntity();

		m_ecs.bindComponentToEnt(id, Rect::id);
		m_ecs.bindComponentToEnt(id, Velocity::id);
		m_ecs.addEntToFilter(m_noColorFilter, id);
		m_ecs.addEntToFilter(m_moveFilter, id);
		m_entities.push_back(id);
		initNoColor();
	}


	void initColored() {
		


		size_t count = m_ecs.getComponentsByFilter(m_coloredFilter, m_queries, MAX_QUERIES);
		uint8_t r = rand() % 255, g = rand() % 255, b = rand() % 255;

	
		size_t maxCount = (count > MAX_QUERIES) ? MAX_QUERIES : count;


		for (uint32_t i = maxCount - 3; i < maxCount; i++) {

			if (m_queries[i].compID == Rect::id) {
				Rect* rect = (Rect*)m_queries[i].component;
				rect->w = 20;
				rect->h = 20;
				rect->x = (rand() % m_width) + 1;
				rect->y = (rand() % m_height) + 1;
			}

			if (m_queries[i].compID == Color::id) {
				Color* color = (Color*)m_queries[i].component;
				color->color = { r,g,b, 255};
			}
			if (m_queries[i].compID == Velocity::id) {
				Velocity* velocity = (Velocity*)m_queries[i].component;
				velocity->x = rand() % 50 * ((rand() % 2) ? -1 : 1);
				velocity->y = rand() % 50 * ((rand() % 2) ? -1 : 1);
			}
		}

	}

	void initNoColor() {
		becs::QueryComponent query[64];


		size_t count = m_ecs.getComponentsByFilter(m_coloredFilter, query, 64);



		for (uint32_t i = count - 2; i < count; i++) {

			if (query[i].compID == Rect::id) {
				Rect* rect = (Rect*)query[i].component;
				rect->w = 20;
				rect->h = 20;
				rect->x = 0;
				rect->y = 255;
			}

			if (query[i].compID == Velocity::id) {
				Velocity* velocity = (Velocity*)query[i].component;
				velocity->x = 0;
				velocity->y = 0;
			}
		}
	}

	void input() {
		s2d::KeyState ks = m_window->GetKeyState();

		if (ks.state == S2D_KEY_PRESSED) {

			switch (ks.key) {
			case VK_SPACE:
				spawnColoredEntitySystem(); 
				break;
			case 'Q':
				spawnNonColoredEntitySystem();
				break;
			}
			
		}

	}


	void drawSystem() {
		





		size_t count = m_ecs.getComponentsByFilter(m_drawFilter, m_queries, MAX_QUERIES);

		size_t maxCount = (count > MAX_QUERIES) ? MAX_QUERIES : count;

		Rect* rect = nullptr;
		Color* color = nullptr;
		for (uint32_t i = 0; i < maxCount; i++) {

			
			
			if (m_queries[i].compID == Rect::id) {
				rect = (Rect*)m_queries[i].component;
			}

			if (m_queries[i].compID == Color::id) {
				color = (Color*)m_queries[i].component;
			}

			if (color != nullptr && rect != nullptr) {
				m_graphics->drawRect(rect->x, rect->y, rect->w, rect->h, color->color);
				color = nullptr;
				rect = nullptr;
			}
				
		}
		
	}
	

	void moveSystem(float fElapseTime) {

		


		size_t count = m_ecs.getComponentsByFilter(m_moveFilter, m_queries, MAX_QUERIES);
		Rect* rect = nullptr;
		Velocity* velocity = nullptr;
		size_t maxCount = (count > MAX_QUERIES) ? MAX_QUERIES : count;

		for (uint32_t i = 0; i < maxCount; i++) {



			if (m_queries[i].compID == Rect::id) {
				rect = (Rect*)m_queries[i].component;
			}

			else if (m_queries[i].compID == Velocity::id) {
				velocity = (Velocity*)m_queries[i].component;
			}


			if (rect != nullptr && velocity != nullptr) {

				rect->x += velocity->x * fElapseTime;
				rect->y += velocity->y * fElapseTime;

				//velocity->x -= 0.1 * fElapseTime;
				//velocity->y -= 0.1 * fElapseTime;
				
				if (velocity->x < 0.1 && velocity->x > -0.1) velocity->x = 0;
				if (velocity->y < 0.1 && velocity->y > -0.1) velocity->y = 0;

				if (rect->x >= m_width || rect->x <= 0)velocity->x *= -1;
				if (rect->y >= m_height || rect->y <= 0)velocity->y *= -1;
				rect = nullptr;
				velocity = nullptr;
			}

		}
		

	}



	void Run() {

		float fElapseTime = 0, fTimeAccum = 0; 
		long long tick = 0, fps = 0;

		while (!m_window->WindowShouldClose()) {

			auto t1 = std::chrono::high_resolution_clock::now();
			
			input();
			moveSystem(fElapseTime);
			drawSystem();
			tick++;
			
			m_graphics->flushBuffer();
			m_window->ProcessMessage();
			m_window->SwapWindowBuffers();

			auto t2 = std::chrono::high_resolution_clock::now();

			std::chrono::duration<float> duration = t2 - t1;


			fElapseTime = duration.count();
			fTimeAccum += fElapseTime;

			if (fTimeAccum >= 1) {
				
				fps = tick;
				tick = 0;
				fTimeAccum = 0;
				std::cout << "FPS: " << fps << '\n';
			}
		}

	}



	~MyApp() {
		delete m_graphics;
		delete m_window;
		delete[] m_queries;
	}
private:

	

	uint32_t m_width = 1000, m_height = 800;
	const char const* m_title = "ECS";
	const uint32_t MAX_QUERIES = 4000;
	s2d::S2DGraphics* m_graphics = nullptr;
	s2d::S2DWindow* m_window = nullptr;
	becs::BECS		m_ecs;
	becs::FilterID m_drawFilter;
	becs::FilterID m_moveFilter;
	becs::FilterID m_coloredFilter;
	becs::FilterID m_noColorFilter;
	becs::QueryComponent* m_queries = nullptr;

	std::vector<becs::EntityID> m_entities;
};



int main() {

	MyApp app;
	app.Run();
	
	return 0;
}

