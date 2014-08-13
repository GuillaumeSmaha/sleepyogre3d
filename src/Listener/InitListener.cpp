#include "Listener/InitListener.h"

void InitListener::init()
{
	//Create Window Singleton
	ListenerWindow::createSingleton(GestSceneManager::getRoot(), PROJECT_NAME);
	
	//Create InputManager Singleton
	ListenerInputManager::createSingleton();
	
	//Create Frame Singleton
  ListenerFrame::createSingleton(GestSceneManager::getRoot());
	
	//Create Keyboard Singleton
	ListenerKeyboard::createSingleton();
	
	//Create Mouse Singleton
	ListenerMouse::createSingleton();

	//Update the size of window and mouse window size
	ListenerWindow::getSingletonPtr()->windowResized(ListenerWindow::getSingletonPtr()->getRenderWindow());
}

void InitListener::destroy()
{	
	ListenerMouse::destroySingleton();
	ListenerKeyboard::destroySingleton();
	ListenerFrame::destroySingleton();
	ListenerInputManager::destroySingleton();
	ListenerWindow::destroySingleton();
}
