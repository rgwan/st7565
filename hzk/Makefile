all: hzk out.h

out.h: hzk list.txt
	./hzk list.txt out.h
hzk: main.c
	$(CC) main.c -o hzk

clean:
	rm -f hzk out.h
