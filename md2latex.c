#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include "md4c/src/md4c.h"

#define print(str) write(1, (str), strlen((str)))
#define printl(str, limit) write(1, (str), (limit))

int enter_block (MD_BLOCKTYPE t, void *details, void *userdata) {
	switch (t) {
		case MD_BLOCK_DOC:
			print("\\begin{document}\n");
			break;
		case MD_BLOCK_QUOTE:
			print("\\begin{displayquote}\n");
			break;
		case MD_BLOCK_UL:
			print("\\begin{itemize}\n");
			break;
		case MD_BLOCK_OL:
			print("\\begin{enumerate}\n");
			break;
		case MD_BLOCK_LI:
			print("\\item\t");
			break;
		case MD_BLOCK_HR:
			print("\\hrulefill\n");
			break;
		case MD_BLOCK_H:
			print("\\section{");
			break;
		case MD_BLOCK_P:
			print("\n");
			break;
		default:
			print("");
	}
	return 0;
}

int leave_block (MD_BLOCKTYPE t, void *details, void *userdata) {
	switch (t) {
		case MD_BLOCK_DOC:
			print("\\end{document}\n");
			break;
		case MD_BLOCK_QUOTE:
			print("\\end{displayquote}\n");
			break;
		case MD_BLOCK_UL:
			print("\\end{itemize}\n");
			break;
		case MD_BLOCK_OL:
			print("\\end{enumerate}\n");
			break;
		case MD_BLOCK_LI:
			print("\n");
			break;
		case MD_BLOCK_HR:
			break;
		case MD_BLOCK_H:
			print("}");
			break;
		case MD_BLOCK_P:
			print("\n");
			break;
		default:
			print("");
	}
	return 0;
}

int enter_span (MD_SPANTYPE t, void *details, void *userdata) {
	switch (t) {
		case MD_SPAN_EM:
			print("\\emph{");
			break;
		case MD_SPAN_STRONG:
			print("\\textbf{");
			break;
		case MD_SPAN_A:
			print("");
			break;
		case MD_SPAN_IMG:
			print("\\begin{figure}\n");
			print("\\includegraphics[line=\\linewidth]{");
			struct MD_SPAN_IMG_DETAIL *d = (struct MD_SPAN_IMG_DETAIL *) details;
			printl(d->src.text, d->src.size);
			print("}\n");
			break;
		case MD_SPAN_CODE:
			print("\\verb!");
			break;
		case MD_SPAN_DEL:
			print("");
			break;
		case MD_SPAN_LATEXMATH:
		case MD_SPAN_LATEXMATH_DISPLAY:
			print("$");
			break;
		case MD_SPAN_WIKILINK:
			print("");
			break;
		case MD_SPAN_U:
			print("\\underline{");
			break;
	}
	return 0;
}

int leave_span (MD_SPANTYPE t, void *details, void *userdata) {
	switch (t) {
		case MD_SPAN_CODE:
			print("!");
			break;
		case MD_SPAN_LATEXMATH:
		case MD_SPAN_LATEXMATH_DISPLAY:
			print("$");
			break;
		case MD_SPAN_IMG:
			print("\n\\end{figure}\n");
			break;
		default:
			print("}");
	}
	return 0;
}

static inline int text (MD_TEXTTYPE t, const MD_CHAR *str, MD_SIZE size, void *userdata) {
	switch (t) {
		case MD_TEXT_NORMAL:
			printl(str, size);
			break;
		case MD_TEXT_NULLCHAR:
			print("<?>");
			break;
		case MD_TEXT_BR:
			printl(str, size);
			break;
		case MD_TEXT_ENTITY:
			printl(str, size);
			break;
		case MD_TEXT_CODE:
			printl(str, size);
			break;
		case MD_TEXT_HTML:
			break;
		case MD_TEXT_LATEXMATH:
			printl(str, size);
			break;
		default:
			break;
	}
	return 0;
}

int main(int argc, char **argv) {
	int fd = argc > 1 ? open(argv[1], O_RDONLY) : -1;
	if (fd == -1) return 1;
	int len = lseek(fd, 0, SEEK_END);
	lseek(fd, 0, SEEK_SET);
	MD_PARSER p = {
		0,
		0,
		enter_block,
		leave_block,
		enter_span,
		leave_span,
		text,
		NULL,
		NULL
	};
	char *input = malloc(sizeof(char) * len);
	read(fd, input, len);
	close(fd);
	print("\\documentclass{article}\n");
	print("\\usepackage{graphicx}\n");
	md_parse(input, strlen(input), &p, NULL);
	free(input);
}
