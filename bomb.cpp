#include "main.h"

RESULT BOMB::Init()
{
	CHAR pImagePath[] = "resource/image/";

	CHAR pBombImageFile[70];
	strcpy(pBombImageFile,pImagePath);
	strcat(pBombImageFile,"bomb.gif");

	setImage(IMG_Load(pBombImageFile));
	setLifeTime(2000);

	SDL_SetColorKey(getImage(), SDL_SRCCOLORKEY, SDL_MapRGB(getImage()->format, 0, 255, 0));

	m_pBombExplosion = getStage()->m_pBombExplosion;

	return OK;
}

RESULT BOMB::FrameMove(INT iTimeElapsed)
{
	setLifeTime(getLifeTime()-iTimeElapsed);
	if(getLifeTime()<0)
	{
		setFinished();
	}

	if(isFinished())
	{
		FSOUND_PlaySound(FSOUND_FREE, m_pBombExplosion);
		if(getPower()!=0)
		{
			TOOLS::POINT pPosition;
			pPosition.setXY(getPosition().getX(),getPosition().getY());

			FIRE* pFire;

			pFire = new FIRE(getStage(), pPosition, FIRE::CENTER);
			pFire->Init();
			getStage()->getFires()->push_front(pFire);

			for(INT iX=-1;iX>=-INT(getPower());--iX)
			{
				pPosition.setXY(getPosition().getX()+iX,getPosition().getY());

				if(getStage()->getBombByPosition(pPosition)==NULL && getStage()->getMap()->isPassable(pPosition))
				{
					if(iX==-INT(getPower()))
					{
						pFire = new FIRE(getStage(), pPosition, FIRE::LEFT_END);
					}
					else
					{
						pFire = new FIRE(getStage(), pPosition, FIRE::LEFT);
					}
					pFire->Init();
					getStage()->getFires()->push_front(pFire);
				}
				else
				{
					if(getStage()->getBombByPosition(pPosition)!=NULL)
					{
						getStage()->getBombByPosition(pPosition)->setFinished();
					}
					else
					{
						if(getStage()->getMap()->getType(pPosition)==MAP::DESTRUCTIBLE)
						{
							pFire = new FIRE(getStage(), pPosition, FIRE::LEFT_END);
							pFire->Init();
							getStage()->getFires()->push_front(pFire);
						}
					}
					break;
				}
			}

			for(INT iX=1;iX<=INT(getPower());++iX)
			{
				TOOLS::POINT pPosition;
				pPosition.setXY(getPosition().getX()+iX,getPosition().getY());

				if(getStage()->getBombByPosition(pPosition)==NULL && getStage()->getMap()->isPassable(pPosition))
				{
					if(iX==INT(getPower()))
					{
						pFire = new FIRE(getStage(), pPosition, FIRE::RIGHT_END);
					}
					else
					{
						pFire = new FIRE(getStage(), pPosition, FIRE::RIGHT);
					}
					pFire->Init();
					getStage()->getFires()->push_front(pFire);
				}
				else
				{
					if(getStage()->getBombByPosition(pPosition)!=NULL)
					{
						getStage()->getBombByPosition(pPosition)->setFinished();
					}
					else
					{
						if(getStage()->getMap()->getType(pPosition)==MAP::DESTRUCTIBLE)
						{
							pFire = new FIRE(getStage(), pPosition, FIRE::RIGHT_END);
							pFire->Init();
							getStage()->getFires()->push_front(pFire);
						}
					}
					break;
				}
			}

			for(INT iY=-1;iY>=-INT(getPower());--iY)
			{
				pPosition.setXY(getPosition().getX(),getPosition().getY()+iY);

				if(getStage()->getBombByPosition(pPosition)==NULL && getStage()->getMap()->isPassable(pPosition))
				{
					if(iY==-INT(getPower()))
					{
						pFire = new FIRE(getStage(), pPosition, FIRE::UP_END);
					}
					else
					{
						pFire = new FIRE(getStage(), pPosition, FIRE::UP);
					}
					pFire->Init();
					getStage()->getFires()->push_front(pFire);
				}
				else
				{
					if(getStage()->getBombByPosition(pPosition)!=NULL)
					{
						getStage()->getBombByPosition(pPosition)->setFinished();
					}
					else
					{
						if(getStage()->getMap()->getType(pPosition)==MAP::DESTRUCTIBLE)
						{
							pFire = new FIRE(getStage(), pPosition, FIRE::UP_END);
							pFire->Init();
							getStage()->getFires()->push_front(pFire);
						}
					}
					break;
				}
			}

			for(INT iY=1;iY<=INT(getPower());++iY)
			{
				TOOLS::POINT pPosition;
				pPosition.setXY(getPosition().getX(),getPosition().getY()+iY);

				if(getStage()->getBombByPosition(pPosition)==NULL && getStage()->getMap()->isPassable(pPosition))
				{
					if(iY==INT(getPower()))
					{
						pFire = new FIRE(getStage(), pPosition, FIRE::DOWN_END);
					}
					else
					{
						pFire = new FIRE(getStage(), pPosition, FIRE::DOWN);
					}
					pFire->Init();
					getStage()->getFires()->push_front(pFire);
				}
				else
				{
					if(getStage()->getBombByPosition(pPosition)!=NULL)
					{
						getStage()->getBombByPosition(pPosition)->setFinished();
					}
					else
					{
						if(getStage()->getMap()->getType(pPosition)==MAP::DESTRUCTIBLE)
						{
							pFire = new FIRE(getStage(), pPosition, FIRE::DOWN_END);
							pFire->Init();
							getStage()->getFires()->push_front(pFire);
						}
					}
					break;
				}
			}
		}
		getPlayer()->setBomb(getPlayer()->getBomb()+1);
	}

	return OK;
}

RESULT BOMB::FrameRender(SDL_Surface* & sScreen)
{
	static SDL_Rect rec;	rec.w = TILE_SIZE;  rec.h = TILE_SIZE;
	rec.x = OFFSET_X*TILE_SIZE+getPosition().getX()*TILE_SIZE;  rec.y = OFFSET_Y*TILE_SIZE+getPosition().getY()*TILE_SIZE;

	SDL_BlitSurface(getImage(), 0, sScreen, &rec);

	return OK;
}

RESULT BOMB::Destroy()
{
	SDL_FreeSurface(getImage());

	return OK;
}
