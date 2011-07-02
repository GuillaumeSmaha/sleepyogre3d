#include "Controls/MouseFunction.h"


template<> MouseFunction * ClassRootSingleton<MouseFunction>::_instance = NULL;


CEGUI::MouseButton MouseFunction::convertButton(OIS::MouseButtonID id)
{
    switch(id)
    {
        case OIS::MB_Left:
            return CEGUI::LeftButton;

        case OIS::MB_Right:
            return CEGUI::RightButton;

        case OIS::MB_Middle:
            return CEGUI::MiddleButton;

        default:
            return CEGUI::LeftButton;
    }
}


void MouseFunction::createSingleton()
{
    std::cerr << "Le constructeur de MouseFunction ne doit pas être appelé via \
        createSingleton() et doit être appelé avec un Ogre::RenderWindow * en argument \
        !" << std::endl << "Attention le singleton n'ayant pas été crée, il est fort \
        possible d'avoir des erreurs de segmentation"  << std::endl ;
}

void MouseFunction::createSingleton(Ogre::RenderWindow * win)
{
    new MouseFunction(win);
}

MouseFunction::MouseFunction(Ogre::RenderWindow * win) : ClassRootSingleton<MouseFunction>()
{
	this->winWidth = win->getWidth();
	this->winHeight = win->getHeight();

	//la souris est centré initialement
	this->posMouse[0] = 0.5;        //correspond à la position horizontale
	this->posMouse[1] = 0.5;        //correspond à la position verticale
	
	ListenerWindow::getSingletonPtr()->signalWindowResized.add(&MouseFunction::onWindowResize, this);
}


MouseFunction::~MouseFunction()
{
	
}



void MouseFunction::injectMouseMove(float delta_x, float delta_y)
{
	//réglage horizontal
	this->posMouse[0] = this->posMouse[0] + (delta_x / this->winWidth);

	//Ces conditions permettent d'éviter que la souris ne sorte de la fenetre
	//C'est nécéssaire car la souris CEGUI est prévu pour ne pas sortir de la fenetre, 
	//on perd donc la correspondance si l'une sort et pas l'autre
	if(this->posMouse[0] < (0.0))
	{
		this->posMouse[0] = 0.0;
	}
	if(this->posMouse[0] > (1.0))
	{
		this->posMouse[0] = 1.0;
	}

	//réglage vertical
	this->posMouse[1] = this->posMouse[1] + (delta_y / this->winHeight);

	//Ces conditions permettent d'éviter que la souris ne sorte de la fenetre
	//C'est nécéssaire car la souris CEGUI est prévu pour ne pas sortir de la fenetre, 
	//on perd donc la correspondance si l'une sort et pas l'autre
	if(this->posMouse[1] < (0.0))
	{
		this->posMouse[1] = 0.0;
	}
	if(this->posMouse[1] > (1.0))
	{
		this->posMouse[1] = 1.0;
	}
}


void MouseFunction::onWindowResize(Ogre::RenderWindow * rw)
{
	this->winWidth = rw->getWidth();
	this->winHeight = rw->getHeight();
}


//Getter - Setter

Ogre::Vector3 MouseFunction::getPosMouse()
{
	return this->posMouse;
}
