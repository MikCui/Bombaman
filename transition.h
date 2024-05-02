#ifndef _TRANSITION_
#define _TRANSITION_

///Classe TRANSITION heritant de la classe FRAME
class TRANSITION : public FRAME
{
	public :

		///les differents types de transitions
		enum TYPE_TRANSITION
		{
			INTRO = 0,
			WORLD1_STAGE1,
			WORLD1_STAGE2,
			WORLD1_STAGE3,
			WORLD2_STAGE1,
			WORLD2_STAGE2,
			WORLD2_STAGE3,
			WORLD3_STAGE1,
			WORLD3_STAGE2,
			WORLD3_STAGE3,
			WORLD4_STAGE1,
			WORLD4_STAGE2,
			WORLD4_STAGE3,
			WORLD5_STAGE1,
			WORLD5_STAGE2,
			WORLD5_STAGE3,
			WORLD6_STAGE1,
			WORLD6_STAGE2,
			WORLD6_STAGE3,
			WORLD7_STAGE1,
			WORLD7_STAGE2,
			WORLD7_STAGE3,
			WORLD8_STAGE1,
			WORLD8_STAGE2,
			WORLD8_STAGE3,
			PLAYER1_WIN,
			PLAYER2_WIN,
			PLAYER3_WIN,
			PLAYER4_WIN,
			GAME_OVER,
			WIN,
			DRAW_GAME,
			EXIT
		};


	private :

		///classe SCENE, une transition est definie par des scenes (une image affichee un certain temps)
		class SCENE
		{
			public :

				///l'image a afficher
				SDL_Surface* m_pImage;
				///le temps pendant lequel elle est affichee
				INT m_iTimeWait;

				///Le constructeur n°1 de la classe SCENE
				SCENE();
				///Le constructeur n°2 de la classe SCENE
				SCENE(SDL_Surface* pImage, INT iTimeWait) {m_pImage=pImage;m_iTimeWait=iTimeWait;}
				///Le destructeur de la classe SCENE
				~SCENE() {SDL_FreeSurface(m_pImage);}
		};

		///la liste de scenes
		vector<SCENE*> m_lScenes;
		///le nombre restant de scenes a afficher
		INT m_iSceneNumber;
		///le type de la transition
		TYPE_TRANSITION m_tTransition;

	public :

		///Le constructeur de la classe TRANSITION
		TRANSITION(TYPE_TRANSITION tTransition);
		///Le destructeur de la classe TRANSITION
		~TRANSITION();

		///Initialisation
		virtual RESULT Init();
		///Animation
		virtual RESULT FrameMove(INT iTimeElapsed);
		///Affichage
		virtual RESULT FrameRender(SDL_Surface* & sScreen);
		///Destruction
		virtual RESULT Destroy();

		///reste-t-il une frame apres celle ci ?
		virtual BOOL NoMoreFrame();
		///si oui donnez la moi
		virtual FRAME* NextFrame();
};

#endif

