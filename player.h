#ifndef _PLAYER_
#define _PLAYER_

///Classe PLAYER, representant les joueurs (Utilisateurs et I.A.)
class PLAYER
{
	protected :

		///le niveau ou le joueur a ete cree
		STAGE* m_pStage;
		///le joueur va-t-il etre detruit
		BOOL m_bFinished;

		///l'identifiant du joueur
		UINT m_uID;
		///son image (prevu dans le cas ou on le voit de face, de dos, profil gauche et droite)
		SDL_Surface* m_pCharacters[4];

		///Le constructeur protege de la classe PLAYER
		PLAYER(STAGE* pStage) {m_uID=100;m_bFinished=false;m_pStage=pStage;}

	public :

		///les differents types d'action que l'on peut effectuer
		typedef enum ACTION
		{
			UP = 0,
			DOWN,
			LEFT,
			RIGHT,
			PLANT_BOMB,
			SPECIAL
		};

		///la puissance des bombes que l'on peut poser
		UINT m_uRange;
		///le nombre de bombes que l'on peut poser
		UINT m_uBomb;
		///la vitesse a laquelle on se deplace
		FLOAT m_fSpeed;
		///la position au carreau pres
		TOOLS::POINT m_pPositionStep;
		///la position au pixel pres selon la position au carreau
		POINTF m_pPosition;

		///le tableau regissant les differentes actions
		BOOL m_bActions[6];

		//static list<CHARACTER*> m_pImageCharacter;

		///Le destructeur de la classe PLAYER
		virtual ~PLAYER() {}

		///Initialisation
		virtual RESULT Init();
		///Gestion des entrees
		virtual RESULT Input(TOOLS::INPUT* iInput) {return OK;}
		///Animation
		virtual RESULT FrameMove(INT iTimeElapsed);
		///Affichage
		virtual RESULT FrameRender(SDL_Surface* & sScreen);
		///Destruction
		virtual RESULT Destroy();

		///Le joueur est-il un utilisateur
		virtual BOOL isUser() {return false;}
		///Ou une I.A.
		virtual BOOL isAI() {return false;}

		///Obtenir l'ID du joueur
		inline UINT getID() {return m_uID;}

		///Obtenir la position au carreau pres
		inline TOOLS::POINT  getPositionStep() {return m_pPositionStep;}
		///Obtenir la position au pixel pres selon la position au carreau
		inline POINTF getPosition() {return m_pPosition;}
		///Obtenir le niveau ou a ete cree le joueur
		inline STAGE* getStage() {return m_pStage;}

		///Obtenir la puissance des bombes (leur portee)
		inline UINT getRange() {return m_uRange;}
		///Obtenir le nombre des bombes que l'on peut poser
		inline UINT getBomb() {return m_uBomb;}
		///Obtenir la vitesse de deplacement
		inline FLOAT getSpeed() {return m_fSpeed;}

		///Definir la position au carreau pres
		inline VOID setPositionStep(UINT uX, UINT uY) {m_pPositionStep.setX(uX); m_pPositionStep.setY(uY);}
		///Definir la position au pixel pres
		inline VOID setPosition(FLOAT fX, FLOAT fY) {m_pPosition.setX(fX); m_pPosition.setY(fY);}

		///Definir la puissance des bombes
		inline VOID setRange(UINT uRange) {m_uRange = uRange;}
		///Definir le nombre de bombes posables
		inline VOID setBomb(UINT uBomb) {m_uBomb  = uBomb;}
		///Definir la vitesse de deplacement
		inline VOID setSpeed(FLOAT fSpeed) {m_fSpeed = fSpeed;}

		///le joueur va-t-il etre detruit a la prochaine frame ?
		inline BOOL isFinished() {return m_bFinished;}
		///Definir si le joueur va etre detruit a la prochaine frame
		inline VOID setFinished() {m_bFinished=true;}
};

#endif

