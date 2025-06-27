#pragma once
#include <GL/gl.h>
#include <SOIL/SOIL.h>

extern GLuint metalTexture;
extern GLuint plasticTexture;
extern GLuint goldTexture;
extern GLuint onyxTexture;
extern GLuint tilesTexture;
extern GLuint pavingStonesTexture;
extern GLuint metalSheetTexture;
extern GLuint porcelainTexture;
extern GLuint pavingStonesPlainTexture;
extern GLuint porcelainPlainTexture;
extern GLuint metalSheetPlainTexture;
extern GLuint earthTexture;
extern GLuint glassTexture;
extern GLuint grassTexture;
extern GLuint brickChimneyTexture;
extern GLuint brickHouseTexture;
extern GLuint woodTexture;
extern GLuint trunkTexture;
extern GLuint roofTexture;
extern GLuint leavesTexture;

GLuint loadTexture(const char* filename);
void   drawTexturedCube(GLuint texture);
void   initTextures();
