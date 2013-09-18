#include "ShaderManager.hpp"
#include "ShaderProgram.hpp"

std::map<std::string,ShaderProgram*> ShaderManager::programs;

ShaderManager::ShaderManager() {
}

ShaderManager::~ShaderManager() {
}

bool ShaderManager::load(const std::string &programID, const std::string &vert, const std::string &frag) {
	std::cout << "* Loading new ShaderProgram with ID " << programID << " from " << vert << " and " << frag << std::endl;
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
	std::cout << "* Deleting ShaderProgram with ID " << programID << std::endl;
	delete programs.at(programID);
	programs.erase(programID);
}

void ShaderManager::clear() {
	while(!programs.empty())
		erase(programs.begin()->first);
}
