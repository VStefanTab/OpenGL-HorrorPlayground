#include "Hills\Hills.h"
#include "House\House.h"
#include "Robot\Robot.h"

#define WIDTH 800
#define HEIGHT 800

// TODO: make the hills smaller, move them in the background, get the robot movement
// from the classroom, get better lightning. Prepare the raport

// Lighting parameters
GLfloat light_position[] = {5.0, 10.0, 5.0, 1.0};
GLfloat light_ambient[] = {0.2, 0.2, 0.2, 1.0};
GLfloat light_diffuse[] = {0.8, 0.8, 0.8, 1.0};
GLfloat light_specular[] = {1.0, 1.0, 1.0, 1.0};

// for camera position
float camX, camY = 2.0f, camZ = 8.0f;
float lookX, lookY = 2.0f, lookZ;

// for camera rotation angles...ensuring that the movement is relativ to the
// direction the camera is facing
float angleX, angleY;

// Movement speed
float speed = 0.3f;

// for mouse
bool isDragging;
int prevMouseX, prevMouseY;

// Robot variables
Robot *robot = NULL;

#define ROUTE_LEN 2
static const float route[ROUTE_LEN][2] = {
    {0.0f, 4.0f}, // (x,z) in front of the door
    {0.0f, 8.0f}  // front edge of the foundation
};
static int currentWaypoint = 0;
float robotX = 0.0f, robotZ = 2.0f; // start at the door
float robotSpeed = 0.03f;
float robotAngle = 0.0f;

void drawHouse()
{
    Foundation();
    glPushMatrix();
    glTranslatef(0.0f, -0.1f, -1.0f);
    HouseBase();
    WroofWroof();
    drawChimney(0.5f, 1.6f, -0.5f, 0.3f, 0.7f, 0.3f);
    door();
    window(-0.6, 0.0, 1.051);
    window(0.6, 0.0, 1.051);
    glPopMatrix();
    glPushMatrix();
    glRotatef(-100.0f, 0.0f, 1.0f, 0.0f);
    glScalef(0.3f, 0.2f, .3f);
    glTranslatef(-2.0f, -4.0f, 5.2f);
    drawFence();
    glPopMatrix();
    Tree(0.0f, -0.05f, -3.0f);
    Tree(-5.0f, -0.05f, 0.0f);
    Tree(8.0f, -0.05f, 4.0f);
    Tree(2.0f, -0.05f, -3.0f);
    Tree(-6.0f, -0.05f, 2.0f);
    Tree(6.0f, -0.05f, -6.0f);
    Tree(3.0f, -0.05f, -5.0f);
}

void update(int value)
{
    float moveSpeed = robotSpeed; // now 0.05f
    float angleChange = 1.0f;

    float tx = route[currentWaypoint][0];
    float tz = route[currentWaypoint][1];
    float dx = tx - robotX;
    float dz = tz - robotZ;

    const float arrivalRadius = 0.5f;
    if (dx * dx + dz * dz < arrivalRadius * arrivalRadius)
    {
        currentWaypoint = (currentWaypoint + 1) % ROUTE_LEN;
        tx = route[currentWaypoint][0];
        tz = route[currentWaypoint][1];
        dx = tx - robotX;
        dz = tz - robotZ;
    }

    float desiredAngle = atan2f(dx, dz) * (180.0f / M_PI);

    float delta = desiredAngle - robotAngle;
    while (delta > 180.0f)
        delta -= 360.0f;
    while (delta < -180.0f)
        delta += 360.0f;
    if (fabsf(delta) <= angleChange)
        robotAngle = desiredAngle;
    else if (delta > 0)
        robotAngle += angleChange;
    else
        robotAngle -= angleChange;
    if (robotAngle < 0.0f)
        robotAngle += 360.0f;
    if (robotAngle >= 360.0f)
        robotAngle -= 360.0f;

    robotX += moveSpeed * sinf(robotAngle * M_PI / 180.0f);
    robotZ += moveSpeed * cosf(robotAngle * M_PI / 180.0f);

    updateNode(robot->root);
    glutPostRedisplay();
    glutTimerFunc(30, update, 0);
}

