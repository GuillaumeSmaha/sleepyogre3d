#include "Camera/CameraFree.h"


CameraFree::CameraFree(Ogre::String cameraName) : CameraAbstract(cameraName)
{
	this->cameraType = CameraAbstract::CAMERA_FREE;
}

CameraFree::~CameraFree()
{
}
		
void CameraFree::initCamera()
{
}
		
void CameraFree::updateCamera(void * null)
{
}


void CameraFree::applyTranslateBeforce()
{
	this->moveRelative(0.0, 0.0, -this->getTranslateStep());
}

void CameraFree::applyTranslateBehind()
{
	this->moveRelative(0.0, 0.0, this->getTranslateStep());
}

void CameraFree::applyTranslateLeft()
{
	this->moveRelative(-this->getTranslateStep(), 0.0, 0.0);
}

void CameraFree::applyTranslateRight()
{
	this->moveRelative(this->getTranslateStep(), 0.0, 0.0);
}

void CameraFree::applyTranslateUp()
{
	this->moveRelative(0.0, this->getTranslateStep(), 0.0);
}

void CameraFree::applyTranslateDown()
{
	this->moveRelative(0.0, -this->getTranslateStep(), 0.0);
}

void CameraFree::applyRotateLeft()
{
	this->camera->yaw(Ogre::Radian(this->getRotateStep()));
}

void CameraFree::applyRotateRight()
{
	this->camera->yaw(-Ogre::Radian(this->getRotateStep()));
}

void CameraFree::applyRotateUp()
{
	this->camera->pitch(Ogre::Radian(this->getRotateStep()));
}

void CameraFree::applyRotateDown()
{
	this->camera->pitch(-Ogre::Radian(this->getRotateStep()));
}



void CameraFree::applyTranslateMouse(MouseMove_t &mouseMove)
{
	Ogre::Real move = (mouseMove.vector[0]+mouseMove.vector[1])/2.0;
	this->moveRelative(0.0, 0.0, move);
}

void CameraFree::applyRotateMouse(MouseMove_t &mouseMove)
{
	Ogre::Degree yaw = Ogre::Degree(-mouseMove.vector[0] * 0.25f);
	Ogre::Degree pitch = Ogre::Degree(-mouseMove.vector[1] * 0.25f);
	
	this->camera->yaw(yaw);
	this->camera->pitch(pitch);
}

void CameraFree::applyWheelMouse(MouseMove_t &mouseMove)
{
	if(abs(mouseMove.vector[2]) > 1.0)
	{
		Ogre::Real move = mouseMove.vector[2]/6.0;
		this->moveRelative(move, 0.0, 0.0);
	}
}
