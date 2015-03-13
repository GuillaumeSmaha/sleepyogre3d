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
