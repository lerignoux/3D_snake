// ----------------------------------------------------------------------------
// Light shafts demo variables
// ----------------------------------------------------------------------------

#include "GodRays.h"

// God ray data struct
struct GodRayData
{
  GodRayData()
  {
  }

  // Arrays information:
  // [0] -> Current value
  // [1] -> Final value
  // [2] -> Step value
  // [3] -> Final-Current value
  // [4] -> Step addition
  Ogre::Radian MainAngle[5];
  float Radius[5];
  Ogre::Radian RotateAngle[5];

  float Dimension;

} GDData[_def_NumberOfRays];
  
    

using namespace std;
using namespace Ogre;

GodRays::GodRays(Ogre::SceneManager *mSceneMgr, Camera* mLightCamera, SceneNode* mLightCameraSN, int num): mSceneMgr(mSceneMgr), mLightCamera(mLightCamera), mLightCameraSN(mLightCameraSN), ID(num)
{
  raySceneNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("RaySceneNode"+num);
//   cout << "God Rays Constructed" << endl;
}

GodRays::~GodRays()
{
}


/** Calcule the current ray position from ray data
    @param RayData Ray data
	@return Two vertex position stored in a Ogre::Vector4
 */
Ogre::Vector4 GodRays::calculateRayPosition(const GodRayData& RayData)
{
//   cout << "calculating position" << endl;
  Ogre::Vector2 A = Ogre::Vector2(
    Ogre::Math::Sin(RayData.MainAngle[0]),
    Ogre::Math::Cos(RayData.MainAngle[0]))*RayData.Radius[0];

  Ogre::Vector2 B = Ogre::Vector2(
    Ogre::Math::Sin(RayData.RotateAngle[0]),
    Ogre::Math::Cos(RayData.RotateAngle[0]))*RayData.Dimension;

  Ogre::Vector4 Result = Ogre::Vector4(
    // X1
    A.x - B.x,
    // Y1
    A.y - B.y,
    // X2
    A.x + B.y,
    // Y2
    A.y + B.y);

//   cout << "position calculated" << endl;
return Result;
}

/** Update god rays
    @param RaysLength Rays lenght
	@param FarWidth Far clip distance width(Assuming Width = Heigth)
	@param Delta Delta Time since last frame
 */
void GodRays::updateRays(const float& RaysLength, const float& FarWidth, const int& NumberOfRays, float Delta)
{
  cout<< "updating rays" << endl;
  Delta *= _def_Simulation_Speed;

  mManualGodRays->beginUpdate(1);

  for(int k = 0; k < NumberOfRays; k++)
  {
    // Add steps
    GDData[k].Radius[0] += GDData[k].Radius[2]*Delta;
    GDData[k].Radius[4] += GDData[k].Radius[2]*Delta;
    GDData[k].MainAngle[0] += GDData[k].MainAngle[2]*Delta;
    GDData[k].MainAngle[4] += GDData[k].MainAngle[2]*Delta;
    GDData[k].RotateAngle[0] += GDData[k].RotateAngle[2]*Delta;
    GDData[k].RotateAngle[4] += GDData[k].RotateAngle[2]*Delta;

    // Check if final values needs to be recalculate
    if (Ogre::Math::Abs(GDData[k].Radius[4]) > Ogre::Math::Abs(GDData[k].Radius[3]))
    {
      GDData[k].Radius[1] = Ogre::Math::RangeRandom(-FarWidth/2, FarWidth/2);
      GDData[k].Radius[3] = GDData[k].Radius[1] - GDData[k].Radius[0];
      GDData[k].Radius[2] = GDData[k].Radius[3] / Ogre::Math::RangeRandom(90,100);
      GDData[k].Radius[4] = 0;
    }

    if (Ogre::Math::Abs(GDData[k].MainAngle[4].valueRadians()) > Ogre::Math::Abs(GDData[k].MainAngle[3].valueRadians()))
    {
      GDData[k].MainAngle[1] = Ogre::Degree(Ogre::Math::RangeRandom(0, 360));
      GDData[k].MainAngle[3] = GDData[k].MainAngle[1] - GDData[k].MainAngle[0];
      GDData[k].MainAngle[2] = GDData[k].MainAngle[3] / Ogre::Math::RangeRandom(90,100);
      GDData[k].MainAngle[4] = Ogre::Radian(0);
    }

    if (Ogre::Math::Abs(GDData[k].RotateAngle[4].valueRadians()) > Ogre::Math::Abs(GDData[k].RotateAngle[3].valueRadians()))
    {
      GDData[k].RotateAngle[1] = Ogre::Degree(Ogre::Math::RangeRandom(0, 360));
      GDData[k].RotateAngle[3] = GDData[k].RotateAngle[1] - GDData[k].RotateAngle[0];
      GDData[k].RotateAngle[2] = GDData[k].RotateAngle[3] / Ogre::Math::RangeRandom(90,100);
      GDData[k].RotateAngle[4] = Ogre::Radian(0);
    }

    // Get the position from ray data
    Ogre::Vector4 Pos = calculateRayPosition(GDData[k]);

    // A
    mManualGodRays->position(0, 0, 0);
    mManualGodRays->textureCoord(0.5,0);
    // B
    mManualGodRays->position(Pos.x, Pos.y, -RaysLength);
    mManualGodRays->textureCoord(0,1);
    // C
    mManualGodRays->position(Pos.z, Pos.w, -RaysLength);
    mManualGodRays->textureCoord(1,1);
  }

  mManualGodRays->end();
  cout << "rays updated" << endl;
}

