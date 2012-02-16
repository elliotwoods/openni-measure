#include "testApp.h"

testApp::testApp() {
	
}

//--------------------------------------------------------------
void testApp::setup(){	
	ofBackground(100);
	ofSetVerticalSync(true);
	testScan.load();
	
	camera.rotate(180, 0, 1, 0);

}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){
	camera.begin();
	ofDrawGrid(2.0f, 5.0f, true);
	testScan.draw();
	camera.end();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	if (key == 'l')
		testScan.load();
	if (key == 'c')
		camera.toggleCursorDraw();
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