#include <iostream>
using namespace std;
template <class T>
class vector {
public:
	vector()
	:_a(nullptr)
	,_capacity(0)
	,_size(0)
	{}
	void push_back(const T& x);
	~vector() {
		delete(_a);
		_capacity = _size = 0;
	}
	int size() {
		return _size;
	}
	T& operator[](int i) {
		return _a[i];//������������أ������ÿɽ������Ϊ��ֵ
	}

private:
	T* _a;
	int _capacity;
	int _size;
};

template <class T>//�������������ⶨ�壬������������ ����ģ������б�
void vector<T>::push_back(const T& x) {
	if (_capacity == _size) {
		int newcapacity = _capacity == 0 ? 2 : _capacity * 2;
		T* temp = new T[newcapacity];
		if (_a) {
			memcpy(temp, _a, sizeof(T) * _size);
			delete _a;
		}
		_a = temp;
		_capacity = newcapacity;
	}
	_a[_size] = x;
	_size++;
}

int main() {
	vector<int> v;//vector��������vector<int>��������
	v.push_back(1);
	v.push_back(2);
	for (int i = 0; i < v.size(); i++) {
		v[i] *= 2;
	}
	for (int i = 0; i < v.size(); i++) {
		cout << v[i] << endl;
	}
	return 0;
}