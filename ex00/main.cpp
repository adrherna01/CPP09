#include "BitcoinExchange.hpp"
#include <filesystem>

int main (int argc, char **argv)
{
	if (argc > 2) {
		std::cout << "Too many arguments" << std::endl;
	} else if (!std::filesystem::exists(argv[1])) {
		std::cout << "Input file does not exist" << std::endl;
	}

	BitcoinExchange btc;
	btc.parseDataBase("data.csv");
	btc.parseInputFile(argv[1]);
	btc.calculateValues();
}