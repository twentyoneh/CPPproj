#include <iostream>
#include"MathematicalSet.h"

/*
* 
* ��������� - ��������� ��������
* +, +=(�������� 2-� ��������) 
* -, -=(��������� 2-� ��������)
* *, *=(����������� 2-� ��������)
* 
* ������� �������� ��������� 
* ==, !=  
* 
* ���������� ��������� << 
* ���������� ��������� = (����������� �����������)
* 
*/

int main()
{
    int set_data1[]{ 5,6,7,8,2,15 };
    int set_data2[]{ 8,0,11,22,21,31 };
    MathematicalSet set1(set_data1, 6);
    MathematicalSet set2(set_data2, 6);
    set2.SetItem(7); //��� ���� ������� ��� ��������� 
    set1.PrintSet();
    set2.PrintSet();
    /*MathematicalSet set3 = set1 * set2;
    set3.PrintSet();*/
    set1 -= set2; 
    set1.PrintSet();

}