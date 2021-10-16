#pragma once

#include "Ball.h"
#include "playerPaddle.h"

#include "OgreApplicationContext.h"
#include "OgreInput.h"
#include "OgreRTShaderSystem.h"
#include "OgreTrays.h"
#include <iostream>

using namespace Ogre;
using namespace OgreBites;
Ogre::Vector3 translate(0, 0, 0);

Ogre::int32 movDirY;
Ogre::int32 movDirX;

class ExampleFrameListener : public Ogre::FrameListener
{
private:

public:

    ExampleFrameListener()
    {
    }

    bool frameStarted(const Ogre::FrameEvent& evt)
    {       
        return true;
    }
};

class Game
    : public ApplicationContext
    , public InputListener
{
private:
    SceneNode* paddleNode;
    Ogre::SceneNode* ballNode;
    SceneManager* scnMgr;
    OgreBites::TrayManager* mTrayMgr;
    Root* root;
    Ogre::int32 isCollide;
   
    Ogre::int32 score = 0;
    Ogre::int32 lives = 3;

    //Game state variable
    bool gameover = false; 

    //Frame rate variables
    int numberOfFrame = 0;
    float timeSinceLastFrame = 0;
    float frameRate = 0;
    float deltaTime = 0.03;

    //Check bounds variable
    int bound = 50;
public:
    Game();
    virtual ~Game() {}

    void setup();
    bool keyPressed(const KeyboardEvent& evt);
    bool frameRenderingQueued(const FrameEvent& evt);
    
    void createScene();
    void createCamera();
    void createFrameListener();
    OgreBites::TrayListener myTrayListener;
    OgreBites::Label* mInfoLabel;
    OgreBites::Label* mScoreLabel;
    OgreBites::Label* mScore;
    OgreBites::Label* mLivesLabel;
    OgreBites::Label* mPlayerLives;
    OgreBites::Label* mFPS;
    OgreBites::Label* mTPU;
    OgreBites::Button* mQuitButton = nullptr;
    OgreBites::Label* mGameOverLabel;
    
    Ogre::DisplayString sc ;
    Ogre::DisplayString l;
    Ball* mBall;
    playerPaddle* mPlayerPaddle;
};


Game::Game()
    : ApplicationContext("GAME3121_Assignment1_Phu_Pham")
{
    //Declares player's score and lives
    score = 0;
    lives = 5;
    isCollide = 0;
    mBall = nullptr;

}


void Game::setup()
{
    // do not forget to call the base first
    ApplicationContext::setup();
    addInputListener(this);

    // get a pointer to the already created root
    //Root* 
        root = getRoot();
    //SceneManager* 
        scnMgr = root->createSceneManager();

    // register our scene with the RTSS
    RTShader::ShaderGenerator* shadergen = RTShader::ShaderGenerator::getSingletonPtr();
    shadergen->addSceneManager(scnMgr);
    createScene();
    createCamera();
    createFrameListener();


    


}

void Game::createScene()
{
    // -- tutorial section start --
//! [turnlights]
    scnMgr->setAmbientLight(ColourValue(0.8, 0.1, 0.5));
    //! [turnlights]

    //! [newlight]
    Light* light = scnMgr->createLight("MainLight");
    SceneNode* lightNode = scnMgr->getRootSceneNode()->createChildSceneNode();
    lightNode->attachObject(light);
    //! [newlight]

    //! [lightpos]
    lightNode->setPosition(20, 80, 50);
    //! [lightpos]

    //OgreBites::TrayManager* 
        mTrayMgr = new OgreBites::TrayManager("InterfaceName", getRenderWindow());

    //you must add this in order to add a tray
    scnMgr->addRenderQueueListener(mOverlaySystem);
    //Once you have your tray manager, make sure you relay input events to it.
    addInputListener(mTrayMgr);

 
    sc = std::to_string(score);
    l = std::to_string(lives);

    //Title Label
    mInfoLabel = mTrayMgr->createLabel(TL_TOP, "TInfo", "GAME3121_Assignment1_Phu_Pham", 375);
    //Score Label
    mScoreLabel = mTrayMgr->createLabel(TL_TOPLEFT, "Curent Score", "Score:", 180);
    mScore = mTrayMgr->createLabel(TL_TOPLEFT, "score", sc, 180);
    //Lives Label
    mLivesLabel = mTrayMgr->createLabel(TL_TOPRIGHT, "Lives Remaining", "Lives:", 180);
    mPlayerLives = mTrayMgr->createLabel(TL_TOPRIGHT, "lives", l, 180);

    //FPS/TPU Label
    mFPS = mTrayMgr->createLabel(TL_BOTTOMLEFT, "FPS", "Frames/Second: 60", 200);
    mTPU = mTrayMgr->createLabel(TL_BOTTOMLEFT, "TPU", "Time/Update: 0m/s", 200);

    //Creates ball
    Ogre::Entity* ballEntity = scnMgr->createEntity(SceneManager::PrefabType::PT_SPHERE);

    mBall = new Ball(ballEntity, scnMgr);

    ballNode = mBall->getShape();


    //Creates paddle
    Ogre::Entity* paddleEntity = scnMgr->createEntity(SceneManager::PrefabType::PT_PLANE);
    
    mPlayerPaddle = new playerPaddle(paddleEntity, scnMgr);

    paddleNode = mPlayerPaddle->getPlayerShape();


}

