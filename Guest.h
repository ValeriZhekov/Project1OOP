class Guest
{private:
char* name;
char* note;
char entry[9]; //YYYYMMDD
char exit[9];   //YYYYMMDD
public:
Guest();
Guest(const char* name, const char* note,const char entry[9], const char exit[9]);
~Guest();
char* getEntry();
char* getExit();
void copy(const Guest& other);
Guest& operator =(const Guest& other);
friend std::ostream& operator <<(std::ostream& out,const Guest& obj);
friend std::istream& operator >>(std::istream& in,Guest& obj);
};