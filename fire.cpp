#include "main.h"

RESULT FIRE::Init()
{
	CHAR pImagePath[] = "resource/image/";

	CHAR pFireImageFile[70];
	strcpy(pFireImageFile,pImagePath);

	switch(getDirection())
	{
		case CENTER :
		{
			strcat(pFireImageFile,"fire_center.gif");
			break;
		}
		case UP :
		{
			strcat(pFireImageFile,"fire_up.gif");
			break;
		}
		case DOWN :
		{
			strcat(pFireImageFile,"fire_down.gif");
			break;
		}
		case LEFT :
		{
			strcat(pFireImageFile,"fire_left.gif");
			break;
		}
		case RIGHT :
		{
			strcat(pFireImageFile,"fire_right.gif");
			break;
		}
		case UP_END :
		{
			strcat(pFireImageFile,"fire_up_end.gif");
			break;
		}
		case DOWN_END :
		{
			strcat(pFireImageFile,"fire_down_end.gif");
			break;
		}
		case LEFT_END :
		{
			strcat(pFireImageFile,"fire_left_end.gif");
			break;
		}
		case RIGHT_END :
		{
			strcat(pFireImageFile,"fire_right_end.gif");
			break;
		}
		default :
		{
			return ERROR;
		}
	}

	setImage(IMG_Load(pFireImageFile));
	setLifeTime(400);

	SDL_SetColorKey(getImage(), SDL_SRCCOLORKEY, SDL_MapRGB(getImage()->format, 0, 255, 0));

	return OK;
}

RESULT FIRE::FrameMove(INT iTimeElapsed)
{
	setLifeTime(getLifeTime()-iTimeElapsed);
	if(getLifeTime()<0)
	{
		setFinished();
		if(getStage()->getMap()->getType(getPosition())==MAP::DESTRUCTIBLE)
		{
			getStage()->getMap()->ChangeInPassable(getPosition());
			UINT uRandomNumber1 = UINT(0 + (int)((double)rand() / ((double)RAND_MAX + 1) * 99));
			if(uRandomNumber1<BONUS::s_fProbaBonus)
			{
				BONUS* pBonus = NULL;
				UINT uRandomNumber2 = UINT(0 + (int)((double)rand() / ((double)RAND_MAX + 1) * 99));
				if(uRandomNumber2>=0 && uRandomNumber2<BONUS::s_fProbaFire)
				{
					pBonus = new BONUS(getStage(), getPosition(), BONUS::FIRE);
				}
				else
				{
					if(uRandomNumber2>=BONUS::s_fProbaFire && uRandomNumber2<BONUS::s_fProbaFire+BONUS::s_fProbaBomb)
					{
						pBonus = new BONUS(getStage(), getPosition(), BONUS::BOMB);
					}
					else
					{
						pBonus = new BONUS(getStage(), getPosition(), BONUS::SPEED);
					}
				}
				pBonus->Init();
				getStage()->getBonus()->push_front(pBonus);
			}
		}
	}
	else
	{
		if(getStage()->getBonusByPosition(getPosition()))
		{
			getStage()->getBonusByPosition(getPosition())->setFinished();
		}
		if(getStage()->getBombByPosition(getPosition()))
		{
			getStage()->getBombByPosition(getPosition())->setFinished();
		}
		while(getStage()->getPlayerByPosition(getPosition()) && !getStage()->getPlayerByPosition(getPosition())->isFinished())
		{
			getStage()->getPlayerByPosition(getPosition())->setFinished();
		}
	}

	return OK;
}

RESULT FIRE::FrameRender(SDL_Surface* & sScreen)
{
	static SDL_Rect rec;	rec.w = TILE_SIZE;  rec.h = TILE_SIZE;
	rec.x = OFFSET_X*TILE_SIZE+getPosition().getX()*TILE_SIZE;  rec.y = OFFSET_Y*TILE_SIZE+getPosition().getY()*TILE_SIZE;

	SDL_BlitSurface(getImage(), 0, sScreen, &rec);

	return OK;
}

RESULT FIRE::Destroy()
{
	SDL_FreeSurface(getImage());

	return OK;
}
