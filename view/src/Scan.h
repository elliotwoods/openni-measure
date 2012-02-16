//
//  Scan.h
//  view
//
//  Created by Mimi Son on 16/02/2012.
//  Copyright (c) 2012 Kimchi and Chips. All rights reserved.
//
#pragma once
#include "ofMain.h"

#define XYZ_EXT "-xyz.hdr"
#define RGB_EXT "-rgb.jpg"

#define V1 topLeft + 1
#define V2 topLeft
#define V3 topLeft + width
#define V4 topLeft + width
#define V5 topLeft + width + 1
#define V6 topLeft + 1

#define Z_PLANE 2.0f

class Scan : public ofNode {
public:
	Scan();
	Scan(string filename);
	bool load(string filename="");
	void customDraw();
	
	string getPathRGB() const;
	string getPathXYZ() const;
	
	float pointSize;
	float maxJump;
protected:
	void fixNegatives();
	string fileTrunk;
	
	ofFloatPixels xyz;
	ofPixels rgb;
	
	void updateMesh();
	ofMesh mesh;
	ofTexture texture;
};