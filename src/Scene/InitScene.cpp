#include "Scene/InitScene.h"
#include "Camera/GestCamera.h"
#include "Camera/CameraAbstract.h"
#include "Viewport/GestViewport.h"

void InitScene::init()
{
	GestSceneManager::getSceneManager()->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));
	Ogre::Light * l = GestSceneManager::getSceneManager()->createLight("MainLight");
	l->setPosition(250.0, 250.0, 0.0);
	l->setDirection(0.0, 0.0, 0.0);
	Ogre::SceneNode * nodeLight1 = GestSceneManager::getSceneManager()->getRootSceneNode()->createChildSceneNode("NodeLight1");
	nodeLight1->attachObject(l);		
	
	
	Ogre::SceneNode * ogreHeadNode = GestSceneManager::getSceneManager()->getSceneNode(NODE_NAME_GROUPE_OBJECT)->createChildSceneNode("OgreNode");
	Ogre::Entity * ogreHead = GestSceneManager::getSingletonPtr()->createEntity("Ogre", "Ogre.mesh");
	ogreHeadNode->attachObject(ogreHead);
	
    
    CameraAbstract * camera = GestCamera::getSingletonPtr()->addCamera(CameraAbstract::CAMERA_TARGET, "mainCam", ogreHeadNode);
    CameraAbstract * camera4 = GestCamera::getSingletonPtr()->addCamera(CameraAbstract::CAMERA_ORBITAL_TARGET, "mainCam4", ogreHeadNode);
    
	GestViewport::getSingletonPtr()->addViewport(camera);
	GestViewport::getSingletonPtr()->addViewport(camera4);
}

void InitScene::destroy()
{
}
