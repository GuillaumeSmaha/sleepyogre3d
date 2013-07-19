#include "Menus/MenuAbstract.h"

using namespace CEGUI;


MenuAbstract::MenuAbstract(CEGUI::String name)
{
	this->name = name;
	this->window = 0;
	this->isOpen = false;
	this->buttonCloseShow = true;
}


void MenuAbstract::initMenu()
{
	CEGUI::Window ** content = this->generateContent();
	
	this->windowCreateBase(0.1f, 0.1f, 0.8f, 0.8, content);
	
	delete content;
}


void MenuAbstract::initMenu(float posX, float posY, float width, float height)
{
	CEGUI::Window ** content = this->generateContent();
	
	this->windowCreateBase(posX, posY, width, height, content);
	
	delete content;
}


void MenuAbstract::windowShow()
{
	if(this->window != 0)
	{
		CEGUI::System::getSingleton().setGUISheet(this->window);

		this->window->show();
		this->isOpen = true;
	}
}

void MenuAbstract::windowHide()
{
	if(this->window != 0)
	{
		this->window->hide();
		this->isOpen = false;
	}
}

void MenuAbstract::windowSwitch()
{
	if(this->window != 0)
	{
		if(this->isOpen)
			this->windowHide();
		else
			this->windowShow();
	}
}


bool MenuAbstract::actionButtonClose(const CEGUI::EventArgs & evt)
{
	this->windowHide();
	
	return true;
}

void MenuAbstract::windowCreateBase(float posX, float posY, float width, float height, CEGUI::Window ** content)
{
    //création de la nouvelle fenetre
    CEGUI::WindowManager &wmgr = CEGUI::WindowManager::getSingleton();
    this->window = wmgr.createWindow("DefaultWindow", "Briquette/"+this->name+"main");

    //Titlebar
    CEGUI::Window * titlebar = wmgr.createWindow("TaharezLook/Titlebar", "Briquette/titlebar"+this->name);
    titlebar->setText(name);
    titlebar->setSize(CEGUI::UVector2(CEGUI::UDim(width, 0.0f), CEGUI::UDim(0.05f, 0.0f)));
    titlebar->setPosition(CEGUI::UVector2(CEGUI::UDim(posX, 0.0f), CEGUI::UDim(posY, 0.0f)));
    this->window->addChildWindow(titlebar);

    //création du background
    CEGUI::Window * menuBackground = wmgr.createWindow("TaharezLook/StaticImage", "Background"+this->name);
    menuBackground->setSize(CEGUI::UVector2(CEGUI::UDim(width, 0.0f), CEGUI::UDim(height, 0.0f)));
    menuBackground->setPosition(CEGUI::UVector2(CEGUI::UDim(posX, 0.0f),CEGUI::UDim((posY+0.05f), 0.0f)));

    if(content[0] != 0)
    {
		int i = 0;
		while(content[i] != 0)
		{
			CEGUI::Window * tmp_content = content[i];
			menuBackground->addChildWindow(tmp_content);
			i++;
		}
	}

	if(this->buttonCloseShow)
	{
		//On ajoute un close bouton à chaque fenetre
		CEGUI::Window * quit = wmgr.createWindow("SleekSpace/Button", "Briquette/close"+this->name);
		quit->setText("Fermer");
		quit->setSize(CEGUI::UVector2(CEGUI::UDim( 0.2f, 0.0f ), CEGUI::UDim( 0.14f, 0.0f )));
		quit->setPosition( UVector2( UDim( 0.8f, 0.0f ), UDim( 0.85, 0.0f ) ) );
		quit->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&MenuAbstract::actionButtonClose, this));
		menuBackground->addChildWindow(quit);
	}
    
    this->window->addChildWindow(menuBackground);
}


// Getter - Setter


bool MenuAbstract::getIsOpen()
{
	return this->isOpen;
}

CEGUI::Window * MenuAbstract::getWindow()
{
	return this->window;
}

CEGUI::String MenuAbstract::getName()
{
	return this->name;
}
