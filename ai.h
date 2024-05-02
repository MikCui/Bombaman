#ifndef _AI_
#define _AI_

/// Classe AI (Intelligence Artificielle), heritant de la classe Player (Joueur)
class AI : public PLAYER
{
	private :

		/// Le type de terrain, vu que l'image representant le monstre est en fonction du terrain
		MAP::TYPE_TERRAIN m_tTerrain;
		UINT m_uDirection;

	public :

		/// Constructeur de la classe AI
		AI(STAGE* pStage, MAP::TYPE_TERRAIN tTerrain, TOOLS::POINT pPosition) : PLAYER(pStage){m_tTerrain=tTerrain;m_pPosition.setXY(pPosition.getX(),pPosition.getY());}
		/// Destructeur de la classe AI
		~AI() {}

		/// Initialisation
		virtual RESULT Init();
		/// Gestion des entrees
		virtual RESULT Input(TOOLS::INPUT* iInput);
		/// Animation
		virtual RESULT FrameMove(INT iTimeElapsed);
		/// Affichage
		virtual RESULT FrameRender(SDL_Surface* & sScreen);
		/// Destruction
		virtual RESULT Destroy();

		/// Ce joueur est-il une IA ? Oui
		virtual BOOL isAI() {return true;}

		/// Obtenir la direction dans laquelle se dirige l'IA
		inline	UINT getDirection() {return m_uDirection;}

		/// Definir la direction dans laquelle se dirige l'IA
		inline	VOID setDirection(UINT uDirection) {m_uDirection=uDirection;}

};

#endif
