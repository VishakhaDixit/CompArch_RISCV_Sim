CC=g++
CFLAGS=-Iheaders --std=c++11 -g
OBJS = system.o main.o
TARGET = demo

.PHONY : clean run all

all : clean $(TARGET) run

%.o : %.cpp
	$(CC) -c -o $@ $< $(CFLAGS)
	#g++ -c -o helloworld.o helloworld.cpp -Iheaders --std=c++11

$(TARGET) : $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)
	#g++ -o demo helloworld.o -Iheaders --std=c++11

clean :
	rm -rf $(TARGET)
	rm -rf *.o

run :
	./$(TARGET)
