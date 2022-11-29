#pragma once
#include<initializer_list>

template <class T>
class List {
	
	class Node {
		Node* next;
		T value;
	};

	Node* first;

	List();
	List(size_t n);
	List(List<T>& old);
	List(List<T>&& old);
	List(std::initializer_list<T> in);
	~List();

	List<T>& operator=(const List<T>& ls);
	List<T>& operator=(const List<T>&& ls);
	bool operator==(const List<T> ls) const;

	class Iterator {
	public:
		Node* ptr;
		Node& operator++();
		Node& operator*();
		bool operator==(Iterator i);
		bool operator!=(Iterator i);
	};
	Iterator& begin();
	Iterator& end();

	T first() const;
	T last() const;
	bool empty();
	size_t size();

	void clear();
	void insert(int i, T v);
	T erase(int);
	void push_back(T v);
	void push_front(T v);
	T pop_front();
	T pop_back();
	List<T>& merge(const List<T>& ls) const;
	void sort();

};