// ----------------------------------------------------------------------------
// Define the application object
// This is derived from ExampleApplication which is the class OGRE provides to
// make it easier to set up OGRE without rewriting the same code all the time.
// You can override extra methods of ExampleApplication if you want to further
// specialise the setup routine, otherwise the only mandatory override is the
// 'createScene' method which is where you set up your own personal scene.
// ----------------------------------------------------------------------------
// class LightShaftsListener : public ExampleFrameListener
// {
// public:
//     SceneManager *mSceneMgr;
//     Real mKeyBuffer;
// 	Real mKnotRotation;
// 	bool mRotateEnable;
// 	bool mRotateKnot;
// 	
//     LightShaftsListener(RenderWindow* win, Camera* cam, SceneManager *sm)
//             : ExampleFrameListener(win,cam)
//             , mSceneMgr(sm)
//             , mKeyBuffer(-1)
// 			, mKnotRotation(0)
// 			, mRotateEnable(false)
// 			, mRotateKnot(false)
//     {
//     }
// 
//     bool frameStarted(const FrameEvent &e)
//     {
//         mKeyboard->capture();
// 
// 		// Enable/disable knot rotation
// 		if (mKeyboard->isKeyDown(OIS::KC_B) && mKeyBuffer < 0)
//         {
// 			mRotateKnot = !mRotateKnot;
// 
// 			mKeyBuffer = 0.5f;
// 		}
// 
// 		// Show/hide knot
// 		if (mKeyboard->isKeyDown(OIS::KC_N) && mKeyBuffer < 0)
//         {
// 			mKnotSN->getAttachedObject(0)->setVisible(
// 				!mKnotSN->getAttachedObject(0)->isVisible());
// 
// 			mKeyBuffer = 0.5f;
// 		}
// 
// 		mKeyBuffer -= e.timeSinceLastFrame;
//      
// 		// Update light position
//         updatePosition(e);
// 
// 		// Get frustum corners to calculate far plane dimension
// 		const Ogre::Vector3 *FrustumCorners = mLightCamera->getWorldSpaceCorners();
// 		float FarWidth   = (FrustumCorners[4] - FrustumCorners[5]).length();
// 
// 		// Update god rays
// 		updateRays(mLightCamera->getFarClipDistance(), FarWidth, _def_NumberOfRays, e.timeSinceLastFrame);
// 
// 		updateDebugOverlay();
// 		
//         return true;
//     }
// 
// 	void updatePosition(const FrameEvent &e)
// 	{
// 		// Fixed camera position
// 		mCamera->setPosition(Ogre::Vector3(0,0,0));
// 
// 		if (mRotateKnot)
// 		{
// 			mKnotRotation += 25*e.timeSinceLastFrame;
// 
// 			mKnotSN->setOrientation(
// 				Ogre::Quaternion(
// 				      Ogre::Degree(mKnotRotation),
// 				      Ogre::Vector3(0,1,0)));
// 		}
// 	}
// 
// 	void updateDebugOverlay()
// 	{
// 		Ogre::OverlayElement* guiDbg = OverlayManager::getSingleton().getOverlayElement("Core/DebugText");
// 		guiDbg->setCaption(
// 			"Show/hide knot("+Ogre::StringConverter::toString(mKnotSN->getAttachedObject(0)->isVisible())+"): Press N to change\n" +
// 			"Rotate knot("+Ogre::StringConverter::toString(mRotateKnot)+"): Press B to change");
// 	}
// };

