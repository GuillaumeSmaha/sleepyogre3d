#include "Scene/InitSceneGraph.h"

void InitSceneGraph::init()
{
	GestSceneManager::createSingleton();
	
	if(GestSceneManager::getSceneManager() != NULL)
	{
		GestSceneManager::getSceneManager()->getRootSceneNode()->createChildSceneNode(NODE_NAME_GROUPE_CAMERA);
		GestSceneManager::getSceneManager()->getRootSceneNode()->createChildSceneNode(NODE_NAME_GROUPE_CAMERA_TARGET);
		GestSceneManager::getSceneManager()->getRootSceneNode()->createChildSceneNode(NODE_NAME_GROUPE_OBJECT);
		
		GestSceneManager::getSceneManager()->getSceneNode(NODE_NAME_GROUPE_CAMERA)->setPosition(0.0, 0.0, 0.0);
		GestSceneManager::getSceneManager()->getSceneNode(NODE_NAME_GROUPE_CAMERA_TARGET)->setPosition(0.0, 0.0, 0.0);
		GestSceneManager::getSceneManager()->getSceneNode(NODE_NAME_GROUPE_OBJECT)->setPosition(0.0, 0.0, 0.0);
	}
}

void InitSceneGraph::destroy()
{
	if(GestSceneManager::getSceneManager() != NULL)
	{
		GestSceneManager::getSceneManager()->getSceneNode(NODE_NAME_GROUPE_CAMERA)->removeAndDestroyAllChildren();
		GestSceneManager::getSceneManager()->getSceneNode(NODE_NAME_GROUPE_CAMERA_TARGET)->removeAndDestroyAllChildren();
		GestSceneManager::getSceneManager()->getSceneNode(NODE_NAME_GROUPE_OBJECT)->removeAndDestroyAllChildren();
		
		GestSceneManager::getSceneManager()->destroySceneNode(NODE_NAME_GROUPE_CAMERA);
		GestSceneManager::getSceneManager()->destroySceneNode(NODE_NAME_GROUPE_CAMERA_TARGET);
		GestSceneManager::getSceneManager()->destroySceneNode(NODE_NAME_GROUPE_OBJECT);
	}
}
