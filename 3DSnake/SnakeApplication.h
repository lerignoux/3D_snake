/*
-----------------------------------------------------------------------------
Filename:    SnakeApplication.h
-----------------------------------------------------------------------------
 
This source file is part of the
   ___                 __    __ _ _    _ 
  /___\__ _ _ __ ___  / / /\ \ (_) | _(_)
 //  // _` | '__/ _ \ \ \/  \/ / | |/ / |
/ \_// (_| | | |  __/  \  /\  /| |   <| |
\___/ \__, |_|  \___|   \/  \/ |_|_|\_\_|
      |___/                              
	  Snake Framework
	  http://www.ogre3d.org/tikiwiki/
-----------------------------------------------------------------------------
*/
#ifndef __SnakeApplication_h_
#define __SnakeApplication_h_
 
 
#include "BaseApplication.h"
 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
 
#include "Poisson.h"
#include "Shark.h"
#include "Flora.h"
#include "GodRays.h"

#include <Terrain/OgreTerrain.h>
#include <Terrain/OgreTerrainGroup.h>

// #include <CEGUI/CEGUISystem.h>
// #include <CEGUI/CEGUISchemeManager.h>
// #include <CEGUI/RendererModules/Ogre/CEGUIOgreRenderer.h>

#define BASE_DIST = 100

class Shark;
 
class SnakeApplication : public BaseApplication
{
  private:
    Shark* shark;
    Poisson** poissons;
    Flora** flora;
    Ogre::Light *sky, *sky2;
    Ogre::Plane plane;    
    Ogre::Terrain *terrain;
    
    
    Ogre::TerrainGlobalOptions* mTerrainGlobals;
    Ogre::TerrainGroup* mTerrainGroup;
    bool mTerrainsImported;
 
    void defineTerrain(long x, long y);
    void initBlendMaps(Ogre::Terrain* terrain);
    void configureTerrainDefaults(Ogre::Light* light);

    OgreBites::Label* mInfoLabel;
    
    ///////// God Rays stuff //////////
    /// Camera used for rendering the shadow map and as light frustum
    Ogre::Camera       *mLightCamera;
    /// Light camera scene node
    Ogre::SceneNode    *mLightCameraSN;
    GodRays **godRays;
    Ogre::Light *mLight0;
    // Knot scene node
    Ogre::SceneNode    *mKnotSN;
    Ogre::Entity *mKnot;

    
    ///////// God Rays stuff //////////
    
    bool mMouseDown;     // If a mouse button is depressed
    Ogre::Real mToggle;    // The time left until next toggle
    Ogre::Real mRotate;   // The rotate constant
    Ogre::Real mMove;      // The movement constant
    Ogre::Vector3 mDirection;
  
    Ogre::Real mYaw;
    Ogre::Real mPitch;
    Ogre::Real mRoll;
    
    Ogre::RaySceneQuery *mRaySceneQuery;     // The ray scene query pointer

    
  public:
    SnakeApplication(void);
    virtual ~SnakeApplication(void);
    Ogre::Vector3 getGround(Ogre::Vector3);
    
  protected:
    virtual void createScene(void);
    virtual void createFrameListener(void);
    virtual void destroyScene(void);
    virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);
    virtual bool keyPressed( const OIS::KeyEvent &arg );
    virtual bool keyReleased( const OIS::KeyEvent &arg );
    virtual bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
    
  private:
    bool processUnbufferedInput(const Ogre::FrameEvent& evt);
};
 
#endif // #ifndef __SnakeApplication_h_
