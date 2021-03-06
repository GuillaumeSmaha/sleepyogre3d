/*!
 * \file  CameraOrbital.h
 * \brief Ce fichier contient la déclaration de la classe CameraOrbital. C'est la classe gérant une caméra fixe.
 */
#ifndef __CAMERA_ORBITAL_H__
#define __CAMERA_ORBITAL_H__

#ifndef DOXYGEN_SKIP
#include <Ogre.h>
#endif

#include "Camera/CameraAbstract.h"


/*!
 * \class CameraOrbital
 * \brief Classe permettant de gérer une caméra orbitale autour d'un point.
 */
class CameraOrbital : public CameraAbstract
{

    private:
		Ogre::Entity * targetEntity;
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
		 * \param position Position de la cible de la caméra
		 */
		CameraOrbital(Ogre::String cameraName, Ogre::Vector3 position = Ogre::Vector3(0.0, 0.0, 0.0));
		/*!
		 * \brief Constructeur
		 * \param cameraType Type nouvelle caméra
		 * \param cameraName Nom de la nouvelle caméra
		 * \param targetNode Cible de la caméra
		 */
		CameraOrbital(Ogre::String cameraName, Ogre::SceneNode * targetNode);
		/*!
		 * \brief Destructeur
		 */
		~CameraOrbital();
		
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
        void moveCameraOrbital(Ogre::Vector3 vector);
        
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

#endif //__CAMERA_ORBITAL_H__
