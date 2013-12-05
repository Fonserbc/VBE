#include "Game.hpp"
#include "Manager.hpp"
#include "audio/AudioManager.hpp"
#include "input/Input.hpp"
#include "Clock.hpp"

Game* Game::instance = NULL;

Game::Game(bool slave, char* ip) :isRunning(true), root(NULL), idCounter(1), isSlave(slave) {
	VBE_ASSERT(Game::instance == NULL, "Two games created");
	Game::instance = this;
    this->serverIp = ip;
	VBE_LOG("* INIT GAME");

    window.create(sf::VideoMode(SCRWIDTH,SCRHEIGHT,32), WINDOW_TITLE ,sf::Style::Fullscreen,CONTEXT_SETTINGS_OPENGL);
    //window.setMouseCursorVisible(false);
	window.setKeyRepeatEnabled(false);
	window.setVerticalSyncEnabled(false);

	isRunning = true;

	VBE_LOG("* INIT GAME SUCCESFUL");

    initConnection();
}

Game::~Game() {
	//Free resources, delete scenegraph nodes and close windows
	VBE_LOG("* EXITING GAME: CLEARING RESOURCES" );
	Textures.clear();
	Meshes.clear();
	AudioManager::clear();
	Programs.clear();
	window.close();
	isRunning = false;
	VBE_LOG("* EXIT GAME SUCCESFUL" );
}

void Game::initConnection() {
    sf::IpAddress address(serverIp);
    if (isSlave) {
        sf::Socket::Status status = socket.connect(address, 42424);
        if (status != sf::Socket::Done)
        {
            std::cout << "Could not connect" << std::endl;
        }
    }
    else {
        sf::TcpListener listener;

        if (listener.listen(42424) != sf::Socket::Done)
        {
            std::cout << "Could not listen" << std::endl;
        }

        if (listener.accept(socket) != sf::Socket::Done)
        {
            std::cout << "Could not accept connection" << std::endl;
        }
    }
}

sf::TcpSocket* Game::getConnection() {
    return &socket;
}

GameObject* Game::getObjectByName(std::string name) const {
	return nameMap.at(name);
}

GameObject* Game::getObjectByID(int id) const {
	return idMap.at(id);
}

// Main game loop
void Game::run() {
	VBE_ASSERT(root != NULL, "Null scenegraph root");
    Clock clock((isSlave)? Clock::Network : Clock::Local, &socket);
	while (isRunning) {
        Clock::TimeStruct t = clock.tick();
        update(t.deltaTime, t.time);
		draw();
	}
    Clock::TimeStruct t = clock.tick();
    update(t.deltaTime, t.time);
}

// Set root for the scenegraph
void Game::setRoot(GameObject *newRoot) {
	VBE_ASSERT(root == NULL, "Root has already been set!");
	root = newRoot;
	root->addToGame();
}

// Update scenegraph
void Game::update(float deltaTime, float time) {
	Input::update(isRunning,window);
	VBE_ASSERT(root != NULL, "Null scenegraph root");

	while(!objectTasksToRemove.empty()) {
		GameObject* obj = objectTasksToRemove.front();
		updateTasks.erase(obj);
		drawTasks.erase(obj);
		objectTasksToRemove.pop();
		if(!obj->isAlive) delete obj;
	}

	while(!objectTasksToAdd.empty()) {
		GameObject* obj = objectTasksToAdd.front();
		updateTasks.insert(obj);
		drawTasks.insert(obj);
		objectTasksToAdd.pop();
	}

	for(std::set<GameObject*,FunctorCompareUpdate>::iterator it = updateTasks.begin(); it != updateTasks.end(); ++it)
        (*it)->update(deltaTime, time);
}

// Draw scenegraph
void Game::draw() {
	VBE_ASSERT(root != NULL, "Null scenegraph root");
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	root->propragateTransforms();
	for(std::set<GameObject*,FunctorCompareDraw>::iterator it = drawTasks.begin(); it != drawTasks.end(); ++it)
		(*it)->draw();
    window.display(); // I need to display just when I finished postprocessing (and 3d)
}

// Draw scenegraph: call all of the draw functions for postprocessing (and 3d)
void Game::drawScene() {
    VBE_ASSERT(root != NULL, "Null scenegraph root");
    root->propragateTransforms();
    for(std::set<GameObject*,FunctorCompareDraw>::iterator it = drawTasks.begin(); it != drawTasks.end(); ++it)
        (*it)->draw();
}

