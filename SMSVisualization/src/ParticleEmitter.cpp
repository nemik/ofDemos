#include "ParticleEmitter.h"

#include "mongoose.h"

static string incoming_message;

static void
test_get_var(struct mg_connection *conn, const struct mg_request_info *ri,
			 void *user_data)
{
	char *value;
	
	value = mg_get_var(conn, "text");
	if (value != NULL) 
	{
		//string s = value;
		mg_printf(conn, "Value: [%s]\n", value);
		mg_printf(conn, "Value size: [%u]\n", (unsigned) strlen(value));
		incoming_message = value;
		free(value);
	}
	else
	{
		mg_printf(conn, "Text cannot be null");
	}
}

void ParticleEmitter::setup()
{	
	myFont.loadFont(font, 32,true,true,true);
	
    ofBackground(0, 0, 0);
    ofHideCursor();
	//for smooth animation, set vertical sync if we can
	ofSetVerticalSync(true);
	
	//debug
	//ofSetFrameRate(1);
	
    //ofEnableSmoothing();
    ofSetCircleResolution(70);
	centerX = ofGetWidth()/2;
    centerY = ofGetHeight() - 100;
    rotation = 0;
    for (int i=0; i<max_particles; i++)
	{
		p[i] = new Particle();
	}
	for (int i=0; i<m_size; i++)
	{
		m[i] = 0;
	}	
	glEnable(GL_ALPHA_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	//server
	//TCP.setup(11999);
	
	struct mg_context *ctx;
	ctx = mg_start();
	mg_set_option(ctx, "ports", "11999");
	
	mg_set_uri_callback(ctx, "/sms", &test_get_var, NULL);
}

void ParticleEmitter::update()
{
	centerX += ofRandom(0,4);
	centerY += ofRandom(0,4);
	
	if(centerX > ofGetWidth())
	{
		centerX = 0;
	}
	if(centerY > ofGetHeight())
	{
		centerY = 0;
	}
	
	for (int i=0; i<max_particles; i++) 
	{
        p[i]->update();
		if (p[i]->dead==true) 
		{
			delete p[i];	
			p[i] = new Particle(centerX,centerY);
		} 
    }
	for (int i=0; i<m_size; i++) 
	{
		if(m[i] != 0)
		{
			m[i]->update();
			if (m[i]->dead==true) 
			{
				delete m[i];
				m[i] = 0;			
			}
		}
    }
    rotation+=0.3;
}

void ParticleEmitter::draw()
{	
	for (int i=0; i<max_particles; i++) 
	{
		p[i]->draw();
	}
	
	for(int i=0; i< m_size; i++)
	{
		if(m[i] != 0)
		{
			m[i]->draw();
		}
	}
	//draw framerate
	ofSetColor(0xffffff);
	ofDrawBitmapString("frame rate: "+ofToString(ofGetFrameRate(), 3), 20, 30);
	
	if(incoming_message.length() > 1)
	{
		bubbleMessage(incoming_message);
		incoming_message = "";
	}
}

void ParticleEmitter::bubbleMessage(string message)
{
	delete m[0];
	m[0] = 0;
	
	for(int i=1; i<m_size; i++)
	{
		if(m[i] != 0)
		{
			Message *t = new Message(*m[i]);
			delete m[i];
			m[i] = 0;
			m[i-1] = t;
		}
	}
	
	if(m[m_size-1] != 0)
	{
		delete m[m_size-1];//->dead = true;
	}
	m[m_size-1] = new Message(message);
	m[m_size-1]->draw();
}