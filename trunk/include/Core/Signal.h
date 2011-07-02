/*
-----------------------------------------------------------------------------
This source file is part of SleepyOgre3D
 
Copyright (c) 2011 Guillaume Smaha

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
of the Software, and to permit persons to whom the Software is furnished to do
so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
-----------------------------------------------------------------------------
*/
/*!
 * \file  Signal.h
 * \brief Ce fichier contient la déclaration de la classe Signal.
*/
#ifndef __SIGNAL_H__
#define __SIGNAL_H__

#ifndef DOXYGEN_SKIP
#include <vector>
#endif

#include "Core/ClassRoot.h"


/*!
 * \class Signal
 * \brief Permet la communication entre 2 classes facilement et proprement
 */
template <typename Retour>
class Signal : public ClassRoot
{
    private:
        /*!
         * \brief Contient la liste des listeners Class
         */
		std::vector<ClassRoot *> listenersClass;
        /*!
         * \brief Contient la liste des listeners Method
         */
		std::vector<void (ClassRoot::*)(Retour)> listenersMethod;
		
		
    public:
        /*!
		* \brief Constructor
		*/
        Signal()
        {

        }
        /*!
         * \brief Destructor
         */
        virtual ~Signal()
        {

        }

        /*!
		* \brief Enregistre la fonction passée en paramètre comme listener
		* \param function La fonction listener
		* \param ptrClass La class contenant le listener
		*/
        template<class myclass>
        void add(void (myclass::* function)(Retour), myclass * ptrClass)
        {
			this->listenersClass.push_back(ptrClass);
			this->listenersMethod.push_back((void(ClassRoot::*)(Retour))function);
        }

        /*!
		* \brief Appelle les différents listeners sans leur passer de paramètre
		*/
        void dispatch(void)
        {
            this->dispatch(NULL);
        }

        /*!
		* \brief Appelle les différents listeners en leur passant un paramètre
		* \param argument Paramètre passé aux listeners
		*/
        void dispatch(Retour argument)
        {
			ClassRoot * ptrClass;
            void (ClassRoot::* func)(Retour);
            for ( size_t i = 0, size = this->listenersClass.size(); i < size; ++i )
            {
				ptrClass = this->listenersClass[i];
                func = this->listenersMethod[i];
                (ptrClass->*func)(argument);
            }
        }

        /*!
		* \brief Retire des listeners la fonction passée en paramètre
		* \param function La fonction listener
		* \param ptrClass La class contenant le listener
		*/
        template<class myclass>
        void remove(void (myclass::* function)(Retour), myclass * ptrClass)
        {
            void (ClassRoot::* func)(Retour);
            func = (void(ClassRoot::*)(Retour))function;
			ClassRoot * ptr_class = ptrClass;

            for ( size_t i = 0; i < this->listenersClass.size(); ++i )
            {
                if(this->listenersClass[i] == ptr_class && this->listenersMethod[i] == func)
                {
                    this->listenersClass.erase(this->listenersClass.begin()+i);
                    this->listenersMethod.erase(this->listenersMethod.begin()+i);
                    break;
                }
            }
        }
};

#endif // __SIGNAL_H__






