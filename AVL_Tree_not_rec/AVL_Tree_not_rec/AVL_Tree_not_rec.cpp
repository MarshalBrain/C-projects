// AVL_Tree_not_rec.cpp: определяет точку входа для консольного приложения.
//
#include <iostream>
#include <list>
#include <algorithm>
#include <cstdio>
#include <fstream>

struct Node {
	Node () : count(0) {}
	int val;
	int count;
	Node* right;
	Node* left;
};

class Tree {
public:
	Tree(Node* Root) : root(Root) {}
	Tree() : root(nullptr){}
	~Tree() {
		using std::list;
		list<Node*> r = { root };
		while (r.size()) {
			Node* q = r.front();
			if (q->left) r.push_back(q->left); 
			if (q->right) r.push_back(q->right);
			delete q;
			r.pop_front();
		}
	}

	//Добавление к дереву нового узла
	bool Push(int &val) {
		int left_or_right = 0;
		Node* q = root;
		Node* parent = root;
		while (q) {
			if (val > q->val) {
				parent = q;
				q = q->right;
				left_or_right = 1;
			}
			else {
				parent = q;
				q = q->left;
				left_or_right = 2;
			}
		}
		q = new Node;
		q->val = val;
		q->left = nullptr;
		q->right = nullptr;

		if (left_or_right == 0) {
			root = q;
		}
		if (left_or_right == 1) {
			parent->right = q;
		}
		if (left_or_right == 2) {
			parent->left = q;
		}
		return 1;
	} 

	Node * root;
};

struct treeProcesing {
	treeProcesing(int High = 0, int PointerOnAVL = 0, bool IsAVL = 0, int CountOfVisits = 0, Node* Root = nullptr) : high(High), pointerOnAVL(PointerOnAVL), 
		isAVL(IsAVL), countOfVisits(CountOfVisits), root(Root) {}
	int high; //Высота АВЛ-дерева
	bool isAVL; //Флаг - является ли АВЛ-деревом дерево, растущее из рассматриваемого узла 
	int pointerOnAVL; //Число узла, из которого растёт ближайщее АВЛ-дерево, к расматриваемому узлу
	int countOfVisits; //Количество посещений данного узла (используется для обработки подъмов из поддеревьев)
	Node* root; //Сам рассматриваемый узел в дереве
};

