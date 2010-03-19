#ifndef _TEST_APP
#define _TEST_APP


#include "ofMain.h"
#include "ofxVec3f.h"
#include "Boid.h"
#include "Boids.h"
#include "ofxSimpleGuiToo.h"
#include <map>

class testApp : public ofBaseApp{

	public:

		testApp();
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void resized(int w, int h);

		Boids* boids;
		char mode;
		ofxVec3f target; // target used to seek, flee, arrive

		ofxSimpleGuiToo gui;
		map<string,float> slider_vals;
};
#endif
