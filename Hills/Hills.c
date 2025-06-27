#include "Hills.h"

// Animation and camera
float animationTime = 0.0f;
int animationActive = 1;
float cameraAngle = 0.0f;
int selectedPoint = -1;
float cameraDistance = 15.0f;
float cameraHeight = 8.0f;

// Control points for the Catmull-Rom spline
GLfloat controlPoints[6][3] = {
    {-10.0f, 1.5f, 0.0f},
    {-6.0f, 0.5f, 0.0f},
    {-2.0f, 3.0f, 0.0f},
    {2.0f, 1.0f, 0.0f},
    {6.0f, 4.0f, 0.0f},
    {10.0f, 2.0f, 0.0f}};

// Calculate a point on the Catmull-Rom spline (t in [0,1])
void calculateSplinePoint(float t, float *result)
{
  int segment = (int)(t * (6 - 3));
  if (segment > 2)
    segment = 2;
  float localT = t * (6 - 3) - segment;
  int p0 = segment, p1 = segment + 1, p2 = segment + 2, p3 = segment + 3;
  float t2 = localT * localT, t3 = t2 * localT;
  for (int i = 0; i < 3; i++)
  {
    result[i] = 0.5f * (2.0f * controlPoints[p1][i] +
                        (-controlPoints[p0][i] + controlPoints[p2][i]) * localT +
                        (2.0f * controlPoints[p0][i] - 5.0f * controlPoints[p1][i] + 4.0f * controlPoints[p2][i] - controlPoints[p3][i]) * t2 +
                        (-controlPoints[p0][i] + 3.0f * controlPoints[p1][i] - 3.0f * controlPoints[p2][i] + controlPoints[p3][i]) * t3);
  }
}

// Compute a triangle normal
void calculateNormal(float *v1, float *v2, float *v3, float *n)
{
  float u[3] = {v2[0] - v1[0], v2[1] - v1[1], v2[2] - v1[2]};
  float v[3] = {v3[0] - v1[0], v3[1] - v1[1], v3[2] - v1[2]};
  n[0] = u[1] * v[2] - u[2] * v[1];
  n[1] = u[2] * v[0] - u[0] * v[2];
  n[2] = u[0] * v[1] - u[1] * v[0];
  float len = sqrtf(n[0] * n[0] + n[1] * n[1] + n[2] * n[2]);
  if (len > 0)
  {
    n[0] /= len;
    n[1] /= len;
    n[2] /= len;
  }
}

// Generate and draw the hill mesh textured with earthTexture
void generateHillMesh(int segments)
{
  static float vertices[MESH_SIZE + 1][MESH_SIZE + 1][3];
  static float normals[MESH_SIZE + 1][MESH_SIZE + 1][3];
  const float hillRadius = 2.0f;

  // Vertex positions
  for (int i = 0; i <= segments; i++)
  {
    for (int j = 0; j <= segments; j++)
    {
      float gridX = (i - segments / 2) / (segments / 4.0f);
      float gridZ = (j - segments / 2) / (segments / 4.0f);
      float dist = sqrtf(gridX * gridX + gridZ * gridZ);
      float hf = (dist <= hillRadius)
                     ? (hillRadius - dist) / hillRadius
                     : 0.0f;
      // sample spline profile
      float angle = atan2f(gridZ, gridX);
      if (angle < 0)
        angle += 2 * M_PI;
      int idx = (int)((angle / (2 * M_PI)) * segments + 0.5f);
      if (idx < 0)
        idx = 0;
      if (idx > segments)
        idx = segments;
      float t = idx / (float)segments;
      float sp[3];
      calculateSplinePoint(t, sp);
      // base height + noise + animation
      float noise = 0.1f * sinf(gridX * 5) * cosf(gridZ * 5);
      float anim = animationActive
                       ? 0.1f * sinf(animationTime + gridX + gridZ)
                       : 0.0f;
      float y = (sp[1] + noise + anim) * hf;
      vertices[i][j][0] = gridX * 5.0f;
      vertices[i][j][1] = y;
      vertices[i][j][2] = gridZ * 5.0f;
    }
  }
  //Normals
  for (int i = 0; i <= segments; i++)
  {
    for (int j = 0; j <= segments; j++)
    {
      float n1[3] = {0, 1, 0}, n2[3] = {0, 1, 0};
      if (i > 0 && j > 0)
        calculateNormal(vertices[i][j], vertices[i - 1][j], vertices[i][j - 1], n1);
      if (i < segments && j < segments)
        calculateNormal(vertices[i][j], vertices[i + 1][j], vertices[i][j + 1], n2);
      normals[i][j][0] = 0.5f * (n1[0] + n2[0]);
      normals[i][j][1] = 0.5f * (n1[1] + n2[1]);
      normals[i][j][2] = 0.5f * (n1[2] + n2[2]);
    }
  }
  //Draw textured mesh
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, earthTexture);
  for (int i = 0; i < segments; i++)
  {
    glBegin(GL_TRIANGLE_STRIP);
    for (int j = 0; j <= segments; j++)
    {
      float u = j / (float)segments;
      float v0 = i / (float)segments;
      float v1 = (i + 1) / (float)segments;
      // first vertex
      glNormal3fv(normals[i][j]);
      glTexCoord2f(u, v0);
      glVertex3fv(vertices[i][j]);
      // second vertex
      glNormal3fv(normals[i + 1][j]);
      glTexCoord2f(u, v1);
      glVertex3fv(vertices[i + 1][j]);
    }
    glEnd();
  }
  glDisable(GL_TEXTURE_2D);
}