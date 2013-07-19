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
 * \file  GestViewport.h
 * \brief Ce fichier contient la déclaration de la classe GestViewport. C'est la classe gérant les événements de la fenêtre.
 */
#ifndef __GEST_VIEWPORT_H__
#define __GEST_VIEWPORT_H__

#ifndef DOXYGEN_SKIP
#include <vector>
#include <algorithm>
#include <math.h>
#include <Ogre.h>
#endif

#include "Core/ClassRootSingleton.h"
#include "Listener/ListenerWindow.h"
#include "Viewport/Viewport.h"
#include "Camera/CameraAbstract.h"
#include "Tools/Utils.h"


/// Define a structure contening the viewport position and dimension
struct ViewportPosDim_t
{
	///Left position
	Ogre::Real left;
	
	///Top position
	Ogre::Real top;
	
	///Width dimension
	Ogre::Real width;
	
	///Height dimension
	Ogre::Real height;
};

/*!
 * \class GestViewport
 * \brief Classe permettant de gérer les viewports.
 */
class GestViewport : public ClassRootSingleton<GestViewport>
{
	public:
		/*!
		 * \brief Returns the list of positions/dimensions for n viewport
		 * \param nbViewport Number of viewport
		 * \return List of viewport
         */
		static std::vector<ViewportPosDim_t> getViewportPosDim(int nbViewport);
		
		
	private:
        /*!
		 * \brief Liste des viewports
		 */
		std::vector<Viewport *> lstViewport;
		
	public:
		/*!
		 * \brief Constructor
		 */
		GestViewport();
		/*!
		 * \brief Destructeur
		 */
		~GestViewport();
		
		
	public:
		/*!
		 * \brief Ajoute un nouveau viewport
		 * \param camera La caméra correspondant au viewport
		 * \return Id du viewport
		 */
		int addViewport(CameraAbstract * camera);
		/*!
		 * \brief Change la caméra affecté à un viewport
		 * \param viewportId Id du viewport
		 * \param camera La caméra correspondant au viewport
		 * \return Si le changement a réussit
		 */
		bool changeCameraViewport(int viewportId, CameraAbstract * camera);
		/*!
		 * \brief Supprime un viewport par son id
		 * \param viewportId Id du viewport
		 * \return Si la suppression à réussit
		 */
		bool removeViewportById(int viewportId);
		/*!
		 * \brief Supprime un viewport par son index
		 * \param viewportIndex Index du viewport
		 * \return Si la suppression à réussit
		 */
		bool removeViewportByIndex(int viewportIndex);
		
		/*!
		 * \brief Return if the position is in the viewport
		 * \param viewportId Viewport id
		 * \param position Position to test
		 * \return If the position is in the viewport
		 */
		bool isInViewport(int viewportId, Ogre::Vector3 position);
		
		/*!
		 * \brief Return the viewport with the viewport id
		 * \param viewportId Viewport id
		 * \return A pointer on the object or 0
		 */
		Viewport * find(int viewportId);
		/*!
		 * \brief Return the index of viewport with the viewport id
		 * \param viewportId Viewport id
		 * \return An index of the viewport on the object or -1
		 */
		int findIndex(int viewportId);
        
        /*!
		 * \brief Permet de recevoir un evènement quand la fenetre est redimensionné
		 * \param rw Pointeur sur le rendu de la fenetre
        */
        void onWindowResize(Ogre::RenderWindow * rw);
		
		
	private:		
		/*!
		 * \brief Update the size of the viewport
		 */
		void updateViewportSize();
        
        
		//Getter - Setter
	public:
         /*!
		 * \brief Returns the number of viewport
		 * \return Number of viewport
         */
		int countViewport();
		/*!
		 * \brief Returns the list of viewport
		 * \return List of viewport
         */
		std::vector<Viewport *> & getLstViewport();
};

#endif //__GEST_VIEWPORT_H__
