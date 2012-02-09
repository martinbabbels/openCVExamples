#pragma once

#define CAM_WIDTH_FS 160
#define CAM_HEIGHT_FS 120

#include "ofMain.h";
#include "ofxState.h"
#include "ofxOpenCv.h"
#include "ofxNMPTFastSalience.h"

class fastSalienceExample : public ofxState {
	
public:
	
	fastSalienceExample();
	~fastSalienceExample();
	void stop();
	void start();
	void update();
	void draw();
	string getStateName();
	
private:
	vector<cv::KeyPoint> points;
	cv::Point			 lqrpt;
	ofxNMPTFastSalience* salienceTracker;
	ofxCvGrayscaleImage  grayImage;
	ofxCvColorImage		 currentFrame;
	ofxCvGrayscaleImage	 resultFrame;
	ofVideoGrabber		 grabber;
	
};