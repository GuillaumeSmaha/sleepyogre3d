/*!
 * \file InitSceneGraph.h
 * \brief This file contains the declaration of the class InitSceneGraph.
 */
#ifndef __INIT_SCENE_GRAPH_H__
#define __INIT_SCENE_GRAPH_H__

#include "Core/InitAbstract.h"
#include "Scene/nodeName.h"
#include "Scene/GestSceneManager.h"

/*!
 * \class InitSceneGraph
 * \brief Class to init the scene graph
 */
class InitSceneGraph : public InitAbstract
{		
	public:
		/*!
		 * \brief Init the scene graph
		 */
		static void init();		
		/*!
		 * \brief Destroy the scene graph
		 */
		static void destroy();
		
};

#endif //__INIT_SCENE_GRAPH_H__
