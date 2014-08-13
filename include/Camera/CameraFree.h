/*
-----------------------------------------------------------------------------
This source file is part of SleepyOgre3D
-----------------------------------------------------------------------------
*/
/*!
 * \file  CameraFree.h
 * \brief Ce fichier contient la déclaration de la classe CameraFree. C'est la classe gérant une caméra fixe.
 */
#ifndef __CAMERA_FREE_H__
#define __CAMERA_FREE_H__

#ifndef DOXYGEN_SKIP
#include <Ogre.h>
#endif

#include "Camera/CameraAbstract.h"


/*!
 * \class CameraFree
 * \brief Classe permettant de gérer une caméra libre.
 */
class CameraFree : public CameraAbstract
{        
	public:
		/*!
		 * \brief Constructeur
		 * \param cameraType Type nouvelle caméra
		 * \param cameraName Nom de la nouvelle caméra
		 */
		CameraFree(Ogre::String cameraName);
		/*!
		 * \brief Destructeur
		 */
		~CameraFree();
		
		/*!
		 * \brief Initialise la position de la caméra
		 */
		void initCamera();	
		
		/*!
		 * \brief Met à jour la position de la caméra
		 * \param null 0
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
};

#endif //__CAMERA_FREE_H__
