CC=gcc
CFLAGS=-Wall -W -O3 -fPIC -pipe -g
LDFLAGS=-shared -lblitz -lboost_python -lpython2.6 -L core -llss
SRCDIR=./
LIB=pylss.so
INCLUDE=/usr/include/python2.6
SRC= $(wildcard $(SRCDIR)/*.cpp)
OBJ= $(SRC:.cpp=.o)

all: $(LIB)

$(LIB): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CC) -o $@ -c $< $(CFLAGS) -I $(INCLUDE)

clean:
	rm -rf $(SRCDIR)/*.o *.so
