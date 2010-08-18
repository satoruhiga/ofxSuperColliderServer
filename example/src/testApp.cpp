#include "testApp.h"

#include "ofxSuperCollider.h"
#include "ofxSuperColliderServer.h"

ofxSCSynth *synth1 = NULL;
ofxSCSynth *synth2 = NULL;

//--------------------------------------------------------------
void testApp::setup(){
	
	ofxSuperColliderServer::init();
}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
	if (synth1)
	{
		synth1->set("freq", x * 2);
		synth1->set("pan", ofMap(x, 0, ofGetWidth(), -1, 1, true));
		
		synth2->set("freq", x * 4);
		synth2->set("pan", ofMap(x, 0, ofGetWidth(), 1, -1, true));
	}
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	if (synth1 == NULL)
	{
		synth1 = new ofxSCSynth("sine");
		synth1->create();
		
		synth2 = new ofxSCSynth("sine");
		synth2->create();		
	}	
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

