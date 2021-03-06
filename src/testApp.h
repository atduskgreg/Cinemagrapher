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
    
    
        int gifFrameDensity;
        int targetNumFrames;
    
        int movieFrame;
        bool drawPolygon;
        bool recording;
    
    float blendDistance;
    
        float distanceFromPoly(const ofPoint & p, const vector<ofPoint> & poly);
        float distanceFromLine(const ofPoint & p, const ofPoint & l1, const ofPoint & l2);

};
