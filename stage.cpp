#include "main.h"

STAGE::STAGE(TYPE_GAME tGame, MAP::TYPE_TERRAIN tTerrain)
{
	m_tGame	 = tGame;
	m_tTerrain  = tTerrain;
}

STAGE::STAGE(TYPE_GAME tGame, MAP::TYPE_TERRAIN tTerrain, INT iStage)
{
	m_tGame	 = tGame;
	m_tTerrain  = tTerrain;
	m_iStage	= iStage;
}

STAGE::~STAGE()
{

}

RESULT STAGE::Init()
{
	USER::s_uNumUser = 0;
	m_pMusic = FMUSIC_LoadSong("resource/music/battlehysterical.mid");
	FMUSIC_PlaySong(m_pMusic);
	FMUSIC_SetLooping(m_pMusic,-1);

	m_pBombExplosion = FSOUND_Sample_Load(FSOUND_FREE, "resource/sound/explosion3.wav", 0, 0, 0);

	m_iFadeOutTime = 1000;
	m_pScoreBar = IMG_Load("resource/image/score_bar.gif");
	if(m_tGame==RANDOM)
	{
		m_mMap.Init(this,m_tTerrain,NULL);
		USER* pPlayer;
		for(UINT i=0;i<g_pEngine->getPlayerNumber();++i)
		{
			pPlayer = new USER(this);
			m_lPlayers.push_back(pPlayer);
		}
	}
	else
	{
		m_pLifeTitle  = IMG_Load("resource/image/lifetitle.gif");
		m_pLifeNumber = IMG_Load("resource/image/character/boby.gif");
		SDL_SetColorKey(m_pLifeNumber, SDL_SRCCOLORKEY, SDL_MapRGB(m_pLifeNumber->format, 0, 255, 0));
		CHAR pMapFile[70];
		strcpy(pMapFile,"resource/scenario/");
		strcat(pMapFile,"w");
		CHAR cTerrain[2]; cTerrain[0] = (m_tTerrain+1)+'0'; cTerrain[1]='\0';
		strcat(pMapFile,cTerrain);
		strcat(pMapFile,"s");
		CHAR cStage[2]; cStage[0] = (m_iStage)+'0'; cStage[1]='\0';
		strcat(pMapFile,cStage);
		strcat(pMapFile,".sce");
		m_mMap.Init(this,m_tTerrain,pMapFile);
	}

	list<PLAYER*>::iterator itPlayer;
	for(itPlayer=m_lPlayers.begin();itPlayer!=m_lPlayers.end();++itPlayer)
	{
		(*itPlayer)->Init();
	}

	list<BONUS*>::iterator itBonus;
	for(itBonus=m_lBonus.begin();itBonus!=m_lBonus.end();++itBonus)
	{
		(*itBonus)->Init();
	}

	list<BOMB*>::iterator itBomb;
	for(itBomb=m_lBombs.begin();itBomb!=m_lBombs.end();++itBomb)
	{
		(*itBomb)->Init();
	}

	list<FIRE*>::iterator itFire;
	for(itFire=m_lFires.begin();itFire!=m_lFires.end();++itFire)
	{
		(*itFire)->Init();
	}

	return OK;
}

RESULT STAGE::Input(TOOLS::INPUT* iInput)
{
	if(iInput[SDLK_ESCAPE] == CLICK)
	{
		FRAME* pFrame = g_pEngine->getFrame();
		pFrame->Destroy();
		Release(pFrame);
		FRAME* pNewFrame = new MENU(MENU::MODE);
		g_pEngine->setFrame(pNewFrame);
		Validate(pNewFrame->Init());

		return OK;
	}

	list<PLAYER*>::iterator itPlayer;
	for(itPlayer=m_lPlayers.begin();itPlayer!=m_lPlayers.end();++itPlayer)
	{
		(*itPlayer)->Input(iInput);
	}

	return OK;
}

