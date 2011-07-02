/*
-----------------------------------------------------------------------------
This source file is part of SleepyOgre3D
 
Copyright (c) 2011 Guillaume Smaha

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
of the Software, and to permit persons to whom the Software is furnished to do
so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
-----------------------------------------------------------------------------
*/
/*!
 * \file  GestMenus.h
 * \brief Ce fichier contient la déclaration de la classe GestMenus. C'est la classe gérant les événements de la fenêtre.
 */
#ifndef __GEST_MENUS_H__
#define __GEST_MENUS_H__

#ifndef DOXYGEN_SKIP
#include <map>
#endif

#include "Core/ClassRootSingleton.h"
#include "Menus/MenuAbstract.h"
#include "Controls/controls.h"
#include "Controls/MouseFunction.h"
#include "Controls/PlayerControls.h"

/*!
 * \class GestMenus
 * \brief Classe permettant de gérer les menus.
 */
class GestMenus : public ClassRootSingleton<GestMenus>
{        
    private:
        /*!
        * \brief Le renderer de CEGUI pour Ogre
        */
        CEGUI::OgreRenderer * menusRenderer;
        /*!
        * \brief Le renderer de CEGUI pour Ogre
        */
        CEGUI::Window * rootWindow;        
        /*!
        * \brief Liste des menus en fonction de leur clé
        */
        std::map<CEGUI::String, MenuAbstract *> lstMenus;
        
	public:
        /*!
        * \brief constructeur
        */
        GestMenus();
        /*!
        * \brief destructeur
        */
        ~GestMenus();

	public:
        /*!
         * \brief Lance l'affichage des différents éléments du menus lors de l'activation de celui ci
         * \param menu The menu
         */
        void addMenu(MenuAbstract * menu);

        /*!
         * \brief Lance l'affichage des différents éléments du menus lors de l'activation de celui ci
         * \param key Key of the menu
         */
        void menuShow(CEGUI::String key);
        /*!
         * \brief Retire le menus lorsque l'on le quitte.
         * \param key Key of the menu
         */
        void menuHide(CEGUI::String key);
        
        /*!
         * \brief Affiche la souris
         */
        void mouseShow();
        /*!
         * \brief cache la souris
        */
        void mouseHide();

        /*!
         * \brief Permet de déplacer la souris en lui injectant le vecteur x, y.
         * La souris n'est pas géré directement dans cette classe mais dans la
         * classe MouseFunction car en réalité on à 2 souris (la souris du
         * menus CEGUI et la souris de bullet pour attraper les briquettes.
         *
         * Cette fonction permet donc a GestInteraction de déplacer la souris de
         * CEGUI pour que les deux ai la même position
         * \param delta_x Déplacement sur l'axe X
         * \param delta_y Déplacement sur l'axe Y
        */
        void injectMouseMove(float delta_x, float delta_y);
        
        /*!
        * \brief Réagis aux actions de player, en particulier pour gérer l'ouverture/fermeture du menus
        * \param keyControls Action appelé par le joueur
        */
        void actionFromUser(Controls::Controls keyControls);

    private:          
        /*!
         * \brief Crée le WindowManager de cegui
         */
        void rootWindowCreate();        

        /*!
        * \brief Permet d'afficher un curseur de souris
        */
        void mouseCreate();
                
        /*!
         * \brief Permet de récupérer appuis sur touche dans cegui
        */
        void keyStillPressed(const OIS::KeyCode key);
        /*!
         * \brief Permet de récupérer appuis sur touche dans cegui
        */
        void keyPressed(const OIS::KeyEvent &evt);
        /*!
         * \brief Permet de récupérer les relachements d'une touche dans cegui
        */
        void keyReleased(const OIS::KeyEvent &evt);
        /*!
         * \brief Permet de récupérer les déplacements de la souris
        */
        void mouseMoved(MouseMove_t &mouse);
        /*!
         * \brief Permet de récupérer les clics de souris dans cegui
        */
        void mousePressed(OIS::MouseButtonID id);
        /*!
         * \brief Permet de récupérer les relachements de la souris dans cegui
        */
        void mouseReleased(OIS::MouseButtonID id);  
};


#endif //__GEST_MENUS_H__
