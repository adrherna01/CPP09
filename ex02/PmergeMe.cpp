#include "PmergeMe.hpp"

PmergeMe::PmergeMe(const PmergeMe& other) {
	_mainChainVec = other._mainChainVec;
	_mainChainDeque = other._mainChainDeque;
}

PmergeMe& PmergeMe::operator=(const PmergeMe& other) {
	_mainChainVec = other._mainChainVec;
	_mainChainDeque = other._mainChainDeque;
	return (*this);
}

void PmergeMe::setVecInit() {
	_vectorStart = getTime();
}

void PmergeMe::setVecFinish() {
	_vectorEnd = getTime();
}

void PmergeMe::setDequeInit() {
	_dequeStart = getTime();
}

void PmergeMe::setDequeFinish() {
	_dequeEnd= getTime();
}

sizetVector PmergeMe::generateJacobsthalInsertionOrder() {
	sizetVector order;
	sizetVector jacob = generateJacobsthalSequence(_secondaryChainVec.size());

	// Build order from Jacobsthal sequence
	for (size_t j = 1; j < jacob.size(); ++j) {
		size_t start = jacob[j - 1] + 1;
		size_t end = std::min(jacob[j], _secondaryChainVec.size() - 1);

		// Add indices in reverse order (for efficiency)
		for (size_t i = end; i >= start; --i) {
			order.push_back(i);
		}
	}

	return order;
}

void PmergeMe::insertSingleElementVec(int value) {
	auto insertPos = std::lower_bound(_mainChainVec.begin(), _mainChainVec.end(), value);
	_mainChainVec.insert(insertPos, value);
}

void PmergeMe::binaryInsertionVec() {
	if (_secondaryChainVec.empty()) return;

	std::cout << "AAA chain\n";
	printVector(_secondaryChainVec);
	std::cout << "BBB chain\n";
	printVector(_mainChainVec);

	// Step 1: Insert first pend element
	insertSingleElementVec(_secondaryChainVec[0]);

	// Step 2: Generate Jacobsthal sequence
	std::vector<size_t> insertionOrder = generateJacobsthalInsertionOrder();
	printVector(insertionOrder);

	// Step 3: Insert remaining elements in optimized order
	for (size_t index : insertionOrder) {
		if (index < _secondaryChainVec.size()) {
			insertSingleElementVec(_secondaryChainVec[index]);
			// std::cout << "Main chain\n\n";
			// printVector(_mainChainVec);
		}
	}

	_secondaryChainVec.clear();
}

// void PmergeMe::binaryInsertionVec(vector& mainChain, vector& secChain){
// 	if (secChain.empty()) return;

// 	std::cout << "AAA chain\n";
// 	printVector(secChain);
// 	std::cout << "BBB chain\n";
// 	printVector(mainChain);

// 	// Step 1: Insert first pend element
// 	insertSingleElementVec(secChain[0]);

// 	// Step 2: Generate Jacobsthal sequence
// 	std::vector<size_t> insertionOrder = generateJacobsthalInsertionOrder();
// 	printVector(insertionOrder);

// 	// Step 3: Insert remaining elements in optimized order
// 	for (size_t index : insertionOrder) {
// 		if (index < secChain.size()) {
// 			insertSingleElementVec(secChain[index]);
// 			// std::cout << "Main chain\n\n";
// 			// printVector(mainChain);
// 		}
// 	}

// 	secChain.clear();
// }

void PmergeMe::separatePairsVec() {
	int a;
	int b;
	vector newMain;

	for (size_t i = 0; i < _mainChainVec.size(); i += 2)
	{
		if (i + 1 >= _mainChainVec.size()) {
			_secondaryChainVec.push_back(_mainChainVec[i]);
		} else {
			a = _mainChainVec[i];
			b = _mainChainVec[i + 1];
			newMain.push_back(a > b ? a : b);
			_secondaryChainVec.push_back(a > b ? b : a);
		}
	}
	_mainChainVec = newMain;
}

