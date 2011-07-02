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
 * \file  ListenerInputManager.h
 * \brief Ce fichier contient la déclaration de la classe ListenerInputManager. C'est la classe gérant les événements du clavier.
 */
#ifndef __LISTENER_INPUT_MANAGER_H__
#define __LISTENER_INPUT_MANAGER_H__

#ifndef DOXYGEN_SKIP
#include <OISInputManager.h>
#endif

#include "Core/ClassRootSingleton.h"
#include "Listener/ListenerWindow.h"


/*!
 * \class ListenerInputManager
 * \brief Classe permettant de gérer les événements du clavier.
 */
class ListenerInputManager : public ClassRootSingleton<ListenerInputManager>
{			
	public:
		/*!
		 * \brief Créé le singleton
		 */		
		static void createSingleton();
		
	private:
		/*!
		 * \brief Gestionnaire d'entrées
		 */
        OIS::InputManager * inputManager;
                
        
	public:
		/*!
		 * \brief Constructeur
		 */
		ListenerInputManager();
		/*!
		 * \brief Destructeur
		 */
		~ListenerInputManager();

        
        //Getter/Setter

	public:
		/*!
		* \brief [Getter] Returns a pointer on inputManager
		* \return Get the value of inputManager
		*/
		OIS::InputManager * getInputManager()
		{
			return this->inputManager;
		}
};

#endif //__LISTENER_INPUT_MANAGER_H__
