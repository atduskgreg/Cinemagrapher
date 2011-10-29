#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofBackground(0, 0, 0);
    ofSetVerticalSync(true);
    
    movie.loadMovie("fingers.mov");
    addingPoints = true;

}

//--------------------------------------------------------------
void testApp::update(){
}

//--------------------------------------------------------------
void testApp::draw(){
    ofSetColor(255, 255, 255);
    
    ofNoFill();
    ofBeginShape();
    for (int i = 0; i < polygonPoints.size(); i++){
        ofVertex(polygonPoints[i].x, polygonPoints[i].y);
    }
    ofEndShape(true);
}

// TODO:
// - refactor this to vector of ofPoints
static bool InsidePolygon(ofPoint *polygon,int N, ofPoint p)
{
    int counter = 0;
    int i;
    double xinters;
    ofPoint p1,p2;
    
    p1 = polygon[0];
    for (i=1;i<=N;i++) {
        p2 = polygon[i % N];
        if (p.y > MIN(p1.y,p2.y)) {
            if (p.y <= MAX(p1.y,p2.y)) {
                if (p.x <= MAX(p1.x,p2.x)) {
                    if (p1.y != p2.y) {
                        xinters = (p.y-p1.y)*(p2.x-p1.x)/(p2.y-p1.y)+p1.x;
                        if (p1.x == p2.x || p.x <= xinters)
                            counter++;
                    }
                }
            }
        }
        p1 = p2;
    }
    
    if (counter % 2 == 0)
        return false;
    else
        return true;
}



//--------------------------------------------------------------
void testApp::keyPressed(int key){
    addingPoints = !addingPoints;
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
   
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    if(addingPoints){
        polygonPoints.push_back(ofPoint(x, y));
    }

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
//    if(addingPoints){
//        polygonPoints.push_back(ofPoint(x, y));
//    }
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}