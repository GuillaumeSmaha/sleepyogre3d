#include "Listener/ListenerMouse.h"

template<> ListenerMouse * ClassRootSingleton<ListenerMouse>::_instance = NULL;

void ListenerMouse::createSingleton()
{
	if(ListenerInputManager::getSingletonPtr()->getInputManager() != NULL)
	{
		new ListenerMouse();
	}
	else
	{
		std::cerr << "@ListenerMouse::createSingleton() : InputManager undefined" << std::endl;
	}
}


ListenerMouse::ListenerMouse() : ClassRootSingleton<ListenerMouse>()
{
	OIS::InputManager * inputManager = ListenerInputManager::getSingletonPtr()->getInputManager();
	this->mouse = static_cast<OIS::Mouse*>(inputManager->createInputObject(OIS::OISMouse, true));
	this->mouse->setEventCallback(this);
	
	//Add signals to capture the event
	ListenerWindow::getSingletonPtr()->signalWindowResized.add(&ListenerMouse::onWindowResize, this);
	ListenerFrame::getSingletonPtr()->signalFrameRendering.add(&ListenerMouse::capture, this);
}

ListenerMouse::~ListenerMouse()
{
	ListenerInputManager::getSingletonPtr()->getInputManager()->destroyInputObject(this->mouse);
}

void ListenerMouse::capture()
{
    this->capture(NULL);
}

void ListenerMouse::capture(void *)
{
    this->mouse->capture();
}

bool ListenerMouse::mouseMoved(const OIS::MouseEvent &evt)
{
	if(this->lstMousePressedId.empty())
	{
		MouseMove_t move;
		move.mouseId = static_cast<OIS::MouseButtonID>(-1);
		move.vector = Ogre::Vector3(evt.state.X.rel, evt.state.Y.rel, evt.state.Z.rel);
		this->signalMouseMoved.dispatch(move);
	}
	else
	{
		std::list<OIS::MouseButtonID>::iterator it;
		for(it = this->lstMousePressedId.begin() ; it != this->lstMousePressedId.end() ; it ++)
		{
			MouseMove_t move;
			move.mouseId = *it;
			move.vector = Ogre::Vector3(evt.state.X.rel, evt.state.Y.rel, evt.state.Z.rel);
			this->signalMouseMoved.dispatch(move);
		}
	}

	return true;
}

bool ListenerMouse::mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
{
	this->lstMousePressedId.push_back(id);
	
    this->signalMousePressed.dispatch(id);
	return true;
}

bool ListenerMouse::mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
{	
	this->lstMousePressedId.remove(id);

    this->signalMouseReleased.dispatch(id);
	return true;
}


void ListenerMouse::onWindowResize(Ogre::RenderWindow * rw)
{
	const OIS::MouseState &ms = this->mouse->getMouseState();
	ms.width = rw->getWidth();
	ms.height = rw->getHeight();
}



//Getter - Setter

OIS::MouseButtonID ListenerMouse::getLastMousePressedId()
{
	if(!this->lstMousePressedId.empty())
		return this->lstMousePressedId.back();
	else
		return static_cast<OIS::MouseButtonID>(-1);
}

OIS::Mouse * ListenerMouse::getMouse()
{
	return this->mouse;
}
