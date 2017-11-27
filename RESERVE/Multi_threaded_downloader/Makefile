SRC=main.c download.c
FLAGS=`xml2-config --cflags` `xml2-config --libs` -std=c99 -D_GNU_SOURCE -pthread
NAME=std
CONF=file
LIB=/usr/include/libxml2/libxml

all: $(NAME)

$(NAME): main.o download.o
	gcc $(FLAGS) $(SRC) -o $(NAME) -lxml2 -lcurl

main.o: main.c std.h
	gcc -c main.c -I $(LIB) $(FLAGS)

download.o: download.c std.h
	gcc -c download.c -I $(LIB) $(FLAGS) `curl-config --libs` -lcurl

install: $(NAME)
	cp $(NAME) /usr/bin

clean:
	@rm -f main.o
	@rm -f download.o

fclean: clean
	@rm -f $(NAME)

re: fclean all
