#ifndef _EMITTER
#define _EMITTER

#include "ofMain.h"

#include "Particle.h"
#include "Message.h"

#define max_particles 1000
#define m_size 10

class ParticleEmitter : public ofBaseApp
{
	
	private:
	
		int centerX;
		int centerY;
		float rotation;
		
		ofTrueTypeFont myFont;
	
	public:
	
		void setup();
		void update();
		void draw();
	
		void ParticleEmitter::bubbleMessage(string message);
	
		Particle* p[max_particles];
		Message* m[m_size];
};
#endif