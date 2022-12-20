#include <gtest.h>
#include "List.h"

void task1(List<int>& a, int value) {


	if (value <= a.first->value) {
		a.push_front(value);
		return;
	}
	int i = -1;
	for (auto it = a.begin(); it != a.end(); ++it) {
		if (it.value() >= value) {
			a.insert(i, value);
			return;
		}
		i++;
	}
}

void task2(List<int>& a, int value) {

	int i = 0, j = 0;
	for (auto it = a.begin(); it != a.end(); ++it) {
		if (it.value() == value)
			j = i;
		i++;
	}
	a.erase(j);
}

int task3(List<int>& a, int k) {

	auto it1 = a.begin();
	int i = 0;
	for (; i < k; ++it1)
		i++;

	auto it2 = a.begin();
	for (; it1 != a.end(); ++it1)
		++it2;

	return it2.value();
}

void task4(List<int>& a, int& f, int& s) {  //если только один, то s = -1

	auto fast = a.begin();
	auto slow = a.begin();

	while (fast != a.end()) {
		++fast;
		if (fast == a.end()) {
			f = slow.value();
			s = -1;
			return;
		}
		++slow;
		++fast;
	}

	
	f = slow.value();
	s = (++slow).value();
}

void task5(List<int>& a) {          //erase работает за константу, если передать итератор на элемент перед удаляемым

	if (a.first->next == nullptr || a.first->next->next == nullptr) {
		a.clear();
		return;
	}

	auto fast = a.begin();
	auto slow = a.begin();
	auto prev = a.begin();

	while (fast.ptr->next != nullptr) {
		++fast;
		if (fast.ptr->next == nullptr) {
			a.erase(slow);
			a.erase(prev);
			return;
		}
		prev = slow;
		++slow;
		++fast;
	}

	a.erase(prev);
}

void task6(List<int>& a, int k) {            //раз 1 проход, то k меньше длины списка
	int m = a.size() - k - 1;
	auto it = a.begin();
	for (int i = 0; i < m; i++) {
		++it;
	}
	auto end = it.ptr;
	++it;
	auto start = it.ptr;
	end->next = nullptr;
	while (it.ptr->next != nullptr)
		++it;
	it.ptr->next = a.first;
	a.first = start;
}

void task7(List<int>& a, int i, int n) {
	if (n == 0)
		return;

	auto it = a.begin();



	for (int j = 0; j < i; j++) {
		++it;
	}
	auto start = it.ptr;
	for (int j = 0; j < n; j++) {
		++it;
	}
	auto it1 = List<int>::Iterator(start->next); //разворачиватель
	start->next = it.ptr;                        //it указывает на конец блока
	start = it1.ptr;
	++it1;
	start->next = it.ptr->next;
	auto tmp = it1.ptr;

	while (it1.ptr != it.ptr) {
		++it1;
		tmp->next = start;
		start = tmp;
		tmp = it1.ptr;
	}
	tmp->next = start;
}

void task8(List<int>& a) {
	auto it = a.begin();
	while (it != a.end()) {

		int item = it.value();
		for (List<int>::Iterator it1(it); it1.ptr->next != nullptr; ++it1) {
			if (it1.next() == item) {
				a.erase(it1);
				if (it1.ptr->next == nullptr)           //если удаленный элемент был последним
					break;
			}
		}

		++it;
	}
}

void task9(List<int>& a) {
	if (a.first->next == nullptr)
		return;

	auto it = a.begin();
	auto prev = it.ptr;
	++it;
	auto tmp = it.ptr;
	prev->next = nullptr;
	while (tmp->next != nullptr) {
		++it;
		tmp->next = prev;
		prev = tmp;
		tmp = it.ptr;
	}
	tmp->next = prev;
	a.first = tmp;
}

void task10(List<int>& a) {
	task9(a);
	a.print();
	task9(a);
}

void task11(List<int>& a, int num2) {
	int ord = 1;
	int num1 = 0;
	task9(a);
	for (auto it = a.begin(); it != a.end(); ++it) {
		num1 += ord * it.value();
		ord *= 10;
	}
	num1 += num2;
	for (auto it = a.begin(); it != a.end(); ++it) {
		it.ptr->value = num1 % 10;
		num1 /= 10;
	}
	task9(a);
	if (num1 > 0) {
		while (num1 > 0) {
			a.push_front(num1 % 10);
			num1 /= 10;
		}
	}
}

List<int> task12(List<int>& a, int num2) {
	int ord = 1;
	int num1 = 0;
	task9(a);
	for (auto it = a.begin(); it != a.end(); ++it) {
		num1 += ord * it.value();
		ord *= 10;
	}
	num1 *= num2;
	List<int> r(a.size());
	for (auto it = r.begin(); it != r.end(); ++it) {
		it.ptr->value = num1 % 10;
		num1 /= 10;
	}

	task9(a);
	while (num1 > 0) {
		r.push_front(num1 % 10);
		num1 /= 10;
	}

	return r;
}

void task13(List<int>& a, List<int>& b, List<int>& res) {
	res = a.merge(b);
}

void task14(List<int>& a) { //merge sort
	a.sort();
}

bool task15(List<int>& a) {
	auto fast = a.begin();
	auto slow = a.begin();
	while (fast != a.end()) {
		if (slow == ++fast)
			return true;
		if (fast == a.end())
			return false;
		++fast;
		++slow;
	}
	return false;
}



