#define ELEVATORBUILDER_H
#ifdef ELEVATORBUILDER_H

#include<queue>
#include"passengerrequest.h"

class ElevatorBuilder
{
public:
	int currentFloor; // ������� ���� �����
	std::queue<PassengerRequest> requests; // ������� �������� ������ �����
	bool direction;   // ������� ����������� ��������
	bool isIdle;      // ������� �� ���� �������

	ElevatorBuilder();
	~ElevatorBuilder();

private:

};


#endif