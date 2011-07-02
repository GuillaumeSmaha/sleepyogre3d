#include "Menus/InitMenus.h"

void InitMenus::init()
{
	//Create GestMenus Singleton
	GestMenus::createSingleton();   
	
    //Menus
    MenuMain * menuMain = new MenuMain("MenuMain");
    
    menuMain->initMenu();
    
    GestMenus::getSingletonPtr()->addMenu(menuMain);
    GestMenus::getSingletonPtr()->menuShow(menuMain->getName());
}

void InitMenus::destroy()
{
	GestMenus::destroySingleton();
}
