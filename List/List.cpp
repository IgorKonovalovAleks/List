/*#include "List.h"


template <class T>
List<T>::List() {
	first = nullptr;
}


template <class T>
List<T>::List(size_t s) : first(nullptr) {
	Node* cur = first;
	for (int i = 0; i < s; i++) {
		cur = new Node();
		cur = cur->next;
	}
}

template <class T>
List<T>::~List() {
	Node* cur = first;
	while (cur != nullptr) {
		Node* tmp = cur->next;
		delete[] cur;
		cur = tmp;
	}
}

template <class T>
List<T>::List(Node* f) : first(f) {}

template <class T>
List<T>::List(List<T>& old) : first(nullptr) {
	if (old.first == nullptr)
		return;
	Node* cur = first;
	for (auto it = old.begin(); it != nullptr; ++it) {
		cur = new Node();
		cur->value = it.current().value;
		cur = cur->next;
	}

}

template <class T>
List<T>::List(List<T>&& old) : first(nullptr) {
	first = old.first;
	old.first = nullptr;
}

template <class T>
List<T>::List(std::initializer_list<T> in) : first(nullptr) {
	if (in.empty())
		return;
	Node* cur = first;
	for (auto it : in) {
		cur = new Node();
		cur->value = it;
		cur = cur->next;
	}
}

template <class T>
typename List<T>::Node& List<T>::Iterator::current() {
	return *ptr;
}

template <class T>
typename List<T>::Node& List<T>::Iterator::operator++() {
	ptr = ptr->next;
	return *ptr;
}

template <class T>
bool List<T>::Iterator::operator==(Iterator i) {
	return ptr == i.ptr;
}

template <class T>
bool List<T>::Iterator::operator!=(Iterator i) {
	return ptr != i.ptr;
}

template <class T>
List<T>& List<T>::operator=(const List<T>& ls) {

	if (ls.first == nullptr) {
		clear();
		first = nullptr;
		return *this;
	}
	Node* cur = first;
	for (List<T>::Node* it = ls.first; it != nullptr; it = it->next) {
		cur = new Node();
		cur->value = it->value;
		cur = cur->next;
	}
	return *this;
}

template <class T>
List<T>& List<T>::operator=(List<T>&& ls) {
	first = ls.first;
	ls.first = nullptr;
	return *this;
}

template <class T>
bool List<T>::operator==(const List<T> ls) const {

	if (ls.first == nullptr)
		return;
	Node* cur = first;
	for (auto it = ls.begin(); it != nullptr; ++it) {
		if (cur == nullptr || it.current().value != cur.value)
			return false;

		cur = cur->next;
	}
	return true;

}

template <class T>
typename List<T>::Iterator List<T>::begin() {
	return Iterator(first);
}

template <class T>
typename List<T>::Iterator List<T>::end() {
	return Iterator(nullptr);
}

template <class T>
T List<T>::firstValue() const {
	return first->value;
}

template <class T>
bool List<T>::empty() {
	return first->next == nullptr;
}

template <class T>
size_t List<T>::size() {
	int res = 0;
	for (auto it = begin(); it != nullptr; ++it) {
		res++;
	}
	return res;
}

template <class T>
void List<T>::insert(int i, T v) {
	Node* cur = first;
	for (int j = 0; j < i - 1; j++) {
		cur = cur->next;
	}

	Node* nx = cur->next;
	Node* nw = new Node();
	nw->value = v;
	nw->next = nx;
	cur->next = nw;
}

template <class T>
void List<T>::clear() {
	Node* cur = first;
	while (cur != nullptr) {
		Node* tmp = cur->next;
		delete[] cur;
		cur = tmp;
	}
}

template <class T>
T List<T>::erase(int i) {
	Node* cur = first;
	for (int j = 0; j < i; j++) {
		if (cur->next == nullptr)
			throw std::exception();
		cur = cur->next;
	}

	Node nx = cur->next;
	cur->next = nx->next;
	T res = nx->value;
	delete[] nx;
	return res;
}

template <class T>
void List<T>::push_front(T v) {
	Node* nd = new Node();
	nd->value = v;
	nd->next = first;
	first = nd;
}

template <class T>
void List<T>::push_back(T v) {
	if (first == nullptr) {
		first = new Node();
		first->next = nullptr;
		first->value = v;
		return;
	}
	Node* cur = first;
	while (cur->next != nullptr) {
		cur = cur->next;
	}
	Node* nd = new Node();
	nd->value = v;
	nd->next = nullptr;
	cur->next = nd;
}

template <class T>
T List<T>::pop_back() {
	if (first == nullptr)
		throw std::exception();
	else if (first->next == nullptr) {
		T res = first->value;
		delete[] first;
		return res;
	}
	Node* cur = first;
	while (cur->next->next != nullptr) {
		cur = cur->next;
	}
	Node* nd = cur->next;
	cur->next = nullptr;
	T res = nd->value;
	delete[] nd;
	return res;
}

template <class T>
T List<T>::pop_front() {
	if (first == nullptr)
		throw std::exception();
	Node* nd = first;
	first = nd->next;
	T res = nd->value;
	delete[] nd;
	return res;
}

template <class T>
List<T> List<T>::merge(const List<T>& ls) const {
	List<T> res;
	Node* p2 = ls.first;
	Node* p1 = first;

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

template <class T>
List<T> List<T>::cutInHalf() {
	Node* fast = first;
	Node* slow = first;

	if (first->next == nullptr)
		return List<T>();

	if (first->next->next == nullptr) {
		std::cout << "cut\n";
		fast = first->next;
		first->next = nullptr;
		return List<T>(fast);
	}
	
	while (fast->next != nullptr && fast->next->next != nullptr) {
		fast = fast->next->next;
		slow = slow->next;
	}

	Node* nd = slow->next;
	slow->next = nullptr;
	return List<T>(nd);

}

template <class T>
void List<T>::sort() {

	if (first->next != nullptr) {
		List<T> second = cutInHalf();
		sort();
		second.sort();
		*this = merge(second);
	}

}

template <class T>
void List<T>::print() {
	for (List<T>::Iterator it = begin(); it != end(); ++it) {
		Node a = it.current();
		std::cout << a.value;
	}
}


*/