#pragma once
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>
#include <stdbool.h>
#include "..\Textures\texturex.h"

void Foundation();
void HouseBase();
void WroofWroof();
void door();
void window(GLfloat x, GLfloat y, GLfloat z);
void drawChimney(GLfloat x, GLfloat y, GLfloat z, GLfloat width, GLfloat height,
                 GLfloat depth);
void drawTrunk();
void drawCrown();
void Tree(GLfloat x, GLfloat y, GLfloat z);
void drawFence();
        