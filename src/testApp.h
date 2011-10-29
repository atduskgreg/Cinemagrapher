#pragma once

#include "ofMain.h"
#include "ofxGifEncoder.h"


class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        ofxGifEncoder gifEncoder;
        ofVideoPlayer 		movie;
        
        vector<ofPoint> polygonPoints;
        ofImage result;
        ofImage background;
    
        unsigned char * moviePixels;
        unsigned char * backgroundPixels;
        unsigned char * outputPixels;
    
    
    int framesRecorded;
        bool drawPolygon;

        bool pointInPolygon(vector<ofPoint> *polygon,int polysides, ofPoint p);
    
    bool recording;
};
