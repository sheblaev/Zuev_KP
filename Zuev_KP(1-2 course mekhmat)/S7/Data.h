#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct Student
{
	char name[64];
	int group;
	double rating;
	char * info;	    
};

class Data
{

	private:
		Student student;
	public:
		Data();
		Data(Student student_);
		~Data();

		void Print();
		void DataEntry(Student student_);

		Student GetStudent() { return student; };

		Data& operator = (Data d_o);
};

void DataEntry(Data* (&d), int& n);
void DataReading(Data* (&d), int& n, string fileName);
void Copy(Data *d_n, Data *d_o, int n);
void AddData(Data* (&d), int& n);
void DeleteDate(Data* (&d), int& n);
void SaveData(Data* d, int n, string fileName);

