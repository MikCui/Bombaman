#include "main.h"

BUTTON::BUTTON(INT iName, const SDL_Rect& rRect)
{
	m_iName = iName;
	m_rRect = rRect;
}

BUTTON::~BUTTON()
{

}

RESULT BUTTON::Init()
{
	CHAR pImagePath[] = "resource/image/menu/";
	CHAR pImageFile[70];
	strcpy(pImageFile,pImagePath);

	switch(m_iName)
	{
		case SCENARIO :
		{
			strcat(pImageFile,"/scenario.gif");

			break;
		}
		case ARENA :
		{
			strcat(pImageFile,"/arena.gif");

			break;
		}
		case EXIT :
		{
			strcat(pImageFile,"/exit.gif");

			break;
		}
		case EASY :
		{
			strcat(pImageFile,"/easy.gif");

			break;
		}
		case AVERAGE :
		{
			strcat(pImageFile,"/average.gif");

			break;
		}
		case HARD :
		{
			strcat(pImageFile,"/hard.gif");

			break;
		}
		case ONE_PLAYER :
		{
			strcat(pImageFile,"/one_player.gif");

			break;
		}
		case TWO_PLAYER :
		{
			strcat(pImageFile,"/two_player.gif");

			break;
		}
		case THREE_PLAYER :
		{
			strcat(pImageFile,"/three_player.gif");

			break;
		}
		case FOUR_PLAYER :
		{
			strcat(pImageFile,"/four_player.gif");

			break;
		}
		case GREENLAND :
		{
			strcat(pImageFile,"/greenland.gif");

			break;
		}
		case SNOWLAND :
		{
			strcat(pImageFile,"/snowland.gif");

			break;
		}
		case FIRELAND :
		{
			strcat(pImageFile,"/fireland.gif");

			break;
		}
		default :
		{
			return ERROR;
		}
	}

	m_pImage = IMG_Load(pImageFile);

	return OK;
}

RESULT BUTTON::FrameMove(INT iTimeElapsed)
{


	return OK;
}

RESULT BUTTON::FrameRender(SDL_Surface* & sScreen)
{
	SDL_BlitSurface(m_pImage, 0, sScreen, &m_rRect);

	return OK;
}

RESULT BUTTON::Destroy()
{
	SDL_FreeSurface(m_pImage);

	return OK;
}

RESULT BUTTON::LinkButton(BUTTON* pUp, BUTTON* pDown, BUTTON* pLeft, BUTTON* pRight)
{
	m_pUp	   = pUp;
	m_pDown	 = pDown;
	m_pLeft	 = pLeft;
	m_pRight	= pRight;

	return OK;
}
