/*
-----------------------------------------------------------------------------
This source file is part of SleepyOgre3D
 
Copyright (c) 2011 Guillaume Smaha

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
of the Software, and to permit persons to whom the Software is furnished to do
so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
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
