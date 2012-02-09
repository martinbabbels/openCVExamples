#pragma once

#define CAM_WIDTH_MS 320
#define CAM_HEIGHT_MS 240
#define CAM_X_MS 0
#define CAM_Y_MS 0

#include "ofMain.h";
#include "ofxState.h"
#include "ofxOpenCv.h"
#include "ofxOpenCvUtilsMeanShift.h"
#include "GGui.h"

class openCvMeanShiftExample : public ofxState {
	
public:
	
	openCvMeanShiftExample();
	~openCvMeanShiftExample();
	
	void stop();
	void start();
	void update();
	void draw();

	void mouseDragged(ofMouseEventArgs &e);
	void mousePressed(ofMouseEventArgs &e);
	void mouseReleased(ofMouseEventArgs &e);
	void keyPressed(ofKeyEventArgs &e);
	void keyReleased(ofKeyEventArgs &e);
	void gotMessage(ofMessage &e);
	
	string getStateName();
	bool mouseInside();

private:
	GGui*						gui;
	ofxOpenCvUtilsMeanShift*	meanShift;
	ofxCvColorImage				currentFrame;
	ofxCvGrayscaleImage			backprojection1;
	ofxCvGrayscaleImage			backprojection2;
	ofVideoGrabber				grabber;
	
	float						minSaturation;
	bool						roiSelected;
	bool						selectEnabled;
	cv::Rect					roi;
};