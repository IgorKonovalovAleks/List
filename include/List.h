#pragma once
#include <iostream>
#include <initializer_list>


template<class T>
class Node {
public:
	Node* next;
	T value;
	Node* another; //для 17 задачи
};



template <class T>
class List {

public:
	
	Node<T>* first;

	List(){ first = nullptr; }

	List(size_t s) {
		if (s > 0) {
			first = new Node<T>();
			auto cur = first;
			for (int i = 1; i < s; i++) {
				cur->next = new Node<T>();
				cur = cur->next;
			}
		}
	}

	List(Node<T>* f) : first(f) {}

	List(List<T>& old) : first(nullptr) {
		if (old.first == nullptr)
			return;
		int i = 0;
		Node<T>* cur;
		for (auto it = old.begin(); it != old.end(); ++it) {
			if (i != 0) {
				cur->next = new Node<T>();
				cur = cur->next;
				cur->value = it.ptr->value;
			}
			else {
				first = new Node<T>();
				cur = first;
				i++;
				cur->value = it.ptr->value;
			}
		}

	}

	List(List<T>&& old) : first(nullptr) {
		first = old.first;
		old.first = nullptr;
	}

	List(std::initializer_list<T> in) : first(nullptr) {
		if (in.size() == 0)
			return;
		Node<T>* cur;
		int i = 0;
		for (T it : in) {
			if (i != 0) {
				cur->next = new Node<T>();
				cur = cur->next;
				cur->value = it;
			}
			else {
				first = new Node<T>();
				cur = first;
				i++;
				cur->value = it;
			}
		}
	}

	~List() {
		Node<T>* cur = first;
		while (cur != nullptr) {
			Node<T>* tmp = cur->next;
			delete cur;
			cur = tmp;
		}
	}


	List<T>& operator=(const List<T>& ls) {

		if (ls.first == nullptr) {
			clear();
			first = nullptr;
			return *this;
		}
		int i = 0;
		Node<T>* cur;
		for (auto it = ls.begin(); it != ls.end(); ++it) {
			if (i != 0) {
				cur->next = new Node<T>();
				cur = cur->next;
				cur->value = it.ptr->value;
			}
			else {
				first = new Node<T>();
				cur = first;
				i++;
				cur->value = it.ptr->value;
			}
		}
		return *this;
	}

	List<T>& operator=(List<T>&& ls) {
		first = ls.first;
		ls.first = nullptr;
		return *this;
	}

	bool operator==(const List<T>& const ls) const {

		if (ls.first == nullptr) {
			if (first == nullptr)
				return true;
			else
				return false;
		}

		Node<T>* cur = first;
		for (auto it = ls.begin(); it != nullptr; ++it) {
			if (cur == nullptr || it.value() != cur->value)
				return false;

			cur = cur->next;
		}
		return true;

	}

	class Iterator {
	public:
		Node<T>* ptr;
		Iterator(Node<T>* p) : ptr(p) {}
		Iterator(Iterator& old) : ptr(old.ptr) {}
		Iterator(Iterator&& old) : ptr(old.ptr) {
			old.ptr = nullptr;
		}

		Iterator operator++() {
			ptr = ptr->next;
			return Iterator(ptr);
		}

		T value() {
			return (*ptr).value;
		}

		T next() {
			if (ptr->next == nullptr)
				throw std::exception();
			return (*(ptr->next)).value;
		}

		Iterator& operator=(const Iterator& old) {
			ptr = old.ptr;
			return *this;
		}

		Iterator& operator=(Iterator&& old) {
			ptr = old.ptr;
			old.ptr = nullptr;
			return *this;
		}

		bool operator==(Iterator i) {
			return ptr == i.ptr;
		}

		bool operator!=(Iterator i) {
			return ptr != i.ptr;
		}

	};

	Iterator begin() const {
		return Iterator(first);
	}

	Iterator end() const {
		return Iterator(nullptr);
	}

	T firstValue() const {
		return first->value;
	}

	bool empty() const {
		return first->next == nullptr;
	}

	size_t size() const {
		int res = 0;
		for (auto it = begin(); it != end(); ++it) {
			res++;
		}
		return res;
	}