// Robot
void drawRobot()
{
    if (!robot)
        return;

    glPushMatrix();
    glScalef(0.5f, 0.7f, 0.5f);
    glTranslatef(robotX, -1.5f, robotZ);
    glRotatef(robotAngle, 0.0f, 1.0f, 0.0f);

    updateNode(robot->root);
    glPopMatrix();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (float)WIDTH / HEIGHT, 0.1, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(camX, camY, camZ, lookX, lookY, lookZ, 0.0, 1.0, 0.0);

    // Draw all components
    drawHouse();

    glPushMatrix();
    glTranslatef(robotX, 0.0f, robotZ);
    glScalef(0.2f, 0.25f, 0.2f);
    drawRobot();
    glPopMatrix();

    // define hill centers (x,z) around the foundation
    float hillCenters[4][2] = {
        {-10.0f, -20.0f},
        {-10.f, -10.0f},
        {10.0f, -20.0f},
        {5.0f, -20.0f},
    };

    // draw each hill
    for (int i = 0; i < 4; ++i)
    {
        glPushMatrix();
        // move to hill center, leave y=0 (ground level)
        glTranslatef(hillCenters[i][0], -1.1f, hillCenters[i][1]);
        generateHillMesh(MESH_SIZE);
        glPopMatrix();
    }

    glutSwapBuffers();
}

// Function to update the camera direction based on angles
void updateLookAt()
{
    float radY = angleY * (M_PI / 180.0f);
    float radX = angleX * (M_PI / 180.0f);

    lookX = camX + cos(radY);
    lookZ = camZ + sin(radY);
    lookY = camY + tan(radX);
}

void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (GLfloat)w / (GLfloat)h, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
}

void motion(int x, int y)
{
    if (isDragging)
    {
        angleY += (x - prevMouseX) * 0.5f;
        angleX -= (y - prevMouseY) * 0.5f;
        prevMouseX = x;
        prevMouseY = y;
        updateLookAt();
        glutPostRedisplay();
    }
}

void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON)
    {
        if (state == GLUT_DOWN)
        {
            isDragging = true;
            prevMouseX = x;
            prevMouseY = y;
        }
        else if (state == GLUT_UP)
        {
            isDragging = false;
        }
    }
}

void keyboard(unsigned char key, int x, int y)
{
    float radY = angleY * (M_PI / 180.0f);

    switch (key)
    {
    case 'w':
        camX += cos(radY) * speed;
        camZ += sin(radY) * speed;
        break;
    case 's':
        camX -= cos(radY) * speed;
        camZ -= sin(radY) * speed;
        break;
    case 'a':
        camX += sin(radY) * speed;
        camZ -= cos(radY) * speed;
        break;
    case 'd':
        camX -= sin(radY) * speed;
        camZ += cos(radY) * speed;
        break;
    case 'q':
        camY--;
        break;
    case 'e':
        camY++;
        break;
    }
    updateLookAt();
    glutPostRedisplay();
}

void InitLighting()
{
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);

    // Main light (sun)
    GLfloat sunColor[] = {1.0f, 0.95f, 0.8f, 1.0f};       // Slightly warm sunlight
    GLfloat sunPosition[] = {50.0f, 100.0f, 50.0f, 1.0f}; // Position the sun high and to the side

    glLightfv(GL_LIGHT0, GL_DIFFUSE, sunColor);
    glLightfv(GL_LIGHT0, GL_POSITION, sunPosition);

    // Add some specular highlights
    GLfloat sunSpecular[] = {0.5f, 0.5f, 0.5f, 1.0f};
    glLightfv(GL_LIGHT0, GL_SPECULAR, sunSpecular);

    // Ambient light (sky)
    GLfloat ambientColor[] = {0.2f, 0.3f, 0.4f, 1.0f}; // Slightly blue ambient
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientColor);

    // Secondary light (fill light)
    GLfloat fillColor[] = {0.4f, 0.4f, 0.5f, 1.0f}; // Slightly cool fill light
    GLfloat fillPosition[] = {-30.0f, 30.0f, -70.0f, 1.0f};

    glLightfv(GL_LIGHT1, GL_DIFFUSE, fillColor);
    glLightfv(GL_LIGHT1, GL_POSITION, fillPosition);

    // Enable fog for depth
    glEnable(GL_FOG);
    GLfloat fogColor[] = {0.5f, 0.5f, 0.5f, 1.0f};
    glFogi(GL_FOG_MODE, GL_LINEAR);
    glFogfv(GL_FOG_COLOR, fogColor);
    glFogf(GL_FOG_START, 20.0f);
    glFogf(GL_FOG_END, 60.0f);
}

void init()
{
    initTextures();
    robot = malloc(sizeof(Robot));
    if (!robot)
    {
        fprintf(stderr, "Failed to allocate Robot\n");
        exit(EXIT_FAILURE);
    }

    buildRobot(robot);
    robotAnimationTimer(0);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("My House!");

    init();

    glClearColor(0.53f, 0.81f, 0.98f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    InitLighting();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);

    glutTimerFunc(30, update, 0);
    glutMainLoop();
}