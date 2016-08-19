#ifndef _SnakeFrameListener
#define _SnakeFrameListener

#include <CEGUI/CEGUISystem.h>
#include <CEGUI/CEGUISchemeManager.h>
// #include <OgreCEGUIRenderer.h>

// #include "MaterialInstance.h"
// #include "EntityMaterialInstance.h"
// #include "SubEntityMaterialInstance.h"

#include "Poisson.h"
#include "Shark.h"

#include "SnakeApplication.h"
#include "BaseFrameListener.h"

class SnakeFrameListener : public BaseFrameListener, public OIS::MouseListener, public OIS::KeyListener
{
  public :
    SnakeFrameListener(RenderWindow* win, Camera* cam, SceneManager *sceneMgr, Shark* shark, Poisson* poisson);
    ~SnakeFrameListener();

    bool nextLocation();
    
    bool frameStarted(const FrameEvent &evt);
    bool mouseMoved(const OIS::MouseEvent &e);

    bool mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id);
    bool mouseReleased(const OIS::MouseEvent &e, OIS::MouseButtonID id);
    bool keyPressed(const OIS::KeyEvent &e);
    bool keyReleased(const OIS::KeyEvent &e);
    
  protected:
    bool mContinue; // continue rendering or not
    
    Real mRotate, mMove, mDistance;
    Real mWalkSpeed;
    Ogre::Degree mYaw, mPitch, mRoll;
    Ogre::Vector3 mDirection, mDestination;
    
    bool mRMouseDown;
    bool mLMouseDown;
    
    Ogre::SceneManager *mSceneMgr;
    Ogre::SceneNode *mNode, *mCamNode, *mNodePersonnage, *staticNode;

    Shark* shark;
    Poisson * poisson;
}; 

#endif
