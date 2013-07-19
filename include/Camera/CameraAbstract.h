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
 * \file  CameraAbstract.h
 * \brief Ce fichier contient la déclaration de la classe CameraAbstract. C'est la classe une classe abstraite qui permet d'utiliser différents types de caméras fixes.
 */
#ifndef __CAMERA_ABSTRACT_H__
#define __CAMERA_ABSTRACT_H__

#ifndef DOXYGEN_SKIP
#include <set>
#include <Ogre.h>
#endif

#include "Core/ClassRoot.h"
#include "Scene/nodeName.h"
#include "Scene/GestSceneManager.h"
#include "Listener/ListenerFrame.h"
#include "Viewport/Viewport.h"
#include "Controls/mouseMove.h"
#include "Controls/controls.h"
#include "Controls/PlayerControls.h"
#include "GestInteraction.h"

class Viewport;

/*!
 * \class CameraAbstract
 * \brief Classe abstraite entre le programme principale et la caméra effectivement utilisé. Elle ne peut donc pas être instancié directement
 */
class CameraAbstract : public ClassRoot
{
	public:
		/// Définit les différents types de caméra
		enum CameraType
		{
			/// Caméra Null
			CAMERA_0 = 0,
			/// Caméra libre
			CAMERA_FREE,
			/// Caméra orbitale
			CAMERA_ORBITAL,
			/// Caméra suivant un noeud
			CAMERA_TARGET,
			/// Caméra orbitale suivant un noeud
			CAMERA_ORBITAL_TARGET
		};
		
		/// Définit le nombre de type de caméra
		static const int CameraTypeCount = 2;
		
	private:
		/*!
		 * \brief List of the viewport
		 */
        std::set<Viewport *> lstViewport;	
		
	protected:
		/*!
		 * \brief Type de la caméra
		 */
		CameraAbstract::CameraType cameraType;
		/*!
		 * \brief Camera instanciée
		 */
		Ogre::Camera * camera;
		/*!
		 * \brief Nom de la caméra
		 */
		Ogre::String cameraName;
		/*!
		 * \brief Noeud contenant la caméra
		 */
        Ogre::SceneNode * nodeCamera;
		
		/*!
		 * \brief A step for a translation
		 */
		Ogre::Real translateStep;
		/*!
		 * \brief A step for a rotation
		 */
		Ogre::Real rotateStep;
	
	public:		 
		/*!
		 * \brief Constructeur
		 * \param cameraType Type nouvelle caméra
		 * \param cameraName Nom de la nouvelle caméra
		 */
		CameraAbstract(Ogre::String cameraName);
		/*!
		 * \brief Destructeur virtuel
		 */
		 virtual ~CameraAbstract();
		 
		/*!
		 * \brief Initialise la position de la caméra\n
		 * Méthode virtuelle pure à réimplémenter.
		 */
		virtual void initCamera() = 0;
		/*!
		 * \brief Met à jour la position de la caméra\n
		 * Méthode virtuelle pure à réimplémenter.
		 */
		virtual void updateCamera(void * null) = 0;
		
		
		/*!
		 * \brief Insert a viewport on the list
		 * \param viewport Pointer on the viewport
		 * \return If the adding is a success
		 */
		bool insertViewport(Viewport * viewport);
		/*!
		 * \brief Remove a viewport on the list
		 * \param viewport Pointer on the viewport
		 * \return If the viewport exist
		 */
		bool removeViewport(Viewport * viewport);
		/*!
		 * \brief Return if the position is in the current camera
		 * \param position Position to test
		 * \return If the position is in the camera
		 */
		bool isInViewport(Ogre::Vector3 position);
		
		

