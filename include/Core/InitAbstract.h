/*
-----------------------------------------------------------------------------
This source file is part of SleepyOgre3D
-----------------------------------------------------------------------------
*/
/*!
 * \file InitAbstract.h
 * \brief This file contains the declaration of the class InitAbstract.
 */
#ifndef __INIT_ABSTRACT_H__
#define __INIT_ABSTRACT_H__

/*!
 * \class InitAbstract
 * \brief Class to init a module
 */
class InitAbstract
{
	private:
		/*!
		 * \brief Constructor
		 */
		InitAbstract();
		/*!
		 * \brief Destructor
		 */
		~InitAbstract();
		
	public:
		/*!
		 * \brief Init the module
		 */
		static void init(){};
		/*!
		 * \brief Destroy the module
		 */
		static void destroy(){};
		
};

#endif //__INIT_ABSTRACT_H__
