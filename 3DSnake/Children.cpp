#include "Children.h"

using namespace std;
using namespace Ogre;

Children::Children(Shark* shark, Ogre::SceneManager* sceneMgr):shark(shark), sceneMgr(sceneMgr)
{
  childrenNodes[0]=shark->getNode();
  children[0] = sceneMgr->createEntity("Default", "Shark.mesh");
  childrenEntityNode[0] = childrenNodes[0]->createChildSceneNode("FirstEntityNode",childrenNodes[0]->getPosition());
  animationState[0] = children[0]->getAnimationState("Swim");
  animationState[0]->setLoop(true);
  animationState[0]->setEnabled(true);
  
  number = 1;
  speed = 1;

}

void Children::add(void)
{
  if (number<NUMBER-1)
  {

    char name[16];
    sprintf( name, "children%d", number );
    children[number] = sceneMgr->createEntity(name, "Shark.mesh");
    
    childrenNodes[number] = sceneMgr->getRootSceneNode()->createChildSceneNode(String(name) + "Node",Vector3(0,0,0),Node::TS_WORLD /*itr->worldFragment->singleIntersection*/);
    childrenNodes[number]->setDirection(childrenNodes[number-1]->getPosition()-childrenNodes[number]->getPosition(),Node::TS_PARENT);

    childrenEntityNode[number] = childrenNodes[number]->createChildSceneNode(String(name) + "EntityNode",childrenNodes[number]->getPosition());
    childrenEntityNode[number]->yaw(Degree(-90));
    childrenEntityNode[number]->attachObject(children[number]);
    childrenEntityNode[number]->setScale(2.0f, 2.0f, 2.0f);
    
    animationState[number] = children[number]->getAnimationState("Swim");
    animationState[number]->setLoop(true);
    animationState[number]->setEnabled(true);
    
    number++;
  } // if
}

void Children::move(Real timeSinceLastFrame)
{
  if (number>0)
  {
    for(unsigned int i=1; i<number; i++)
    {
      
//       cout << "move started for " << i << "position = " << childrenNodes[i]->getPosition() << endl;
//       Vector3 src = childrenNodes[i]->getOrientation( ) * -Vector3::UNIT_SCALE;
//       Ogre::Quaternion quat = src.getRotationTo( childrenNodes[i-1]->getPosition() - childrenNodes[i]->getPosition() );
//       childrenNodes[i]->rotate( quat );

      Vector3 direction = childrenNodes[i-1]->getPosition() - childrenNodes[i]->getPosition();
      
      Real distance = direction.normalise();
      speed = distance/3;
      Real vitesse = speed*timeSinceLastFrame;
      
      childrenNodes[i]->setDirection(direction,Node::TS_WORLD);
//       childrenNodes[i]->translate(Vector3(childrenNodes[i-1]->getPosition().x-childrenNodes[i]->getPosition().x,childrenNodes[i-1]->getPosition().y-childrenNodes[i]->getPosition().y,childrenNodes[i-1]->getPosition().z-childrenNodes[i]->getPosition().z).normalisedCopy()*vitesse, Node::TS_WORLD);

      childrenNodes[i]->translate(direction*vitesse,Node::TS_WORLD);
//       cout << "move ended for " << i << "time = " << timeSinceLastFrame << "child = " << children[i] << endl;
      anim(timeSinceLastFrame, i);
    }
  }
}

void Children::anim(Real time,unsigned int num)
{
  animationState[num]->addTime(time/1);
  animationState[num] = children[num]->getAnimationState("Swim");
  animationState[num]->setLoop(true);
  animationState[num]->setEnabled(true);
}