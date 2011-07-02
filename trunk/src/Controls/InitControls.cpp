#include "Controls/InitControls.h"

void InitControls::init()
{
	//Create MouseFunction Singleton
    MouseFunction::createSingleton(ListenerWindow::getSingletonPtr()->getRenderWindow());

	//Create PlayerControls Singleton
	PlayerControls::createSingleton();
}

void InitControls::destroy()
{
	PlayerControls::destroySingleton();
	
	MouseFunction::destroySingleton();
}
