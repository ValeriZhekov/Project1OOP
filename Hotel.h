#include "Room.h"
class Hotel
{private:
Room* Rooms;
int capacity;
int size;
void resize();
public:
Hotel();
~Hotel();
void copy(const Hotel& other);
Hotel& operator=(const Hotel& other);
Hotel& operator+=(const Room& other);
friend std::ostream& operator<<(std::ostream& out,const Hotel& obj);
void addGuest(int roomnum);
int findRoom(int num);
void freeRooms(char date[9]);
void clearRoom(int roomnum,char date[9]);
void findFreeRoom(char start[9],char end[9],int beds);
void closeRoom(int roomnum);
void isFreeFile();
int getSize();
void Menu();
};