#ifndef GAME_HPP
#define GAME_HPP

#include<map>

#include <VBE-Scenegraph/scenegraph/GameObject.hpp>
#include <VBE-Scenegraph/scenegraph/ContainerObject.hpp>
#include <VBE/system/Window.hpp>

class Game : public ContainerObject {
	public:
        Game(const Window::DisplayMode& mode, const ContextSettings& settings);
		virtual ~Game();
		static Game* i() { return Game::instance;}

		GameObject* getObjectByName(std::string name) const;
		GameObject* getObjectByID(int id) const;

		virtual void run();

		void setFixedUpdateRate(int fixedUpdateRate);
		void setDynamicFramerate();

		bool isRunning;
	protected:
		virtual void update(float deltaTime);
		virtual void draw();
	private:
        Window window;

		std::map<std::string, GameObject*> nameMap;
		std::map<int, GameObject*> idMap;
		int idCounter;

		int fixedUpdateRate;
		bool isFixedUpdateRate;

		static Game* instance;

		friend class GameObject;
		friend class ContainerObject;
};

#endif //GAME_HPP
