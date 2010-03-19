#ifndef FONT
#define FONT

#import "ofMain.h"

class Font 
{
	
private:
	float x;
	float y;
	
	int color;
	int radius;
	int age;
	int maxAge;
	float speedX;
	float speedY;
	
public:
	Particle();
	
	void update();
	void draw();
	bool dead;
};
#endif