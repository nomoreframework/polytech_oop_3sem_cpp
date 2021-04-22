#include <iostream>
#include <string>
#include <vector>
using namespace std;
using  std::cout;
using  std::cin;

struct book  
{	
public:
	const unsigned int year_now = 2021;
	book(string n, unsigned int y_of_p, unsigned int n_of_p)
	{
		name = n;
		if (y_of_p > year_now) throw "Error! Uncorrect year";
		else year_of_publishing = y_of_p;
		if (n_of_p < 1) throw "Error! Uncorrect number of pages";
		else number_of_pages = n_of_p;
	}
	string get_name() { return name; }
	int get_year_of_publishing() { return year_of_publishing; }
	unsigned get_number_of_pages() { return number_of_pages; }
	string get_book_info()
	{
		return name + "\n" +
			(year_of_publishing < 0 ?
				to_string(year_of_publishing) + " year BC" :
				to_string(year_of_publishing) + " year") + "\n" +
			to_string(number_of_pages);
	}
	~book() {}
private:	
	string name;
	int year_of_publishing;
	unsigned int number_of_pages;
};
class author
{
public:
	author(string name, string surname, int year_of_birth, int year_of_death = 0) 
	{
		this->name = name;
		this->surname = surname;
		this->year_of_birth = year_of_birth;
		if (year_of_death != 0) this->year_of_death = year_of_death;
	}
	vector<book> books;
	virtual string get_name() { return name; }
	virtual string get_surname() { return surname; }
	virtual string get_full_name() { return name + surname; }
	virtual int get_year_of_birth() { return year_of_birth; }
	virtual int get_year_of_death() { return year_of_death; }
	virtual string get_info()
	{
		string result = "";
		return get_full_name() + "\n"
			+ to_string(year_of_birth)
			+ (year_of_death != 0 ? " - " + to_string(year_of_death) : "") + "\n"
			+ get_info_books();
	}
	~author(){}
protected:
	string name;
	string surname;
	int year_of_birth;
	int year_of_death;
private:
	vector<book>::iterator book_iterator;
	string get_info_books()
	{
		string result = "";
		book_iterator = books.begin();
		while (book_iterator != books.end())
		{
			result += book_iterator->get_book_info();
			++book_iterator;
		}
		return result;
	}
};
class console_manager
{
public:
	console_manager(){}
	~console_manager(){}
    static string AUTHOR_TITLE;
	static string BOOK_TITLE;
	static void print(string mes)
	{
		cout << "-------------------------------" << endl;
		cout << console_manager::AUTHOR_TITLE << endl;
		cout << mes << endl;
		cout << console_manager::BOOK_TITLE << endl;
		cout << "-------------------------------" << endl;
	}
};
class worker
{
public:
	worker(){}
	~worker(){}
	vector<author> sort_author_by_age(vector<author> authors)
	{
		return authors;
	}
};
string console_manager::AUTHOR_TITLE = "   Athor";
string console_manager::BOOK_TITLE = "   Books";
int main()
{
	return 0;
}
