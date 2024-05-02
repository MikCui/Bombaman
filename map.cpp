#include "main.h"

vector<SDL_Surface*> MAP::TILE::s_sImage;

RESULT MAP::TILE::FrameRender(SDL_Surface* & sScreen, TOOLS::POINT & pPosition)
{
	SDL_Rect rec;   rec.x = pPosition.getX()*TILE_SIZE;  rec.y = pPosition.getY()*TILE_SIZE;
	rec.w = TILE_SIZE;  rec.h = TILE_SIZE;
	SDL_BlitSurface(m_pImage, 0, sScreen, &rec);

	return OK;
}

MAP::MAP()
{

}

MAP::~MAP()
{

}

RESULT MAP::Init(STAGE* pStage, TYPE_TERRAIN tTerrain, CHAR* pFilename)
{
	m_pStage		  = pStage;
	m_tTerrain		= tTerrain;

	CHAR pTerrainDir[50];

	switch(m_tTerrain)
	{
		default :
		{
			return ERROR;
		}
		case GREENLAND :
		{
			strcpy(pTerrainDir,"greenland");
			break;
		}
		case SNOWLAND :
		{
			strcpy(pTerrainDir,"snowland");
			break;
		}
		case FIRELAND :
		{
			strcpy(pTerrainDir,"fireland");
			break;
		}
		case FREELAND :
		{
			strcpy(pTerrainDir,"freeland");
			break;
		}
	}

	CHAR pImagePath[] = "resource/image/map/";

	CHAR pPassableImageFile[70];
	strcpy(pPassableImageFile,pImagePath);
	strcat(pPassableImageFile,pTerrainDir);
	strcat(pPassableImageFile,"/passable.gif");

	CHAR pPassableShadowImageFile[70];
	strcpy(pPassableShadowImageFile,pImagePath);
	strcat(pPassableShadowImageFile,pTerrainDir);
	strcat(pPassableShadowImageFile,"/passable_shadow.gif");

	CHAR pDestructibleImageFile[70];
	strcpy(pDestructibleImageFile,pImagePath);
	strcat(pDestructibleImageFile,pTerrainDir);
	strcat(pDestructibleImageFile,"/destructible.gif");

	CHAR pIndestructibleImageFile[70];
	strcpy(pIndestructibleImageFile,pImagePath);
	strcat(pIndestructibleImageFile,pTerrainDir);
	strcat(pIndestructibleImageFile,"/indestructible.gif");

	CHAR pLinkedImageFile[70];
	strcpy(pLinkedImageFile,pImagePath);
	strcat(pLinkedImageFile,pTerrainDir);
	strcat(pLinkedImageFile,"/linked.gif");

	CHAR pEndImageFile[70];
	strcpy(pEndImageFile,pImagePath);
	strcat(pEndImageFile,pTerrainDir);
	strcat(pEndImageFile,"/end.gif");

	CHAR pBorderImageFile[70];
	strcpy(pBorderImageFile,pImagePath);
	strcat(pBorderImageFile,pTerrainDir);
	strcat(pBorderImageFile,"/border.gif");

	TILE::s_sImage.push_back(IMG_Load(pPassableImageFile));
	TILE::s_sImage.push_back(IMG_Load(pPassableShadowImageFile));
	TILE::s_sImage.push_back(IMG_Load(pDestructibleImageFile));
	TILE::s_sImage.push_back(IMG_Load(pIndestructibleImageFile));
	TILE::s_sImage.push_back(IMG_Load(pLinkedImageFile));
	TILE::s_sImage.push_back(IMG_Load(pEndImageFile));
	TILE::s_sImage.push_back(IMG_Load(pBorderImageFile));

	if(pFilename==NULL)
	{
		srand(UINT(time(NULL)));

		//Generer la carte
		for(UINT y=0;y<MAP_HEIGHT;y++)
		{
			for(UINT x=0;x<MAP_WIDTH;x++)
			{
				if(x==MAP_WIDTH-1 || y==MAP_HEIGHT-1 || x==0 || y==0 || (x%2==0 && y%2==0))
				{
					m_mMap[x][y].setType(INDESTRUCTIBLE);
					if(x==MAP_WIDTH-1 || y==MAP_HEIGHT-1 || x==0 || y==0)
					{
						m_mMap[x][y].setImage(TILE::s_sImage[BORDER]);
					}
					else
					{
						m_mMap[x][y].setImage(TILE::s_sImage[INDESTRUCTIBLE]);
					}
				}
				else
				{
					int iRandomNumber = 0 + (int)((double)rand() / ((double)RAND_MAX + 1) * 99);
					if(!((x==1 && y==1) || (x==2 && y==1) || (x==1 && y==2)) &&
					   !((x==MAP_WIDTH-2 && y==1) || (x==MAP_WIDTH-3 && y==1) || (x==MAP_WIDTH-2 && y==2)) &&
					   !((x==MAP_WIDTH-2 && y==MAP_HEIGHT-2) || (x==MAP_WIDTH-3 && y==MAP_HEIGHT-2) || (x==MAP_WIDTH-2 && y==MAP_HEIGHT-3)) &&
					   !((x==1 && y==MAP_HEIGHT-2) || (x==2 && y==MAP_HEIGHT-2) || (x==1 && y==MAP_HEIGHT-3)) &&
					   iRandomNumber<90)
					{
						m_mMap[x][y].setType(DESTRUCTIBLE);
						m_mMap[x][y].setImage(TILE::s_sImage[DESTRUCTIBLE]);
					}
					else
					{
						if(y>0 && (m_mMap[x][y-1].getType()==DESTRUCTIBLE || m_mMap[x][y-1].getType()==INDESTRUCTIBLE))
						{
							m_mMap[x][y].setType(PASSABLE);
							m_mMap[x][y].setImage(TILE::s_sImage[PASSABLE_SHADOW]);
						}
						else
						{
							m_mMap[x][y].setType(PASSABLE);
							m_mMap[x][y].setImage(TILE::s_sImage[PASSABLE]);
						}
					}
				}
			}
		}
	}
	else
	{
		INT iTileType;

		FILE * pFile = fopen(pFilename,"r");

		for(UINT y=0;y<MAP_HEIGHT;y++)
		{
			for(UINT x=0;x<MAP_WIDTH;x++)
			{
				fscanf (pFile, "%i;", &iTileType);

				switch(iTileType)
				{
					case MAP::PASSABLE :
					{
						if(y>0 && (m_mMap[x][y-1].getType()==DESTRUCTIBLE || m_mMap[x][y-1].getType()==INDESTRUCTIBLE))
						{
							m_mMap[x][y].setImage(TILE::s_sImage[PASSABLE_SHADOW]);
						}
						else
						{
							m_mMap[x][y].setImage(TILE::s_sImage[PASSABLE]);
						}
						m_mMap[x][y].setType(PASSABLE);

						break;
					}
					case MAP::DESTRUCTIBLE :
					{
						m_mMap[x][y].setImage(TILE::s_sImage[MAP::DESTRUCTIBLE]);
						m_mMap[x][y].setType(MAP::DESTRUCTIBLE);

						break;
					}
					case MAP::INDESTRUCTIBLE :
					{
						m_mMap[x][y].setType(INDESTRUCTIBLE);
						if(x==MAP_WIDTH-1 || y==MAP_HEIGHT-1 || x==0 || y==0)
						{
							m_mMap[x][y].setImage(TILE::s_sImage[BORDER]);
						}
						else
						{
							m_mMap[x][y].setImage(TILE::s_sImage[INDESTRUCTIBLE]);
						}

						break;
					}
					case MAP::LINKED :
					{
						m_mMap[x][y].setImage(TILE::s_sImage[MAP::LINKED]);
						m_mMap[x][y].setType(MAP::LINKED);

						break;
					}
					case MAP::END :
					{
						m_mMap[x][y].setImage(TILE::s_sImage[MAP::INDESTRUCTIBLE]);
						m_mMap[x][y].setType(MAP::INDESTRUCTIBLE);
						TOOLS::POINT pPoint; pPoint.setXY(x,y);
						setEnd(pPoint);

						break;
					}
					case MAP::PLAYER :
					{
						if(y>0 && (m_mMap[x][y-1].getType()==DESTRUCTIBLE || m_mMap[x][y-1].getType()==INDESTRUCTIBLE))
						{
							m_mMap[x][y].setImage(TILE::s_sImage[PASSABLE_SHADOW]);
						}
						else
						{
							m_mMap[x][y].setImage(TILE::s_sImage[PASSABLE]);
						}
						m_mMap[x][y].setType(PASSABLE);

						USER* pPlayer;
						pPlayer = new USER(getStage());
						pPlayer->m_pPositionStep.setXY(x,y);
						getStage()->getPlayers()->push_back(pPlayer);

						break;
					}
					case MAP::MONSTER :
					{
						if(y>0 && (m_mMap[x][y-1].getType()==DESTRUCTIBLE || m_mMap[x][y-1].getType()==INDESTRUCTIBLE))
						{
							m_mMap[x][y].setImage(TILE::s_sImage[PASSABLE_SHADOW]);
						}
						else
						{
							m_mMap[x][y].setImage(TILE::s_sImage[PASSABLE]);
						}
						m_mMap[x][y].setType(PASSABLE);

						AI* pPlayer;
						TOOLS::POINT pPosition = TOOLS::POINT(x,y);
						pPlayer = new AI(getStage(),m_tTerrain,pPosition);
						pPlayer->m_pPositionStep.setXY(x,y);
						getStage()->getPlayers()->push_back(pPlayer);

						break;
					}
					case MAP::BOSS :
					{
						if(y>0 && (m_mMap[x][y-1].getType()==DESTRUCTIBLE || m_mMap[x][y-1].getType()==INDESTRUCTIBLE))
						{
							m_mMap[x][y].setImage(TILE::s_sImage[PASSABLE_SHADOW]);
						}
						else
						{
							m_mMap[x][y].setImage(TILE::s_sImage[PASSABLE]);
						}
						m_mMap[x][y].setType(PASSABLE);

						break;
					}
				}
			}
		}

		fclose (pFile);
	}

	return OK;
}

RESULT MAP::FrameMove(INT iTimeElapsed)
{


	return OK;
}

RESULT MAP::FrameRender(SDL_Surface* sScreen)
{
	static TOOLS::POINT pPosition;
	for(UINT y=0;y<MAP_HEIGHT;y++)
	{
		for(UINT x=0;x<MAP_WIDTH;x++)
		{
			pPosition.setXY(x+OFFSET_X,y+OFFSET_Y);
			m_mMap[x][y].FrameRender(sScreen,pPosition);
		}
	}

	return OK;
}

RESULT MAP::Destroy()
{
	vector<SDL_Surface*>::iterator itImage;
	for(itImage=TILE::s_sImage.begin();itImage!=TILE::s_sImage.end();++itImage)
	{
		SDL_FreeSurface((*itImage));
	}
	TILE::s_sImage.clear();

	return OK;
}
