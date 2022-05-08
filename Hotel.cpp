#include <iostream>
#include <fstream>
#include <cstring>
#include "Hotel.h"
// Room--------------------------------------------------------
void Room::resize()
{
    Guest *a = new Guest[this->capacity * 2];
    if (!a)
    {
        std::cout << "Problem with memory";
        return;
    }
    this->capacity *= 2;
    for (int i = 0; i < this->size; i++)
    {
        a[i] = this->Guests[i];
    }
    delete[] this->Guests;
    this->Guests = a;
}
Room::Room()
{
    this->num = 0;
    this->beds = 0;
    this->size = 0;
    this->capacity = 8;
    this->Guests = new Guest[this->capacity];
}
Room::Room(const unsigned int num, const unsigned int beds)
{
    this->num = num;
    this->beds = beds;
    this->size = 0;
    this->capacity = 8;
    this->Guests = new Guest[this->capacity];
}
Room::Room(const Room &other)
{
    this->Guests = new Guest[other.capacity];
    if (!this->Guests)
    {
        std::cout << "Problem with memory";
        return;
    }
    for (int i = 0; i < other.size; i++)
    {
        this->Guests[i] = other.Guests[i];
    }
    this->num = other.num;
    this->beds = other.beds;
    this->size = other.size;
    this->capacity = other.capacity;
}
Room::~Room()
{
    delete[] this->Guests;
}
void Room::copy(const Room &other)
{
    this->Guests = new Guest[other.capacity];
    if (!this->Guests)
    {
        std::cout << "Problem with memory";
        return;
    }
    for (int i = 0; i < other.size; i++)
    {
        this->Guests[i] = other.Guests[i];
    }
    this->num = other.num;
    this->beds = other.beds;
    this->size = other.size;
    this->capacity = other.capacity;
}
Room &Room::operator=(const Room &other)
{
    this->~Room();
    this->copy(other);
    return *this;
}
Room &Room::operator+=(const Guest &other)
{
    if (this->size == this->capacity)
    {
        this->resize();
    }
    this->Guests[size++] = other;
    return *this;
}
unsigned int Room::getNum() const
{
    return this->num;
}
unsigned int Room::getBeds() const
{
    return this->beds;
}
int Room::getSize() const
{
    return this->size;
}
Guest *Room::getGuest(int i)
{
    return &this->Guests[i];
}
std::ostream &operator<<(std::ostream &out, const Room &obj)
{
    out << obj.num << '\n' << obj.beds <<'\n'<<obj.size<<'\n';
    for (int i = 0; i < obj.size; i++)
        out << obj.Guests[i];
    return out;
}
// Guest--------------------------------------------------------------
Guest::Guest()
{
    this->name = nullptr;
    this->note = nullptr;
    strcpy(this->entry, "");
    strcpy(this->exit, "");
}
Guest::Guest(const char *name, const char *note, const char entry[9], const char exit[9])
{
    this->name = new char[strlen(name) + 1];
    if (!this->name)
    {
        std::cout << "Problem with memory";
        return;
    }
    strcpy(this->name, name);
    this->note = new char[strlen(note) + 1];
    if (!this->note)
    {
        std::cout << "Problem with memory";
        return;
    }
    strcpy(this->note, note);
    strcpy(this->entry, entry);
    strcpy(this->exit, exit);
}
char *Guest::getEntry()
{
    return this->entry;
}
char *Guest::getExit()
{
    return this->exit;
}
Guest::~Guest()
{
    delete[] this->name;
    delete[] this->note;
}
void Guest::copy(const Guest &other)
{
    this->name = new char[strlen(other.name) + 1];
    strcpy(this->name, other.name);
    this->note = new char[strlen(other.note) + 1];
    strcpy(this->note, other.note);
    strcpy(this->entry, other.entry);
    strcpy(this->exit, other.exit);
}
Guest &Guest::operator=(const Guest &other)
{
    if (this->name != nullptr && this->note != nullptr)
    {
        this->~Guest();
    }
    this->copy(other);
    return *this;
}
std::ostream &operator<<(std::ostream &out, const Guest &obj)
{
    out << obj.name << '\n' << obj.note << '\n' << obj.entry << '\n' << obj.exit << '\n';
    return out;
}
std::istream &operator>>(std::istream &in, Guest &obj)
{
    char namebuffer[100];
    std::cout << "Name: ";
    std::cin.getline(namebuffer,99);
    char notebuffer[100];
    std::cout << "Note: ";
    std::cin.getline(notebuffer,99);
    char entrybuffer[9];
    std::cout << "Entry Date: ";
    std::cin.getline(entrybuffer,9);
    char exitbuffer[100];
    std::cout << "Exit Date: ";
    std::cin.getline(exitbuffer,9);
    Guest a(namebuffer, notebuffer, entrybuffer, exitbuffer);
    obj = a;
    return in;
}
// Hotel------------------------------------------------------------
Hotel::Hotel()
{

    this->capacity = 8;
    this->size = 0;
    this->Rooms = new Room[capacity];
}
void Hotel::resize()
{
    Room *a = new Room[this->capacity * 2];
    if (!a)
    {
        std::cout << "Problem with memory";
        return;
    }
    this->capacity *= 2;
    for (int i = 0; i < this->size; i++)
    {
        a[i] = this->Rooms[i];
    }
    delete[] this->Rooms;
    this->Rooms = a;
}
Hotel::~Hotel()
{
    delete[] this->Rooms;
}
void Hotel::copy(const Hotel &other)
{
    this->Rooms = new Room[other.capacity];
    if (!this->Rooms)
    {
        std::cout << "Problem with memory";
        return;
    }
    for (int i = 0; i < other.size; i++)
    {
        this->Rooms[i] = other.Rooms[i];
    }
    this->capacity = other.capacity;
    this->size = other.size;
}
Hotel &Hotel::operator=(const Hotel &other)
{
    this->~Hotel();
    this->copy(other);
    return *this;
}
Hotel &Hotel::operator+=(const Room &other)
{
    if (this->size == this->capacity)
    {
        this->resize();
    }
    this->Rooms[size++].copy(other);
    return *this;
}
std::ostream &operator<<(std::ostream &out, const Hotel &obj)
{   out<<obj.size<<'\n';
    for (int i = 0; i < obj.size; i++)
    {
        out << obj.Rooms[i];
    }
    return out;
}
int Hotel::findRoom(int num) //намира индекс на стая в масива от нейния номер
{
    for (int i = 0; i < this->size; i++)
    {
        if (this->Rooms[i].getNum() == num)
            return i;
    }
    return -1;
}
void Hotel::addGuest(int roomnum) //добавя гост в стая с даден номер
{
    Guest a;
    std::cin >> a;
    if (this->Rooms[this->findRoom(roomnum)].isFreePeriod(a.getEntry(),a.getExit()))
    {   
        this->Rooms[this->findRoom(roomnum)] += a;
    }
    else
        std::cout << "Room is in use at these dates"<<std::endl;
}
bool Room::isDateBetween(char date[9], char start[9], char end[9]) //проверява дали дата се намира между други две YYYYMMDD
{
    for (int i = 0; i < 8; i++)
    {
        if (date[i] < start[i])
            return false;
        if (date[i] > start[i])
            break;
    }
    for (int i = 0; i < 8; i++)
    {
        if (date[i] > end[i])
            return false;
        if (date[i] < end[i])
            break;
    }
    return true;
}
bool Room::isFree(char date[9]) //проверява дали стая е свободна за определена дата
{
    for (int i = 0; i < this->size; i++)
    {
        if (this->isDateBetween(date, this->Guests[i].getEntry(), this->Guests[i].getExit()))
            return false;
    }
    return true;
}
bool Room::isFreePeriod(char start[9], char end[9]) //проверява дали стая е свободна за определен преиод
{
    for (int i = 0; i < this->size; i++)
    {
        if (this->isDateBetween(this->Guests[i].getEntry(), start, end) || this->isDateBetween(this->Guests[i].getExit(), start, end))
            return false;
    }
    return true;
}
void Hotel::freeRooms(char date[9]) //изкарва номера на стаи, свободни на дадена дата
{
    for (int i = 0; i < this->size; i++)
    {
        if (this->Rooms[i].isFree(date))
            std::cout << this->Rooms[i].getNum() << " ";
    }
    std::cout<<std::endl;
}
void Hotel::clearRoom(int roomnum, char date[9]) //маха гост, посетил на дадена дата
{
    int num = this->findRoom(roomnum);
    this->Rooms[num].clearGuest(date);
}
void Room::clearGuest(char date[9]) //помощна за clearRoom
{
    for (int i = 0; i < this->size; i++)
    {
        if (this->isDateBetween(date, this->Guests[i].getEntry(), this->Guests[i].getExit()))
        {
            this->Guests[i] = this->Guests[--size];
            return;
        }
    }
    std::cout << "No Guest at that time"<<'\n';
}
void Hotel::findFreeRoom(char start[9],char end[9],int beds) //намира празни стай с минимален брой легла
{ int min=100;
    for (int i=0; i<this->size; i++)
{
    if (this->Rooms[i].isFreePeriod(start,end) && this->Rooms[i].getBeds()>=beds)  
    {
         if (this->Rooms[i].getBeds()<min) {min=this->Rooms[i].getBeds();}
    }
}
for (int i=0; i<this->size; i++)
{
    if (this->Rooms[i].isFreePeriod(start,end) && this->Rooms[i].getBeds()==min)  
    {
        std::cout<<this->Rooms[i].getNum()<<" "; 
    }
}
std::cout<<std::endl;
}
void Hotel::closeRoom(int roomnum) //затваря стая за определен период
{ char namebuffer[100];
    std::cout << "Reason: ";
    std::cin.getline(namebuffer,99);
    char notebuffer[100];
    std::cout << "Note: ";
    std::cin.getline(notebuffer,99);
    char entrybuffer[9];
    std::cout << "Starting Date: ";
    std::cin.getline(entrybuffer,9);
    char exitbuffer[100];
    std::cout << "Ending Date: ";
    std::cin.getline(exitbuffer,9);
    Guest a(namebuffer, notebuffer, entrybuffer, exitbuffer);
    if (this->Rooms[this->findRoom(roomnum)].isFreePeriod(a.getEntry(),a.getExit()))
    {   
        this->Rooms[this->findRoom(roomnum)] += a;
    }
    else
        std::cout << "Room is in use at these dates"<<std::endl;
}
void Hotel::isFreeFile() //извежда справка за заетост на всички стай за даден период
{   char start[9],end[9];
    std::cout<<"Starting date: "; std::cin.getline(start,9);
    std::cout<<"Ending date: "; std::cin.getline(end,9);

    std::ofstream file("start.txt"); 
    if (!file.is_open()) 
    {
        std::cout << "Problem while opening the file" << std::endl;
        return;
    }
}
int charToInt(char* array) //преобразува char в int
{ int i=0,num=0;
 while (array[i]!='\0')
{ num=num*10;
    num+=array[i]-48;
    i++;
} return num;
}
int Hotel::getSize() //дава брой стай в хотел
{
    return this->size;
}
void Hotel::Menu() //диалогов режим на работа
{   int num=10;
    do{ std::cout<<"Напишете цифрата пред операцията: "<<'\n';
    std::cout<<"Регистрирай гост: 1 "<<'\n';
    std::cout<<"Свободни стай за дадена дата: 2 "<<'\n';
    std::cout<<"Освобождаване на стая: 3 "<<'\n';
    std::cout<<"Търсене на стая с минимален брой легла: 4 "<<'\n';
    std::cout<<"Затваряне на стая: 5 "<<'\n';
    std::cout<<"Изход: 0"<<'\n';
        std::cout<<">";
        std::cin>>num; std::cin.ignore();
    if (num==1)
    {   int roomnum; std::cout<<"Номер на стая: ";
        std::cin>>roomnum; std::cin.ignore();
        this->addGuest(roomnum);
    }
    if (num==2)
    { char date[9]; std::cout<<"Дата(YYYYMMDD): ";
        std::cin.getline(date,9); 
     this->freeRooms(date);
    }
    if (num==3)
    { int number; char date1[9];
     std::cout<<"Номер на стая: ";
    std::cin>>number;std::cin.ignore(); std::cout<<"Дата: ";
    std::cin.getline(date1,9); 
        clearRoom(number,date1);
    }
    if (num==4)
    { char entry[9],exit[9]; int beds;
    std::cout<<"Брой легла: ";
    std::cin>>beds; std::cin.ignore();
    std::cout<<"Дата на настаняване: ";
    std::cin.getline(entry,9); 
    std::cout<<"Дата на напускане: ";
    std::cin.getline(exit,9);    
    this->findFreeRoom(entry,exit,beds);
    }
    if(num==5)
    { int nomer;
        std::cout<<"Номер на стая: ";
    std::cin>>nomer; std::cin.ignore();
        this->closeRoom(nomer);
    } std::cout<<*this;
    }while(num!=0);
}
int main()
{ 
    Hotel hotel1;
   std::ifstream infile("hotelInfo.txt");
    if (!infile.is_open()) 
    {
        std::cout << "Problem while opening the file" << std::endl;
    }
    char size[100];
    infile.getline(size,100); 
    for (int j=0; j<charToInt(size); j++)
    { char name[100], note[100], entry[9], exit[9],num[10],bed[10],guest[10];
     infile.getline(num,10);
     infile.getline(bed,10);
     infile.getline(guest,10);
     Room newroom(charToInt(num),charToInt(bed));
      for (int i=0; i<charToInt(guest); i++)
     { infile.getline(name, 100);
        infile.getline(note, 100);
        infile.getline(entry, 9);
        infile.getline(exit, 9);
    Guest newguest(name,note,entry,exit);
    newroom+=newguest; 
     }
    hotel1+=newroom; 
    } 
    infile.close(); 
    hotel1.Menu();
    std::ofstream outfile("hotelInfo.txt"); 
    if (!outfile.is_open()) 
    {
        std::cout << "Problem while opening the file" << std::endl;
    }
    outfile<<hotel1;
    outfile.close();
    return 0;
}