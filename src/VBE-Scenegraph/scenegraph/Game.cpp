#include <VBE-Scenegraph/scenegraph/Game.hpp>
#include <VBE/system/Clock.hpp>
#include <VBE/system/Window.hpp>
#include <VBE/system/Log.hpp>
#include <VBE/system/Keyboard.hpp>

Game* Game::instance = nullptr;

Game::Game(const Window::DisplayMode &mode, const ContextSettings &settings) : isRunning(true), window(mode, settings), idCounter(1), fixedUpdateRate(0), isFixedUpdateRate(false) {
    VBE_ASSERT(Game::instance == nullptr, "Two games created");
    Game::instance = this;
    isRunning = true;
    VBE_LOG("* INIT GAME");
}

Game::~Game() {
	//Free resources, delete scenegraph nodes and close windows

	//do this here instead of letting ContainerObject do it, so that the shutdown cleanup is done after everything has been actually deleted.
	for(std::set<GameObject*, FunctorCompareUpdate>::iterator it = updateTasks.begin(); it != updateTasks.end();) {
		GameObject* obj = *it;
		drawTasks.erase(obj);
		it = updateTasks.erase(it);
		delete obj;
	}

	//At this point everything should be totally gone.
	VBE_LOG("* EXITING GAME: CLEARING RESOURCES" );
	isRunning = false;
	Game::instance = nullptr;
	VBE_LOG("* EXIT GAME SUCCESFUL" );
}

void Game::update(float deltaTime) {
	Window::getInstance()->update();
	ContainerObject::update(deltaTime);
}

void Game::draw() {
	ContainerObject::draw();
	Window::getInstance()->swapBuffers();
}

GameObject* Game::getObjectByName(std::string name) const {
	VBE_ASSERT(nameMap.find(name) != nameMap.end(), "There is no object named " << name);
	return nameMap.at(name);
}

GameObject* Game::getObjectByID(int id) const {
	VBE_ASSERT(idMap.find(id) != idMap.end(), "There is no object with id " << id);
	return idMap.at(id);
}

void Game::setFixedUpdateRate(int fixedFramerate) {
	this->fixedUpdateRate = fixedFramerate;
	this->isFixedUpdateRate = true;
}

void Game::setDynamicFramerate() {
	isFixedUpdateRate = false;
}

// Main game loop
void Game::run() {
	if(isFixedUpdateRate) {
		float fixedTime = 1.0f/float(fixedUpdateRate);
		float accumulated = 0.0f;
		float oldTime = Clock::getSeconds();
		while (isRunning) {
			float time = Clock::getSeconds();
			float deltaTime = time-oldTime;
			oldTime = time;
			accumulated += deltaTime;
			while(accumulated >= fixedTime) {
				fixedUpdate(fixedTime);
				accumulated -= fixedTime;
			}
			update(deltaTime);
			draw();
		}
	}
	else {
		float oldTime = Clock::getSeconds();
		while (isRunning) {
			float time = Clock::getSeconds();
			float deltaTime = time-oldTime;
			oldTime = time;
			update(deltaTime);
			draw();
		}
	}
}
