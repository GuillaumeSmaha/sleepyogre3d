#include "Listener/ListenerInputManager.h"

template<> ListenerInputManager * ClassRootSingleton<ListenerInputManager>::_instance = 0;

void ListenerInputManager::createSingleton()
{
	if(ListenerWindow::getSingletonPtr()->getRenderWindow() != 0)
	{
		new ListenerInputManager();
	}
	else
	{
		std::cerr << "@ListenerInputManager::createSingleton() : InputManager undefined" << std::endl;
	}
}


ListenerInputManager::ListenerInputManager() : ClassRootSingleton<ListenerInputManager>()
{
	// Init the input system manager
	OIS::ParamList pl;
	size_t windowHnd = 0;
	std::ostringstream windowHndStr;
	ListenerWindow::getSingletonPtr()->getRenderWindow()->getCustomAttribute("WINDOW", &windowHnd);
	windowHndStr << windowHnd;
	pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));
	
	this->inputManager = OIS::InputManager::createInputSystem(pl);
}

ListenerInputManager::~ListenerInputManager()
{
  delete this->inputManager;
}
