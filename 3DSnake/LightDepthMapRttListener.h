#ifndef __LightDepthMapRttListener__
#define __LightDepthMapRttListener__
// Just to change all entities materials in depth rtt

#include "BaseApplication.h"

class LightDepthMapRttListener : public Ogre::RenderTargetListener
{
  public:
    LightDepthMapRttListener(Ogre::SceneManager *sm, Ogre::ManualObject* mManualGodRays);
    ~LightDepthMapRttListener();

  private:
    Ogre::ManualObject* mManualGodRays;
    std::queue<std::string> mMaterials;	
    Ogre::SceneManager *mSceneMgr;
    
    void preRenderTargetUpdate(const Ogre::RenderTargetEvent& evt);
    void postRenderTargetUpdate(const Ogre::RenderTargetEvent& evt);
};

#endif
