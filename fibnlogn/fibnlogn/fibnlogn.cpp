// fibnlogn.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

vector<vector<int> > COMPS(vector<vector<int> > a, vector<vector<int> > b) {
	vector<vector<int> > s = a;
	s[0][0] = a[0][0] * b[0][0] + a[0][1] * b[1][0];
	s[0][1] = a[0][0] * b[0][1] + a[0][1] * b[1][1];
	s[1][0] = a[1][0] * b[0][0] + a[1][1] * b[0][1];
	s[1][1] = a[1][0] * b[0][1] + a[1][1] * b[1][1];
	return s;
}

vector<vector<int> > POW(vector<vector<int> > a, int v) {
	if (v <= 1) {
		vector<vector<int> > b;
		b.resize(2);
		b[0].push_back(0);
		b[0].push_back(1);
		b[1].push_back(1);
		b[1].push_back(1);
		return b;
	}
	if (!(v & 1)) {
		vector<vector<int> > b = POW(a, v / 2);
		return COMPS(b, b);
	}
	else {
		vector<vector<int> > b = POW(a, v / 2);
		b = COMPS(b, b);
		a = COMPS(a, b);
		return a;
	}
}

int main()
{
	int n;
	cin >> n;
	vector<vector<int> > a;
	a.resize(2);

	a[0].push_back(0);
	a[0].push_back(1);
	a[1].push_back(1);
	a[1].push_back(1);

	a = POW(a, n);

	cout << a[0][0] << "\n";
    return 0;
}

