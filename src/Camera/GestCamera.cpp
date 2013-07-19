#include "Camera/GestCamera.h"

template<> GestCamera * ClassRootSingleton<GestCamera>::_instance = 0;

GestCamera::GestCamera() : ClassRootSingleton<GestCamera>()
{
}

GestCamera::~GestCamera()
{
	while(this->removeCamera(0)) {};
}

void GestCamera::addCamera(CameraAbstract * camera)
{
    this->listCameras.push_back(camera);
}


CameraAbstract * GestCamera::addCamera(CameraAbstract::CameraType cameraType, Ogre::String cameraName, void * param1)
{
	CameraAbstract * cam = 0;
	switch(cameraType)
	{
		case CameraAbstract::CAMERA_FREE :
			cam = new CameraFree(cameraName);
			this->listCameras.push_back(cam);
			break;
			
		case CameraAbstract::CAMERA_ORBITAL :
			cam = new CameraOrbital(cameraName, static_cast<Ogre::SceneNode *>(param1));
			this->listCameras.push_back(cam);
			break;
			
		case CameraAbstract::CAMERA_ORBITAL_TARGET :
			cam = new CameraOrbitalTarget(cameraName, static_cast<Ogre::SceneNode *>(param1));
			this->listCameras.push_back(cam);
			break;
			
		case CameraAbstract::CAMERA_TARGET :
			cam = new CameraTarget(cameraName, static_cast<Ogre::SceneNode *>(param1));
			this->listCameras.push_back(cam);
			break;
			
		default:
			break;
	}
	
	cam->initCamera();
	
	return cam;
}


bool GestCamera::removeCamera(CameraAbstract * cam)
{
	for(unsigned int i = 0; i < this->listCameras.size() ; i++)
	{
		if(this->listCameras[i] == cam)
		{
			delete cam;
			this->listCameras.erase(this->listCameras.begin()+i);
			return true;
		}
	}
	
	return false;
}

bool GestCamera::removeCamera(unsigned int id)
{
	if(id >= this->listCameras.size())
	{
		return false;
	}
	
	CameraAbstract * cam = this->listCameras.at(id);
	this->listCameras.erase(this->listCameras.begin()+id);
	delete cam;
	
	return true;
}

CameraAbstract * GestCamera::getCamera(unsigned int id)
{
    if(id >= this->listCameras.size())
    {
        return 0;
    }
    return this->listCameras.at(id);
}
