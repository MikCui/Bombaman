/*
Mikael Cuinet 2005 - Projet Info
*/

#include "main.h"

ENGINE g_Engine;
ENGINE* g_pEngine;

int main (int argc, char* argv[])
{
	g_pEngine = &g_Engine;
	g_pEngine->OneTimeSceneInit();

	FSOUND_Init(44100, 32, 0);

	if(SDL_Init(SDL_INIT_EVERYTHING)<0)
	{
		printf("Unable to init SDL: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	atexit(SDL_Quit);

	SDL_ShowCursor(false);

	SDL_Surface* screen = SDL_SetVideoMode(g_pEngine->m_iScreenWidth,
										   g_pEngine->m_iScreenHeight,
										   g_pEngine->m_iColorDepth,
										   SDL_HWSURFACE|SDL_DOUBLEBUF|(g_pEngine->m_bFullScreen?SDL_FULLSCREEN:0));

	SDL_WM_SetCaption(g_pEngine->m_pTitle, NULL);

	if(!screen)
	{
		printf("Unable to set video: %s\n", SDL_GetError());
		return 1;
	}

	srand(UINT(time(NULL)));
	INT iTime = SDL_GetTicks(), iTimeElapsed = 0;

	Validate(g_pEngine->Init());

	while(true)
	{
		iTimeElapsed = SDL_GetTicks() - iTime;
		iTime=SDL_GetTicks();
		Validate(g_pEngine->Input());
		if(g_pEngine->m_bExit) break;
		Validate(g_pEngine->FrameMove(iTimeElapsed));
		if(g_pEngine->m_bExit) break;
		Validate(g_pEngine->FrameRender(screen));
	}

	Validate(g_pEngine->Destroy());

	FSOUND_Close();

	return OK;
}
