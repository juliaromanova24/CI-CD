#include <ctype.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

#define _GNU_SOURCE

typedef struct {
  int b;
  int n;
  int s;
  int e;
  int t;
  int v;
} arguments;
void CatFlags(arguments *const arg, char opt);
void Flag(arguments *const arg, int argc, char **const argv);
void CountEmpty(const char current, size_t *const blankLineCounter);
void fnumber(const char previous, const char current,
             const arguments *const arg);
void fends(char current, const arguments *const arg);
void vflag(const char current, const arguments *const arg);
void ftab(const arguments *const arg);
void nextLine();
void printM(const char current, const arguments *const arg);
void printSymbol(const char current, const arguments *const arg);
void Cat(int fileCount, char **const filePath, const arguments *const arg);
void output(const char current);
