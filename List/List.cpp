#include "List.h"


template <class T>
List<T>::List() {
	first = nullptr;
}


template <class T>
List<T>::List(size_t s): first(nullptr) {
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
List<T>::List(List<T>& old) : first(nullptr) {
	if (old.first == nullptr)
		return;
	Node* cur = first;
	for (auto it = old.begin(); it != nullptr; ++it) {
		cur = new Node();
		cur.value = (*it).value;
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
	for (auto it: in) {
		cur = new Node();
		cur->value = it;
		cur = cur->next;
	}
}

template <class T>
List<T>::Node& List<T>::Iterator::operator*() {
	return *ptr;
}

template <class T>
List<T>::Node& List<T>::Iterator::operator++() {
	ptr = ptr->next();
	return ptr;
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

	if (ls.first == nullptr)
		return;
	Node* cur = first;
	for (auto it = ls.begin(); it != nullptr; ++it) {
		cur = new Node();
		cur.value = (*it).value;
		cur = cur->next;
	}
}

template <class T>
List<T>& List<T>::operator=(const List<T>&& ls) {
	first = ls.first;
	ls.first = nullptr;
}


