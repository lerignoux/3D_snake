#ifndef __Flora__
#define __Flora__

#include "BaseApplication.h"

class Flora
{
  private:
    Ogre::Vector3 position;
    Ogre::Entity *floraEntity;
    Ogre::SceneNode *floraNode;
    
    Ogre::AnimationState *animationState;
    
    static unsigned int indice;
    
  public:
    Flora(Ogre::SceneManager *sceneMgr, int);
    ~Flora();
  
    Ogre::Vector3 getPosition();
    void move(Ogre::Vector3);
    void anim(Ogre::Real);
};

#endif

