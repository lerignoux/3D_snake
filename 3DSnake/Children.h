#ifndef __Children__
#define __Children__

#include "BaseApplication.h"
#include "Shark.h"

#define NUMBER 50

class Shark;

class Children
{
  private:
    Ogre::Degree yaw, pitch, roll, virage;
    Ogre::Degree yawFactor, pitchFactor, rollFactor;

    int number;
    Ogre::Real speed;

    Ogre::Entity *children[NUMBER];
    Ogre::SceneNode *childrenNodes[NUMBER];
    Ogre::SceneNode *childrenEntityNode[NUMBER];
    Ogre::SceneManager* sceneMgr;
    
    Ogre::AnimationState *animationState[NUMBER];
    
    Shark* shark;
    
  public:
    Children(Shark* shark, Ogre::SceneManager* sceneMgr);
    ~Children();
  
    void add();
    void move(Ogre::Real);
    void anim(Ogre::Real,unsigned int);
};

#endif
