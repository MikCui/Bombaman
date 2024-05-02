#ifndef _ENGINE_
#define _ENGINE_

///Classe ENGINE, Le moteur de l'application
class ENGINE
{
	private :

		///la frame en cours de traitement
		FRAME* m_fFrame;
		///la couleur de fond par defaut
		SDL_Color m_cBackgroundColor;

	public :

		//VARIABLES//
		///La largeur de l'ecran
		INT m_iScreenWidth;
		///La hauteur de l'ecran
		INT m_iScreenHeight;
		///La profondeur des couleurs
		INT m_iColorDepth;
		///Mode plein ecran ou fenetre
		BOOL m_bFullScreen;
		///Titre de l'application
		CHAR* m_pTitle;
		///Le tableau contenant les entrees clavier (aussi souris)
		TOOLS::INPUT m_iInput[323];
		///Le temps ecoule entre deux frames
		INT m_iTimeElapsed;
		///Le temps depuis que l'application a ete lancee
		INT m_iTime;

		//PARAMETRE DU JEU//
		///le nombre de joueur pour une partie multijoueur
		UINT m_uNumPlayer;
		///le nombre de vie restante pour une partie en solo
		UINT m_uPlayerLife;

		///doit on quitter le programme ?
		BOOL m_bExit;

		//METHODES//
		///Preinitialisation
		RESULT OneTimeSceneInit();
		///Initialisation
		virtual RESULT Init();
		///Gestion des entrees
		virtual RESULT Input();
		///Animation
		virtual RESULT FrameMove(INT iTimeElapsed);
		///Affichage
		virtual RESULT FrameRender(SDL_Surface* sScreen);
		///Destruction
		virtual RESULT Destroy();

		///Obtenir le nombre de joueurs (humains)
		UINT getPlayerNumber() {return m_uNumPlayer;}
		///Obtenir le nombre de vies restantes
		UINT getPlayerLife() {return m_uPlayerLife;}
		///Obtenir la frame en cours de traitement
		FRAME*& getFrame() {return m_fFrame;}
		///Definir le nombre de joueurs (humains)
		VOID setPlayerNumber(UINT uNumPlayer) {m_uNumPlayer=uNumPlayer;}
		///Definir le nombre de vies restantes
		VOID setPlayerLife(UINT uPlayerLife) {m_uPlayerLife=uPlayerLife;}
		///Definir la frame en cours de traitement
		VOID setFrame(FRAME* fFrame) {m_fFrame=fFrame;}
		///Definir si on doit quitter l'application ou pas
		VOID setExit(BOOL bExit) {m_bExit=bExit;}

};

#endif


