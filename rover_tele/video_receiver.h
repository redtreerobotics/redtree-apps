#ifndef VIDEO_RECEIVER_H
#define VIDEO_RECEIVER_H

#include <rtr.h>

#include <GL/glut.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

class video_receiver : m_module
{
	public:
		using m_module::m_module;
		void configure(void);
		void initialize(void){};
		void setup(void);
		void start(void);
		void fetch(void);
		
		m_worker<void, void> Camera_Fetch{this, "Camera_Fetch", std::bind(&video_receiver::fetch, this)};
		
		static GLvoid displayLoop();
		static GLvoid idle();
		static m_blob camera;
	private:
		static int width; static int height;
		static int timeout;
};

#endif