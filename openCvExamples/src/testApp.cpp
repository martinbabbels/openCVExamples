#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	
	// Set the background
	ofBackgroundHex(0x525252);
	
	//ofSetFrameRate(30);
	
	manager = new ofxStateManager::ofxStateManager();
	manager->setState(&fg);
}

//--------------------------------------------------------------
void testApp::update(){
	string fps = ofToString(floor(ofGetFrameRate()));
	fps.append(" fps");
	
	string title = manager->getStateName();
	title.append(" | ");
	title.append(fps);
	
	// Debug the framerate
	ofSetWindowTitle(title);
}

//--------------------------------------------------------------
void testApp::draw(){
	
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	if(key=='1') {
		manager->setState(&facetracker);
	}
	
	if(key=='2') {
		manager->setState(&fastsalience);
	}
	
	if(key=='3') {
		manager->setState(&meanshift);
	}
	
	if(key=='4') {
		manager->setState(&grabcut);
	}
	
	if(key=='5') {
		manager->setState(&fg);
	}
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}