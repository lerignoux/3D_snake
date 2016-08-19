#include "BaseApplication.h"

// Declare a subclass of the BaseFrameListener class
class MyListener : public BaseFrameListener
{
public:
    MyListener(RenderWindow* win, Camera* cam) : BaseFrameListener(win, cam)
    {
    }

    bool frameStarted(const FrameEvent& evt)
    {
        return BaseFrameListener::frameStarted(evt);        
    }

    bool frameEnded(const FrameEvent& evt)
    {
        return BaseFrameListener::frameEnded(evt);        
    }
};
/*
// Declare a subclass of the BaseApplication class
class SnakeApp : public BaseApplication 
{
public:
   SampleApp() 
   {
   }

protected:
   // Define what is in the scene
   void createScene(void)
   {        
     mSceneMgr->setWorldGeometry("terrain.cfg");

   }
  
   // Create new frame listener
   void createFrameListener(void)
   {
//        mFrameListener = new MyListener(mWindow, mCamera);
//        mRoot->addFrameListener(mFrameListener);
   }
};*/



#ifdef __cplusplus
extern "C" {
#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32 
// #define WIN32_LEAN_AND_MEAN 
// #include "windows.h" 
// INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT) 
#else 
int main(int argc, char **argv) 
#endif 
{
    // Instantiate our subclass
    SnakeApplication snakeApp;

    try {
        // ExampleApplication provides a go method, which starts the rendering.
        snakeApp.go();
    }
    catch (Ogre::Exception& e) {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32 
        MessageBoxA(NULL, e.getFullDescription().c_str(), "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
        std::cerr << "Exception:\n";
        std::cerr << e.getFullDescription().c_str() << "\n";
#endif
        return 1;
    }

return 0;
}

#ifdef __cplusplus
}
#endif
