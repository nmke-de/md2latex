MD4C_PATH = md4c/src

md2latex: md2latex.o
	ld -static -s -z norelro -z noseparate-code -o md2latex md2latex.o ../md4c/md4c.o -lc

md4c.o: $(MD4C_PATH)/md4c.c
	$(CC) -c -o $@ $^
