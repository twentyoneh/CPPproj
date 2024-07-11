#pragma once
#include"String.h"

class Var
{
public:
	Var(int, double, const char*, unsigned);
	Var(int);
	Var(double);
	Var(const char*, unsigned);
	~Var();

private:
	int m_IntData;
	double m_DoubleData;
	String m_StringData;
};
