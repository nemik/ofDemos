#include "Message.h"

Message::Message(string t)
{
	//x = ofRandom(-10,10);
	//y = ofRandom(-1,-10);
	x = ofGetWidth()/4.5;
	y = ofGetHeight();
	speedX = ofRandom(0.8,1.8);
	speedY = ofRandom(1.5,2);
	radius = ofRandom(120,400);
	color = ofRandom(0, 0xff0000);
	
	ang = 0;
	grow = false;
	
	count = 0.0;
	
	dead = false;
	text = normalizeText(t);
	myFont.loadFont(font, font_size,true,true,true);
}

Message::Message(string t, float cx, float cy)
{
	x = ofGetWidth()/2;
	y = ofGetHeight();
	
	startx = cx;
	starty = cy;
	
	speedX = ofRandom(0.3,1);
	speedY = ofRandom(1.5,3);
	radius = ofRandom(120,400);
	color = ofRandom(0, 0xff0000);	
	
	ang = 0;
	
	grow = false;
	
	count = 0.0;
	
	dead = false;
	text = normalizeText(t);
	myFont.loadFont(font, font_size,true,true,true);
}


Message::Message(const Message& m)
{
	x = m.x;
	y = m.y;
	speedX = m.speedX;
	speedY = m.speedY;
	radius = m.radius;
	color = m.color;
	
	dead = m.dead;
	text = m.text;
	//myFont = m.myFont;
	myFont.loadFont(font, font_size,true,true,true);
	count = m.count;
	grow = m.grow;
}

void Message::update()
{
	x += (x>0) ? speedX : speedX*-1;
	y += (y>0) ? -1*speedY : speedY;//*-1;
	
	rect = myFont.getStringBoundingBox(text, x,y);
	
	if(x < -1*ofGetWidth() || y < 0)
	{
		dead = true;
	}
	
	if (ang > 360 && grow) 
	{
        ang -= 4;
		grow = false;
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

void Message::draw()
{
	count += 0.02;
	if(count > 1)
	{
		count = 1;
	}
	
	glPushMatrix();
	ofTranslate(ofGetWidth()/12, ofGetHeight()/15);
	ofScale(count, count, count);
	ofSetColor( 255 * ( 0 + sin( ang * 2 * PI / 360/ang )) / 2, 
			   255 * ( 2 + sin( PI + ang * 2 * PI / 360)) / 2,  255 * ( 0 + sin( PI + ang * 2 * PI / 360 )) / 2 );
	//ofEllipse(x,y-20,rect.width*1.7,rect.height*1.7);
	ofCircle(x, y-20, rect.width/1.85);
	ofSetColor(0x000000);
	//ofEllipse(x,y-20,rect.width*1.6,rect.height*1.6);
	ofCircle(x,y-20, rect.width/1.87);
	ofSetColor(0xffffff);
	//myFont.drawString(text+" "+ofToString(x, 3)+" "+ofToString(y, 3), x-(rect.width/2),y-rect.height/2.2);
	myFont.drawString(text, x-(rect.width/2),y-rect.height/2.2);
	glPopMatrix();
}

void Message::setText(string t)
{
	text = t;
}

string Message::normalizeText(string text)
{
	string buf; // Have a buffer string
    stringstream ss(text); // Insert the string into a stream
	
    vector<string> tokens; // Create vector to hold our words
	
    while (ss >> buf)
	{
        tokens.push_back(buf);
	}
	
	string output;
	
	for(int i=0; i< tokens.size(); i++)
	{
		output += tokens.at(i) + " ";
		if((i % 4) == 0 && i != 0)
		{
			output += "\n";
		}
	}
	int osize = output.size();
	return output.substr(0, osize-1);
}