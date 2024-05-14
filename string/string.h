#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
using namespace std;
namespace A {
class string {
public:
	//迭代器
	typedef char* iterator;
	iterator begin() {
		return _str;
	}
	iterator end() {
		return _str + _size;
	}
	//构造函数
	string(const char*str="")
	{	
		_size = strlen(str);
		_capacity = _size;
		_str = new char[_capacity + 1];//构造函数
		strcpy(_str, str);
	}
	//拷贝构造函数传统写法
	//string(string& str) 
	//	
	//{
	//	_size = strlen(str._str);
	//	_capacity = _size;
	//	_str = new char[_capacity + 1];
	//	strcpy(_str, str._str);
	//}
	//拷贝构造现代写法
	void swap(string& s) {
		::swap(_str,s._str);//表示调用全局作用域的swap函数
		::swap(_capacity, s._capacity);
		::swap(_size, s._size);
	}
	string(const string& str)
		:_str(nullptr)
	{
		string tmp(str._str);
		this->swap(tmp);
	}
	//赋值操作符重载传统写法
	//string& operator=(string& str) 
	//{
	//	if (&str != this) {
	//		char*ptr = new char[strlen(str._str) + 1];
	//		strcpy(ptr, str._str);
	//		delete[]_str;	//记得释放旧空间
	//		_str = ptr;
	//		_size = str._size;
	//		_capacity = str._capacity;
	//	}
	//	return *this;
	//}
	//赋值操作符重载现代写法1
	//string& operator=(string& str)
	//{
	//	if (&str != this) {
	//		string s(str);
	//		swap(_str, s._str);
	//	}
	//	return *this;
	//}
	//赋值操作符重载现代写法2(最简便)
	string& operator=(string s)
	{
		this->swap(s);
		return *this;
	}
	void reserve(size_t n) {
		char* tmp = new char[n + 1];
		strcpy(tmp, _str);
		_capacity = n;
		delete[]_str;
		_str = tmp;
	}
	void resize(size_t n, char c='\0') {
		if (_size >= n) {
			_size = n;
			_str[_size] = '\0';
		}
		else {
			if (n > _capacity) {
				reserve(n);
			}
			for (size_t i = _size; i < n; i++) {
				_str[i] = c;
			}
			_str[n] = '\0';
			_size = n;
		}
	}
	void earse(size_t pos, size_t n = npos) {
		if (n >= _size - pos) {
			_size = pos;
			_str[_size] = '\0';
		}
		else {
			for (size_t i = pos; i <=_size-n ;i++) {
				_str[i] = _str[i + n];
			}
			_size = _size - n;
		}
	}
	size_t find(char ch, size_t pos = 0) {
		for (size_t i = pos; i < _size; i++) {
			if (_str[i] == ch) {
				return i;
			}
		}
		return npos;
	}
	size_t find(const char* str, size_t pos = 0) {
		char* p = strstr(_str, str);
		if (p != nullptr) {
			return p - _str;
		}
		return npos;
	}
	bool operator<(const string& s) {
		int n = strcmp(_str, s._str);
		return n < 0;
	}
	bool operator==(const string& s) {
		int n = strcmp(_str, s._str);
		return n == 0;
	}
	bool operator<=(const string& s) {
		return *this < s || *this == s;
	}
	bool operator>(const string& s) {
		return !(*this<=s);
	}
	bool operator>=(const string& s) {
		return !(*this < s);
	}




	//析构函数
	~string(){
		delete[]_str;
		_capacity = _size = 0;
		_str = nullptr;
	}
	void push_back(char ch) {
		if (_size == _capacity) {
			size_t newcapacity = _capacity == 0 ? 2 : _capacity * 2;
			reserve(newcapacity);
		}
		_str[_size] = ch;
		_size++;
		_str[_size] = '\0';//注意末尾\0
	}
	void append(const char*str) {
		size_t len = strlen(str);
		if (_size + len > _capacity) {
			reserve(_size + len);
		}
		strcpy(_str + _size, str);
		_size += len;
	}
	size_t size() const{
		return strlen(_str);
	}
	char& operator[](size_t i)const {
		return _str[i];
	}
	char* c_str()const {
		return _str;
	}
	string& operator+=(char ch) {
		push_back(ch);
		return  *this;
	}
	string& operator+=(const char* str) {
		append(str);
		return *this;
	}
	void insert(size_t pos, char ch) {
		if (_size == _capacity) {
			size_t newcapacity = _capacity == 0 ? 2 : _capacity * 2;
			reserve(newcapacity);
		}
		for (size_t i = _size; i >= pos; i--) {
			_str[i + 1] = _str[i];
		}
		_str[pos] = ch;
		_size++;
	}
	void insert(int  pos, const char* str) {
		size_t len = strlen(str);
		if (_size + len > _capacity) {
			reserve(_size + len);
		}
		for (int i = _size; i >= pos; i--) {
			_str[i + len] = _str[i];
		}
		strncpy(_str + pos, str, len);
		_size += len;
	}
private:
	char* _str;
	size_t _size;//已有多少个有效字符
	size_t _capacity;//能存多少个有效字符 \0不是有效字符
	static size_t npos;
};
size_t string::npos = -1;
ostream& operator<<(ostream& out,const string& s) {
	for (int i = 0; i < s.size(); i++) {
		cout << s[i];
	}
	return out;
}
istream& operator>>(istream& in, string& s) {
	while (1) {
		char ch;
		ch = in.get();
		if (ch == ' ' || ch == '\n') {
			break;
		}
		s += ch;
	}
	return in;
}
void test() {
	string s("aklaa");
	string s1(s);
	string s2;
	s2 = s1;
	cout << s1 << endl << s2;
}

}