#include "House.h"

void Foundation()
{
  glPushMatrix();
  glTranslatef(0.0f, -1.07f, 1.0f);
  glScalef(20.0f, 0.0f, 20.0f);

  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, grassTexture);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(-1.0f, 0.0f, -1.0f);
  glTexCoord2f(0.0f, 5.0f);
  glVertex3f(-1.0f, 0.0f, 1.0f);
  glTexCoord2f(5.0f, 5.0f);
  glVertex3f(1.0f, 0.0f, 1.0f);
  glTexCoord2f(5.0f, 0.0f);
  glVertex3f(1.0f, 0.0f, -1.0f);
  glEnd();
  glDisable(GL_TEXTURE_2D);
  glPopMatrix();
}

void HouseBase()
{
  glPushMatrix();
  glTranslatef(0.0f, -0.05f, 0.0f);
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, brickHouseTexture);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,  GL_MODULATE);
  glPushMatrix();
  glScalef(2.0f, 1.9f, 2.2f);
  drawTexturedCube(brickHouseTexture);
  glPopMatrix();
  glDisable(GL_TEXTURE_2D);
  glPopMatrix();
}

void WroofWroof()
{
  glPushMatrix();
  glTranslatef(0.0f, 0.9f, 0.0f);
  glScalef(1.2f, 1.0f, 1.2f);

  GLfloat vertices[6][3] = {
      {1.0f, 0.0f, -1.0f}, {0.0f, 1.0f, -1.0f}, {-1.0f, 0.0f, -1.0f}, {1.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 1.0f}, {-1.0f, 0.0f, 1.0f}};
  GLint squares[3][4] = {{0, 1, 4, 3}, {0, 2, 5, 3}, {1, 2, 5, 4}};
  GLint triangles[2][3] = {{4, 3, 5}, {1, 0, 2}};

  static const GLfloat uvQuad[4][2] = {
      {0.0f, 1.0f}, // top-left
      {1.0f, 1.0f}, // top-right
      {1.0f, 0.0f}, // bottom-right
      {0.0f, 0.0f}  // bottom-left
  };
  static const GLfloat uvTri[3][2] = {
      {0.5f, 1.0f}, // top-center
      {1.0f, 0.0f}, // bottom-right
      {0.0f, 0.0f}  // bottom-left
  };


  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, roofTexture);

  glBegin(GL_QUADS);
  for (int f = 0; f < 3; f++)
  {
    for (int c = 0; c < 4; c++)
    {
      glTexCoord2fv(uvQuad[c]);
      glVertex3fv(vertices[squares[f][c]]);
    }
  }
  glEnd();

  glBegin(GL_TRIANGLES);
  for (int t = 0; t < 2; t++)
  {
    for (int c = 0; c < 3; c++)
    {
      glTexCoord2fv(uvTri[c]);
      glVertex3fv(vertices[triangles[t][c]]);
    }
  }
  glEnd();

  glDisable(GL_TEXTURE_2D);
  glPopMatrix();
}

