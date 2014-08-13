/*
-----------------------------------------------------------------------------
This source file is part of SleepyOgre3D
-----------------------------------------------------------------------------
*/
/*!
 * \file  PlayerControls.h
 * \brief Ce fichier contient la déclaration de la classe PlayerControls. 
*/
#ifndef __PLAYER_CONTROLS_H__
#define __PLAYER_CONTROLS_H__

#ifndef DOXYGEN_SKIP
#include <vector>
#include <set>
#endif

#include "Core/Signal.h"
#include "Core/ClassRootSingleton.h"
#include "Listener/ListenerKeyboard.h"
#include "Listener/ListenerMouse.h"
#include "Controls/controls.h"
#include "Controls/mouseMove.h"
#include "Tools/Utils.h"

/*!
* \class PlayerControls
* \brief Class Permettant de gérer le contrôle de manière "haut niveau" du joueur au d'utiliser directement les évènements de base de Ogre
* Permettra par la suite de facilemet modifier les contrôles pour chaque joueur (enregistrés dans un fichier par exemple)
* Par la suite il faudra donc écouter les évènements (signaux) de PlayerControls et non plus directement de mouse et keyboard
*/
class PlayerControls: public ClassRootSingleton<PlayerControls>
{
		
	public:
	     /*!
		 * \brief Nombre maximum de touche clavier dans OIS
		 */
		const static int maxOISKeyControl = 0xED+1;
         /*!
		 * \brief Nombre maximum de touche souris dans OIS
		 */
		const static int maxOISMouseControl = 7;
	

	private:
    /*!
		 * \brief Lie une touche à un contrôle (déplacement, tir). 
     * par exemple listKeyControl[25].insert(SHOOT) positionne la touche repéré par le code 25 sur l'action SHOOT
		 */
    std::vector< std::set<Controls::Controls> > listKeyControl;
    /*!
		 * \brief Lie un bouton de souris à un contrôle.
		 */
    std::vector< std::set<Controls::Controls> > listMouseControl;
    /*!
		 * \brief Indique si le mouseMove est pris en compte pour les mouvements du vaisseau
		 */
    bool mouseMovedActif;

       
	public:
		/*!
		 * \brief Emet un dispatche lorsqu'une touche est resté préssée (seulement pour le clavier) Signal(Controls::Controls key)
		 */
    Signal<Controls::Controls> signalKeyStillPressed;
		/*!
		 * \brief Emet un dispatche lorsqu'une touche est préssée  Signal(Controls::Controls key)
		 */
    Signal<Controls::Controls> signalKeyPressed;
        /*!
		 * \brief Emet un dispatche lorsqu'une touche est relâchée  Signal(Controls::Controls key)
		 */
    Signal<Controls::Controls> signalKeyReleased;
    /*!
		 * \brief Emet un dispatche lorsque la souris est déplacée Signal(MouseMove_t)
		 */
    Signal<MouseMove_t&> signalMouseMoved;
		/*!
		 * \brief Emet un dispatche lorsqu'une touche est préssée pendant la pause Signal(Controls::Controls key)
		 */
    Signal<Controls::Controls> signalKeyPressedInPause;
    /*!
		 * \brief Emet un dispatche lorsque la souris est déplacée pendant la pause Signal(MouseMove_t)
		 */
    Signal<MouseMove_t&> signalMouseMovedInPause;
 
    public:
        /*!
         * \brief Constructor
         */
        PlayerControls();
        /*!
         * \brief Destructor
         */
        virtual ~PlayerControls();

    public:
        /*!
         * \brief Permet de remettre les touches par défaults
         */
        void setDefaultKeys(void);        
        /*!
         * \brief Met à zéro les controllers de touche clavier et souris
         */
        void resetControls(void);        
        /*!
         * \brief Définit une touche du clavier pour une action donnée
         * \param keyControl Action à effectuer
         * \param key Touche correspondante
         * \param removeDuplicate Definit si l'on supprime ou non les doublons avant l'affectation.
         * Permet en autre d'ajouter plusieurs touches pour une seule action
         * Définit à vrai par défaut.
         */
        void setKeyControl(const Controls::Controls keyControl, const OIS::KeyCode key, bool removeDuplicate = false);
        /*!
         * \brief Définit une touche de la souris pour une action donnée
         * \param keyControl Action à effectuer
         * \param mouseId Touche correspondante
         * \param removeDuplicate Definit si l'on supprime ou non les doublons avant l'affectation.
         * Permet en autre d'ajouter plusieurs touches pour une seule action
         * Définit à vrai par défaut.
         */
        void setMouseControl(const Controls::Controls keyControl, const OIS::MouseButtonID mouseId, bool removeDuplicate = false);
	
