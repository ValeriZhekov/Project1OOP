#include "Guest.h"
#include <fstream>
#include <iostream>
class Room
{private:
unsigned int num;
unsigned int beds;
Guest* Guests;
int capacity;
int size;
void resize();
public:
Room();
Room(const Room& other);
Room(const unsigned int num,const unsigned int beds);
~Room();
void copy(const Room& other);
Room& operator=(const Room& other);
Room& operator +=(const Guest& other);
unsigned int getNum() const;
unsigned int getBeds() const;
Guest* getGuest(int i);
int getSize() const;
friend std::ostream& operator <<(std::ostream& out,const Room& obj);
bool isFree(char date[9]);
bool isDateBetween(char date[9],char start[9],char end[9]);

};