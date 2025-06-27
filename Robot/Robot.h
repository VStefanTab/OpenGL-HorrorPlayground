#pragma once
#include "..\Textures\texturex.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_CHILDREN 15

typedef struct SceneNode
{
  char name[50];
  int isJoint;
  float angleX, angleY, angleZ;
  float posX, posY, posZ;
  float sizeX, sizeY, sizeZ;
  float colorR, colorG, colorB;

  struct SceneNode *parent;
  struct SceneNode *children[MAX_CHILDREN];
  int childCount;
} SceneNode;

extern unsigned char texture;

extern int jointCount;
extern SceneNode *joints[MAX_CHILDREN];
extern int windowWidth, windowHeight;
extern int legFrames;


typedef struct
{
  SceneNode *root;
} Robot;

void addJoint(SceneNode *node);
SceneNode *createNode(const char *name, int isJoint, SceneNode *parent);
extern SceneNode *selectedJoint;
SceneNode *findJoint(const char *name);
void drawComponent(SceneNode *node);
void updateNode(SceneNode *node);
void buildRobot(Robot *robot);
void animateRobot();
void robotAnimationTimer(int value);