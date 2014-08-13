/*
-----------------------------------------------------------------------------
This source file is part of SleepyOgre3D
-----------------------------------------------------------------------------
*/
/*!
 * \file  MenuMain.h
 * \brief Ce fichier contient la déclaration de la classe Menus. C'est la classe gérant les événements de la fenêtre.
 */
#ifndef __MENU_MAIN_H__
#define __MENU_MAIN_H__

#include "Menus/MenuAbstract.h"
#include "GestInteraction.h"

/*!
 * \class MenuMain
 * \brief Classe permettant de gérer le menu principal.
 */
class MenuMain : public MenuAbstract
{
	public:
    /*!
    * \brief Constructor
    * \param name The name and the key of the menu
    */
		MenuMain(CEGUI::String name);
		
    /*!
    * \brief Generate the content of the menu.
    * The last element of the array must be 0 !
    * \return Define the content of the menu
    */
    CEGUI::Window ** generateContent();

    /*!
    * \brief Réagis aux actions de player, en particulier pour gérer l'ouverture/fermeture du menus
    * \param keyControls Action appelé par le joueur
    */
    void actionFromUser(Controls::Controls keyControls);
        
        
  protected:
    /*!
    * \brief Action lors de la fermeture de la fenetre avec le bouton fermer
    */
    bool actionButtonContinue(const CEGUI::EventArgs & evt);
    /*!
    * \brief Action lors de la fermeture de la fenetre avec le bouton fermer
    */
    bool actionButtonQuit(const CEGUI::EventArgs & evt);
    /*!
    * \brief Permet de supprimer une fenetre (appeler par create_std_window, ne devrait pas être utilisé ailleurs).
    */
    bool destroyWindow(const CEGUI::EventArgs & evt);    
};


#endif //__MENU_MAIN_H__
