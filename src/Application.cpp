#include "Application.h"

template<> Application * ClassRootSingleton<Application>::_instance = 0;


Application::Application() : ClassRootSingleton<Application>()
{	
#ifdef _DEBUG
	this->resourcesCfg = "resources_d.cfg";
#else
	this->resourcesCfg = "resources.cfg";
#endif
}


Application::~Application()
{
	std::cerr << "-" << std::endl << "Stop	application !!" << std::endl;
		
	GestInteraction::destroySingleton();
	
	// Destroy the stats
	//StatsOverlay::destroySingleton();
	
	// Destroy the menus
	InitMenus::destroy();
	
	// Destroy the controls
	InitControls::destroy();
	
	// Destroy the viewports
	InitViewport::destroy();
	
	// Destroy the cameras
	InitCamera::destroy();
	
	// Destroy the listeners
	InitListener::destroy();
	
	// Destroy the ogre root and scene manager
	InitSceneGraph::destroy();
    
  std::cerr << "Singletons destroyed" << std::endl;
}

bool Application::start()
{
	Utils::logFileInit("error.log");

	// Init the ogre root and scene manager
	InitSceneGraph::init();
	if(GestSceneManager::getSceneManager() == 0)
		return false;

	// load the ressources
	this->loadRessources();
	
	// Init the listeners
	InitListener::init();
	
	// Init the viewports
	InitViewport::init();
	
	// Init the controls
	InitControls::init();
	
	// Init the menus
	InitMenus::init();
	
	// Init the cameras
	InitCamera::init();

	// Create debugging overlay
	//StatsOverlay::createSingleton();

	// start the scene rendering (main loop)
	GestSceneManager::getRoot()->startRendering();

	return true;
}

void Application::loadRessources()
{
	// setup resources
	// Load resource paths from config file
	Ogre::ConfigFile cf;
	cf.load(this->resourcesCfg);

	// Go through all sections & settings in the file
	Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();

	Ogre::String secName, typeName, archName;
	while (seci.hasMoreElements())
	{
		secName = seci.peekNextKey();
		Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
		Ogre::ConfigFile::SettingsMultiMap::iterator i;
		for (i = settings->begin(); i != settings->end(); ++i)
		{
			typeName = i->first;
			archName = i->second;
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(archName, typeName, secName);
      printf("archName : %s\n", archName.c_str());
      printf("typeName : %s\n", typeName.c_str());
      printf("secName : %s\n", secName.c_str());
		}
	}
  
	// Initialisation des ressources
  Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}
