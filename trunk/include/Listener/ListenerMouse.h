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
 * \file  ListenerMouse.h
 * \brief Ce fichier contient la déclaration de la classe ListenerKeyboard. C'est la classe gérant les événements de la souris.
 */
#ifndef __LISTENER_MOUSE_H__
#define __LISTENER_MOUSE_H__

#ifndef DOXYGEN_SKIP
#include <list>
#include <OISMouse.h>
#endif

#include "Core/Signal.h"
#include "Core/ClassRootSingleton.h"
#include "Listener/ListenerWindow.h"
#include "Listener/ListenerFrame.h"
#include "Listener/ListenerInputManager.h"
#include "Controls/mouseMove.h"


/*!
 * \class ListenerMouse
 * \brief Classe permettant de gérer les événements de la souris.
 */
class ListenerMouse : public ClassRootSingleton<ListenerMouse>, public OIS::MouseListener 
{
	public:
		/*!
		 * \brief Créé le singleton
		 */		
		static void createSingleton();
		
	private:
		/*!
		 * \brief Capteur d'événements de la souris
		 */
        OIS::Mouse * mouse;
		/*!
		 * \brief Capteur d'événements de la souris
		 */
        std::list<OIS::MouseButtonID> lstMousePressedId;

	public:
        /*!
		 * \brief Dispatche un signal lorsque la souris bouge Signal(Ogre::Vector3(X, Y, Z)))
		 */
        Signal<MouseMove_t&> signalMouseMoved;
        /*!
		 * \brief Dispatche un signal lorsque une touche de la souris est enfoncée Signal(OIS::MouseButtonID)
		 */
        Signal<OIS::MouseButtonID> signalMousePressed;
        /*!
		 * \brief Dispatche un signal lorsque une touche de la souris est relâchée Signal(OIS::MouseButtonID)
		 */
        Signal<OIS::MouseButtonID> signalMouseReleased;
        
	public:
		/*!
		 * \brief Constructeur
		 */
		ListenerMouse();
		/*!
		 * \brief Destructeur
		 */
		~ListenerMouse();
		
	public:
		/*!
		 * \brief Recupère les événements
		 */
		void capture();
		/*!
		 * \brief Recupère les événements
		 */
		void capture(void *);
		/*!
		 * \brief Action à effectuer pour l'événement "souis en mouvement"
		 * \param evt Evenement de la souris
		 * \return Si il y a une erreur durant l'événement
		 */
        bool mouseMoved( const OIS::MouseEvent &evt );
		/*!
		 * \brief Action à effectuer pour l'événement "touche de la souris cliquée"
		 * \param evt Evenement de la souris
		 * \param id Identifiant du bouton de la souris
		 * \return Si il y a une erreur durant l'événement
		 */
        bool mousePressed( const OIS::MouseEvent &evt, OIS::MouseButtonID id );
		/*!
		 * \brief Action à effectuer pour l'événement "touche de la souris relachée"
		 * \param evt Evenement de la souris
		 * \param id Identifiant du bouton de la souris
		 * \return Si il y a une erreur durant l'événement
		 */
        bool mouseReleased( const OIS::MouseEvent &evt, OIS::MouseButtonID id );
        
        /*!
		 * \brief Permet de recevoir un evènement quand la fenetre est redimensionné
		 * \param rw Pointeur sur le rendu de la fenetre
        */
        void onWindowResize(Ogre::RenderWindow * rw);
        
        
        //Getter/Setter
        
        
		/*!
		 * \brief Retourne le dernier bouton de la souris pressé
		 * \return Dernier élément de la liste lstMousePressedId
		 */
        OIS::MouseButtonID getLastMousePressedId();

		/*!
		 * \brief [Getter] Récupère la valeur de mouse
		 * \return Le pointeur sur le capteur d'événements de la souris
		 */
		OIS::Mouse * getMouse();
};

#endif //__LISTENER_MOUSE_H__
