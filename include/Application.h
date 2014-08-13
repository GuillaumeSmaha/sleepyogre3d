/*
-----------------------------------------------------------------------------
This source file is part of SleepyOgre3D
-----------------------------------------------------------------------------
*/
/*!
 * \file  Application.h
 * \brief Ce fichier contient la déclaration de la classe Application. C'est la classe qui permet d'initialiser le logiciel en partie en gérant les aspecs graphiques et évènement
*/
#ifndef __APPLICATION_H__
#define __APPLICATION_H__


#ifndef DOXYGEN_SKIP
#include <Ogre.h>
#endif

#include "Core/ClassRootSingleton.h"
#include "Scene/InitSceneGraph.h"
#include "Listener/InitListener.h"
#include "Viewport/InitViewport.h"
#include "Controls/InitControls.h"
#include "Menus/InitMenus.h"
#include "Camera/InitCamera.h"
#include "Tools/StatsOverlay.h"
#include "GestInteraction.h"

/*!
* \class Application
* \brief Class principale qui permet de démarrer le programme, d'afficher la fenêtre et de réagir aux évènements (ceux-ci sont ensuite dirigé vers les classes adaptés)
*/
class Application : public ClassRootSingleton<Application>
{
	private:
		/*!
		* \brief Chemin du fichier resources.cfg
		*/
		Ogre::String resourcesCfg;
		
    public:
        /*!
         * \brief Constructeur
        */
        Application();
        /*!
         * \brief Destructeur
        */
        ~Application();
        
    public:
        /*!
         * \brief demarrage du programme
        */
        bool start();
    
        /*!
         * \brief charge les ressources du projet (mesh, material...)
        */
        void loadRessources();
};

#endif 
