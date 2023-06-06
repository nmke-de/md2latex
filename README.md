# md2latex

**md2latex** is a simple (and perhaps very primitive) [Markdown](https://github.com/adam-p/markdown-here/wiki/Markdown-Cheatsheet) to [Latex](https://en.wikibooks.org/wiki/LaTeX) compiler. Currently in early development.

## But why?

Write your thesis in Markdown! Or perhaps something else, idk.

### What about pandoc?

Pandoc does the job too, and it is more advanced, but take a look at the number of dependencies:

![full screen terminal window filled to the brim with pandoc dependencies](pandoc-dependencies.png)

So many dependencies scare me!

## Build

Type `make`. To build on Linux with dietlibc, type `make md2latex` instead.

## Usage

md2latex takes a single argument, the path of the markdown file, and prints the corresponding latex to stdout. You may want to pipe that output into a file.

```bash
md2latex file.md > file.tex
```

The generated file can then be used by utilities provided by [TeXLive](https://www.tug.org/texlive/) to generate i.e. a pdf.

```bash
latexmk -pdf
```
