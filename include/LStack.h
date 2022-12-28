#pragma once
#include <iostream>
#include "List.h"


template <class T>
class LStack {
private:
	List<T> data;
	unsigned long long size;
public:

	LStack<T>() : size(0) {
		data = List<T>();
	}

	LStack<T>(LStack<T>& old) : size(old.size) {
		data = List<T>(old.data);
	}

	int getSize() {
		return size;
	}

	bool empty() {
		return size == 0;
	}

	T getTop() {
		if (size == 0)
			throw std::exception();
		return data.firstValue();
	}

	void push(T i) {
		data.push_front(i);
		size++;
	}

	void pop() {
		if (size == 0) {
			throw std::exception();
		}
		size--;
		data.pop_front();
	}
};

