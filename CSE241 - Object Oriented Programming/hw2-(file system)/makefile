CXX = g++
CXXFLAGS = -std=c++11
TARGET = main
SRC = main.cpp shell.cpp directory.cpp

all: clean $(TARGET) run clean2

$(TARGET): $(SRC)
	@$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

run:
	@./$(TARGET)

clean:
	@rm -f $(TARGET)

clean2:
	@rm -f $(TARGET)