#include "Ball.h"
Ball::Ball()
{
}
Ball::Ball(Ogre::Entity* ent, Ogre::SceneManager* scnMgr)
{
	node = scnMgr->getRootSceneNode()->createChildSceneNode();
	node->setPosition(0, 100, 0);
	node->setScale(0.1f, 0.1f, 0.1f);

	node->attachObject(ent);
	reset();
	
	pos = node->getPosition();

	ballSpeed = 80; //Ball's movement speed
	bound = 112;	//Ball's bound
	angle = 135;	//Ball's AoA
	
}
Ball::~Ball()
{
}
void Ball::reset() 
{
	//Called when ball goes out of bounds
	velY = 1;
	velX = 0;
	btranslate = Ogre::Vector3(0, 0, 0);
}
Ogre::Vector3 Ball::getPosition()
{
	return pos;
}
void Ball::setPosition(Ogre::Vector3 p)
{
	pos = p;
}

Ogre::SceneNode* Ball::getShape()
{
	return node;
}

Ogre::int32 Ball::getVelX()
{
	return velX;
}

void Ball::setVelX(Ogre::int32 x)
{
	velX = x;
}

Ogre::int32 Ball::getVelY()
{
	return velY;
}
void Ball::setVelY(Ogre::int32 y)
{
	velY = y;
}
void Ball::update(const Ogre::FrameEvent& evt)
{
	btranslate = Ogre::Vector3(-ballSpeed * velX, -ballSpeed * velY, 0);
    //Ball constant Y velocity
    if (node->getPosition().y > angle)
    {
        velY = 1;
    }
    
	//Setting ball's bounce direction
    if (node->getPosition().x > bound)
    {
        velX = 1;
    }
    if (node->getPosition().x < -bound)
    {
        velX = -1;
    }

	node->translate(btranslate * evt.timeSinceLastFrame);
}
