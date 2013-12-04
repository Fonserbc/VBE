#ifndef GAME_HPP
#define GAME_HPP
#include "GameObject.hpp"

#include <SFML/Network.hpp>

class Game {
		struct FunctorCompareDraw{
				bool operator()(const GameObject* a, const GameObject* b) {
					if(a->drawPriority == b->drawPriority)
						return (a->id < b->id);
					return (a->drawPriority < b->drawPriority);
				}
		};
		struct FunctorCompareUpdate{
				bool operator()(const GameObject* a, const GameObject* b) {
					if(a->updatePriority == b->updatePriority)
						return (a->id < b->id);
					return (a->updatePriority < b->updatePriority);
				}
		};
	public:
        Game(bool slave, char* ip);
		~Game();

		GameObject* getObjectByName(std::string name) const;
		GameObject* getObjectByID(int id) const;

		void run();
        void drawScene();
		void setRoot(GameObject* newRoot);
		GameObject* getRoot() {return root;}
		int getObjectCount() const { return updateTasks.size(); }
		sf::RenderWindow &getWindow() { return window; }

		bool isRunning;

        void initConnection();
        sf::TcpSocket* getConnection();

        bool isSlave;

	private:
		static Game* i() { return Game::instance;}

        void update(float deltaTime, float time);
		void draw();
		bool loadResources ();

        sf::TcpSocket socket;
        char* serverIp;
        void slaveDraw(bool draw);
        bool canSlaveDraw();

        sf::RenderWindow window;
		GameObject* root;
		std::map<std::string,GameObject*> nameMap;
		std::map<int,GameObject*> idMap;
		int idCounter;
		std::set<GameObject*,Game::FunctorCompareDraw> drawTasks;
		std::set<GameObject*,FunctorCompareUpdate> updateTasks;

		std::queue<GameObject*> objectTasksToAdd;
		std::queue<GameObject*> objectTasksToRemove;

		static Game* instance;

		friend class GameObject;
};

#endif //GAME_HPP
