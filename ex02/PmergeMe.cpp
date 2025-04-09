#include "PmergeMe.hpp"
#include <sys/_types/_size_t.h>

void printVector(const std::vector<int>& vec) {
	for (size_t i = 0; i < vec.size(); ++i) {
		std::cout << vec[i];
		if (i != vec.size() - 1)
			std::cout << " ";
	}
	std::cout << std::endl;
}

void PmergeMe::printInitVector() {
	std::cout << "Print of the Main Vector:\n";
	for (size_t i = 0; i < _mainChain.size(); ++i) {
		std::cout << _mainChain[i];
		if (i != _mainChain.size() - 1)
			std::cout << " ";
	}
	std::cout << std::endl;
	std::cout << std::endl;
}


PmergeMe::PmergeMe(const PmergeMe& other) {
	_mainChain = other._mainChain;
	// _deque = other._deque;
}

PmergeMe& PmergeMe::operator=(const PmergeMe& other) {
	_mainChain = other._mainChain;
	// _deque = other._deque;
	return (*this);
}

void PmergeMe::insertValue(int value) {
	_mainChain.push_back(value);
	// _deque.push_back(value);
}

void PmergeMe::separatePairs() {
	int a;
	int b;
	vector newMain;

	for (size_t i = 0; i < _mainChain.size(); i += 2)
	{
		if (i + 1 >= _mainChain.size()) {
			_secondaryChain.push_back(_mainChain[i]);
		} else {
			a = _mainChain[i];
			b = _mainChain[i + 1];
			newMain.push_back(a > b ? a : b);
			_secondaryChain.push_back(a > b ? b : a);
		}
	}
	_mainChain = newMain;
}

	// Generates Jacobsthal numbers for optimal insertion sequence
std::vector<size_t> generateJacobsthalSequence(size_t n)
{
	std::vector<size_t> sequence = {0, 1};
	while (sequence.back() < n)
	{
		size_t next = sequence[sequence.size() - 1] + 2 * sequence[sequence.size() - 2];
		sequence.push_back(next);
	}
	return sequence;
}

// void PmergeMe::binaryInsertion() {
// 	for (size_t i = 0; i < _secondaryChain.size(); ++i)
// 	{
// 		auto pos = std::lower_bound(_mainChain.begin(), _mainChain.end(), _secondaryChain[i]);
// 		_mainChain.insert(pos, _secondaryChain[i]);
// 	}
// 	_secondaryChain.clear();
// }

void PmergeMe::binaryInsertion() {
	if (_secondaryChain.empty()) return;

	// Insert first element directly
	auto pos = std::lower_bound(_mainChain.begin(), _mainChain.end(), _secondaryChain[0]);
	_mainChain.insert(pos, _secondaryChain[0]);

	// Generate Jacobsthal sequence for optimal insertion order
	auto jacob = generateJacobsthalSequence(_secondaryChain.size());

	// Insert remaining elements in optimal order
	for (size_t i = 1; i < _secondaryChain.size(); ++i) {
		size_t insert_pos = jacob[i];
		if (insert_pos >= _secondaryChain.size()) {
			insert_pos = _secondaryChain.size() - 1;
		}
		int val = _secondaryChain[insert_pos];
		pos = std::lower_bound(_mainChain.begin(), _mainChain.end(), val);
		_mainChain.insert(pos, val);
	}

	_secondaryChain.clear();
}

void PmergeMe::algorithm() {

	if (_mainChain.size() <= 1) return;

	separatePairs();

	std::cout << "MainChain Vector:\n";
	printVector(_mainChain);
	std::cout << "SecondaryChain Vector:\n";
	printVector(_secondaryChain);
	std::cout << std::endl;

	// algorithm();
	// binaryInsertion();

}

bool isNumeric(const std::string& str) {
	int i = 0;
	for (char ch : str)
	{
		if (ch == '-' && i == 0 && str.length() != 1)
			continue;
		if (!std::isdigit(ch))
			return false;
		i++;
	}
	return true;
}
