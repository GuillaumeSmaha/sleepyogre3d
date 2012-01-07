#include "Camera/CameraOrbitalTarget.h"


CameraOrbitalTarget::CameraOrbitalTarget(Ogre::String cameraName, Ogre::SceneNode * targetNode) : CameraAbstract(cameraName)
{
	this->cameraType = CameraAbstract::CAMERA_ORBITAL_TARGET;
	
	if(targetNode == NULL)
	{
		std::cerr << std::endl << "CameraOrbitalTarget::CameraOrbitalTarget : targetNode is NULL !" << std::endl << std::endl;
		return;
	}
    this->targetNode = targetNode->createChildSceneNode("nodeOrbitalTargetCamera_"+cameraName+"_"+Utils::toString(Utils::unique()));
    this->targetNode->setPosition(0.0, 0.0, 0.0);
    this->targetPosition = targetNode->_getDerivedPosition();
    
	this->targetEntity = GestSceneManager::getSingletonPtr()->createEntity("Sphere"+Utils::toString(Utils::unique()), "Sphere.mesh");
	this->targetEntity->setMaterialName("SphereGreen");
	this->targetNode->attachObject(this->targetEntity);
}


CameraOrbitalTarget::~CameraOrbitalTarget()
{
	GestSceneManager::getSceneManager()->destroySceneNode(this->targetNode);
}
		
void CameraOrbitalTarget::initCamera()
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
		
void CameraOrbitalTarget::updateCamera(void * null)
{
	Ogre::Vector3 vec = (this->targetPosition - this->targetNode->_getDerivedPosition());
	Ogre::Real dist = vec.length();
	
	if(dist > 1.0)
	{
		//~ vec.normalise();
		this->moveCameraOrbitalTarget(vec);
	}
}

void CameraOrbitalTarget::applyTranslateBeforce()
{
	//~ this->targetPosition += Odgre::Vector3(this->getTranslateStep(), 0.0, 0.0);
	this->targetNode->setPosition(this->targetNode->getPosition() + Ogre::Vector3(this->getTranslateStep(), 0.0, 0.0));
}

void CameraOrbitalTarget::applyTranslateBehind()
{
	//~ this->targetPosition += Ogre::Vector3(-this->getTranslateStep(), 0.0, 0.0);
	this->targetNode->setPosition(this->targetNode->getPosition() + Ogre::Vector3(-this->getTranslateStep(), 0.0, 0.0));
}

void CameraOrbitalTarget::applyTranslateLeft()
{
	//~ this->targetPosition += Ogre::Vector3(0.0, -this->getTranslateStep(), 0.0);
	this->targetNode->setPosition(this->targetNode->getPosition() + Ogre::Vector3(0.0, -this->getTranslateStep(), 0.0));
}

void CameraOrbitalTarget::applyTranslateRight()
{
	//~ this->targetPosition += Ogre::Vector3(0.0, this->getTranslateStep(), 0.0);
	this->targetNode->setPosition(this->targetNode->getPosition() + Ogre::Vector3(0.0, -this->getTranslateStep(), 0.0));
}

void CameraOrbitalTarget::applyTranslateUp()
{
	this->zoom(-this->getTranslateStep());
}

void CameraOrbitalTarget::applyTranslateDown()
{
	this->zoom(this->getTranslateStep());
}

void CameraOrbitalTarget::applyRotateLeft()
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

void CameraOrbitalTarget::applyRotateRight()
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

void CameraOrbitalTarget::applyRotateUp()
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

void CameraOrbitalTarget::applyRotateDown()
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



void CameraOrbitalTarget::applyTranslateMouse(MouseMove_t &mouseMove)
{
	this->zoom((mouseMove.vector[0]+mouseMove.vector[1])/2.0);
}

void CameraOrbitalTarget::applyRotateMouse(MouseMove_t &mouseMove)
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

void CameraOrbitalTarget::applyWheelMouse(MouseMove_t &mouseMove)
{
	if(abs(mouseMove.vector[2]) > 1.0)
		this->zoom(-mouseMove.vector[2]/6.0);
}


void CameraOrbitalTarget::zoom(Ogre::Real zoomDist)
{
	Ogre::Real distMin = 25.0;
    Ogre::Real dist = (this->camera->getPosition() - this->targetNode->_getDerivedPosition()).length();
    
    if((dist < distMin && zoomDist > 0) || (dist >= distMin && (dist+zoomDist) > distMin))
    {
		this->camera->moveRelative(Ogre::Vector3(0.0, 0.0, zoomDist));
	}
}

void CameraOrbitalTarget::checkRotation(Ogre::Degree * yaw, Ogre::Degree * pitch)
{
	Ogre::Real distZ = this->camera->getPosition()[2] - this->targetNode->_getDerivedPosition()[2];
	Ogre::Real dist = (this->camera->getPosition() - this->targetNode->_getDerivedPosition()).length();
	Ogre::Real seuil = 5.0 + abs(distZ / 50.0);
		
	if((distZ >= 0 && (distZ+seuil) > dist && pitch->valueDegrees() <= 0.0)
		|| (distZ < 0 && (distZ-seuil) < -dist && pitch->valueDegrees() > 0.0))
		*pitch = Ogre::Degree(0.0);
}


void CameraOrbitalTarget::moveCameraOrbitalTarget(Ogre::Vector3 vector)
{
	Ogre::Real dist = (this->camera->getPosition() - this->targetNode->_getDerivedPosition()).length();
	Ogre::Vector3 vec = this->targetNode->getPosition() + vector;
	this->targetNode->setPosition(vec);
	Ogre::Real newDist = (this->camera->getPosition() - this->targetNode->_getDerivedPosition()).length();
	this->zoom(dist-newDist);
}



void CameraOrbitalTarget::setPositionTarget(Ogre::Vector3 targetPosition)
{
	this->targetPosition = targetPosition;
}


Ogre::SceneNode * CameraOrbitalTarget::getTargetNode()
{
	return this->targetNode;
}
