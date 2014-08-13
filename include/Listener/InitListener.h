/*
-----------------------------------------------------------------------------
This source file is part of SleepyOgre3D
-----------------------------------------------------------------------------
*/
/*!
 * \file InitListener.h
 * \brief This file contains the declaration of the class InitListener.
 */
#ifndef __INIT_LISTENER_H__
#define __INIT_LISTENER_H__

#include "config.h"
#include "Core/InitAbstract.h"
#include "Scene/GestSceneManager.h"
#include "Listener/ListenerWindow.h"
#include "Listener/ListenerInputManager.h"
#include "Listener/ListenerKeyboard.h"
#include "Listener/ListenerMouse.h"
#include "Listener/ListenerFrame.h"

/*!
 * \class InitListener
 * \brief Class to init the listener
 */
class InitListener : public InitAbstract
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

#endif //__INIT_LISTENER_H__
