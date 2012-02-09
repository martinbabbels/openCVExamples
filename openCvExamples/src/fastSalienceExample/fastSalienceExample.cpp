#include "fastSalienceExample.h"

fastSalienceExample::fastSalienceExample() {
	
}

fastSalienceExample::~fastSalienceExample() {
}

void fastSalienceExample::start() {
	ofEnableSmoothing();
	
	// Init grabber
	grabber.initGrabber(CAM_WIDTH_FS, CAM_HEIGHT_FS);
	
	// Init the salience tracker
	salienceTracker = new ofxNMPTFastSalience();

	// Allocate the images
	currentFrame.allocate(CAM_WIDTH_FS, CAM_HEIGHT_FS);
	grayImage.allocate(CAM_WIDTH_FS, CAM_HEIGHT_FS);
	resultFrame.allocate(CAM_WIDTH_FS, CAM_HEIGHT_FS);
}

void fastSalienceExample::stop() {
	// Close the camera
	grabber.close();

	// Clear all images
	currentFrame.clear();
	grayImage.clear();
	resultFrame.clear();
}

void fastSalienceExample::update() {
	// Grab a frame
	grabber.update();
	
	// Update cv images
	currentFrame.setFromPixels(grabber.getPixels(), CAM_WIDTH_FS, CAM_HEIGHT_FS);
	grayImage = currentFrame;
	
	// Update the tracker
	salienceTracker->update(currentFrame.getCvImage());
	
}

void fastSalienceExample::draw() {
	ofSetHexColor(0x9A9A9A);
	ofRect(0, 0, 320, 600);
	
	ofPushMatrix();
		ofTranslate(0, 0, 0);
		vector<cv::KeyPoint> points_new = salienceTracker->getPoints();
		
		ofSetHexColor(0xFFFFFF);
		currentFrame.draw(0,0, 320, 240);
		
	
		if(points_new.size() < 200) {
			points = vector<cv::KeyPoint>(points_new);
			lqrpt = salienceTracker->getLqrpt();
		}
		
		
		ofSetHexColor(0xFFFFFF);
		ofCircle(lqrpt.x*2, lqrpt.y*2, 10);
		
		ofSetHexColor(0xFF0000);
		ofCircle(lqrpt.x*2, lqrpt.y*2, 5);
		
		ofSetHexColor(0xFFFFFF);
		for (size_t i = 0; i < points.size(); i++) {
			ofCircle(points[i].pt.x*2, points[i].pt.y*2, 1);
		}
	
	ofPopMatrix();
}

string fastSalienceExample::getStateName() {
	return "fastSalienceExample";
}