RESULT STAGE::FrameMove(INT iTimeElapsed)
{
	m_mMap.FrameMove(iTimeElapsed);

	list<FIRE*>::iterator itFire;
	for(itFire=m_lFires.begin();itFire!=m_lFires.end();)
	{
		(*itFire)->FrameMove(iTimeElapsed);
		if((*itFire)->isFinished())
		{
			(*itFire)->Destroy();
			Release(*itFire);
			itFire=m_lFires.erase(itFire);
		}
		else
		{
			++itFire;
		}
	}

	list<BONUS*>::iterator itBonus;
	for(itBonus=m_lBonus.begin();itBonus!=m_lBonus.end();)
	{
		(*itBonus)->FrameMove(iTimeElapsed);
		if((*itBonus)->isFinished())
		{
			(*itBonus)->Destroy();
			Release(*itBonus);
			itBonus=m_lBonus.erase(itBonus);
		}
		else
		{
			++itBonus;
		}
	}

	list<BOMB*>::iterator itBomb;
	for(itBomb=m_lBombs.begin();itBomb!=m_lBombs.end();)
	{
		(*itBomb)->FrameMove(iTimeElapsed);
		if((*itBomb)->isFinished())
		{
			(*itBomb)->Destroy();
			Release(*itBomb);
			itBomb=m_lBombs.erase(itBomb);
		}
		else
		{
			++itBomb;
		}
	}

	UINT uNbMonster = 0;
	UINT uNbUser = 0;
	list<PLAYER*>::iterator itPlayer;
	for(itPlayer=m_lPlayers.begin();itPlayer!=m_lPlayers.end();)
	{
		(*itPlayer)->FrameMove(iTimeElapsed);
		if((*itPlayer)->isFinished())
		{
			(*itPlayer)->Destroy();
			Release(*itPlayer);
			itPlayer=m_lPlayers.erase(itPlayer);
		}
		else
		{
			if((*itPlayer)->isAI())   ++uNbMonster;
			if((*itPlayer)->isUser()) ++uNbUser;
			++itPlayer;
		}
	}

	if(m_tGame==SCENARIO)
	{
		if(uNbMonster==0) getMap()->ShowExit();
		if(uNbUser==0)
		{
			m_iFadeOutTime-=iTimeElapsed;

		}
		else
		{
			if(uNbMonster==0)
			{
				if((*(m_lPlayers.begin()))->getPositionStep().getX()==m_mMap.getEnd().getX() && (*(m_lPlayers.begin()))->getPositionStep().getY()==m_mMap.getEnd().getY()) setFinished();
			}
		}
		if(m_iFadeOutTime<=0)
		{
			setFinished();
		}
	}
	else
	{
		if(m_lPlayers.size()<2)
		{
			m_iFadeOutTime-=iTimeElapsed;

		}
		if(m_iFadeOutTime<=0)
		{
			setFinished();
		}
	}

	return OK;
}

RESULT STAGE::FrameRender(SDL_Surface* & sScreen)
{
	m_mMap.FrameRender(sScreen);

	list<BONUS*>::iterator itBonus;
	for(itBonus=m_lBonus.begin();itBonus!=m_lBonus.end();++itBonus)
	{
		(*itBonus)->FrameRender(sScreen);
	}

	list<BOMB*>::iterator itBomb;
	for(itBomb=m_lBombs.begin();itBomb!=m_lBombs.end();++itBomb)
	{
		(*itBomb)->FrameRender(sScreen);
	}

	list<FIRE*>::iterator itFire;
	for(itFire=m_lFires.begin();itFire!=m_lFires.end();++itFire)
	{
		(*itFire)->FrameRender(sScreen);
	}

	list<PLAYER*>::iterator itPlayer;
	for(itPlayer=m_lPlayers.begin();itPlayer!=m_lPlayers.end();++itPlayer)
	{
		(*itPlayer)->FrameRender(sScreen);
	}

	SDL_BlitSurface(m_pScoreBar, 0, sScreen, 0);
	if(m_tGame==SCENARIO)
	{
		SDL_Rect rec;
		rec.x = 668;  rec.y = 11;  rec.w = 84;  rec.h = 25;
		SDL_BlitSurface(m_pLifeTitle, 0, sScreen, &rec);
		for(UINT uNbLife=0;uNbLife<=g_pEngine->getPlayerLife();++uNbLife)
		{
			rec.x = 668+uNbLife*32;  rec.y = 40;  rec.w = 32;  rec.h = 32;
			SDL_BlitSurface(m_pLifeNumber, 0, sScreen, &rec);
		}
	}

	return OK;
}

