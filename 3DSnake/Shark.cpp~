#include "Shark.h"

using namespace std;
using namespace Ogre;

Shark::Shark(SceneManager *sceneMgr, SnakeApplication *snakeApp):snakeApp(snakeApp)
{
  
  cout << "creation requin" << endl;
  yawFactor = Degree(10);
  pitchFactor = Degree(10);
  rollFactor = Degree(10);
  
  yaw = Degree (0);
  pitch =  Degree (0);
  roll =  Degree (0);
  rotating = false;
  rotationFactor = 0.3f;
  
  startingRotationDirection = Vector3(1,0,0);
  currentRotationDirection = Vector3(1,0,0);
  finalRotationDirection = Vector3(1,0,0);
  /*
  rotationSource = new Quaternion(sharkNode->getOrientation());
  rotationDirection = new Quaternion(rotationSource);*/
  
  vitesse = 20;
  
  nextPosition = Vector3(6,5,5);
    
  sharkNode = sceneMgr->getRootSceneNode()->createChildSceneNode("sharkNode",Vector3(1550,550,1550));
  sharkEntityNode = sharkNode->createChildSceneNode("sharkEntityNode",Vector3(0,0,0));
//  sharkEntityNode->pitch(Degree(-90));
//  sharkEntityNode->roll(Degree(180));
  sharkEntityNode->yaw(Degree(-180));

  sharkEntity = sceneMgr->createEntity("Shark", "Shark.mesh");
  sharkEntity->setMaterialName("HHDSKIN");
  sharkEntity->setCastShadows(true);
  sharkNode->setScale(10.0f, 10.0f, 10.0f);

  sharkEntityNode->attachObject(sharkEntity);
  
  animationState = sharkEntity->getAnimationState("Swim");
  animationState->setLoop(true);
  animationState->setEnabled(true);
  
  eatAnimationState = sharkEntity->getAnimationState("Eat");
  eatAnimationState->setLoop(false);
  eatAnimationState->setEnabled(false);
  
  out = false;
  
  children = new Children(this, sceneMgr);
  
  vectFront = Vector3(1,0,0);
  vectLeft = Vector3(0,0,-1);
  vectUp = Vector3(0,1,0);
  direction=vectFront;
  nextDirection=vectFront;
  commandeDirectionnelle = 4;
}
  
Vector3 Shark::getPosition()
{
  return sharkNode->getPosition();
}

SceneNode* Shark::getNode()
{
  return sharkNode;
}

void Shark::move(Vector3 direction,Real timeSinceLastFrame, Real yaw, Real pitch, Real roll, Node::TransformSpace ref)
{
  sharkNode->translate(direction*timeSinceLastFrame*vitesse, ref); 
  Vector3 ground = snakeApp->getGround(getPosition());
  if (ground.y > getPosition().y) sharkNode->setPosition(ground);
  anim(timeSinceLastFrame);
  
  rotationSource = sharkNode->getOrientation();
  Quaternion delta = Quaternion::Slerp(0.1, rotationSource, rotationDirection, true);
  sharkNode->setOrientation(delta);

  position = sharkNode->getPosition();
  children->move(timeSinceLastFrame);
}

void Shark::move(Ogre::Real timeSinceLastFrame, Node::TransformSpace ref)
{
  setDirection();
  move(direction, timeSinceLastFrame,0 ,0 ,0, ref);
 
  children->move(timeSinceLastFrame);
}

void Shark::setDirection(void)
{
  if (!redirection())
  {
    cout << "distance = " << Shark::getPosition().squaredDistance(getRealPos(nextPosition)) << endl;
    if (Shark::getPosition().squaredDistance(getRealPos(nextPosition))<1000)
    {
      rotationDirection = (sharkNode->getOrientation()* Vector3::UNIT_X).getRotationTo(nextDirection) * sharkNode->getOrientation();
      rotating = true;
      nextPosition = nextPosition+nextDirection;
      updateRotationVectors();
      commandeDirectionnelle = 4;
    }
  }
}


void Shark::left()
{
  commandeDirectionnelle = 0;
  nextDirection = vectLeft;
}

void Shark::right()
{
  commandeDirectionnelle = 1;
  nextDirection = -vectLeft;
}

void Shark::up()
{
  commandeDirectionnelle = 2;
    nextDirection = vectUp;
}

void Shark::down()
{
  commandeDirectionnelle = 3;
  nextDirection = -vectUp;
}


void Shark::updateRotationVectors(void)
{
  Vector3 tmp;
 
  switch (commandeDirectionnelle)
  {
  /* Case ou l'on tourne a gauche */ 
    case 0:
      tmp = vectFront;
      vectFront = vectLeft;
      vectLeft = -tmp;
      break;
    /* Droite */
    case 1:
      tmp = vectFront;
      vectFront = -vectLeft;
      vectLeft = tmp;
      break;
    /*Haut*/
    case 2:
      tmp = vectFront;
      vectFront = vectUp;
      vectUp = -tmp;
      break;
    /*Bas*/
    case 3:
      tmp = vectFront;
      vectFront = -vectUp;
      vectUp = tmp;
      break;
  }
}


Vector3 Shark::getRealPos(Vector3 vect)
{
  return(Vector3(1000+vect.x*100+50, vect.y*100+50, 1000+vect.z*100+50));
}


void Shark::anim(Real time)
{
  if (eatAnimationState->getEnabled())
  {
    eatAnimationState = sharkEntity->getAnimationState("Eat");
    eatAnimationState->addTime(time);
    if (eatAnimationState->hasEnded())
    {
      eatAnimationState->setEnabled(false);
      eatAnimationState->setTimePosition(0);
      animationState->setEnabled(true);
    }
  }
  else
  {
    animationState->addTime(time);
    animationState = sharkEntity->getAnimationState("Swim");
    animationState->setLoop(true);
    animationState->setEnabled(true);
  }
}


void Shark::eatAnim(Real time)
{
  eatAnimationState->setEnabled(true);
  animationState->setEnabled(false);
}

void Shark::spin()
{
  sharkNode->yaw(Degree(180), Node::TS_LOCAL);
}

bool Shark::redirection()
{
  if (sharkNode->getPosition().x >2000 || sharkNode->getPosition().x<1000
    || sharkNode->getPosition().y >1000 || sharkNode->getPosition().y<0
    || sharkNode->getPosition().z >2000 || sharkNode->getPosition().z<1000)
  {
    out=true;
    if(virage<Degree(180))
    {
      sharkNode->yaw(Degree(5));
      virage=virage+Degree(5);
    }
  }
  else
  {
    out=false;
    virage=Degree(0);
  }
  return out;
}

void Shark::add()
{
   children->add();
}
