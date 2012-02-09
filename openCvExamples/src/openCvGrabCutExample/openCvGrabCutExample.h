#pragma once

#define CAM_WIDTH_GC 320
#define CAM_HEIGHT_GC 240

#include "ofMain.h";
#include "ofxState.h"
#include "ofxOpenCv.h"
#include "ofxOpenCvUtilsGrabCut.h"

class openCvGrabCutExample : public ofxState {
	
public:
	
	openCvGrabCutExample();
	~openCvGrabCutExample();
	void stop();
	void start();
	void update();
	void draw();
	void keyReleased(ofKeyEventArgs &e);
	string getStateName();
	
private:
	
	ofxOpenCvUtilsGrabCut*	grabCut;
	ofxCvGrayscaleImage		grayImage;
	ofxCvColorImage			currentFrame;
	ofxCvColorImage			resultFrame;
	ofVideoGrabber			grabber;
		
};