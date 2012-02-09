#include "faceTrackerExample.h"

faceTrackerExample::faceTrackerExample() {
	
}

faceTrackerExample::~faceTrackerExample() {
}

void faceTrackerExample::start() {
	// Init grabber
	grabber.initGrabber(CAM_WIDTH_FT, CAM_HEIGHT_FT);
	
	// The Haar detector xml file 
	// to be used by the tracker
	string haarDetectorXMLFile = "haarcascade_frontalface_alt2.xml";
	const int numScales = 2; 
	
	// Create a ofxFaceTracker instance
	faceTracker = new ofxNMPTFaceTracker(CAM_WIDTH_FT, CAM_HEIGHT_FT, numScales, 96, 72, haarDetectorXMLFile);
	
	// Allocate the images
	currentFrame.allocate(CAM_WIDTH_FT, CAM_HEIGHT_FT);
	grayImage.allocate(CAM_WIDTH_FT, CAM_HEIGHT_FT);
	resultFrame.allocate(CAM_WIDTH_FT, CAM_HEIGHT_FT);
}

void faceTrackerExample::stop() {
	// Close the camera
	grabber.close();
	
	// Clean up facetracker
	faceTracker = NULL;
	delete faceTracker;
	
	// Clear all images
	currentFrame.clear();
	grayImage.clear();
	resultFrame.clear();
}

void faceTrackerExample::update() {
	// Grab a frame
	grabber.update();
	
	if(!grabber.isFrameNew())
		return;
	
	// Update cv images
	currentFrame.setFromPixels(grabber.getPixels(), CAM_WIDTH_FT, CAM_HEIGHT_FT);
	grayImage = currentFrame;
	
	// Update the tracker
	faceTracker->update(grayImage.getCvImage());
	
	// Get fovea image
	resultFrame = faceTracker->getFoveaRepresentation();
}

void faceTrackerExample::draw() {
	ofSetHexColor(0x9A9A9A);
	ofRect(0, 0, 320, 600);
	
	// Draw the result
	ofSetHexColor(0xFFFFFF);
	resultFrame.draw(0,0);
}

string faceTrackerExample::getStateName() {
	return "faceTrackerExample";
}