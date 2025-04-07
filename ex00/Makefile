CXX = c++

CXXFLAGS = -Werror -Wall -Wextra -std=c++17

TARGET = main

SRCS = main.cpp BitcoinExchange.cpp

OBJS = $(SRCS:.cpp=.o)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(TARGET)

re: fclean $(TARGET)

.PHONY: clean fclean re%%%