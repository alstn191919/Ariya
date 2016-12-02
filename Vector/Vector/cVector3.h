#pragma once
#include "stdafx.h"
#include <iostream>

class cVector3
{
public:
	cVector3(void);
	~cVector3(void);

	float x, y, z;

	// ==, !=, +, -, *(scalar, 교환법칙), 
	cVector3 Normalize();
	float Length();
	static float Dot(cVector3& v1, cVector3& v2);
	static cVector3 Cross(cVector3& v1, cVector3 v2);
	void Print(); // (x, y, z) 소수 2째자리까지
};

// ==, !=, +, -, *(scalar, 교환법칙)
//연산자 오버로딩