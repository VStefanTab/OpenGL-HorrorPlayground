#include "texturex.h"
#include <GL/gl.h>
#include <stdio.h>

GLuint metalTexture;
GLuint plasticTexture;
GLuint goldTexture;
GLuint onyxTexture;
GLuint tilesTexture;
GLuint pavingStonesTexture;
GLuint pavingStonesPlainTexture;
GLuint metalSheetTexture;
GLuint metalSheetPlainTexture;
GLuint porcelainTexture;
GLuint porcelainPlainTexture;
GLuint earthTexture;
GLuint glassTexture;
GLuint grassTexture;
GLuint brickChimneyTexture;
GLuint brickHouseTexture;
GLuint woodTexture;
GLuint trunkTexture;
GLuint roofTexture;
GLuint leavesTexture;

GLuint loadTexture(const char *filename)
{
  GLuint textureID;
  glGenTextures(1, &textureID);
  glBindTexture(GL_TEXTURE_2D, textureID);

  int width, height;
  unsigned char *image = SOIL_load_image(filename, &width, &height, 0, SOIL_LOAD_RGB);
  printf("Trying to load: %s\n", filename);
  if (!image)
  {
    printf("SOIL failed to load image: %s\n", SOIL_last_result());
  }
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
               GL_UNSIGNED_BYTE, image);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  SOIL_free_image_data(image);
  return textureID;
}

void drawTexturedCube(GLuint texture)
{
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texture);

  glBegin(GL_QUADS);
  // Front face
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(-0.5f, -0.5f, 0.5f); // 1

  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(0.5f, -0.5f, 0.5f); // 2

  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(0.5f, 0.5f, 0.5f); // 3

  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(-0.5f, 0.5f, 0.5f); // 4

  // back face
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(-0.5f, 0.5f, -0.5f); // 5

  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(-0.5f, -0.5f, -0.5f); // 6

  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(0.5f, -0.5f, -0.5f); // 7

  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(0.5f, 0.5f, -0.5f); // 8

  // left side face
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(-0.5f, -0.5f, 0.5f); // 1

  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(-0.5f, -0.5f, -0.5f); // 6

  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(-0.5f, 0.5f, -0.5f); // 5

  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(-0.5f, 0.5f, 0.5f); // 4

  // right side face
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(0.5f, -0.5f, 0.5f); // 2

  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(.5f, -0.5f, -0.5f); // 7

  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(.5f, .5f, -.5f); // 8

  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(.5f, .5f, .5f); // 3

  // up face
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(-.5f, .5f, .5f); // 4

  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(.5f, .5f, .5f); // 3

  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(.5f, .5f, -.5f); // 8

  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(-.5f, .5f, -.5f); // 5

  // down face
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(-.5f, -.5f, .5f); // 1

  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(.5f, -.5f, .5f); // 2

  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(.5f, -.5f, -.5f); // 7

  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(-.5f, -.5f, -.5f); // 6

  glEnd();
  glDisable(GL_TEXTURE_2D);
}

void initMetal() { metalTexture = loadTexture("Textures/Attachaments/Metal.jpg"); }
void initPlastic() { plasticTexture = loadTexture("Textures/Attachaments/plastic.jpg"); }
void initCleanMetal() { goldTexture = loadTexture("Textures/Attachaments/MetalClean.png"); }
void initOnyx() { onyxTexture = loadTexture("Textures/Attachaments/Onyx.png"); }
void initTiles() { tilesTexture = loadTexture("Textures/Attachaments/Tiles.png"); }
void initPavingStones()
{
  pavingStonesTexture = loadTexture("Textures/Attachaments/PavingStones.png");
  pavingStonesPlainTexture = loadTexture("Textures/Attachaments/PavingStonesSquare.png");
}
void initMetalSheets()
{
  metalSheetTexture = loadTexture("Textures/Attachaments/SheetMetal.png");
  metalSheetPlainTexture = loadTexture("Textures/Attachaments/SheetMetalPlain.png");
}
void initPorcelain()
{
  porcelainTexture = loadTexture("Textures/Attachaments/Porcelain.png");
  porcelainPlainTexture = loadTexture("Textures/Attachaments/PorcelainPlain.png");
}

void initEarth()
{
  earthTexture = loadTexture("Textures/Attachaments/earth.jpg");
}
void initGlass()
{
  glassTexture = loadTexture("Textures/Attachaments/glass.jpg");
}
void initGrass()
{
  grassTexture = loadTexture("Textures/Attachaments/grass.jpg");
}
void initChimney()
{
  brickChimneyTexture = loadTexture("Textures/Attachaments/brickChimney.jpg");
}
void initHouse()
{
  brickHouseTexture = loadTexture("Textures/Attachaments/brickHouse.jpg");
}

void initWood()
{
  woodTexture = loadTexture("Textures/Attachaments/wood.jpg");
}

void initTrunk()
{
  trunkTexture = loadTexture("Textures/Attachaments/trunk.jpg");
}

void initLeaves()
{
  leavesTexture = loadTexture("Textures/Attachaments/treeLeaves.jpg");
}

void initRoof()
{
  roofTexture = loadTexture("Textures/Attachaments/roof.jpg");
}

void initTextures()
{
  initMetal();
  initPlastic();
  initCleanMetal();
  initOnyx();
  initTiles();
  initPorcelain();
  initMetalSheets();
  initPavingStones();
  initEarth();
  initGlass();
  initGrass();
  initChimney();
  initHouse();
  initWood();
  initTrunk();
  initLeaves();
  initRoof();
}
