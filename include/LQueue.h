#pragma once
#include <iostream>
#include "List.h"

const unsigned int DEFAULT_CAPACITY = 256;

template <class T>
class LQueue {
private:
	List<T> data;
	unsigned long long size;
public:

	LQueue<T>() : size(0) {
		data = List<T>();
	}

	LQueue<T>(LQueue<T>& old) : size(old.size) {
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
		data.push_back(i);
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