/*!
 * \file InitScene.h
 * \brief This file contains the declaration of the class InitScene.
 */
#ifndef __INIT_SCENE_H__
#define __INIT_SCENE_H__

#include "Core/InitAbstract.h"
#include "Scene/nodeName.h"
#include "Scene/GestSceneManager.h"

/*!
 * \class InitScene
 * \brief Class to init the scene
 */
class InitScene : public InitAbstract
{		
	public:
		/*!
		 * \brief Init the scene
		 */
		static void init();		
		/*!
		 * \brief Destroy the scene
		 */
		static void destroy();
		
};

#endif //__INIT_SCENE_H__
