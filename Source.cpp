#include <iostream>
#include <string>
#include <cmath>

#include "Shape.h"
#include "DLL.h"

using namespace std;
int main(int argc, char *argv[]) {
	
	sortedDLL<Shape*> l1;
	
	Triangle *one = new Triangle(15, 15, 64, 40, 35, 8);
	Triangle *two = new Triangle(2, 3, 90, 5, 20, 7);
	Quad *three = new Quad(1, 2, 3, 4);
	Quad *four = new Quad(4, 4, 7, 7);

	l1.insert(one);
	l1.insert(three);
	l1.insert(two);
	l1.insert(four);

	l1.print();
	cout << l1.getCount() << endl;

	l1.remove(3);
	l1.print(); 

	 


	return 0;
}
