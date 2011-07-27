#include "Viewport/Viewport.h"


int Viewport::lastViewportId = 0;


Viewport::Viewport(CameraAbstract * camera)
{
	this->id = Viewport::lastViewportId;
	
	this->camera = camera;
	this->camera->insertViewport(this);
	
	ListenerWindow * listenerWindow = ListenerWindow::getSingletonPtr();
	this->viewport = listenerWindow->getRenderWindow()->addViewport(this->camera->getCamera(), this->id);
	
	viewport->setBackgroundColour(Ogre::ColourValue(0.0f, 0.0f, 0.0f));
	
	Viewport::lastViewportId++;
}


Viewport::~Viewport()
{	
	this->camera->removeViewport(this);
	
	ListenerWindow * listenerWindow = ListenerWindow::getSingletonPtr();
	listenerWindow->getRenderWindow()->removeViewport(this->viewport->getZOrder());
	
	this->viewport = NULL;
	this->camera = NULL;
}


bool Viewport::isInViewport(Ogre::Vector3 position)
{
	Ogre::Real left = this->viewport->getLeft();
	Ogre::Real right = this->viewport->getLeft() + this->viewport->getWidth();
	Ogre::Real top = this->viewport->getTop();
	Ogre::Real bottom = this->viewport->getTop() + this->viewport->getHeight();
	
	if(position[0] >= left && position[0] <= right
		&& position[1] >= top && position[1] <= bottom)
		return true;	
	
	return false;
}


void Viewport::updateViewportSize()
{
	if(this->viewport != NULL)
	{
		Ogre::Real left = this->viewport->getLeft();
		Ogre::Real top = this->viewport->getTop();
		Ogre::Real width = this->viewport->getWidth();
		Ogre::Real height = this->viewport->getHeight();
		
		this->updateViewportSize(left, top, width, height);
	}
}


void Viewport::updateViewportSize(Ogre::Real left, Ogre::Real top, Ogre::Real width, Ogre::Real height)
{
	if(this->viewport != NULL)
	{		
		this->viewport->setDimensions(left, top, width, height);
		this->camera->getCamera()->setAspectRatio(Ogre::Real(this->viewport->getActualWidth()) / Ogre::Real(this->viewport->getActualHeight()));
	}
}


// Getter - Setter


Ogre::Viewport * Viewport::getViewport()
{
	return this->viewport;
}

int Viewport::getId()
{
	return this->id;
}


CameraAbstract * Viewport::getCamera()
{
	return this->camera;
}


void Viewport::setCamera(CameraAbstract * camera)
{
	this->camera = camera;
	this->viewport->setCamera(this->camera->getCamera());
	this->camera->getCamera()->setAspectRatio(Ogre::Real(this->viewport->getActualWidth()) / Ogre::Real(this->viewport->getActualHeight()));
	
	this->updateViewportSize();
}
