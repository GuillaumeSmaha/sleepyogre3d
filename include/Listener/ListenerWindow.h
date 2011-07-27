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
 * \file  ListenerWindow.h
 * \brief Ce fichier contient la déclaration de la classe ListenerWindow. C'est la classe gérant les événements de la fenêtre.
 */
#ifndef __LISTENER_WINDOW_H__
#define __LISTENER_WINDOW_H__

#ifndef DOXYGEN_SKIP
#include <Ogre.h>
#include <OISMouse.h>
#endif

#include "Core/Signal.h"
#include "Core/ClassRootSingleton.h"


/*!
 * \class ListenerWindow
 * \brief Classe permettant de gérer les événements de la fenêtre.
 */
class ListenerWindow :  public ClassRootSingleton<ListenerWindow>, public Ogre::WindowEventListener
{
	public:
		/*!
		 * \brief NE PAS UTILISER, present uniquement pour la définition de ClassRootSingleton
         *  il faut utiliser createSingleton(Ogre::Root * root) à la place.
		 */		
		static void createSingleton();
		/*!
		 * \brief Créé le singleton
		 * \param root Pointeur sur l'objet root d'Ogre
		 */		
		static void createSingleton(Ogre::Root  * root);
		/*!
		 * \brief Créé le singleton
		 * \param root Pointeur sur l'objet root d'Ogre
		 * \param windowName Name of the window
		 */		
		static void createSingleton(Ogre::Root  * root, Ogre::String windowName);
		
		
	private:
        /*!
		 * \brief Dispatche un signal lorsque la souris bouge Signal(Ogre::Vector3(X, Y, Z)))
		 */
        Ogre::RenderWindow * renderWindow;		
		
	public:
		/*!
		 * \brief Dispatche un signal lorsque la fenêtre est redimensionnée Signal(Ogre::RenderWindow *)
		 */
		Signal<Ogre::RenderWindow *> signalWindowResized;
		/*!
		 * \brief Dispatche un signal lorsque la fenêtre est fermée Signal(void *)
		 */
		Signal<void *> signalWindowClosed;
		
	public:
		/*!
		 * \brief Constructor
		 * \param root Pointeur sur l'objet root d'Ogre
		 * \param windowName Name of the window
		 */
		ListenerWindow(Ogre::Root * root, Ogre::String windowName);
		/*!
		 * \brief Destructeur
		 */
		~ListenerWindow();

	public:
		/*!
		 * \brief Action à effectuer pour l'événement "redimensionnement de la fenêtre"
		 * 	\param rw Fenêtre de rendu
		 */
        void windowResized(Ogre::RenderWindow * rw);
		/*!
		 * \brief Action à effectuer pour l'événement "fermeture de la fenêtre"
		 * 	\param rw Fenêtre de rendu
		 */
        void windowClosed(Ogre::RenderWindow * rw);
        
		//Getter/Setter
		
		/*!
		 * \brief [Getter] Recupère le pointeur
		 * \return Le pointeur sur le capteur d'événements de la fenêtre
		 */
		Ogre::RenderWindow * getRenderWindow();
		/*!
		 * \brief [Setter] Définit le pointeur
		 * \return window Le pointeur sur le capteur d'événements de la fenêtre
		 */
		void setRenderWindow(Ogre::RenderWindow * renderWindow);
};

#endif //__LISTENER_WINDOW_H__
