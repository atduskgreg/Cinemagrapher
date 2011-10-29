#include "testApp.h"


// TODO:
// - make an image from the first frame of the movie
// - or the frame shown at the time of a click
//--------------------------------------------------------------
void testApp::setup(){
    ofBackground(0, 0, 0);
    ofSetVerticalSync(true);
    
    movie.loadMovie("fingers.mov");
    movie.play();
    
    result.allocate(movie.getWidth(), movie.getHeight(), OF_IMAGE_COLOR);
    background.allocate(movie.getWidth(), movie.getHeight(), OF_IMAGE_COLOR);

    outputPixels = result.getPixels();
    drawPolygon = true;

}

//--------------------------------------------------------------
void testApp::update(){
    movie.idleMovie();
    moviePixels = movie.getPixels();
}

//--------------------------------------------------------------
void testApp::draw(){
    ofBackground(0, 0, 0);
    
    if(polygonPoints.size() > 2){
        for(int y = 0; y < movie.getHeight();y++){
            for(int x = 0; x < movie.getWidth(); x++){
                int i = y * movie.getWidth() + x;
            
                if(pointInPolygon(&polygonPoints, polygonPoints.size(), ofPoint(x,y))){
                    outputPixels[i*3+0] = moviePixels[i*3+0];
                    outputPixels[i*3+1] = moviePixels[i*3+1];
                    outputPixels[i*3+2] = moviePixels[i*3+2];
                } else {
                    outputPixels[i*3+0] = backgroundPixels[i*3+0];
                    outputPixels[i*3+1] = backgroundPixels[i*3+1];
                    outputPixels[i*3+2] = backgroundPixels[i*3+2];
                }
            }
       
        }
    
            result.setFromPixels(outputPixels, movie.getWidth(), movie.getHeight(), OF_IMAGE_COLOR, true);
            result.draw(0,0);

        } else {
            movie.draw(0,0);

        }
    
       if(drawPolygon){
           ofSetColor(255, 255, 255);
           ofNoFill();
           ofBeginShape();
           for (int i = 0; i < polygonPoints.size(); i++){
            ofVertex(polygonPoints[i].x, polygonPoints[i].y);
           }
           ofEndShape(true);
       }
    
}
    


bool testApp::pointInPolygon(vector<ofPoint> *polygon,int N, ofPoint p)
{
    int counter = 0;
    int i;
    double xinters;
    ofPoint p1,p2;
    
    p1 = polygon->at(0);
    for (i=1;i<=N;i++) {
        p2 = polygon->at(i % N);
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

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
   
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
        polygonPoints.push_back(ofPoint(x, y));
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    polygonPoints.clear();
    drawPolygon = true;
    
    background.setFromPixels(moviePixels, movie.getWidth(), movie.getHeight(), OF_IMAGE_COLOR, true);
    backgroundPixels = background.getPixels();
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    drawPolygon = false;
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