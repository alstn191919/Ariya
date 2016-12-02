#pragma once
#include "stdafx.h"
#include <iostream>

class cVector3
{
public:
	cVector3(void);
	~cVector3(void);

	float x, y, z;

	// ==, !=, +, -, *(scalar, ��ȯ��Ģ), 
	cVector3 Normalize();
	float Length();
	static float Dot(cVector3& v1, cVector3& v2);
	static cVector3 Cross(cVector3& v1, cVector3 v2);
	void Print(); // (x, y, z) �Ҽ� 2°�ڸ�����
};

// ==, !=, +, -, *(scalar, ��ȯ��Ģ)
//������ �����ε