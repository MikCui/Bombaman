#ifndef _BONUS_
#define _BONUS_

/// Classe BONUS, represente les bonus generes sur le carte
class BONUS
{
	public :

		/// les differents type de bonus, + de bombes, + de puissance de feu, + de vitesse de deplacement
		typedef enum TYPE_BONUS
		{
			BOMB = 0,
			FIRE,
			SPEED,
		};

		/// la probabilite pour qu'une brique cache un bonus
		static UINT s_fProbaBonus;
		/// la proba pour qu'un bonus soit un bonus de bombe
		static UINT s_fProbaBomb;
		/// la proba pour qu'un bonus soit un bonus de puissace
		static UINT s_fProbaFire;
		/// la proba pour qu'un bonus soit un bonus de vitesse
		static UINT s_fProbaSpeed;

	private :

		/// le niveau d'ou est cree le bonus
		STAGE* m_pStage;
		/// le bonus va-t-il etre detruit ?
		BOOL m_bFinished;
		/// l'image representant le bonus
		SDL_Surface* m_pImage;
		/// le type du bonus
		TYPE_BONUS m_tBonus;
		/// sa position
		TOOLS::POINT m_pPosition;

	public :

		/// Le constructeur de la classe BONUS
		BONUS(STAGE* pStage, TOOLS::POINT pPosition, TYPE_BONUS tBonus);
		/// Le destructeur de la classe BONUS
		~BONUS() {}

		/// Initialisation
		RESULT Init();
		/// Animation
		RESULT FrameMove(INT iTimeElapsed);
		/// Affichage
		RESULT FrameRender(SDL_Surface* & sScreen);
		/// Destruction
		RESULT Destroy();

		/// Obtenir la position du bonus
		inline TOOLS::POINT getPosition() {return m_pPosition;}
		/// Obtenir son type
		inline TYPE_BONUS getType() {return m_tBonus;}
		/// Obtenir son image
		inline SDL_Surface* getImage() {return m_pImage;}
		/// Obtenir le niveau d'ou il a ete cree
		inline STAGE* getStage() {return m_pStage;}
		/// Obtenir l'etat du bonus : s'il va etre detruit a la prochaine frame
		inline BOOL isFinished() {return m_bFinished;}

		///Definir la position
		inline VOID setPosition(UINT uX, UINT uY) {m_pPosition.setX(uX); m_pPosition.setY(uY);}
		///Definir l'etat
		inline VOID setFinished() {m_bFinished=true;}
		///Definir l'image
		inline VOID setImage(SDL_Surface* pImage) {m_pImage=pImage;}
};

#endif
