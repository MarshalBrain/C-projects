// Graphs.cpp: определяет точку входа для консольного приложения.
//
#include <iostream>
#include <vector>
#include <map>
#include <iterator>
#include <algorithm>
#include <fstream>
#include <set>

using std::map;
using std::vector;
using std::fstream;
using std::set;


struct Edge {


	friend std::istream& operator >> (std::istream& in, Edge& Edge) {
		in >> Edge.firstNode >> Edge.secondNode;
		return in;
	}

	int firstNode;
	int secondNode;
};

int main() {
	std::ifstream in("Nodes.txt");
	vector<int> Nodes;

	copy(std::istream_iterator<int>(in), std::istream_iterator<int>(), back_inserter(Nodes));

	in.close();


	in.open("Ages.txt");
	vector<Edge> Edges;
	
	copy(std::istream_iterator<Edge>(in), std::istream_iterator<Edge>(), back_inserter(Edges));

	map<int, vector<int> > Graph;

	for_each(Nodes.begin(), Nodes.end(), [&Graph](int& node) {
		Graph[node].resize(0);
	});
	
	for_each(Edges.begin(), Edges.end(), [&Graph](Edge& edge) {
		Graph[edge.firstNode].push_back(edge.secondNode);
		Graph[edge.secondNode].push_back(edge.firstNode);
	});

//	std::partition();

	vector<int> answer;
	for_each(Graph.begin(), Graph.end(), [&answer](auto& value) {
		if (value.second.size() == 0) answer.push_back(value.first);
	});

	std::cout << "Count of isolated nodes: " << answer.size() << "\n";

	if (answer.size()) {
		std::cout << "This nodes: ";
		copy(answer.begin(), answer.end(), std::ostream_iterator<int>(std::cout, " "));
		std::cout << "\n";
	}

	return 0;
}




/*void files(int i, char flag) {
if (i == 0) {
if (flag == 'o') freopen_s(stdin, ;
if (flag == 'c') fclose(stdin);
}
if (i == 1) {
if (flag == 'o') freopen_s("Edges.txt", "r", stdin);
if (flag == 'c') fclose(stdin);
}
}


int main()
{
std::ios_base::sync_with_stdio(true);
files(0, 'o');

map<int, vector<int> > Graph;

vector<int> Nodes;
copy(Nodes.begin(), Nodes.end(), std::istream_iterator<int>(std::cin));

for (int i = 0; i < Nodes.size(); ++i) {
std::cout << Nodes[i] << " ";
}
/*	for_each(Graph.begin(), Graph.end(), procesOne);

while (!inEdge.eof()) {
int first, second;
inEdge >> first >> second;
Graph[first].push_back(second);
Graph[second].push_back(first);
}

map<int, vector<int> >::iterator it = Graph.begin();
vector<int> answer;

while (it != Graph.end()) {
if (it->second.size() == 0) {
answer.push_back(it->first);
}
++it;
}

system("CLS");
std::cout << "Count of isolated nodes: " << answer.size();
if (answer.size()) {
std::cout << "\nThis nodes: ";
copy(answer.begin(), answer.end(), std::ostream_iterator<int>(std::cout, " "));
}
std::cout << "\n";
return 0;
}*/