int main()
{
	setlocale(LC_ALL, "rus");
	using std::list;

	std::ifstream in("input.txt");

	Tree sourceTree;
	int n;
	in >> n;
	if (n < 1 || n > 10000000) {
		std::cout << "Недопустимый размер дерева/n";
	}

	for (int i = 0; i < n; ++i) {
		int val;
		in >> val;
		sourceTree.Push(val);
	}

	treeProcesing temperateValue(0, -1, 1, 0, sourceTree.root);
	list<treeProcesing> Stek;
	Stek.push_front(temperateValue);

	int high, pointerOnAVL;
	bool isAVL;

	
	while (Stek.size()) {
		Node* q = Stek.front().root;
		if (Stek.front().countOfVisits < 2) q->count++;
		if (q) {
			treeProcesing *Top = &Stek.front();
//Если рассматриваемый узел - лист
			if (q->left == nullptr && q->right == nullptr) {
				high = 1;
				pointerOnAVL = q->val;
				isAVL = 1;
				Stek.pop_front();

				if (Stek.size() == 0) {
					if (isAVL) {
						std::cout << "Номер вершины из которой растёт максимальное AVL-дерево: " << pointerOnAVL << "\n";
						break;
					}
				}
				
				Top = &Stek.front();
				Top->root->count++;
//Если мы поднялись из левого листа, в узел, который содержит этот лист за левого сына. Т.е. мы ни разу ещё не посещали этот узел.
				if (Top->countOfVisits == 0) {
					Top->high = high;
					Top->isAVL = isAVL;
					Top->pointerOnAVL = pointerOnAVL;
					Top->countOfVisits = 1;
					high = 0, pointerOnAVL = -1, isAVL = 1;

					if (Top->root->right) {
						treeProcesing rightTop(0, -1, 1, 0, Top->root->right);
						Stek.push_front(rightTop);
						continue;
					}
					else {
						Top->countOfVisits = 2;
						Top->high = 2;
						Top->pointerOnAVL = Top->root->val;
					}
				}
//Если мы поднялись из правого листа, в узел, который содержит этот лист за правого сына. Т.е. мы уже посещали этот узел, когда подымались в него из левого поддерева
				if (Top->countOfVisits == 1) {
					if (Top->isAVL) {
						Top->high = std::max(Top->high, high) + 1;
						Top->pointerOnAVL = Top->root->val;
						Top->countOfVisits = 2;
					}
					else {
						Top->isAVL = 0;
						Top->high = std::max(Top->high, high) + 1;
						Top->pointerOnAVL = pointerOnAVL;
						Top->countOfVisits = 2;
					}
				}
			}
//Идём в левое поддерево, по возможности
			if (q->left && Top->countOfVisits == 0) {
				treeProcesing leftTop(0, -1, 1, 0, q->left);
				Stek.push_front(leftTop);
				//		Top->countOfVisits = 1;
				continue;
			}
//Если мы уже обошли левое поддерево (или туда невозможно пойти), идём в правое, если это возможно
			if ((!q->left || Top->countOfVisits == 1) && q->right && Top->countOfVisits != 2) {
				Top->countOfVisits = 1;
				treeProcesing rightTop(1, -1, 1, 0, q->right);
				Stek.push_front(rightTop);
				//		Top->countOfVisits = 1;
				continue;
			}
//Если для этого узла мы обошли и правое, и левое поддеревья, обрабатываем этот узел 
			if (Top->countOfVisits == 2 && Stek.size() > 1) {
				isAVL = Top->isAVL;
				high = Top->high;
				pointerOnAVL = Top->pointerOnAVL;
//Поднимаемся на узел вверх
				Stek.pop_front();
				Top = &Stek.front();
				Top->root->count++;
//Если мы поднялись из левого поддерева
				if (Top->countOfVisits == 0) {
					Top->high = high;
					Top->isAVL = isAVL;
					Top->pointerOnAVL = pointerOnAVL;
					Top->countOfVisits = 1;
					high = 0, pointerOnAVL = -1, isAVL = 1;

					if (Top->root->right) {
						treeProcesing rightTop(0, -1, 1, 0, Top->root->right);
						Stek.push_front(rightTop);
						continue;
					}
					else {
						Top->countOfVisits = 2;
						if (Top->isAVL) {
							if (Top->high > 1) {
								Top->isAVL = 0;
							}
							else {
								Top->pointerOnAVL = Top->root->val;
								Top->high = 2;
							}
						}
					}
				}

// Если мы поднялись из правого поддерева
				if (Top->countOfVisits == 1) {
					if (Top->isAVL && isAVL && abs(high - Top->high) < 2) {
						Top->high = std::max(Top->high, high) + 1;
						Top->pointerOnAVL = Top->root->val;
						Top->countOfVisits = 2;
					}
					else {
						if (Top->isAVL || isAVL) {
							if (high > Top->high) {
								Top->high = high;
								Top->pointerOnAVL = pointerOnAVL;
							}
						}
						Top->isAVL = 0;
						Top->countOfVisits = 2;
					}
				}
			}

			if (Top->countOfVisits == 2 && Stek.size() == 1) {
				std::cout << "Номер вершины из которой растёт максимальное AVL-дерево: " << Top->pointerOnAVL << "\n";
				break;
			}
		}
	}
	Node* ptr = sourceTree.root;
	list<Node*> List;
	List.push_front(ptr);
	while (List.size()) {
		Node* q = List.front();
		std::cerr << q->count << "-" << q->val << " ";
		if (q->left) List.push_back(q->left);
		if (q->right) List.push_back(q->right);
		List.pop_front();
	}
    return 0;
}

