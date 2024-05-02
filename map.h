#ifndef _MAP_
#define _MAP_

///Classe MAP, representant une carte
class MAP
{
	public :

		///les differents types de terrains
		typedef enum TYPE_TERRAIN
		{
			GREENLAND = 0,
			SNOWLAND,
			FIRELAND,
			SWAMPLAND,
			FREELAND
		};

		///les differents types de carreaux composants les carte
		typedef enum TYPE_TILE
		{
			PASSABLE = 0,
			PASSABLE_SHADOW,
			DESTRUCTIBLE,
			INDESTRUCTIBLE,
			LINKED,
			END,
			BORDER,
			PLAYER,
			MONSTER,
			BOSS
		};

	private :

		///Classe TILE, representant un carreau d'une carte
		class TILE
		{
			private :
				///le type du carreau
				TYPE_TILE			   m_tType;
				///son image
				SDL_Surface*			m_pImage;

			public :

				///toutes les images des carreaux pour ne pas avoir a les recharger pour chaque carreau
				static vector<SDL_Surface*> s_sImage;

				///Affichage du carreau
				RESULT FrameRender(SDL_Surface* & sScreen, TOOLS::POINT & pPosition);

				///Obtenir le type du carreau
				inline TYPE_TILE	   getType()					   {return m_tType;}
				///Obtenir son image
				inline SDL_Surface*	getImage()					  {return m_pImage;}
				///Definir son type
				inline VOID			setType(TYPE_TILE tType)		{m_tType=tType;}
				///Definir son image
				inline VOID			setImage(SDL_Surface* pImage)   {m_pImage=pImage;}
		};

		///le niveau ou la carte a ete cree
		STAGE*				 m_pStage;
		///la carte en elle meme, un tableau de carreaux
		TILE				 m_mMap[MAP_WIDTH][MAP_HEIGHT];
		///le type de terrain
		TYPE_TERRAIN		 m_tTerrain;
		///le point ou sera situe la sortie quand tous les monstres auront ete elimines dans le cas d'un jeu en solo
		TOOLS::POINT				 m_pEnd;

	public :

		MAP();
		~MAP();
		RESULT Init(STAGE* pStage, TYPE_TERRAIN tTerrain, CHAR* pFilename);
		///Animation
		RESULT FrameMove(INT iTimeElapsed);
		///Affichage
		RESULT FrameRender(SDL_Surface* sScreen);
		///Destruction
		RESULT Destroy();

		inline BOOL isPassable(UINT uX, UINT uY)   {return (m_mMap[uX][uY].getType()==PASSABLE || m_mMap[uX][uY].getType()==END);}
		inline BOOL isPassable(TOOLS::POINT pPosition)	{return (m_mMap[pPosition.getX()][pPosition.getY()].getType()==PASSABLE || m_mMap[pPosition.getX()][pPosition.getY()].getType()==END);}
		inline TYPE_TILE getType(TOOLS::POINT pPosition)  {return m_mMap[pPosition.getX()][pPosition.getY()].getType();}
		inline TOOLS::POINT getEnd()					   {return m_pEnd;}
		inline STAGE* getStage()				   {return m_pStage;}

		inline VOID setEnd(const TOOLS::POINT& pPosition) {m_pEnd=pPosition;}

		VOID ChangeInPassable(TOOLS::POINT pPosition)
		{
			m_mMap[pPosition.getX()][pPosition.getY()].setType(PASSABLE);
			if(pPosition.getY()>0 && isPassable(pPosition.getX(),pPosition.getY()-1))
			{
				m_mMap[pPosition.getX()][pPosition.getY()].setImage(TILE::s_sImage[PASSABLE]);
			}
			else
			{
				m_mMap[pPosition.getX()][pPosition.getY()].setImage(TILE::s_sImage[PASSABLE_SHADOW]);
			}

			if(pPosition.getY()<(MAP_HEIGHT-1) && isPassable(pPosition.getX(),pPosition.getY()+1))
			{
				m_mMap[pPosition.getX()][pPosition.getY()+1].setImage(TILE::s_sImage[PASSABLE]);
			}
		}

		VOID ShowExit()
		{
			m_mMap[getEnd().getX()][getEnd().getY()].setImage(TILE::s_sImage[END]);
			m_mMap[getEnd().getX()][getEnd().getY()].setType(END);
		}
};

#endif
