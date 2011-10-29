#include "testApp.h"


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
    //gifEncoder.setDitherMode(OFX_GIF_DITHER_BAYER4x4);
    
    gifFrameDensity = 2;
    targetNumFrames = movie.getTotalNumFrames() / gifFrameDensity;
    
    float movieFrameRate = movie.getTotalNumFrames()/movie.getDuration();
    
    cout << movieFrameRate <<endl;
    
    movieFrame = 0;    
    gifEncoder.setup(movie.getWidth(), movie.getHeight(), (gifFrameDensity+1)/movieFrameRate, 125);
    
    recording = false;

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
            
                ofPoint p = ofPoint(x,y);
                
                if(ofInsidePoly(p, polygonPoints)){
                    if(distanceFromPoly(p, polygonPoints) < 10){
                        outputPixels[i*3+0] = 255;
                        outputPixels[i*3+1] = 0;
                        outputPixels[i*3+2] = 0;
                    } else {
                    
                    outputPixels[i*3+0] = moviePixels[i*3+0];
                    outputPixels[i*3+1] = moviePixels[i*3+1];
                    outputPixels[i*3+2] = moviePixels[i*3+2];
                    }
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
        
        if(recording && (movieFrame < targetNumFrames)){
            cout << movieFrame << "/" << targetNumFrames << endl;
            gifEncoder.addFrame(outputPixels, movie.getWidth(), movie.getHeight());
            movieFrame+= gifFrameDensity;
        }
    
        if(recording && movieFrame >= targetNumFrames){
            cout << "savng..." << endl;
            gifEncoder.save("test3_ah.gif");
            recording = false;
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


float testApp::distanceFromLine(const ofPoint & p, const ofPoint & l1, const ofPoint & l2){
    float xDelta = l2.x - l1.x;
    float yDelta = l2.y - l1.y;

    //	final double u = ((p3.getX() - p1.getX()) * xDelta + (p3.getY() - p1.getY()) * yDelta) / (xDelta * xDelta + yDelta * yDelta);
    float u = ((p.x - l1.x) * xDelta + (p.y - l1.y)*yDelta) / (xDelta * xDelta + yDelta * yDelta);
    
    ofPoint closestPointOnLine;
    if (u < 0) {
	    closestPointOnLine = l1;
	} else if (u > 1) {
	    closestPointOnLine = l2;
	} else {
        closestPointOnLine = ofPoint(l1.x + u * xDelta, l1.y + u * yDelta);
	}
    
   
    ofPoint d = p - closestPointOnLine;
    return sqrt(d.x * d.x + d.y * d.y); // distance
}


float testApp::distanceFromPoly(const ofPoint & p, const vector<ofPoint> & poly){
    float result = 10000;
    
    // check each line
    for(int i = 0; i < poly.size(); i++){
        int previousIndex = i -1;
        if(previousIndex < 0){
            previousIndex = poly.size() - 1;
        }
        
        ofPoint currentPoint = poly.at(i);
        ofPoint previousPoint = poly.at(previousIndex);
        
        
        float segmentDistance = distanceFromLine(ofPoint(p.x,p.y), previousPoint, currentPoint);
        
        
        if(segmentDistance < result){
            result = segmentDistance;
        }
         
        
        
        
        
    }
    
    return result;
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
  
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    cout << "recording: "  << recording << endl;
    if(key == ' '){
        recording = true;
    }
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
    //vector<ofPoint> diagnolLine;
    //diagnolLine.push_back(ofPoint(0,0));
    //diagnolLine.push_back(ofPoint(ofGetWidth(), ofGetHeight()));
  
    cout << distanceFromPoly(ofPoint(x,y), polygonPoints) << endl;
    //cout << distanceFromLine(ofPoint(x,y), ofPoint(0,0), ofPoint(ofGetWidth(), ofGetHeight())) << endl;
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