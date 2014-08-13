/*
-----------------------------------------------------------------------------
This source file is part of SleepyOgre3D
-----------------------------------------------------------------------------
*/
/*!
 * \file InitCamera.h
 * \brief This file contains the declaration of the class InitCamera.
 */
#ifndef __INIT_CAMERA_H__
#define __INIT_CAMERA_H__

#include "Core/InitAbstract.h"
#include "Viewport/GestViewport.h"
#include "Camera/GestCamera.h"

/*!
 * \class InitCamera
 * \brief Class to init the camera
 */
class InitCamera : public InitAbstract
{
	public:
		/*!
		 * \brief Init the camera
		 */
		static void init();		
		/*!
		 * \brief Destroy the camera
		 */
		static void destroy();
		
};

#endif //__INIT_CAMERA_H__
