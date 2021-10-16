#pragma once
#include "Ogre.h"


class playerPaddle
{
private:
	Ogre::int32 speed;
	Ogre::Vector3 pos;
	Ogre::SceneNode* node;

	int bound;
	int paddleSpeed;

public:
	playerPaddle();
	playerPaddle(Ogre::Entity* batEntity, Ogre::SceneManager* scnMgr);
	~playerPaddle();
	
	Ogre::Vector3 translate;
	Ogre::Vector3 getPlayerPosition();
	void setPlayerPosition(Ogre::Vector3);
	Ogre::SceneNode* getPlayerShape();
	Ogre::int32 getPlayerSpeed();
	void setSpeed(Ogre::int32 x);
	void update(const Ogre::FrameEvent& evt);
	void playerMoveLeft();
	void playerMoveRight();
	void reset();
};
