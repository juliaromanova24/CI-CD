#include "s21_cat.h"
#define _GNU_SOURCE
const struct option long_options[] = {
    {"number", no_argument, NULL, 'n'},
    {"number-nonblank", no_argument, NULL, 'b'},
    {"squeeze", no_argument, NULL, 's'},
    {"ends", no_argument, NULL, 'e'},
    {"tabs", no_argument, NULL, 't'},
    {"nonprinting", no_argument, NULL, 'v'},
    {0, 0, 0, 0}};

void CatFlags(arguments *const arg, char opt) {
  switch (opt) {
    case 'b':
      arg->b = 1;
      arg->n = 0;
      break;
    case 'n':
      if (!arg->b) {
        arg->n = 1;
      }
      break;
    case 's':
      arg->s = 1;
      break;
    case 'E':
      arg->e = 1;
      break;
    case 'e':
      arg->e = 1;
      arg->v = 1;
      break;
    case 'T':
      arg->t = 1;
      break;
    case 't':
      arg->t = 1;
      arg->v = 1;
      break;
    case 'v':
      arg->v = 1;
      break;
    case '?':
      perror("Ошибка");
      exit(1);
    default:
      perror("Ошибка");
      exit(EXIT_FAILURE);
  }
}
void Flag(arguments *const arg, int argc, char **const argv) {
  int opt;
  while ((opt = getopt_long(argc, argv, "bnEestv", long_options, NULL)) != -1) {
    CatFlags(arg, opt);
  }
}

void CountEmpty(const char current, size_t *const blankLineCounter) {
  if (current == '\n') {
    (*blankLineCounter)++;
  } else {
    *blankLineCounter = 0;
  }
}

void fnumber(const char previous, const char current,
             const arguments *const arg) {
  static size_t lineCount = 0;
  if (arg->b && previous == '\n' && current != '\n') {
    fprintf(stdout, "%6zu\t", ++lineCount);
  } else if (arg->n && previous == '\n') {
    fprintf(stdout, "%6zu\t", ++lineCount);
  }
  if (arg->b && arg->e && previous == '\n' && current == '\n') {
    fputs("      \t", stdout);
  }
}

void fends(char current, const arguments *const arg) {
  if (arg->e && current == '\n') {
    fputc('$', stdout);
  }
}

void vflag(const char current, const arguments *const arg) {
  if (arg->v) {
    fputc('^', stdout);
    if (current == 127) {
      fputc(current - 64, stdout);
    } else {
      fputc(current + 64, stdout);
    }
  } else {
    fputc(current, stdout);
  }
}
void ftab(const arguments *const arg) {
  if (arg->t) {
    fputc('^', stdout);
    fputc('\t' + 64, stdout);
  } else {
    fputc('\t', stdout);
  }
}
void nextLine() { fputc('\n', stdout); }

void printM(const char current, const arguments *const arg) {
  if (arg->v) {
    const char MSymbol = (signed char)current + 128;
    fputc('M', stdout);
    fputc('-', stdout);
    if (isprint(MSymbol)) {
      fputc(MSymbol, stdout);
    } else {
      vflag(MSymbol, arg);
    }
  } else {
    fputc(current, stdout);
  }
}

void printSymbol(const char current, const arguments *const arg) {
  if (isprint(current)) {
    fputc(current, stdout);
  } else if (current == '\t') {
    ftab(arg);
  } else if (current == '\n') {
    nextLine();
  } else if (iscntrl(current)) {
    vflag(current, arg);
  } else {
    printM(current, arg);
  }
}

void Cat(int fileCount, char **const filePath, const arguments *const arg) {
  for (int i = 0; i < fileCount; i++) {
    FILE *file = fopen(filePath[i], "r");
    if (file == NULL) {
      perror("Ошибка открытия файла");
      continue;
    }

    size_t blankLineCounter = 1;
    char previous = '\n';
    int current = fgetc(file);

    while (current != EOF) {
      if (arg->s) {
        CountEmpty((char)current, &blankLineCounter);
      }
      if ((char)current != '\n' || blankLineCounter <= 2) {
        fnumber(previous, (char)current, arg);
        fends((char)current, arg);
        printSymbol((char)current, arg);
      }

      previous = (char)current;
      current = fgetc(file);
    }

    fclose(file);
  }
}
void output(const char current) { fputc(current, stdout); }
int main(int argc, char **argv) {
  arguments arg = {0};

  if (argc < 2) {
    fprintf(stderr, "Недостаточно аргументов\n");
    return 1;
  }

  Flag(&arg, argc, argv);

  Cat(argc - optind, argv + optind, &arg);

  return 0;
}
