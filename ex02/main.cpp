#include "PmergeMe.hpp"
#include <cstddef>



int main (int argc, char **argv) {
	int i = 1;
	int value;
	PmergeMe program;

	if (argc < 2)
		return 0;

	while (argv[i] != NULL)
	{
		if (!isNumeric(argv[i]))
		{
			std::cout << "Invalid arguments" << std::endl;
			return 1;
		}

		value = std::stoi(argv[i]);
		program.insertValue(value);
		i++;
	}
	program.printInitVector();

	program.algorithm();

	program.printInitVector();

}