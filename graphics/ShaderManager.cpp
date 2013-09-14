#include "ShaderManager.hpp"
#include "ShaderProgram.hpp"

std::map<std::string,ShaderProgram*> ShaderManager::programs;

ShaderManager::ShaderManager() {
}

ShaderManager::~ShaderManager() {
}

bool ShaderManager::load(const std::string &programID, const std::string &vert, const std::string &frag) {
	assert(programs.find(programID) == programs.end());
	ShaderProgram* p = new ShaderProgram();
	if(!p->makeProgram(vert,frag))
		return false;
	programs.insert(std::pair<std::string,ShaderProgram*>(programID,p));
	return true;
}

ShaderProgram* ShaderManager::get(const std::string &programID) {
	return programs.at(programID);
}

void ShaderManager::erase(const std::string& programID) {
	assert(programs.find(programID) != programs.end());
	delete programs.at(programID);
	programs.erase(programID);
}

void ShaderManager::clear() {
	for(std::map<std::string,ShaderProgram*>::iterator it = programs.begin(); it != programs.end(); ++it) {
		delete it->second;
	}
	programs.clear();
}
