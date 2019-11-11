CC = gcc
TARGET = casino

all: casino

casino:
	$(CC) $(TARGET).c -o $(TARGET) -fno-stack-protector -z execstack

clean:
	rm $(TARGET)
