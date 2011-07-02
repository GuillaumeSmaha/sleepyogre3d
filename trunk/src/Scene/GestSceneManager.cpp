#include "Scene/GestSceneManager.h"

template<> GestSceneManager * ClassRootSingleton<GestSceneManager>::_instance = NULL;


Ogre::SceneManager * GestSceneManager::getSceneManager()
{
	if(GestSceneManager::getSingletonPtr() != NULL)
		return GestSceneManager::getSingletonPtr()->sceneManager;
		
	return NULL;
}

Ogre::Root * GestSceneManager::getRoot()
{
	if(GestSceneManager::getSingletonPtr() != NULL)
		return GestSceneManager::getSingletonPtr()->root;
		
	return NULL;
}

GestSceneManager::GestSceneManager() : ClassRootSingleton<GestSceneManager>()
{
	this->sceneManager = NULL;
	
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
	if(this->sceneManager != NULL)
	{
		this->sceneManager->clearScene();
		this->root->destroySceneManager(this->sceneManager);
	}
	
	delete this->root;
}

Ogre::Entity * GestSceneManager::createEntity(const Ogre::String &name, const Ogre::String meshName)
{
    return this->sceneManager->createEntity(name, meshName);
}
