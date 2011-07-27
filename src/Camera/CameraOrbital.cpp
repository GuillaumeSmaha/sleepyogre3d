#include "Camera/CameraOrbital.h"


CameraOrbital::CameraOrbital(Ogre::String cameraName, Ogre::Vector3 position) : CameraAbstract(cameraName)
{
	this->cameraType = CameraAbstract::CAMERA_ORBITAL;
	
    this->targetNode = GestSceneManager::getSceneManager()->getSceneNode(NODE_NAME_GROUPE_CAMERA)->createChildSceneNode("nodeOrbitalCamera_"+cameraName+"_"+Utils::toString(Utils::unique()));
    this->targetNode->_setDerivedPosition(position);
    this->targetPosition = position;
}

CameraOrbital::CameraOrbital(Ogre::String cameraName, Ogre::SceneNode * targetNode) : CameraAbstract(cameraName)
{
	this->cameraType = CameraAbstract::CAMERA_ORBITAL;
	
	if(targetNode == NULL)
	{
		std::cerr << std::endl << "CameraOrbital::CameraOrbital : targetNode is NULL !" << std::endl << std::endl;
		return;
	}
    this->targetNode = GestSceneManager::getSceneManager()->getSceneNode(NODE_NAME_GROUPE_CAMERA)->createChildSceneNode("nodeOrbitalCamera_"+cameraName+"_"+Utils::toString(Utils::unique()));
    this->targetNode->_setDerivedPosition(targetNode->_getDerivedPosition());
    this->targetPosition = targetNode->_getDerivedPosition();
}


CameraOrbital::~CameraOrbital()
{
	GestSceneManager::getSceneManager()->destroySceneNode(this->targetNode);
}
		
void CameraOrbital::initCamera()
{
	this->camera->setNearClipDistance(1);
	this->camera->setFarClipDistance(1000);

	// enable infinite far clip distance if we can
	if (Ogre::Root::getSingleton().getRenderSystem()->getCapabilities()->hasCapability(Ogre::RSC_INFINITE_FAR_PLANE))
		this->camera->setFarClipDistance(0);   

	// set the position ant rotation of the camera to look at the target
	this->camera->setPosition(this->targetNode->_getDerivedPosition());
	this->camera->setOrientation(this->targetNode->_getDerivedOrientation());
	this->camera->yaw(Ogre::Radian(180));
	this->camera->pitch(Ogre::Radian(-15));
	this->camera->moveRelative(Ogre::Vector3(0.0, 0.0, 500.0));


    this->camera->setFixedYawAxis(true, Ogre::Vector3::UNIT_Z);    
    this->camera->setAutoTracking(true, this->targetNode);
    
	this->targetPosition = this->targetNode->_getDerivedPosition();
}
		
void CameraOrbital::updateCamera(void * null)
{
	Ogre::Vector3 vec = (this->targetPosition - this->targetNode->_getDerivedPosition());
	Ogre::Real dist = vec.length();
	
	if(dist > 1.0)
	{
		vec.normalise();
		this->moveCameraOrbital(vec);
	}
}


void CameraOrbital::applyTranslateBeforce()
{
	this->targetPosition += Ogre::Vector3(this->getTranslateStep(), 0.0, 0.0);
}

void CameraOrbital::applyTranslateBehind()
{
	this->targetPosition += Ogre::Vector3(-this->getTranslateStep(), 0.0, 0.0);
}

void CameraOrbital::applyTranslateLeft()
{
	this->targetPosition += Ogre::Vector3(0.0, -this->getTranslateStep(), 0.0);
}

void CameraOrbital::applyTranslateRight()
{
	this->targetPosition += Ogre::Vector3(0.0, this->getTranslateStep(), 0.0);
}

void CameraOrbital::applyTranslateUp()
{
	this->zoom(-this->getTranslateStep());
}

void CameraOrbital::applyTranslateDown()
{
	this->zoom(this->getTranslateStep());
}

void CameraOrbital::applyRotateLeft()
{
	Ogre::Degree yaw = Ogre::Degree(-this->getRotateStep());
	Ogre::Degree pitch = Ogre::Degree(0.0);
	
	this->checkRotation(&yaw, &pitch);
	
	Ogre::Real dist = (this->camera->getPosition() - this->targetNode->_getDerivedPosition()).length();
	
	this->camera->setPosition(this->targetNode->_getDerivedPosition());

	this->camera->yaw(yaw);
	this->camera->pitch(pitch);
	
	this->camera->moveRelative(Ogre::Vector3(0.0, 0.0, dist));
}