		/*!
		 * \brief Direction de la caméra
		 * 	\param x Coordonnée en X
		 * 	\param y Coordonnée en Y
		 * 	\param z Coordonnée en Z
		 */
        virtual void setDirection( Ogre::Real x, Ogre::Real y, Ogre::Real z );
		/*!
		 * \brief Direction de la caméra
		 * 	\param direction Direction
		 */
        virtual void setDirection( Ogre::Vector3 direction );
		/*!
		 * \brief Direction de la caméra
		 * 	\param nodeDirection Direction
		 */
        virtual void setDirection( Ogre::SceneNode * nodeDirection );
		/*!
		 * \brief Position de la caméra
		 * 	\param x Coordonnée en X
		 * 	\param y Coordonnée en Y
		 * 	\param z Coordonnée en Z
		 */
        virtual void setPosition( Ogre::Real x, Ogre::Real y, Ogre::Real z );
		/*!
		 * \brief Position de la caméra
		 * 	\param position Position
		 */
        virtual void setPosition( Ogre::Vector3 position );
		/*!
		 * \brief Déplace de la caméra
		 * 	\param x Coordonnée en X
		 * 	\param y Coordonnée en Y
		 * 	\param z Coordonnée en Z
		 */
        virtual void move( Ogre::Real x, Ogre::Real y, Ogre::Real z );
		/*!
		 * \brief Déplace de la caméra
		 * 	\param position Vecteur de déplacement
		 */
        virtual void move( Ogre::Vector3 position );
		/*!
		 * \brief Déplace de la caméra de manière relative
		 * 	\param x Coordonnée en X
		 * 	\param y Coordonnée en Y
		 * 	\param z Coordonnée en Z
		 */
        virtual void moveRelative( Ogre::Real x, Ogre::Real y, Ogre::Real z );
		/*!
		 * \brief Déplace de la caméra de manière relative
		 * 	\param position Vecteur de déplacement
		 */
        virtual void moveRelative( Ogre::Vector3 position );
             
             
             
	protected:
        /*!
         * \brief Apply a before translation
         */
        virtual void applyTranslateBeforce();
        /*!
         * \brief Apply a behind translation
         */
        virtual void applyTranslateBehind();
        /*!
         * \brief Apply a left translation
         */
        virtual void applyTranslateLeft();
        /*!
         * \brief Apply a right translation
         */
        virtual void applyTranslateRight();
        /*!
         * \brief Apply an up translation
         */
        virtual void applyTranslateUp();
        /*!
         * \brief Apply a down translation
         */
        virtual void applyTranslateDown();
        /*!
         * \brief Apply a left rotation
         */
        virtual void applyRotateLeft();
        /*!
         * \brief Apply a right rotation
         */
        virtual void applyRotateRight();
        /*!
         * \brief Apply an up rotation
         */
        virtual void applyRotateUp();
        /*!
         * \brief Apply a down rotation
         */
        virtual void applyRotateDown();
        
        /*!
         * \brief Apply a translation with the mouse
         * \param mouseMove Movement of the mouse
         */
        virtual void applyTranslateMouse(MouseMove_t &mouseMove);
        /*!
         * \brief Apply a rotation with the mouse
         * \param mouseMove Movement of the mouse
         */
        virtual void applyRotateMouse(MouseMove_t &mouseMove);
        /*!
         * \brief Apply the movement of the wheel mouse
         * \param mouseMove Movement of the mouse
         */
        virtual void applyWheelMouse(MouseMove_t &mouseMove);
        
        /*!
         * \brief Permet de déplacer la caméra lors d'un mouvement de souris
		 * \param mouseMove Structure de déplacement de la souris
        */
        virtual void onMouseMoved(MouseMove_t &mouseMove);
        /*!
         * \brief Permet de déplacer la caméra selon les touches utilisés
         * \param key Touche du clavier (Controls::Controls)
        */
        virtual void onKeyStillPressed(Controls::Controls key);
        /*!
         * \brief Permet de déplacer la caméra selon les touches utilisés
         * \param key Touche du clavier (Controls::Controls)
        */
        virtual void onKeyPressed(Controls::Controls key);
        /*!
         * \brief Permet de déplacer la caméra selon les touches utilisés
         * \param key Touche du clavier (Controls::Controls)
        */
        virtual void onKeyReleased(Controls::Controls key);
        
	
	public:
		//Getter/Setter

		/*!
		 * \brief [Getter] Pointeur sur la caméra
		 * \return Le nom de la caméra
		 */
		Ogre::Camera * getCamera();		
		/*!
		 * \brief [Getter] Nom de la caméra
		 * \return Le nom de la caméra
		 */
		Ogre::String getCameraName();
		
		/*!
		 * \brief [Getter] Step of a translation
		 * \return Value of "translateStep"
		 */
		Ogre::Real getTranslateStep();
		/*!
		 * \brief [Setter] Define the step of a translation
		 * \param translateStep New value of "translateStep"
		 */
		void setTranslateStep(Ogre::Real translateStep);
		
		/*!
		 * \brief [Getter] Step of a rotation
		 * \return Value of "rotateStep"
		 */
		Ogre::Real getRotateStep();
		/*!
		 * \brief [Setter] Define the step of a rotation
		 * \param rotateStep New value of "rotateStep"
		 */
		void setRotateStep(Ogre::Real rotateStep);
};

#endif // __CAMERA_ABSTRACT_H__ 
