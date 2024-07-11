#pragma once
#include<malloc.h>
#include<iostream>
#include<memory>
#include<iostream>


class MathematicalSet
{
public:
	MathematicalSet();
	MathematicalSet(int*, int);
	MathematicalSet(int*);
	MathematicalSet(const MathematicalSet&);

	~MathematicalSet();
	

	bool isItemInSet(const int) const;
	void PrintSet() const;
	void GetItem(const int) const;
	int* GetPointSet() const;
	int GetLeaght() const;
	MathematicalSet* SetItem(const int);



	friend MathematicalSet operator+(const MathematicalSet&, const MathematicalSet&);
	//MathematicalSet operator+(const MathematicalSet&) const;
	MathematicalSet& operator+=(const MathematicalSet&);
	
	friend MathematicalSet operator-(const MathematicalSet&, const MathematicalSet&);
	//MathematicalSet operator-(const MathematicalSet&) const;
	MathematicalSet& operator-=(const MathematicalSet&);

	friend MathematicalSet operator*(const MathematicalSet&, const MathematicalSet&);
	MathematicalSet& operator*=(const MathematicalSet&);

	//friend MathematicalSet operator=(const MathematicalSet&, const MathematicalSet&);

	friend bool operator==(const MathematicalSet&, const MathematicalSet&);
	friend bool operator!=(const MathematicalSet&, const MathematicalSet&);

	friend std::ofstream& operator<<(std::ofstream&, const MathematicalSet&);
	//friend std::ifstream& operator>>(std::ifstream&, const MathematicalSet&);

	MathematicalSet& operator=(const MathematicalSet& other);
private:
	int* m_pSet{nullptr};
	int m_LenghtOfSet{0};

	static int countOfSets;

	friend int* FillSet(const MathematicalSet&, const MathematicalSet&, int*);
	friend int* DiffSet(const MathematicalSet&, const MathematicalSet&, int*);
	
};

