#include "MathematicalSet.h"

int MathematicalSet::countOfSets = 0;

MathematicalSet::MathematicalSet(int* set, int lenght) :
	m_pSet{set ? new int [lenght] : nullptr},
	m_LenghtOfSet {lenght}
{
	if (m_pSet) 
	{
		for (int i = 0; i < lenght; i++)
		{
			m_pSet[i] = set[i];
		}
	}
	countOfSets++; 
}

MathematicalSet::MathematicalSet(int* set) : 
	MathematicalSet(set, int(_msize(set) / sizeof(int))) {}


MathematicalSet::MathematicalSet() : 
	MathematicalSet(nullptr, 0) {}

MathematicalSet::MathematicalSet(const MathematicalSet& other)
{
	m_LenghtOfSet = other.m_LenghtOfSet;
	if (other.m_pSet) {
		m_pSet = other.m_pSet;
		for (int i = 0; i < m_LenghtOfSet; i++)
		{
			m_pSet[i] = other.m_pSet[i];
		}
	}

}


MathematicalSet::~MathematicalSet()
{
	if (m_pSet)
		delete[] m_pSet;
	countOfSets--;
}

bool MathematicalSet::isItemInSet(const int data) const
{
	bool flag = false;
	for (int i = 0; i < m_LenghtOfSet; i++)
	{
		if (m_pSet[i] == data)
		{
			return true;
		}
		else
		{
			flag = false;
		}
	}
	return flag;
	
}

void MathematicalSet::PrintSet() const
{
	for (int i = 0; i < m_LenghtOfSet; i++)
	{
		std::cout << m_pSet[i] << " ";
	}
	std::cout << "\n";
}

void MathematicalSet::GetItem(const int index) const
{
	if (index <= m_LenghtOfSet)
	{
		std::cout << m_pSet[index];
	}
	std::cout << "\n";
}

int* MathematicalSet::GetPointSet() const
{
	return m_pSet;
}

int MathematicalSet::GetLeaght() const
{
	return m_LenghtOfSet;
}

//Правильно ли я выделяю память, пример вызова метода в main.cpp
MathematicalSet* MathematicalSet::SetItem(const int data) 
{
	if (!isItemInSet(data))
	{
		m_LenghtOfSet++;
		int* tmpSet = new int[m_LenghtOfSet];
		for (int i = 0; i < m_LenghtOfSet - 1; i++)
		{
			tmpSet[i] = m_pSet[i];
		}
		tmpSet[m_LenghtOfSet-1] = data;

		delete[] m_pSet;
		m_pSet = new int[m_LenghtOfSet];

		for (int i = 0; i < m_LenghtOfSet; i++)
		{
			m_pSet[i] = tmpSet[i];
		}
		delete[] tmpSet;
		return this;
	}
	else {
		return this;
	}
}

int* FillSet(const MathematicalSet& set1,const MathematicalSet& set2, int* tmpSet)
{
	for (int i = 0; i < set1.m_LenghtOfSet; i++)
	{
		tmpSet[i] = set1.m_pSet[i];
	}
	for (int i = 0; i < set2.m_LenghtOfSet; i++)
	{
		tmpSet[set1.m_LenghtOfSet + i] = set2.m_pSet[i];
	}
	return tmpSet;
}

int* DiffSet(const MathematicalSet& set1, const MathematicalSet& set2, int* tmpSet)
{
	int index = 0;
	for (int i = 0; i < set1.m_LenghtOfSet; i++)
	{
		if (!set2.isItemInSet(set1.m_pSet[i])) {
			tmpSet[index] = set1.m_pSet[i];
			index++;
		}
	}
	return tmpSet;
}

MathematicalSet operator+(const MathematicalSet& set1, const MathematicalSet& set2)
{
	unsigned newSize = set1.m_LenghtOfSet + set2.m_LenghtOfSet;
	int* tmpSet = new int[newSize];
	tmpSet = FillSet(set1, set2, tmpSet);
	MathematicalSet tmp(tmpSet, newSize);
	delete[] tmpSet;
	return tmp;
}

MathematicalSet operator-(const MathematicalSet& set1, const MathematicalSet& set2)
{
	unsigned newSize = 0;
	for (int i = 0; i < set1.m_LenghtOfSet; i++)
	{
		if (!set2.isItemInSet(set1.m_pSet[i])) {
			newSize++;
		}
	}

	int* tmpSet = new int[newSize];
	tmpSet = DiffSet(set1, set2, tmpSet);

	MathematicalSet tmp(tmpSet, newSize);
	delete[] tmpSet;
	return tmp;
}