void door()
{
  static const GLfloat uv[4][2] = {
      {0.0f, 0.0f}, // bottom‐left
      {1.0f, 0.0f}, // bottom‐right
      {1.0f, 1.0f}, // top‐right
      {0.0f, 1.0f}  // top‐left
  };

  glPushMatrix();
  glTranslatef(0.0f, -0.99f, 1.1f);
  glScalef(0.3f, 0.8f, 0.1f);

  // frame geometry
  GLfloat frameVertices[8][3] = {
      {-1.0f, 0.0f, 1.0f}, {1.0f, 0.0f, 1.0f}, {1.0f, 1.0f, 1.0f}, {-1.0f, 1.0f, 1.0f}, {-1.0f, 1.0f, -1.0f}, {-1.0f, 0.0f, -1.0f}, {1.0f, 0.0f, -1.0f}, {1.0f, 1.0f, -1.0f}};
  GLint frameSquares[6][4] = {
      {2, 3, 0, 1}, {3, 4, 5, 0}, {7, 4, 5, 6}, {2, 7, 6, 1}, {1, 6, 5, 0}, {2, 7, 4, 3}};

  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, woodTexture);
  glColor3f(0.5f, 0.3f, 0.3f);
  glBegin(GL_QUADS);
  for (int face = 0; face < 6; face++)
  {
    for (int corner = 0; corner < 4; corner++)
    {
      glTexCoord2fv(uv[corner]);
      glVertex3fv(frameVertices[frameSquares[face][corner]]);
    }
  }
  glEnd();
  glDisable(GL_TEXTURE_2D);
  glPopMatrix();

  // Door panel
  glPushMatrix();
  glTranslatef(0.0f, -0.99f, 1.08f);
  glScalef(0.2f, 0.7f, 0.05f);

  // panel geometry
  GLfloat doorVertices[8][3] = {
      {-1.0f, 0.0f, 1.0f}, {1.0f, 0.0f, 1.0f}, {1.0f, 1.0f, 1.0f}, {-1.0f, 1.0f, 1.0f}, {-1.0f, 1.0f, -1.0f}, {-1.0f, 0.0f, -1.0f}, {1.0f, 0.0f, -1.0f}, {1.0f, 1.0f, -1.0f}};
  GLint doorSquares[6][4] = {
      {2, 3, 0, 1}, {3, 4, 5, 0}, {7, 4, 5, 6}, {2, 7, 6, 1}, {1, 6, 5, 0}, {2, 7, 4, 3}};

  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, woodTexture);
  glBegin(GL_QUADS);
  for (int face = 0; face < 6; face++)
  {
    for (int corner = 0; corner < 4; corner++)
    {
      glTexCoord2fv(uv[corner]);
      glVertex3fv(doorVertices[doorSquares[face][corner]]);
    }
  }
  glEnd();
  glDisable(GL_TEXTURE_2D);
  glPopMatrix();
}

void drawFence()
{
    const float radius = 8.0f;
    const int posts = 20;

    // UVs for a single quad (rail)
    static const GLfloat uv[4][2] = {
        {0.0f, 0.0f}, // bottom-left
        {1.0f, 0.0f}, // bottom-right
        {1.0f, 1.0f}, // top-right
        {0.0f, 1.0f}  // top-left
    };

    // bind once up front
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, woodTexture);

    for (int i = 0; i < posts; i++)
    {
        float angle = 2.0f * M_PI * i / posts;
        float x = radius * cosf(angle);
        float z = radius * sinf(angle) - 5.0f;

        // — Textured post —
        glPushMatrix();
        glTranslatef(x, 0.0f, z);
        glScalef(0.2f, 2.5f, 0.2f);
        drawTexturedCube(woodTexture);
        glPopMatrix();

        // — Textured rail to previous post —
        if (i > 0)
        {
            float prevAngle = 2.0f * M_PI * (i - 1) / posts;
            float px = radius * cosf(prevAngle);
            float pz = radius * sinf(prevAngle) - 5.0f;

            glBegin(GL_QUADS);
            // bottom-left
            glNormal3f(0, 1, 0);
            glTexCoord2fv(uv[0]);
            glVertex3f(px, 1.0f, pz);
            // bottom-right
            glTexCoord2fv(uv[1]);
            glVertex3f(x, 1.0f, z);
            // top-right
            glTexCoord2fv(uv[2]);
            glVertex3f(x, 1.2f, z);
            // top-left
            glTexCoord2fv(uv[3]);
            glVertex3f(px, 1.2f, pz);
            glEnd();
        }
    }

    glDisable(GL_TEXTURE_2D);
}


