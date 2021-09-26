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
	string patronymic;
	optional<string> create(bool patronymic)
	{
		return patronymic ? optional<string>{""} : nullopt;
	}


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

	return s << p1.name << " " << p1.surname << " " << p1.patronymic;


};


struct PhoneNumber
{
	int country_code{};
	int city_code{};
	string number;
	int additional_number{};
	optional<int> creat(bool additional_number)
	{
		return additional_number ? optional<int>{} : nullopt;
	}
};

std::ostream& operator<< (std::ostream& out,  PhoneNumber& p1)
{



	return out << "+" << p1.country_code << "(" << p1.city_code << ")" << p1.number << " " << p1.additional_number;

};

class Phonebook
{
public:
	vector<pair<Person, PhoneNumber>>myphonebook;

public:
	Phonebook(ifstream& file)
	{

		Person person;
		PhoneNumber number;
		
		
		

		if (file.is_open())
		{
			
			while (!file.eof())
			{
				file >> person.name >> person.surname >> person.patronymic>> number.country_code >>number.city_code>>number.number>>number.additional_number;
				
				
					myphonebook.push_back(make_pair(person, number));
			}
			
			file.close();
			
		}
		
	}

};
ostream& operator<< (ostream& print, Phonebook& phonebook)
{
	
	for (auto i = 0; i < phonebook.myphonebook.size(); i++)
	{
		print << phonebook.myphonebook[i].first<< phonebook.myphonebook[i].second;
	}
	return print;
}






int main()
{

	ifstream file("Input.txt");
	Phonebook book(file);
	cout << book;



}

