#pragma once
#include <iostream>
#include <cassert> 
#include <string>
using namespace std;

namespace A {

template <class T>
class vector {
public:
	typedef T* iterator;
	typedef const T* const_iterator;
	vector() {
		_start = _finish = _endofstorage = nullptr;
	}
	~vector() {
		delete[]_start;
		_start = _finish = _endofstorage = nullptr;
	}
	vector(const vector<T>& v) {
		_start = new T[v.capacity()];
		for (size_t i = 0; i < v.size(); i++) {
			_start[i] = v[i];
		}
		_finish = _start + v.size();
		_endofstorage = _start + v.capacity();
	}
	//vector<T>& operator=(const vector<T>& v) {
	//	if (*this != &v) {
	//		delete[]_start;
	//		_start = new T[v.capacity()];
	//		memcpy(_start, v._start, sizeof(T) * v.size());
	//		_finish = _start + v.size();
	//		_endofstorage = _start + v.capacity;
	//	}
	//	return *this;
	//}
	vector<T>& operator=(vector <T> v) {
		swap(v);
		return *this;
	}

	void swap(vector<T>& v) {
		::swap(_start, v._start);
		::swap(_finish, v._finish);
		::swap(_endofstorage, v._endofstorage);
	}

	iterator begin() {
		return _start;
	}
	const_iterator begin()const {
		return _start;
	}
	iterator end() {
		return _finish;
	}
	const_iterator end()const {
		return _finish;
	}
	T& operator[](size_t i) {
		return _start[i];
	}
	const T& operator[](size_t i)const {
		return _start[i];
	}
	void reserve(size_t n) {
		T* tmp = new T[n];
		int Size = size();
		if (_start) {//如果vector里存string 需要深拷贝，用memcpy是浅拷贝
			//memcpy(tmp, _start, sizeof(T) * Size);
			//delete[]_start;
			for (size_t i = 0; i < Size; i++) {
				tmp[i] = _start[i];
			}
			delete[]_start;

		}
		_start = tmp;
		_finish = _start + Size ;
		_endofstorage=_start+n;
	}

	void resize(size_t n, const T& val = T()) {
		if (n <= size()) {
			_finish = _start + n;
		}
		else {
			if(n>capacity())
			reserve(n);
			while (_finish < _start + n) {
				*_finish = val;
				++_finish;
			}
		}
	}
	void push_back(const T& x) {
		if (_finish == _endofstorage) {
			int newcapacity = capacity() == 0 ? 2 : capacity() * 2;
			reserve(newcapacity);
		}
		*_finish = x;
		_finish++;
	}
	void pop_back() {
		assert(_start < _finish);
		_finish--;
	}
	void insert(iterator pos, const T& x) {
		if (_finish == _endofstorage) {
			size_t n = pos - _start;
			int newcapacity = capacity() == 0 ? 2 : capacity() * 2;
			reserve(newcapacity);//如果增容了原来的pos就失效了
			pos = _start + n;
		}
		iterator end = _finish - 1;
		while (end >= pos) {
			*(end + 1) = *end;
			--end;
		}
		*pos = x;
		++_finish;
	}
	iterator erase(iterator pos) {
		iterator it = pos;
		while (it<_finish) {
			*it = *(it + 1);
			it++;
		}
		--_finish;
		return pos;
	}
	int size()const{
		return _finish - _start;
	}
	int capacity()const {
		return _endofstorage - _start;
	}



private:
	iterator _start;
	iterator _finish;//指向最后一个位置的下一个位置
	iterator _endofstorage;
};
void print(const vector<string>& v) {
	vector<string>::const_iterator it= v.begin();
	while (it != v.end()) {
		cout << *it << " ";
		++it;
	}
  }
void test() {
	vector<string>v;
	v.push_back("aaaa");
	v.push_back("bbbb");
	v.push_back("cccc");
	v.push_back("dddd");
	v.push_back("eeee");
	vector<string> v1(v);
	//v.push_back("llll");
	vector <string> v2;
	v2 = v;
	print(v1);

}

}