#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	//engine setup
	ofHideCursor();
	ofSetFrameRate(60);
	kinectEngine.set();
	oscEngine.setup();
	soundAnalyzer.setup(oscEngine.ampList);

	//artwork setup
	titlePage.setup();
	bodyMasker.set(1);
	firework.setup();
	fallingParticle.setup();
	rectMotion.setup();
	bodyExpand.setup();
	multipleBodies.setup();
	shapeExpand.setup();
	singleLine.setup();
	arms.setup(55,45);
	blocks.setup();
	sand.setup();
	particleOnBody.setup();
	amebaCircle.setup();
	beach.setup();

	//-----------------other variables--------------------------
	kicked = false;
	snared = false;

	drawMod = 0;
}

//--------------------------------------------------------------
void ofApp::update(){
	
	std::stringstream strm;
	strm << "fps: " << ofGetFrameRate();
	ofSetWindowTitle(strm.str());

	kicked = soundAnalyzer.getKick();
	snared = soundAnalyzer.getSnare();

	kinectEngine.update();
	oscEngine.recieve();
	soundAnalyzer.update(oscEngine.ampList);
	//artwork
	
	if (!kinectEngine.isEmpty) {
		
		if (kinectEngine.isStreamed) {
			//------------------basic body masking---------------------
			auto temp = kinectEngine.kinect.getBodyIndexSource()->getPixels();
			temp.resize(64, 53);
			bodyMasker.update2(&(temp),kinectEngine.trackingId,kicked);

			//---------------------------------------------------------
			if (drawMod == 0) {
				shapeExpand.update(oscEngine.smoothed, kicked);
			}
			else if (drawMod == 1) {
				bodyExpand.update(oscEngine.ampList,kicked,bodyMasker.modifiedPath);
			}
			else if (drawMod ==2) {
				multipleBodies.update(bodyMasker.basePath);
			}
			else if (drawMod == 3) {
				arms.update(oscEngine.smoothed, kinectEngine.leftHand, kinectEngine.rightHand);
				multipleBodies.update(bodyMasker.basePath);
			}
			else if (drawMod == 4) {
				sand.update(oscEngine.smoothed, kicked);
				beach.update(kicked, oscEngine.smoothed);
			}
			else if (drawMod == 5) {
				blocks.update(kicked, oscEngine.smoothed);
				multipleBodies.update(bodyMasker.basePath);
				
			}
			else if (drawMod == 6) {
				amebaCircle.update(kicked, oscEngine.smoothed);
				multipleBodies.update(bodyMasker.basePath);
				
			}
			else if (drawMod == 7) {
				fallingParticle.update(bodyMasker.modifiedPath.getOutline().at(0), kicked);
			}
			oscEngine.send(0, kinectEngine.leftHandRelative.z, kinectEngine.rightHandRelative.z, kinectEngine.head.x, ofMap(ofDistSquared(kinectEngine.leftHand.x, kinectEngine.leftHand.y, kinectEngine.rightHand.x, kinectEngine.rightHand.y), 0, 1820, 0, 400));
			//particleOnBody.update(bodyMasker.modifiedPath);
		}
	}
	else {
		firework.update();
		firework.kicked(kicked);

		rectMotion.update(oscEngine.ampList, kicked);
		oscEngine.send(1,0.f, 0.f,960.0f, 400.0f);
	}
	drawMod = oscEngine.isPlayed;
}

//--------------------------------------------------------------
void ofApp::draw(){
	
	ofBackgroundGradient(ofColor(39.0f), ofColor(0.0f),OF_GRADIENT_LINEAR);
	
	if (!kinectEngine.isEmpty) {
		float tempHead = abs(960.0f - kinectEngine.head.x) / 960;
		if (drawMod == 0) {
			shapeExpand.drawRectFromPosition(oscEngine.smoothed, kinectEngine.leftHand, kinectEngine.rightHand);
		}
		else if (drawMod == 1) {
			ofSetColor(255);
			bodyExpand.draw(oscEngine.ampList);
		}
		else if (drawMod == 2) {
			singleLine.draw(oscEngine.smoothed);
			multipleBodies.draw1(oscEngine.smoothed);
			bodyMasker.draw3(tempHead, oscEngine.smoothed);
		}
		else if (drawMod == 3) {
			arms.draw(kinectEngine.head.x, kinectEngine.head.y, oscEngine.smoothed);
			multipleBodies.draw2(oscEngine.smoothed);
		}
		else if (drawMod == 4) {
			beach.draw2(oscEngine.smoothed,kinectEngine.leftHand,kinectEngine.rightHand,kinectEngine.head);
			sand.draw2(kinectEngine.leftHand, kinectEngine.rightHand, kinectEngine.head);
		}
		else if (drawMod == 5) {
			blocks.drawRect(oscEngine.smoothed);
			multipleBodies.draw3(oscEngine.smoothed);
		}
		else if (drawMod == 6) {
			amebaCircle.draw2(kinectEngine.leftHand, kinectEngine.rightHand, kinectEngine.head);
			multipleBodies.draw4(oscEngine.smoothed);
		}
		else if (drawMod == 7) {
			fallingParticle.draw(oscEngine.ampList);
			bodyMasker.draw3(tempHead, oscEngine.smoothed);
		}
	}
	else {
		firework.draw();
		rectMotion.draw();
		titlePage.draw3(oscEngine.ampList, kicked);
	}
	kicked = false;
	snared = false;
}

void ofApp::mousePressed(int x, int y, int button)
{
	drawMod++;
	if (drawMod > 2) {
		drawMod = 0;
	}
}
