#include "Controls/PlayerControls.h"

template<> PlayerControls * ClassRootSingleton<PlayerControls>::_instance = 0;

PlayerControls::PlayerControls() : ClassRootSingleton<PlayerControls>()
{ 
  this->setDefaultKeys();

  ListenerKeyboard::getSingletonPtr()->signalKeyStillPressed.add(&PlayerControls::keyboardStillPressed, this);
  ListenerKeyboard::getSingletonPtr()->signalKeyPressed.add(&PlayerControls::keyboardPressed, this);
  ListenerKeyboard::getSingletonPtr()->signalKeyReleased.add(&PlayerControls::keyboardReleased, this);
  ListenerMouse::getSingletonPtr()->signalMouseMoved.add(&PlayerControls::mouseMoved, this);
  ListenerMouse::getSingletonPtr()->signalMousePressed.add(&PlayerControls::mousePressed, this);
  ListenerMouse::getSingletonPtr()->signalMouseReleased.add(&PlayerControls::mouseReleased, this);
}

PlayerControls::~PlayerControls()
{
  ListenerKeyboard::getSingletonPtr()->signalKeyStillPressed.remove(&PlayerControls::keyboardStillPressed, this);
  ListenerKeyboard::getSingletonPtr()->signalKeyPressed.remove(&PlayerControls::keyboardPressed, this);
  ListenerKeyboard::getSingletonPtr()->signalKeyReleased.remove(&PlayerControls::keyboardReleased, this);
  ListenerMouse::getSingletonPtr()->signalMouseMoved.remove(&PlayerControls::mouseMoved, this);
  ListenerMouse::getSingletonPtr()->signalMousePressed.remove(&PlayerControls::mousePressed, this);
  ListenerMouse::getSingletonPtr()->signalMouseReleased.remove(&PlayerControls::mouseReleased, this);
  
  ListenerMouse::getSingletonPtr()->signalMouseMoved.remove(&PlayerControls::mouseMovedInPause, this);
  ListenerMouse::getSingletonPtr()->signalMousePressed.remove(&PlayerControls::mousePressedInPause, this);
  ListenerKeyboard::getSingletonPtr()->signalKeyPressed.remove(&PlayerControls::keyboardPressedInPause, this);
  
  this->resetControls();
}

void PlayerControls::setDefaultKeys()
{
  this->resetControls();
    
	this->setMouseControl(Controls::CAMERA_TRANSLATE_MOUSE, OIS::MB_Middle);
	this->setMouseControl(Controls::CAMERA_ROTATE_MOUSE, OIS::MB_Right);
	
	this->setKeyControl(Controls::CAMERA_TRANSLATE_BEFORE, OIS::KC_UP);
	this->setKeyControl(Controls::CAMERA_TRANSLATE_BEHIND, OIS::KC_DOWN);
	this->setKeyControl(Controls::CAMERA_TRANSLATE_LEFT, OIS::KC_LEFT);
	this->setKeyControl(Controls::CAMERA_TRANSLATE_RIGHT, OIS::KC_RIGHT);	
	this->setKeyControl(Controls::CAMERA_TRANSLATE_UP, OIS::KC_P);
	this->setKeyControl(Controls::CAMERA_TRANSLATE_DOWN, OIS::KC_M);
	
	this->setKeyControl(Controls::CAMERA_ROTATE_LEFT, OIS::KC_Q);
	this->setKeyControl(Controls::CAMERA_ROTATE_RIGHT, OIS::KC_D);
	this->setKeyControl(Controls::CAMERA_ROTATE_UP, OIS::KC_Z);
	this->setKeyControl(Controls::CAMERA_ROTATE_DOWN, OIS::KC_S);
	
	
	this->setKeyControl(Controls::ADD_CAMERA, OIS::KC_Y);
   
	this->setKeyControl(Controls::QUIT, OIS::KC_F10);
	
	this->setKeyControl(Controls::OPEN_MENU, OIS::KC_ESCAPE);
	
	this->setMouseMovedActif(true);
}

void PlayerControls::resetControls(void)
{
	this->setMouseMovedActif(false);
	
	this->listKeyControl.resize(PlayerControls::maxOISKeyControl);
	for(unsigned int i = 0 ; i < this->listKeyControl.size() ; i++)
		this->listKeyControl[i].clear();
		
	this->listMouseControl.resize(PlayerControls::maxOISMouseControl);
	for(unsigned int i = 0 ; i < this->listMouseControl.size() ; i++)
		this->listMouseControl[i].clear();
}

void PlayerControls::setKeyControl(const Controls::Controls keyControl, const OIS::KeyCode key, bool removeDuplicate)
{
	if(key <= PlayerControls::maxOISKeyControl)
	{
		if(removeDuplicate)
		{			
			for(unsigned int i = 0 ; i < this->listMouseControl.size() ; i++)
			{
				std::set<Controls::Controls>::iterator it = this->listMouseControl[i].find(keyControl);
				if(it != this->listMouseControl[i].end())
					this->listMouseControl[i].erase(it);
			}
			
			for(unsigned int i = 0 ; i < this->listKeyControl.size() ; i++)
			{
				std::set<Controls::Controls>::iterator it = this->listKeyControl[i].find(keyControl);
				if(it != this->listKeyControl[i].end())
					this->listKeyControl[i].erase(it);
			}
		}
		
		std::set<Controls::Controls>::iterator it = this->listKeyControl[key].find(keyControl);
		if(it == this->listKeyControl[key].end())
			this->listKeyControl[key].insert(keyControl);
	}
}