void PmergeMe::algorithmVec() {
	if (_mainChainVec.size() <= 1) return;

	separatePairsVec();
	std::cout << "MainChain Vector:\n";
	printVector(_mainChainVec);
	std::cout << "SecondaryChain Vector:\n";
	printVector(_secondaryChainVec);
	std::cout << std::endl;
	algorithmVec();
	binaryInsertionVec();
}

////////////////////////////////////////////////////////////////////

void PmergeMe::insertSingleElementDeque(int value) {
	auto insertPos = std::lower_bound(_mainChainDeque.begin(), _mainChainDeque.end(), value);
	_mainChainDeque.insert(insertPos, value);
}

void PmergeMe::binaryInsertionDeque() {
	if (_secondaryChainDeque.empty()) return;

	insertSingleElementDeque(_secondaryChainDeque[0]);
	std::vector<size_t> insertionOrder = generateJacobsthalInsertionOrder();
	for (size_t index : insertionOrder) {
		if (index < _secondaryChainDeque.size()) {
			insertSingleElementDeque(_secondaryChainDeque[index]);

		}
	}

	_secondaryChainDeque.clear();
}

void PmergeMe::separatePairsDeque() {
	int a;
	int b;
	deque newMain;

	for (size_t i = 0; i < _mainChainDeque.size(); i += 2)
	{
		if (i + 1 >= _mainChainDeque.size()) {
			_secondaryChainDeque.push_back(_mainChainDeque[i]);
		} else {
			a = _mainChainDeque[i];
			b = _mainChainDeque[i + 1];
			newMain.push_back(a > b ? a : b);
			_secondaryChainDeque.push_back(a > b ? b : a);
		}
	}
	_mainChainDeque = newMain;
}

void PmergeMe::algorithmDeque() {
	if (_mainChainDeque.size() <= 1) return;

	separatePairsDeque();
	// std::cout << "MainChain Vector:\n";
	// printVector(_mainChain);
	// std::cout << "SecondaryChain Vector:\n";
	// printVector(_secondaryChainDeque);
	// std::cout << std::endl;
	algorithmDeque();
	binaryInsertionDeque();
}

////////////////////////////////////////////////////////////////////

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

TimePoint getTime() {
	return std::chrono::high_resolution_clock::now();
}

long long PmergeMe::calculateDurationVec() {
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(_vectorEnd - _vectorStart);
	return duration.count();
}

long long PmergeMe::calculateDurationDeque() {
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(_dequeEnd - _dequeStart);
	return duration.count();
}

void printVector(const std::vector<int>& vec) {
	for (size_t i = 0; i < vec.size(); ++i) {
		std::cout << vec[i];
		if (i != vec.size() - 1)
			std::cout << " ";
	}
	std::cout << std::endl;
}

void printVector(const std::vector<size_t>& vec) {
	std::cout << "Jacob vector\n";
	for (size_t i = 0; i < vec.size(); ++i) {
		std::cout << vec[i];
		if (i != vec.size() - 1)
			std::cout << " ";
	}
	std::cout << std::endl;
}

void PmergeMe::printMainChain(const string& message) {
	std::cout << message << ": ";
	for (size_t i = 0; i < _mainChainVec.size(); ++i) {
		std::cout << _mainChainVec[i];
		if (i != _mainChainVec.size() - 1)
			std::cout << " ";
	}
	std::cout << std::endl;
}

void PmergeMe::insertValue(int value) {
	_mainChainVec.push_back(value);
	_mainChainDeque.push_back(value);
}

sizetVector generateJacobsthalSequence(size_t n)
{
	sizetVector sequence = {0, 1};
	while (sequence.back() < n)
	{
		size_t next = sequence[sequence.size() - 1] + 2 * sequence[sequence.size() - 2];
		sequence.push_back(next);
	}
	return sequence;
}