void window(GLfloat x, GLfloat y, GLfloat z)
{
  // window
  glPushMatrix();
  glTranslatef(x, y, z + 0.1);
  glScalef(0.2, 0.5, 0.05);
  GLfloat windowVertices[16][3] = {
      {-1.0, 0.0, 1.0},
      {1.0, 0.0, 1.0},
      {1.0, 1.0, 1.0},
      {-1.0, 1.0, 1.0},
      {-1.0, 1.0, -1.0},
      {1.0, 1.0, -1.0},
      {1.0, 0.0, -1.0},
      {-1.0, 0.0, -1.0},
      {-0.8, 0.1, 1.0},
      {0.8, 0.1, 1.0},
      {0.8, 0.9, 1.0},
      {-0.8, 0.9, 1.0},
      {-0.8, 0.9, -1.0},
      {0.8, 0.9, -1.0},
      {0.8, 0.1, -1.0},
      {-0.8, 0.1, -1.0},
  };
  GLint sideWindowSquares[8][4] = {{0, 1, 6, 7}, {3, 2, 5, 4}, {0, 7, 4, 3}, {1, 6, 5, 2}, {8, 9, 14, 15}, {11, 10, 13, 12}, {8, 15, 12, 11}, {9, 14, 13, 10}};
  GLint frontWindowSquares[8][4] = {{0, 1, 9, 8}, {0, 8, 11, 3}, {3, 11, 10, 2}, {1, 13, 10, 9}, {7, 6, 14, 15}, {7, 15, 12, 4}, {4, 12, 13, 5}, {6, 5, 13, 14}};

  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, woodTexture);

  static const GLfloat uv[4][2] = {
      {0.0f, 0.0f}, // bottom-left
      {1.0f, 0.0f}, // bottom-right
      {1.0f, 1.0f}, // top-right
      {0.0f, 1.0f}  // top-left
  };

  glBegin(GL_QUADS);
  // frames side
  for (int face = 0; face < 8; face++)
  {
    for (int corner = 0; corner < 4; corner++)
    {
      glTexCoord2fv(uv[corner]);
      glVertex3fv(windowVertices[sideWindowSquares[face][corner]]);
    }
  }
  // frames front
  for (int face = 0; face < 8; face++)
  {
    for (int corner = 0; corner < 4; corner++)
    {
      glTexCoord2fv(uv[corner]);
      glVertex3fv(windowVertices[frontWindowSquares[face][corner]]);
    }
  }
  glEnd();

  glDisable(GL_TEXTURE_2D);

  // glass
  glPushMatrix();
  glTranslatef(0.0, 0.0, 0.0);
  glScalef(0.8, 0.9, 1.0);
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, glassTexture);
  glBegin(GL_QUADS);
  // bottom-left
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(-1.0f, 0.0f, 1.0f);
  // bottom-right
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(1.0f, 0.0f, 1.0f);
  // top-right
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(1.0f, 1.0f, 1.0f);
  // top-left
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(-1.0f, 1.0f, 1.0f);
  glEnd();

  glPopMatrix();
  glDisable(GL_TEXTURE_2D);
  // pop for window
  glPopMatrix();
}

void drawChimney(GLfloat x, GLfloat y, GLfloat z, GLfloat width, GLfloat height,
                 GLfloat depth)
{
  glPushMatrix();
  glTranslatef(x, y, z);
  glScalef(width, height, depth);
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, brickChimneyTexture);
  drawTexturedCube(brickChimneyTexture);
  glDisable(GL_TEXTURE_2D);
  glPopMatrix();
}

void drawTrunk()
{
  GLUquadric *quadric = gluNewQuadric();
  gluQuadricNormals(quadric, GLU_SMOOTH);
  gluQuadricTexture(quadric, GL_TRUE);

  glPushMatrix();
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, trunkTexture);

  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

  glTranslatef(0.0f, -0.5f, 0.0f);
  gluCylinder(quadric, 0.1f, 0.1f, 1.0f, 32, 32);

  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
  glDisable(GL_TEXTURE_2D);
  glPopMatrix();

  gluDeleteQuadric(quadric);
}

void drawCrown()
{
  GLUquadric *quad = gluNewQuadric();
  gluQuadricNormals(quad, GLU_SMOOTH);
  gluQuadricTexture(quad, GL_TRUE);

  glPushMatrix();
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, leavesTexture);

  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

  glTranslatef(0.0f, 0.5f, 0.0f);
  gluCylinder(quad, 0.4f, 0.0f, 1.0f, 16, 16);

  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
  glDisable(GL_TEXTURE_2D);
  glPopMatrix();

  gluDeleteQuadric(quad);
}

void Tree(GLfloat x, GLfloat y, GLfloat z)
{
  glPushMatrix();
  glTranslatef(x, y, z);
  glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
  drawTrunk();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(x, y, z);
  glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
  drawCrown();
  glPopMatrix();
}