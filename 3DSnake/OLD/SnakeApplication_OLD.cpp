#include "SnakeApplication.h"

using namespace std;
using namespace Ogre;

SnakeApplication::SnakeApplication()
{
}

SnakeApplication::~SnakeApplication() 
{
}
  



  void SnakeApplication::createCamera(void)
  {
    mCamera = mSceneMgr->createCamera("PlayerCam");
    mCamera->setNearClipDistance(5);
//       mCamera->setFarClipDistance(1000);
    mCameraMan = new OgreBites::SdkCameraMan(mCamera);

    cam1 = mSceneMgr->createCamera("Cam1");
    cam1->setPosition(Vector3(1000,2000,1000));
    cam1->lookAt(Vector3(1000,100,1000));

    cam2 = mSceneMgr->createCamera("Cam2");
    cam2->setPosition(Vector3(1000,100,2000));
    cam2->lookAt(Vector3(0,0,0));

    cam3 = mSceneMgr->createCamera("Cam3");
    cam3->setPosition(Vector3(1000,100,2000));
    cam3->lookAt(Vector3(0,0,0));

    cam1->setNearClipDistance(5);
    cam2->setNearClipDistance(5);
    cam3->setNearClipDistance(5);
    
    cout << " Camera created " << endl;
  }

  void SnakeApplication::createViewports(void)
  {
    
    cout << "************************************ creating viewports *************************************" << endl;
    
    vp = mWindow->addViewport(mCamera,1,0.0,0.0,0.5,0.5);
    vp->setBackgroundColour(ColourValue(0,0,0));
    mCamera->setAspectRatio(Real(vp->getActualWidth()) / Real(vp->getActualHeight()));
    
    vp1 = mWindow->addViewport(cam1,2,0.5,0.5,0.5,0.5);
    vp->setBackgroundColour(ColourValue(1,0,0));
    mCamera->setAspectRatio(Real(vp->getActualWidth()) / Real(vp->getActualHeight()));
  
    vp2 = mWindow->addViewport(cam2,3,0.0,0.5,0.5,0.5);
    vp->setBackgroundColour(ColourValue(0,1,0));
    mCamera->setAspectRatio(Real(vp->getActualWidth()) / Real(vp->getActualHeight()));
    
    vp3 = mWindow->addViewport(cam3,4,0.5,0.0,0.5,0.5);
    vp->setBackgroundColour(ColourValue(0,0,1));
    mCamera->setAspectRatio(Real(vp->getActualWidth()) / Real(vp->getActualHeight()));
    
	  cout << " Viewports created " << endl;
  }

  void SnakeApplication::createScene(void)
  {
    mSceneMgr->setWorldGeometry("terrain.cfg");
    Ogre::MaterialManager::getSingleton().setDefaultTextureFiltering(Ogre::TFO_ANISOTROPIC);
    Ogre::MaterialManager::getSingleton().setDefaultAnisotropy(7);
  
    cout << "********************************** creating scene ****************************************" << endl;

    ColourValue fadeColour(0.9, 0.9, 0.9);

    mSceneMgr->setFog(FOG_EXP,fadeColour, 0.001);

//       mSceneMgr->setSkyBox(true, "MonSkyBox");
	  
//       particleSys = new ParticleSystem ();
//       bullesEmit = new BullesEmitter (particleSys);
//       
//       bullesEmit->setPosition(Vector3(100,100,200));
//       bullesEmit->setEmissionRate(100.0);
//       bullesEmit->setColour(ColourValue(1,0,0));
    
    // HYDRAX content :
//       hydrax= new Hydrax::Hydrax(mSceneMgr, mCamera);

      sky = mSceneMgr->createLight("SkyRay");
      sky->setType(Light::LT_DIRECTIONAL);
// 	sky->setPosition(Vector3(0,1000,0));
      sky->setDirection(Vector3(0.55,-0.3,0.75));
      sky->setDiffuseColour(ColourValue(1,1,1));
      sky->setSpecularColour(ColourValue(0.4,0.4,5));
// 	sky->setAttenuation(2000,1.2,0.5,0.5);
      
/*	
      ray = mSceneMgr->createLight("SunRay");
      ray->setType(Light::LT_SPOTLIGHT);
      ray->setPosition(Vector3(0,1000,0));
      ray->setDirection(Vector3(0,-100,0));
      ray->setDiffuseColour(ColourValue(1,1,1));
      ray->setSpecularColour(ColourValue(1,1,1));
      ray->setAttenuation(5000,0,0,0);
      ray->setSpotlightRange(Radian(0),Radian(0.1),0.0);
      ray->setPowerScale(500);
      ray->setCastShadows(true);
      */

      
//       mSceneMgr->setAmbientLight( ColourValue( 0.1, 0.1, 0.6 ) );
//       mSceneMgr->setShadowTechnique(SHADOWTYPE_STENCIL_ADDITIVE);
/*
    Light * lightRay = mSceneMgr->createLight("LightRay");
    lightRay->setType(Light::LT_POINT);
    lightRay->setPosition(0,200,0);
    lightRay->setDiffuseColour(ColourValue(0.8,0.8,0.8));
    lightRay->setSpecularColour(ColourValue(1,1,1));*/
    
//       	cout << "light ray created " << endl;
//       
// //       camNode  = mSceneMgr->getRootSceneNode()->createChildSceneNode();
// //       lightRayNode = camNode->createChildSceneNode();
//       
//       cout << "child cam node  created" << endl;
//       
// //       lightRayNode->setScale(100,100,100);
//       
//             cout << " Lights created " << endl;
    
//       mBillboardSet = mSceneMgr->createBillboardSet("LightBillboardSet",1);
// //       mBillboardSet->setMaterialName("lightray");
//       mBillboardSet->setMaterialName("Examples/Flare");	
//       mBillboardSet->setBillboardRotationType(Ogre::BBR_VERTEX);
//       mBillboardSet->setCastShadows(false);
// //       Billboard *lightBillboard = mBillboardSet->createBillboard(0,0,0,ColourValue(0.5,0.3,1));
// //       lightRayNode->attachObject(mBillboardSet);
//       
//              cout << " Billboard created " << mBillboardSet << " camera : " << mCamera << endl;
      
//       createLightShafts(mBillboardSet,mCamera, 100);
/*      
	  cout << " LightShafts created " << endl;
    */
//       createLightCameraRTT();
//       mSceneMgr->setWorldGeometry("terrain.cfg");
//             cout << " Lightcamera Created " << endl;
    
      // Création du requin et des suivants.
      shark = new Shark(mSceneMgr);

      // Création des nodes d'objets.
      poisson = new Poisson(mSceneMgr);
      
      camNode = shark->getNode()->createChildSceneNode("mCamNode", Vector3(0, 0, 0));
      camNode->attachObject(mCamera);
      mCamera->setPosition(Vector3(0,50,50));
//	mCamera->lookAt(Vector3(0,60,0));
      mCamera->lookAt(shark->getNode()->getPosition());

    cout << "*********************** Scene Created *********************" << endl;
  }
  
  void SnakeApplication::createFrameListener(void)
  {
    cout << "************* creating FrameListener *****************" << endl;
    mFrameListener = new SnakeFrameListener(mWindow, mCamera, mSceneMgr, shark, poisson);
    mRoot->addFrameListener(mFrameListener);
    mFrameListener->showDebugOverlay(true);
  }
  
  void SnakeApplication::updateTextureProjectionMatrix()
  {
    cout << "updating Texture project " << endl;
    const Ogre::Matrix4 PROJECTIONCLIPSPACE2DTOIMAGESPACE_PERSPECTIVE(0.5,0,0,0.5,0,-0.5,0,0.5,0,0,1,0,0,0,0,1);
    
    Ogre::Matrix4 TexViewProj = (PROJECTIONCLIPSPACE2DTOIMAGESPACE_PERSPECTIVE * mCamera->getProjectionMatrixWithRSDepth() * mCamera->getViewMatrix()); 
    
    static_cast<Ogre::MaterialPtr>(Ogre::MaterialManager::getSingleton().getByName(""))->getTechnique(0)->getPass(0)->getVertexProgramParameters()->setNamedConstant("uTexViewProj",TexViewProj);
  }
  
  bool SnakeApplication::createLightShafts(BillboardSet* Billboard, Camera* LightCamera, const int &numberOfPlanes)
  {
    Ogre::Billboard *currentBB;
    
	  cout << " Camera created " << endl;
    
    float DistanceBetweenPlanes = (LightCamera->getFarClipDistance()-LightCamera->getNearClipDistance())/numberOfPlanes;
    const Vector3 *FrustumCorners = LightCamera->getWorldSpaceCorners();
    
	  cout << " variables initialisées " << endl;
    
    float NearWidth = (FrustumCorners[0]-FrustumCorners[1]).length(),
    NearHeight =  (FrustumCorners[1]-FrustumCorners[2]).length(),
    FarWidth =  (FrustumCorners[4]-FrustumCorners[5]).length(),
    FarHeight =  (FrustumCorners[5]-FrustumCorners[6]).length();
    
    float WidthStep = (FarWidth-NearWidth)/numberOfPlanes,
    HeightStep = (FarHeight-NearHeight)/numberOfPlanes;
    
    cout << " entree boucle " << endl;
    for(int k =0;k<numberOfPlanes;k++)
    {
      currentBB = Billboard->createBillboard(Vector3(0,0,-LightCamera->getNearClipDistance()-k*DistanceBetweenPlanes), ColourValue::White);
      currentBB->setDimensions(NearWidth + k*WidthStep,NearHeight + k* HeightStep);
    }
    return true;
  }
    
    
    void SnakeApplication::createLightCameraRTT()
      {
	      // Creat a texture for use as rtt
	      Ogre::TexturePtr LightCameraRTT = Ogre::TextureManager::getSingleton()
		      .createManual("LightDepthMap",
				    "General",
			Ogre::TEX_TYPE_2D,
						// 256*256 must be sufficient
			256, 
						256, 
						0,
			Ogre::PF_R8G8B8,
			Ogre::TU_RENDERTARGET);

cout << " Texture crée " << endl;
			
      Ogre::RenderTarget* RT_Texture = LightCameraRTT->getBuffer()->getRenderTarget();
      cout << " etape 1 " << endl;
      Ogre::Viewport *RT_Texture_Viewport = RT_Texture->addViewport(mCamera);
      cout << " etape 2 " << endl;
      RT_Texture_Viewport->setClearEveryFrame(true);
      cout << " etape 3 " << endl;
      RT_Texture_Viewport->setBackgroundColour(Ogre::ColourValue::Black);
	      cout << " etape 4 " << endl;
      RT_Texture_Viewport->setOverlaysEnabled(false);
	      cout << " etape 5 " << endl;
      RT_Texture_Viewport->setSkiesEnabled(false);
	      
      cout << " Texture initialisées " << endl;
      /*
	      // Add our depth listener
	      RT_Texture->addListener(new LightDepthMapRttListener(mSceneMgr, mBillboardSet));

		      cout << " depth listener ajoute " << endl;
	      
	      // Fill the texture in our material
	      static_cast<Ogre::MaterialPtr>(Ogre::MaterialManager::getSingleton().getByName("LightShafts"))->
		      getTechnique(0)->getPass(0)->getTextureUnitState(0)->
			  setTextureName("LightDepthMap");*/
      }

