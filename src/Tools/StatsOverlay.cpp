
#include "Tools/StatsOverlay.h"

template<> StatsOverlay * ClassRootSingleton<StatsOverlay>::_instance = 0;


StatsOverlay::StatsOverlay() : ClassRootSingleton<StatsOverlay>()
{
  this->mGuiAvg   = CEGUI::WindowManager::getSingleton().getWindow("OPAverageFPS");
  this->mGuiCurr  = CEGUI::WindowManager::getSingleton().getWindow("OPCurrentFPS");
  this->mGuiBest  = CEGUI::WindowManager::getSingleton().getWindow("OPBestFPS");
  this->mGuiWorst = CEGUI::WindowManager::getSingleton().getWindow("OPWorstFPS");
  this->mGuiTris  = CEGUI::WindowManager::getSingleton().getWindow("OPTriCount");
  this->mGuiBatches   = CEGUI::WindowManager::getSingleton().getWindow("OPBatchesCount");
  
	//this->show(true);
}


StatsOverlay::~StatsOverlay()
{
	
}


void StatsOverlay::updateStats(void *)
{
  static CEGUI::String currFps = "Current FPS: ";
  static CEGUI::String avgFps = "Average FPS: ";
  static CEGUI::String bestFps = "Best FPS: ";
  static CEGUI::String worstFps = "Worst FPS: ";
  static CEGUI::String tris = "Triangle Count: ";
  static CEGUI::String batches = "Batch Count: ";

	// update stats when necessary
	try {
    const Ogre::RenderTarget::FrameStats& stats = ListenerWindow::getSingletonPtr()->getRenderWindow()->getStatistics();

    mGuiAvg->setText(avgFps + Ogre::StringConverter::toString(stats.avgFPS));
    mGuiCurr->setText(currFps + Ogre::StringConverter::toString(stats.lastFPS));
    mGuiBest->setText(bestFps + Ogre::StringConverter::toString(stats.bestFPS)
        + " " + Ogre::StringConverter::toString(stats.bestFrameTime)+" ms");
    mGuiWorst->setText(worstFps + Ogre::StringConverter::toString(stats.worstFPS)
        + " " + Ogre::StringConverter::toString(stats.worstFrameTime)+" ms");

    mGuiTris->setText(tris + Ogre::StringConverter::toString(stats.triangleCount));
    mGuiBatches->setText(batches + Ogre::StringConverter::toString(stats.batchCount));
    mAvgFrameTime = 1.0f/(stats.avgFPS + 1.0f);
    if (mAvgFrameTime > 0.1f) mAvgFrameTime = 0.1f;
    
	}	
	catch(...) { /* ignore */ }
}


void StatsOverlay::draw()
{
  this->mGuiAvg->show();
  this->mGuiCurr->show();
  this->mGuiBest->show();
  this->mGuiWorst->show();
  this->mGuiTris->show();
  this->mGuiBatches->show();
  
	ListenerFrame::getSingletonPtr()->signalFrameRendering.add(&StatsOverlay::updateStats, this);
}

void StatsOverlay::hide()
{
  this->mGuiAvg->hide();
  this->mGuiCurr->hide();
  this->mGuiBest->hide();
  this->mGuiWorst->hide();
  this->mGuiTris->hide();
  this->mGuiBatches->hide();
  
	ListenerFrame::getSingletonPtr()->signalFrameRendering.remove(&StatsOverlay::updateStats, this);
}


void StatsOverlay::show(bool show)
{
  if (show)
    this->draw();
  else
    this->hide();
}
