#include <iostream>
#include <vector>
#include <deque>
#include <chrono>

using TimePoint = std::chrono::high_resolution_clock::time_point;
using string = std::string;
using vector = std::vector<int>;
using sizetVector = std::vector<size_t>;
using deque = std::deque<int>;

class PmergeMe {
	private:
		vector _mainChainVec;
		vector _secondaryChainVec;

		deque _mainChainDeque;
		deque _secondaryChainDeque;

		TimePoint _vectorStart;
		TimePoint _vectorEnd;

		TimePoint _dequeStart;
		TimePoint _dequeEnd;

	public:
		PmergeMe() = default;
		PmergeMe(const PmergeMe& other);
		PmergeMe& operator=(const PmergeMe& other);
		~PmergeMe() = default;

		sizetVector generateJacobsthalInsertionOrder();

		void algorithmVec();
		void separatePairsVec();
		void binaryInsertionVec();
		// void binaryInsertionVec(vector& mainChain, vector& secChain);
		void insertSingleElementVec(int value);
		void setVecInit();
		void setVecFinish();
		long long calculateDurationVec();

		void algorithmDeque();
		void separatePairsDeque();
		void binaryInsertionDeque();
		void insertSingleElementDeque(int value);
		void setDequeInit();
		void setDequeFinish();
		long long calculateDurationDeque();

		void printMainChain(const string& message);
		void insertValue(int value);

	};

	TimePoint getTime();
	sizetVector generateJacobsthalSequence(size_t n);
	void printVector(const vector& vec);
	void printVector(const sizetVector& vec);
	bool isNumeric(const std::string& str);