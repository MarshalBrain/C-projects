#pragma once

#include <exception>
#include <locale>

using namespace std;

//int nod(int aNum, int aDenom);
class KRat;

class KNumProxy
{
public:
	KNumProxy(KRat& r1) : r(r1) {};

	operator int();
	KRat& operator = (int a);

private:
	KRat & r;
};

class KDenomProxy
{
public:
	KDenomProxy(KRat& r1) : r(r1) {};

	KRat& operator = (int a);
	operator int();

private:
	KRat & r;
};




class KRat
{
public:
	KRat() : num(0), denom(1) {};
	explicit KRat(int const aNum) : num(aNum), denom(1) {};
	KRat(int const aNum, int const aDenom) : num(aNum), denom(aDenom) {};
	KRat(KRat const & r) : num(r.num), denom(r.denom) {};

	KRat& operator +=(KRat const & r2)
	{
		num = r2.denom*num + r2.num*denom;
		denom *= r2.denom;
		normalize();
		return *this;
	}

	KRat& operator += (int const a)
	{
		num = num + denom * a;
		normalize();
		return *this;
	}

	KRat operator + (KRat const & r2) const
	{
		KRat t(r2);
		t += *this;
		return t;
	}

	KRat operator + (int const a) const
	{
		KRat t(a);
		t += *this;
		return t;
	}


	KRat& operator -= (KRat const & r2)
	{
		num = num * r2.denom - denom * r2.num;
		denom *= r2.denom;
		normalize();
		return *this;
	}

	KRat& operator -= (int const a)
	{
		num -= a * denom;
		normalize();
		return *this;
	}

	KRat operator - (KRat const & r2) const
	{
		KRat t(*this);
		t -= r2;
		return t;
	}

	KRat operator - (int const a) const
	{
		KRat t(*this);
		t -= a;
		return t;
	}


	KRat& operator *= (KRat const & r2)
	{
		num *= r2.num;
		denom *= r2.denom;
		normalize();
		return *this;
	}

	KRat& operator *= (int const a)
	{
		num *= a;
		normalize();
		return *this;
	}

	KRat operator * (KRat const & r2) const
	{
		KRat t(r2);
		t *= *this;
		return t;
	}

	KRat operator * (int a) const
	{
		KRat t(*this);
		t *= a;
		return t;
	}

	KRat& operator /= (KRat const & r2)
	{
		num *= r2.denom;
		denom *= r2.num;
		normalize();
		return *this;
	}

	KRat& operator /= (int a)
	{
		denom *= a;
		normalize();
		return *this;
	}

	KRat operator / (KRat const & r2) const
	{
		KRat t(*this);
		t /= r2;
		return t;
	}

	KRat operator / (int a) const
	{
		KRat t(*this);
		t /= a;
		return t;
	}

	KRat operator ++ (int)
	{
		KRat bufer = *this;
		this->num += this->denom;
		this->normalize();
		return bufer;
	}

	KRat& operator ++ ()
	{
		this->num += this->denom;
		this->normalize();
		return *this;
	}

	explicit operator double() const
	{
		return (double)num / denom;
	}


	bool operator == (KRat const &r2) const
	{
		return (r2.num == num && r2.denom == denom);
	}

	friend bool operator == (int a, const KRat &r)
	{
		return (a == r.num && r.denom == 1);
	}

	/*bool operator == (int a) const
	{
	return (a == num && denom == 1);
	}*/



	KRat& operator = (KRat const &r2)
	{
		num = r2.num;
		denom = r2.denom;
		return *this;
	}



	bool operator != (KRat const &r2) const
	{
		return (!(*this == r2));
	}

	bool operator > (KRat const &r2) const
	{
		if (denom < r2.denom) return 1;
		else if (denom == r2.denom && num > r2.num) return 1;
		else return 0;
	}

	bool operator >= (KRat const &r2)
	{
		return (!(*this < r2));
	}

	bool operator < (KRat const &r2) const
	{
		return (!(*this > r2) && !(*this == r2));
	}

	bool operator <= (KRat const &r2) const
	{
		return (!(*this > r2));
	}

	friend KRat operator / (int a, const KRat &r)
	{
		KRat t(r);
		swap(t.num, t.denom);
		t.num *= a;
		t.normalize();
		return t;
	}

	friend class KNumProxy;
	friend class KDenomProxy;

	KNumProxy Num()
	{
		return KNumProxy(*this);
	}

	int Num() const
	{
		return num;
	}

	int Denom() const
	{
		return denom;
	}

	KDenomProxy Denom()
	{
		return KDenomProxy(*this);
	}

	KRat& normalize()
	{
		int del = nod(num, denom);
		num /= del;
		denom /= del;
		return *this;
	}

	friend ostream& operator << (ostream& OS, KRat const &r)
	{
		if (r.denom == 1) OS << r.num;
		else OS << r.num << "/" << r.denom;
		return OS;
	}

	friend istream& operator >> (istream& is, KRat &r)
	{
		is >> r.num;
		char ch;
		is.unsetf(ios::skipws);
		is >> ch;
		while (ch != '/' && ch != '\\' && ch != '\n' && !isdigit(ch))
		{
			is >> ch;
		}
		is.setf(ios::skipws);
		if (ch == '/' || ch == '\\')
			is >> r.denom;
		else
		{
			is.putback(ch);
			r.denom = 1;
		}
		if (r.denom == 0) { cerr << "Denominator equals zero.\n"; system("pause"); exit(0); }
		else r.normalize();
		return is;

	}

	int nod(int aNum, int aDenom)
	{
		int rem;
		if (aNum == 0) return aDenom;
		if (aNum < aDenom) swap(aNum, aDenom);
		while (rem = aNum % aDenom)
		{
			aNum = aDenom;
			aDenom = rem;
		}
		return aDenom;
	}

	int num;
	int denom;
};


KNumProxy :: operator int()
{
	return r.num;
}

KRat& KNumProxy:: operator = (int a)
{
	r.num = a;
	r.normalize();
	return r;
}

KDenomProxy :: operator int()
{
	return r.denom;
}

KRat& KDenomProxy :: operator = (int a)
{
	if (a != 0)
	{
		r.denom = a;   // r - поле класс KDenomProxy
		r.normalize();
		return r;
	}
	else { cout << "[Denom] Impossible.\n"; return r; }
}