/*
Пусть, цикл длиннее расстояния от начала до цикла(далее - хвост)
Тогда когда slow достигнет начала цикла, fast будет впереди на длину хвоста, и fast будет отставать от slow на (длина цикла - длина хвоста) нод.
Тогда до их встречи пройдет еще столько же шагов (длина цикла - длина хвоста)
Значит, столкновение произойдет, когда slow будет в точке (длина цикла - (длина цикла - длина хвоста)) нод до начала цикла
Следовательно, до начала цикла будет (длина хвоста) нод

Если же цикл короче хвоста, то расстояние от fast до  slow будет равным остатку от деления длины хвоста на длину цикла
тогда расстояние от места встречи до начала цикла так же будет остатком от деления длины хвоста на длину цикла

первый случай есть частный случай второго
*/
int task16(List<int>& a) {
	auto fast = a.begin();
	auto slow = a.begin();
	while (++fast != slow) {
		++fast;
		++slow;
	}
	++fast;
	++slow;
	int rendezvouz = 0;
	auto start = a.begin();
	while (slow != start) {
		++start;
		++slow;
		rendezvouz++;
	}
	return rendezvouz;
}


/*
Первый проход
Вставляем между элементами исходного списка еще по ноде

Второй проход
Обрабатываем ноды по две, ставим в соответствие второй ноде в паре ноду, следующую после той, на которую указывает первая нода в паре

Третий проход
Растаскиваем ноды на два списка
*/
List<int> task17(List<int>& a) {

	auto cur = a.first;
	while (cur != nullptr) {
		auto n = cur->next;
		cur->next = new Node<int>;
		cur->next->value = cur->value;
		cur->next->next = n;
		cur = n;
	}

	cur = a.first;
	while (cur != nullptr) {
		cur->next->another = cur->another->next;
		cur = cur->next->next;
	}

	List<int> res;
	if (a.first->next->next == nullptr) {
		res.first = a.first->next;
		a.first->next = nullptr;
		return res;
	}
	cur = a.first;
	auto end = res.first;
	end = cur->next;
	while (cur != nullptr) {
		cur->next = end->next;
		if (cur->next != nullptr)
			end->next = cur->next->next;
		end = end->next;
		cur = cur->next;
	}
	return res;
}

int main(int argc, char** argv) {

	List<int> ordered;
	ordered.push_back(1);
	ordered.push_back(2);
	ordered.push_back(3);
	ordered.push_back(5);
	ordered.push_back(6);
	ordered.push_back(7);
	ordered.push_back(8);
	ordered.push_back(8);
	ordered.push_back(9);

	List<int> a;
	a.push_back(1);
	a.push_back(2);
	a.push_back(1);
	a.push_back(4);
	a.push_back(4);
	a.push_back(3);
	a.push_back(7);
	a.push_back(14);
	a.push_back(5);
	a.push_back(3);

	std::cout << "start\n";
	ordered.print();
	std::cout << "\n";

	task1(ordered, 4);
	std::cout << "task1\n";
	ordered.print();

	task2(ordered, 3);
	std::cout << "task2\n";
	ordered.print();

	int res = task3(ordered, 4);
	std::cout << "task3: " << res << '\n';
	
	int s;
	task4(ordered, res, s);
	std::cout << "task4: " << res << '\n';
	ordered.print();

	task5(ordered);
	std::cout << "task5\n";
	ordered.print();

	task6(ordered, 2);
	std::cout << "task6 \n";
	ordered.print();

	task7(ordered, 1, 4);
	std::cout << "task7 \n";
	ordered.print();

	ordered.print();
	task8(ordered);
	std::cout << "task8 \n";
	ordered.print();

	task9(ordered);
	std::cout << "task9 \n";
	ordered.print();

	std::cout << "task10 \n";
	ordered.print();
	task10(ordered);

	std::cout << "task11 \n";
	ordered.print();
	task11(ordered, 13456789);
	ordered.print();

	std::cout << "task12 \n";
	ordered.print();
	List<int> res1 = task12(ordered, 3);
	res1.print();

	//слияние работает в сортировке
	std::cout << "merge sort ";
	a.print();
	a.sort();
	a.print();

	auto cr = a.first;
	for (int z = 0; z < 3; z++)                        //зацикливание на 3 ноде
		cr = cr->next;
	auto it = a.begin();
	for (; it.ptr->next != nullptr; ++it) {}
	it.ptr->next = cr;
	std::cout << "task15: " << task15(a) << "\n";
	std::cout << "task16: " << task16(a) << "\n";
	it.ptr->next = nullptr;
	
	List<int> b(5);
	b.first->another = b.first->next->next;
	b.first->next->another = b.first->next->next->next;
	b.first->next->next->another = b.first->next;
	b.first->next->next->next->another = b.first;
	b.first->next->next->next->next->another = b.first->next->next->next->next;
	int c = 0;
	for (auto it = b.begin(); it != b.end(); ++it) {
		c++;
		it.ptr->value = c;
	}
	for (auto it = b.first; it != nullptr; it = it->next)
		std::cout << it->another->value;
	auto d = task17(b);
	std::cout << '\n';
	for (auto it = b.first; it != nullptr; it = it->next)
		std::cout << it->another->value;

	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}


