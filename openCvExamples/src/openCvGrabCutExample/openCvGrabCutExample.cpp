#include "openCvGrabCutExample.h"

openCvGrabCutExample::openCvGrabCutExample() {
	
}

openCvGrabCutExample::~openCvGrabCutExample() {
}

void openCvGrabCutExample::start() {
	ofEnableSmoothing();
	
	// Init grabber
	grabber.initGrabber(CAM_WIDTH_GC, CAM_HEIGHT_GC);
	
	// Init the salience tracker
	grabCut = new ofxOpenCvUtilsGrabCut();
	// Allocate the images
	currentFrame.allocate(CAM_WIDTH_GC, CAM_HEIGHT_GC);
	grayImage.allocate(CAM_WIDTH_GC, CAM_HEIGHT_GC);
	resultFrame.allocate(CAM_WIDTH_GC, CAM_HEIGHT_GC);
}

void openCvGrabCutExample::stop() {
	// Close the camera
	grabber.close();

	// Clear all images
	currentFrame.clear();
	grayImage.clear();
	resultFrame.clear();
}

void openCvGrabCutExample::update() {
	// Grab a frame
	grabber.update();
	
}

void openCvGrabCutExample::draw() {
	ofSetHexColor(0x9A9A9A);
	ofRect(0, 0, 320, 600);
	
	ofSetHexColor(0xFFFFFF);
	grabber.draw(0, 0);
	
	ofRect(320, 0, 320, 240);
	resultFrame.draw(320, 0);
	
	ofSetHexColor(0xB0B0B0);
	ofRect(320, 240, 320, 360);
	
}

void openCvGrabCutExample::keyReleased(ofKeyEventArgs &e) {
	if(e.key!='m' && e.key!='c') {
		return;
	}
	
	cv::Rect rect(10,10,300,220);
	IplImage fg;
	
	if(e.key=='c') {
		currentFrame.setFromPixels(grabber.getPixels(), CAM_WIDTH_GC, CAM_HEIGHT_GC);
	}
	
	fg = grabCut->grabcut(currentFrame.getCvImage(), rect, 2);
	resultFrame = &fg;
	
}

string openCvGrabCutExample::getStateName() {
	return "openCvGrabCutExample";
}