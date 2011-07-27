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
 * \file MouseFunction.h
 * \brief This file contains the declaration of a structure for mouse dragging
*/
#ifndef __MOUSE_FUNCTION_H__
#define __MOUSE_FUNCTION_H__

#ifndef DOXYGEN_SKIP
#include <Ogre.h>
#include <CEGUI.h>
#include <OIS.h>
#endif

#include "Core/ClassRootSingleton.h"
#include "Listener/ListenerWindow.h"

/*!
 * \class MouseFunction
 * \brief Classe permettant de gérer les functions de la souris
 */
class MouseFunction : public ClassRootSingleton<MouseFunction>
{	
     
	public:
        /*!
         * \brief Permet de convertir les clics de souris pour CEGUI
         * \param id Evenement OIS de la souris
         * \return Evenement CEGUI de la souris
        */
        static CEGUI::MouseButton convertButton(OIS::MouseButtonID id);  
        
	public:
		/*!
		 * \brief NE PAS UTILISER, present uniquement pour la définition de ClassRootSingleton
         *  il faut utiliser createSingleton(Ogre::RenderWindow * win) à la place.
		*/		
        static void createSingleton();
        /*!
         * Permet de creer la souris, celle ci ce présente sous la forme d'un curseur qui peut saisir les briquettes.
         * \param win: Le renderWindow permet d'avoir la taille de la fenetre et donc d'adapter la taille du curseur à celle ci
        */
        static void createSingleton(Ogre::RenderWindow * win);
        
	private:        
        /*!
         * \brief Position de la souris
        */
        Ogre::Vector3 posMouse;
        /*!
         * \brief Permet de conserver la largeur la fenetre
        */
        int winWidth;
        /*!
         * \brief Permet de conserver la hauteur de la fenetre
        */
        int winHeight;
        
	public:
        /*!
         * \brief Constructor
         * \param win Le renderWindow permet d'avoir la taille de la fenetre et donc d'adapter la taille du curseur à celle ci
        */
		MouseFunction(Ogre::RenderWindow * win);
        /*!
         * \brief Destructor
        */
		~MouseFunction();

	public:
        /*!
         * \brief Permet de déplacer la souris en lui injectant le vecteur x, y.
         * La souris n'est pas géré directement dans cette classe mais dans la
         * classe MouseFunction car en réalité on à 2 souris (la souris du
         * menus CEGUI et la souris de bullet pour attraper les briquettes.
         *
         * Cette fonction permet donc a GestInteraction de déplacer la souris de
         * Bullet pour que les deux ai la même position
         * \param delta_x Déplacement sur l'axe X
         * \param delta_y Déplacement sur l'axe Y
        */
        void injectMouseMove(float delta_x, float delta_y);
        
        /*!
		 * \brief Permet de recevoir un evènement quand la fenetre est redimensionné
		 * \param rw Pointeur sur le rendu de la fenetre
        */
        void onWindowResize(Ogre::RenderWindow * rw);
             
           
		// Getter - Setter
        /*!
         * \brief [Getter] Return the mouse position
         * \return The value of "posMouse"
        */
        Ogre::Vector3 getPosMouse();   
		
};

#endif //__MOUSE_FUNCTION_H__
