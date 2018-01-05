DEBUG = -g
CFLAGS = ${DEBUG} -Wall

EXEC = wc
OBJS = wc.o

all: ${EXEC}

${EXEC}: ${OBJS}
	g++ ${CFLAGS} -o ${EXEC} ${OBJS}

${OBJS}: %.o: %.cpp
	g++ ${CFLAGS} -c -o $@ $<

clean:
	rm -f ${EXEC} ${OBJS}
