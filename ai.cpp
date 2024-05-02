#include "main.h"

RESULT AI::Init()
{
	PLAYER::Init();

	srand(UINT(time(NULL)));
	UINT uDirection = UINT(0 + (int)((double)rand() / ((double)RAND_MAX + 1) * 3));
	setDirection(uDirection);

	CHAR pImagePath[70];
	switch(getStage()->getTerrain())
	{
		case MAP::GREENLAND :
		{
			strcpy(pImagePath,"resource/image/map/greenland/");
			break;
		}
		case MAP::SNOWLAND :
		{
			strcpy(pImagePath,"resource/image/map/snowland/");
			break;
		}
		case MAP::FIRELAND :
		{
			strcpy(pImagePath,"resource/image/map/fireland/");
			break;
		}
		default:
		{
			return ERROR;
		}
	}

	CHAR pUpImageFile[70];
	CHAR pDownImageFile[70];
	CHAR pLeftImageFile[70];
	CHAR pRightImageFile[70];

	strcpy(pUpImageFile,pImagePath);
	strcpy(pDownImageFile,pImagePath);
	strcpy(pLeftImageFile,pImagePath);
	strcpy(pRightImageFile,pImagePath);

	strcat(pUpImageFile,"monster.gif");
	strcat(pDownImageFile,"monster.gif");
	strcat(pLeftImageFile,"monster.gif");
	strcat(pRightImageFile,"monster.gif");

	m_pCharacters[UP]=IMG_Load(pUpImageFile);
	m_pCharacters[DOWN]=IMG_Load(pDownImageFile);
	m_pCharacters[LEFT]=IMG_Load(pLeftImageFile);
	m_pCharacters[RIGHT]=IMG_Load(pRightImageFile);

	SDL_SetColorKey(m_pCharacters[UP], SDL_SRCCOLORKEY, SDL_MapRGB( m_pCharacters[UP]->format, 0, 255, 0));
	SDL_SetColorKey(m_pCharacters[DOWN], SDL_SRCCOLORKEY, SDL_MapRGB( m_pCharacters[UP]->format, 0, 255, 0));
	SDL_SetColorKey(m_pCharacters[LEFT], SDL_SRCCOLORKEY, SDL_MapRGB( m_pCharacters[UP]->format, 0, 255, 0));
	SDL_SetColorKey(m_pCharacters[RIGHT], SDL_SRCCOLORKEY, SDL_MapRGB( m_pCharacters[UP]->format, 0, 255, 0));

	return OK;
}

RESULT AI::Input(TOOLS::INPUT* iInput)
{
	TOOLS::POINT pPosition = TOOLS::POINT(getPositionStep().getX()-m_bActions[LEFT]+m_bActions[RIGHT],getPositionStep().getY()-m_bActions[UP]+m_bActions[DOWN]);
	if((getPosition().getX()==0 && getPosition().getY()==0))
	{
		for(UINT uIteration=0;uIteration<6;++uIteration)
		{
			m_bActions[uIteration]=false;
		}
		UINT uDirection = UINT(0 + (int)((double)rand() / ((double)RAND_MAX + 1) * 4));
		setDirection(uDirection);
		m_bActions[getDirection()]=true;
	}

	return OK;
}

RESULT AI::FrameMove(INT iTimeElapsed)
{
	PLAYER::FrameMove(iTimeElapsed);

	if(getStage()->getUserByPosition(getPositionStep()))
	{
		getStage()->getUserByPosition(getPositionStep())->setFinished();
	}

	return OK;
}

RESULT AI::FrameRender(SDL_Surface* & sScreen)
{
	PLAYER::FrameRender(sScreen);

	return OK;
}

RESULT AI::Destroy()
{
	PLAYER::Destroy();

	return OK;
}
