#include "SceneMain.hpp"
#include "../Game.hpp"
#include "TriangleObject.hpp"
#include "RegularPolygonObject.hpp"

SceneMain::SceneMain(Game &parent) :
	GameObject(NULL,vec3f(0.0),vec3f(1.0)),
	debugCounter(0.0), fpsCount(0), parentGame(parent) {
	//SCENE INIT
	std::cout << "* Loading new scene: Main" << std::endl;
	if (!loadResources()) {
		std::cout << "Could not load resources for SceneMain" << std::endl;
		parent.isRunning = false;
		return;
	}
	//Center mouse
	InputManager::setMousePos(SCRWIDTH/2,SCRHEIGHT/2,parent.getWindow());
	//add a new triangle
	addObject(new       TriangleObject(this, vec3f( 1.0f, 0.0f,-3.0f), vec3f(0.1f)));
	addObject(new RegularPolygonObject(this, vec3f(-1.0f, 0.0f,-3.0f), vec3f(1.0f), 6));
	std::cout << "* Init done" << std::endl;
}

SceneMain::~SceneMain() {
}

bool SceneMain::loadResources() {
	//shaders
	if(!ShaderManager::load("sample","data/shaders/sample.vert","data/shaders/sample.frag"))
		return false;
	if(!ShaderManager::load("sample2","data/shaders/sample2.vert","data/shaders/sample2.frag"))
		return false;
	//textures
	if(!TextureManager::load("cubetex","data/10x10tex.png",2))
		return false;
	//Create meshes
	MeshManager::add("cube",new Mesh("data/10x10.obj"));
	return true;
}

void SceneMain::update(float deltaTime) {
	++fpsCount;
	debugCounter += deltaTime;
	if (debugCounter > 1) {
		std::cout << "FPS: " << fpsCount << ". Amount of GameObjects: " << children.size() << std::endl;
		debugCounter -= 1;
		fpsCount = 0;
	}
	for(std::list<GameObject*>::iterator it = children.begin(); it != children.end();) {
		(*it)->update(deltaTime);
		if (!(*it)->isAlive) {
			delete *it;
			it = children.erase(it);;
		}
		else
			++it;
	}
}

void SceneMain::draw() const {
	//calculate perspective matrix
	RenderState::projection = glm::perspective(FOV,float(SCRWIDTH)/float(SCRHEIGHT),ZNEAR,ZFAR);
	//Move matrix to position (according to player)
	RenderState::view = mat4f(1.0);
	//models
	for(std::list<GameObject*>::const_iterator it = children.begin();it != children.end(); ++it)
		(*it)->draw();
}

