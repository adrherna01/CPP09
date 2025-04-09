#include <iostream>
#include <vector>
#include <deque>

using string = std::string;
using vector = std::vector<int>;
using deque = std::deque<int>;

class PmergeMe {
	private:
		vector _mainChain;
		vector _secondaryChain;

	public:
		PmergeMe() = default;
		PmergeMe(const PmergeMe& other);
		PmergeMe& operator=(const PmergeMe& other);
		~PmergeMe() = default;

		// void separateInitial();
		void algorithm();
		void separatePairs();
		void binaryInsertion();

		void insertValue(int value);
		void printInitVector();
	};
	void printVector(const vector& vec);
	bool isNumeric(const std::string& str);