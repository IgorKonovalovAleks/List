#pragma once
#include <iostream>
#include "List.h"


template <class T>
class LQueue {
private:
	List<T> data;
	unsigned long long size;
	Node<T>* last;
public:

	LQueue<T>() : size(0) {
		data = List<T>();
		last = nullptr;
	}

	LQueue<T>(LQueue<T>& old) : size(old.size) {
		data = List<T>(old.data);
		last = getLast();
	}

	Node<T>* getLast() {
		Node<T>* res;
		for (auto it = data.begin(); it != data.end(); ++it) {
			res = it.ptr;
		}
		return res;
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
		data.insert(last, i);
		if (last != nullptr) {
			last = last->next;
		}
		else {
			last = data.first;
		}
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