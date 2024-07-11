#include"String.h"
#include "Var.h"



Var::Var(int intData, double doubleData, const char* stringData, unsigned stringSize) :
	m_IntData{ intData },
	m_DoubleData{ doubleData },
	m_StringData{ stringData,stringSize } {

}

Var::Var(int intData) : 
	Var(intData,0,nullptr,0) {}

Var::Var(double doubleData) : 
	Var(0,doubleData,nullptr,0) {}

Var::Var(const char* stringData, unsigned stringSize) :
	Var(0,0, stringData, stringSize) {}


Var::~Var()
{
}