void PlayerControls::setMouseControl(const Controls::Controls keyControl, const OIS::MouseButtonID mouseId, bool removeDuplicate)
{
	if(mouseId <= PlayerControls::maxOISMouseControl)
	{
		if(removeDuplicate)
		{			
			for(unsigned int i = 0 ; i < this->listMouseControl.size() ; i++)
			{
				std::set<Controls::Controls>::iterator it = this->listMouseControl[i].find(keyControl);
				if(it != this->listMouseControl[i].end())
					this->listMouseControl[i].erase(it);
			}
			
			for(unsigned int i = 0 ; i < this->listKeyControl.size() ; i++)
			{
				std::set<Controls::Controls>::iterator it = this->listKeyControl[i].find(keyControl);
				if(it != this->listKeyControl[i].end())
					this->listKeyControl[i].erase(it);
			}
		}
		
		std::set<Controls::Controls>::iterator it = this->listMouseControl[mouseId].find(keyControl);
		if(it == this->listMouseControl[mouseId].end())
			this->listMouseControl[mouseId].insert(keyControl);
	}
}

void PlayerControls::suspendListening()
{
  ListenerKeyboard::getSingletonPtr()->signalKeyStillPressed.remove(&PlayerControls::keyboardStillPressed, this);
  ListenerKeyboard::getSingletonPtr()->signalKeyPressed.remove(&PlayerControls::keyboardPressed, this);
  ListenerKeyboard::getSingletonPtr()->signalKeyReleased.remove(&PlayerControls::keyboardReleased, this);
  ListenerMouse::getSingletonPtr()->signalMouseMoved.remove(&PlayerControls::mouseMoved, this);
  ListenerMouse::getSingletonPtr()->signalMousePressed.remove(&PlayerControls::mousePressed, this);
  ListenerMouse::getSingletonPtr()->signalMouseReleased.remove(&PlayerControls::mouseReleased, this);
  
  ListenerMouse::getSingletonPtr()->signalMouseMoved.add(&PlayerControls::mouseMovedInPause, this);
  ListenerMouse::getSingletonPtr()->signalMousePressed.add(&PlayerControls::mousePressedInPause, this);
  ListenerKeyboard::getSingletonPtr()->signalKeyPressed.add(&PlayerControls::keyboardPressedInPause, this);
}

void PlayerControls::continueListening()
{
  ListenerKeyboard::getSingletonPtr()->signalKeyStillPressed.add(&PlayerControls::keyboardStillPressed, this);
  ListenerKeyboard::getSingletonPtr()->signalKeyPressed.add(&PlayerControls::keyboardPressed, this);
  ListenerKeyboard::getSingletonPtr()->signalKeyReleased.add(&PlayerControls::keyboardReleased, this);
  ListenerMouse::getSingletonPtr()->signalMouseMoved.add(&PlayerControls::mouseMoved, this);
  ListenerMouse::getSingletonPtr()->signalMousePressed.add(&PlayerControls::mousePressed, this);
  ListenerMouse::getSingletonPtr()->signalMouseReleased.add(&PlayerControls::mouseReleased, this);
  
  ListenerMouse::getSingletonPtr()->signalMouseMoved.remove(&PlayerControls::mouseMovedInPause, this);
  ListenerMouse::getSingletonPtr()->signalMousePressed.remove(&PlayerControls::mousePressedInPause, this);
  ListenerKeyboard::getSingletonPtr()->signalKeyPressed.remove(&PlayerControls::keyboardPressedInPause, this);
}



void PlayerControls::mousePressedInPause(const OIS::MouseButtonID id)
{
   	std::set<Controls::Controls>::iterator it;
   	
    std::set<Controls::Controls> keys = this->OISEventToControlKey(id);
    
    if(!keys.empty())
    {
		for(it = keys.begin() ; it != keys.end() ; it ++)
		{
			Controls::Controls keyControls = *it;
			if(keyControls != Controls::NONE)
			{
				 this->signalKeyPressedInPause.dispatch(keyControls);
			}
		}
	}
}

void PlayerControls::keyboardPressedInPause(const OIS::KeyEvent &evt)
{
   	std::set<Controls::Controls>::iterator it;
   	
    std::set<Controls::Controls> keys = this->OISEventToControlKey(evt);
    
    if(!keys.empty())
    {
		for(it = keys.begin() ; it != keys.end() ; it ++)
		{
			Controls::Controls keyControls = *it;
			if(keyControls != Controls::NONE)
			{
				 this->signalKeyPressedInPause.dispatch(keyControls);
			}
		}
	}
}

