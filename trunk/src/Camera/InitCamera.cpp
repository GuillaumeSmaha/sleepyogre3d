#include "Camera/InitCamera.h"

void InitCamera::init()
{
    CameraAbstract * camera = GestCamera::getSingletonPtr()->addCamera(CameraAbstract::CAMERA_TARGET, "mainCam", GestSceneManager::getSceneManager()->getSceneNode(NODE_NAME_GROUPE_CAMERA_TARGET));
    
    
    CameraAbstract * camera2 = GestCamera::getSingletonPtr()->addCamera(CameraAbstract::CAMERA_FREE, "mainCam2");
    camera2->setPosition(0.0, 0.0, 250.0);
    
	if(GestViewport::getSingletonPtr() != NULL)
	{
		GestViewport::getSingletonPtr()->addViewport(camera);
		GestViewport::getSingletonPtr()->addViewport(camera2);
    }
}

void InitCamera::destroy()
{
	GestCamera::destroySingleton();
}
