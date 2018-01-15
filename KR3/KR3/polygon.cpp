#pragma once
#include "polygon.h"
#include <algorithm>

P::P(double x0, double y0, double a, double b) : Point(x0, y0), a(a), b(b) {}
P::P(P const& p) : Point(p.x0,p.y0), a(p.a), b(p.b) {}
P::P() : Point(0, 0), a(1), b(1) {}

P& P::operator += (P const& pol) {
	x0 = (x0 + pol.x0) / 2;
	y0 = (y0 + pol.y0) / 2;
	a = std::min(a, pol.a);
	b = std::min(b, pol.b);
	return *this;
}

P& P::operator += (Point const& t) {
	x0 = (x0 + t.x0) / 2;
	y0 = (y0 + t.y0) / 2;
	return *this;
}

P P::operator + (P const& pol) const& {
	P newPol(*this);
	newPol += pol;
	return newPol;
}

P P::operator + (Point const& t) const& {
	P newPol(*this);
	newPol += t;
	return newPol;
}

void P::Print(std::ostream& os) {
	os << x0 << " " << y0 << " " << a << " " << b;
}

std::ostream& operator << (std::ostream& os, P& pol) {
	pol.Print(os);
	return os;
}

bool P::operator == (P const& pol) const& {
	if (abs(x0 - pol.x0) < eps && abs(y0 - pol.y0) < eps && abs(a - pol.a) < eps && abs(b - pol.b) < eps) return 1;
	else return 0;
}

bool P::operator < (P const& pol) const& {
	if (x0 < pol.x0 || (abs(x0 - pol.x0) < eps && y0 < pol.y0) ||
		(abs(x0 - pol.x0) < eps && abs(y0 - pol.y0) < eps && a < pol.a) ||
		(abs(x0 - pol.x0) < eps && abs(y0 - pol.y0) < eps && abs(a - pol.a) < eps && b < pol.b)) return 1;
	else return 0;
}

bool P::operator <=(P const& pol) const& {
	if (*this < pol || *this == pol) return 1;
	else return 0;
}