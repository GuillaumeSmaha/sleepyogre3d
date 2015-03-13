/*!
 * \file  Viewport.h
 * \brief Ce fichier contient la déclaration de la classe Viewport.
*/
#ifndef __VIEWPORT_H__
#define __VIEWPORT_H__

#ifndef DOXYGEN_SKIP
#include <Ogre.h>
#endif

#include "Core/Signal.h"
#include "Core/ClassRoot.h"
#include "Listener/ListenerWindow.h"
#include "Controls/controls.h"
#include "Camera/CameraAbstract.h"

class CameraAbstract;

/*!
* \class Viewport
* \brief Elle définit le viewport
*/
class Viewport : public ClassRoot
{
    public:
        /*!
        * \brief Viewport for Ogre
        */
        static int lastViewportId;
        
    private:
        /*!
        * \brief Viewport for Ogre
        */
        Ogre::Viewport * viewport;
        /*!
        * \brief Camera
        */
        CameraAbstract * camera;
        /*!
        * \brief Viewport Id
        */
        int id;
        

	public:
        /*!
        * \brief Constructor
        * \param camera The camera of the viewport
        */
		Viewport(CameraAbstract * camera); 
        /*!
        * \brief Destructor
        */
		~Viewport();
		
		
		/*!
		 * \brief Return if the position is in the current viewport
		 * \param position Position to test
		 * \return If the position is in the viewport
		 */
		bool isInViewport(Ogre::Vector3 position);     
		
		
		/*!
		 * \brief Update the dimension of the viewport
		 */
		void updateViewportSize();				
		/*!
		 * \brief Update the dimension of the viewport
		 * \param left Position at the left
		 * \param top Position at the top
		 * \param width Width of the viewport
		 * \param height Height of the viewport
		 */
		void updateViewportSize(Ogre::Real left, Ogre::Real top, Ogre::Real width, Ogre::Real height);
        
	// Getter - Setter	

	public:
        /*!
        * \brief [Getter] Return the id of viewport
        * \return Value of "id"
        */
        int getId();
        /*!
        * \brief [Getter] Return the viewport
        * \return Value of "viewport"
        */
        Ogre::Viewport * getViewport();
        /*!
        * \brief [Getter] Return the camera
        * \return Value of "camera"
        */
        CameraAbstract * getCamera();
        /*!
        * \brief [Getter] Return the camera
        * \return Value of "camera"
        */
        void setCamera(CameraAbstract * camera);
};

#endif // __VIEWPORT_H__