MathematicalSet operator*(const MathematicalSet& set1, const MathematicalSet& set2)
{
	unsigned newSize = 0;
	for (int i = 0; i < set1.m_LenghtOfSet; i++)
	{
		if (set2.isItemInSet(set1.m_pSet[i])) {
			newSize++;
		}
	}

	int* tmpSet = new int[newSize];
	int index = 0;
	for (int i = 0; i < set1.m_LenghtOfSet; i++)
	{
		if (set2.isItemInSet(set1.m_pSet[i])) {
			tmpSet[index] = set1.m_pSet[i];
			index++;
		}
	}

	MathematicalSet tmp(tmpSet, newSize);
	delete[] tmpSet;
	return tmp;
}

bool operator==(const MathematicalSet& set1, const MathematicalSet& set2)
{
	bool flag = 1;
	if (set1.m_LenghtOfSet == set2.m_LenghtOfSet)
	{
		return false;
	}
	for (int i = 0; i < set1.m_LenghtOfSet; i++)
	{
		for (int j = 0; j < set2.m_LenghtOfSet; j++)
		{
			if (set1.m_pSet[i] == set1.m_pSet[j])
			{
				flag = true;
				break;
			}
			else
			{
				flag = false;
			}
		}
	}

	return flag;
}

bool operator!=(const MathematicalSet& set1, const MathematicalSet& set2)
{
	return !operator==(set1,set2);
}

std::ofstream& operator<<(std::ofstream& output, const MathematicalSet& set)
{
	set.PrintSet();
	return output;
}


MathematicalSet& MathematicalSet::operator+=(const MathematicalSet& other)
{
	int newSize = this->m_LenghtOfSet + other.m_LenghtOfSet;
	int* tmpSet = new int[newSize];
	tmpSet = FillSet(*this, other, tmpSet);
	delete[] m_pSet;
	m_LenghtOfSet = newSize;
	m_pSet = new int[newSize];

	for (int i = 0; i < m_LenghtOfSet; i++)
	{
		this->m_pSet[i] = tmpSet[i];
	}
	delete[] tmpSet;
	return *this;
}

MathematicalSet& MathematicalSet::operator-=(const MathematicalSet& other)
{
	unsigned newSize = 0;
	for (int i = 0; i < this->m_LenghtOfSet; i++)
	{
		if (!other.isItemInSet(this->m_pSet[i])) {
			newSize++;
		}
	}

	int* tmpSet = new int[newSize];
	tmpSet = DiffSet(*this, other, tmpSet);

	delete[]m_pSet;
	this->m_LenghtOfSet = newSize;
	this->m_pSet = new int[m_LenghtOfSet];

	for (int i = 0; i < this->m_LenghtOfSet; i++)
	{
		this->m_pSet[i] = tmpSet[i];
	}
	delete[] tmpSet;
	return *this;
}

MathematicalSet& MathematicalSet::operator*=(const MathematicalSet& other)
{
	unsigned newSize = 0;
	for (int i = 0; i < this->m_LenghtOfSet; i++)
	{
		if (other.isItemInSet(this->m_pSet[i])) {
			newSize++;
		}
	}
	m_LenghtOfSet = newSize;

	int* tmpSet = new int[newSize];
	int index = 0;
	for (int i = 0; i < this->m_LenghtOfSet; i++)
	{
		if (other.isItemInSet(this->m_pSet[i])) {
			tmpSet[index] = this->m_pSet[i];
			index++;
		}
	}
	delete[] m_pSet;
	m_pSet = new int[newSize];
	for (int i = 0; i < m_LenghtOfSet; i++)
	{
		m_pSet[i] = tmpSet[i];
	}

	delete[] tmpSet;
	return *this;
}

MathematicalSet& MathematicalSet::operator=(const MathematicalSet& other)
{
	if (this == &other) return *this; 

	delete[] m_pSet; 

	m_LenghtOfSet = other.m_LenghtOfSet;
	m_pSet = new int[m_LenghtOfSet];
	for (int i = 0; i < m_LenghtOfSet; ++i) {
		m_pSet[i] = other.m_pSet[i];
	}

	return *this;
}
