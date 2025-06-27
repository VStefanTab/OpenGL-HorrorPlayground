#include "Robot.h"

int windowWidth = 800, windowHeight = 600;

int jointCount;
SceneNode *joints[MAX_CHILDREN];
int armsFrames;
int legFrames;
int headFrames;

unsigned char texture;
// Robot robot;

void addJoint(SceneNode *node)
{
  for (jointCount = 0; jointCount < MAX_CHILDREN; jointCount++)
  {
    if (joints[jointCount] == NULL)
    {
      joints[jointCount] = node;
      return;
    }
  }
}

SceneNode *createNode(const char *name, int isJoint, SceneNode *parent)
{
  SceneNode *node = (SceneNode *)malloc(sizeof(SceneNode));
  strcpy(node->name, name);
  node->isJoint = isJoint;
  node->angleX = node->angleY = node->angleZ = 0.0f;
  node->posX = node->posY = node->posZ = 0.0f;
  node->sizeX = node->sizeY = node->sizeZ = 1.0f;
  node->colorR = node->colorG = node->colorB = 0.5f;
  node->parent = parent;
  node->childCount = 0;

  if (parent != NULL)
  {
    parent->children[parent->childCount++] = node;
  }
  return node;
}

SceneNode *selectedJoint = NULL;

SceneNode *findJoint(const char *name)
{
  for (int joint = 0; joint < jointCount; joint++)
  {
    if (strcmp(joints[joint]->name, name) == 0)
    {
      return joints[joint];
    }
  }
  return NULL;
}

void drawComponent(SceneNode *node)
{
  if (strstr(node->name, "Body") != NULL)
  {
    glEnable(GL_TEXTURE_2D);
    drawTexturedCube(onyxTexture);
    glDisable(GL_TEXTURE_2D);
  }
  else if (strcmp(node->name, "torso") == 0)
  {
    glEnable(GL_TEXTURE_2D);
    drawTexturedCube(tilesTexture);
    glDisable(GL_TEXTURE_2D);
  }
  else if (strstr(node->name, "neckJoint") != NULL)
  {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, metalTexture);
    glMatrixMode(GL_TEXTURE);
    glPushMatrix();
    glLoadIdentity();
    glScalef(node->sizeX, node->sizeY, 1.0f);
    glMatrixMode(GL_MODELVIEW);

    GLUquadric *quad = gluNewQuadric();
    gluQuadricTexture(quad, GL_TRUE);

    glPushMatrix();
    glRotatef(-90, 1, 0, 0);
    gluCylinder(quad, 0.2, 0.2, node->sizeY, 20, 20);
    glPopMatrix();
    gluDeleteQuadric(quad);

    glMatrixMode(GL_TEXTURE);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glDisable(GL_TEXTURE_2D);
  }
  else if (strstr(node->name, "Joint") != NULL)
  {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, plasticTexture);

    glMatrixMode(GL_TEXTURE);
    glPushMatrix();
    glLoadIdentity();
    glScalef(node->sizeX, node->sizeY, 1.0f);
    glRotatef(45, 1.0f, 0.0f, 0.0f);
    glMatrixMode(GL_MODELVIEW);

    GLUquadric *quad = gluNewQuadric();
    gluQuadricTexture(quad, GL_TRUE);

    glPushMatrix();
    gluSphere(quad, 0.6, 20, 20);
    glPopMatrix();

    gluDeleteQuadric(quad);

    glMatrixMode(GL_TEXTURE);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);

    glDisable(GL_TEXTURE_2D);
  }
  else if (strstr(node->name, "Arm") != NULL || strstr(node->name, "Leg") != NULL)
  {
    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, metalSheetTexture);

    glMatrixMode(GL_TEXTURE);
    glPushMatrix();
    glLoadIdentity();
    glScalef(node->sizeX + 10.0f, node->sizeY + 10.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);

    GLUquadric *quad = gluNewQuadric();
    gluQuadricTexture(quad, GL_TRUE);

    glPushMatrix();
    glRotatef(-90, 1, 0, 0); // Make cylinder vertical
    gluCylinder(quad, 0.13f, 0.2f, node->sizeY, 20, 20);
    glPopMatrix();

    gluDeleteQuadric(quad);

    glMatrixMode(GL_TEXTURE);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);

    glDisable(GL_TEXTURE_2D);
  }
  else if (strstr(node->name, "Head") != NULL)
  {

    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, porcelainPlainTexture);

    glMatrixMode(GL_TEXTURE);
    glPushMatrix();
    glLoadIdentity();

    glScalef(node->sizeX, node->sizeY, 0.0f);

    glMatrixMode(GL_MODELVIEW);
    glRotatef(90, 1.0f, .0f, .0f);
    GLUquadric *quad = gluNewQuadric();
    gluQuadricTexture(quad, GL_TRUE);
    gluQuadricNormals(quad, GLU_SMOOTH);
    gluSphere(quad, 0.8, 20, 20);
    gluDeleteQuadric(quad);

    glMatrixMode(GL_TEXTURE);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);

    glDisable(GL_TEXTURE_2D);
  }
  else if (strstr(node->name, "Hand") != NULL || strstr(node->name, "Foot"))
  {
    glEnable(GL_TEXTURE_2D);
    drawTexturedCube(pavingStonesPlainTexture);
    glDisable(GL_TEXTURE_2D);
  }
}

