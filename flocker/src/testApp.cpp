#include "testApp.h"
#include "stdio.h"

//--------------------------------------------------------------
testApp::testApp()
{
	ofSetFrameRate(60);
	boids = new Boids(80);

	ofBackground(0,0,0);
	//ofBackground(230,230,230);

	gui.addSlider("boid.max_vel", slider_vals["boid.max_vel"],0.1f, 40.0f, 0.1f);
	gui.loadFromXML();
	slider_vals["boid.max_vel"] = 6.0;
	mode = 'a';
}

//--------------------------------------------------------------
void testApp::setup()
{
}

//--------------------------------------------------------------
void testApp::update()
{
	target.set(mouseX,mouseY,300);
	boids->setMaxVelocity(slider_vals["boid.max_vel"]);
	boids->flock();
	if (mode == 'a') 
	{
		boids->arrive(target);
	}
	else if (mode == 'f') 
	{
		boids->flee(target);
	}
	else if (mode == 'e') 
	{
		boids->explode();
		mode = 0;
	}
	boids->update();
	boids->bounce();
}


//--------------------------------------------------------------
void testApp::draw()
{
	gui.draw();
	boids->draw();
}

//--------------------------------------------------------------
void testApp::keyPressed  (int key)
{
	if (key == ' ') 
	{
		gui.toggleDraw();
	}
	else if (key == 'a') 
	{
		//target.set(ofGetWidth()/2, ofGetHeight()/2,0);
		mode = key;
	}
	else if (key == 'f') 
	{
		//target.set(ofGetWidth()/2, ofGetHeight()/2,0);
		mode = key;
	}
	else if (key == 'e') 
	{
		mode = key;
	}
	else if (key == 'c') 
	{
		mode = 0;
	}
}


//--------------------------------------------------------------
void testApp::keyReleased(int key)
{

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y )
{

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button)
{
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button)
{

}
//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button)
{

}

//--------------------------------------------------------------
void testApp::resized(int w, int h)
{

}