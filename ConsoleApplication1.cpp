#include <iostream>
#include <string>
#include <fstream>
#include <optional>
#include <vector>
#include <sstream>
#include <iomanip>
#include <algorithm> 
#include <tuple>
#include <stdexcept>
#include<functional>





using namespace std;

struct Person
{
	string surname;
	string name;
	string a;
	optional<string> patronymic;

};



bool operator == (const struct Person& p1, const  Person& p2)
{
	return tie(p1.surname, p1.name, p1.a) == tie(p2.surname, p2.name, p2.a);
}
bool operator < (struct Person& p1, struct Person& p2)
{
	return tie(p1.surname, p1.name, p1.a) < tie(p2.surname, p2.name, p2.a);
};

istream& operator>> (istream& is, Person& p1)
{


	is >> p1.surname >> p1.name >> p1.a;
	p1.patronymic = p1.a;

	return is;


};

std::ostream& operator<< (std::ostream& s, Person& p1)
{

	if (p1.patronymic && p1.patronymic == "-")
	{

		s << right << setw(11) << p1.surname << "        " << right << setw(11) << p1.name << "                      ";
	}
	else
	{

		s << right << setw(11) << p1.surname << "        " << right << setw(11) << p1.name << "        " << right << setw(14) << p1.patronymic.value();

	}

	return s;
};


struct PhoneNumber
{
	int country_code{};
	int city_code{};
	string number;
	int b{};
	optional<int>additional_number;



};


bool operator == (struct PhoneNumber& p1, struct PhoneNumber& p2)
{
	return tie(p1.country_code, p1.city_code, p1.b) == tie(p2.country_code, p2.city_code, p2.b);
}
bool operator < (struct PhoneNumber& p1, struct PhoneNumber& p2)
{
	return  tie(p1.country_code, p1.city_code,p1.number, p1.b) < tie(p2.country_code, p2.city_code,p2.number, p2.b);
}



istream& operator>> (istream& is,  PhoneNumber& p1)
{

	is >> p1.country_code >> p1.city_code >> p1.number >> p1.b;
	p1.additional_number = p1.b;
	return is;
};


std::ostream& operator<< (std::ostream& out, PhoneNumber& p1)
{
	if (p1.additional_number && p1.additional_number == 0)
	{
		out << "+" << p1.country_code << "(" << p1.city_code << ")" << p1.number << " ";
	}
	else
	{
		out << "+" << p1.country_code << "(" << p1.city_code << ")" << p1.number << " " << p1.additional_number.value();
	}
	return out;
};
bool Compare(pair<Person, PhoneNumber> phonebook1, pair<Person, PhoneNumber> phonebook2)
{
	return phonebook1.first < phonebook2.first;
};
bool Compare1(pair<Person, PhoneNumber> phonebook1, pair<Person, PhoneNumber> phonebook2)
{
	return phonebook1.second < phonebook2.second;
};


bool operator == (pair<Person, PhoneNumber> phonebook1, Person &a)
{
	return phonebook1.first == a;
}


class Phonebook
{
public:
	vector<pair<Person, PhoneNumber>>phonebook;

public:

	Phonebook(ifstream& file)
	{

		Person person;
		PhoneNumber number;
		string line;

		

		if (file.is_open())
		{

			while (!file.eof())
			{

				//file >> person >> number;
				getline(file, line);
				stringstream geek(line);

				geek >>person>> number;

				phonebook.push_back(make_pair(person, number));
			}

				file.close();
			
		};
		
		
	};
	
	void SortByName()
	{
		sort(phonebook.begin(), phonebook.end(), Compare);
	
	}

	void SortByPhone()
	{
		sort(phonebook.begin(), phonebook.end(), Compare1);

	}


	
	
	pair<string,PhoneNumber> GetPhoneNumber(string surname)
	{
		
		int  flag=0;
		PhoneNumber number;
		
	

		for_each(phonebook.begin(), phonebook.end(), [surname, &number,&flag](const  pair<Person, PhoneNumber>& vec) 
		{
				
				if(vec.first.surname==surname)
				{ 
					number = vec.second;
					++flag;
				}
				
		});
		
		if (flag==1)
		{
			return { "",number };
		}
		else if (flag > 1)
		{
			return { "found more than 1",number };
		}
		else
		{
			return { "not found",number };
		}
		
		 
	};


	
	void ChangePhoneNumber(Person a, PhoneNumber b)
	{




		vector<pair<Person, PhoneNumber>>::iterator itr = find_if(phonebook.begin(), phonebook.end(), [a, b](const pair< Person, PhoneNumber>& vec)
		{
				return vec.first == a;

		});

		if (itr != phonebook.end())
		{
			itr->second = b;
			
		}
		else
			{ }

		


	}



};


ostream& operator<< (ostream& print, Phonebook& vec)
{
	for ( auto&[Person,PhoneNumber]:vec.phonebook )
	{
		print<< Person << right << setw(12) <<PhoneNumber << endl;
	};


	return print;
}





int main()
{

	ifstream file("Input.txt");
	Phonebook book(file);
	cout << book;
	cout << "------SortByPhone-------" << endl;
	book.SortByPhone();
	cout << book;
	cout << "------SortByName--------" << endl;
	book.SortByName();
	cout << book;
	cout << "-----GetPhoneNumber-----" << endl;
	auto print_phone_number = [&book](const string&surname)
	{
		cout << surname << "\t";
		auto answer = book.GetPhoneNumber(surname);
		if (get<0>(answer).empty())
			cout << get<1>(answer);
		else
			cout << get<0>(answer);
		cout << endl;
	};

	print_phone_number("Solovev");

	print_phone_number("Petrov");

	cout << "----ChangePhoneNumber----" << endl;
	book.ChangePhoneNumber(Person{ "Kotov", "Vasilii", "Eliseevich" },
		PhoneNumber{ 7, 123, "15344458", 0 });
	book.ChangePhoneNumber(Person{ "Mironova", "Margarita", "Vladimirovna" },
		PhoneNumber{ 16, 465, "9155448", 13 });
	cout << book;

	
}



