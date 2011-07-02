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
 * \file  CameraTarget.h
 * \brief Ce fichier contient la déclaration de la classe CameraTarget. C'est la classe gérant une caméra fixe.
 */
#ifndef __CAMERA_TARGET_H__
#define __CAMERA_TARGET_H__

#ifndef DOXYGEN_SKIP
#include <Ogre.h>
#endif

#include "Camera/CameraAbstract.h"


/*!
 * \class CameraTarget
 * \brief Classe permettant de gérer une caméra orbitale autour d'un point.
 */
class CameraTarget : public CameraAbstract
{

    private:
		/*!
		 * \brief Cible de la caméra
		 */
        Ogre::SceneNode * targetNode;        
		/*!
		 * \brief Position de la cible de la caméra
		 */
        Ogre::Vector3 targetPosition;
        
        
	public:
		/*!
		 * \brief Constructeur
		 * \param cameraType Type nouvelle caméra
		 * \param cameraName Nom de la nouvelle caméra
		 * \param targetNode Cible de la caméra
		 */
		CameraTarget(Ogre::String cameraName, Ogre::SceneNode * targetNode);
		/*!
		 * \brief Destructeur
		 */
		~CameraTarget();
		
		/*!
		 * \brief Initialise la position de la caméra
		 */
		void initCamera();	
		
		/*!
		 * \brief Met à jour la position de la caméra
		 * \param null NULL
		 */
		void updateCamera(void * null);     
        
        
        
	private:
	
        /*!
         * \brief Apply a before translation
         */
        void applyTranslateBeforce();
        /*!
         * \brief Apply a behind translation
         */
        void applyTranslateBehind();
        /*!
         * \brief Apply a left translation
         */
        void applyTranslateLeft();
        /*!
         * \brief Apply a right translation
         */
        void applyTranslateRight();
        /*!
         * \brief Apply an up translation
         */
        void applyTranslateUp();
        /*!
         * \brief Apply a down translation
         */
        void applyTranslateDown();
        /*!
         * \brief Apply a left rotation
         */
        void applyRotateLeft();
        /*!
         * \brief Apply a right rotation
         */
        void applyRotateRight();
        /*!
         * \brief Apply an up rotation
         */
        void applyRotateUp();
        /*!
         * \brief Apply a down rotation
         */
        void applyRotateDown();
        
        /*!
         * \brief Apply a translation with the mouse
         * \param mouseMove Movement of the mouse
         */
        void applyTranslateMouse(MouseMove_t &mouseMove);
        /*!
         * \brief Apply a rotation with the mouse
         * \param mouseMove Movement of the mouse
         */
        void applyRotateMouse(MouseMove_t &mouseMove);
        /*!
         * \brief Apply the movement of the wheel mouse
         * \param mouseMove Movement of the mouse
         */
        void applyWheelMouse(MouseMove_t &mouseMove);	
	
	
        /*!
         * \brief Effectue un zoom
         * \param zoomDist Zoom à effectuer
        */
        void zoom(Ogre::Real zoomDist);
        /*!
         * \brief Vérifie la rotation de la caméra et met à jour en conséquence
         * \return Vrai si on ne sort pas des limites
        */
		void checkRotation(Ogre::Degree * yaw, Ogre::Degree * pitch);
	
		/*!
		 * \brief Déplace la cible de la caméra
		 * \param vector Vecteur de déplacement
		 */
        void moveCameraTarget(Ogre::Vector3 vector);
        
        // Getter - Setter
        
	public:        
        /*!
         * \brief Définit la cible de la caméra
         * \param targetPosition Position de la ciblel
        */
		void setPositionTarget(Ogre::Vector3 targetPosition);
        /*!
         * \brief Retourne le pointeur sur l'attribut 'targetNode'
         * \return Retourne le noeud de la cible
        */
        Ogre::SceneNode * getTargetNode();
        
};

#endif //__CAMERA_TARGET_H__
