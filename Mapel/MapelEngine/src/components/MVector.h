#pragma once

#include <math.h>
#include <stdlib.h>
#include <stdio.h>

class MVector{
private: 
	float x = 0;
	float y = 0;

public: 
	MVector();
	MVector(float, float);
	~MVector();
	float getX();
	float getY();
	float getLength();
	void increaseVec(float, float);
	void increaseVec(MVector);

};

