CXX = g++
CXXFLAGS = -std=c++11
TARGET = main
SRC = main.cpp piece.cpp board.cpp
	
all: clean $(TARGET) run

$(TARGET): $(SRC)
	@$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

run:
	@./$(TARGET)

clean:
	@rm -f $(TARGET)
 