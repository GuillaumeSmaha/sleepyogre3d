#include "Scene/GestSceneManager.h"

template<> GestSceneManager * ClassRootSingleton<GestSceneManager>::_instance = 0;


Ogre::SceneManager * GestSceneManager::getSceneManager()
{
	if(GestSceneManager::getSingletonPtr() != 0)
		return GestSceneManager::getSingletonPtr()->sceneManager;
		
	return 0;
}

Ogre::Root * GestSceneManager::getRoot()
{
	if(GestSceneManager::getSingletonPtr() != 0)
		return GestSceneManager::getSingletonPtr()->root;
		
	return 0;
}

GestSceneManager::GestSceneManager() : ClassRootSingleton<GestSceneManager>()
{
	this->sceneManager = 0;
	
	// construct Ogre::Root
	#ifdef _DEBUG
		this->root = new Ogre::Root("plugins_d.cfg");
	#else
		this->root = new Ogre::Root("plugins.cfg");
	#endif

	// restore the config or show the configuration dialog and
	if (!this->root->showConfigDialog())
		return;
	
	this->sceneManager = root->createSceneManager(Ogre::ST_GENERIC);
}

GestSceneManager::~GestSceneManager()
{
	if(this->sceneManager != 0)
	{
		this->sceneManager->clearScene();
		this->root->destroySceneManager(this->sceneManager);
	}
}

Ogre::Entity * GestSceneManager::createEntity(const Ogre::String &name, const Ogre::String meshName)
{
  return this->sceneManager->createEntity(name, meshName);
}
