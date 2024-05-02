#include "main.h"

UINT BONUS::s_fProbaBonus = 40;
UINT BONUS::s_fProbaFire  = 60;
UINT BONUS::s_fProbaBomb  = 30;
UINT BONUS::s_fProbaSpeed = 10;

BONUS::BONUS(STAGE* pStage, TOOLS::POINT pPosition, TYPE_BONUS tBonus)
{
	m_bFinished=false;

	m_pStage=pStage;
	m_pPosition=pPosition;
	m_tBonus=tBonus;
}

RESULT BONUS::Init()
{
	CHAR pImagePath[] = "resource/image/bonus/";
	CHAR pBonusImageFile[70];

	strcpy(pBonusImageFile,pImagePath);
	switch(m_tBonus)
	{
		case BOMB :
		{
			strcat(pBonusImageFile,"bomb.gif");
			break;
		}
		case FIRE :
		{
			strcat(pBonusImageFile,"fire.gif");
			break;
		}
		case SPEED :
		{
			strcat(pBonusImageFile,"speed.gif");
			break;
		}
		default :
		{
			return ERROR;
		}
	}

	setImage(IMG_Load(pBonusImageFile));

	return OK;
}

RESULT BONUS::FrameMove(INT iTimeElapsed)
{


	return OK;
}

RESULT BONUS::FrameRender(SDL_Surface* & sScreen)
{
	static SDL_Rect rec;	rec.w = TILE_SIZE;  rec.h = TILE_SIZE;
	rec.x = OFFSET_X*TILE_SIZE+getPosition().getX()*TILE_SIZE;  rec.y = OFFSET_Y*TILE_SIZE+getPosition().getY()*TILE_SIZE;

	SDL_BlitSurface(getImage(), 0, sScreen, &rec);

	return OK;
}

RESULT BONUS::Destroy()
{
	SDL_FreeSurface(m_pImage);

	return OK;
}
