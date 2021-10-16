#include "playerPaddle.h"

void playerPaddle::reset()
{
	translate = Ogre::Vector3(0, 0, 0);
	
}

playerPaddle::playerPaddle()
{
}

playerPaddle::playerPaddle(Ogre::Entity* ent, Ogre::SceneManager* scnMgr)
{
	node = scnMgr->getRootSceneNode()->createChildSceneNode();
	node->setPosition(0, -10, 0);
	node->setScale(0.3f, 0.08f, 1.0f);
	node->attachObject(ent);
	reset();

	pos = node->getPosition();

	bound = 102;	//Paddle's bounds
	paddleSpeed = 300;	//Paddle's speed
}

playerPaddle::~playerPaddle()
{
}

//Setting player's speed, position and shape
Ogre::Vector3 playerPaddle::getPlayerPosition()
{
	return pos;
}

void playerPaddle::setPlayerPosition(Ogre::Vector3 p)
{
	pos = p;
}

Ogre::SceneNode* playerPaddle::getPlayerShape()
{
	return node;
}

Ogre::int32 playerPaddle::getPlayerSpeed()
{
	return speed;
}

void playerPaddle::setSpeed(Ogre::int32 x)
{
	speed = x;
}

void playerPaddle::update(const Ogre::FrameEvent& evt)
{
	
		node->translate(translate * evt.timeSinceLastFrame);
		translate = Ogre::Vector3(0, 0, 0);
	
}

//Player movement
void playerPaddle::playerMoveLeft()
{
	if (node->getPosition().x > -bound)
		translate = Ogre::Vector3(-paddleSpeed, 0, 0);
}

void playerPaddle::playerMoveRight()
{
	if (node->getPosition().x < bound)
		translate = Ogre::Vector3(paddleSpeed, 0, 0);
}
