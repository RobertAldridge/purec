/*************************************************************************\

  Copyright 2007 The University of North Carolina at Chapel Hill.
  All Rights Reserved.

  Permission to use, copy, modify and distribute this software and its
  documentation for educational, research and non-profit purposes, without
   fee, and without a written agreement is hereby granted, provided that the
  above copyright notice and the following three paragraphs appear in all
  copies.

  IN NO EVENT SHALL THE UNIVERSITY OF NORTH CAROLINA AT CHAPEL HILL BE
  LIABLE TO ANY PARTY FOR DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR
  CONSEQUENTIAL DAMAGES, INCLUDING LOST PROFITS, ARISING OUT OF THE
  USE OF THIS SOFTWARE AND ITS DOCUMENTATION, EVEN IF THE UNIVERSITY
  OF NORTH CAROLINA HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH
  DAMAGES.

  THE UNIVERSITY OF NORTH CAROLINA SPECIFICALLY DISCLAIM ANY
  WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.  THE SOFTWARE
  PROVIDED HEREUNDER IS ON AN "AS IS" BASIS, AND THE UNIVERSITY OF
  NORTH CAROLINA HAS NO OBLIGATIONS TO PROVIDE MAINTENANCE, SUPPORT,
  UPDATES, ENHANCEMENTS, OR MODIFICATIONS.

  The authors may be contacted via:

  US Mail:             GAMMA Research Group at UNC
                       Department of Computer Science
                       Sitterson Hall, CB #3175
                       University of N. Carolina
                       Chapel Hill, NC 27599-3175

  Phone:               (919)962-1749

  EMail:              {geom, tangm}@cs.unc.edu


\**************************************************************************/



// need: NVIDIA SDK 9.5
// Author: Tang, Min tangm@cs.unc.edu

#if defined(WIN32)
#  include <windows.h>
#endif

#include "logger.h"
Logger *logger;

#include <glh/glh_glut.h>

#include <shared/timer.h>
timer fps(10);

bool b[256];
int win_w = 512, win_h = 512;

using namespace glh;
glut_simple_mouse_interactor object;

#include "timing.h"

// for sprintf
#pragma warning(disable: 4996)

extern void initModel();
extern void quitModel();
extern void drawModel(int *boxes, int *pairs, int level);
extern void dynamicModel(int t, bool refit);
extern void printCollideInfo();

static int level = 0;

// check for OpenGL errors
void checkGLError()
{
    GLenum error;
    while ((error = glGetError()) != GL_NO_ERROR) {
		char msg[512];
		sprintf(msg, "error - %s\n", (char *) gluErrorString(error));
		logger->update(msg);
    }
}

void initSetting()
{
    b[' '] = false;
    b['w'] = true;
	b['r'] = true;
}

void initOpengl()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);

	// initialize OpenGL lighting
	GLfloat matAmb[4] =    {1.0, 1.0, 1.0, 1.0};
	GLfloat matDiff[4] =   {1.0, 0.1, 0.2, 1.0};
	GLfloat matSpec[4] =   {1.0, 1.0, 1.0, 1.0};

	GLfloat lightpos1[] = {1.0, -1.0, -1.0, 0};
	GLfloat lightpos2[] = {-1.0, 1.0, 1.0, 0};

	GLfloat lightAmb[4] =  {0.0, 0.0, 0.0, 1.0};
	GLfloat lightDiff[4] = {1.0, 1.0, 1.0, 1.0};
	GLfloat lightSpec[4] = {1.0, 1.0, 1.0, 1.0};

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, matAmb);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, matDiff);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matSpec);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 60.0);

	glLightfv(GL_LIGHT0, GL_POSITION, lightpos1);
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiff);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpec);

	glLightfv(GL_LIGHT1, GL_POSITION, lightpos2);
	glLightfv(GL_LIGHT1, GL_AMBIENT, lightAmb);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightDiff);
	glLightfv(GL_LIGHT1, GL_SPECULAR, lightSpec);

	glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL_EXT, GL_SEPARATE_SPECULAR_COLOR_EXT);
	GLfloat black[] =  {0.0, 0.0, 0.0, 1.0};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, black);

	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
}

void updateFPS(int boxes, int pairs)
{
    char buf[512];
	static float ffps;

    fps.frame();
    if (fps.timing_updated()) {
		ffps = fps.get_fps();
	}

	sprintf(buf, "DeformCD (FPS: %.1f, boxes = %d, pairs = %d, %s)",
		fps.get_fps(), boxes, pairs, b['r']?"refit":"rebuild");

	glutSetWindowTitle(buf);
}

