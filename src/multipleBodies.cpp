#include "multipleBodies.h"

ofColor red1(255, 30, 45), red2(230, 15, 15),
blue1(5, 20, 245), blue2(0, 80, 255),
green1(5, 205, 100), green2(0, 235, 180),
yellow1(255, 255, 0), yellow2(255, 205, 50);

void multipleBodies::setup()
{
	multipleBodyShader.load("multipleBodyShader/multipleBodyShader");
}

void multipleBodies::update(ofPath bodyPath)
{
	ofPath temp = bodyPath;
	temp.setFilled(true);
	temp.scale(8.0, 8.0);
	bodyDelayPath.push_back(temp);
	if (bodyDelayPath.size() > 50) {
		bodyDelayPath.erase(bodyDelayPath.begin());
	}
	addedSize = 0;
}

void multipleBodies::draw1(float * amps)
{
	shaderBegin(blue1, blue2, green2, green1,amps);
	if (bodyDelayPath.size() >= 50) {
		for (int i =0; i <=40; i += 5) {
			bodyDelayPath[i].scale(0.95, 0.95);
			bodyDelayPath[i].setFillColor(ofColor(75 + 20 * i / 5));
			bodyDelayPath[i].draw((float)ofGetWidth() / 2 -1224+(float)(i+10)/10 * 160, (float)ofGetHeight() - 824.0f +(float)i*7.5);
			bodyDelayPath[i].draw((float)ofGetWidth() / 2 +824 - (float)(i + 10) / 10 * 160, (float)ofGetHeight() - 824.0f + (float)i*7.5);
		}
	}
	shaderEnd();
}

void multipleBodies::draw2(float * amps)
{
	shaderBegin(yellow2, yellow1, red2, red1, amps);
	if (bodyDelayPath.size() >= 50) {
		for (int i = 0; i < 40; i++) {
			ofPushMatrix();
			ofTranslate(ofGetWidth() / 2-550 +i*8, ofGetHeight() / 2);
			bodyDelayPath[i].scale(1.02f, 1.02f);
			bodyDelayPath[i].setFillColor(ofColor(255, (float)(40 - i) / 40 * 255));
			bodyDelayPath[i].draw(0.f,  -575+i *30);
			ofPopMatrix();
		}
	}
	shaderEnd();
}

void multipleBodies::draw3(float* amps)
{
	shaderBegin(blue1, blue2, green1, green2,amps);
	if (bodyDelayPath.size() >= 50) {
		for (int i = 0; i < 40; i++) {
			ofPushMatrix();
			ofScale(1.1f, 1.1f);
			ofTranslate(ofGetWidth() / 2-50.0f, ofGetHeight() / 2);
			ofRotate(ofGetElapsedTimef()*10+(float)i / 40 * 365);
			bodyDelayPath[i].draw(0.f, 0.f);
			ofRotate(-ofGetElapsedTimef() * 20);
			bodyDelayPath[i].draw(500.0f, 0.f);
			ofPopMatrix(); 
		}
	}
	shaderEnd();
}

void multipleBodies::draw4(float * amps)
{
	shaderBegin(green2, green1, yellow2, yellow1, amps);
	if (bodyDelayPath.size() >= 50) {
		for (int i = 0; i < 10; i++) {
			for (int i2 = 0; i2 < 5; i2++) {
				ofPushMatrix();
				ofScale(0.9f, 0.9f);

				bodyDelayPath[i * 5 + i2].setFilled(true);
				bodyDelayPath[i * 5 + i2].draw(i*300.0f - 110.0f, i2 * 320 - 140.0f);
				ofPopMatrix();
			}
		}
	}
	shaderEnd();
}

void multipleBodies::shaderBegin(ofColor color1, ofColor color2, ofColor color3, ofColor color4,float* amps)
{

	ofFloatColor	blue1 = color1;
	ofFloatColor	blue2 = color2;
	ofFloatColor	green1 = color3;
	ofFloatColor	green2 = color4;

	blue1.lerp(green2, (cos(ofGetElapsedTimef() * 3.5f + amps[0] / 2.f) + 1) / 2);
	green1.lerp(blue2, (sin(ofGetElapsedTimef() * 2.5f + amps[1] / 1.5f) + 1) / 2);

	multipleBodyShader.begin();
	multipleBodyShader.setUniform1f("sound", amps[0]);
	multipleBodyShader.setUniform1f("time", ofGetElapsedTimef());
	multipleBodyShader.setUniform4f("inputColor1", blue1);
	multipleBodyShader.setUniform4f("inputColor2", green1);
}

void multipleBodies::shaderEnd()
{
	multipleBodyShader.end();
}
