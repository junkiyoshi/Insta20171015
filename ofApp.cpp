#include "ofApp.h"

//--------------------------------------------------------------
ofApp::~ofApp() {
	for (int i = this->particles.size() - 1; i > -1; i--) {
		delete this->particles[i];
		this->particles.erase(this->particles.begin() + i);
	}
}

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(60);
	ofBackground(0);
	ofSetWindowTitle("Insta");

	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);
}

//--------------------------------------------------------------
void ofApp::update(){
	Leap::Frame frame = leap.frame();
	for (Leap::Hand hand : frame.hands()) {
		if (hand.grabStrength() < 0.5) {
			ofVec2f velocity = ofVec2f(hand.palmVelocity().x, hand.palmVelocity().y);
			velocity.limit(15);
			this->particles.push_back(new Particle(ofVec2f(hand.palmPosition().x, hand.palmPosition().y - ofGetHeight() / 5), velocity));
		}
	}

	for (int i = this->particles.size() - 1; i > -1; i--) {
		this->particles[i]->update();

		if (this->particles[i]->isDead()) {
			delete this->particles[i];
			this->particles.erase(this->particles.begin() + i);
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	this->cam.begin();
	
	for (Particle* p : this->particles) {
		p->draw();
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main(){
	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}