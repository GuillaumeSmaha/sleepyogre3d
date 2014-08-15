#include "Viewport/GestViewport.h"


template<> GestViewport * ClassRootSingleton<GestViewport>::_instance = 0;


std::vector<ViewportPosDim_t> GestViewport::getViewportPosDim(int nbViewport)
{

	std::vector<ViewportPosDim_t> result;
	int iViewport;
	int numberColumn;
	int numberLine = (int)(floor(sqrt(1.0 * nbViewport)) + 0.5);
	int numberColumnMax = (int)ceil(nbViewport*1.0/numberLine);
	
	iViewport = 0;
	for(int i = 0 ; i < numberLine ; i++)
	{
		numberColumn = std::min(numberColumnMax, (nbViewport-iViewport));
		for(int j = 0 ; j < numberColumn ; j++)
		{
			ViewportPosDim_t viewport;
			
			viewport.top = Utils::floorValue((1.0/numberLine)*i, 4);
			viewport.left = Utils::floorValue((1.0/numberColumn)*j, 4);			
			
			if((i+1) != numberLine)
			{
				viewport.height = Utils::floorValue((1.0/numberLine), 4) + (1.0/pow(10.0, 2));
			}
			else
			{
				viewport.height = Utils::floorValue((1.0/numberLine), 4) + (1.0/pow(10.0, 2));
			}
			
			if((j+1) != numberColumn)
			{
				viewport.width = Utils::floorValue((1.0/numberColumn), 4) + (1.0/pow(10.0, 2));
			}
			else
			{
				viewport.width = Utils::floorValue((1.0/numberColumn), 4) + (1.0/pow(10.0, 2));
			}
			
			result.push_back(viewport);
			
			iViewport++;
		}
	}
	
	return result;
}


GestViewport::GestViewport() : ClassRootSingleton<GestViewport>()
{
	ListenerWindow::getSingletonPtr()->signalWindowResized.add(&GestViewport::onWindowResize, this);
}

GestViewport::~GestViewport()
{
	while(this->removeViewportByIndex(0)) {};
	ListenerWindow * listenerWindow = ListenerWindow::getSingletonPtr();
	listenerWindow->getRenderWindow()->removeAllViewports();
}

int GestViewport::addViewport(CameraAbstract * camera)
{
	Viewport * viewport = new Viewport(camera);	
	
	this->lstViewport.push_back(viewport);
	
	this->updateViewportSize();
	
	return viewport->getId();
}


bool GestViewport::changeCameraViewport(int viewportId, CameraAbstract * camera)
{
	Viewport * viewport = this->find(viewportId);	
	if(viewport != 0)
	{
		viewport->setCamera(camera);
	
		return true;
	}
	
	return false;
}


bool GestViewport::removeViewportById(int viewportId)
{	
	int viewportIndex = this->findIndex(viewportId);	
	
	if(viewportIndex != -1)
	{	
		Viewport * viewport = this->lstViewport.at(viewportIndex);
		
		this->lstViewport.erase(this->lstViewport.begin()+viewportIndex);
		
		delete viewport;
		
		this->updateViewportSize();
		
		return true;
	}
	
	return false;
}


bool GestViewport::removeViewportByIndex(int viewportIndex)
{	
	int count = this->countViewport();
	
	if(count != 0)
	{	
		Viewport * viewport = this->lstViewport.at(viewportIndex);
		
		this->lstViewport.erase(this->lstViewport.begin()+viewportIndex);
		
		delete viewport;
		
		this->updateViewportSize();
		
		return true;
	}
	
	return false;
}


bool GestViewport::isInViewport(int viewportId, Ogre::Vector3 position)
{	
	if(this->countViewport() > 0)
	{
		Viewport * viewport = this->find(viewportId);
		if(viewport != 0)
		{
			return viewport->isInViewport(position);
		}
	}
	
	return false;
}


Viewport * GestViewport::find(int viewportId)
{
	for(int i = 0 ; i < this->countViewport() ; i++)
	{
		if(this->lstViewport.at(i)->getId() == viewportId)
			return this->lstViewport.at(i);
	}
	
	return 0;
}


int GestViewport::findIndex(int viewportId)
{
	for(int i = 0 ; i < this->countViewport() ; i++)
	{
		if(this->lstViewport.at(i)->getId() == viewportId)
			return i;
	}
	
	return -1;
}


void GestViewport::onWindowResize(Ogre::RenderWindow * rw)
{
	this->updateViewportSize();
}


void GestViewport::updateViewportSize()
{
	int count = this->countViewport();	
	
	if(count > 0)
	{
		std::vector<ViewportPosDim_t> viewports =  GestViewport::getViewportPosDim(count);
		
		for(int i = 0 ; i < count ; i++)
		{
			Viewport * viewport = this->lstViewport.at(i);
			
			Ogre::Real left = viewports[i].left;
			Ogre::Real top = viewports[i].top;
			Ogre::Real width = viewports[i].width;
			Ogre::Real height = viewports[i].height;
			
			viewport->updateViewportSize(left, top, width, height);
		}
	}
}


// Getter - Setter


int GestViewport::countViewport()
{
	return this->lstViewport.size();
}


std::vector<Viewport *> & GestViewport::getLstViewport()
{
	return this->lstViewport;
}
