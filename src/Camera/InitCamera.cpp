#include "Camera/InitCamera.h"

void InitCamera::init()
{
    
    CameraAbstract * camera2 = GestCamera::getSingletonPtr()->addCamera(CameraAbstract::CAMERA_FREE, "mainCam2");
    camera2->setPosition(0.0, 0.0, 250.0);
    
    
    CameraAbstract * camera3 = GestCamera::getSingletonPtr()->addCamera(CameraAbstract::CAMERA_ORBITAL, "mainCam3", GestSceneManager::getSceneManager()->getSceneNode(NODE_NAME_GROUPE_CAMERA_TARGET));
    
    //~ CameraAbstract * camera = GestCamera::getSingletonPtr()->addCamera(CameraAbstract::CAMERA_TARGET, "mainCam", GestSceneManager::getSceneManager()->getSceneNode(NODE_NAME_GROUPE_CAMERA_TARGET));
    //~ CameraAbstract * camera4 = GestCamera::getSingletonPtr()->addCamera(CameraAbstract::CAMERA_ORBITAL_TARGET, "mainCam4", GestSceneManager::getSceneManager()->getSceneNode(NODE_NAME_GROUPE_CAMERA_TARGET));
   
		
	if(GestViewport::getSingletonPtr() != 0)
	{
		GestViewport::getSingletonPtr()->addViewport(camera2);
		GestViewport::getSingletonPtr()->addViewport(camera3);
		//~ GestViewport::getSingletonPtr()->addViewport(camera);
		//~ GestViewport::getSingletonPtr()->addViewport(camera4);
    }
}

void InitCamera::destroy()
{
	GestCamera::destroySingleton();
}
