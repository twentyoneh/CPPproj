#define PASSENGERREQUEST_H
#ifdef PASSENGERREQUEST_H

class PassengerRequest {
    int callFloor;    // Этаж, с которого вызывают лифт
    int targetFloor;  // Целевой этаж
    bool direction;   // true - вверх, false - вниз
};

#endif