/*!
 * \file  GestCamera.h
 * \brief Ce fichier contient la déclaration de la classe GestCamera. C'est la classe gérant les caméras.
 */
#ifndef __GEST_CAMERA_H__
#define __GEST_CAMERA_H__

#ifndef DOXYGEN_SKIP
#include <vector>
#include <Ogre.h>
#endif

#include "Core/ClassRootSingleton.h"
#include "Camera/CameraAbstract.h"
#include "Camera/CameraFree.h"
#include "Camera/CameraOrbital.h"
#include "Camera/CameraOrbitalTarget.h"
#include "Camera/CameraTarget.h"

/*!
 * \class GestCamera
 * \brief Classe permettant de gérer les viewports.
 */
class GestCamera : public ClassRootSingleton<GestCamera>
{
	private:
        /*!
		 * \brief Vecteur des caméras
		 */
        std::vector<CameraAbstract *> listCameras;
		
		
	public:
		/*!
		 * \brief Constructor
		 */
		GestCamera();
		/*!
		 * \brief Destructor
		 */
		~GestCamera();

		
	public:
        /*!
		 * \brief Rajoute une caméra à la liste
		 * \param camera Caméra à rajouter à la liste
		 */
        void addCamera(CameraAbstract * camera);
        /*!
		 * \brief Rajoute une caméra à la liste
		 * \param cameraType Type de caméra à rajouter à la liste
		 * \param cameraName Nom de la caméra à rajouter
		 * \param param1 Paramètre 1 de la caméra créer
		 * \return Un pointeur sur la caméra créée
		 */
        CameraAbstract * addCamera(CameraAbstract::CameraType cameraType, Ogre::String cameraName, void * param1 = 0);
        /*!
		 * \brief Supprime la caméra de la liste
		 * \param cam Camera à supprimer
		 * \return Si la suppression a réussit
		 */
        bool removeCamera(CameraAbstract * cam);
        /*!
		 * \brief Supprime la caméra de la liste
		 * \param id ID de la caméra à récupérer
		 * \return Si la suppression a réussit
		 */
        bool removeCamera(unsigned int id);
        /*!
		 * \brief Supprime la caméra de la liste
		 * \param id ID de la caméra à récupérer
		 * \return Si la suppression a réussit
		 */
        bool removeCamera(int id)
        {
			return this->removeCamera(static_cast<unsigned int>(id));
		}
        /*!
		 * \brief Récupère l'instance d'une caméra (nonsafe)
		 * \param id ID de la caméra à récupérer
		 * \return Instance de la caméra
		 */
        CameraAbstract * getCamera(unsigned int id);

        /**
         * \brief recupere la dernière camera placé
        */
        CameraAbstract * getCurrentCamera()
        {
            return (listCameras.back());
        }
};

#endif //__GEST_CAMERA_H__
