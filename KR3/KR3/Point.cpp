#include "Point.h"

Point::Point(double x0, double y0) : x0(x0), y0(y0) {}

Point::Point(Point const& p) : x0(p.x0), y0(p.y0) {}

Point::Point() : x0(0), y0(0) {}

Point& Point::operator += (Point const& t) {
	x0 = (x0 + t.x0) / 2;
	y0 = (y0 + t.y0) / 2;
	return *this;
}

Point Point::operator + (Point const& t) const& {
	Point newPoint(*this);
	newPoint += t;
	return newPoint;
}

Point* Point::operator + (Point* t) const& {
	*t += *this;
	return t;
}

Point& Point::operator += (Point* t) {
	Point newPoint(*this);
	*this += *t;
	return *this;
}

bool Point::operator == (Point const& t) const {
	if (abs(x0 - t.x0) < eps && abs(y0 - t.y0) < eps) return 1;
	else return 0;
}

bool Point::operator < (Point const& t) const {
	if (x0 < t.x0 || (x0 == t.x0 && y0 < t.y0)) return 1;
	else return 0;
}

bool Point::operator <= (Point const& t) const {
	if (*this < t || *this == t) return 1;
	else return 0;
}

void Point::Print(std::ostream& os) {
	os << x0 << " " << y0;
}

std::ostream& operator << (std::ostream& os, Point t) {
	t.Print(os);
	return os;
}