RESULT STAGE::Destroy()
{
	list<PLAYER*>::iterator itPlayer;
	for(itPlayer=m_lPlayers.begin();itPlayer!=m_lPlayers.end();++itPlayer)
	{
		(*itPlayer)->Destroy();
		Release(*itPlayer);
	}

	list<BONUS*>::iterator itBonus;
	for(itBonus=m_lBonus.begin();itBonus!=m_lBonus.end();++itBonus)
	{
		(*itBonus)->Destroy();
		Release(*itBonus);
	}

	list<BOMB*>::iterator itBomb;
	for(itBomb=m_lBombs.begin();itBomb!=m_lBombs.end();++itBomb)
	{
		(*itBomb)->Destroy();
		Release(*itBomb);
	}

	list<FIRE*>::iterator itFire;
	for(itFire=m_lFires.begin();itFire!=m_lFires.end();++itFire)
	{
		(*itFire)->Destroy();
		Release(*itFire);
	}

	m_lPlayers.clear();
	m_lBonus.clear();
	m_lBombs.clear();
	m_lFires.clear();
	m_mMap.Destroy();
	SDL_FreeSurface(m_pScoreBar);
	if(m_tGame==SCENARIO)
	{
		SDL_FreeSurface(m_pLifeTitle);
		SDL_FreeSurface(m_pLifeNumber);
	}

	FSOUND_Sample_Free(m_pBombExplosion);
	//FMUSIC_StopSong(m_pMusic);
	FMUSIC_FreeSong(m_pMusic);

	return OK;
}

FRAME* STAGE::NextFrame()
{
	FRAME* pNewFrame;
	if(m_tGame==SCENARIO)
	{
		UINT uNbUser = 0;
		list<PLAYER*>::iterator itPlayer;
		for(itPlayer=m_lPlayers.begin();itPlayer!=m_lPlayers.end();++itPlayer)
		{
			if((*itPlayer)->isUser()) ++uNbUser;
		}
		if(uNbUser==0 && g_pEngine->getPlayerLife()==0)
		{
			pNewFrame = new TRANSITION(TRANSITION::GAME_OVER);
		}
		else
		{
			TRANSITION::TYPE_TRANSITION tTransition = TRANSITION::WORLD1_STAGE1;
			if(uNbUser!=0)
			{
				switch(m_tTerrain)
				{
					case MAP::GREENLAND :
					{
						if(m_iStage==1)
						{
							tTransition = TRANSITION::WORLD1_STAGE2;
							break;
						}
						if(m_iStage==2)
						{
							tTransition = TRANSITION::WORLD1_STAGE3;
							break;
						}
						if(m_iStage==3)
						{
							tTransition = TRANSITION::WORLD2_STAGE1;
							break;
						}
					}
					case MAP::SNOWLAND :
					{
						if(m_iStage==1)
						{
							tTransition = TRANSITION::WORLD2_STAGE2;
							break;
						}
						if(m_iStage==2)
						{
							tTransition = TRANSITION::WORLD2_STAGE3;
							break;
						}
						if(m_iStage==3)
						{
							tTransition = TRANSITION::WORLD3_STAGE1;
							break;
						}
					}
					case MAP::FIRELAND :
					{
						if(m_iStage==1)
						{
							tTransition = TRANSITION::WORLD3_STAGE2;
							break;
						}
						if(m_iStage==2)
						{
							tTransition = TRANSITION::WORLD3_STAGE3;
							break;
						}
						if(m_iStage==3)
						{
							//tTransition = TRANSITION::WORLD4_STAGE1;
							tTransition = TRANSITION::WIN;
							break;
						}
					}
					case MAP::SWAMPLAND :
					{
						if(m_iStage==1)
						{
							tTransition = TRANSITION::WORLD4_STAGE2;
							break;
						}
						if(m_iStage==2)
						{
							tTransition = TRANSITION::WORLD4_STAGE3;
							break;
						}
						if(m_iStage==3)
						{
							tTransition = TRANSITION::WORLD5_STAGE1;
							break;
						}
					}
					case MAP::FREELAND :
					{
						if(m_iStage==1)
						{
							tTransition = TRANSITION::WORLD5_STAGE2;
							break;
						}
						if(m_iStage==2)
						{
							tTransition = TRANSITION::WORLD5_STAGE3;
							break;
						}
						if(m_iStage==3)
						{
							tTransition = TRANSITION::WORLD6_STAGE1;
							break;
						}
					}

				}
			}
			else
			{
				g_pEngine->setPlayerLife(g_pEngine->getPlayerLife()-1);
				switch(m_tTerrain)
				{
					case MAP::GREENLAND :
					{
						if(m_iStage==1)
						{
							tTransition = TRANSITION::WORLD1_STAGE1;
							break;
						}
						if(m_iStage==2)
						{
							tTransition = TRANSITION::WORLD1_STAGE2;
							break;
						}
						if(m_iStage==3)
						{
							tTransition = TRANSITION::WORLD1_STAGE3;
							break;
						}
					}
					case MAP::SNOWLAND :
					{
						if(m_iStage==1)
						{
							tTransition = TRANSITION::WORLD2_STAGE1;
							break;
						}
						if(m_iStage==2)
						{
							tTransition = TRANSITION::WORLD2_STAGE2;
							break;
						}
						if(m_iStage==3)
						{
							tTransition = TRANSITION::WORLD2_STAGE3;
							break;
						}
					}
					case MAP::FIRELAND :
					{
						if(m_iStage==1)
						{
							tTransition = TRANSITION::WORLD3_STAGE1;
							break;
						}
						if(m_iStage==2)
						{
							tTransition = TRANSITION::WORLD3_STAGE2;
							break;
						}
						if(m_iStage==3)
						{
							tTransition = TRANSITION::WORLD3_STAGE3;
							break;
						}
					}
					case MAP::SWAMPLAND :
					{
						if(m_iStage==1)
						{
							tTransition = TRANSITION::WORLD4_STAGE1;
							break;
						}
						if(m_iStage==2)
						{
							tTransition = TRANSITION::WORLD4_STAGE2;
							break;
						}
						if(m_iStage==3)
						{
							tTransition = TRANSITION::WORLD4_STAGE3;
							break;
						}
					}
					case MAP::FREELAND :
					{
						if(m_iStage==1)
						{
							tTransition = TRANSITION::WORLD5_STAGE1;
							break;
						}
						if(m_iStage==2)
						{
							tTransition = TRANSITION::WORLD5_STAGE2;
							break;
						}
						if(m_iStage==3)
						{
							tTransition = TRANSITION::WORLD5_STAGE3;
							break;
						}
					}

				}
			}
			pNewFrame = new TRANSITION(tTransition);
		}
	}
	else
	{
		if(m_lPlayers.size()==0)
		{
			pNewFrame = new TRANSITION(TRANSITION::DRAW_GAME);
		}
		else
		{
			list<PLAYER*>::iterator itPlayer;
			for(itPlayer=m_lPlayers.begin();itPlayer!=m_lPlayers.end();++itPlayer)
			{
				if(!(*itPlayer)->isFinished()) break;
			}
			switch((*itPlayer)->getID())
			{
				case 0 :
				{
					pNewFrame = new TRANSITION(TRANSITION::PLAYER1_WIN);
					break;
				}
				case 1 :
				{
					pNewFrame = new TRANSITION(TRANSITION::PLAYER2_WIN);
					break;
				}
				case 2 :
				{
					pNewFrame = new TRANSITION(TRANSITION::PLAYER3_WIN);
					break;
				}
				case 3 :
				{
					pNewFrame = new TRANSITION(TRANSITION::PLAYER4_WIN);
					break;
				}
				default :
				{
					return NULL;
				}
			}
		}
	}

	return pNewFrame;
}

