#ifndef _BUTTON_
#define _BUTTON_


class BUTTON;
///Classe BUTTON, les boutons des menus du jeu
class BUTTON
{
	public :

		///Le nom de tous les boutons
		enum NAME
		{
			LAST = 0,
			SCENARIO,
			ARENA,
			EXIT,
			EASY,
			AVERAGE,
			HARD,
			ONE_PLAYER,
			TWO_PLAYER,
			THREE_PLAYER,
			FOUR_PLAYER,
			GREENLAND,
			SNOWLAND,
			FIRELAND
		};

	private :

		///le nom du bouton
		INT m_iName;
		///son emplacement et sa taille
		SDL_Rect m_rRect;
		///son image
		SDL_Surface* m_pImage;
		///le bouton au dessus de lui
		BUTTON* m_pUp;
		///le bouton au dessous de lui
		BUTTON* m_pDown;
		///le bouton a sa gauche
		BUTTON* m_pLeft;
		///le bouton a sa droite
		BUTTON* m_pRight;

	public :

		///Le constructeur de la classe BUTTON
		BUTTON(INT iName, const SDL_Rect& rRect);
		///Le destructeur de la classe BUTTON
		~BUTTON();
		///Initialisation
		RESULT Init();
		///Animation
		RESULT FrameMove(INT iTimeElapsed);
		///Affichage
		RESULT FrameRender(SDL_Surface* & sScreen);
		///Destruction
		RESULT Destroy();

		///Lie le bouton avec les autres pour pouvoir se deplacer dans le menu
		RESULT LinkButton(BUTTON* pUp, BUTTON* pDown, BUTTON* pLeft, BUTTON* pRight);

		///Obtenir le nom du bouton
		inline INT getName() {return m_iName;};
		///Obtenir le bouton du dessus
		inline BUTTON* getButtonUp() {return m_pUp;};
		///Obtenir le bouton du dessous
		inline BUTTON* getButtonDown() {return m_pDown;};
		///Obtenir le bouton de gauche
		inline BUTTON* getButtonLeft() {return m_pLeft;};
		///Obtenir le bouton de droite
		inline BUTTON* getButtonRight() {return m_pRight;};
		///Obtenir l'emplacement et la taille du bouton
		inline SDL_Rect getRect() {return m_rRect;};
};

#endif
