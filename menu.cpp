#include "main.h"

MENU::MENU(TYPE_MENU tMenu)
{
	m_tMenu = tMenu;
}

MENU::~MENU()
{

}

RESULT MENU::Init()
{
	SDL_Rect rRect;

	switch(m_tMenu)
	{
		case MODE :
		{
			m_tLastMenu = MODE;

			rRect.x = 300; rRect.y = 150; rRect.w = 200; rRect.h = 100;
			BUTTON* pButtonScenario = new BUTTON(BUTTON::SCENARIO, rRect);
			m_bButtons.push_back(pButtonScenario);

			rRect.x = 300; rRect.y = 300; rRect.w = 200; rRect.h = 100;
			BUTTON* pButtonArena = new BUTTON(BUTTON::ARENA, rRect);
			m_bButtons.push_back(pButtonArena);

			rRect.x = 300; rRect.y = 450; rRect.w = 200; rRect.h = 100;
			BUTTON* pButtonExit = new BUTTON(BUTTON::EXIT, rRect);
			m_bButtons.push_back(pButtonExit);

			pButtonScenario->LinkButton (NULL,pButtonArena,NULL,NULL);
			pButtonArena->LinkButton	(pButtonScenario,pButtonExit,NULL,NULL);
			pButtonExit->LinkButton	 (pButtonArena,NULL,NULL,NULL);

			m_pSelection = pButtonScenario;

			break;
		}

		case NUM_PLAYER :
		{
			m_tLastMenu = MODE;

			rRect.x = 300; rRect.y = 150; rRect.w = 200; rRect.h = 100;
			BUTTON* pButtonTwo = new BUTTON(BUTTON::TWO_PLAYER, rRect);
			m_bButtons.push_back(pButtonTwo);

			rRect.x = 300; rRect.y = 300; rRect.w = 200; rRect.h = 100;
			BUTTON* pButtonThree = new BUTTON(BUTTON::THREE_PLAYER, rRect);
			m_bButtons.push_back(pButtonThree);

			rRect.x = 300; rRect.y = 450; rRect.w = 200; rRect.h = 100;
			BUTTON* pButtonFour = new BUTTON(BUTTON::FOUR_PLAYER, rRect);
			m_bButtons.push_back(pButtonFour);

			//pButtonOne->LinkButton	(NULL,pButtonThree,NULL,pButtonTwo);
			pButtonTwo->LinkButton	(NULL,pButtonThree,NULL,NULL);
			pButtonThree->LinkButton  (pButtonTwo,pButtonFour,NULL,NULL);
			pButtonFour->LinkButton   (pButtonThree,NULL,NULL,NULL);

			m_pSelection = pButtonTwo;

			break;
		}
		case MAP :
		{
			m_tLastMenu = NUM_PLAYER;

			rRect.x = 300; rRect.y = 150; rRect.w = 200; rRect.h = 100;
			BUTTON* pButtonGreen = new BUTTON(BUTTON::GREENLAND, rRect);
			m_bButtons.push_back(pButtonGreen);

			rRect.x = 300; rRect.y = 300; rRect.w = 200; rRect.h = 100;
			BUTTON* pButtonSnow = new BUTTON(BUTTON::SNOWLAND, rRect);
			m_bButtons.push_back(pButtonSnow);

			rRect.x = 300; rRect.y = 450; rRect.w = 200; rRect.h = 100;
			BUTTON* pButtonFire = new BUTTON(BUTTON::FIRELAND, rRect);
			m_bButtons.push_back(pButtonFire);

			pButtonGreen->LinkButton(NULL,pButtonSnow,NULL,NULL);
			pButtonSnow->LinkButton (pButtonGreen,pButtonFire,NULL,NULL);
			pButtonFire->LinkButton (pButtonSnow,NULL,NULL,NULL);

			m_pSelection = pButtonGreen;

			break;
		}
		default :
		{
			return ERROR;
		}
	}

	list<BUTTON*>::iterator itButton;
	for(itButton=m_bButtons.begin();itButton!=m_bButtons.end();++itButton)
	{
		(*itButton)->Init();
	}

	m_pSelectionImage = IMG_Load("resource/image/menu/selection.gif");

	m_pBackground = IMG_Load("resource/image/menu/background.gif");

	SDL_SetColorKey(m_pSelectionImage, SDL_SRCCOLORKEY, SDL_MapRGB(m_pSelectionImage->format, 0, 255, 0));

	return OK;
}

