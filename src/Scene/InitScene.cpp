#include "Scene/InitScene.h"

void InitScene::init()
{
	GestSceneManager::getSceneManager()->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));
	Ogre::Light * l = GestSceneManager::getSceneManager()->createLight("MainLight");
	l->setPosition(250.0, 250.0, 0.0);
	l->setDirection(0.0, 0.0, 0.0);
	Ogre::SceneNode * nodeLight1 = GestSceneManager::getSceneManager()->getRootSceneNode()->createChildSceneNode("NodeLight1");
	nodeLight1->attachObject(l);		
	
	
	Ogre::Entity * ogreHead = GestSceneManager::getSingletonPtr()->createEntity("Ogre", "Ogre.mesh");
	//~ ogreHead->setMaterialName("Ogre");
	Ogre::SceneNode * ogreHeadNode = GestSceneManager::getSceneManager()->getSceneNode(NODE_NAME_GROUPE_OBJECT)->createChildSceneNode("OgreNode");
	ogreHeadNode->attachObject(ogreHead);
}

void InitScene::destroy()
{
}
