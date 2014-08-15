/*
-----------------------------------------------------------------------------
This source file is part of SleepyOgre3D
-----------------------------------------------------------------------------
*/
/*!
 * \file  MenuAbstract.h
 * \brief Ce fichier contient la déclaration de la classe MenuAbstract. Elle utilise cegui pour offrir des fenetre standard. Utiliser par le Menus et Annonce
*/
#ifndef __MENU_ABSTRACT_H__
#define __MENU_ABSTRACT_H__

#ifndef DOXYGEN_SKIP
#include <CEGUI/CEGUI.h>
#include <RendererModules/Ogre/CEGUIOgreRenderer.h>
#endif

#include "Core/Signal.h"
#include "Core/ClassRoot.h"
#include "Controls/controls.h"

/*!
* \class MenuAbstract
* \brief Elle utilise cegui pour offrir des fenetre standard. Utiliser par le Menus et Annonce
*/
class MenuAbstract : public ClassRoot
{
  protected:
    /*!
    * \brief Window of the menu
    */
    CEGUI::Window * window;
    /*!
    * \brief Define if the window is open
    */
    bool isOpen;     
    /*!
    * \brief Define if the close button is showing
    */
    bool buttonCloseShow;      
    /*!
    * \brief The name and the key of the menu
    */
    CEGUI::String name;
        

	public:
    /*!
    * \brief Constructor
    * \param name The name and the key of the menu
    */
		MenuAbstract(CEGUI::String name);
		
    /*!
    * \brief Init the menu
    */
		void initMenu();
    /*!
    * \brief Init the menu
    * \param posX Position on the axis X of the menu
    * \param posY Position on the axis Y of the menu
    * \param width Width of the menu
    * \param height Height of the menu
    */
		void initMenu(float posX, float posY, float width, float height);
		
    /*!
    * \brief Show the window
    */
		void windowShow();
    /*!
    * \brief Hide the window
    */
		void windowHide();
    /*!
    * \brief Show/Hide the window
    */
		void windowSwitch();
	
    /*!
    * \brief Generate the content of the menu.
    * The last element of the array must be 0 !
    * \return Define the content of the menu
    */
    virtual CEGUI::Window ** generateContent() = 0;

    /*!
    * \brief Réagis aux actions de player, en particulier pour gérer l'ouverture/fermeture du menus
    * \param keyControls Action appelé par le joueur
    */
    virtual void actionFromUser(Controls::Controls keyControls) = 0;


  protected:
    /*!
    * \brief Action lors de la fermeture de la fenetre avec le bouton fermer
    */
    virtual bool actionButtonClose(const CEGUI::EventArgs & evt);

    /*!
    * \brief Permet de supprimer une fenetre (appeler par create_std_window, ne devrait pas être utilisé ailleurs).
    */
    virtual bool destroyWindow(const CEGUI::EventArgs & evt) = 0;        
    
    /*!
    * \brief Permet de créer une fentre de menus générique
    * \param posX Position on the axis X of the menu
    * \param posY Position on the axis Y of the menu
    * \param width Width of the menu
    * \param height Height of the menu
    * \param content Content of the menu
    */
    void windowCreateBase(float posX, float posY ,float width, float height, CEGUI::Window ** content);
        
        
        
	// Getter - Setter	

	public:
    /*!
    * \brief [Getter] Return if the menu is open
    * \return Value of "isOpen"
    */
    bool getIsOpen();
    /*!
    * \brief [Getter] Return the window
    * \return Value of "window"
    */
    CEGUI::Window * getWindow();
    /*!
    * \brief [Getter] Return the name
    * \return Value of "name"
    */
    CEGUI::String getName();
};

#endif // __MENU_ABSTRACT_H__

