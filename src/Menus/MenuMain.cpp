#include "Menus/MenuMain.h"

MenuMain::MenuMain(CEGUI::String name) : MenuAbstract(name)
{
	this->buttonCloseShow = false;
}


CEGUI::Window ** MenuMain::generateContent()
{
    CEGUI::WindowManager &wmgr = CEGUI::WindowManager::getSingleton();

    //the add MainMenu button
    CEGUI::Window * continueWdw = wmgr.createWindow("SleekSpace/Button", "MainMenu/continue"+this->name);
    continueWdw->setText("Reprendre");
    continueWdw->setSize(CEGUI::UVector2(CEGUI::UDim( 0.8f, 0.0f ), CEGUI::UDim( 0.10f, 0.0f )));
    continueWdw->setPosition(CEGUI::UVector2( CEGUI::UDim( 0.1f, 0.0f ), CEGUI::UDim( 0.33f, 0.0f )));
    continueWdw->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&MenuMain::actionButtonContinue, this));
        
    CEGUI::Window * quitWdw = wmgr.createWindow("SleekSpace/Button", "MainMenu/quit"+this->name);
    quitWdw->setText("Quitter");
    quitWdw->setSize(CEGUI::UVector2(CEGUI::UDim( 0.8f, 0.0f ), CEGUI::UDim( 0.10f, 0.0f )));
    quitWdw->setPosition(CEGUI::UVector2( CEGUI::UDim( 0.1f, 0.0f ), CEGUI::UDim( 0.66f, 0.0f )));
    quitWdw->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&MenuMain::actionButtonQuit, this));
    
    CEGUI::Window ** tblWin = new CEGUI::Window *[3];
    tblWin[0] = continueWdw;
    tblWin[1] = quitWdw;
    tblWin[2] = 0;
    
    return tblWin;
}


void MenuMain::actionFromUser(Controls::Controls key)
{
    switch(key)
    {
      case Controls::OPEN_MENU :
        if(GestInteraction::getSingletonPtr()->getAppLauched())
        {
          this->windowSwitch();
          GestInteraction::getSingletonPtr()->switchPauseState();
        }
        break;
          
      default:
          break;
    }
}

bool MenuMain::actionButtonContinue(const CEGUI::EventArgs & evt)
{
	this->windowHide();
	
	GestInteraction::getSingletonPtr()->initScene();
	
	return true;
}

bool MenuMain::actionButtonQuit(const CEGUI::EventArgs & evt)
{
	this->windowHide();
	
	GestInteraction::getSingletonPtr()->quitApplication();
	
	return true;
}


bool MenuMain::destroyWindow(const CEGUI::EventArgs & evt)
{
	CEGUI::WindowManager &wmgr = CEGUI::WindowManager::getSingleton();
	wmgr.destroyWindow((static_cast<const CEGUI::WindowEventArgs&>(evt)).window->getParent()->getParent()->getParent());
    
  return true;
}
