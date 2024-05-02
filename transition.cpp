#include "main.h"

TRANSITION::TRANSITION(TYPE_TRANSITION tTransition)
{
	m_tTransition = tTransition;
}

TRANSITION::~TRANSITION()
{

}

RESULT TRANSITION::Init()
{
	INT iWorldStageWait = 2000;  //Temps par défaut d'une transition dans un scénario
	SDL_Surface* pImage;

	switch(m_tTransition)
	{
		case INTRO :
		{
			pImage=IMG_Load("resource/image/transition/intro.gif");
			m_lScenes.push_back(new SCENE(pImage,3000));
			break;
		}
		case WORLD1_STAGE1 :
		{
			pImage=IMG_Load("resource/image/transition/w1s1.gif");
			m_lScenes.push_back(new SCENE(pImage,iWorldStageWait));
			break;
		}
		case WORLD1_STAGE2 :
		{
			pImage=IMG_Load("resource/image/transition/w1s2.gif");
			m_lScenes.push_back(new SCENE(pImage,iWorldStageWait));
			break;
		}
		case WORLD1_STAGE3 :
		{
			pImage=IMG_Load("resource/image/transition/w1s3.gif");
			m_lScenes.push_back(new SCENE(pImage,iWorldStageWait));
			break;
		}
		case WORLD2_STAGE1 :
		{
			pImage=IMG_Load("resource/image/transition/w2s1.gif");
			m_lScenes.push_back(new SCENE(pImage,iWorldStageWait));
			break;
		}
		case WORLD2_STAGE2 :
		{
			pImage=IMG_Load("resource/image/transition/w2s2.gif");
			m_lScenes.push_back(new SCENE(pImage,iWorldStageWait));
			break;
		}
		case WORLD2_STAGE3 :
		{
			pImage=IMG_Load("resource/image/transition/w2s3.gif");
			m_lScenes.push_back(new SCENE(pImage,iWorldStageWait));
			break;
		}
		case WORLD3_STAGE1 :
		{
			pImage=IMG_Load("resource/image/transition/w3s1.gif");
			m_lScenes.push_back(new SCENE(pImage,iWorldStageWait));
			break;
		}
		case WORLD3_STAGE2 :
		{
			pImage=IMG_Load("resource/image/transition/w3s2.gif");
			m_lScenes.push_back(new SCENE(pImage,iWorldStageWait));
			break;
		}
		case WORLD3_STAGE3 :
		{
			pImage=IMG_Load("resource/image/transition/w3s3.gif");
			m_lScenes.push_back(new SCENE(pImage,iWorldStageWait));
			break;
		}
		case WORLD4_STAGE1 :
		{
			pImage=IMG_Load("resource/image/transition/w4s1.gif");
			m_lScenes.push_back(new SCENE(pImage,iWorldStageWait));
			break;
		}
		case WORLD4_STAGE2 :
		{
			pImage=IMG_Load("resource/image/transition/w4s2.gif");
			m_lScenes.push_back(new SCENE(pImage,iWorldStageWait));
			break;
		}
		case WORLD4_STAGE3 :
		{
			pImage=IMG_Load("resource/image/transition/w4s3.gif");
			m_lScenes.push_back(new SCENE(pImage,iWorldStageWait));
			break;
		}
		case WORLD5_STAGE1 :
		{
			pImage=IMG_Load("resource/image/transition/w5s1.gif");
			m_lScenes.push_back(new SCENE(pImage,iWorldStageWait));
			break;
		}
		case WORLD5_STAGE2 :
		{
			pImage=IMG_Load("resource/image/transition/w5s2.gif");
			m_lScenes.push_back(new SCENE(pImage,iWorldStageWait));
			break;
		}
		case WORLD5_STAGE3 :
		{
			pImage=IMG_Load("resource/image/transition/w5s3.gif");
			m_lScenes.push_back(new SCENE(pImage,iWorldStageWait));
			break;
		}
		case WORLD6_STAGE1 :
		{
			pImage=IMG_Load("resource/image/transition/w6s1.gif");
			m_lScenes.push_back(new SCENE(pImage,iWorldStageWait));
			break;
		}
		case WORLD6_STAGE2 :
		{
			pImage=IMG_Load("resource/image/transition/w6s2.gif");
			m_lScenes.push_back(new SCENE(pImage,iWorldStageWait));
			break;
		}
		case WORLD6_STAGE3 :
		{
			pImage=IMG_Load("resource/image/transition/w6s3.gif");
			m_lScenes.push_back(new SCENE(pImage,iWorldStageWait));
			break;
		}
		case WORLD7_STAGE1 :
		{
			pImage=IMG_Load("resource/image/transition/w7s1.gif");
			m_lScenes.push_back(new SCENE(pImage,iWorldStageWait));
			break;
		}
		case WORLD7_STAGE2 :
		{
			pImage=IMG_Load("resource/image/transition/w7s2.gif");
			m_lScenes.push_back(new SCENE(pImage,iWorldStageWait));
			break;
		}
		case WORLD7_STAGE3 :
		{
			pImage=IMG_Load("resource/image/transition/w7s3.gif");
			m_lScenes.push_back(new SCENE(pImage,iWorldStageWait));
			break;
		}
		case WORLD8_STAGE1 :
		{
			pImage=IMG_Load("resource/image/transition/w8s1.gif");
			m_lScenes.push_back(new SCENE(pImage,iWorldStageWait));
			break;
		}
		case WORLD8_STAGE2 :
		{
			pImage=IMG_Load("resource/image/transition/w8s2.gif");
			m_lScenes.push_back(new SCENE(pImage,iWorldStageWait));
			break;
		}
		case WORLD8_STAGE3 :
		{
			pImage=IMG_Load("resource/image/transition/w8s3.gif");
			m_lScenes.push_back(new SCENE(pImage,iWorldStageWait));
			break;
		}
		case PLAYER1_WIN :
		{
			pImage=IMG_Load("resource/image/transition/p1win.gif");
			m_lScenes.push_back(new SCENE(pImage,3000));
			break;
		}
		case PLAYER2_WIN :
		{
			pImage=IMG_Load("resource/image/transition/p2win.gif");
			m_lScenes.push_back(new SCENE(pImage,3000));
			break;
		}
		case PLAYER3_WIN :
		{
			pImage=IMG_Load("resource/image/transition/p3win.gif");
			m_lScenes.push_back(new SCENE(pImage,3000));
			break;
		}
		case PLAYER4_WIN :
		{
			pImage=IMG_Load("resource/image/transition/p4win.gif");
			m_lScenes.push_back(new SCENE(pImage,3000));
			break;
		}
		case GAME_OVER :
		{
			pImage=IMG_Load("resource/image/transition/gameover.gif");
			m_lScenes.push_back(new SCENE(pImage,5000));
			break;
		}
		case WIN :
		{
			pImage=IMG_Load("resource/image/transition/win.gif");
			m_lScenes.push_back(new SCENE(pImage,5000));
			break;
		}
		case DRAW_GAME :
		{
			pImage=IMG_Load("resource/image/transition/drawgame.gif");
			m_lScenes.push_back(new SCENE(pImage,3000));
			break;
		}
		case EXIT :
		{
			pImage=IMG_Load("resource/image/transition/exit.gif");
			m_lScenes.push_back(new SCENE(pImage,3000));
			break;
		}
		default :
		{
			return ERROR;
		}
	}

	m_iSceneNumber = int(m_lScenes.size()-1);

	return OK;
}

