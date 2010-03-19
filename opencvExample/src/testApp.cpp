#include "testApp.h"


int f = 0;

//--------------------------------------------------------------
void testApp::setup()
{
	ofSetVerticalSync(true);
	
	#ifdef _USE_LIVE_VIDEO
        vidGrabber.setVerbose(true);
		//vidGrabber.initGrabber(1280,1024);
		vidGrabber.initGrabber(640,480);
		//vidGrabber.initGrabber(320,240);
	#else
        vidPlayer.loadMovie("fingers.mov");
        vidPlayer.play();
	#endif

	colorImg.allocate(640,480);
	grayImage.allocate(640,480);
	
    //colorImg.allocate(320,240);
	//grayImage.allocate(320,240);
	//grayBg.allocate(320,240);
	//grayDiff.allocate(320,240);
	//floatImg.allocate(320,240);
	
	//haarFinder.setup("haarcascade_frontalface_default.xml");
	haarFinder.setup("haarcascade_frontalface_alt_tree.xml");
	//haarFinder.setup("haarcascade_frontalface_alt2.xml");
	
	frank_overlay.loadImage("frank.png");
	frank_overlay_orig.loadImage("frank.png");
	frank_overlay.setImageType(OF_IMAGE_COLOR_ALPHA);
	frank_overlay_orig.setImageType(OF_IMAGE_COLOR_ALPHA);
	mode = 0;
	//frank_overlay.setUseTexture(true);
	frank_overlay_orig.setUseTexture(true);
}

//--------------------------------------------------------------
void testApp::update()
{
	ofBackground(100,100,100);

    bool bNewFrame = false;

	#ifdef _USE_LIVE_VIDEO
       vidGrabber.grabFrame();
	   bNewFrame = vidGrabber.isFrameNew();
    #else
        vidPlayer.idleMovie();
        bNewFrame = vidPlayer.isFrameNew();
	#endif

	if (bNewFrame)
	{
		#ifdef _USE_LIVE_VIDEO
            //colorImg.setFromPixels(vidGrabber.getPixels(), 320, 240);
			colorImg.setFromPixels(vidGrabber.getPixels(), 640, 480);
	    #else
            colorImg.setFromPixels(vidPlayer.getPixels(), 320, 240);
        #endif
		
		colorImg.mirror(false, true);
		
        grayImage = colorImg;
		f++;
	}
	if(ofGetFrameNum() % 5 == 0)
	{
		haarFinder.findHaarObjects(grayImage);
	}

}

//--------------------------------------------------------------
void testApp::draw()
{

	ofSetColor(0xffffff);
	ofDrawBitmapString("colorimg ", 20, 19);
	colorImg.draw(20,20);
	
	if(mode == 0)
	{
		for (int i = 0; i < haarFinder.blobs.size(); i++)
		{
			ofRectangle cur = haarFinder.blobs[i].boundingRect;
			ofEnableAlphaBlending();
			ofSetColor(255, 255, 255);
			//frank_overlay.draw(cur.x-frank_overlay.getWidth()/2.5, cur.y-frank_overlay.getHeight(), frank_overlay.getWidth()*(frank_overlay.getWidth()/cur.width), 
			//				   frank_overlay.getHeight()*(frank_overlay.getHeight()/cur.height));
			int ch = cur.height;
			int fow = frank_overlay.getWidth();
			frank_overlay.resize(fow*(ch/frank_overlay.getHeight()), ch);
			frank_overlay.draw(cur.x-frank_overlay.getWidth()/4, cur.y-frank_overlay.getHeight(), frank_overlay.getWidth()*2, frank_overlay.getHeight()*2);
			ofDisableAlphaBlending();
		}
		if(ofGetFrameNum() % 11 == 0)
		{
			frank_overlay = frank_overlay_orig;
		}
	}

	// finally, a report:

	ofSetColor(0xffffff);
	char reportStr[1024];
	sprintf(reportStr, "mode %i, num blobs found %i, fps: %f", mode, haarFinder.blobs.size(), ofGetFrameRate());
	ofDrawBitmapString(reportStr, 20, 600);

}


//--------------------------------------------------------------
void testApp::keyPressed  (int key)
{
	switch (key)
	{
		case 'f':
			mode = 0;
			break;
	}
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

