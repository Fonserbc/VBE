#ifndef MANAGER_HPP
#define MANAGER_HPP
#include "graphics/Texture.hpp"
#include "graphics/ShaderProgram.hpp"
#include "graphics/Mesh.hpp"

template<class T>
class Manager {
	public:
		Manager() {}
		virtual ~Manager() {}

		void add  (const std::string& resID,T* resource) {
			VBE_ASSERT(resources.find(resID) == resources.end(), "Failed to add resource. resource " << resID << " already exists");
			VBE_LOG("* Adding resource with ID " << resID );
			resources.insert(std::pair<std::string,T*>(resID,resource));
		}

		T*   get  (const std::string& resID) const {
			VBE_ASSERT(resources.find(resID) != resources.end(), "Failed to get resource. resource " << resID << " doesn't exist");
			return resources.at(resID);
		}

		void erase(const std::string& resID) {
			VBE_ASSERT(resources.find(resID) != resources.end(), "Failed to delete resource. resource " << resID << " doesn't exist");
			VBE_LOG("* Deleting resource with ID " << resID );
			delete resources.at(resID);
			resources.erase(resID);
		}

		bool exists(const std::string& resID) {
			return (resources.find(resID) != resources.end());
		}

		void clear() {
			while(!resources.empty())
				erase(resources.begin()->first);
		}
	private:
		std::map<std::string,T*> resources;
};

//default Managers
extern Manager<Texture> Textures;
extern Manager<Mesh> Meshes;
extern Manager<ShaderProgram> Programs;

#endif // MANAGER_HPP
