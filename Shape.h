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
	Point();
	Point(float a, float b);

	Point(const Point &pt);

	friend ostream& operator<< (ostream &os, const Point &pt);

	//getters
	float getX() { return x; }
	float getY() { return y; }

	//setters
	void setX(float a);
	void setY(float b);
	void moveBy(float a, float b);

	//overloading operators
	Point operator+ (const Point&right);
	const Point& operator= (const Point &pt);



	//destructors
	~Point();


};
Point::Point() {
	x = 0;
	y = 0;
}
Point::~Point()
{
	//do nothing
}
Point::Point(const Point &pt)
{
	x = pt.x;
	y = pt.y;
}
Point::Point(float a, float b) {
	x = a;
	y = b;
}
void Point::setX(float a)
{
	x = a;
}
void Point::setY(float b)
{
	y = b;
}
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
	virtual void Draw(SDL_Renderer *rdr) = 0;
	virtual bool inBounds(Point one, Point two) = 0;
	virtual void moveBy(Point aPlus, Point bPlus) = 0;
	virtual void erase(SDL_Renderer *rdr) = 0;
	virtual float getArea() = 0; 
	virtual void Draw() = 0; 

};
class Quad : public Shape {
private:
	Point a; 
	Point b;

public:
	void moveBy(Point aPlus, Point bPlus);
	void erase(SDL_Renderer *rdr);
	int getAX() { return a.getX(); }
	int getAY() { return a.getY(); }
	int getBX() { return b.getX(); }
	int getBY() { return b.getY(); }
	float getArea();
	Quad(int x1, int y1, int x2, int y2);
	void Draw(SDL_Renderer *rdr);
	bool inBounds(Point one, Point two);
	void Draw();
};
float Quad::getArea()
{
	//calculates area
	float width = a.getX() - b.getX();
	float height = a.getY() - b.getY();
	return abs(height*width);
}
void Quad::Draw()
{
	//prints out information
	cout << "Shape type: Quad\n";
	cout << "Point A (" << a.getX() << "," << a.getY() << ")\n";
	cout << "Point B (" << b.getX() << "," << b.getY() << ")\n";

}
void Quad::erase(SDL_Renderer *rdr)
{
	SDL_SetRenderDrawColor(rdr, 0, 0, 0, 255);
	SDL_RenderDrawLine(rdr, a.getX(), a.getY(), b.getX(), a.getY());
	SDL_RenderDrawLine(rdr, a.getX(), a.getY(), a.getX(), b.getY());
	SDL_RenderDrawLine(rdr, b.getX(), b.getY(), a.getX(), b.getY());
	SDL_RenderDrawLine(rdr, b.getX(), b.getY(), b.getX(), a.getY());

}
bool Quad::inBounds(Point one, Point two)
{
	if ((a.getX() > one.getX()) && (a.getY() > one.getY()) && (b.getX() < two.getX()) && (b.getY() < two.getY()))
	{
		return true;
	}
	else
	{
		return false;
	}
}
Quad::Quad(int x1, int y1, int x2, int y2)
{
	a.setX(x1);
	a.setY(y1);
	b.setX(x2);
	b.setY(y2);
}
void Quad::Draw(SDL_Renderer *rdr)
{
	SDL_SetRenderDrawColor(rdr, 194, 255, 245, 255);
	SDL_RenderDrawLine(rdr, a.getX(), a.getY(), b.getX(), a.getY());
	SDL_RenderDrawLine(rdr, a.getX(), a.getY(), a.getX(), b.getY());
	SDL_RenderDrawLine(rdr, b.getX(), b.getY(), a.getX(), b.getY());
	SDL_RenderDrawLine(rdr, b.getX(), b.getY(), b.getX(), a.getY());
}
	
void Quad::moveBy(Point aPlus, Point bPlus) {
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
	void Draw(SDL_Renderer *rdr);
	~Triangle();
	void moveBy(Point aPlus, Point bPlus);
	bool inBounds(Point one, Point two);
	void erase(SDL_Renderer *rdr);
	float getArea(); 
	void Draw();
};

void Triangle::Draw()
{
	//prints info
	cout << "Shape type: Triangle\n";
	cout << "Point A (" << A.getX() << "," << A.getY() << ")\n";
	cout << "Point B (" << B.getX() << "," << B.getY() << ")\n";
	cout << "Point C (" << C.getX() << "," << C.getY() << ")\n";
}
float Triangle::getArea()
{	//calculates area using points
	float Ax = A.getX()*(B.getY() - C.getY());
	float Bx = B.getX()*(C.getY() - A.getY());
	float Cx = C.getX()*(A.getY() - B.getY());
	return abs((Ax + Bx + Cx) / 2);
}
void Triangle::erase(SDL_Renderer *rdr)
{

	SDL_SetRenderDrawColor(rdr, 0, 0, 0, 255);
	SDL_RenderDrawLine(rdr, A.getX(), A.getY(), B.getX(), B.getY());
	SDL_RenderDrawLine(rdr, A.getX(), A.getY(), C.getX(), C.getY());
	SDL_RenderDrawLine(rdr, B.getX(), B.getY(), C.getX(), C.getY());
}
bool Triangle::inBounds(Point one, Point two)
{
	if ((A.getX() > one.getX()) && (A.getX() < two.getX()) && (A.getY() > one.getY()) && (A.getY() < two.getY()) &&
		(B.getX() > one.getX()) && (B.getX() < two.getX()) && (B.getY() > one.getY()) && (B.getY() < two.getY()) &&
		(C.getX() > one.getX()) && (C.getX() < two.getX()) && (C.getY() > one.getY()) && (C.getY() < two.getY()))
	{
		return true;
	}
	else
	{
		return false;
	}
}
void Triangle::moveBy (Point aPlus, Point bPlus)
{
	A.setX(A.getX() + aPlus.getX());
	A.setY(A.getY() + aPlus.getY());
	B.setX(B.getX() + aPlus.getX());
	B.setY(B.getY() + aPlus.getY());
	C.setX(C.getX() + aPlus.getX());
	C.setY(C.getY() + aPlus.getY());
}
Triangle::Triangle(int aX, int aY, int bX, int bY, int cX, int cY)
{
	A.setX(aX);
	A.setY(aY);
	B.setX(bX);
	B.setY(bY);
	C.setX(cX);
	C.setY(cY);
}
Triangle::~Triangle()
{}
void Triangle::Draw(SDL_Renderer *rdr)
{
	SDL_SetRenderDrawColor(rdr, 194, 255, 245, 255);
	SDL_RenderDrawLine(rdr, A.getX(), A.getY(), B.getX(), B.getY());
	SDL_RenderDrawLine(rdr, A.getX(), A.getY(), C.getX(), C.getY());
	SDL_RenderDrawLine(rdr, B.getX(), B.getY(), C.getX(), C.getY());
}

#endif // !SHAPE_H