RESULT TRANSITION::FrameMove(INT iTimeElapsed)
{
	m_lScenes[m_iSceneNumber]->m_iTimeWait -= iTimeElapsed;
	if(m_lScenes[m_iSceneNumber]->m_iTimeWait<=0)
		m_iSceneNumber--;

	if(m_iSceneNumber==-1)
		setFinished();

	return OK;
}

RESULT TRANSITION::FrameRender(SDL_Surface* & sScreen)
{
	SDL_Rect rRect;
	rRect.x = 0; rRect.y = 0; rRect.w = g_pEngine->m_iScreenWidth; rRect.h = g_pEngine->m_iScreenHeight;

	SDL_BlitSurface(m_lScenes[m_iSceneNumber]->m_pImage, 0, sScreen, &rRect);

	return OK;
}

RESULT TRANSITION::Destroy()
{
	vector<SCENE*>::iterator itScene;
	for(itScene=m_lScenes.begin();itScene!=m_lScenes.end();++itScene)
	{
		Release(*itScene);
	}
	m_lScenes.clear();

	return OK;
}

BOOL TRANSITION::NoMoreFrame()
{
	if(m_tTransition==EXIT)
		return true;

	return false;
}

FRAME* TRANSITION::NextFrame()
{
	FRAME* pNewFrame;
	switch(m_tTransition)
	{
		case INTRO :
		{
			pNewFrame = new MENU(MENU::MODE);
			break;
		}
		case WORLD1_STAGE1 :
		{
			pNewFrame = new STAGE(STAGE::SCENARIO,MAP::GREENLAND,1);
			break;
		}
		case WORLD1_STAGE2 :
		{
			pNewFrame = new STAGE(STAGE::SCENARIO,MAP::GREENLAND,2);
			break;
		}
		case WORLD1_STAGE3 :
		{
			pNewFrame = new STAGE(STAGE::SCENARIO,MAP::GREENLAND,3);
			break;
		}
		case WORLD2_STAGE1 :
		{
			pNewFrame = new STAGE(STAGE::SCENARIO,MAP::SNOWLAND,1);
			break;
		}
		case WORLD2_STAGE2 :
		{
			pNewFrame = new STAGE(STAGE::SCENARIO,MAP::SNOWLAND,2);
			break;
		}
		case WORLD2_STAGE3 :
		{
			pNewFrame = new STAGE(STAGE::SCENARIO,MAP::SNOWLAND,3);
			break;
		}
		case WORLD3_STAGE1 :
		{
			pNewFrame = new STAGE(STAGE::SCENARIO,MAP::FIRELAND,1);
			break;
		}
		case WORLD3_STAGE2 :
		{
			pNewFrame = new STAGE(STAGE::SCENARIO,MAP::FIRELAND,2);
			break;
		}
		case WORLD3_STAGE3 :
		{
			pNewFrame = new STAGE(STAGE::SCENARIO,MAP::FIRELAND,3);
			break;
		}
		case WORLD4_STAGE1 :
		{
			pNewFrame = new STAGE(STAGE::SCENARIO,MAP::SWAMPLAND,1);
			break;
		}
		case WORLD4_STAGE2 :
		{
			pNewFrame = new STAGE(STAGE::SCENARIO,MAP::SWAMPLAND,2);
			break;
		}
		case WORLD4_STAGE3 :
		{
			pNewFrame = new STAGE(STAGE::SCENARIO,MAP::SWAMPLAND,3);
			break;
		}
		case WORLD5_STAGE1 :
		{
			pNewFrame = new STAGE(STAGE::SCENARIO,MAP::FREELAND,1);
			break;
		}
		case WORLD5_STAGE2 :
		{
			pNewFrame = new STAGE(STAGE::SCENARIO,MAP::FREELAND,2);
			break;
		}
		case WORLD5_STAGE3 :
		{
			pNewFrame = new STAGE(STAGE::SCENARIO,MAP::FREELAND,3);
			break;
		}
		case WORLD6_STAGE1 :
		{
			pNewFrame = new STAGE(STAGE::SCENARIO,MAP::FREELAND,1);
			break;
		}
		case WORLD6_STAGE2 :
		{
			pNewFrame = new STAGE(STAGE::SCENARIO,MAP::FREELAND,2);
			break;
		}
		case WORLD6_STAGE3 :
		{
			pNewFrame = new STAGE(STAGE::SCENARIO,MAP::FREELAND,3);
			break;
		}
		case WORLD7_STAGE1 :
		{
			pNewFrame = new STAGE(STAGE::SCENARIO,MAP::FREELAND,1);
			break;
		}
		case WORLD7_STAGE2 :
		{
			pNewFrame = new STAGE(STAGE::SCENARIO,MAP::FREELAND,1);
			break;
		}
		case WORLD7_STAGE3 :
		{
			pNewFrame = new STAGE(STAGE::SCENARIO,MAP::FREELAND,1);
			break;
		}
		case WORLD8_STAGE1 :
		{
			pNewFrame = new STAGE(STAGE::SCENARIO,MAP::FREELAND,1);
			break;
		}
		case WORLD8_STAGE2 :
		{
			pNewFrame = new STAGE(STAGE::SCENARIO,MAP::FREELAND,1);
			break;
		}
		case WORLD8_STAGE3 :
		{
			pNewFrame = new STAGE(STAGE::SCENARIO,MAP::FREELAND,1);
			break;
		}
		case PLAYER1_WIN :
		{
			pNewFrame = new MENU(MENU::MAP);
			break;
		}
		case PLAYER2_WIN :
		{
			pNewFrame = new MENU(MENU::MAP);
			break;
		}
		case PLAYER3_WIN :
		{
			pNewFrame = new MENU(MENU::MAP);
			break;
		}
		case PLAYER4_WIN :
		{
			pNewFrame = new MENU(MENU::MAP);
			break;
		}
		case GAME_OVER :
		{
			pNewFrame = new MENU(MENU::MODE);
			break;
		}
		case WIN :
		{
			pNewFrame = new MENU(MENU::MODE);
			break;
		}
		case DRAW_GAME :
		{
			pNewFrame = new MENU(MENU::MAP);
			break;
		}
		case EXIT :
		default :
		{
			return NULL;
		}
	}

	return pNewFrame;
}