void PlayerControls::mouseMovedInPause(MouseMove_t &mouseMove)
{
	if(this->getMouseMovedActif())
	{
    if(mouseMove.mouseId >= 0)
    {        
			std::set<Controls::Controls>::iterator it;
			
			std::set<Controls::Controls> keys = this->OISEventToControlKey(mouseMove.mouseId);
			
			if(!keys.empty())
			{
				for(it = keys.begin() ; it != keys.end() ; it ++)
				{
					MouseMove_t mouseMoveCopy = mouseMove;
					
					mouseMoveCopy.controlMouseId = *it;
					
					this->signalMouseMovedInPause.dispatch(mouseMoveCopy);
				}
			}
			else
			{
				mouseMove.controlMouseId = Controls::NONE;
				this->signalMouseMovedInPause.dispatch(mouseMove);
			}
		}
		else
		{
			mouseMove.controlMouseId = Controls::NONE;
			this->signalMouseMovedInPause.dispatch(mouseMove);
		}
	}
}



void PlayerControls::keyboardStillPressed(const OIS::KeyCode key)
{
   	std::set<Controls::Controls>::iterator it;
   	
    std::set<Controls::Controls> keys = this->OISEventToControlKey(key);
    
    if(!keys.empty())
    {
		for(it = keys.begin() ; it != keys.end() ; it ++)
		{
			Controls::Controls keyControls = *it;
			if(keyControls != Controls::NONE)
			{
				 this->signalKeyStillPressed.dispatch(keyControls);
			}
		}
	}
}


void PlayerControls::keyboardPressed(const OIS::KeyEvent &evt)
{
   	std::set<Controls::Controls>::iterator it;
   	
    std::set<Controls::Controls> keys = this->OISEventToControlKey(evt);
    
    if(!keys.empty())
    {
		for(it = keys.begin() ; it != keys.end() ; it ++)
		{
			Controls::Controls keyControls = *it;
			if(keyControls != Controls::NONE)
			{
				 this->signalKeyPressed.dispatch(keyControls);
			}
		}
	}
}

void PlayerControls::keyboardReleased(const OIS::KeyEvent &evt)
{
   	std::set<Controls::Controls>::iterator it;
   	
    std::set<Controls::Controls> keys = this->OISEventToControlKey(evt);
    
    if(!keys.empty())
    {
		for(it = keys.begin() ; it != keys.end() ; it ++)
		{
			Controls::Controls keyControls = *it;
			if(keyControls != Controls::NONE)
			{
				 this->signalKeyReleased.dispatch(keyControls);
			}
		}
	}
}

void PlayerControls::mouseMoved(MouseMove_t &mouseMove)
{
	if(this->getMouseMovedActif())
	{
    if(mouseMove.mouseId >= 0)
    {        
			std::set<Controls::Controls>::iterator it;
			
			std::set<Controls::Controls> keys = this->OISEventToControlKey(mouseMove.mouseId);
			
			if(!keys.empty())
			{
				for(it = keys.begin() ; it != keys.end() ; it ++)
				{
					MouseMove_t mouseMoveCopy = mouseMove;
					
					mouseMoveCopy.controlMouseId = *it;
					
					this->signalMouseMoved.dispatch(mouseMoveCopy);
				}
			}
			else
			{
				mouseMove.controlMouseId = Controls::NONE;
				this->signalMouseMoved.dispatch(mouseMove);
			}
		}
		else
		{
			mouseMove.controlMouseId = Controls::NONE;
			this->signalMouseMoved.dispatch(mouseMove);
		}
	}
}

void PlayerControls::mousePressed(const OIS::MouseButtonID id)
{
   	std::set<Controls::Controls>::iterator it;
   	
    std::set<Controls::Controls> keys = this->OISEventToControlKey(id);
    
    if(!keys.empty())
    {
		for(it = keys.begin() ; it != keys.end() ; it ++)
		{
			Controls::Controls keyControls = *it;
			if(keyControls != Controls::NONE)
			{
				 this->signalKeyPressed.dispatch(keyControls);
			}
		}
	}
}

void PlayerControls::mouseReleased(const OIS::MouseButtonID id)
{
   	std::set<Controls::Controls>::iterator it;
   	
    std::set<Controls::Controls> keys = this->OISEventToControlKey(id);
    
    if(!keys.empty())
    {
		for(it = keys.begin() ; it != keys.end() ; it ++)
		{
			Controls::Controls keyControls = *it;
			if(keyControls != Controls::NONE)
			{
				 this->signalKeyReleased.dispatch(keyControls);
			}
		}
	}
}

std::set<Controls::Controls> & PlayerControls::OISEventToControlKey(const OIS::KeyCode key)
{
	return this->listKeyControl[key];
}

std::set<Controls::Controls> & PlayerControls::OISEventToControlKey(const OIS::KeyEvent &evt)
{
	return this->listKeyControl[evt.key];
}

std::set<Controls::Controls> & PlayerControls::OISEventToControlKey(const OIS::MouseButtonID id)
{
	return this->listMouseControl[id];
}

bool PlayerControls::getMouseMovedActif()
{
	return this->mouseMovedActif;
}

void PlayerControls::setMouseMovedActif(bool mouseMovedActif)
{
	this->mouseMovedActif = mouseMovedActif;
}
