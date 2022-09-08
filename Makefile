md2latex: md2latex.o
	ld -static -s -z norelro -z noseparate-code -o md2latex md2latex.o ../md4c/md4c.o -lc
