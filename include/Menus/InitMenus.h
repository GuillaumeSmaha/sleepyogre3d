/*
-----------------------------------------------------------------------------
This source file is part of SleepyOgre3D
-----------------------------------------------------------------------------
*/
/*!
 * \file InitMenus.h
 * \brief This file contains the declaration of the class InitMenus.
 */
#ifndef __INIT_MENUS_H__
#define __INIT_MENUS_H__

#include "Core/InitAbstract.h"
#include "Menus/GestMenus.h"
#include "Menus/MenuMain.h"

/*!
 * \class InitMenus
 * \brief Class to init the menus
 */
class InitMenus : public InitAbstract
{		
	public:
		/*!
		 * \brief Init the menus
		 */
		static void init();
		/*!
		 * \brief Destroy the menus
		 */
		static void destroy();
		
};

#endif //__INIT_MENUS_H__
