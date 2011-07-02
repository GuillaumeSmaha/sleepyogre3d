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
 * \file  GestSceneManager.h
 * \brief Ce fichier contient la déclaration de la classe GestSceneManager. 
 */
#ifndef __GEST_SCENE_MANAGER_H__
#define __GEST_SCENE_MANAGER_H__

#ifndef DOXYGEN_SKIP
#include <Ogre.h>
#endif

#include "Core/ClassRootSingleton.h"


/*!
 * \class GestSceneManager
 * \brief Classe permettant de gérer les viewports.
 */
class GestSceneManager : public ClassRootSingleton<GestSceneManager>
{
	public:
		/*!
		* \brief [Getter] Returns a pointer on sceneManager
		* \return Get the value of sceneManager
		*/
		static Ogre::SceneManager * getSceneManager();
		/*!
		* \brief [Getter] Returns a pointer on root
		* \return Get the value of root
		*/
		static Ogre::Root * getRoot();
		
	private:
		/*!
		* \brief Ogre root
		*/
		Ogre::Root * root;
		
		/*!
		* \brief Scene manager
		*/
		Ogre::SceneManager * sceneManager;		
		
		
	public:
		/*!
		 * \brief Constructor
		 */
		GestSceneManager();
		/*!
		 * \brief Destructeur
		 */
		~GestSceneManager();
	
    public:
        /*!
         * \brief Permet de créer une nouvelle entité
        */
        Ogre::Entity * createEntity(const Ogre::String &name, const Ogre::String meshName);
};

#endif //__GEST_SCENE_MANAGER_H__
