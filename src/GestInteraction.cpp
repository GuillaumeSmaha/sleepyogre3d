#include "GestInteraction.h"

template<> GestInteraction * ClassRootSingleton<GestInteraction>::_instance = 0;


GestInteraction::GestInteraction() : ClassRootSingleton<GestInteraction>()
{
  this->appLaunched = false;
  this->pauseState = false;
  this->moveAllCamera = false;
  
  PlayerControls::getSingletonPtr()->signalKeyPressed.add(&GestInteraction::onKeyPressed, this);
  PlayerControls::getSingletonPtr()->signalKeyReleased.add(&GestInteraction::onKeyReleased, this);
  PlayerControls::getSingletonPtr()->signalMouseMoved.add(&GestInteraction::onMouseMoved, this);
  PlayerControls::getSingletonPtr()->signalKeyPressedInPause.add(&GestInteraction::onKeyPressed, this);
  PlayerControls::getSingletonPtr()->signalMouseMovedInPause.add(&GestInteraction::onMenuMouseMoved, this);
}


GestInteraction::~GestInteraction()
{
	
}

void GestInteraction::initScene()
{
	if(!this->appLaunched)
	{		
		this->appLaunched = true;
		
		InitScene::init();
	}
}


void GestInteraction::quitApplication()
{
	ListenerFrame::getSingletonPtr()->shutdown();
}

void GestInteraction::switchPauseState()
{
	if(this->pauseState)
	{
		this->setPauseState(false);
	}
	else
	{
		this->setPauseState(true);
	}
}


void GestInteraction::injectMouseMove(float delta_x, float delta_y)
{
	//permet de déplacer également la souris de Bullet
	MouseFunction::getSingletonPtr()->injectMouseMove(delta_x, delta_y);
	
	//permet de déplacer également la souris du menus CEGUI
	GestMenus::getSingletonPtr()->injectMouseMove(delta_x, delta_y);
}



void GestInteraction::onKeyPressed(Controls::Controls key)
{
  switch(key)
  {            
    case Controls::QUIT :
      this->quitApplication();
      break;

    default:
      break;
  }
}


void GestInteraction::onKeyReleased(Controls::Controls key)
{
  switch(key)
  {     
      default:
          break;
  }
}


void GestInteraction::onMouseMoved(MouseMove_t &mouseMove)
{	
  switch(mouseMove.controlMouseId)
  {     
    case Controls::NONE :
    {
      this->injectMouseMove(mouseMove.vector[0], mouseMove.vector[1]);
      break;
    }		
    
    default:
        break;
  }
}


void GestInteraction::onMenuMouseMoved(MouseMove_t &mouseMove)
{	
    switch(mouseMove.controlMouseId)
    {     
      case Controls::NONE :
      {
        GestMenus::getSingletonPtr()->injectMouseMove(mouseMove.vector[0], mouseMove.vector[1]);
        break;
      }		
			
      default:
          break;
    }
}


Ogre::Vector3 GestInteraction::getPosMouse()
{
	return MouseFunction::getSingletonPtr()->getPosMouse();
}


bool GestInteraction::getAppLauched()
{
	return this->appLaunched;
}  


void GestInteraction::setPauseState(bool pauseState)
{
	this->pauseState = pauseState;
	if(pauseState)
		PlayerControls::getSingletonPtr()->suspendListening();
	else
		PlayerControls::getSingletonPtr()->continueListening();
}

bool GestInteraction::getPauseState()
{
	return this->pauseState;
}  

bool GestInteraction::getMoveAllCamera()
{
	return this->moveAllCamera;
}  
