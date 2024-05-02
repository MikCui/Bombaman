#ifndef _STAGE_
#define _STAGE_

///Classe STAGE heritant de FRAME, represente un niveau solo ou multi
class STAGE : public FRAME
{
	public :

		///le type de jeu SCENARIO = solo, RANDOM = multi
		typedef enum TYPE_GAME
		{
			RANDOM = 0,
			SCENARIO
		};

		///la musique d'ambiance
		FMUSIC_MODULE* m_pMusic;
		///le son emit dans le cas ou une bombe explose
		FSOUND_SAMPLE* m_pBombExplosion;

	private :

		///le type du jeu
		TYPE_GAME m_tGame;
		///le type de terrain
		MAP::TYPE_TERRAIN m_tTerrain;
		///le numero du niveau
		INT m_iStage;
		///le temps restant avant de changer de frame
		INT m_iFadeOutTime;
		///l'image de la bar des scores
		SDL_Surface* m_pScoreBar;
		///l'image affichant "Vies :"
		SDL_Surface* m_pLifeTitle;
		///l'image representant une vie
		SDL_Surface* m_pLifeNumber;
		///la carte du niveau
		MAP m_mMap;
		///la liste des joueurs dans le niveau
		list<PLAYER*> m_lPlayers;
		///la liste des bonus
		list<BONUS*> m_lBonus;
		///la liste des bombes
		list<BOMB*> m_lBombs;
		///la liste des flammes
		list<FIRE*> m_lFires;

	public :

		///Le constructeur n°1 de la classe STAGE
		STAGE(TYPE_GAME tGame, MAP::TYPE_TERRAIN tTerrain);
		///Le constructeur n°2 de la classe STAGE
		STAGE(TYPE_GAME tGame, MAP::TYPE_TERRAIN tTerrain, INT iStage);
		///Le destructeur de la classe STAGE
		~STAGE();
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

		///donne la frame a traiter apres celle-ci
		virtual FRAME* NextFrame();

		///Obtenir le type de jeu
		TYPE_GAME getGameType() {return m_tGame;}
		///Obtenir le type de terrain
		MAP::TYPE_TERRAIN getTerrain() {return m_tTerrain;}

		///Obtenir la carte
		MAP* getMap() {return &m_mMap;}
		///Obtenir la liste des joueurs
		list<PLAYER*>* getPlayers() {return &m_lPlayers;}
		///Obtenir la liste des bonus
		list<BONUS*>* getBonus() {return &m_lBonus;}
		///Obtenir la liste des bombes
		list<BOMB*>* getBombs() {return &m_lBombs;}
		///Obtenir la liste des flammes
		list<FIRE*>* getFires() {return &m_lFires;}

		///Obtenir le premier joueur a une certaine position
		PLAYER* getPlayerByPosition(TOOLS::POINT pPosition);
		///Obtenir le premier joueur humain a une certaine position
		PLAYER* getUserByPosition(TOOLS::POINT pPosition);
		///Obtenir le bonus situee a une certaine position
		BONUS* getBonusByPosition(TOOLS::POINT pPosition);
		///Obtenir la bombe situee a une certaine position
		BOMB* getBombByPosition(TOOLS::POINT pPosition);
};

#endif
