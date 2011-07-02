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
 * \file StatsOverlay.h
 * \brief This file contains the declaration of the class StatsOverlay.
 */
#ifndef __STATS_OVERLAY_H__
#define __STATS_OVERLAY_H__

#ifndef DOXYGEN_SKIP
#include <Ogre.h>
#endif

#include "Core/Signal.h"
#include "Core/ClassRootSingleton.h"
#include "Listener/ListenerWindow.h"
#include "Listener/ListenerFrame.h"

/*!
 * \class StatsOverlay
 * \brief Class to draw the stats
 */
class StatsOverlay : public ClassRootSingleton<StatsOverlay>
{	
    private:
		/*!
		* \brief GUI to draw the stats
		*/
		Ogre::Overlay * debugOverlay;
		/*!
		* \brief Text for the debug
		*/
		Ogre::String debugText;
    		
	public:
		/*!
		 * \brief Constructor
		 */
		StatsOverlay();
		/*!
		 * \brief Destructor
		 */
		~StatsOverlay();
	
	public:
        /*!
         * \brief Update the stats
        */
        void updateStats(void *);
        
		/*!
		* \brief Draw the overlay
		*/
		void drawDebugOverlay();
        
		/*!
		* \brief Draw the overlay
		*/
		void hideDebugOverlay();
        
		/*!
		* \brief Define if the overlay is drawing
		* \param show If the overlay is drawing
		*/
		void showDebugOverlay(bool show);
		
		/*!
		* \brief [Getter] Returns a pointer on debugOverlay
		* \return Get the value of debugOverlay
		*/		
		Ogre::Overlay * getDebugOverlay();
};

#endif //__STATS_OVERLAY_H__


