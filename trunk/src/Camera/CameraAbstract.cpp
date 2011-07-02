#include "Camera/CameraAbstract.h"
#include "Viewport/GestViewport.h"
#include "Camera/GestCamera.h"

CameraAbstract::CameraAbstract(Ogre::String cameraName)
{
	this->cameraName = cameraName;
	this->camera = GestSceneManager::getSceneManager()->createCamera(cameraName);
	
	// set the frustrum plan
	this->camera->setNearClipDistance(1);
	this->camera->setFarClipDistance(1000);
	
	// enable infinite far clip distance if we can
	if (Ogre::Root::getSingleton().getRenderSystem()->getCapabilities()->hasCapability(Ogre::RSC_INFINITE_FAR_PLANE))
		this->camera->setFarClipDistance(0);
    //permet de gérer les déplacements de caméra
    
    this->nodeCamera = GestSceneManager::getSceneManager()->getSceneNode(NODE_NAME_GROUPE_CAMERA)->createChildSceneNode("nodeCamera_"+cameraName+"_"+Utils::toString(Utils::unique()));
    this->nodeCamera->attachObject(this->camera);
    
    this->translateStep = 1.0;
    this->rotateStep = 0.01;
    

	PlayerControls::getSingletonPtr()->signalMouseMoved.add(&CameraAbstract::onMouseMoved, this);
	PlayerControls::getSingletonPtr()->signalKeyStillPressed.add(&CameraAbstract::onKeyStillPressed, this);
	PlayerControls::getSingletonPtr()->signalKeyPressed.add(&CameraAbstract::onKeyPressed, this);
	PlayerControls::getSingletonPtr()->signalKeyReleased.add(&CameraAbstract::onKeyReleased, this);
	
	ListenerFrame::getSingletonPtr()->signalFrameRendering.add(&CameraAbstract::updateCamera, this);
}


CameraAbstract::~CameraAbstract()
{	
	ListenerFrame::getSingletonPtr()->signalFrameRendering.remove(&CameraAbstract::updateCamera, this);
	
	PlayerControls::getSingletonPtr()->signalMouseMoved.remove(&CameraAbstract::onMouseMoved, this);
	PlayerControls::getSingletonPtr()->signalKeyStillPressed.remove(&CameraAbstract::onKeyStillPressed, this);
	PlayerControls::getSingletonPtr()->signalKeyPressed.remove(&CameraAbstract::onKeyPressed, this);
	PlayerControls::getSingletonPtr()->signalKeyReleased.remove(&CameraAbstract::onKeyReleased, this);
	
	this->nodeCamera->detachObject(this->camera);
	
	GestSceneManager::getSceneManager()->destroySceneNode(this->nodeCamera);
	GestSceneManager::getSceneManager()->destroyCamera(this->cameraName);
}


bool CameraAbstract::insertViewport(Viewport * viewport)
{
	if(this->lstViewport.find(viewport) == this->lstViewport.end())
	{
		this->lstViewport.insert(viewport);
		return true;
	}
	
	return false;
}

bool CameraAbstract::removeViewport(Viewport * viewport)
{
	if(this->lstViewport.find(viewport) != this->lstViewport.end())
	{
		this->lstViewport.erase(viewport);
		return true;
	}
	
	return false;
}

bool CameraAbstract::isInViewport(Ogre::Vector3 position)
{
	if(this->lstViewport.size() > 0)
	{
		std::set<Viewport *>::iterator it;
		for(it = this->lstViewport.begin() ; it != this->lstViewport.end() ; it++)
		{
			if((*it)->isInViewport(position) == true)
				return true;
		}
	}
	
	return false;
}


void CameraAbstract::setDirection( Ogre::Real x, Ogre::Real y, Ogre::Real z )
{
	this->camera->lookAt( Ogre::Vector3(x, y, z) );
}


void CameraAbstract::setDirection( Ogre::Vector3 direction )
{
	this->camera->lookAt( direction );
}


void CameraAbstract::setDirection( Ogre::SceneNode * nodeDirection )
{
	this->camera->lookAt( nodeDirection->getPosition() );
}


void CameraAbstract::setPosition( Ogre::Real x, Ogre::Real y, Ogre::Real z )
{
	this->camera->setPosition( Ogre::Vector3(x, y, z) );
}


void CameraAbstract::setPosition( Ogre::Vector3 position )
{
	this->camera->setPosition( position );
}


void CameraAbstract::move( Ogre::Real x, Ogre::Real y, Ogre::Real z )
{
	this->camera->move( Ogre::Vector3(x, y, z) );
}

void CameraAbstract::move( Ogre::Vector3 position )
{
	this->camera->move( position );
}


void CameraAbstract::moveRelative( Ogre::Real x, Ogre::Real y, Ogre::Real z )
{
	this->camera->moveRelative( Ogre::Vector3(x, y, z) );
}

void CameraAbstract::moveRelative( Ogre::Vector3 position )
{
	this->camera->moveRelative( position );
}




