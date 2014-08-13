#include "Listener/ListenerFrame.h"

template<> ListenerFrame * ClassRootSingleton<ListenerFrame>::_instance = 0;


void ListenerFrame::createSingleton()
{
	std::cerr << "Le constructeur de ListenerFrame ne doit pas être appelé via createSingleton() et doit être appelé avec un Ogre::Root * en argument!" << std::endl << "Attention le singleton n'ayant pas été crée, il est fort possible d'avoir des erreurs de segmentation" << std::endl;
}

void ListenerFrame::createSingleton(Ogre::Root * root)
{
	new ListenerFrame(root);
}

ListenerFrame::ListenerFrame(Ogre::Root * root) : ClassRootSingleton<ListenerFrame>(), closed(false)
{
  root->addFrameListener(this);   	

	//Add signals to close the application
	ListenerWindow::getSingletonPtr()->signalWindowClosed.add(&ListenerFrame::shutdown, this);
}

ListenerFrame::~ListenerFrame()
{
}

bool ListenerFrame::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
    if(this->closed)
    {
        return false;
    }

    this->signalFrameRendering.dispatch();
    
	return true;
}

bool ListenerFrame::frameStarted(const Ogre::FrameEvent &evt)
{
	this->signalFrameStarted.dispatch(evt);
	
    return true;
}

bool ListenerFrame::frameEnded(const Ogre::FrameEvent &evt)
{
	this->signalFrameEnded.dispatch(evt);
	
	return true;
}


void ListenerFrame::shutdown()
{
    this->shutdown(0);

}

void ListenerFrame::shutdown(void*)
{
    this->closed = true;
}
