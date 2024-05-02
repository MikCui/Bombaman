#include "main.h"

UINT USER::s_uNumUser = 0;

RESULT USER::Init()
{
	PLAYER::Init();

	CHAR pImagePath[] = "resource/image/character/";

	CHAR pUpImageFile[70];
	CHAR pDownImageFile[70];
	CHAR pLeftImageFile[70];
	CHAR pRightImageFile[70];

	strcpy(pUpImageFile,pImagePath);
	strcpy(pDownImageFile,pImagePath);
	strcpy(pLeftImageFile,pImagePath);
	strcpy(pRightImageFile,pImagePath);

	switch(getID())
	{
		default:
		case 0 :
		{
			if(getStage()->getGameType()==STAGE::RANDOM) m_pPositionStep.setXY(1,1);
			m_sControllers[UP]=SDLK_UP;
			m_sControllers[DOWN]=SDLK_DOWN;
			m_sControllers[LEFT]=SDLK_LEFT;
			m_sControllers[RIGHT]=SDLK_RIGHT;
			m_sControllers[PLANT_BOMB]=SDLK_RCTRL;
			m_sControllers[SPECIAL]=SDLK_RSHIFT;

			strcat(pUpImageFile,"boby.gif");
			strcat(pDownImageFile,"boby.gif");
			strcat(pLeftImageFile,"boby.gif");
			strcat(pRightImageFile,"boby.gif");

			break;
		}
		case 1 :
		{
			if(getStage()->getGameType()==STAGE::RANDOM) m_pPositionStep.setXY(MAP_WIDTH-2,1);
			m_sControllers[UP]=SDLK_w;
			m_sControllers[DOWN]=SDLK_s;
			m_sControllers[LEFT]=SDLK_a;
			m_sControllers[RIGHT]=SDLK_d;
			m_sControllers[PLANT_BOMB]=SDLK_LCTRL;
			m_sControllers[SPECIAL]=SDLK_LSHIFT;

			strcat(pUpImageFile,"sohene.gif");
			strcat(pDownImageFile,"sohene.gif");
			strcat(pLeftImageFile,"sohene.gif");
			strcat(pRightImageFile,"sohene.gif");

			break;
		}
		case 2 :
		{
			if(getStage()->getGameType()==STAGE::RANDOM) m_pPositionStep.setXY(MAP_WIDTH-2,MAP_HEIGHT-2);
			m_sControllers[UP]=SDLK_i;
			m_sControllers[DOWN]=SDLK_k;
			m_sControllers[LEFT]=SDLK_j;
			m_sControllers[RIGHT]=SDLK_l;
			m_sControllers[PLANT_BOMB]=SDLK_h;
			m_sControllers[SPECIAL]=SDLK_y;

			strcat(pUpImageFile,"nix.gif");
			strcat(pDownImageFile,"nix.gif");
			strcat(pLeftImageFile,"nix.gif");
			strcat(pRightImageFile,"nix.gif");

			break;
		}
		case 3 :
		{
			if(getStage()->getGameType()==STAGE::RANDOM) m_pPositionStep.setXY(1,MAP_HEIGHT-2);
			m_sControllers[UP]=SDLK_KP8;
			m_sControllers[DOWN]=SDLK_KP5;
			m_sControllers[LEFT]=SDLK_KP4;
			m_sControllers[RIGHT]=SDLK_KP6;
			m_sControllers[PLANT_BOMB]=SDLK_KP0;
			m_sControllers[SPECIAL]=SDLK_KP1;

			strcat(pUpImageFile,"jarod.gif");
			strcat(pDownImageFile,"jarod.gif");
			strcat(pLeftImageFile,"jarod.gif");
			strcat(pRightImageFile,"jarod.gif");

			break;
		}
	}

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

RESULT USER::Input(TOOLS::INPUT* iInput)
{
	for(UINT uIteration=0;uIteration<6;++uIteration)
	{
		if(uIteration==PLANT_BOMB)
		{
			if(iInput[m_sControllers[uIteration]]==CLICK) m_bActions[uIteration]=true;
			else m_bActions[uIteration]=false;
		}
		else
		{
			if(iInput[m_sControllers[uIteration]]==CLICK || iInput[m_sControllers[uIteration]]==PRESSED) m_bActions[uIteration]=true;
			else m_bActions[uIteration]=false;
		}
	}

	return OK;
}

RESULT USER::FrameMove(INT iTimeElapsed)
{
	PLAYER::FrameMove(iTimeElapsed);

	return OK;
}

RESULT USER::FrameRender(SDL_Surface* & sScreen)
{
	PLAYER::FrameRender(sScreen);

	return OK;
}

RESULT USER::Destroy()
{
	PLAYER::Destroy();

	return OK;
}
