#pragma once
namespace A {

template <class T>
struct __list_node {
	__list_node<T>* _next;
	__list_node<T>* _prev;
	T _data;
	__list_node(const T& x=T()) {
		_data = x;
		_next = _prev = nullptr;
	}
};

template <class T,class Ref,class Ptr>
struct  __list_iterator {
	typedef __list_node<T> node;
	typedef __list_iterator<T, Ref, Ptr> self;
	node* _node;

	__list_iterator(node* n)
		:_node(n)
	{}

	//*it
	Ref operator*() {
		return _node->_data;
	}

	Ptr operator->() {
		return &(_node->_data);
	}
	//++it
	self& operator++() {
		_node = _node->_next;
		return *this;
	}

	self operator++(int) {
		self a (*this);
		_node = _node->_next;
		return a;
	}
	self& operator--() {
		_node = _node->_prev;
		return *this;
	}

	self operator--(int) {
		self a(*this);
		_node = _node->_prev;
		return a;
	}

	bool operator!=(const self& x )const {
		return x._node != _node;
	}
	bool operator==(const self& x)const {
		return x._node == _node;
	}

};

template <class T>
class list {
public:        //带头双向循环链表
	typedef __list_node<T> node;
	typedef __list_iterator<T,T&,T*> iterator;
	typedef __list_iterator<T, const T&, const T*> const_iterator;

	list()
		:_head(new node)
	{
		_head->_prev = _head;
		_head->_next = _head;
	}
	list(const list<T>& l) {
		_head = new node;
		_head->_next = _head->_prev = _head;
		for (auto e : l) {
			push_back(e);
		}
	}
	//list<T>& operator=(const list<T>& l) {
	//	if (this != &l) {
	//		clear();
	//		for (auto e : l) {
	//			push_back(e);
	//		}
	//	}
	//	return *this;
	//}
	//现代写法
	list<T>& operator=(list<T> l) {
		swap(_head, l._head);//出了作用域，自动调用l的析构函数销毁
		return *this;
	}

	~list() {
		clear();
		delete _head;
		_head = nullptr;
	}
	void clear() {
		iterator it = begin();
		while (it != end()) {
			erase(it++);
		}
	}
	iterator erase(iterator it) {
		node* next = it._node->_next;
		node* cur = it._node->_prev;
		cur->_next = it._node->_next;
		it._node->_next->_prev = cur;
		delete it._node;
		return next;
	}

	void insert(iterator pos, const T& x) {
		node* cur = pos._node->_prev;
		node* newnode = new node(x);
		cur->_next = newnode;
		newnode->_prev = cur;
		newnode->_next = pos._node;
		pos._node->_prev = newnode;
	}

	iterator begin() {
		return iterator(_head->_next);//匿名对象
	}
	iterator end() {
		return iterator(_head);
	}
	const_iterator begin()const {
		return const_iterator(_head->_next);
	}
	const_iterator end()const {
		return const_iterator(_head);
	}
	void push_back(const T& x) {
		//node* newnode = new node(x);
		////newnode->_data = x;
		//node* tail = _head->_prev;
		//tail->_next = newnode;
		//newnode->_prev = tail;
		//newnode->_next = _head;
		//_head->_prev = newnode;
		insert(end(), x);
	}
	void push_front(const T& x) {
		insert(begin(), x);
	}
	void pop_back() {
		erase(iterator(_head->_prev));//匿名对象
	}
	void pop_front() {
		erase(begin());
	}


private:
	node* _head;
};

void print( list<int>& l) {
	list<int>::iterator it = l.begin();
	while (it != l.end()) {
		
		if (*it % 2 == 0) {
			it=l.erase(it);
		}
		else {
			it++;
		}
	}
}
void pri(const list<int>& l) {
	list<int>::const_iterator it = l.begin();
	while (it != l.end()) {
		cout << *it << " ";
		it++;

	}
}

void test() {
	list<int> l;
	l.push_back(1);
	l.push_back(2);
	l.push_back(3);
	l.push_back(4);
	l.push_back(5);
	l.push_front(0);
	l.pop_front();
	l.pop_back();
	list<int> l1(l);
	list<int> l2=l1;

	pri(l2);
;


}







}