// class SampleApp : public ExampleApplication
// {
// public:
//     // Basic constructor
//     SampleApp()
//     {}
// 
// protected:
// 	
//     // Just override the mandatory create scene method
//     void createScene(void)
//     {
// 		// Set some camera params
//         mCamera->setFarClipDistance(1000);
// 		mCamera->setNearClipDistance(0.25f);
// 		mCamera->setDirection(0,0,1);
// 
// 		mWindow->getViewport(0)->setBackgroundColour(Ogre::ColourValue(0.1, 0.4, 0.9));
// 
// 		// Set up light 0
// 		Ogre::Light *mLight0 = mSceneMgr->createLight("Light0");
// 		mLight0->setType(Light::LT_POINT);
//         mLight0->setPosition(0,200,0);
//         mLight0->setDiffuseColour(0.9, 0.9, 0.9);
//         mLight0->setSpecularColour(1, 1, 1);
// 
// 		// Set up our light camera
// 		mLightCamera = mSceneMgr->createCamera("LightCamera");
// 		mLightCamera->setProjectionType(Ogre::PT_PERSPECTIVE);
// 		// Not forget to set near+far distance in materials
// 		mLightCamera->setNearClipDistance(8);
// 		mLightCamera->setFarClipDistance(40);
// 		mLightCamera->setAspectRatio(1);
// 		mLightCamera->setFOVy(Ogre::Degree(17.5f));
// 		mLightCamera->setDebugDisplayEnabled(true);
// 		mLightCameraSN = mSceneMgr->getRootSceneNode()->createChildSceneNode();
// 		mLightCameraSN->setPosition(0,40,0);
// 		mLightCameraSN->attachObject(mLightCamera);
// 		mLightCameraSN->setDirection(0, -1, 0);
// 
// 		// Create god rays
// 		createGodRays(mSceneMgr, mLightCameraSN, mLightCamera, _def_NumberOfRays, 0.45f);
// 
// 		// Create a RRT for depth/shadow map
// 		createLightCameraRTT();
// 
// 		// Set a knot
// 		Ogre::Entity *mKnot = mSceneMgr->createEntity("Knot", "knot.mesh");
// 		mKnot->setMaterialName("Knot");
// 		mKnot->setVisible(false);
// 		mKnotSN = mLightCameraSN->createChildSceneNode();
// 		mKnotSN->attachObject(mKnot);
// 		mKnotSN->setPosition(0, 0, -17.5f);
// 		mKnotSN->setScale(0.0225, 0.0225, 0.0225);
// 
// 		mCamera->lookAt(mLightCameraSN->getPosition());
// 
// 		// NOTE: If you change light(Sun) position/orientation, recall it!(IE: each frame)
// 		updateMaterialsParameters();
// 
// 		// Add frame listener
// 		mRoot->addFrameListener(new LightShaftsListener(mWindow, mCamera, mSceneMgr));
//     }

	/** Call it every frame if the light position/orientation changes!
	 */
// 	void updateMaterialsParameters()
// 	{
// 		// Upload current position to light shafts materials
// 		static_cast<Ogre::MaterialPtr>(Ogre::MaterialManager::getSingleton().getByName("GodRays"))->
// 			getTechnique(0)->getPass(0)->getFragmentProgramParameters()->
// 			setNamedConstant( "uLightPosition", mLightCameraSN->getPosition());
// 		static_cast<Ogre::MaterialPtr>(Ogre::MaterialManager::getSingleton().getByName("GodRaysDepth"))->
// 			getTechnique(0)->getPass(0)->getFragmentProgramParameters()->
// 			setNamedConstant( "uLightPosition", mLightCameraSN->getPosition());
// 
// 		// For projective texturing
// 		const Ogre::Matrix4 PROJECTIONCLIPSPACE2DTOIMAGESPACE_PERSPECTIVE(
//                0.5,    0,    0,  0.5,
//                0,   -0.5,    0,  0.5,
//                0,      0,    1,    0,
//                0,      0,    0,    1);
// 		
// 		Ogre::Matrix4 TexViewProj = 
// 			PROJECTIONCLIPSPACE2DTOIMAGESPACE_PERSPECTIVE * 
// 			mLightCamera->getProjectionMatrixWithRSDepth() * 
// 			mLightCamera->getViewMatrix(); 
// 		
// 		static_cast<Ogre::MaterialPtr>(Ogre::MaterialManager::getSingleton().getByName("GodRays"))->
// 			getTechnique(0)->getPass(0)->getVertexProgramParameters()->
// 			    setNamedConstant( "uTexViewProj", TexViewProj );
// 	}

