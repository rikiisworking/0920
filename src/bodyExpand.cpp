#include "bodyExpand.h"

void bodyExpand::setup()
{
	bodyExpandShader.load("bodyParticleShader/bodyParticleShader");
	
}

void bodyExpand::update(bool kick,ofPath path)
{
	if (kick||ofGetFrameNum()%15==0) {
		bodyParticles.push_back(bodyExpandParticle(path));
	}
	for (int i = bodyParticles.size() - 1; i >= 0; i--) {
		bodyParticles[i].update();
		if (!bodyParticles[i].isAlive) {
			bodyParticles.erase(bodyParticles.begin() + i);
		}
	}
}

void bodyExpand::update(float * fft, ofPath path)
{
	ofPath temp = path;
	temp.setFilled(false);

	if (fft[0] > 0.65f&&ofGetFrameNum()%5==0) {
		bodyParticles.push_back(bodyExpandParticle(temp));
	}
	for (int i = bodyParticles.size() - 1; i >= 0; i--) {
		bodyParticles[i].update();
		if (bodyParticles[i].isAlive == false) {
			bodyParticles[i].bodyPath.clear();
			bodyParticles.erase(bodyParticles.begin() + i);
		}
	}
}

void bodyExpand::update(float * fft, bool kicked, ofPath path)
{
	if (fft[0] > 0.85f) {
		for(int i=0;i<5;i++){ bodyParticles.push_back(bodyExpandParticle(path)); }
	}
	for (int i = bodyParticles.size() - 1; i >= 0; i--) {
		bodyParticles[i].update(kicked);
		if (bodyParticles[i].isAlive == false) {
			bodyParticles[i].bodyPath.clear();
			bodyParticles.erase(bodyParticles.begin() + i);
		}
	}
}

void bodyExpand::draw(float*fft)
{
	bodyExpandShader.begin();
	bodyExpandShader.setUniform1f("time", ofGetElapsedTimef());
	bodyExpandShader.setUniform1fv("fft", &fft[0], 100);
	for (int i = 0; i < bodyParticles.size(); i++) {
		bodyParticles[i].draw();
		
	}
	bodyExpandShader.end();
}