void CameraOrbital::applyRotateRight()
{
	Ogre::Degree yaw = Ogre::Degree(this->getRotateStep());
	Ogre::Degree pitch = Ogre::Degree(0.0);
	
	this->checkRotation(&yaw, &pitch);
	
	Ogre::Real dist = (this->camera->getPosition() - this->targetNode->_getDerivedPosition()).length();
	
	this->camera->setPosition(this->targetNode->_getDerivedPosition());

	this->camera->yaw(yaw);
	this->camera->pitch(pitch);
	
	this->camera->moveRelative(Ogre::Vector3(0.0, 0.0, dist));
}

void CameraOrbital::applyRotateUp()
{
	Ogre::Degree yaw = Ogre::Degree(0.0);
	Ogre::Degree pitch = Ogre::Degree(this->getRotateStep());
	
	this->checkRotation(&yaw, &pitch);
	
	Ogre::Real dist = (this->camera->getPosition() - this->targetNode->_getDerivedPosition()).length();
	
	this->camera->setPosition(this->targetNode->_getDerivedPosition());

	this->camera->yaw(yaw);
	this->camera->pitch(pitch);
	
	this->camera->moveRelative(Ogre::Vector3(0.0, 0.0, dist));
}

void CameraOrbital::applyRotateDown()
{
	Ogre::Degree yaw = Ogre::Degree(0.0);
	Ogre::Degree pitch = Ogre::Degree(-this->getRotateStep());
	
	this->checkRotation(&yaw, &pitch);
	
	Ogre::Real dist = (this->camera->getPosition() - this->targetNode->_getDerivedPosition()).length();
	
	this->camera->setPosition(this->targetNode->_getDerivedPosition());

	this->camera->yaw(yaw);
	this->camera->pitch(pitch);
	
	this->camera->moveRelative(Ogre::Vector3(0.0, 0.0, dist));
}



void CameraOrbital::applyTranslateMouse(MouseMove_t &mouseMove)
{
	this->zoom((mouseMove.vector[0]+mouseMove.vector[1])/2.0);
}

void CameraOrbital::applyRotateMouse(MouseMove_t &mouseMove)
{
	Ogre::Degree yaw = Ogre::Degree(mouseMove.vector[0] * 0.25f);
	Ogre::Degree pitch = Ogre::Degree(mouseMove.vector[1] * 0.25f);
	
	this->checkRotation(&yaw, &pitch);
	
	Ogre::Real dist = (this->camera->getPosition() - this->targetNode->_getDerivedPosition()).length();
	
	this->camera->setPosition(this->targetNode->_getDerivedPosition());

	this->camera->yaw(yaw);
	this->camera->pitch(pitch);
	
	this->camera->moveRelative(Ogre::Vector3(0.0, 0.0, dist));
}

void CameraOrbital::applyWheelMouse(MouseMove_t &mouseMove)
{
	if(abs(mouseMove.vector[2]) > 1.0)
		this->zoom(-mouseMove.vector[2]/6.0);
}


void CameraOrbital::zoom(Ogre::Real zoomDist)
{
	Ogre::Real distMin = 25.0;
    Ogre::Real dist = (this->camera->getPosition() - this->targetNode->_getDerivedPosition()).length();
    
    if((dist < distMin && zoomDist > 0) || (dist >= distMin && (dist+zoomDist) > distMin))
    {
		this->camera->moveRelative(Ogre::Vector3(0.0, 0.0, zoomDist));
	}
}

void CameraOrbital::checkRotation(Ogre::Degree * yaw, Ogre::Degree * pitch)
{
	Ogre::Real distZ = this->camera->getPosition()[2] - this->targetNode->_getDerivedPosition()[2];
	Ogre::Real dist = (this->camera->getPosition() - this->targetNode->_getDerivedPosition()).length();
	Ogre::Real seuil = 5.0 + abs(distZ / 50.0);
		
	if((distZ >= 0 && (distZ+seuil) > dist && pitch->valueDegrees() <= 0.0)
		|| (distZ < 0 && (distZ-seuil) < -dist && pitch->valueDegrees() > 0.0))
		*pitch = Ogre::Degree(0.0);
}


void CameraOrbital::moveCameraOrbital(Ogre::Vector3 vector)
{
	Ogre::Real dist = (this->camera->getPosition() - this->targetNode->_getDerivedPosition()).length();
	Ogre::Vector3 vec = this->targetNode->getPosition() + vector;
	this->targetNode->setPosition(vec);
	Ogre::Real newDist = (this->camera->getPosition() - this->targetNode->_getDerivedPosition()).length();
	this->zoom(dist-newDist);
}



void CameraOrbital::setPositionTarget(Ogre::Vector3 targetPosition)
{
	this->targetPosition = targetPosition;
}


Ogre::SceneNode * CameraOrbital::getTargetNode()
{
	return this->targetNode;
}