bool GodRays::createGodRays(Ogre::SceneManager *mSceneMgr, Ogre::SceneNode* mSceneNode, Ogre::Camera *LightCamera, const int &NumberOfRays, const float &RaysSize)
{
  cout << "creating rays"<< endl;
  // Calculate how long rays should be
  // 	 float RaysLength = LightCamera->getFarClipDistance();
  float RaysLength = 1000;

  cout << "length set" << endl;
  // Get frustum corners to calculate near/far planes dimensions
  // 	const Ogre::Vector3 *FrustumCorners = LightCamera->getWorldSpaceCorners();

  const Ogre::Vector3 FrustumCorners[8] = {Vector3(1000,1000,1000),Vector3(1500,1000,1000),Vector3(1500,1000,1500),Vector3(1000,1000,1500),Vector3(1000,0,1000),Vector3(1500,0,1000),Vector3(1500,0,1500),Vector3(1000,0,1500)};

  cout << "frustum corners founds" << endl;
  // Calcule far plane dimensions
  float FarWidth   = (FrustumCorners[4] - FrustumCorners[5]).length(), FarHeigth  = (FrustumCorners[5] - FrustumCorners[6]).length();

  cout << "creating manual god rays " << endl;
  // Create our manual objetc to create god rays poligons
  mManualGodRays = mSceneMgr->createManualObject("ManualGodRays"+ID);
  mManualGodRays->setDynamic(true);

  // God rays are rendered as triangles with add blend
  //       ______
  //      / SUN /
  //     /_____/
  //        /\ A(0,0)
  //       /  \
  //      /    \
  //     / RAY  \
  //    /        \
  //   /B_________\C
  //

  // Sun
  // (-,-)      (+,-)
  // 0,0        1,0
  // A _________B
  // |          |
  // |          |
  // |    O     |
  // |(-,+)     |(+,+)
  // |0,1_______|1,1
  // C          D
  mManualGodRays->begin("GodRaysSun", Ogre::RenderOperation::OT_TRIANGLE_LIST);
  mManualGodRays->setRenderQueueGroup(Ogre::RENDER_QUEUE_9);

  float SunScale = 0.75;

//   cout << "setting positions" << endl;
  // Firs triangle ACD
  // A
  mManualGodRays->position(-FarWidth*SunScale/2, -FarHeigth*SunScale/2, 0);
  mManualGodRays->textureCoord(0,0);
  mManualGodRays->index(0);
  // C
  mManualGodRays->position(-FarWidth*SunScale/2, FarHeigth*SunScale/2, 0);
  mManualGodRays->textureCoord(0,1);
  mManualGodRays->index(1);
  // D
  mManualGodRays->position(FarWidth*SunScale/2, FarHeigth*SunScale/2, 0);
  mManualGodRays->textureCoord(1,1);
  mManualGodRays->index(2);
  // Second triangle ABD
  // A
  mManualGodRays->position(-FarWidth*SunScale/2, -FarHeigth*SunScale/2, 0);
  mManualGodRays->textureCoord(0,0);
  mManualGodRays->index(3);
  // B
  mManualGodRays->position(FarWidth*SunScale/2, -FarHeigth*SunScale/2, 0);
  mManualGodRays->textureCoord(1,0);
  mManualGodRays->index(4);
  // D
  mManualGodRays->position(FarWidth*SunScale/2, FarHeigth*SunScale/2, 0);
  mManualGodRays->textureCoord(1,1);
  mManualGodRays->index(5);

  mManualGodRays->end();

  // Rays
  mManualGodRays->begin("GodRays", Ogre::RenderOperation::OT_TRIANGLE_LIST);
  mManualGodRays->setRenderQueueGroup(Ogre::RENDER_QUEUE_9);

  for(int k = 0; k < NumberOfRays; k++)
  {
    float RandomSize = Ogre::Math::RangeRandom(0.5,2);

    GDData[k].Dimension = RaysSize*RandomSize;
    GDData[k].Radius[0] = Ogre::Math::RangeRandom(-FarWidth/2, FarWidth/2);
    GDData[k].MainAngle[0] = Ogre::Degree(Ogre::Math::RangeRandom(0, 45));
    GDData[k].RotateAngle[0] = Ogre::Degree(Ogre::Math::RangeRandom(0, 360));

    GDData[k].Radius[1] = Ogre::Math::RangeRandom(-FarWidth/2, FarWidth/2);
    GDData[k].MainAngle[1] = Ogre::Degree(Ogre::Math::RangeRandom(0, 45));
    GDData[k].RotateAngle[1] = Ogre::Degree(Ogre::Math::RangeRandom(0, 360));

    GDData[k].Radius[3] = GDData[k].Radius[1] - GDData[k].Radius[0];
    GDData[k].MainAngle[3] = GDData[k].MainAngle[1] - GDData[k].MainAngle[0];
    GDData[k].RotateAngle[3] = GDData[k].RotateAngle[1] - GDData[k].RotateAngle[0];

    GDData[k].Radius[2] = GDData[k].Radius[3] / Ogre::Math::RangeRandom(90,100);
    GDData[k].MainAngle[2] = GDData[k].MainAngle[3] / Ogre::Math::RangeRandom(90,100);
    GDData[k].RotateAngle[2] = GDData[k].RotateAngle[3] / Ogre::Math::RangeRandom(90,100);

    GDData[k].Radius[4] = 0;
    GDData[k].MainAngle[4] = Ogre::Radian(0);
    GDData[k].RotateAngle[4] = Ogre::Radian(0);

    Ogre::Vector4 Pos = calculateRayPosition(GDData[k]);

    // A
    mManualGodRays->position(0, 0, 0);
    mManualGodRays->textureCoord(0.5,0);
    mManualGodRays->index(k*3);
    // B
    mManualGodRays->position(Pos.x, Pos.y, -RaysLength);
    mManualGodRays->textureCoord(0,1);
    mManualGodRays->index(k*3+1);
    // C
    mManualGodRays->position(Pos.z, Pos.w, -RaysLength);
    mManualGodRays->textureCoord(1,1);
    mManualGodRays->index(k*3+2);
  }

//   cout << "end loop" << endl;

  mManualGodRays->end();
  raySceneNode->attachObject(mManualGodRays);

//   cout << "rays created" << endl;
  return true;
}

