/*
 * Video sets up a server for other Hydra's to stream video
 * from. It also shows the camera window that it is streaming
 * 
 * Jason Ernst, Redtree Robotics 2015
 */
#include "video_sender.h"
#include <rt_input_user.h>
#include <iostream>

//#define M_VIDEO_DISPLAY

using namespace std;

camera cam{"cam"};
video_sender vc{"vc"};

int video_sender::width;
int video_sender::height;
int video_sender::size;
m_blob video_sender::camblob;

void video_sender::configure(void) 
{
	camblob.name = "camera";
	m_tagdb::insert_tag(&camblob);
}
void video_sender::initialize(void) {}
void video_sender::setup(void) {}
void video_sender::start(void)
{
	Started = true;
	#ifdef M_VIDEO_DISPLAY
		GLInit();
	#endif
	UpdateCam.run_when(Started);
}

void video_sender::gl_init(void)
{
	cam.wait_for_start();
	
	width = cam.getWidth();
	height = cam.getHeight();
	size = cam.getSize();
	
	int argc = 1;
	char * argv[1] = {(char*)"HydraScreen"};
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE);
	glutInitWindowSize(width, height);
	glutCreateWindow("camera test");
		
	glutIdleFunc(idle);
	glutDisplayFunc(displayLoop);
		
	glutMainLoop();
}

GLvoid video_sender::idle(void)
{
	int type = cam.getType();
	int rows = cam.getRows();
	int cols = cam.getCols();
	
	//cout << "TYPE: " << type << " ROWS: " << rows << " COLS: " << cols << endl;
	
	width = cam.getWidth();
	height = cam.getHeight();
	size = cam.getSize();
	//cout << "W: " << width << " H: " << height << " S: " << size << endl;
	
	camblob.lock();
	char * data = (char*)camblob.get();
	camblob.unlock();
	Mat image2 = Mat(rows, cols, type, data);
	if(!image2.empty())
	{
		glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, image2.cols, image2.rows, 0, GL_BGR, GL_UNSIGNED_BYTE, image2.ptr());
		glutPostRedisplay();
	}
}

void video_sender::cam_refresh(void)
{
	m_blob temp = cam.getBlob();
	camblob.lock();
	camblob = temp;
	camblob.unlock();
}

GLvoid video_sender::displayLoop(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_TEXTURE_2D);
		
	// These are necessary if using glTexImage2D instead of gluBuild2DMipmaps
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

	// Set Projection Matrix
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, width, height, 0);

	// Switch to Model View Matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Draw a textured quad
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex2f(0.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex2f(width, 0.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex2f(width, height);
	glTexCoord2f(0.0f, 1.0f); glVertex2f(0.0f, height);
	glEnd();

	glFlush();
	glutSwapBuffers();
}
