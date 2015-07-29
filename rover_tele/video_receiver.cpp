/*
 * Video receiver module for the Redtree Hydra
 */
#include <rt_ddb_user.h>
#include "video_receiver.h"
using namespace std;

int video_receiver::width;
int video_receiver::height;
int video_receiver::timeout;
m_blob video_receiver::camera;

video_receiver vr{"vr"};

void video_receiver::setup(void)
{
	timeout = 1;	
}

void video_receiver::configure(void)
{
	Camera_Fetch.run_every_when(100000, Started);
}

/*
 * This loop will run over and over as quickly as possible
 */
void video_receiver::fetch(void)
{
	unsigned int i;
	std::vector<m_tag *> tags = get_tag_broadcast("camera", timeout, 0);
	
	if(tags.size() == 0)
	{	
		timeout++;
		cout << "TIMEOUT: " << timeout << endl;
		return;
	}
	else
	{
		if(timeout > 1)
			timeout--;
		cout << "TIMEOUT: " << timeout << endl;
	}
	
	for(i = 0; i < tags.size(); i++)
	{
		m_tag * t = tags.at(i);
		m_blob *bt = dynamic_cast<m_blob*>(t);
		if(bt != NULL)
		{
			cout << "GOT BLOB" << endl;
			//char * data = (char*)bt->get();
			
			camera.set(*bt);
		}
	}
}

void video_receiver::start(void)
{
	Started = true;
	
	width = 640;
	height = 480;
	int argc = 1;
	char * argv[1] = {(char*)"HydraScreen"};
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(width, height);
	glutCreateWindow("Remote Camera");
	
	glutIdleFunc(idle);
	glutDisplayFunc(displayLoop);
	
	glutMainLoop();
}

GLvoid video_receiver::idle(void)
{	
	//todo: get all this information from the network packet
	int type = 16;
	int rows = 480;
	int cols = 640;
	
	Mat image;
	if(camera.size() == 0)
		return;
	
	char * data = (char*)camera.get();
	image = Mat(rows, cols, type, data);
		
	if(image.empty())
		cout << "Empty cam image" << endl;
	else
	{
		glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, image.cols, image.rows, 0, GL_BGR, GL_UNSIGNED_BYTE, image.ptr());
        glutPostRedisplay();
	}
}

GLvoid video_receiver::displayLoop(void)
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
