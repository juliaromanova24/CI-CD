#ifndef S21_GREP_H
#define S21_GREP_H
#define _GNU_SOURCE
#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct arguments {
  int e;
  int i;
  int v;
  int c;
  int l;
  int n;
  int h;
  int s;
  int f;
  int o;
} arguments;

void flags(int argc, char **argv, arguments *arg, char **pattern);
void grep(int argc, char **argv);
void findmatches(arguments *arg, FILE *file, const char *filename,
                 const char *pattern, int *numberline, int *countMatch,
                 int fileCount);
void fFlag(arguments *arg, char **pattern, const char *filename);
void eFlag(char **pattern, const char *template);
void output(arguments *arg, const char *line, const char *filename,
            int numberline, int fileCount, const char *pattern);

#endif
