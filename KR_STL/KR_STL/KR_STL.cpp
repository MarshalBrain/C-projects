// KR_STL.cpp: определяет точку входа для консольного приложения.
//
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <fstream>
#include <iterator>
#include <algorithm>

using namespace std;

struct Node {
	Node(int _Num = 0, int _Value = 0) : Num(_Num), Value(_Value) {}

	friend std::istream& operator >> (std::istream& in, Node& Node) {
		in >> Node.Num >> Node.Value;
		return in;
	}

	int Num;
	int Value;
};

struct Edge {
	Edge(int _Begin = 0, int _End = 0, int _Weight = 0) : Begin(_Begin), End(_End), Weight(_Weight) {}

	bool operator == (Edge const& _arg) const {
		if (_arg.Begin == Begin && _arg.End == End) return true;
		return false;
	}

	bool operator != (Edge const& _arg) const {
		return !((*this) == _arg);
	}

	bool operator < (Edge const& _arg) const {
		bool f = 0;
		if (Begin < _arg.Begin) f = 1;
		if (Begin == _arg.Begin && End < _arg.End) f = 1;
		return f;
	}

	friend istream& operator >> (istream& in, Edge& Edge) {
		in >> Edge.Begin >> Edge.End >> Edge.Weight;
		return in;
	}

	friend ostream& operator << (ostream& out, Edge const& Edge) {
		out << Edge.Begin << "->" << Edge.End;
		return out;
	}

	int Begin;
	int End;
	int Weight;
};


bool isAdj(Edge _arg1, Edge _arg2) {
	if (_arg1.Begin != _arg2.Begin && _arg1.End != _arg2.Begin
		&& _arg1.Begin != _arg2.End && _arg1.End != _arg2.End) return true;
	return false;
}

int main()
{
	vector<Node> nodes;
	vector<Edge> edges;

	ifstream in("inv.txt");
	ofstream out("output.txt");

	copy(istream_iterator<Node>(in), istream_iterator<Node>(), back_inserter(nodes));

	in.close();
	in.open("ine.txt");

	copy(istream_iterator<Edge>(in), istream_iterator<Edge>(), back_inserter(edges));

	map<Edge, set<Edge> > answer1;
	set<Edge> answer3;
	pair<Edge, Edge> answer2;

///////////////////////////////////SOLVE_1//////////////////////////////////////////////////
	for (auto it : edges) {
		answer1[it] = {};
	}

	for_each(edges.begin(), edges.end(), [&answer1, &edges](Edge arg) {
											for (auto it : edges){
												if (it == arg) continue;
												if ((find(edges.begin(), edges.end(), Edge(arg.Begin, it.Begin)) != edges.end()
													|| find(edges.begin(), edges.end(), Edge(arg.End, it.Begin)) != edges.end()
													|| find(edges.begin(), edges.end(), Edge(arg.Begin, it.End)) != edges.end()
													|| find(edges.begin(), edges.end(), Edge(arg.End, it.End)) != edges.end())
													&& isAdj(arg, it)) answer1[arg].insert(it);
											}
										});

	out << "Ответ на первую задачу:\n";

	map<Edge, set<Edge> >::iterator it = answer1.begin();

	while (it != answer1.end()) {
		out << it->first.Begin << "->" << it->first.End << ": ";
		set<Edge>::iterator itS = it->second.begin();
		while (itS != it->second.end()) {
			out << itS->Begin << "->" << itS->End << " ";
			++itS;
		}
		out << "\n";
		++it;
	}


///////////////////////////////////SOLVE_2//////////////////////////////////////////////////	
	for_each(edges.begin(), edges.end(), [&answer2, &edges](Edge arg) {
											for (auto it : edges) {
												if (it == arg) continue;
												if ((find(edges.begin(), edges.end(), Edge(arg.Begin, it.Begin)) == edges.end()
													&& find(edges.begin(), edges.end(), Edge(arg.End, it.Begin)) == edges.end()
													&& find(edges.begin(), edges.end(), Edge(arg.End, it.End)) == edges.end()
													&& find(edges.begin(), edges.end(), Edge(arg.Begin, it.End)) == edges.end()
													&& find(edges.begin(), edges.end(), Edge(it.Begin, arg.Begin)) == edges.end()
													&& find(edges.begin(), edges.end(), Edge(it.Begin, arg.End)) == edges.end()
													&& find(edges.begin(), edges.end(), Edge(it.End, arg.End)) == edges.end()
													&& find(edges.begin(), edges.end(), Edge(it.End, arg.Begin)) == edges.end())
													&& isAdj(arg, it)) {
													answer2 = make_pair(arg, it); break;
												}
											}
	});

	out << "Ответ на вторую задачу:\n";
	out << answer2.first.Begin << "->" << answer2.first.End << " " << answer2.second.Begin << "->" << answer2.second.End << "\n";
///////////////////////////////////SOLVE_3//////////////////////////////////////////////////
	for_each(edges.begin(), edges.end(), [&answer3, &edges](Edge arg) {
		bool f = 0;
		for (auto it : edges) {
			if (it == arg) continue;
			if (arg.Begin == it.End || arg.End == it.End) {
				f = 1;
				break;
			}
		}
		if (!f) answer3.insert(arg);
	});

	out << "Ответ на третью задачу:\n";
	copy(answer3.begin(), answer3.end(), ostream_iterator<Edge>(out, "\n"));
    return 0;
}

