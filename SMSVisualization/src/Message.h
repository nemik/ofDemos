#ifndef MESSAGE
#define MESSAGE

#import "ofMain.h"

#define font_size 24

#define font "arialuni.ttf"

class Message
{
	private:
		float x;
		float y;
	
		float startx;
		float starty;
		int ang;
		int color;
		int radius;
		float speedX;
		float speedY;
		string text;
		bool grow;
	
		ofTrueTypeFont myFont;
	
		ofRectangle rect;

		string normalizeText(string text);
	
		float count;
	
	public:
		Message(string text);
		Message(string text, float x, float y);
		Message(const Message& m);
		void update();
		void draw();
		void setText(string s);
		bool dead;
};
#endif