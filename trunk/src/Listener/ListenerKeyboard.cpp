#include "Listener/ListenerKeyboard.h"

template<> ListenerKeyboard * ClassRootSingleton<ListenerKeyboard>::_instance = NULL;

void ListenerKeyboard::createSingleton()
{
	if(ListenerInputManager::getSingletonPtr()->getInputManager() != NULL)
	{
		new ListenerKeyboard();
	}
	else
	{
		std::cerr << "@ListenerKeyboard::createSingleton() : InputManager undefined" << std::endl;
	}
}

ListenerKeyboard::ListenerKeyboard() : ClassRootSingleton<ListenerKeyboard>()
{
    OIS::InputManager * inputManager = ListenerInputManager::getSingletonPtr()->getInputManager();
	this->keyboard = static_cast<OIS::Keyboard*>(inputManager->createInputObject(OIS::OISKeyboard, true));
	this->keyboard->setEventCallback(this);
	
	//Add signals to capture the event
	ListenerFrame::getSingletonPtr()->signalFrameRendering.add(&ListenerKeyboard::capture, this);
}

ListenerKeyboard::~ListenerKeyboard()
{
	ListenerInputManager::getSingletonPtr()->getInputManager()->destroyInputObject(this->keyboard);
}

void ListenerKeyboard::capture()
{
    this->capture(NULL);
}

void ListenerKeyboard::capture(void *)
{
    this->keyboard->capture();
    this->keyStillPressed(NULL);
}

bool ListenerKeyboard::keyStillPressed(void *)
{
	if(!this->lstKeyPressedId.empty())
	{
		std::list<OIS::KeyCode>::iterator it;
		for(it = this->lstKeyPressedId.begin() ; it != this->lstKeyPressedId.end() ; it ++)
		{
			this->signalKeyStillPressed.dispatch(*it);
		}
	}

	return true;
}

bool ListenerKeyboard::keyPressed(const OIS::KeyEvent &evt)
{
	this->lstKeyPressedId.push_back(evt.key);
	
	this->signalKeyPressed.dispatch(evt);
	return true;
}


bool ListenerKeyboard::keyReleased(const OIS::KeyEvent &evt)
{
	this->lstKeyPressedId.remove(evt.key);
	
	this->signalKeyReleased.dispatch(evt);
	return true;
}
