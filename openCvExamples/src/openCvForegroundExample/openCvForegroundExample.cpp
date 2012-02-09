#include "openCvForegroundExample.h"

openCvForegroundExample::openCvForegroundExample():
	 minBlobSize(100)
	,maxBlobSize(1000)
	,useMoG(false)
	,shadowThreshold(10.0f)
{
	
}

openCvForegroundExample::~openCvForegroundExample() {
	// Allocate the images
	
}

void openCvForegroundExample::start() {
	
	fg = new ofxOpenCvUtilsForeground();
	meanShift = new ofxOpenCvUtilsMeanShift();
	
	grabber.initGrabber(CAM_WIDTH_FG, CAM_HEIGHT_FG);
	
	currentFrame.allocate(CAM_WIDTH_FG, CAM_HEIGHT_FG);
	resultFrame.allocate(CAM_WIDTH_FG, CAM_HEIGHT_FG);
	blobFrame.allocate(CAM_WIDTH_FG, CAM_HEIGHT_FG);
	trackFrame.allocate(CAM_WIDTH_FG, CAM_HEIGHT_FG);
	
	selectEnabled = false;
	
	// Setup the GUI
	gui = new GGui();
	gui->y = 275;
	gui->addBool("MoG", useMoG);
	gui->addFloat("Threshold", threshold, 1.0f, 250.0f, 1.0f);
	gui->addFloat("Learning", learningRate, 0.0f, 1.0f, 0.01f);
	gui->addFloat("Block", blockSize, 0.0f, 50.0f, 1.0f);
	gui->addFloat("Blur", blur, 0.0f, 50.0f, 1.0f);
	gui->addFloat("Shadows", shadowThreshold, 0.0f, 50.0f, 0.1f);
}

void openCvForegroundExample::stop() {
	grabber.close();
	
	selectEnabled = false;
	isTracking = false;
	
	fg->backgroundSet = false;
	fg = NULL;
	delete fg;
	
	meanShift = NULL;
	delete meanShift;
	
	// Clear all images
	currentFrame.clear();
	resultFrame.clear();
	blobFrame.clear();
}

void openCvForegroundExample::update() {
	// Update the player
	grabber.update();
	
	currentFrame.setFromPixels(grabber.getPixels(), CAM_WIDTH_FG, CAM_HEIGHT_FG);
	
	
	if(isTracking) {
		// define ROI 
		cv::Mat img = currentFrame.getCvImage();
		cv::Mat img2;
	
		IplImage imgf = fg->update(currentFrame.getCvImage());
		
		cvNot(&imgf, &imgf);
		resultFrame = &imgf;
		
		blobFrame = resultFrame;
		cv::Mat mask = blobFrame.getCvImage();
		cv::threshold(mask,mask,128,255,cv::THRESH_BINARY_INV);
		cv::add(mask,img,img2);

		IplImage* tmp = new IplImage(img2);
		trackFrame = tmp;
		
		meanShift->update(tmp);
		
		return;
	}
	
	if((grabber.isFrameNew() && fg->backgroundSet)) {

		fg->threshold = threshold;
		fg->learningRate = learningRate;
		fg->blockSize = blockSize;
		fg->shadowThreshold = shadowThreshold;
		
		if((int)blur%2==0) {
			blur++;
		}
		fg->blur = blur;
		
		if(useMoG) {
			fg->setMethod(MIXTURE_OF_GUASSIAN);
		} else {
			fg->setMethod(ACCUMULATE_WEIGHTED);
		}
		
		// Update the fg
		IplImage img = fg->update(currentFrame.getCvImage());
		cvNot(&img, &img);
		resultFrame = &img;
	
		blobFrame = resultFrame;
	} 
}

void openCvForegroundExample::draw() {
	ofSetHexColor(0x9A9A9A);
	ofRect(0, 0, 320, 600);
	
	ofSetHexColor(0xFFFFFF);
	grabber.draw(0,0);
	
	if(fg->backgroundSet) {
		
		resultFrame.draw(320, 0);
		if(isTracking) {
			trackFrame.draw(320,240);
		} else {
			blobFrame.draw(320,240);
		}
	}
	
	cv::RotatedRect rotated = meanShift->getRotatedRect();
	cv::Rect rect = rotated.boundingRect();
	
	float rb = rect.x + rect.width;
	float bb = rect.y + rect.height;
	
	
	// Draw rect
	if(isTracking) {
		
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
	
	
	// Draw GUI
	if(selectEnabled)
		ofSetHexColor(0x000000);
	else 
		ofSetHexColor(0xFFFFFF);
	
	gui->drawLabel("Hit spacebar to capture background", 10, 260);
	
	ofSetHexColor(0xFFFFFF);
	gui->draw();
}

void openCvForegroundExample::keyPressed(ofKeyEventArgs &e) {
	selectEnabled = (e.key==' ');
}

void openCvForegroundExample::keyReleased(ofKeyEventArgs &e) {
	if(e.key==' ') {
		fg->setBackground(currentFrame.getCvImage());
		selectEnabled = false;
	}
	
}

void openCvForegroundExample::gotMessage(ofMessage &e) {
	cout << e.message << endl;
}
	

string openCvForegroundExample::getStateName() {
	return "openCvForegroundExample";
}