#include "Menus/GestMenus.h"


template<> GestMenus * ClassRootSingleton<GestMenus>::_instance = 0;

GestMenus::GestMenus() : ClassRootSingleton<GestMenus>()
{
    this->rootWindow = 0;
    
   //démarre le menusRenderer
	this->menusRenderer = &CEGUI::OgreRenderer::bootstrapSystem();

    //prépare les différents groupes de ressources
    CEGUI::Imageset::setDefaultResourceGroup("Imagesets");
    CEGUI::Font::setDefaultResourceGroup("Fonts");
    CEGUI::Scheme::setDefaultResourceGroup("Schemes");
    CEGUI::WidgetLookManager::setDefaultResourceGroup("LookNFeel");
    CEGUI::WindowManager::setDefaultResourceGroup("Layouts");

    //charge un scheme
    CEGUI::SchemeManager::getSingleton().create("SleekSpace.scheme");
    CEGUI::SchemeManager::getSingleton().create("TaharezLook.scheme");

    //enregistre les signaux sur le clavier
    ListenerKeyboard::getSingletonPtr()->signalKeyStillPressed.add(&GestMenus::keyStillPressed, this);
    ListenerKeyboard::getSingletonPtr()->signalKeyPressed.add(&GestMenus::keyPressed, this);
	ListenerKeyboard::getSingletonPtr()->signalKeyReleased.add(&GestMenus::keyReleased, this);
	
    //enregistre les signaux sur la souris
    ListenerMouse::getSingletonPtr()->signalMouseMoved.add(&GestMenus::mouseMoved, this);
    ListenerMouse::getSingletonPtr()->signalMousePressed.add(&GestMenus::mousePressed, this);
    ListenerMouse::getSingletonPtr()->signalMouseReleased.add(&GestMenus::mouseReleased, this);
    
    PlayerControls::getSingletonPtr()->signalKeyPressed.add(&GestMenus::actionFromUser, this);
    PlayerControls::getSingletonPtr()->signalKeyPressedInPause.add(&GestMenus::actionFromUser, this);
    
    this->rootWindowCreate();
    this->mouseCreate(); 
    this->mouseShow();    
}

GestMenus::~GestMenus()
{
	ListenerKeyboard::getSingletonPtr()->signalKeyStillPressed.remove(&GestMenus::keyStillPressed, this);
	ListenerKeyboard::getSingletonPtr()->signalKeyPressed.remove(&GestMenus::keyPressed, this);
	ListenerKeyboard::getSingletonPtr()->signalKeyReleased.remove(&GestMenus::keyReleased, this);
    
	ListenerMouse::getSingletonPtr()->signalMouseMoved.remove(&GestMenus::mouseMoved, this);
	ListenerMouse::getSingletonPtr()->signalMousePressed.remove(&GestMenus::mousePressed, this);
	ListenerMouse::getSingletonPtr()->signalMouseReleased.remove(&GestMenus::mouseReleased, this);
    
    
    PlayerControls::getSingletonPtr()->signalKeyPressed.remove(&GestMenus::actionFromUser, this);
    PlayerControls::getSingletonPtr()->signalKeyPressedInPause.remove(&GestMenus::actionFromUser, this);

	std::map<CEGUI::String, MenuAbstract *>::iterator it;
	for(it = this->lstMenus.begin() ; it != this->lstMenus.end() ; it ++)
	{
		MenuAbstract * menuTmp = (*it).second;
		delete menuTmp;
	}

	this->lstMenus.clear();

    this->menusRenderer->destroyAllGeometryBuffers();
    this->menusRenderer->destroyAllTextureTargets();
    this->menusRenderer->destroyAllTextures();

    //~ CEGUI::WindowManager &wmgr = CEGUI::WindowManager::getSingleton();
    //~ wmgr.destroyAllWindows(); // Executer à l'appel du return dans main.cpp (eh oui etrange xD)
    //~ CEGUI::OgreRenderer::destroySystem(); // Executer à l'appel du return dans main.cpp (eh oui etrange xD)
}


void GestMenus::addMenu(MenuAbstract * menu)
{
	if(this->lstMenus.find(menu->getName()) == this->lstMenus.end())
	{
		this->lstMenus[menu->getName()] = menu;
		
		this->rootWindow->addChildWindow(menu->getWindow());
	}
	else
	{
		std::cerr << "Menu '" << menu->getName() << "' already exist !" << std::endl;
	}
}


void GestMenus::menuShow(CEGUI::String key)
{
	if(this->lstMenus.find(key) != this->lstMenus.end())
	{
		this->lstMenus[key]->windowShow();
	}
}

void GestMenus::menuHide(CEGUI::String key)
{
	if(this->lstMenus.find(key) != this->lstMenus.end())
	{
		this->lstMenus[key]->windowHide();
	}
}

void GestMenus::mouseShow()
{
    CEGUI::MouseCursor::getSingleton().show();
}

void GestMenus::mouseHide()
{
    CEGUI::MouseCursor::getSingleton().hide();
}

void GestMenus::injectMouseMove(float delta_x, float delta_y)
{
    CEGUI::System::getSingleton().injectMouseMove(delta_x, delta_y);
}

void GestMenus::actionFromUser(Controls::Controls keyControls)
{
	std::map<CEGUI::String, MenuAbstract *>::iterator it;
	for(it = this->lstMenus.begin() ; it != this->lstMenus.end() ; it ++)
	{
		(*it).second->actionFromUser(keyControls);
	}
}



void GestMenus::rootWindowCreate()
{
    CEGUI::WindowManager &wmgr = CEGUI::WindowManager::getSingleton();
    this->rootWindow = wmgr.createWindow ("DefaultWindow", "Briquette/root");
}

void GestMenus::mouseCreate()
{
    CEGUI::System::getSingleton().setDefaultMouseCursor("SleekSpace", "MouseArrow");
    CEGUI::MouseCursor::getSingleton().setImage(CEGUI::System::getSingleton().getDefaultMouseCursor());
    CEGUI::MouseCursor::getSingleton().hide();
}



void GestMenus::keyStillPressed(const OIS::KeyCode key)
{
}

void GestMenus::keyPressed(const OIS::KeyEvent &evt)
{
    CEGUI::System &sys = CEGUI::System::getSingleton();
    sys.injectKeyDown(evt.key);
    sys.injectChar(evt.text);
}

void GestMenus::keyReleased(const OIS::KeyEvent &evt)
{
    CEGUI::System::getSingleton().injectKeyUp(evt.key);
}

void GestMenus::mousePressed(OIS::MouseButtonID id)
{
    CEGUI::System::getSingleton().injectMouseButtonDown(MouseFunction::convertButton(id));
}

void GestMenus::mouseReleased(OIS::MouseButtonID id)
{
    CEGUI::System::getSingleton().injectMouseButtonUp(MouseFunction::convertButton(id));
}

void GestMenus::mouseMoved(MouseMove_t &mouse)
{
}

