#include "main.h"

RESULT PLAYER::Init()
{
	setRange(1);
	setBomb(1);
	setSpeed(128.0f);
	setPosition(0,0);

	return OK;
}

RESULT PLAYER::FrameMove(INT iTimeElapsed)
{
	BOOL bAlreadyVerticalMoved = false, bAlreadyHorizontalMoved = false;
	TOOLS::POINT pPosition = TOOLS::POINT(0,0);
	if(m_bActions[UP])
	{
		pPosition.setXY(getPositionStep().getX(),getPositionStep().getY()-1);
		if(getStage()->getMap()->isPassable(pPosition) && !getStage()->getBombByPosition(pPosition))
		{
			if(getPosition().getX()!=0.0f)
			{
				if(abs(INT(getPosition().getX()))<=getSpeed()*iTimeElapsed/TIME_NORMALIZE)
				{
					setPosition(0,getPosition().getY());
				}
				else
				{
					if(getPosition().getX()<0.0f)
						setPosition(getPosition().getX()+getSpeed()*iTimeElapsed/TIME_NORMALIZE,getPosition().getY());
					else
						setPosition(getPosition().getX()-getSpeed()*iTimeElapsed/TIME_NORMALIZE,getPosition().getY());

					bAlreadyHorizontalMoved = true;
				}
			}
			else
			{
				setPosition(0,getPosition().getY()-getSpeed()*iTimeElapsed/TIME_NORMALIZE);
				bAlreadyVerticalMoved = true;
			}
		}
		else
		{
			if(!bAlreadyVerticalMoved && getPosition().getY()>0.0f)
			{
				setPosition(0,getPosition().getY()-getSpeed()*iTimeElapsed/TIME_NORMALIZE);
				bAlreadyVerticalMoved = true;
			}
		}
		if(getPosition().getY()<=-TILE_SIZE/2.0f)
		{
			setPositionStep(getPositionStep().getX(),getPositionStep().getY()-1);
			setPosition(0,getPosition().getY()+TILE_SIZE);
		}
		if(getPosition().getY()<=0.0f && (!getStage()->getMap()->isPassable(pPosition) || getStage()->getBombByPosition(pPosition)))
		{
			setPosition(getPosition().getX(),0);
		}
	}
	if(m_bActions[DOWN])
	{
		pPosition.setXY(getPositionStep().getX(),getPositionStep().getY()+1);
		if(getStage()->getMap()->isPassable(pPosition) && !getStage()->getBombByPosition(pPosition))
		{
			if(getPosition().getX()!=0.0f)
			{
				if(abs(INT(getPosition().getX()))<=getSpeed()*iTimeElapsed/TIME_NORMALIZE)
				{
					setPosition(0,getPosition().getY());
				}
				else
				{
					if(!bAlreadyHorizontalMoved)
					{
						if(getPosition().getX()<0.0f)
							setPosition(getPosition().getX()+getSpeed()*iTimeElapsed/TIME_NORMALIZE,getPosition().getY());
						else
							setPosition(getPosition().getX()-getSpeed()*iTimeElapsed/TIME_NORMALIZE,getPosition().getY());

						bAlreadyHorizontalMoved = true;
					}
				}
			}
			else
			{
				if(!bAlreadyVerticalMoved)
				{
					setPosition(0,getPosition().getY()+getSpeed()*iTimeElapsed/TIME_NORMALIZE);
					bAlreadyVerticalMoved = true;
				}
			}
		}
		else
		{
			if(!bAlreadyVerticalMoved && getPosition().getY()<0.0f)
			{
				setPosition(0,getPosition().getY()+getSpeed()*iTimeElapsed/TIME_NORMALIZE);
				bAlreadyVerticalMoved = true;
			}
		}
		if(getPosition().getY()>=TILE_SIZE/2.0f)
		{
			setPositionStep(getPositionStep().getX(),getPositionStep().getY()+1);
			setPosition(0,getPosition().getY()-TILE_SIZE);
		}
		if(getPosition().getY()>=0.0f && (!getStage()->getMap()->isPassable(pPosition) || getStage()->getBombByPosition(pPosition)))
		{
			setPosition(getPosition().getX(),0);
		}
	}
	if(m_bActions[LEFT])
	{
		pPosition.setXY(getPositionStep().getX()-1,getPositionStep().getY());
		if(getStage()->getMap()->isPassable(pPosition) && !getStage()->getBombByPosition(pPosition))
		{
			if(getPosition().getY()!=0.0f)
			{
				if(abs(INT(getPosition().getY()))<=getSpeed()*iTimeElapsed/TIME_NORMALIZE)
				{
					setPosition(getPosition().getX(),0);
				}
				else
				{
					if(!bAlreadyVerticalMoved)
					{
						if(getPosition().getY()<0.0f)
							setPosition(getPosition().getX(),getPosition().getY()+getSpeed()*iTimeElapsed/TIME_NORMALIZE);
						else
							setPosition(getPosition().getX(),getPosition().getY()-getSpeed()*iTimeElapsed/TIME_NORMALIZE);

						bAlreadyVerticalMoved = true;
					}
				}
			}
			else
			{
				if(!bAlreadyHorizontalMoved)
				{
					setPosition(getPosition().getX()-getSpeed()*iTimeElapsed/TIME_NORMALIZE,0);
					bAlreadyHorizontalMoved = true;
				}
			}
		}
		else
		{
			if(!bAlreadyHorizontalMoved && getPosition().getX()>0.0f)
			{
				setPosition(getPosition().getX()-getSpeed()*iTimeElapsed/TIME_NORMALIZE,0);
				bAlreadyHorizontalMoved = true;
			}
		}
		if(getPosition().getX()<=-TILE_SIZE/2.0f)
		{
			setPositionStep(getPositionStep().getX()-1,getPositionStep().getY());
			setPosition(getPosition().getX()+TILE_SIZE,0);
		}
		if(getPosition().getX()<=0.0f && (!getStage()->getMap()->isPassable(pPosition) || getStage()->getBombByPosition(pPosition)))
		{
			setPosition(0,getPosition().getY());
		}
	}
	if(m_bActions[RIGHT])
	{
		pPosition.setXY(getPositionStep().getX()+1,getPositionStep().getY());
		if(getStage()->getMap()->isPassable(pPosition) && !getStage()->getBombByPosition(pPosition))
		{
			if(getPosition().getY()!=0.0f)
			{
				if(abs(INT(getPosition().getY()))<=getSpeed()*iTimeElapsed/TIME_NORMALIZE)
				{
					setPosition(getPosition().getX(),0);
				}
				else
				{
					if(!bAlreadyVerticalMoved)
					{
						if(getPosition().getY()<0.0f)
							setPosition(getPosition().getX(),getPosition().getY()+getSpeed()*iTimeElapsed/TIME_NORMALIZE);
						else
							setPosition(getPosition().getX(),getPosition().getY()-getSpeed()*iTimeElapsed/TIME_NORMALIZE);

						bAlreadyVerticalMoved = true;
					}
				}
			}
			else
			{
				if(!bAlreadyHorizontalMoved)
				{
					setPosition(getPosition().getX()+getSpeed()*iTimeElapsed/TIME_NORMALIZE,0);
					bAlreadyHorizontalMoved = true;
				}
			}
		}
		else
		{
			if(!bAlreadyHorizontalMoved && getPosition().getX()<0.0f)
			{
				setPosition(getPosition().getX()+getSpeed()*iTimeElapsed/TIME_NORMALIZE,0);
				bAlreadyHorizontalMoved = true;
			}
		}
		if(getPosition().getX()>=TILE_SIZE/2.0f)
		{
			setPositionStep(getPositionStep().getX()+1,getPositionStep().getY());
			setPosition(getPosition().getX()-TILE_SIZE,0);
		}
		if(getPosition().getX()>=0.0f && (!getStage()->getMap()->isPassable(pPosition) || getStage()->getBombByPosition(pPosition)))
		{
			setPosition(0,getPosition().getY());
		}
	}
	if(m_bActions[PLANT_BOMB])
	{
		if(getStage()->getBombByPosition(getPositionStep())==NULL && getBomb()>0)
		{
			setBomb(getBomb()-1);
			BOMB* pBomb = new BOMB(getStage(),this,getPositionStep(),getRange());
			pBomb->Init();
			getStage()->getBombs()->push_back(pBomb);
		}
	}

	if(getStage()->getBonusByPosition(getPositionStep()))
	{
		switch(getStage()->getBonusByPosition(getPositionStep())->getType())
		{
			case BONUS::FIRE :
			{
				setRange(getRange()+1);
				break;
			}
			case BONUS::BOMB :
			{
				setBomb(getBomb()+1);
				break;
			}
			case BONUS::SPEED :
			{
				setSpeed(getSpeed()+16.0f);
				break;
			}
			default :
			{
				return ERROR;
			}
		}
		getStage()->getBonusByPosition(getPositionStep())->setFinished();
	}

	return OK;
}

RESULT PLAYER::FrameRender(SDL_Surface* & sScreen)
{
	if(!isFinished())
	{
		static SDL_Rect rec;	rec.w = TILE_SIZE;  rec.h = TILE_SIZE;

		rec.x = OFFSET_X*TILE_SIZE+getPositionStep().getX()*TILE_SIZE+INT(getPosition().getX());  rec.y = OFFSET_Y*TILE_SIZE+getPositionStep().getY()*TILE_SIZE+INT(getPosition().getY());
		SDL_BlitSurface(m_pCharacters[DOWN], 0, sScreen, &rec);
	}

	return OK;
}

RESULT PLAYER::Destroy()
{
	SDL_FreeSurface(m_pCharacters[UP]);
	SDL_FreeSurface(m_pCharacters[DOWN]);
	SDL_FreeSurface(m_pCharacters[LEFT]);
	SDL_FreeSurface(m_pCharacters[RIGHT]);

	return OK;
}
