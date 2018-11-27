/**
 * This file is part of RT2D, a 2D OpenGL framework.
 *
 * - Copyright 2015 Rik Teerling <rik@onandoffables.com>
 *   - Initial commit
 */

#include <rt2d/resourcemanager.h>

ResourceManager::ResourceManager()
{
	std::cout << "#######################" << std::endl;
	std::cout << "resourcemanager created" << std::endl;
}

ResourceManager::~ResourceManager()
{
	std::cout << "################ ResourceManager::delete ################" << std::endl;

	// delete shaders only in destructor. There might be an ubershader.
	// shaders
	std::cout << "---------- Delete Shaders ----------" << std::endl;
	std::map<std::string, Shader*>::iterator shad_it;
	for (shad_it=_shaders.begin(); shad_it!=_shaders.end(); ++shad_it) {
		if (shad_it->second != nullptr) {
			//std::cout << shad_it->first << " => " << shad_it->second << '\n';
			deleteShader(shad_it->first);
		}
	}
	_shaders.clear();

	// cleanup Textures and Meshes
	this->cleanup();

	std::cout << "resourcemanager empty" << std::endl;
	std::cout << "#####################" << std::endl;

	std::cout << "resourcemanager closed" << std::endl;
}

void ResourceManager::cleanup()
{
	std::cout << "################ ResourceManager::cleanup ################" << std::endl;
	// textures
	std::cout << "---------- Delete Textures ----------" << std::endl;
	std::map<std::string, Texture*>::iterator text_it;
	for (text_it=_textures.begin(); text_it!=_textures.end(); ++text_it) {
		if (text_it->second != nullptr) {
			//std::cout << text_it->first << " => " << text_it->second << '\n';
			deleteTexture(text_it->first);
		}
	}
	_textures.clear();

	// meshes
	std::cout << "---------- Delete Meshes ----------" << std::endl;
	std::map<std::string, Mesh*>::iterator mesh_it;
	for (mesh_it=_meshes.begin(); mesh_it!=_meshes.end(); ++mesh_it) {
		if (mesh_it->second != nullptr) {
			//std::cout << mesh_it->first << " => " << mesh_it->second << '\n';
			deleteMesh(mesh_it->first);
		}
	}
	_meshes.clear();
}

// Texture
Texture* ResourceManager::getTexture(const std::string& filename, int filter, int wrap)
{
	if (_textures[filename] != nullptr) {
		//std::cout << "return existing resource: " << filename << " (texture)" << std::endl;
		return _textures[filename];
	} else {
		Texture* t = new Texture();
		if (filename == AUTOGENWHITE) {
			t->createWhitePixels(32, 32);
		} else {
			t->loadTGAImage(_prefix+filename, filter, wrap);
		}
		_textures[filename] = t;
		std::cout << "return new resource: " << filename << " (texture)" << std::endl;
		return t;
	}

	return nullptr;
}

void ResourceManager::deleteTexture(const std::string& filename)
{
	delete _textures[filename];
	_textures[filename] = nullptr;

	std::cout << "==> deleting resource: " << filename << " (texture)" << std::endl;
}

// Shaders
Shader* ResourceManager::getShader(const std::string& vs, const std::string& fs)
{
	std::string filename;
	filename = vs;
	std::string tmp("_");
	filename.append(tmp);
	filename.append(fs);
	if (_shaders[filename] != nullptr) {
		//std::cout << "return existing resource: " << filename << " (shader)" << std::endl;
		return _shaders[filename];
	} else {
		Shader* s = new Shader();
		std::string fss = _prefix;
		fss.append(fs);
		std::string vss = _prefix;
		vss.append(vs);
		s->loadShaders(vss.c_str(), fss.c_str());
		_shaders[filename] = s;

		std::cout << "return new resource: " << filename << " (shader)" << std::endl;
		return s;
	}

	return nullptr;
}

void ResourceManager::deleteShader(const std::string& shadername)
{
	std::string filename = _prefix;
	filename.append(shadername);

	delete _shaders[filename];
	_shaders[filename] = nullptr;

	std::cout << "==> deleting resource: " << filename << " (shader)" << std::endl;
}


// Meshes
Mesh* ResourceManager::getSpriteMesh(int width, int height, float pivotx, float pivoty, float uvwidth, float uvheight, int circle, int which)
{
	char buf[64]; // should be big enough: "1024x1024_0.50000x0.50000_1.00000x1.00000_0_60"
	sprintf(buf, "%dx%d_%.5fx%.5f_%.5fx%.5f_%d_%d", width, height, pivotx, pivoty, uvwidth, uvheight, circle, which);
	std::string meshname(buf);

	if (_meshes[meshname] != nullptr) {
		//std::cout << "return existing resource: " << meshname << " (mesh)" << std::endl;
		return _meshes[meshname];
	} else {
		Mesh* m = new Mesh();
		if (circle != 0) {
			if (which >= 0) {
				m->generateSegmentMesh(width/2, circle, which);
			} else {
				m->generateCircleMesh(width/2, circle, uvwidth, uvheight);
			}
		} else {
			m->generateSpriteMesh(width, height, pivotx, pivoty, uvwidth, uvheight);
		}
		_meshes[meshname] = m;

		std::cout << "return new resource: " << meshname << " (mesh)" << std::endl;
		return m;
	}

	return nullptr;
}


Mesh* ResourceManager::getLineMesh(Line* line)
{
	std::string meshname = line->filename();

	if (_meshes[meshname] != nullptr) {
		//std::cout << "return existing resource: " << meshname << " (mesh)" << std::endl;
		return _meshes[meshname];
	} else {
		Mesh* m = new Mesh();
		m->generateLineMesh(line);
		_meshes[meshname] = m;

		std::cout << "return new resource: " << meshname << " (mesh)" << std::endl;
		return m;
	}

	return nullptr;
}

void ResourceManager::deleteMesh(const std::string& meshname)
{
	delete _meshes[meshname];
	_meshes[meshname] = nullptr;

	std::cout << "==> deleting resource: " << meshname << " (mesh)" << std::endl;
}
