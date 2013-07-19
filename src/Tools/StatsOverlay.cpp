#include "Tools/StatsOverlay.h"

template<> StatsOverlay * ClassRootSingleton<StatsOverlay>::_instance = 0;


StatsOverlay::StatsOverlay() : ClassRootSingleton<StatsOverlay>()
{
	this->debugOverlay = Ogre::OverlayManager::getSingleton().getByName("Core/DebugOverlay");
	this->showDebugOverlay(true);
	ListenerFrame::getSingletonPtr()->signalFrameRendering.add(&StatsOverlay::updateStats, this);
}


StatsOverlay::~StatsOverlay()
{
	
}


void StatsOverlay::updateStats(void *)
{
	static Ogre::String currFps = "Current FPS: ";
	static Ogre::String avgFps = "Average FPS: ";
	static Ogre::String bestFps = "Best FPS: ";
	static Ogre::String worstFps = "Worst FPS: ";
	static Ogre::String tris = "Triangle Count: ";
	static Ogre::String batches = "Batch Count: ";

	// update stats when necessary
	try {
		Ogre::OverlayElement * guiAvg = Ogre::OverlayManager::getSingleton().getOverlayElement("Core/AverageFps");
		Ogre::OverlayElement * guiCurr = Ogre::OverlayManager::getSingleton().getOverlayElement("Core/CurrFps");
		Ogre::OverlayElement * guiBest = Ogre::OverlayManager::getSingleton().getOverlayElement("Core/BestFps");
		Ogre::OverlayElement * guiWorst = Ogre::OverlayManager::getSingleton().getOverlayElement("Core/WorstFps");

		const Ogre::RenderTarget::FrameStats& stats = ListenerWindow::getSingletonPtr()->getRenderWindow()->getStatistics();
		guiAvg->setCaption(avgFps + Ogre::StringConverter::toString(stats.avgFPS));
		guiCurr->setCaption(currFps + Ogre::StringConverter::toString(stats.lastFPS));
		guiBest->setCaption(bestFps + Ogre::StringConverter::toString(stats.bestFPS)
			+" "+Ogre::StringConverter::toString(stats.bestFrameTime)+" ms");
		guiWorst->setCaption(worstFps + Ogre::StringConverter::toString(stats.worstFPS)
			+" "+Ogre::StringConverter::toString(stats.worstFrameTime)+" ms");

		Ogre::OverlayElement * guiTris = Ogre::OverlayManager::getSingleton().getOverlayElement("Core/NumTris");
		guiTris->setCaption(tris + Ogre::StringConverter::toString(stats.triangleCount));

		Ogre::OverlayElement * guiBatches = Ogre::OverlayManager::getSingleton().getOverlayElement("Core/NumBatches");
		guiBatches->setCaption(batches + Ogre::StringConverter::toString(stats.batchCount));

		Ogre::OverlayElement * guiDbg = Ogre::OverlayManager::getSingleton().getOverlayElement("Core/DebugText");
		guiDbg->setCaption(debugText);
	}	
	catch(...) { /* ignore */ }
}


void StatsOverlay::drawDebugOverlay()
{
	if (debugOverlay != 0)
	{
		this->debugOverlay->show();
	}
}


void StatsOverlay::hideDebugOverlay()
{
	if (debugOverlay != 0)
	{
		this->debugOverlay->hide();
	}
}


void StatsOverlay::showDebugOverlay(bool show)
{
	if (debugOverlay != 0)
	{
		if (show)
			this->debugOverlay->show();
		else
			this->debugOverlay->hide();
	}
}


Ogre::Overlay * StatsOverlay::getDebugOverlay()
{
	return this->debugOverlay;
}
