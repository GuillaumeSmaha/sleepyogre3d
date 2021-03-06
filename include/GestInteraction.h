/*!
 * \file  GestInteraction.h
 * \brief Ce fichier contient la déclaration de la classe GestInteraction. C'est la classe gérant les informations de la partie
 */
#ifndef __GEST_INTERACTION_H__
#define __GEST_INTERACTION_H__

#include "Core/ClassRootSingleton.h"
#include "Scene/nodeName.h"
#include "Scene/GestSceneManager.h"
#include "Scene/InitScene.h"
#include "Listener/ListenerFrame.h"
#include "Listener/ListenerWindow.h"
#include "Controls/controls.h"
#include "Controls/MouseFunction.h"
#include "Controls/PlayerControls.h"
#include "Menus/GestMenus.h"


/*!
 * \class GestInteraction
 * \brief Classe permettant de gérer le jeu.
 */
class GestInteraction : public ClassRootSingleton<GestInteraction>
{        
	private:
    /*!
    * \brief Indicate if the application is launched
    */
    bool appLaunched;
    /*!
    * \brief Indicate if the application is launched
    */
    bool pauseState;
    /*!
    * \brief Indicate if the movement move all camera in the same time or if the movement depend the cursor position
    */
    bool moveAllCamera;
        
	public:
    /*!
    * \brief constructeur
    */
    GestInteraction();
    /*!
    * \brief destructeur
    */
    ~GestInteraction();

	public:
    /*!
     * \brief Charge la scène
    */
    void initScene();
 
    /*!
    * \brief Quit the application
    */
    void quitApplication();
    
    /*!
    * \brief Switch the pause state
    */
    void switchPauseState();
            
    /*!
     * \brief Permet de déplacer la souris en lui injectant le vecteur x, y.
     * La souris n'est pas géré directement dans cette classe mais dans la
     * classe MouseFunction car en réalité on à 2 souris (la souris du
     * menus CEGUI et la souris de bullet pour attraper les briquettes.
     *
     * Cette fonction permet donc a GestInteraction de déplacer la souris de
     * Bullet et de CEGUI pour que les deux ai la même position
     * \param delta_x Déplacement sur l'axe X
     * \param delta_y Déplacement sur l'axe Y
    */
    void injectMouseMove(float delta_x, float delta_y);
        
        
    /*!
     * \brief Permet de recevoir un evènement quand une touche est appuyé
     * \param key Touche du clavier (Controls::Controls)
    */	
    void onKeyPressed(Controls::Controls key);
    /*!
     * \brief Permet de recevoir un evènement quand une touche est appuyé
     * \param key Touche du clavier (Controls::Controls)
    */
    void onKeyReleased(Controls::Controls key);        
    /*!
     * \brief Permet de recevoir un evènement quand une touche de la souris est appuyé ou quand la souris est déplacé
     * \param mouseMove Structure de déplacement de la souris
    */
    void onMouseMoved(MouseMove_t &mouseMove);
    /*!
     * \brief Permet de recevoir un evènement quand une touche de la souris est appuyé ou quand la souris est déplacé
     * \param mouseMove Structure de déplacement de la souris
    */
    void onMenuMouseMoved(MouseMove_t &mouseMove);
        
        
	public:
	
        // Getter - Setter
    /*!
     * \brief [Getter] Return the mouse position
     * \return The value of "posMouse"
    */
    Ogre::Vector3 getPosMouse();        
		/*!
		 * \brief Return if the application is launched
		 * \return Value of appLaunched
		*/
    bool getAppLauched();
    /*!
    * \brief Define the pause state
    * \param pauseState The new pause state
    */
    void setPauseState(bool pauseState);
		/*!
		 * \brief Return if the application is paused
		 * \return Value of pauseState
		*/
    bool getPauseState();
		/*!
		 * \brief Return if the movement move all camera in the same time or if the movement depend the cursor position
		 * \return Value of moveAllCamera
		*/
    bool getMoveAllCamera();
};


#endif //__GEST_INTERACTION_H__
