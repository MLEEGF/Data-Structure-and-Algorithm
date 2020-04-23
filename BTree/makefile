CC:=gcc
TARGET:=main.exe
OBJS:=BTree.o main.o
$(TARGET):$(OBJS)
		$(CC) -o $@ $^
$(OBJS):%.c:%.o
		$(CC) -o $@ $^
.PHONY:rebuild clean all
rebuild:clean all
all:$(TARGET)
clean:
		$(RM) *.o $(TARGET)
