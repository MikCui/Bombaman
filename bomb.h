#ifndef _BOMB_
#define _BOMB_

/// Classe BOMB, represente les bombes posees par les joueurs
class BOMB
{
	private :

		/// Le niveau ou est posee la bombe
		STAGE* m_pStage;
		/// Le joueur l'ayant posee
		PLAYER* m_pPlayer;
		/// La bombe existe-t-elle encore ou va-t-elle etre detruite
		BOOL m_bFinished;
		/// La position de la bombe
		TOOLS::POINT m_pPosition;
		/// Le temps qu'il lui reste avant d'exploser
		INT m_iLifeTime;
		/// La puissance de la bombe
		UINT m_uPower;
		/// L'image la representant
		SDL_Surface* m_pImage;
		/// Le son jouee au moment de l'explosion
		FSOUND_SAMPLE* m_pBombExplosion;

	public :

		/// Le constructeur de la class BOMB
		BOMB(STAGE* pStage, PLAYER* pPlayer, TOOLS::POINT pPosition, UINT uPower) {m_bFinished=false;m_pStage=pStage;m_pPlayer=pPlayer;m_pPosition=pPosition;m_uPower=uPower;}
		/// Le destructeur de la class BOMB
		~BOMB() {}

		/// Initialisation
		RESULT Init();
		/// Animation
		RESULT FrameMove(INT iTimeElapsed);
		/// Affichage
		RESULT FrameRender(SDL_Surface* & sScreen);
		/// Destruction
		RESULT Destroy();

		/// Obtenir la position de la bombe
		inline  TOOLS::POINT getPosition() {return m_pPosition;}
		/// Obtenir le temps avant son explosion
		inline  INT getLifeTime() {return m_iLifeTime;}
		/// Obtenir sa puissance
		inline  UINT getPower() {return m_uPower;}
		/// Obtenir son image
		inline  SDL_Surface* getImage() {return m_pImage;}
		/// Obtenir le niveau ou elle a ete cree
		inline  STAGE* getStage() {return m_pStage;}
		/// Obtenir le joueur qui l'a cree
		inline  PLAYER* getPlayer() {return m_pPlayer;}

		/// Definir la position de la bombe
		inline  VOID setPosition(UINT uX, UINT uY) {m_pPosition.setX(uX); m_pPosition.setY(uY);}
		/// Definir son temps de vie
		inline  VOID setLifeTime(INT iLifeTime) {m_iLifeTime=iLifeTime;}
		/// Definir sa puissance
		inline  VOID setPower(UINT uPower) {m_uPower=uPower;}
		/// Definir son image
		inline  VOID setImage(SDL_Surface* pImage) {m_pImage=pImage;}

		/// A-t-elle explosee ?
		inline BOOL isFinished() {return m_bFinished;}
		/// Definir si la bombe a explosee
		inline VOID setFinished() {m_bFinished=true;}
};

#endif
