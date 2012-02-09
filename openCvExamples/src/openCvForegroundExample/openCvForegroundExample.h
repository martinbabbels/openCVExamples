#pragma once

#define CAM_WIDTH_FG 320
#define CAM_HEIGHT_FG 240

#include "ofMain.h";
#include "ofxState.h"
#include "ofxOpenCv.h"

#include "ofxOpenCvUtilsForeground.h"
#include "ofxOpenCvUtilsMeanShift.h"

#include "GGui.h"

class openCvForegroundExample : public ofxState {
	
public:
	
	openCvForegroundExample();
	~openCvForegroundExample();
	void stop();
	void start();
	void update();
	void draw();
	void keyPressed(ofKeyEventArgs &e);
	void keyReleased(ofKeyEventArgs &e);
	void gotMessage(ofMessage &e);
	void sendOSC();
	string getStateName();
	
private:
	GGui*						gui;
	ofxOpenCvUtilsForeground*	fg;
	ofxOpenCvUtilsMeanShift*	meanShift;
	
	ofxCvColorImage				currentFrame;
	ofxCvColorImage				blobFrame;
	ofxCvColorImage				trackFrame;
	ofxCvGrayscaleImage			resultFrame;
	
	ofVideoGrabber				grabber;
	
	float						threshold;
	float						learningRate;
	float						blockSize;
	float						minBlobSize;
	float						maxBlobSize;
	float						shadowThreshold;
	float						blur;
	bool						selectEnabled;
	bool						useMoG;
	bool						isTracking;
	
	
};