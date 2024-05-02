#include "main.h"

RESULT ENGINE::OneTimeSceneInit()
{
	m_iScreenWidth		  =   800;
	m_iScreenHeight		 =   600;
	m_iColorDepth		   =   32;
	m_bFullScreen		   =   true;
	m_pTitle				=   "Bomberman";
	m_iTime				 =   0;
	m_iTimeElapsed		  =   0;
	m_bExit				 =   false;

	m_cBackgroundColor.r = 50; m_cBackgroundColor.g = 50; m_cBackgroundColor.b = 50;

	m_fFrame	=   NULL;

	return OK;
}

RESULT ENGINE::Init()
{
	for(UINT i=0;i<323;++i)
	{
		m_iInput[i]=UNPRESSED;
	}

	m_fFrame = new TRANSITION(TRANSITION::INTRO);

	Validate(m_fFrame->Init());

	return OK;
}

RESULT ENGINE::Input()
{
	for(UINT i=0;i<323;++i)
	{
		if(m_iInput[i]==RELEASED)
			m_iInput[i]=UNPRESSED;

		if(m_iInput[i]==CLICK)
			m_iInput[i]=PRESSED;
	}

	SDL_Event sEvent;

	while(SDL_PollEvent(&sEvent))
	{
		switch (sEvent.type)
		{
			case SDL_KEYDOWN :
			{
				m_iInput[sEvent.key.keysym.sym]=CLICK;
				break;
			}
			case SDL_QUIT :
			{
				m_bExit = true;
				return OK;

				break;
			}
			case SDL_KEYUP :
			{
				m_iInput[sEvent.key.keysym.sym] = RELEASED;
				break;
			}
		}
	}

	Validate(m_fFrame->Input(m_iInput));

	return OK;
}

RESULT ENGINE::FrameMove(INT iTimeElapsed)
{
	m_iTimeElapsed = iTimeElapsed;
	m_iTime += m_iTimeElapsed;

	if(!getFrame()->isFinished())
	{
		Validate(getFrame()->FrameMove(iTimeElapsed));
	}

	if(getFrame()->isFinished())
	{
		if(getFrame()->NoMoreFrame())
		{
			getFrame()->Destroy();
			Release(getFrame());
			setExit(true);
		}
		else
		{
			FRAME* fOldFrame = getFrame();
			setFrame(fOldFrame->NextFrame());
			if(getFrame()==NULL) return ERROR;
			Validate(fOldFrame->Destroy());
			Release(fOldFrame);
			Validate(getFrame()->Init());
		}
	}

	return OK;
}

RESULT ENGINE::FrameRender(SDL_Surface* sScreen)
{
	SDL_Rect rec;   rec.x = 0;  rec.y = 0; rec.w = m_iScreenWidth;  rec.h = m_iScreenHeight;
	SDL_FillRect(sScreen, 0, SDL_MapRGB(sScreen->format, m_cBackgroundColor.r, m_cBackgroundColor.g, m_cBackgroundColor.b));

	Validate(m_fFrame->FrameRender(sScreen));

	SDL_Flip(sScreen);

	return OK;
}

RESULT ENGINE::Destroy()
{
	if(m_fFrame!=NULL)
	{
		Validate(m_fFrame->Destroy());
		Release(m_fFrame);
	}

	return OK;
}
