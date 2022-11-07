CC=g++
CFLAGS=-Iheaders --std=c++11 -g
OBJS = system.o main.o pipeline.o simulator.o dram.o iport.o dport.o arbiter.o cache.o
TARGET = demo

.PHONY : clean run all

all : clean $(TARGET) run

%.o : %.cpp
	$(CC) -c -o $@ $< $(CFLAGS)

$(TARGET) : $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)

clean :
	rm -rf $(TARGET)
	rm -rf *.o
	rm -f result.txt

run :
	./$(TARGET) >> result.txt
