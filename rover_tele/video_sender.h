#ifndef VIDEO_SENDER_H
#define VIDEO_SENDER_H

#include <rtr.h>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <GL/glut.h>

class video_sender : m_module
{
	public:
		using m_module::m_module;
		void configure(void);
		void initialize(void);
		void setup(void);
		void start(void);
		
		m_job<void, void> GLInit{this, "GLInit", std::bind(&video_sender::gl_init, this)};
		m_worker<void, void> UpdateCam{this, "UpdateCam", std::bind(&video_sender::cam_refresh, this)};
		
		static GLvoid displayLoop();
		static GLvoid idle();
	private:
		void gl_init(void);
		void cam_refresh(void);
		static int width; static int height; static int size;
		static m_blob camblob;
};


#endif