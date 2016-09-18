#ifndef SHAPE_H
#define SHAPE_H


using namespace std;

//Point base class
class Point
{
private:
	float x, y;

public:
	//constructors
	Point() : x(0), y(0) {}
	Point(float a, float b) : x(a), y(b) {} 
	Point(const Point &pt) : x(pt.x), y(pt.y) {} 

	//getters
	float getX() const { return x; }
	float getY() const { return y; }

	//setters
	void setX(float a) { x = a; }
	void setY(float b) { y = b; }
	void moveBy(float a, float b);

	//overloading operators
	Point operator+ (const Point&right);
	const Point& operator= (const Point &pt);

	//destructors
	~Point() {} //do nothing

};
void Point::moveBy(float a, float b)
{
	x += a;
	y += b;
}
Point Point::operator+ (const Point &right)
{
	x += right.x;
	y += right.y;
	Point newPoint(x, y);
	return newPoint;
}
const Point& Point::operator=(const Point &pt)
{
	if (pt.x == x && pt.y == y)
	{
		return *this;
	}
	else
	{
		x = pt.x;
		y = pt.y;
		return *this;
	}
}
class Shape
{
public:
	virtual void Draw() = 0;
	virtual void moveBy(Point aPlus, Point bPlus) = 0;
	virtual float getArea() = 0;

};

class Quad : public Shape {
private:
	Point a;
	Point b;

public:
	void moveBy(Point aPlus, Point bPlus);
	int getAX() { return a.getX(); }
	int getAY() { return a.getY(); }
	int getBX() { return b.getX(); }
	int getBY() { return b.getY(); }

	Quad(int x1, int y1, int x2, int y2);
	void Draw();
	float getArea();
	friend ostream& operator<<(ostream &os, const Quad &obj);
};
ostream& operator<<(ostream &os, const Quad &obj)
{
	os << "Shape type: Quad\n";
	os << "Point A (" << obj.a.getX() << "," << obj.a.getY() << ")\n";
	os << "Point B (" << obj.b.getX() << "," << obj.b.getY() << ")\n";
	return os;
}
float Quad::getArea()
{
	//calculates area
	float width = a.getX() - b.getX();
	float height =a.getY() - b.getY();
	return abs(height*width);
}
Quad::Quad(int x1, int y1, int x2, int y2)
{
	//Point setter
	a.setX(x1);
	a.setY(y1);
	b.setX(x2);
	b.setY(y2);
}
void Quad::Draw()
{
	//prints out information
	cout << "Shape type: Quad\n";
	cout << "Point A (" << a.getX() << "," << a.getY() << ")\n";
	cout << "Point B (" << b.getX() << "," << b.getY() << ")\n";
	
}

void Quad::moveBy(Point aPlus, Point bPlus) {
	//moves by points entered
	a.moveBy(aPlus.getX(), aPlus.getY());
	b.moveBy(bPlus.getX(), bPlus.getY());

}

class Triangle : public Shape {
private:
	Point A;
	Point B;
	Point C;
public:
	Triangle(int aX, int aY, int bX, int bY, int cX, int cY);
	void Draw();
	void moveBy(Point aPlus, Point bPlus);
	float getArea();
	friend ostream& operator<<(ostream &os, const Triangle &obj);

	~Triangle();
};
ostream& operator<<(ostream &os, const Triangle &obj)
{//prints info
	os << "Shape type: Triangle\n";
	os << "Point A (" << obj.A.getX() << "," << obj.A.getY() << ")\n";
	os << "Point B (" << obj.B.getX() << "," << obj.B.getY() << ")\n";
	os << "Point C (" << obj.C.getX() << "," << obj.C.getY() << ")\n";
	return os;
}
float Triangle::getArea()
{	//calculates area using points
	float Ax = A.getX()*(B.getY() - C.getY());
	float Bx = B.getX()*(C.getY() - A.getY());
	float Cx = C.getX()*(A.getY() - B.getY());
	return abs((Ax + Bx + Cx)/2);
}
void Triangle::moveBy(Point aPlus, Point bPlus)
{
	//moves coordinates by two points entered
	A.setX(A.getX() + aPlus.getX());
	A.setY(A.getY() + aPlus.getY());
	B.setX(B.getX() + aPlus.getX());
	B.setY(B.getY() + aPlus.getY());
	C.setX(C.getX() + aPlus.getX());
	C.setY(C.getY() + aPlus.getY());
}
Triangle::Triangle(int aX, int aY, int bX, int bY, int cX, int cY)
{//point setter
	A.setX(aX);
	A.setY(aY);
	B.setX(bX);
	B.setY(bY);
	C.setX(cX);
	C.setY(cY);
}
Triangle::~Triangle()
{
	//will be called by parent
}
void Triangle::Draw()
{
	//prints info
	cout << "Shape type: Triangle\n";
	cout << "Point A (" << A.getX() << "," << A.getY() << ")\n";
	cout << "Point B (" << B.getX() << "," << B.getY() << ")\n";
	cout << "Point C (" << C.getX() << "," << C.getY() << ")\n";
}

#endif // !SHAPE_H