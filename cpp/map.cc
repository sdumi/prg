#include <iostream>
#include <map>
#include <utility>
using namespace std;
void adauga();
void sterge(int index);
void print();

typedef struct
{
	int a;
	char b;
	int c[10];
} ioana;

typedef std::map<int, ioana> ioanaMap;

ioana ioanaStruct;
ioanaMap im;

int main()
{

	int opt;
	int cheie;

	do 
	{
		cout << "optiunea: ";
		cin >> opt;
		if (opt == 1)
		{
			adauga();
			cout << "ADAUGA: harta dupa adaugare este: " << endl;
			print();
		}
		if (opt == 2)
		{
			cout << "cheia: ";
			cin >> cheie;
			sterge(cheie);
			cout << "STERGE: harta dupa stergere cheie " << cheie << "este: " << endl;
			print();
		}
		if (opt == 3)
			print();
	}
	while (opt == 0);
	return 0;
}

void adauga()
{
	int nrElem;
	cout << "a = ";
	cin >> ioanaStruct.a;
	cout << "b = ";
	cin >> ioanaStruct.b;
	cout << "cate elemente are sirul? ";
	cin >> nrElem;
	for (int i = 0; i < nrElem; i++)
	{
		cout << "elem = ";
		cin >> ioanaStruct.c[i];
		
	}
	im.insert ( make_pair (ioanaStruct.a, ioanaStruct) );//    (ioanaStruct.a, ioanaStruct);
	return;
}

void sterge(const int& index)
{
	ioanaMap::iterator iter = im.find(index);
	im.erase(iter);
}

void print()
{
	cout << ioanaStruct.a << "; " << ioanaStruct.b << "; ";
	//	for ()
}
