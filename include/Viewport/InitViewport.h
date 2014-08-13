/*
-----------------------------------------------------------------------------
This source file is part of SleepyOgre3D
-----------------------------------------------------------------------------
*/
/*!
 * \file InitViewport.h
 * \brief This file contains the declaration of the class InitViewport.
 */
#ifndef __INIT_VIEWPORT_H__
#define __INIT_VIEWPORT_H__

#include "Core/InitAbstract.h"
#include "Viewport/GestViewport.h"

/*!
 * \class InitViewport
 * \brief Class to init the listener
 */
class InitViewport : public InitAbstract
{		
	public:
		/*!
		 * \brief Init the listener
		 */
		static void init();		
		/*!
		 * \brief Destroy the listener
		 */
		static void destroy();
		
};

#endif //__INIT_VIEWPORT_H__