void GodRays::createLightCameraRTT()
{
  cout << "creating rtt cam" << endl;
	// Creat a texture for use as rtt
  Ogre::TexturePtr LightCameraRTT = Ogre::TextureManager::getSingleton()
	.createManual("LightDepthMap", "General", Ogre::TEX_TYPE_2D, /*256*256 must be sufficient*/  256, 256, 0, Ogre::PF_R8G8B8, Ogre::TU_RENDERTARGET);

  cout << "manually created" << endl;  
  Ogre::RenderTarget* RT_Texture = LightCameraRTT->getBuffer()->getRenderTarget();
    
  cout << "starting viewport" << endl;
  Ogre::Viewport *RT_Texture_Viewport = RT_Texture->addViewport(mLightCamera);
  RT_Texture_Viewport->setClearEveryFrame(true);
  RT_Texture_Viewport->setBackgroundColour(Ogre::ColourValue::White);
  RT_Texture_Viewport->setOverlaysEnabled(false);
  RT_Texture_Viewport->setSkiesEnabled(false);
	
  cout << "viewport end" << endl;
  // Add our depth listener
  RT_Texture->addListener(new LightDepthMapRttListener(mSceneMgr,mManualGodRays));

  cout << "LightDepthMapRttListener made" << endl;
	// Fill the texture in our material
/*		static_cast<Ogre::MaterialPtr>(Ogre::MaterialManager::getSingleton().getByName("GodRays"))->
		getTechnique(0)->getPass(0)->getTextureUnitState(0)->
		    setTextureName("LightDepthMap");*/
		    cout << "rtt cam created" << endl;
}

    void GodRays::yaw(Degree degree)
    {
      raySceneNode->yaw(degree);
    }
    void GodRays::pitch(Degree degree)
    {
      raySceneNode->pitch(degree);
    }
    void GodRays::roll(Degree degree)
    {
      raySceneNode->roll(degree);
    }
    
    void GodRays::move(Vector3 position)
    {
      raySceneNode->setPosition(position);
    }