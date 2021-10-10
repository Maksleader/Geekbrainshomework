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
	string patronymic;
	optional<string> creat(string& patronymic)
	{
		if (patronymic == "-")
			return " ";
		return{};
	}

};



bool operator == (const struct Person& p1, const  Person& p2)
{
	return tie(p1.surname, p1.name, p1.patronymic) == tie(p2.surname, p2.name, p2.patronymic);
}
bool operator < (struct Person& p1, struct Person& p2)
{
	return tie(p1.surname, p1.name, p1.patronymic) < tie(p2.surname, p2.name, p2.patronymic);
};

istream& operator>> (istream& is, Person& p1)
{


	is >> p1.surname >> p1.name >> p1.patronymic;


	return is;


};

std::ostream& operator<< (std::ostream& s, Person& p1)
{

	s << right << setw(12) << p1.surname << "        " << right << setw(12) << p1.name << "                   " << setw(14) << p1.creat(p1.patronymic).value_or(p1.patronymic);



	return s;
};


struct PhoneNumber
{
	int country_code{};
	int city_code{};
	string number;
	int additional_number{};





};


bool operator == (struct PhoneNumber& p1, struct PhoneNumber& p2)
{
	return tie(p1.country_code, p1.city_code, p1.additional_number) == tie(p2.country_code, p2.city_code, p2.additional_number);
}
bool operator < (struct PhoneNumber& p1, struct PhoneNumber& p2)
{
	return  tie(p1.country_code, p1.city_code, p1.number, p1.additional_number) < tie(p2.country_code, p2.city_code, p2.number, p2.additional_number);
}



istream& operator>> (istream& is, PhoneNumber& p1)
{

	return is >> p1.country_code >> p1.city_code >> p1.number >> p1.additional_number;


};


std::ostream& operator<< (std::ostream& out, PhoneNumber& p1)
{

	if (p1.additional_number == 0)
		return out << "+" << p1.country_code << "(" << p1.city_code << ")" << p1.number << " ";

	else
	{
		return out << "+" << p1.country_code << "(" << p1.city_code << ")" << p1.number << " " << p1.additional_number;
	}


};
bool Compare_Person(pair<Person, PhoneNumber> phonebook1, pair<Person, PhoneNumber> phonebook2)
{
	return phonebook1.first < phonebook2.first;
};
bool Compare_PhoneNumber(pair<Person, PhoneNumber> phonebook1, pair<Person, PhoneNumber> phonebook2)
{
	return phonebook1.second < phonebook2.second;
};



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

			while (getline(file, line))
			{

				stringstream b_convert_int_to_string(line);
				b_convert_int_to_string >> person >> number;

				phonebook.push_back(make_pair(person, number));
			}

			file.close();


		}
		else
		{
			cout << "ERROR";
		}

		

	};

	void SortByName()
	{
		sort(phonebook.begin(), phonebook.end(), Compare_Person);

	}

	void SortByPhone()
	{
		sort(phonebook.begin(), phonebook.end(), Compare_PhoneNumber);

	}




	pair<string, PhoneNumber> GetPhoneNumber(string surname)
	{

		int  flag_for_counting_repetitive_surname = 0;
		PhoneNumber number;



		for_each(phonebook.begin(), phonebook.end(), [surname, &number, &flag_for_counting_repetitive_surname](const  pair<Person, PhoneNumber>& vec)
			{

				if (vec.first.surname == surname)
				{
					number = vec.second;
					++flag_for_counting_repetitive_surname;
				}

			});

		if (flag_for_counting_repetitive_surname == 1)
		{
			return { "",number };
		}
		else if (flag_for_counting_repetitive_surname > 1)
		{
			return { "found more than 1",number };
		}
		else
		{
			return { "not found",number };
		}


	};



	void ChangePhoneNumber(Person a_varaible_of_struct_Person, PhoneNumber b_varaible_of_struct_PhoneNumber)
	{




		vector<pair<Person, PhoneNumber>>::iterator itr_for_replace_PhoneNumber = find_if(phonebook.begin(), phonebook.end(), [a_varaible_of_struct_Person](const pair< Person, PhoneNumber>& vec)
			{
				return vec.first == a_varaible_of_struct_Person;

			});

		if (itr_for_replace_PhoneNumber != phonebook.end())
		{
			itr_for_replace_PhoneNumber->second = b_varaible_of_struct_PhoneNumber;

		}
		else {}





	}



};


ostream& operator<< (ostream& print, Phonebook& vec)
{
	for (auto& [Person, PhoneNumber] : vec.phonebook)
	{
		print << Person << right << setw(12) << PhoneNumber << endl;
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
	auto print_phone_number = [&book](const string& surname)
	{
		cout << surname << "\t";
		auto answer = book.GetPhoneNumber(surname);
		if (get<0>(answer).empty())
			cout << get<1>(answer);
		else
			cout << get<0>(answer);
		cout << endl;
	};

	print_phone_number("Ivanov");

	print_phone_number("Petrov");

	cout << "----ChangePhoneNumber----" << endl;
	book.ChangePhoneNumber(Person{ "Kotov", "Vasilii", "Eliseevich" },
		PhoneNumber{ 7, 123, "15344458", 0 });
	book.ChangePhoneNumber(Person{ "Mironova", "Margarita", "Vladimirovna" },
		PhoneNumber{ 16, 465, "9155448", 13 });
	cout << book;


}








