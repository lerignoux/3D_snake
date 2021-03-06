#include "LightDepthMapRttListener.h"

LightDepthMapRttListener::LightDepthMapRttListener(Ogre::SceneManager *sm, Ogre::ManualObject* mManualGodRays): mSceneMgr(sm), mManualGodRays(mManualGodRays)
{
}

LightDepthMapRttListener::~LightDepthMapRttListener()
{
}

void LightDepthMapRttListener::preRenderTargetUpdate(const Ogre::RenderTargetEvent& evt)
{
  Ogre::SceneManager::MovableObjectIterator EntityIterator = mSceneMgr->getMovableObjectIterator("Entity");
  Ogre::Entity * CurrentEntity = NULL;
  unsigned int k = 0;

  mMaterials.empty();

  mManualGodRays->setVisible(false);

  while( EntityIterator.hasMoreElements() )
  {
    CurrentEntity = static_cast<Ogre::Entity *>(EntityIterator.peekNextValue());
    for( k = 0; k < CurrentEntity->getNumSubEntities(); k++ )
    {
      mMaterials.push(CurrentEntity->getSubEntity(k)->getMaterialName());
      CurrentEntity->getSubEntity(k)->setMaterialName("GodRaysDepth");
    }

    EntityIterator.moveNext();
  }
}

void LightDepthMapRttListener::postRenderTargetUpdate(const Ogre::RenderTargetEvent& evt)
{
  Ogre::SceneManager::MovableObjectIterator EntityIterator = mSceneMgr->getMovableObjectIterator("Entity");
  Ogre::Entity * CurrentEntity = NULL;
  unsigned int k = 0;

  mManualGodRays->setVisible(true);

  while( EntityIterator.hasMoreElements() )
  {
    CurrentEntity = static_cast<Ogre::Entity *>(EntityIterator.peekNextValue());
    for( k = 0; k < CurrentEntity->getNumSubEntities(); k++ )
    {
	    CurrentEntity->getSubEntity(k)->setMaterialName(mMaterials.front());
	    mMaterials.pop();
    }

    EntityIterator.moveNext();
  }
}
