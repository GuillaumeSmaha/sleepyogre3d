/*
-----------------------------------------------------------------------------
This source file is part of SleepyOgre3D
-----------------------------------------------------------------------------
*/
/*!
 * \file InitControls.h
 * \brief This file contains the declaration of the class InitControls.
 */
#ifndef __INIT_CONTROLS_H__
#define __INIT_CONTROLS_H__

#include "Core/InitAbstract.h"
#include "Controls/MouseFunction.h"
#include "Controls/PlayerControls.h"

/*!
 * \class InitControls
 * \brief Class to init the listener
 */
class InitControls : public InitAbstract
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

#endif //__INIT_CONTROLS_H__
