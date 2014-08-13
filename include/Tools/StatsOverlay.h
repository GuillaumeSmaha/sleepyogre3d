/*
-----------------------------------------------------------------------------
This source file is part of SleepyOgre3D

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
#include <CEGUI/CEGUIPropertyHelper.h>
#include <CEGUI/CEGUIWindowManager.h>
#include <CEGUI/CEGUIWindow.h>
#include <CEGUI/CEGUIRenderer.h>
#include <OIS/OIS.h>
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
      CEGUI::Window* mGuiAvg;
      CEGUI::Window* mGuiCurr;
      CEGUI::Window* mGuiBest;
      CEGUI::Window* mGuiWorst;
      CEGUI::Window* mGuiTris;
      CEGUI::Window* mGuiBatches;
      float mAvgFrameTime;
    		
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
		void draw();
        
		/*!
		* \brief Draw the overlay
		*/
		void hide();
        
		/*!
		* \brief Define if the overlay is drawing
		* \param show If the overlay is drawing
		*/
		void show(bool show);
};

#endif //__STATS_OVERLAY_H__


