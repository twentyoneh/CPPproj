#define ELEVATORBUILDER_H
#ifdef ELEVATORBUILDER_H

#include<queue>
#include"passengerrequest.h"

class ElevatorBuilder
{
public:
	int currentFloor; // Текущий этаж лифта
	std::queue<PassengerRequest> requests; // Очередь запросов внутри лифта
	bool direction;   // Текущее направление движения
	bool isIdle;      // Ожидает ли лифт запросы

	ElevatorBuilder();
	~ElevatorBuilder();

private:

};


#endif