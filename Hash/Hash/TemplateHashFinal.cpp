#include "Hash.h"
#include "rational.h"

Hash<KRat> name(Hash<KRat>& _arg) {
	return _arg;
}

int main()
{
	Hash<KRat> hash = { KRat(1, 2), KRat(2, 1) };
	Hash<KRat> hash2;
	
	hash2.Emplace(3, 1);

	hash2.Emplace(1, 3);

	hash2.Emplace(1, 2);


	for (auto it = hash2.cbegin(); it != hash2.cend(); ++it) {
		std::cout << it->val << " ";
	}

	hash2 = name(hash);
	std::cout << "\n________________________\n\n";

	for (auto it = hash.begin(); it != hash.end(); ++it) {
		std::cout << it->val << " ";
	}

	std::cout << "\n____________________________\n";

	for (auto it = hash2.begin(); it != hash2.end(); ++it) {
		std::cout << it->val << " ";
	}
	std::cout << "\n";
	return 0;
}