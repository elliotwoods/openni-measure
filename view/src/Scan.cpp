//
//  Scan.cpp
//  view
//
//  Created by Mimi Son on 16/02/2012.
//  Copyright (c) 2012 Kimchi and Chips. All rights reserved.
//
#include "Scan.h"

Scan::Scan() {
	this->fileTrunk = "";
	this->pointSize = 1.0f;
	this->maxJump = 0.1f;
}

Scan::Scan(string filename) {
	this->fileTrunk = "";
	this->pointSize = 1.0f;
	this->maxJump = 0.1f;
	this->load(filename);
}

bool Scan::load(string filename) {
	if (filename=="")
		filename = ofSystemLoadDialog("Select xyz or rgb file from pair").getPath();
	
	if (filename=="" || !ofFile::doesFileExist(filename)) {
		ofLogError() << "Scan::load(" << filename << ") failed to find file you selected";
		return false;
	}
	
	string fileTrunk = ofFilePath::removeExt(filename);
	fileTrunk = fileTrunk.substr(0, fileTrunk.length() - 4);
	
	if (!(ofFile::doesFileExist(fileTrunk + XYZ_EXT) && ofFile::doesFileExist(fileTrunk + RGB_EXT))) {
		ofLogError() << "Scan::load(" << filename << ") failed to find both xyz and rgb file";
		return false;
	}
	
	this->fileTrunk = fileTrunk;
	ofLoadImage(this->rgb, getPathRGB());
	ofLoadImage(this->xyz, getPathXYZ());
	
	updateMesh();
	return true;		
}

void Scan::customDraw() {
	texture.bind();
	glPointSize(pointSize);
	mesh.drawFaces();
	texture.unbind();
}

string Scan::getPathRGB() const {
	return this->fileTrunk + RGB_EXT;
}

string Scan::getPathXYZ() const {
	return this->fileTrunk + XYZ_EXT;
}

void Scan::updateMesh() {
	
	int width = xyz.getWidth();
	int height = xyz.getHeight();

	float distance;
	const ofVec3f const * xyzPixels = (ofVec3f*) xyz.getPixels();
	vector<ofIndexType> indices;
	indices.reserve((width-1) * (height-1) * 6);
	ofIndexType topLeft;
	vector<ofVec2f> texCoords;
	texCoords.reserve(width * height);
	for (int j=0; j<height; j++) {
		for (int i=0; i<width; i++) {
			topLeft = i + j * width;
			
			distance = abs((xyzPixels[V1] + xyzPixels[V2] + xyzPixels[V3]).z / 3.0f - xyzPixels[V1].z);
			if ((xyzPixels[V1].z > Z_PLANE && xyzPixels[V2].z > Z_PLANE && xyzPixels[V3].z > Z_PLANE) && (distance < maxJump)) {
				indices.push_back(V1);
				indices.push_back(V2);
				indices.push_back(V3);
			}
			
			distance = abs((xyzPixels[V4] + xyzPixels[V5] + xyzPixels[V6]).z / 3.0f - xyzPixels[V1].z);
			if ((xyzPixels[V4].z > Z_PLANE && xyzPixels[V5].z > Z_PLANE && xyzPixels[V6].z > Z_PLANE) && (distance < maxJump)) {
				indices.push_back(V4);
				indices.push_back(V5);
				indices.push_back(V6);
			}
			
			texCoords.push_back(ofVec2f(i, j));
		}
	}
	
	mesh.clear();
	mesh.addVertices((ofVec3f*) xyz.getPixels(), xyz.getWidth() * xyz.getHeight());
	mesh.addIndices(indices);
	mesh.addTexCoords(texCoords);
	texture.allocate(rgb.getWidth(), rgb.getHeight(), GL_RGB);
	texture.loadData(rgb);
}

void Scan::fixNegatives() {
	//fix cols
	ofVec3f* xyz = (ofVec3f*) this->xyz.getPixels();
	for (int i=0; i<this->xyz.getWidth()-1; i++) {
		for (int j=0; 
	}
}