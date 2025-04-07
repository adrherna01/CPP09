#include "BitcoinExchange.hpp"
#include <string>

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other) {
	_dataBaseMap = other._dataBaseMap;
	_inputMap = other._inputMap;
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other) {
	_dataBaseMap = other._dataBaseMap;
	_inputMap = other._inputMap;
	return (*this);
}

BitcoinExchange::~BitcoinExchange() {}

void BitcoinExchange::printMatch(const valuePair& pair) {

	string inputDate = pair.first;
	float inputValue = pair.second;

	if (!isDateValid(inputDate))
	{
		std::cout << "Error: Date is Invalid (Input file) => " << inputDate << std::endl;
		return;
	} else if (!isValueValid(std::to_string(inputValue))) {
		std::cout << "Error: Bad Input (Input file) => " << inputValue << std::endl;
		return;
	} else if ( inputValue > 1000) {
		std::cout << "Error: too large a number (Input file) => " << inputValue << std::endl;
		return;
	}

	valueMap::iterator it =  _dataBaseMap.find(inputDate);
	if ((it != _dataBaseMap.end()))
	{
		// std::cout << it->second  << " * " << inputValue << std::endl;
		std::cout << inputDate << " => " << inputValue << " = " << it->second * inputValue << std::endl;
	}
	else
	{
		valuePair pairCopy = pair;
		_dataBaseMap.insert(pairCopy);
		it =  _dataBaseMap.find(inputDate);
		if (it != _dataBaseMap.begin())
			it--;
		else
			it++;

		// std::cout << it->second  << " * " << inputValue << std::endl;
		std::cout << inputDate << " => " << inputValue << " = " << inputValue * it->second << std::endl;
		_dataBaseMap.erase(pairCopy.first);
	}
}

void BitcoinExchange::calculateValues() {
	string inputDate;

	if (_dataBaseMap.empty() || _inputMap.empty())
		return;

	for (const auto& pair : _inputMap)
	{
		printMatch(pair);
	}
}

void BitcoinExchange::parseLineDataBase(const string& line) {
	size_t commaPos = line.find(',');
	// Check if no comma was found or no value after the comma

	string date = trim(line.substr(0, commaPos));
	string value = trim(line.substr(commaPos + 1));

	// std::cout << "|" << date << "|" << std::endl;
	// std::cout << "|" << value << "|" << std::endl;

	if (!isDateValid(date))
	{
		std::cout << "Error: Bad Input (DB) => " << date << std::endl;
		return;
	} else if (!isValueValid(value)) {
		std::cout << "Error: Bad Input (DB) => " << value << std::endl;
		return;
	}

	float fValue = std::stof(value);
	_dataBaseMap.insert(valuePair(date, fValue));
	// std::cout << std::endl;
}

void BitcoinExchange::parseDataBase(const string& fileName) {
	std::ifstream	file(fileName);
	string			line;

	if (!file.is_open()) {
		std::cout << "DB file could not be opened" << std::endl;
		return;
	}

	std::getline(file, line);

	while (std::getline(file, line))
	{
		// std::cout << line << std::endl;
		parseLineDataBase(line);
	}
}

void BitcoinExchange::parseLineInputFile(const string& line) {
	size_t commaPos = line.find('|');

	string date = trim(line.substr(0, commaPos));
	string value = trim(line.substr(commaPos + 1));
	float fValue = std::stof(value);

	_inputMap.insert(valuePair(date, fValue));
}

void BitcoinExchange::parseInputFile(const string& fileName) {
	std::ifstream	file(fileName);
	string			line;

	if (!file.is_open()) {
		std::cout << "Input file could not be opened" << std::endl;
		return;
	}

	std::getline(file, line);

	while (std::getline(file, line))
	{
		// Might to a try catch here an throw and error for bad formating
		parseLineInputFile(line);
	}
}

void BitcoinExchange::printMap() {
	for (auto& pair : _inputMap)
	{
		std::cout << "-   Key: " << pair.first << std::endl;
		std::cout << "- Value: " << pair.second << std::endl;
	}
}

bool isDateValid(const string& date)
{
	std::vector<string> strVector;

	strVector = split(date, '-');

	if (stoi(strVector[0]) > 2025 || stoi(strVector[1]) > 12  || stoi(strVector[2]) > 31)
		return false;

	for (auto& word : strVector)
	{
		// std::cout << word << std::endl;
		if (!isNumeric(word))
			return false;
	}
	return true;
}

bool isValueValid(const string& value) {
	if (!isNumeric(value) || !isValidFormat(value))
		return false;
	return true;
}

string trim(const std::string& str) {
	size_t start = 0;
	while (start < str.length() && std::isspace(str[start])) {
		start++;
	}

	size_t end = str.length();
	while (end > start && std::isspace(str[end - 1])) {
		end--;
	}

	return str.substr(start, end - start);

}

bool isNumeric(const std::string& str) {
	int i = 0;
	int len = str.length();
	for (char ch : str)
	{
		if (ch == '.' && i != 0 && i != len -1)
		continue;
	if (!std::isdigit(ch))
		{
			// std::cout << ch << std::endl;
			return false;
		}
		i++;
	}
	return true;
}

bool isValidFormat(const std::string& value)
{
	int count = std::count(value.begin(), value.end(), '.');
	if (count > 1)
		return false;
	return true;
}

std::vector<std::string> split(const std::string& str, char delimiter) {
	std::vector<std::string> result;
	std::stringstream ss(str);
	std::string item;

	while (std::getline(ss, item, delimiter)) {
		result.push_back(item);
	}

	return result;
}
