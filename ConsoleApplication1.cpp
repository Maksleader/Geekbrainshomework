#include <iostream>
#include <string>
#include <fstream>
#include <optional>
#include <functional>
#include <tuple>
#include <map>
#include <vector>



using namespace std;
struct Person
{
	string name;
	string surname;
	optional<string> patronymic;


};



bool operator == (struct Person& p1, struct Person& p2)
{
	return tie(p1.name, p1.surname, p1.patronymic) == tie(p2.name, p2.surname, p2.patronymic);
}
bool operator < (struct Person& p1, struct Person& p2)
{
	return tie(p1.name, p1.surname, p1.patronymic) < tie(p2.name, p2.surname, p2.patronymic);
};



std::ostream& operator<< (std::ostream& s, const Person& p1)
{
	if (p1.patronymic == nullopt)
	{
		return s << p1.name << " " << p1.surname << "  ";

	}
	else
	{
		return s << p1.name << " " << p1.surname << " " << p1.patronymic.value() << "   ";
	}

};


struct PhoneNumber
{
	int country_code{};
	int city_code{};
	string number;
	optional<int> additional_number;
};

std::ostream& operator<< (std::ostream& out, const PhoneNumber& p1)
{
	if (p1.additional_number == nullopt)
	{
		return out << "+" << "(" << p1.country_code << ")" << p1.city_code << p1.number << endl;

	}
	else
	{

		return out << "+" << p1.country_code << "(" << p1.city_code << ")" << p1.number << " " << p1.additional_number.value() << endl;
	}
};

class Phonebook
{
public:
	pair<Person, PhoneNumber>myphonebook;

public:
	Phonebook(ifstream& file)
	{

		Person person;
		PhoneNumber number;

		if (file.is_open())
		{
			file >> person.name >> person.surname >> person.patronymic.value();
			file >> number.country_code >> number.city_code >> number.number >> number.additional_number.value();

			file.close();
		}

	}

};
ostream& operator<< (ostream& print, Phonebook& phonebook)
{
	return print << phonebook.myphonebook.first << "  " << phonebook.myphonebook.second;


}





int main()
{

	ifstream file("Input.txt");
	Phonebook book(file);
	cout << book;



}