RESULT MENU::Input(TOOLS::INPUT* iInput)
{
	if(iInput[SDLK_ESCAPE] == CLICK)
	{
		TYPE_MENU tMenu = m_tMenu;
		FRAME* pFrame = g_pEngine->getFrame();
		pFrame->Destroy();
		Release(pFrame);
		FRAME* pNewFrame = NULL;
		if(tMenu==MODE)		pNewFrame = new TRANSITION(TRANSITION::EXIT);
		else				pNewFrame = new MENU(MENU::MODE);
		g_pEngine->setFrame(pNewFrame);
		Validate(pNewFrame->Init());

		return OK;
	}

	if((iInput[UP1]==CLICK || iInput[UP2]==CLICK) && m_pSelection->getButtonUp()!=NULL)
		m_pSelection = m_pSelection->getButtonUp();
	if((iInput[DOWN1]==CLICK || iInput[DOWN2]==CLICK) && m_pSelection->getButtonDown()!=NULL)
	{
		m_pSelection = m_pSelection->getButtonDown();
	}
	if((iInput[LEFT1]==CLICK || iInput[LEFT2]==CLICK) && m_pSelection->getButtonLeft()!=NULL)
		m_pSelection = m_pSelection->getButtonLeft();
	if((iInput[RIGHT1]==CLICK || iInput[RIGHT2]==CLICK) && m_pSelection->getButtonRight()!=NULL)
		m_pSelection = m_pSelection->getButtonRight();

	if(iInput[START]==CLICK || iInput[BACK]==CLICK)
	{
		if(iInput[BACK]==CLICK) m_pSelection = NULL;
		setFinished();
	}

	return OK;
}

RESULT MENU::FrameMove(INT iTimeElapsed)
{
	list<BUTTON*>::iterator itButton;
	for(itButton=m_bButtons.begin();itButton!=m_bButtons.end();++itButton)
	{
		(*itButton)->FrameMove(iTimeElapsed);
	}

	return OK;
}

RESULT MENU::FrameRender(SDL_Surface* & sScreen)
{
	SDL_Rect rSelectionRect;
	rSelectionRect.x = 0;   rSelectionRect.y = 0;
	rSelectionRect.w = 800; rSelectionRect.h = 600;
	SDL_BlitSurface(m_pBackground, 0, sScreen, &rSelectionRect);

	list<BUTTON*>::iterator itButton;
	for(itButton=m_bButtons.begin();itButton!=m_bButtons.end();++itButton)
	{
		(*itButton)->FrameRender(sScreen);

		if(m_pSelection==(*itButton))
		{
			rSelectionRect = (*itButton)->getRect();
			rSelectionRect.x -= 10;
			rSelectionRect.y -= 10;
			rSelectionRect.w += 20;
			rSelectionRect.h += 20;
			SDL_BlitSurface(m_pSelectionImage, 0, sScreen, &rSelectionRect);
		}
	}

	return OK;
}

RESULT MENU::Destroy()
{
	list<BUTTON*>::iterator itButton;
	for(itButton=m_bButtons.begin();itButton!=m_bButtons.end();++itButton)
	{
		(*itButton)->Destroy();
		Release(*itButton);
	}
	m_bButtons.clear();

	SDL_FreeSurface(m_pSelectionImage);

	return OK;
}

FRAME* MENU::NextFrame()
{
	FRAME* pNewFrame;
	if(m_pSelection==NULL)
	{
		pNewFrame = new MENU(m_tLastMenu);
	}
	else
	{
		switch(m_pSelection->getName())
		{
			case BUTTON::SCENARIO :
			{
				g_pEngine->setPlayerNumber(1);
				g_pEngine->setPlayerLife(2);
				pNewFrame = new TRANSITION(TRANSITION::WORLD1_STAGE1);
				//pNewFrame = new MENU(DIFFICULTY);

				break;
			}
			case BUTTON::ARENA :
			{
				pNewFrame = new MENU(NUM_PLAYER);

				break;
			}

			case BUTTON::TWO_PLAYER :
			{
				g_pEngine->setPlayerNumber(2);
				pNewFrame = new MENU(MAP);

				break;
			}
			case BUTTON::THREE_PLAYER :
			{
				g_pEngine->setPlayerNumber(3);
				pNewFrame = new MENU(MAP);

				break;
			}
			case BUTTON::FOUR_PLAYER :
			{
				g_pEngine->setPlayerNumber(4);
				pNewFrame = new MENU(MAP);

				break;
			}
			case BUTTON::GREENLAND :
			{
				pNewFrame = new STAGE(STAGE::RANDOM,MAP::GREENLAND);

				break;
			}
			case BUTTON::SNOWLAND :
			{
				pNewFrame = new STAGE(STAGE::RANDOM,MAP::SNOWLAND);

				break;
			}
			case BUTTON::FIRELAND :
			{
				pNewFrame = new STAGE(STAGE::RANDOM,MAP::FIRELAND);

				break;
			}
			case BUTTON::EXIT :
			{
				pNewFrame = new TRANSITION(TRANSITION::EXIT);

				break;
			}
			default :
			{
				return NULL;
			}
		}
	}

	return pNewFrame;
}