PLAYER* STAGE::getPlayerByPosition(TOOLS::POINT pPosition)
{
	list<PLAYER*>::iterator itPlayer;
	for(itPlayer=m_lPlayers.begin();itPlayer!=m_lPlayers.end();++itPlayer)
	{
		if((*itPlayer)->getPositionStep().getX()==pPosition.getX() && (*itPlayer)->getPositionStep().getY()==pPosition.getY())
		{
			return (*itPlayer);
		}
	}

	return NULL;
}

PLAYER* STAGE::getUserByPosition(TOOLS::POINT pPosition)
{
	list<PLAYER*>::iterator itPlayer;
	for(itPlayer=m_lPlayers.begin();itPlayer!=m_lPlayers.end();++itPlayer)
	{
		if((*itPlayer)->getPositionStep().getX()==pPosition.getX() && (*itPlayer)->getPositionStep().getY()==pPosition.getY() && (*itPlayer)->isUser())
		{
			return (*itPlayer);
		}
	}

	return NULL;
}

BONUS* STAGE::getBonusByPosition(TOOLS::POINT pPosition)
{
	list<BONUS*>::iterator itBonus;
	for(itBonus=m_lBonus.begin();itBonus!=m_lBonus.end();++itBonus)
	{
		if((*itBonus)->getPosition().getX()==pPosition.getX() && (*itBonus)->getPosition().getY()==pPosition.getY())
		{
			return (*itBonus);
		}
	}

	return NULL;
}

BOMB* STAGE::getBombByPosition(TOOLS::POINT pPosition)
{
	list<BOMB*>::iterator itBomb;
	for(itBomb=m_lBombs.begin();itBomb!=m_lBombs.end();++itBomb)
	{
		if((*itBomb)->getPosition().getX()==pPosition.getX() && (*itBomb)->getPosition().getY()==pPosition.getY())
		{
			return (*itBomb);
		}
	}

	return NULL;
}
