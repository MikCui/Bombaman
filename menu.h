#ifndef _MENU_
#define _MENU_

///Classe MENU heritant de FRAME, designe les menus du jeu
class MENU : public FRAME
{
	public :
		///les types de menus differents
		enum TYPE_MENU
		{
			MODE = 0,	  //Choix du mode : Solo,Multi,Options,Quitter
			DIFFICULTY,
			NUM_PLAYER,	 //Choix du nombre de joueur
			MAP,
			SETTINGS
		};

		///les touches du clavier (americain) permettant d'intereagir avec le menu
		enum PAD	//CLAVIER US
		{
			 UP1 = SDLK_w,
			 DOWN1 = SDLK_s,
			 LEFT1 = SDLK_a,
			 RIGHT1 = SDLK_d,
			 UP2 = SDLK_UP,
			 DOWN2 = SDLK_DOWN,
			 LEFT2 = SDLK_LEFT,
			 RIGHT2 = SDLK_RIGHT,
			 START = SDLK_RETURN,
			 BACK = SDLK_BACKSPACE,
			 EXIT = SDLK_ESCAPE
		};

	private :

		///le bouton selectionne du menu
		BUTTON* m_pSelection;
		///le type du menu
		TYPE_MENU m_tMenu;
		///le type du menu precedant le menu actuel
		TYPE_MENU m_tLastMenu;
		///la liste des boutons composant le menu
		list<BUTTON*> m_bButtons;
		///l'image de la selection
		SDL_Surface* m_pSelectionImage;
		///l'image de fond
		SDL_Surface* m_pBackground;

	public :

		///Le constructeur de la classe MENU
		MENU(TYPE_MENU tMenu);
		///Le destructeur de la classe MENU
		~MENU();

		///Initialisation
		virtual RESULT Init();
		///Gestion des entrees
		virtual RESULT Input(TOOLS::INPUT* iInput);
		///Animation
		virtual RESULT FrameMove(INT iTimeElapsed);
		///Affichage
		virtual RESULT FrameRender(SDL_Surface* & sScreen);
		///Destruction
		virtual RESULT Destroy();

		///La frame suivant la frame actuelle
		virtual FRAME* NextFrame();
};

#endif
