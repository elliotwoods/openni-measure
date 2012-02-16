#include "testApp.h"

testApp::testApp() :
scrPreviewDepth("Depth", kinect.getDepthTextureReference()),
scrPreviewRGB("RGB", kinect.getRGBTextureReference()),
scr3D("3D", kinectView),

wdgNewSession("Select path")

{
	scrMain.push(scrPreviewDepth);
	scrMain.push(scrPreviewRGB);
	scrMain.push(scrControl);
	scrMain.push(scr3D);
	
	scr3D.enableGrid(3.0f);
	//scr3D.setCursorEnabled(true);
	scrControl.push(&wdgNewSession);
	scrControl.push(new wdgButton("Capture [SPACE]", needsCapture));
	scrControl.push(new wdgCounter("snaps taken", count));
	scrControl.push(new wdgSlider("Point size", kinectView.pointSize, 1.0f, 20.0f, 1.0f, "px"));
    
	wdgButton* open = new wdgButton("Connected", this->open);
	scrControl.push(open);
	open->enabled = false;
	count = 0;
	needsCapture = false;

}

//--------------------------------------------------------------
void testApp::setup(){	
	screens.init(scrMain);	
	ofBackground(117/2,130/2,160/2);
	ofSetVerticalSync(true);
	ofSetFrameRate(30);
	
	if (!kinect.setupFromXML("settings/ofxopenni_config.xml")) {
		ofSystemAlertDialog("Failed to initialise device. Check config xml!");
		std::exit(0);
	}

	kinect.enableCalibratedRGBDepth();
	kinectView.init(kinect);
	startThread(true, false);

	chooseSessionName();
}

//--------------------------------------------------------------
void testApp::update(){
	lock();
	kinect.update();
	unlock();
	
	if (wdgNewSession.getBang())
		chooseSessionName();
}

void testApp::threadedFunction() {
	while (isThreadRunning()) {
		if (needsCapture)
			capture();
		ofSleepMillis(10);
	}
}
//--------------------------------------------------------------
void testApp::draw(){
	
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	if (key==' ')
		needsCapture = true;
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

//--------------------------------------------------------------
void testApp::chooseSessionName() {
	stringstream name;
	name << ofGetYear() << "-" << ofGetMonth() << "-" << ofGetDay() << "," << ofGetHours() << "." << ofGetMinutes() << "." << ofGetSeconds();
	sessionName = ofSystemSaveDialog(name.str(), "Choose session save path").getPath();
	
	ofDirectory::createDirectory(sessionName);
}
//--------------------------------------------------------------
void testApp::capture(){
	if (!kinect.getDepthPixels().isAllocated())
		return;
	
	string filename = sessionName + "/" + ofToString(ofGetElapsedTimeMillis(),0);
	
	lock();
	rgb = kinect.getRGBPixels();
	xyz = kinectView.getXYZ();
	unlock();
	
	ofSaveImage(rgb, filename + string(RGB_EXT));
	ofSaveImage(xyz, filename + string(XYZ_EXT));
	
	count++;
	needsCapture = false;
}