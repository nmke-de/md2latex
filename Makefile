MD4C_PATH = md4c/src

build: md2latex.o md4c.o
	$(CC) -s -o md2latex md2latex.o md4c.o -lc

md2latex: md2latex.o md4c.o
	ld -static -s -z norelro -z noseparate-code -o md2latex md2latex.o md4c.o /opt/diet/lib-x86_64/libc.a

md4c.o: $(MD4C_PATH)/md4c.c
	$(CC) -c -o $@ $^

example: md2latex
	./md2latex README.md > README.tex
	latexmk -pdf

clean:
	rm -f md2latex *.o *.aux *.fdb_latexmk *.fls *.log *.pdf *.tex
