#ifndef _USER_
#define _USER_

///Classe USER heritant de PLAYER
class USER : public PLAYER
{
	private :

		///un tableau contenant les touches du clavier servant a controler le joueur
		SHORT m_sControllers[6];

	public :

		///le nombre de joueurs humains
		static UINT s_uNumUser;

		///Le constructeur de la classe USER
		USER(STAGE* pStage) : PLAYER(pStage) {m_uID=s_uNumUser;s_uNumUser++;}
		///Le destructeur de la classe USER
		~USER() {s_uNumUser--;}

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

		///le joueur est-il un joueur humain ? oui
		virtual BOOL isUser() {return true;}
};

#endif