void begin_window_coords()
{
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0.0, win_w, 0.0, win_h, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void end_window_coords()
{
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}


void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glShadeModel(GL_SMOOTH);

	{
    // gradient background
    begin_window_coords();
    glBegin(GL_QUADS);
        glColor3f(0.2, 0.4, 0.8);
        glVertex2f(0.0, 0.0);
        glVertex2f(win_w, 0.0);
        glColor3f(0.05, 0.1, 0.2);
        glVertex2f(win_w, win_h);
        glVertex2f(0, win_h);
    glEnd();
    end_window_coords();
	}

    glMatrixMode(GL_MODELVIEW);
    object.apply_transform();

    // draw scene
	if (!b['w'])
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // draw scene
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);

	//glutSolidTeapot(1.0);
	int boxes = 0, pairs = 0;
	drawModel(&boxes, &pairs, level);

    glutSwapBuffers();
	updateFPS(boxes, pairs);
	checkGLError();
}

void idle()
{
	static int s_count = 0;

    if (b[' '])
        object.trackball.increment_rotation();

	if (b['d']) {
		dynamicModel(s_count++, b['r']);
	}

    glutPostRedisplay();
}

void quit()
{
	quitModel();

    exit(0);
}

void key(unsigned char k, int x, int y)
{
	b[k] = ! b[k];

    switch(k) {
    case 27:
    case 'q':
		quit();
        break;
		
	case '=':
		level++;
		break;

	case '-':
		level--;
		break;

	case 'l':
		printCollideInfo();
		break;
	}

    object.keyboard(k, x, y);    
	glutPostRedisplay();
}

void resize(int w, int h)
{
    if (h == 0) h = 1;

    glViewport(0, 0, w, h);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLfloat)w/(GLfloat)h, 0.1, 500.0);
    //gluPerspective(60.0, (GLfloat)w/(GLfloat)h, 0.01, 10.0);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    object.reshape(w, h);

    win_w = w; win_h = h;
}

void mouse(int button, int state, int x, int y)
{
    object.mouse(button, state, x, y);
}

void motion(int x, int y)
{
    object.motion(x, y);
}

void main_menu(int i)
{
    key((unsigned char) i, 0, 0);
}

void initMenu()
{    
    glutCreateMenu(main_menu);
	glutAddMenuEntry("Toggle deforming       [d]", 'd');
	glutAddMenuEntry("====================", '=');
	glutAddMenuEntry("Toggle rebuild/refit   [r]", 'r');
	glutAddMenuEntry("Increasing boxes level [=]", '=');
	glutAddMenuEntry("Decreasing boxes level [-]", '-');
	glutAddMenuEntry("====================", '=');
    glutAddMenuEntry("Toggle wireframe       [w]", 'w');
    glutAddMenuEntry("Quit               [q/esc]", '\033');
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

bool initWin(int argc, char **argv)
{
	if (argc > 1) {
		int rx = 0, ry = 0;

		for (int i=1; i<argc; i++)
			if (!strcmp(argv[i], "rx") && (i+1) < argc)
				rx = atol(argv[i+1]);
			else if (!strcmp(argv[i], "ry") && (i+1) < argc)
				ry = atol(argv[i+1]);

		char mode[128];
		sprintf(mode, "%dx%d:32", rx, ry);
		glutGameModeString(mode);
		if (glutGameModeGet(GLUT_GAME_MODE_POSSIBLE))
			glutEnterGameMode(); 
		else {
			char msg[512];
			sprintf(msg, "unsupported resolution: %s", mode);
			logger->update(msg);
			logger->update("return to window mode (512x512)");
			return false;
		}

		return true;
	}

	return false;
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA | GLUT_STENCIL);

	logger = new Logger("logger.txt");
	if (!initWin(argc, argv)) {
		glutInitWindowSize(win_w, win_h);
		glutCreateWindow("Model Viewer");
	}

	initOpengl();
	initModel();

    object.configure_buttons(1);
    object.dolly.dolly[2] = -3;
    object.trackball.incr = rotationf(vec3f(1, 1, 0), 0.05);

	glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutIdleFunc(idle);
    glutKeyboardFunc(key);
    glutReshapeFunc(resize);

    initMenu();

	initSetting();

	glutMainLoop();

	return 0;
}