        /*!
         * \brief Permet d'arréter de réagir aux listeners 
         * Utile lorsque le menu est activé.
        */
        void suspendListening();
        /*!
         * \brief Permet de rependre l'écoute des listeneurs
         * Appelé aprés que le menu ai été fermé.
        */
        void continueListening();
        
        
    private:
    /*!
		 * \brief Reçoit un dispatche lorsqu'une touche du clavier est pressée pendant la pause et le transmet à signalKeyPressed
		 * \param id Evénement du clavier
		 */
    void mousePressedInPause(const OIS::MouseButtonID id);
    /*!
		 * \brief Reçoit un dispatche lorsqu'un la souris est bougée pendant la pause et le transmet à signalMouseMoved
		 * \param mouseMove Structure de déplacement de la souris
		 */
    void mouseMovedInPause(MouseMove_t &mouseMove);
    /*!
		 * \brief Reçoit un dispatche lorsqu'une touche du clavier est pressée pendant la pause et le transmet à signalKeyPressed
		 * \param evt Evénement du clavier
		 */
    void keyboardPressedInPause(const OIS::KeyEvent &evt);
        
    /*!
		 * \brief Reçoit un dispatche lorsqu'une touche du clavier est resté pressée et le transmet à signalKeyStillPressed
		 * \param key Evénement du clavier
		 */
    void keyboardStillPressed(const OIS::KeyCode key);
    /*!
		 * \brief Reçoit un dispatche lorsqu'une touche du clavier est pressée et le transmet à signalKeyPressed
		 * \param evt Evénement du clavier
		 */
    void keyboardPressed(const OIS::KeyEvent &evt);
    /*!
		 * \brief Reçoit un dispatche lorsqu'une touche du clavier est relâchée et le transmet à signalKeyReleased
		 * \param evt Evénement du clavier
		 */
    void keyboardReleased(const OIS::KeyEvent &evt);
    /*!
		 * \brief Reçoit un dispatche lorsqu'un la souris est bougée et le transmet à signalMouseMoved
		 * \param mouseMove Structure de déplacement de la souris
		 */
    void mouseMoved(MouseMove_t &mouseMove);
    /*!
		 * \brief Reçoit un dispatche lorsqu'une touche de la souris est pressée et le transmet à signalMousePressed
		 * \param id Evénement de la souris
		 */
    void mousePressed(const OIS::MouseButtonID id);
    /*!
		 * \brief Reçoit un dispatche lorsqu'une touche de la souris est relâchée et le transmet à signalMouseReleased
		 * \param id Evénement de la souris
		 */
    void mouseReleased(const OIS::MouseButtonID id);
    /*!
		 * \brief Convertit un évènement OIS::KeyEvent en Controls::Controls pour se défaire du couplage aux touches physiques
		 * \param key Evénement du clavier (OIS)
		 * \return Touches correspondantes
		 */
    std::set<Controls::Controls> & OISEventToControlKey(const OIS::KeyCode key);
    /*!
		 * \brief Convertit un évènement OIS::KeyEvent en Controls::Controls pour se défaire du couplage aux touches physiques
		 * \param evt Evénement du clavier (OIS)
		 * \return Touches correspondantes
		 */
    std::set<Controls::Controls> & OISEventToControlKey(const OIS::KeyEvent &evt);
    /*!
		 * \brief Convertit un id IS::MouseButtonID en Controls::Controls pour se défaire du couplage aux touches physiques
		 * \param id Evénement de la souris (OIS)
		 * \return Touches correspondantes
		 */
    std::set<Controls::Controls> & OISEventToControlKey(const OIS::MouseButtonID id);
        
        
//Getter-Setter
        
	public:        
    /*!
		 * \brief [Getter] Recupère la valeur de mouseMovedActif
		 * \return Indique si le mouvement de la souris est actif pour le vaisseau
		 */
    bool getMouseMovedActif();
    /*!
		 * \brief [Setter] Définit la valeur de mouseMovedActif
		 * \param mouseMovedActif Indique si le mouvement de la souris est actif pour le vaisseau
		 */
    void setMouseMovedActif(bool mouseMovedActif);


};

#endif // __PLAYER_CONTROLS_H__
