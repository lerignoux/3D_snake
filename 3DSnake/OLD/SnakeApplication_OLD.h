#ifndef _SnakeApplication
#define _SnakeApplication

#include <CEGUI/CEGUISystem.h>
#include <CEGUI/CEGUISchemeManager.h>
// #include <OgreCEGUIRenderer.h>

#include "BaseApplication.h"

#include "Poisson.h"
#include "Shark.h"

#include "SnakeFrameListener.h"
#include "BaseApplication.h"

 class SnakeFrameListener;

class SnakeApplication : public BaseApplication
{
  
  public:
    SnakeApplication();
    ~SnakeApplication();
  
  protected:
    Ogre::Entity *personnage;
    Ogre::SceneNode *nodePersonnage, *node, *camNode, *staticNode, *nodeFish, *nodeAquarium, *lightRayNode;
    Shark* shark;
    Poisson *poisson;
    Ogre::Light *light, *sky, *ray;
    
    Ogre::Camera *cam1, *cam2, *cam3;
    Ogre::Viewport *vp, *vp1, *vp2, *vp3;

    SnakeFrameListener* mFrameListener;

  public:
    virtual void createCamera(void);
    virtual void createViewports(void);
    void createScene(void);
    void createFrameListener(void);
    void updateTextureProjectionMatrix();
    bool createLightShafts(BillboardSet* Billboard, Camera* LightCamera, const int &numberOfPlanes);
    void createLightCameraRTT();
  
    
// Just for change all entities materials in depth rtt
    Ogre::BillboardSet *mBillboardSet;
    // Knot scene node
    Ogre::SceneNode    *mKnotSN;

    // Current cookie selected
    int mCurrentCookie;


    
    
};

#endif
