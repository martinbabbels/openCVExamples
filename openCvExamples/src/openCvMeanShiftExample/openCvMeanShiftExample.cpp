#include "openCvMeanShiftExample.h"

openCvMeanShiftExample::openCvMeanShiftExample() {
	
}

openCvMeanShiftExample::~openCvMeanShiftExample() {

}

string openCvMeanShiftExample::getStateName() {
	return "openCvMeanShiftExample";
}

void openCvMeanShiftExample::start() {
	// Enable smoothing
	ofEnableSmoothing();
	
	// Init the video grabber
	grabber.initGrabber(CAM_WIDTH_MS, CAM_HEIGHT_MS);
	
	// Setup the meanshift
	meanShift = new ofxOpenCvUtilsMeanShift();
	
	// Selection
	selectEnabled	= false;
	roiSelected		= false;
	roi				= cv::Rect(0,0,0,0);
	
	// Saturation threshold
	minSaturation	= 0;

	// Allocate the ofxOpenCv images
	currentFrame.allocate(CAM_WIDTH_MS, CAM_HEIGHT_MS);
	backprojection1.allocate(CAM_WIDTH_MS, CAM_HEIGHT_MS);
	backprojection2.allocate(CAM_WIDTH_MS, CAM_HEIGHT_MS);
	
	// Setup the GUI
	gui = new GGui();
	gui->y = CAM_Y_MS + CAM_HEIGHT_MS + 50;
	gui->addFloat("Saturation", minSaturation, 0.0f, 50.0f, 1.0f);
	
}

void openCvMeanShiftExample::stop() {
	// Clear all images
	currentFrame.clear();
	backprojection1.clear();
	backprojection2.clear();
	
	// Clean meanshift instance
	meanShift = NULL;
	delete meanShift;
	
	// Close the camera
	grabber.close();
}

void openCvMeanShiftExample::update() {
	
	// Grab a frame
	grabber.update();
	
	if(!grabber.isFrameNew())
		return;
	
	// Update cv images
	currentFrame.setFromPixels(grabber.getPixels(), CAM_WIDTH_MS, CAM_HEIGHT_MS);
	
	// Meanshift
	if(roiSelected) {
		meanShift->setMinSat(minSaturation);
		IplImage img = meanShift->update(currentFrame.getCvImage());
		backprojection2 = &img;
	}
	
}

void openCvMeanShiftExample::draw() {
	
	// Draw backgrounds
	ofSetHexColor(0x9A9A9A);
	ofRect(0, 0, 320, 600);
	
	ofSetHexColor(0xB0B0B0);
	ofRect(320, 0, 320, 600);

	// Draw video
	ofSetHexColor(0xFFFFFF);
	currentFrame.draw(0, 0);
	
	// Draw selection
	if(selectEnabled) {
		ofEnableAlphaBlending();
			ofSetColor(255, 255, 255, 100);
			ofRect(roi.x, roi.y, roi.width, roi.height);
		ofDisableAlphaBlending();
	}
	
	cv::RotatedRect rotated = meanShift->getRotatedRect();
	cv::Rect rect = rotated.boundingRect();
	
	float rb = rect.x + rect.width;
	float bb = rect.y + rect.height;
	
	
	// Draw rect
	if(roiSelected) {
		
		ofSetHexColor(0xFF0000);
		ofLine(rect.x, rect.y, rb, rect.y);	// Top
		ofLine(rb, rect.y, rb, bb);			// Right
		ofLine(rect.x, bb, rb, bb);			// Bottom
		ofLine(rect.x, rect.y, rect.x, bb);	// Left
		
		// Angle
		float angle = (rotated.angle>90) ? -(180-rotated.angle) : rotated.angle;
	
		ofPushMatrix();
			
			// Rotate
			ofTranslate(rotated.center.x, rotated.center.y, 0);
			ofRotateZ(angle);
			ofTranslate(-(rotated.center.x), -(rotated.center.y), 0);
			
			ofEnableAlphaBlending();
			ofSetColor(255, 255, 255, 100);
			
			float hw = rect.width/2;
			float hh = rect.height/2;
			
			// Angled lines
			ofLine(rotated.center.x, rotated.center.y-hh, rotated.center.x, rotated.center.y+hh);
			ofLine(rotated.center.x-hw, rotated.center.y, rotated.center.x+hw, rotated.center.y);
		
			ofDisableAlphaBlending();
		
			gui->drawLabel(ofToString(floor(angle)), rotated.center.x+5, rotated.center.y-6);
		
			
		ofPopMatrix();
	}
	
	// Draw debug images
	
	if(roiSelected) {
		ofSetHexColor(0xFFFFFF);
		backprojection1.draw(320, 0, 320, 240);
		backprojection2.draw(320, 240, 320, 240);
	}
	
	// Draw GUI
	if(selectEnabled)
		ofSetHexColor(0x000000);
	else 
		ofSetHexColor(0xFFFFFF);
	
	gui->drawLabel("Hold the spacebar and drag inside\nthe image to start selection", CAM_X_MS+10, CAM_Y_MS+CAM_HEIGHT_MS+20);
	
	ofSetHexColor(0xFFFFFF);
	gui->draw();
	
	
}

void openCvMeanShiftExample::mousePressed(ofMouseEventArgs &e) {
	
	// Check mouse
	if(!mouseInside()) {
		return;
	}
	
	// Reset the selection
	roiSelected = false;
	
	// Update selection
	roi = cv::Rect(e.x-CAM_X_MS, e.y-CAM_Y_MS, 0, 0);
}

void openCvMeanShiftExample::mouseReleased(ofMouseEventArgs &e) {
	
	// Check mouse
	if(!mouseInside()) {
		return;
	}
	
	int w = abs(roi.width);
	int h = abs(roi.height);
	
	// Minimum of 5px width and height
	roiSelected = (w>30 && h>30);
	
	// Set ROI
	if(roiSelected) {
		IplImage img = meanShift->setROI(currentFrame.getCvImage(), roi);
		backprojection1 = &img;
	}
	
	// Reset ROI
	roi = cv::Rect(0, 0, 0, 0);
}

void openCvMeanShiftExample::mouseDragged(ofMouseEventArgs &e) {
	
	// Check selection
	if(!selectEnabled) return;
	
	// Update selection
	roi.width = (e.x-CAM_X_MS) - roi.x;
	roi.height = (e.y-CAM_Y_MS) - roi.y;
}

void openCvMeanShiftExample::keyPressed(ofKeyEventArgs &e) {
	selectEnabled = (e.key==' ');
}

void openCvMeanShiftExample::keyReleased(ofKeyEventArgs &e) {
	if(e.key==' ') {
		selectEnabled = false;
	}
}

void openCvMeanShiftExample::gotMessage(ofMessage &e) {
	
}

bool openCvMeanShiftExample::mouseInside() {
	
	bool is_inside = true;

	if((roi.x+CAM_X_MS)+roi.width > CAM_WIDTH_MS+CAM_X_MS 
	   || (roi.y+CAM_Y_MS)+roi.height > CAM_HEIGHT_MS+CAM_Y_MS
	   || !selectEnabled) {
		is_inside = false;
	}
	
	if(!is_inside && roiSelected) {
		return false;
	}
	
	if(!is_inside) {
		roiSelected = false;
		roi = cv::Rect(0, 0, 0, 0);
	}
	return is_inside;
}