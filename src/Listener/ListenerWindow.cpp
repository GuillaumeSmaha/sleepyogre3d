#include "Listener/ListenerWindow.h"

template<> ListenerWindow * ClassRootSingleton<ListenerWindow>::_instance = 0;

void ListenerWindow::createSingleton()
{
	std::cerr << "Le constructeur de ListenerWindow ne doit pas être appelé via createSingleton() et doit être appelé avec un Ogre::Root * en argument !" << std::endl << "Attention le singleton n'ayant pas été crée, il est fort possible d'avoir des erreurs de segmentation"  << std::endl ;
}

void ListenerWindow::createSingleton(Ogre::Root  * root)
{
	ListenerWindow::createSingleton(root, "Generic Window");
}

void ListenerWindow::createSingleton(Ogre::Root  * root, Ogre::String windowName)
{
	new ListenerWindow(root, windowName);
}

ListenerWindow::ListenerWindow(Ogre::Root  * root, Ogre::String windowName) : ClassRootSingleton<ListenerWindow>()
{
	this->renderWindow = root->initialise(true, windowName);
	Ogre::WindowEventUtilities::addWindowEventListener(this->renderWindow, this);
}

ListenerWindow::~ListenerWindow()
{
	Ogre::WindowEventUtilities::removeWindowEventListener(this->renderWindow, this);
	this->windowClosed(this->renderWindow);
}

void ListenerWindow::windowResized(Ogre::RenderWindow * rw)
{	
	if(rw == this->renderWindow)
	{
		this->signalWindowResized.dispatch(rw);
	}
}

void ListenerWindow::windowClosed(Ogre::RenderWindow * rw)
{
	if(rw == this->renderWindow)
	{
		this->signalWindowClosed.dispatch();
	}
}



//Getter - Setter

Ogre::RenderWindow * ListenerWindow::getRenderWindow()
{
	return this->renderWindow;
}


void ListenerWindow::setRenderWindow(Ogre::RenderWindow * renderWindow)
{
	this->renderWindow = renderWindow;
}
