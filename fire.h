#ifndef _FIRE_
#define _FIRE_

///Classe FIRE, utilisee au moment de l'explosion d'une bombe
class FIRE
{
	public :

		///la direction de la flamme
		typedef enum DIRECTION
		{
			CENTER = 0,
			UP,
			DOWN,
			LEFT,
			RIGHT,
			UP_END,
			DOWN_END,
			LEFT_END,
			RIGHT_END
		};

	private :

		///le niveau ou la flamme a ete cree
		STAGE* m_pStage;
		///la flamme va-t-elle etre detruire a la prochaine frame (prochain cycle [framemove/framerender])
		BOOL m_bFinished;
		///la position de la flamme
		TOOLS::POINT m_pPosition;
		///sa duree de vie
		INT m_iLifeTime;
		///sa direction
		DIRECTION m_dDirection;
		///son image
		SDL_Surface* m_pImage;

	public :

		///Le constructeur de la classe FIRE
		FIRE(STAGE* pStage, TOOLS::POINT pPosition, DIRECTION dDirection) {m_bFinished=false;m_pStage=pStage;m_pPosition=pPosition;m_dDirection=dDirection;}
		///Le destructeur de la classe FIRE
		~FIRE() {}

		///Initialisation
		RESULT Init();
		///Animation
		RESULT FrameMove(INT iTimeElapsed);
		///Affichage
		RESULT FrameRender(SDL_Surface* & sScreen);
		///Destruction
		RESULT Destroy();

		///Obtenir la position
		inline  TOOLS::POINT getPosition() {return m_pPosition;}
		///Obtenir la duree de vie
		inline  INT getLifeTime() {return m_iLifeTime;}
		///Obtenir la direction
		inline  DIRECTION getDirection() {return m_dDirection;}
		///Obtenir l'image
		inline  SDL_Surface* getImage() {return m_pImage;}
		///Obtenir le niveau
		inline  STAGE* getStage() {return m_pStage;}

		///Definir la position
		inline  VOID setPosition(UINT uX, UINT uY) {m_pPosition.setX(uX); m_pPosition.setY(uY);}
		///Definir la duree de vie
		inline  VOID setLifeTime(INT iLifeTime) {m_iLifeTime=iLifeTime;}
		///Definir l'image
		inline  VOID setImage(SDL_Surface* pImage) {m_pImage=pImage;}
		///Definir la direction
		inline  VOID setDirection(DIRECTION dDirection) {m_dDirection=dDirection;}

		///la flamme va-t-elle etre detruite
		inline BOOL isFinished() {return m_bFinished;}
		///Definir si la flamme doit etre detruite
		inline VOID setFinished() {m_bFinished=true;}
};

#endif
