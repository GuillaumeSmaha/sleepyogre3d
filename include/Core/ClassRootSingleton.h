/*
-----------------------------------------------------------------------------
This source file is part of SleepyOgre3D
-----------------------------------------------------------------------------
*/
/*!
 * \file  ClassRootSingleton.h
 * \brief Ce fichier contient la déclaration de la classe ClassRootSingleton. 
*/
#ifndef __CLASS_ROOT_SINGLETON_H__
#define __CLASS_ROOT_SINGLETON_H__

#ifndef DOXYGEN_SKIP
#include <stddef.h>
#endif

#include "Core/ClassRoot.h"

/*!
 * \class ClassRootSingleton
 * \brief Permet de créer une classe singleton
 */
 
template <typename T>
class ClassRootSingleton : public ClassRoot
{
	private:
		/*!
		 * \brief Explicit private copy constructor. This is a forbidden operation.
		*/
		ClassRootSingleton(const ClassRootSingleton<T> &);
		/*!
		 * \brief Private operator= . This is a forbidden operation.
		*/
		ClassRootSingleton& operator=(const ClassRootSingleton<T> &);
    
	protected:
		/*!
		 * \brief Instance de ClassRootSingleton pour le singleton
		 */
    static T * _instance;

    public:
        /*!
		* \brief Constructor
		*/
    ClassRootSingleton() : ClassRoot()
    {			
			if(_instance == 0)
			{
				_instance = static_cast<T *>(this);
			}
    }
    /*!
     * \brief Destructor
     */
    ~ClassRootSingleton()
    {
      _instance = 0;
		}
        
		/*!
		 * \brief Créé le singleton
		 */		
		static void createSingleton()
		{
			if (_instance == 0)
			{
				new T();
			}
		}
		
		/*!
		 * \brief Retourne un pointeur sur l'instance du singleton
		 * \return Le pointeur sur le singleton
		 */
		static T * getSingletonPtr()
		{
			if (_instance == 0)
			{
				T::createSingleton();
			}
			return _instance;
		}
		/*!
		 * \brief Retourne une référence sur l'instance du singleton
		 * \return La référence sur le singleton
		 */		
		static T & getSingleton()
		{
			if (_instance == 0)
			{
				T::createSingleton();
			}
			return *_instance;
		}
		/*!
		 * \brief Retourne une référence sur l'instance du singleton
		 * \return La référence sur le singleton
		 */		
		static void destroySingleton()
		{
			if(_instance != 0)
			{
				delete _instance;
			}
		}
};


#endif // __CLASS_ROOT_SINGLETON_H__