void updateNode(SceneNode *node)
{
  glPushMatrix();
  glTranslatef(node->posX, node->posY, node->posZ);
  glScalef(node->sizeX, node->sizeY, node->sizeZ);

  if (node->isJoint)
  {
    glRotatef(node->angleX, 1, 0, 0);
    glRotatef(node->angleY, 0, 1, 0);
    glRotatef(node->angleZ, 0, 0, 1);
    addJoint(node);
  }

  drawComponent(node);

  for (int i = 0; i < node->childCount; i++)
  {
    updateNode(node->children[i]);
  }

  glPopMatrix();
}

void buildRobot(Robot *robot)
{
  // Create root node (hip/lower body)
  robot->root = createNode("lowerBody", 0, NULL);
  robot->root->sizeX = 1.3f;
  robot->root->sizeY = .8f;
  robot->root->sizeZ = 1.0f;
  robot->root->colorR = .75f;
  robot->root->colorG = .75f;
  robot->root->colorB = .75f;

  // Torso
  SceneNode *torso = createNode("torso", 0, robot->root);
  torso->posY = 1.5f;
  torso->sizeX = 1.1f;
  torso->sizeY = 2.0f;
  torso->sizeZ = .8f;
  torso->colorR = .6f;
  torso->colorG = .2f;
  torso->colorB = .2f;

  // Head
  SceneNode *neckJoint = createNode("neckJoint", 1, torso);
  neckJoint->posY = .4f;
  neckJoint->sizeX = .6f;
  neckJoint->sizeY = .6f;

  SceneNode *head = createNode("Head", 0, neckJoint);
  head->posY = .8f;
  head->sizeX = .6f;
  head->sizeY = .5f;
  head->sizeZ = .6f;
  head->colorR = .8f;
  head->colorG = .8f;
  head->colorB = .2f;

  // Left arm
  SceneNode *lShoulderJoint = createNode("lShoulderJoint", 1, torso);
  lShoulderJoint->posX = -.47f;
  lShoulderJoint->posY = .38f;
  lShoulderJoint->sizeX = .2f;
  lShoulderJoint->sizeY = .2f;
  lShoulderJoint->sizeZ = .27f;

  SceneNode *lUpperArm = createNode("lUpperArm", 0, lShoulderJoint);
  lUpperArm->posX = -.5f;
  lUpperArm->posY = -3.5f;
  lUpperArm->sizeX = 3.0f;
  lUpperArm->sizeY = 2.0f;
  lUpperArm->sizeZ = 5.0f;
  lUpperArm->colorR = .2f;
  lUpperArm->colorG = .8f;
  lUpperArm->colorB = .2f;

  // Left Elbow
  SceneNode *lElbow = createNode("lElbowJoint", 1, lUpperArm);
  lElbow->posY = -.1f;
  lElbow->sizeX = .2f;
  lElbow->sizeY = .8f;
  lElbow->sizeZ = .2f;

  // Right arm (similar to left)
  SceneNode *rShoulderJoint = createNode("rShoulderJoint", 1, torso);
  rShoulderJoint->posX = .5f;
  rShoulderJoint->posY = .38f;
  rShoulderJoint->sizeX = .2f;
  rShoulderJoint->sizeY = .2f;
  rShoulderJoint->sizeZ = .27f;

  SceneNode *rUpperArm = createNode("rUpperArm", 0, rShoulderJoint);
  rUpperArm->posX = .5f;
  rUpperArm->posY = -3.5f;
  rUpperArm->sizeX = 3.0f;
  rUpperArm->sizeY = 2.0f;
  rUpperArm->sizeZ = 5.0f;
  rUpperArm->colorR = .2f;
  rUpperArm->colorG = .8f;
  rUpperArm->colorB = .2f;

  // right Elbow
  SceneNode *rElbow = createNode("rElbowJoint", 1, rUpperArm);
  rElbow->posY = -.1f;
  rElbow->sizeX = .2f;
  rElbow->sizeY = .8f;
  rElbow->sizeZ = .2f;

  // Left forearm
  SceneNode *lForearm = createNode("lForeArm", 0, lElbow);
  lForearm->posY = -2.5f;
  lForearm->sizeX = 3.0f;
  lForearm->sizeY = 1.7f;
  lForearm->sizeZ = 3.0f;
  lForearm->colorR = .2f;
  lForearm->colorG = .8f;
  lForearm->colorB = .2f;

  // Rigth forearm
  SceneNode *rForearm = createNode("rForeArm", 0, rElbow);
  rForearm->posY = -2.5f;
  rForearm->sizeX = 3.0f;
  rForearm->sizeY = 1.7f;
  rForearm->sizeZ = 3.0f;
  rForearm->colorR = .2f;
  rForearm->colorG = .8f;
  rForearm->colorB = .2f;
  // Left Wrist Joint
  SceneNode *lWrist = createNode("lWristJoint", 1, lForearm);
  lWrist->posY = -.1f;
  lWrist->sizeX = .2f;
  lWrist->sizeY = .5f;
  lWrist->sizeZ = .2f;
  // Right Wrist Joint
  SceneNode *rWrist = createNode("lWristJoint", 1, rForearm);
  rWrist->posY = -.1f;
  rWrist->sizeX = .2f;
  rWrist->sizeY = .5f;
  rWrist->sizeZ = .2f;

  // Left Hand
  SceneNode *lHand = createNode("lHand", 0, lWrist);
  lHand->posY = -0.5f;
  lHand->sizeX = 3.8f;
  lHand->sizeY = 1.0f;
  lHand->sizeZ = 1.6f;
  lHand->colorR = 1.0f;
  lHand->colorG = 1.0f;
  lHand->colorB = .3f;

  // Right Hand
  SceneNode *rHand = createNode("rHand", 0, rWrist);
  rHand->posY = -0.5f;
  rHand->sizeX = 3.8f;
  rHand->sizeY = 1.0f;
  rHand->sizeZ = 1.6f;
  rHand->colorR = 1.0f;
  rHand->colorG = 1.0f;
  rHand->colorB = .3f;

  // lF1
  SceneNode *lF1 = createNode("lF1", 0, lHand);
  lF1->posX = -.4f;
  lF1->posY = -.6f;
  lF1->sizeX = .1f;
  lF1->sizeY = 0.7f;
  lF1->sizeZ = .3f;

  // lF2
  SceneNode *lF2 = createNode("lF2", 0, lHand);
  lF2->posX = -.14f;
  lF2->posY = -.6f;
  lF2->sizeX = .1f;
  lF2->sizeY = .7f;
  lF2->sizeZ = .3f;

  // lF3
  SceneNode *lF3 = createNode("lF3", 0, lHand);
  lF3->posX = .1f;
  lF3->posY = -.6f;
  lF3->sizeX = .1f;
  lF3->sizeY = .7f;
  lF3->sizeZ = .3f;

  // lF4
  SceneNode *lF4 = createNode("lF4", 0, lHand);
  lF4->posX = .35f;
  lF4->posY = -.6f;
  lF4->sizeX = .1f;
  lF4->sizeY = .7f;
  lF4->sizeZ = .3f;
  //
  //// rF1
  SceneNode *rF1 = createNode("rF1", 0, rHand);
  rF1->posX = -.4f;
  rF1->posY = -.6f;
  rF1->sizeX = .1f;
  rF1->sizeY = .7f;
  rF1->sizeZ = .3f;
  //// rF2
  SceneNode *rF2 = createNode("rF2", 0, rHand);
  rF2->posX = -.14f;
  rF2->posY = -.6f;
  rF2->sizeX = .1f;
  rF2->sizeY = .7f;
  rF2->sizeZ = .3f;
  //// rF3
  SceneNode *rF3 = createNode("rF3", 0, rHand);
  rF3->posX = .1f;
  rF3->posY = -.6f;
  rF3->sizeX = .1f;
  rF3->sizeY = .7f;
  rF3->sizeZ = .3f;
  //// rF4
  SceneNode *rF4 = createNode("rF4", 0, rHand);
  rF4->posX = .35f;
  rF4->posY = -.6f;
  rF4->sizeX = .1f;
  rF4->sizeY = .7f;
  rF4->sizeZ = .3f;

  // Legs(similar pattern)
  // Left Leg
  SceneNode *lLegJoint = createNode("lLegJoint", 1, torso);
  lLegJoint->posX = -.3f;
  lLegJoint->posY = -1.04f;
  lLegJoint->sizeX = .2f;
  lLegJoint->sizeY = .2f;
  lLegJoint->sizeZ = .4f;

  SceneNode *lLeg = createNode("lLeg", 0, lLegJoint);
  lLeg->posX = .0f;
  lLeg->posY = -4.36f;
  lLeg->posZ = -.2f;
  lLeg->sizeX = 4.0f;
  lLeg->sizeY = 2.1f;
  lLeg->sizeZ = 5.0f;
  lLeg->colorR = .2f;
  lLeg->colorG = .8f;
  lLeg->colorB = .2f;

  // Lower Left Leg
  // Left Knee
  SceneNode *lKnee = createNode("lKneeJoint", 1, lLeg);
  lKnee->posX = .0f;
  lKnee->posY = -.2f;
  lKnee->sizeX = .22f;
  lKnee->sizeY = .4f;
  lKnee->sizeZ = .15f;

  SceneNode *lLowerLeg = createNode("lLowerLeg", 0, lKnee);
  lLowerLeg->posX = .0f;
  lLowerLeg->posY = -6.0f;
  lLowerLeg->posZ = -.2f;
  lLowerLeg->sizeX = 2.4f;
  lLowerLeg->sizeY = 2.4f;
  lLowerLeg->sizeZ = 5.0f;
  lLowerLeg->colorR = .2f;
  lLowerLeg->colorG = .8f;
  lLowerLeg->colorB = .2f;

  // Right Leg
  SceneNode *rLegJoint = createNode("rLegJoint", 1, torso);
  rLegJoint->posX = .3f;
  rLegJoint->posY = -1.04f;
  rLegJoint->sizeX = .2f;
  rLegJoint->sizeY = .2f;
  rLegJoint->sizeZ = .4f;

  SceneNode *rLeg = createNode("rLeg", 0, rLegJoint);
  rLeg->posX = .0f;
  rLeg->posY = -4.36f;
  rLeg->posZ = -.2f;
  rLeg->sizeX = 4.0f;
  rLeg->sizeY = 2.1f;
  rLeg->sizeZ = 5.0f;
  rLeg->colorR = .2f;
  rLeg->colorG = .8f;
  rLeg->colorB = .2f;

  // Lower Right Leg
  // Right Knee
  SceneNode *rKnee = createNode("rKneeJoint", 1, rLeg);
  rKnee->posX = .0f;
  rKnee->posY = -.2f;
  rKnee->sizeX = .22f;
  rKnee->sizeY = .4f;
  rKnee->sizeZ = .15f;

  SceneNode *rLowerLeg = createNode("rLowerLeg", 0, rKnee);
  rLowerLeg->posX = .0f;
  rLowerLeg->posY = -6.0f;
  rLowerLeg->posZ = -.2f;
  rLowerLeg->sizeX = 2.4f;
  rLowerLeg->sizeY = 2.4f;
  rLowerLeg->sizeZ = 5.0f;
  rLowerLeg->colorR = .2f;
  rLowerLeg->colorG = .8f;
  rLowerLeg->colorB = .2f;

  // Left foot joint
  SceneNode *lFootJoint = createNode("lFootJoint", 1, lLowerLeg);
  lFootJoint->posX = .0f;
  lFootJoint->posY = -.2f;
  lFootJoint->sizeX = .3f;
  lFootJoint->sizeY = .4f;
  lFootJoint->sizeZ = .2f;
  // Right foot Joint
  SceneNode *rFootJoint = createNode("rFootJoint", 1, rLowerLeg);
  rFootJoint->posX = .0f;
  rFootJoint->posY = -.2f;
  rFootJoint->sizeX = .3f;
  rFootJoint->sizeY = .4f;
  rFootJoint->sizeZ = .2f;
  // Left foot
  SceneNode *lFoot = createNode("lFoot", 0, lFootJoint);
  lFoot->posY = -.7f;
  lFoot->posZ = 1.0f;
  lFoot->sizeX = 2.0f;
  lFoot->sizeY = 1.0f;
  lFoot->sizeZ = 4.0f;
  lFoot->colorR = .2f;
  lFoot->colorG = .8f;
  lFoot->colorB = .2f;
  // Right foot
  SceneNode *rFoot = createNode("rFoot", 0, rFootJoint);
  rFoot->posY = -.7f;
  rFoot->posZ = 1.0f;
  rFoot->sizeX = 2.0f;
  rFoot->sizeY = 1.0f;
  rFoot->sizeZ = 4.0f;
  rFoot->colorR = .2f;
  rFoot->colorG = .8f;
  rFoot->colorB = .2f;
}

void animateRobot()
{
  float animationSpeed = 0.04f;
  float amplitude = 30.0f;

  float kneeBend = (cos(legFrames * animationSpeed * 0.2f) + 1.0f) * 25.0f;
  float elbowMovement = (cos(armsFrames * animationSpeed * 0.2f) + 1.0f) * 50.0f;
  for (int j = 0; j < jointCount; j++)
  {
    if (strcmp(joints[j]->name, "lLegJoint") == 0)
    {
      joints[j]->angleX = sin(legFrames * animationSpeed * 0.2f) * amplitude;
    }

    if (strcmp(joints[j]->name, "rLegJoint") == 0)
    {
      joints[j]->angleX = -sin(legFrames * animationSpeed * 0.2f) * amplitude;
    }

    if (strcmp(joints[j]->name, "lKneeJoint") == 0)
    {
      joints[j]->angleX = kneeBend;
    }

    if (strcmp(joints[j]->name, "rKneeJoint") == 0)
    {
      joints[j]->angleX = kneeBend;
    }

    legFrames++;
  }
}

void robotAnimationTimer(int value)
{
  animateRobot();
  glutPostRedisplay();
  glutTimerFunc(16, robotAnimationTimer, 0); // ~60 FPS
}