void Game::createCamera()
{
    //! [camera]
    SceneNode* camNode = scnMgr->getRootSceneNode()->createChildSceneNode();

    // create the camera
    Camera* cam = scnMgr->createCamera("myCam");
    cam->setNearClipDistance(5); // specific to this sample
    cam->setAutoAspectRatio(true);
    camNode->attachObject(cam);
    camNode->setPosition(0, 0, 140);

    // and tell it to render into the main window
    getRenderWindow()->addViewport(cam);
    //! [camera]


    //! [cameramove]
    camNode->setPosition(0, 47, 222);


}

void Game::createFrameListener()
{
    Ogre::FrameListener* FrameListener = new ExampleFrameListener();
   
    mRoot->addFrameListener(FrameListener);
}

bool Game::frameRenderingQueued(const FrameEvent& evt)
{
    //Calling update for ball and paddle

    mPlayerPaddle->update(evt);
    mBall->update(evt);

    //Fixed frame update
    if (timeSinceLastFrame < deltaTime)
    {
        timeSinceLastFrame += evt.timeSinceLastFrame;
        numberOfFrame++;
    }
    //Getting frames per second
    else
    {
        frameRate = (float)numberOfFrame / timeSinceLastFrame;
        numberOfFrame = 0;
        timeSinceLastFrame = 0;
        char str[20];
        sprintf_s(str, "FPS: %.1f", frameRate);
        mFPS->setCaption(str);
    }
    //Getting time since last update
    char str1[80];
    sprintf_s(str1, "Time/Update: %.3f m/s", evt.timeSinceLastFrame);
    mTPU->setCaption(str1);

    //Check if game is over
    if (gameover)
    {

        if (mQuitButton->getState() == OgreBites::ButtonState::BS_DOWN)
        {
            getRoot()->queueEndRendering();
        }
        return true;
    }
    else
    {
        if (ballNode->getPosition().y < -bound)
        {

            if (lives > 0)
            {
                //Decrement lives of out of bound
                lives--;
                l = std::to_string(lives);
                mPlayerLives->setCaption(l);
                ballNode->setPosition(Ogre::Vector3(0, 100, 0));
                std::cout << "Lives:" << lives;
                mBall->reset();
            }
            //Display game over label
            else
            {
                mGameOverLabel = mTrayMgr->createLabel(TL_CENTER, "gameO", "GAME OVER!", 300);
                mQuitButton = mTrayMgr->createButton(TL_CENTER, "qbtn", "Quit Game", 300);
                gameover = true;
            }

        }
        //Collision detection
        AxisAlignedBox ballBox = ballNode->_getWorldAABB();
        AxisAlignedBox paddleBox = paddleNode->_getWorldAABB();
        if (ballBox.intersects(paddleBox))
        {
            if (isCollide == 0)
            {
                std::cout << "collide";
                isCollide = 1;
                movDirY = -1;
                mBall->setVelY(-1); //Ball constant Y velocity
                //Increment score
                score++;
                sc = std::to_string(score);
                mScore->setCaption(sc);
                std::cout << "score:" << score << std::endl;

                const auto attackVector = ballNode->getPosition() - paddleNode->getPosition();
                const auto normal = Ogre::Vector3(0, -1, 0);

                const auto dot = attackVector.dotProduct(normal);
                const auto ballAngle = acos(dot / attackVector.length()) * Ogre::Math::fRad2Deg;

                if ((attackVector.x > 0 && attackVector.y > 0) || (attackVector.x < 0 && attackVector.y > 0))
                    // Ball Direction Check
                {

                    if (ballAngle <= 135)
                    {

                        movDirX = 1;
                        movDirY = -1;
                        mBall->setVelY(-1);
                        mBall->setVelX(1);

                    }
                    else
                    {

                        movDirY = -1;
                        movDirX = -1;
                        mBall->setVelY(-1);
                        mBall->setVelX(-1);

                    }
                }
            }

        }
        else
            isCollide = 0;

    }
    return true;
}


bool Game::keyPressed(const KeyboardEvent& evt)
{
    switch (evt.keysym.sym)
    {
        //Move left
    case 'a':
    
        mPlayerPaddle->playerMoveLeft();
        break;


        //Move Right
    case 'd':
    
        mPlayerPaddle->playerMoveRight();
        break;


        //Exit game
    case SDLK_ESCAPE:
        getRoot()->queueEndRendering();
        break;

    default:
        break;
    }
    return true;
}



int main(int argc, char** argv)
{
    try
    {
        Game app;
        app.initApp();
        
        app.getRoot()->startRendering();
        app.closeApp();
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error occurred during execution: " << e.what() << '\n';
        return 1;
    }

    return 0;
}

//! [fullsource]
