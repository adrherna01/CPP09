#include <iostream>
#include <map>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using string = std::string;
using valueMap = std::multimap<string, float>;
using valuePair = std::pair<string, float>;

class BitcoinExchange {
	private:
		valueMap _dataBaseMap;
		valueMap _inputMap;

	public:
		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange& other);
		BitcoinExchange& operator=(const BitcoinExchange& other);
		~BitcoinExchange();

		void parseDataBase(const string& fileName);
		void parseInputFile(const string& fileName);
		void calculateValues();

		// This one returns the closest value if not found (lower one)
		void printMatch(const valuePair& pair);
		void findClosest();

		void parseLineDataBase(const string& line);
		void parseLineInputFile(const string& line);
		void printMap();
};

bool isDateValid(const string& date);
bool isValueValid(const string& value);

string trim(const std::string& str);
bool isNumeric(const std::string& str);
bool isValidFormat(const std::string& value);
std::vector<std::string> split(const std::string& str, char delimiter);