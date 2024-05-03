#include <iostream>
using namespace std;
class date {
public:
	friend ostream& operator<<(ostream& out, const date& d);
	friend istream& operator>>(istream& in,  date& d);
	int getmonth(int year, int month)const{
		int arr[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
		if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)) {
			return 29;
		}
		return arr[month];
	}
	date(int year = 0, int month = 1,int day = 1)
		:_year(year)
		,_month(month)
		,_day(day)
	{
		/*if (year >= 0 && month >= 1 && month <= 12 && day <= getmonth(year, month)) {
			_year = year;
			_month = month;
			_day = day;
		}
		else {
			cout << "日期输入非法" << endl;
		}*/
	}
	date(const date& d) {
		_year = d._year;
		_month = d._month;
		_day = d._day;
	}
	bool operator==(const date& d)const {
		return (_year == d._year) &&( _month == d._month )&&( _day == d._day);
	}
	bool operator<(const date& d)const {
		if (_year < d._year)
			return true;
		else if (_year == d._year && _month < d._month)
			return true;
		else if (_year == d._year && _month == d._month && _day < d._day)
			return true;
		else
			return false;
	}
	bool operator<=(const date& d)const {
		return *this < d || *this == d;
	}
	bool operator>(const date& d)const {
		return !(*this <= d);
	}
	bool operator>=(const date& d)const {
		return !(*this < d);
	}
	date operator+(int day)const {
		date d(*this);
		d += day;
		return d;
	}
	date& operator+=(int day) {
		if (day < 0) {
			return *this -= -day;
		}
		_day += day;
		while (_day > getmonth(_year,_month)) {
			_day -= getmonth(_year,_month);
			_month += 1;
			if (_month == 13) {
				_month = 1;
				_year++;
			}
		}
		return (*this);
	}
	date operator-(int day)const {
		date d(*this);
		d -= day;

		return d;
	}
	date& operator-=(int day) {
		if (day < 0) {
			return *this += -day;
		}
		_day -= day;
		while (_day <= 0) {
			_month--;
			if (_month == 0) {
				_year--;
				_month = 12;
			}
			_day += getmonth(_year, _month);
		}
		return *this;
	}
	date& operator=(const date& d) {
		if (this != &d) {
			_year = d._year;
			_month = d._month;
			_day = d._day;
		}
		return (*this);
	}
	date& operator++() {
		*this += 1;
		return *this;
	}
	date operator++(int) {
		date d(*this);
		*this += 1;
		return d;
	}
	date& operator--() {
		*this -= 1;
		return *this;
	}
	date operator--(int) {
		date d(*this);
		*this -= 1;
		return d;
	}
	int operator-(const date& d)const {
		date max = *this;
		date min = d;
		int flag = 1;
		if (*this < d) {
			max = d;
			min = *this;
			flag = -1;
		}
		int cnt = 0;
		while (min < max) {
			cnt++;
			min++;
		}
		return cnt * flag;
	}
	void print()const {
		cout << _year << '-' << _month << '-' << _day << endl;
	}
private:
	int _year;
	int _month;
	int _day;
};
ostream& operator<<(ostream& out, const date& d) {
	out << d._year << ' ' << d._month << ' ' << d._day << endl;
	return out;
}
istream& operator>>(istream& in,  date& d) {
	in >> d._year >> d._month >> d._day;
	return in;
}
class test {
public:
	test()
	{
		_i++;
	}
	static int sum(){
		return _i;
	}
private:
	static int _i;
};
int test::_i = 0;
int main() {
	date d1(2020, 4, 11);
	date d2(2020, 4, 10);
	cin >> d1>>d2;
	cout << d1;
	//test a[10];
	//cout << test::sum() << endl;

	
//hellowakka


	return 0;
}
