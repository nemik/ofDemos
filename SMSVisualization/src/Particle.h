#ifndef PARTICLE
#define PARTICLE

#import "ofMain.h"

class Particle 
{
	
	private:
		float x;
		float y;
	
		int color;
		int radius;
		int age;
		int ang;
		int maxAge;
		float speedX;
		float speedY;
		bool grow;
	
		string message;
	
	public:
		Particle();
		Particle(int x, int y);
	
		void update();
		void draw();
		bool dead;
};
#endif