#pragma once

#define CAM_WIDTH_FT 320
#define CAM_HEIGHT_FT 240

#include "ofMain.h";
#include "ofxState.h"
#include "ofxOpenCv.h"
#include "ofxNMPTFaceTracker.h"

class faceTrackerExample : public ofxState {
	
public:
	
	faceTrackerExample();
	~faceTrackerExample();
	
	void stop();
	void start();
	void update();
	void draw();
	
	string getStateName();

private:
	
	ofxNMPTFaceTracker* faceTracker;
	ofxCvGrayscaleImage grayImage;
	ofxCvColorImage		currentFrame;
	ofxCvGrayscaleImage	resultFrame;
	ofVideoGrabber		grabber;
	
};