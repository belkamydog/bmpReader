CC=g++
WWW=-Wall -Werror -Wextra
SRC=`find . -name '*.cc'`
H=`find . -name '*.h'`
DEST=build/bmp_reader.out

all: clean app

app:
	mkdir -p build
	$(CC) $(WWW) $(SRC) -o $(DEST)
	./$(DEST)

style:
	clang-format -i $(SRC) $(H);

memcheck:
	leaks -atExit -- ./$(DEST)

clean:
	rm -rf build