// maxVosrPodposl.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int INF = 2147483647;

int main()
{
	int n;
	cin >> n;
	
	vector<int> a(n);
	vector<int> f(n+1);

	for (int i = 0; i < n; ++i) {
		cin >> a[i];
	}

	if (n == 1) {
		cout << 1 << "\n" << a[0] << "\n";
		return 0;
	}

	f[0] = -INF;
	for (int i = 1; i <= n; ++i) f[i] = INF;

	for (int i = 0; i < n; ++i) {
		int j = (int)(upper_bound(f.begin(), f.end(), a[i]) - f.begin());
		if (f[j - 1] < a[i] && a[i] < f[j]) f[j] = a[i];
	}

	for (int i = n; i >= 1; --i) {
		if (f[i] != INF) {
			cout << i << "\n";
			break;
		}
	}

	int i = 1;
	while (f[i] != INF) {
		cout << f[i] << " ";
		++i;
	}
	cout << "\n";
	return 0;
}

