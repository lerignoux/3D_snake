#include "Flora.h"

using namespace std;
using namespace Ogre;

unsigned int Flora::indice = 0;

Flora::Flora(SceneManager *sceneMgr, int type)
  {
      Flora::indice++;
      char meshName[16], nodeName[16],  entityName[16];
      sprintf( meshName, "Flora%d.mesh", type%5);
      sprintf( nodeName, "FloraNode_%d",Flora::indice);
      sprintf( entityName, "Flora_%d",Flora::indice);
      
//       cout << meshName << nodeName << entityName << endl;
      
      floraNode=sceneMgr->getRootSceneNode()->createChildSceneNode(nodeName, Vector3(100, 20, 20));
      floraEntity = sceneMgr->createEntity(entityName,meshName);
      floraNode->yaw(Degree(-90));
      floraNode->setScale(5.f,2.0f,5.f);
      floraNode->attachObject(floraEntity);
      
  }
  
  Vector3 Flora::getPosition()
  {
    return floraNode->getPosition();
  }
  
void Flora::move(Vector3 position)
  {
    floraNode->setPosition(position);
  }
  
  void Flora::anim(Real time)
{

}