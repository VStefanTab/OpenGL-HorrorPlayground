#pragma once
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "..\Textures\texturex.h"

#define TEX_WIDTH 256
#define TEX_HEIGHT 256

#define MESH_SIZE 30

extern float animationTime;
extern int animationActive ;

extern float cameraAngle;

extern int selectedPoint;

extern float cameraDistance;
extern float cameraHeight;
extern GLuint textureID;

void calculateSplinePoint(float t, float *result);
void generateHillMesh(int segments);
void createTexture();
void calculateNormal(float *v1, float *v2, float *v3, float *normal);