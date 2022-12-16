#include "List.h"

int main() {

	List<int> a;
	a.push_back(3);
	a.push_back(2);
	a.push_front(0);
	a.print();
	
	a.sort();
	a.print();

	return 0;
}


