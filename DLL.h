#ifndef DLL_H
#define DLL_H

using namespace std;

template <typename T>
struct Node {
	T _data;
	Node<T> *_next; 
	Node<T> *_prev;
	//default constructor 
	Node() : _data(), _next(nullptr), _prev(nullptr) {} 
	//constructor with value
	Node(T val) : _data(val), _next(nullptr), _prev(nullptr) {} 
	bool operator<(const Node<T> &rhs);
	~Node();
};
bool Node<Shape*>::operator<(const Node<Shape*> &rhs)
{//specializing less than operator for Shape pointers
	return (this->_data->getArea() < rhs._data->getArea());

}
template <typename T>
Node<T>::~Node()
{
//	cout << "Node destructor called." << endl;
}

template <typename T>
class Iterator
{
	Node<T> *current;
public:
	//default constructor
	Iterator() : current(nullptr) {}
	//constructor node
	Iterator(Node<T>* p) : current(p) {}
	
	//overloaded operators
	T operator* () { return current->_data; }
	Iterator<T> operator++();
	Iterator<T> operator--(); 
	bool operator== (const Iterator<T> &right);
};
template <typename T> 
Iterator<T> Iterator<T>::operator++()
{ //increment operator
	current = current->_next;
	return *this;
}
template <typename T>
Iterator<T> Iterator<T>::operator--()
{//decrement operator
	current = current->_prev;
	return *this;
}

template <typename T>
bool Iterator<T>::operator== (const Iterator<T> &right)
{//equals to operator
	if (current == right.current)
		//compares addresses of two nodes
		return true;
	else
		return false;
}

template <typename T>
class dLL {
protected:
	int _cnt;
	Node<T> *_head;
public:
	//setters for iterator
	Iterator<T> begin(); 
	Iterator<T> end(); 
	//default constructor
	dLL();
	// copy constructor
	//dLL(const dLL<T>& copy);
	

	int getCount() { return _cnt; }
	void insert(T val);
	void print();
	int search(T val);
	void remove(int idx);
	T get(int idx);
	void destroy();

	// destructor
	~dLL() { destroy(); }


};
template <typename T>
dLL<T>::dLL()
{//default constructor
	_head = new Node<T>();
	_head->_next = _head;
	_head->_prev = _head;
}

template <typename T>
Iterator<T> dLL<T>::begin()
{//creates iterator to point to first 
	Iterator<T> t(_head->_next);
	return t;
	//now current refers to _head
}
template <typename T>
Iterator<T> dLL<T>::end()
{//creates iterator to point to last
	Iterator<T> t(_head->_prev);
	//nullptr defines end of list
	return t;
}
template <typename T>
void dLL<T>::insert(T val) {
	//inserts new node directly after head
	Node<T> *p = new Node<T>(val);
	p->_next = _head->_next;
	p->_prev = _head->_next->_prev;
	p->_next->_prev = p;
	p->_prev->_next = p;
	

	_cnt++;

}
template <typename T>
void dLL<T>::print() {
	//prints all values in list
	Node<T> *p = _head->_next;
	int itr = 1;
	while (p != _head)
	{
		cout << "Data stored in node " << itr << ": " << p->_data << endl;
		itr++;
		p = p->_next;
	}

}
void dLL<Shape*>::print(){
	//specialized for Shape*
	Node<Shape*> *p = _head->_next;
	int itr = 1;
	while (p != _head)
	{
		cout << "Data stored in node " << itr << ":\n";
			p->_data->Draw();
			cout << "Area of shape: " << p->_data->getArea() << endl;
		itr++;
		p = p->_next;
	}
}
template <typename T>
int dLL<T>::search(T val) {
	//finds number for node holding certain value
	int intItr = 1;
	if (_head->_next->_data == val)
	{
		return intItr;
	}
	else
	{
		Node *itr = _head->_next;
		while (itr != _head)
		{
			intItr++;
			itr = itr->_next;
			if (itr->_data == val)
			{
				return intItr;
			}
		}
		return -1;
	}

}
template <typename T>
void dLL<T>::remove(int idx) {
	//ensure inside bounds
	Node<T> *itr = _head;//->_next;
	for (int i = 0; i < idx; i++)
	{
		itr = itr->_next;
	}
	itr->_next->_prev = itr->_prev;
	itr->_prev->_next = itr->_next;
	delete itr;
	_cnt--;
}
void dLL<Shape*>::remove(int idx)
{
	Node<Shape*> *itr = _head;
	for (int i = 0; i < idx; i++)
	{
		itr = itr->_next;
	}
	
	delete itr->_data;
	//itr->_data = nullptr;
	itr->_next->_prev = itr->_prev;
	itr->_prev->_next = itr->_next;

	delete itr; 
	_cnt--;
}
template <typename T>
T dLL<T>::get(int idx) {
	//check in bounds
	Node<T> *itr = _head->_next;
	for (int i = 1; i < idx; i++)
	{
		itr = itr->_next;
	}
	return itr->_data;
}
template <typename T>
void dLL<T>::destroy() {
	//deletes all items in list
	if (_cnt == 0)
	{//list is empty
	}
	else
	{
		Node<T> *p = _head->_next;
		while (p != _head)
		{
			p = p->_next;
			delete p->_prev;
			_cnt--;
		}
		delete _head;
	}
}
template <typename T>
class sortedDLL : public dLL<T>
	//class to sort list
{
public:
	//order as inserted 
	void insert(T val);
};
template <typename T>
void sortedDLL<T>::insert(T val)
{
	if (_cnt >= 1)
	{
		Node<T> *p = _head->_next;
		while (val > p->_data && p != _head)
		{
			p = p->_next;
		}
		Node<T> *toAdd = new Node<T>(val);
		toAdd->_next = p;
		toAdd->_prev = p->_prev;
		toAdd->_next->_prev = toAdd;
		toAdd->_prev->_next = toAdd;
		_cnt++;
	}
	else
	{//if list is empty
		this->dLL<T>::insert(val);
	}
}

void sortedDLL<string>::insert(string val)
{ //specialized for string
	if (_cnt >= 1)
	{
		Node<string> *p = _head->_next;
		while (val.length() > p->_data.length() && p != _head)
		{
			p = p->_next;
		}
		Node<string> *toAdd = new Node<string>(val);
		toAdd->_next = p;
		toAdd->_prev = p->_prev;
		toAdd->_next->_prev = toAdd;
		toAdd->_prev->_next = toAdd;
		_cnt++;
	}
	else
	{
		this->dLL<string>::insert(val);
	}
}
void sortedDLL<Shape*>::insert(Shape* val)
{//specialized for shape*

	if (_cnt >= 1)
	{
		Node<Shape*> *p = _head->_next;
		while (val->getArea() > p->_data->getArea() && p != _head)
		{
			p = p->_next;
		}
		Node<Shape*> *toAdd = new Node<Shape*>(val);
		toAdd->_next = p;
		toAdd->_prev = p->_prev;
		toAdd->_next->_prev = toAdd;
		toAdd->_prev->_next = toAdd;
		_cnt++;
	}
	else
	{
		this->dLL<Shape*>::insert(val);
	}
}
#endif // !DLL_H