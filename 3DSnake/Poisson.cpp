#include "Poisson.h"

using namespace std;
using namespace Ogre;

unsigned int Poisson::indice = 0;

Poisson::Poisson(SceneManager *sceneMgr, int type)
  {
      char meshName[16], nodeName[16],  entityName[16];
      sprintf( meshName, "Fish%d.mesh", (type%2)+1);
      sprintf( nodeName, "FishNode_%d",Poisson::indice);
      sprintf( entityName, "Fish_%d",Poisson::indice);
      
      poissonNode=sceneMgr->getRootSceneNode()->createChildSceneNode(nodeName, Vector3(100, 20, 20));
      poissonEntity = sceneMgr->createEntity(entityName,meshName);
      Poisson::indice++;
      poissonNode->yaw(Degree(-90));
//       poissonNode->roll(Degree(180));
      poissonNode->setScale(0.2f,0.2f,0.2f);
      poissonNode->attachObject(poissonEntity);
      
      animationState = poissonEntity->getAnimationState("Wait");
      animationState->setLoop(true);
      animationState->setEnabled(true);
      
      move();
  }
  
  Vector3 Poisson::getPosition()
  {
    return position;
  }
  
void Poisson::move()
  {
    position=Vector3(1000+(rand()%10)*100+50, (rand()%10)*100+50, 1000+(rand()%10)*100+50);
    poissonNode->setPosition(position);
  }
  
  void Poisson::anim(Real time)
{
  animationState->addTime(time/3);
  animationState = poissonEntity->getAnimationState("Wait");
  animationState->setLoop(true);
  animationState->setEnabled(true);
}