void CameraAbstract::applyTranslateBeforce()
{
}

void CameraAbstract::applyTranslateBehind()
{
}

void CameraAbstract::applyTranslateLeft()
{
}

void CameraAbstract::applyTranslateRight()
{
}

void CameraAbstract::applyTranslateUp()
{
}

void CameraAbstract::applyTranslateDown()
{
}

void CameraAbstract::applyRotateLeft()
{
}

void CameraAbstract::applyRotateRight()
{
}

void CameraAbstract::applyRotateUp()
{
}

void CameraAbstract::applyRotateDown()
{
}



void CameraAbstract::applyTranslateMouse(MouseMove_t &mouseMove)
{
}

void CameraAbstract::applyRotateMouse(MouseMove_t &mouseMove)
{
}

void CameraAbstract::applyWheelMouse(MouseMove_t &mouseMove)
{
}




void CameraAbstract::onMouseMoved(MouseMove_t &mouseMove)
{
	Ogre::Vector3 posMouse = GestInteraction::getSingletonPtr()->getPosMouse();
	if(!GestInteraction::getSingletonPtr()->getMoveAllCamera() && !this->isInViewport(posMouse))
		return;
	
    switch(mouseMove.controlMouseId)
    {
		case Controls::CAMERA_TRANSLATE_MOUSE :
			this->applyTranslateMouse(mouseMove);
			break;
		
		case Controls::CAMERA_ROTATE_MOUSE :
			this->applyRotateMouse(mouseMove);
			break;
		
        default:
            break;
    }
    
    this->applyWheelMouse(mouseMove);
}


void CameraAbstract::onKeyStillPressed(Controls::Controls key)
{
	Ogre::Vector3 posMouse = GestInteraction::getSingletonPtr()->getPosMouse();
	if(!GestInteraction::getSingletonPtr()->getMoveAllCamera() && !this->isInViewport(posMouse))
		return;
		
    switch(key)
    {
		case Controls::CAMERA_TRANSLATE_BEFORE :
			this->applyTranslateBeforce();
			break;
		
		case Controls::CAMERA_TRANSLATE_BEHIND :
			this->applyTranslateBehind();
			break;
		
		case Controls::CAMERA_TRANSLATE_LEFT :
			this->applyTranslateLeft();
			break;
		
		case Controls::CAMERA_TRANSLATE_RIGHT :
			this->applyTranslateRight();
			break;
		
		case Controls::CAMERA_TRANSLATE_UP :
			this->applyTranslateUp();
			break;
		
		case Controls::CAMERA_TRANSLATE_DOWN :
			this->applyTranslateDown();
			break;
		
		case Controls::CAMERA_ROTATE_LEFT :
			this->applyRotateLeft();
			break;
		
		case Controls::CAMERA_ROTATE_RIGHT :
			this->applyRotateRight();
			break;
		
		case Controls::CAMERA_ROTATE_UP :
			this->applyRotateUp();
			break;
		
		case Controls::CAMERA_ROTATE_DOWN :
			this->applyRotateDown();
			break;
			
        default:
            break;
    }
}

void CameraAbstract::onKeyPressed(Controls::Controls key)
{
	Ogre::Vector3 posMouse = GestInteraction::getSingletonPtr()->getPosMouse();
	if(!GestInteraction::getSingletonPtr()->getMoveAllCamera() && !this->isInViewport(posMouse))
		return;
		
    switch(key)
    {
        case Controls::ADD_CAMERA :
        {
			static CameraAbstract * camera3 = GestCamera::getSingletonPtr()->addCamera(CameraAbstract::CAMERA_TARGET, "mainCam3", GestSceneManager::getSceneManager()->getSceneNode(NODE_NAME_GROUPE_CAMERA_TARGET));
			GestViewport::getSingletonPtr()->addViewport(camera3);
            break;
		}
		
        default:
            break;
    }
    
}

void CameraAbstract::onKeyReleased(Controls::Controls key)
{	
	Ogre::Vector3 posMouse = GestInteraction::getSingletonPtr()->getPosMouse();
	if(!GestInteraction::getSingletonPtr()->getMoveAllCamera() && !this->isInViewport(posMouse))
		return;
		
    switch(key)
    {
        default:
            break;
    }
}

//Getter - Setter



Ogre::Camera * CameraAbstract::getCamera()
{
	return this->camera;
}

Ogre::String CameraAbstract::getCameraName()
{
	return this->cameraName;
}


Ogre::Real CameraAbstract::getTranslateStep()
{
	return this->translateStep;
}

void CameraAbstract::setTranslateStep(Ogre::Real translateStep)
{
	this->translateStep = translateStep;
}


Ogre::Real CameraAbstract::getRotateStep()
{
	return this->rotateStep;
}

void CameraAbstract::setRotateStep(Ogre::Real rotateStep)
{
	this->rotateStep = rotateStep;
}
