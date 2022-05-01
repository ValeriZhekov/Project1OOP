#include <iostream>
#include <fstream>
#include <cstring>
#include "Hotel.h"
// Room--------------------------------------------------------
void Room::resize()
{Guest* a=new Guest[this->capacity*2];
if (!a)
{
    std::cout<<"Problem with memory";
    return;
}
this->capacity*=2;
for (int i=0; i<this->size; i++)
{
    a[i]=this->Guests[i];
}
delete[] this->Guests;
this->Guests=a;
}
Room::Room()
{
    this->num = 0;
    this->beds = 0;
    this->size=0;
    this->capacity=8;
    this->Guests=new Guest[this->capacity];
}
Room::Room(const unsigned int num, const unsigned int beds)
{
    this->num = num;
    this->beds = beds;
    this->size=0;
    this->capacity=8;
    this->Guests=new Guest[this->capacity];
}
Room::Room(const Room& other)
{this->Guests=new Guest[other.capacity];
if (!this->Guests)
{
    std::cout<<"Problem with memory";
    return;
}
for (int i=0; i<other.size; i++)
{
    this->Guests[i]=other.Guests[i];
}
this->num=other.num;
this->beds=other.beds;
this->size=other.size;
this->capacity=other.capacity;
}
Room::~Room()
{  delete[] this->Guests;
}
void Room::copy(const Room& other)
{this->Guests=new Guest[other.capacity];
if (!this->Guests)
{
    std::cout<<"Problem with memory";
    return;
}
for (int i=0; i<other.size; i++)
{
    this->Guests[i]=other.Guests[i];
}
this->num=other.num;
this->beds=other.beds;
this->size=other.size;
this->capacity=other.capacity;
}
Room& Room::operator=(const Room& other)
{    this->~Room();
    this->copy(other);
    return *this;
}
Room& Room::operator +=(const Guest& other)
{ if (this->size==this->capacity)
{
this->resize();
}
this->Guests[size++]=other;
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
Guest* Room::getGuest(int i)
{
    return &this->Guests[i];
}
std::ostream &operator<<(std::ostream &out, const Room &obj)
{
    out <<"Room: "<< obj.num << " " << obj.beds << '\n';
    for (int i=0; i<obj.size; i++)
    out<<obj.Guests[i];
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
char* Guest::getEntry()
{
    return this->entry;
}
char* Guest::getExit()
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
{   if(this->name!=nullptr && this->note!=nullptr)
  { this->~Guest();}
    this->copy(other);
    return *this;
}
std::ostream &operator<<(std::ostream &out, const Guest &obj)
{
    out << obj.name <<" "<<obj.note<<" "<<obj.entry<<" "<<obj.exit<<'\n';
    return out;
}
std::istream& operator >>(std::istream& in,Guest& obj)
{   char namebuffer[100];
    std::cout<<"Name: "; in>>namebuffer;
    char notebuffer[100];
    std::cout<<"Note: "; in>>notebuffer;
    char entrybuffer[9];
    std::cout<<"Entry Date: "; in>>entrybuffer;
    char exitbuffer[100];
    std::cout<<"Exit Date: "; in>>exitbuffer;
    Guest a(namebuffer,notebuffer,entrybuffer,exitbuffer);
    obj=a;
    return in;
}
// Hotel------------------------------------------------------------
Hotel::Hotel()
{
    
    this->capacity=8;
   this->size=0;
   this->Rooms = new Room[capacity];
}
void Hotel::resize()
{Room* a=new Room[this->capacity*2];
if (!a)
{
    std::cout<<"Problem with memory";
    return;
}
this->capacity*=2;
for (int i=0; i<this->size; i++)
{
    a[i]=this->Rooms[i];
}
delete[] this->Rooms;
this->Rooms=a;

}
Hotel::~Hotel()
{
    delete[] this->Rooms;
}
void Hotel::copy(const Hotel &other)
{this->Rooms=new Room[other.capacity];
if(!this->Rooms)
{
    std::cout<<"Problem with memory";
    return;
}
for(int i=0; i<other.size; i++)
{
    this->Rooms[i]=other.Rooms[i];
}
this->capacity=other.capacity;
this->size=other.size;
}
Hotel& Hotel::operator=(const Hotel& other)
{    this->~Hotel();
    this->copy(other);
    return *this;
}
Hotel& Hotel::operator+=(const Room& other)
{
if (this->size==this->capacity)
{
this->resize();
}
this->Rooms[size++].copy(other);
return *this;
}
std::ostream& operator<<(std::ostream& out,const Hotel& obj)
{
    for(int i=0; i<obj.size; i++)
    {
        out<<obj.Rooms[i];
    }
    return out;
}
int Hotel::findRoom(int num) //намира индекс на стая в масива от нейния номер
{ for (int i=0; i<this->size; i++)
{
    if (this->Rooms[i].getNum()==num) 
    return i;
}
return -1;
}
void Hotel::addGuest(int roomnum) //добавя гост в стая с даден номер
{  Guest a;
std::cin>>a;
    this->Rooms[this->findRoom(roomnum)]+=a;
    
}
bool Room::isDateBetween(char date[9],char start[9],char end[9]) //проверява дали дата се намира между други две YYYYMMDD
{
    for (int i=0; i<8; i++)   
  { if (date[i] < start[i])
      return false;
      if(date[i]>start[i])
      break;
  }
    for (int i=0; i<8; i++)   
  { if (date[i] > end[i])
      return false;
      if (date[i] < end[i])
      break;
  }
    return true;
}
bool Room::isFree(char date[9]) //проверява дали стая е свободна за определена дата
{   for (int i=0; i<this->size; i++)
    {
      if(this->isDateBetween(date,this->Guests[i].getEntry(),this->Guests[i].getExit()))
      return false;  
    }
    return true;
}
bool Room::isFreePeriod(char start[9],char end[9]) //проверява дали стая е свободна за определен преиод
{  

}
void Hotel::freeRooms(char date[9]) //изкарва номера на стаи, свободни на дадена дата
{ for (int i=0; i<this->size; i++)
{
    if (this->Rooms[i].isFree(date))  std::cout<<this->Rooms[i].getNum()<<" "; 
}
}
void Hotel::clearRoom(int roomnum,char date[9]) //маха гост, посетил на дадена дата
{ int num=this->findRoom(roomnum);
    this->Rooms[num].clearGuest(date);
}
void Room::clearGuest(char date[9]) //помощна за clearRoom
{ for(int i=0; i<this->size; i++)
{
    if(this->isDateBetween(date,this->Guests[i].getEntry(),this->Guests[i].getExit()))
       {    
           this->Guests[i]=this->Guests[--size];      
           return;
       }
}
std::cout<<"No Guest at that time";
}
int main()
{   Hotel hotel1;
    Room room101(101, 2),room102(102,3),room103(103,2);
    Guest a("aname", "anote", "20021101", "20021106"),b("bname", "bnote", "20021108", "20021109"),c("cname", "cnote", "20021110", "20021115"); 
    room101+=a; room101+=b; room102+=b; room102+=c; room103+=a; room103+=c;
    hotel1+=room101; hotel1+=room102; hotel1+=room103;
 
  hotel1.clearRoom(101,"20021101");
  hotel1.addGuest(101);
   std::cout<<hotel1;
   hotel1.freeRooms("20021117"); 
    return 0;
}