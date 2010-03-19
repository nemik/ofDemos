#include "Particle.h"

Particle::Particle()
{
	x = ofRandomf();
	//y = ofRandom(0.3,-10);
	y = ofRandomf();
	speedX = ofRandom(0,4);
	speedY = ofRandom(0,4);
	radius = ofRandom(1,40);
	color = ofRandom(0, 0xff0000);	
	
	age = 0;
	dead = false;
	maxAge = ofRandom(0, 550)+350;
	ang = ofRandom(100, 200);
	grow = false;
}

Particle::Particle(int cx, int cy)
{
	x = cx;
	y = cy;
	//y = ofRandomf();
	speedX = ofRandom(0,4);
	speedY = ofRandom(0,4);
	radius = ofRandom(1,40);
	color = ofRandom(0, 0xff0000);	
	
	age = 0;
	dead = false;
	maxAge = ofRandom(0, 550)+250;
	ang = ofRandom(100, 200);
	grow = false;
}

void Particle::update()
{
	age++;
	x += (x>0) ? speedX : speedX*-1;
	y += (y>0) ? speedY : speedY*-1;
	if (age >= maxAge)
	{
		dead = true;
	}
	
	if (ang > 360 && grow) 
	{
        ang -= 4;
		grow = false;
		//ofSleepMillis(900);
    }
	else if (ang < 0 && !grow)
	{
		ang += 4;
		grow = true;
	}
	else if(grow)
	{
		ang += 4;
	}
	else if(!grow)
	{
		ang -= 4;
	}
}

void Particle::draw()
{
	//ofEnableAlphaBlending();
	//glBlendFunc(GL_SRC_COLOR, GL_ONE);
	//glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	//glTexEnvi(GL_POINT_SPRITE, GL_COORD_REPLACE, GL_TRUE); 
	//ofSetColor(color);
	ofSetColor( 255 * ( 0 + sin( ang * 2 * PI / 360/ang )) / 2, 
			   255 * ( 2 + sin( PI + ang * 2 * PI / 360)) / 2,  255 * ( 0 + sin( PI + ang * 2 * PI / 360 )) / 2 );
	ofCircle(x, y, radius);
	
	//ofDisableAlphaBlending();
	//ofNoFill();
	ofSetColor(0,0,0);
	ofCircle(x,y,radius*0.92);
	//ofFill();
	//ofDisableAlphaBlending();
	
}