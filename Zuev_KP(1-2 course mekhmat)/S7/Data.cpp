#include "Data.h"

Data::Data()
{
	student.name[64] = '\0';
	student.group = 0;
	student.rating = 0;
	student.info = NULL;
}

Data::Data(Student student_)
{
	student.name[64] = student_.name[64];
	student.group = student_.group;
	student.rating = student_.rating;
	student.info = student_.info;
}

Data::~Data()
{
}

void Data::DataEntry(Student student_)
{
	student.name[64] = student_.name[64];
	student.group = student_.group;
	student.rating = student_.rating;
	student.info = student_.info;
}

Data& Data::operator=(Data d_o)
{	
	this->student.name[64] = d_o.student.name[64];
	this->student.group = d_o.student.group;
	this->student.rating = d_o.student.rating;
	this->student.info = d_o.student.info;

	return *this;
}





void DataEntry(Data* (&d), int& n)
{
	Student student;

	cout << "Введите размер массива: ";
	cin >> n;

	d = new Data[n];

	for (int i = 0; i < n; i++)
	{
		cout << "Введите: ";
		cin >> student.name[64] >> student.group >> student.rating >> student.info;

		d[i].DataEntry(student);
		cout << "_\n";
	}
}

void DataReading(Data* (&d), int& n, string fileName)
{
	ifstream reading(fileName);
	if(reading)
	{
		Student student;

		reading >> n;

		d = new Data[n];

		for(int i = 0; i < n; i++)
		{
			reading >> student.name[64] >> student.group >> student.rating >> student.info;

			d[i].DataEntry(student);
		}
		cout << "Данные считаны!" << endl;
	}
	else
		cout << "Ошибка открытия файла!" << endl;
	reading.close();
}

void Copy(Data * d_n, Data * d_o, int n)
{
	for(int i = 0; i < n; i ++)
	{
		d_n[i] = d_o[i];
	}
}
void AddData(Data * (&d), int& n)
{
	Student student;
	Data* buf = new Data[n];
	int size = n, new_size = ++n;

	Copy(buf, d, size);

	d = new Data[new_size];

	Copy(d, buf, size);

	cout << "Введите новое: ";
	cin >> student.name[64] >> student.group >> student.rating >> student.info;

	d[size].DataEntry(student);

	cout << "Данные добавлены!" << endl;

	delete[] buf;
}

void DeleteData(Data* (&d), int& n)
{
	int _n;
	Data* buf = new Data[n];

	cout << "Введите номер нужного элемента: ";
	cin >> _n;
	_n--;
	if (_n >= 0 && _n < n)
	{
		Copy(buf, d, n);
		int q = 0;
		n--;

		d = new Data[n];

		for(int i = 0; i <= n; i++)
		{
			if(i != _n)
			{
				d[q] = buf[i];
				q++;
			}
		}
		cout << "Данные удалены!" << endl;
	}
	else
		cout << "Номер введен не верно!" << endl;

	delete[]buf;
}

void SaveData(Data* d, int n, string fileName)
{
	ofstream record(fileName);
	if(record)
	{
		record << n << endl;

		for(int i = 0; i < n; i ++)
		{
			record << d[i].GetStudent().name[64] << " " << d[i].GetStudent().group << " " << d[i].GetStudent().rating << " " << d[i].GetStudent().info << endl;
			if(i < n-1)
				record << endl;
		}
	}
	else
		cout << "Ошбика открытия файла!" << endl;

	cout << "Данные сохранены в файл: " << fileName << endl;

	record.close();
}

main()
{
}