	void print() const {
		for (List<T>::Iterator it = begin(); it != end(); ++it) {
			std::cout << it.value() << " ";
		}
		std::cout << '\n';
	}

	void clear() {
		Node<T>* cur = first;
		while (cur != nullptr) {
			Node<T>* tmp = cur->next;
			delete cur;
			cur = tmp;
		}
	}

	void insert(int i, T v) {
		Node<T>* cur = first;
		for (int j = 0; j < i; j++) {
			if (cur->next == nullptr)
				throw std::exception();
			cur = cur->next;
		}

		Node<T>* nx = cur->next;
		Node<T>* nw = new Node<T>();
		nw->value = v;
		nw->next = nx;
		cur->next = nw;
	}

	void insert(Node<T>* n, T v) {        //O(1)
		if (first != nullptr) {
			n->next = new Node<T>();
			n->next->value = v;
			n->next->next = nullptr;
		}
		else {
			first = new Node<T>();
			first->value = v;
			first->next = nullptr;
		}
	}

	T erase(int i) {                     //O(n) принимает номер удаляемого
		if (i == 0)
			return pop_front();
		Node<T>* cur = first;
		for (int j = 0; j < i - 1; j++) {
			if (cur->next == nullptr)
				throw std::exception();
			cur = cur->next;
		}

		Node<T>* nx = cur->next;
		cur->next = nx->next;
		T res = nx->value;
		delete nx;
		return res;
	}

	T erase(Iterator prev) {               //O(1) принимает итератор на элемент перед удаляемым

		if (prev.ptr->next == nullptr) {
			throw std::exception();
		}

		Node<T>* nx = prev.ptr->next;
		prev.ptr->next = prev.ptr->next->next;
		T res = nx->value;
		delete nx;
		return res;
	}

	void push_back(T v) {
		if (first == nullptr) {
			first = new Node<T>();
			first->next = nullptr;
			first->value = v;
			return;
		}
		Node<T>* cur = first;
		while (cur->next != nullptr) {
			cur = cur->next;
		}
		Node<T>* nd = new Node<T>();
		nd->value = v;
		nd->next = nullptr;
		cur->next = nd;
	}

	void push_front(T v) {
		Node<T>* nd = new Node<T>();
		nd->value = v;
		nd->next = first;
		first = nd;
	}

	T pop_front() {
		if (first == nullptr)
			throw std::exception();
		Node<T>* nd = first;
		first = nd->next;
		T res = nd->value;
		delete nd;
		return res;
	}

	T pop_back() {
		if (first == nullptr)
			throw std::exception();
		else if (first->next == nullptr) {
			T res = first->value;
			delete first;
			return res;
		}
		Node<T>* cur = first;
		while (cur->next->next != nullptr) {
			cur = cur->next;
		}
		Node<T>* nd = cur->next;
		cur->next = nullptr;
		T res = nd->value;
		delete nd;
		return res;
	}

	List<T> merge(const List<T>& ls) const {
		List<T> res;
		Node<T>* p2 = ls.first;
		Node<T>* p1 = first;

		while (p1 != nullptr && p2 != nullptr) {

			if (p2->value <= p1->value) {
				res.push_back(p2->value);
				p2 = p2->next;
			}
			else {
				res.push_back(p1->value);
				p1 = p1->next;
			}

		}

		if (p2 == nullptr) {
			while (p1 != nullptr) {
				res.push_back(p1->value);
				p1 = p1->next;
			}
		}

		else if (p1 == nullptr) {
			while (p2 != nullptr) {
				res.push_back(p2->value);
				p2 = p2->next;
			}
		}

		return res;
	}

	void sort() {

		if (first->next != nullptr) {
			List<T> second = cutInHalf();
			sort();
			second.sort();
			*this = merge(second);
		}

	}

	List<T> cutInHalf() {
		Node<T>* fast = first;
		Node<T>* slow = first;

		if (first->next == nullptr)
			return List<T>();

		if (first->next->next == nullptr) {
			fast = first->next;
			first->next = nullptr;
			return List<T>(fast);
		}

		while (fast->next != nullptr && fast->next->next != nullptr) {
			fast = fast->next->next;
			slow = slow->next;
		}

		Node<T>* nd = slow->next;
		slow->next = nullptr;
		return List<T>(nd);

	}
};

