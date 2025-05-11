#include "s21_grep.h"

void grep(int argc, char **argv) {
  if (argc == 1) {
    fprintf(stderr, "\n");
  } else if (argc > 1) {
    char *pattern = NULL;
    arguments arg = {0};
    flags(argc, argv, &arg, &pattern);

    int fileCount = argc - optind;
    for (int i = optind; i < argc; i++) {
      int numberline = 0;
      int countMatch = 0;
      FILE *file = fopen(argv[i], "r");
      if (file != NULL) {
        findmatches(&arg, file, argv[i], pattern, &numberline, &countMatch,
                    fileCount);
        fclose(file);
      } else if (!arg.s) {
        fprintf(stderr, "No such file or directory\n");
      }
    }
    if (pattern) {
      free(pattern);
    }
  }
}

void flags(int argc, char **argv, arguments *arg, char **pattern) {
  while (1) {
    int opt = getopt(argc, argv, "e:ivclnhsf:o");
    if (opt == -1) {
      break;
    }

    switch (opt) {
      case 'i':
        arg->i = 1;
        break;
      case 'v':
        arg->v = 1;
        break;
      case 'c':
        arg->c = 1;
        break;
      case 'l':
        arg->l = 1;
        break;
      case 'n':
        arg->n = 1;
        break;
      case 'h':
        arg->h = 1;
        break;
      case 's':
        arg->s = 1;
        break;
      case 'o':
        arg->o = 1;
        break;
      case '?':
      default:
        exit(EXIT_FAILURE);
    }
  }
  if (!arg->e && !arg->f) {
    if (optind < argc) {
      *pattern = strdup(argv[optind]);
      optind++;
    } else {
      fprintf(stderr, "\n");
      exit(EXIT_FAILURE);
    }
  }
}

void fFlag(arguments *arg, char **pattern, const char *filename) {
  FILE *file = fopen(filename, "r");
  if (file != NULL) {
    char line[5000];
    while (fgets(line, sizeof(line), file) != NULL) {
      line[strcspn(line, "\n")] = 0;
      if (*pattern == NULL) {
        *pattern = strdup(line);
      } else {
        *pattern = realloc(*pattern, strlen(*pattern) + strlen(line) + 2);
        strcat(strcat(*pattern, "|"), line);
      }
    }
    fclose(file);
  } else if (!arg->s) {
    fprintf(stderr, "No such file or directory\n");
  }
}
void eFlag(char **pattern, const char *template) {
  if (*pattern == NULL) {
    *pattern = strdup(template);
  } else {
    *pattern = realloc(*pattern, strlen(*pattern) + strlen(template) + 2);
    strcat(strcat(*pattern, "|"), template);
  }
}

void findmatches(arguments *arg, FILE *file, const char *filename,
                 const char *pattern, int *numberline, int *countMatch,
                 int fileCount) {
  regex_t regex;
  int match = 1;
  if (pattern != NULL) {
    match = regcomp(&regex, pattern, arg->i ? REG_ICASE : REG_EXTENDED);
  } else {
    fprintf(stderr, "Ошибка компиляции regex\n");
    exit(EXIT_FAILURE);
  }
  if (match) {
    fprintf(stderr, "Ошибка компиляции regex\n");
    exit(EXIT_FAILURE);
  }
  char line[5000];
  while (fgets(line, sizeof(line), file) != NULL) {
    (*numberline)++;
    line[strcspn(line, "\n")] = 0;
    match = regexec(&regex, line, 0, NULL, 0);
    int coincidence;
    if (match == 0) {
      coincidence = 1;
    } else {
      coincidence = 0;
    }
    if (arg->v) {
      coincidence = !coincidence;
    }
    if (coincidence) {
      (*countMatch)++;
      if (arg->c == 0 && arg->l == 0) {
        output(arg, line, filename, *numberline, fileCount, pattern);
      }
    }
  }
  if (arg->c && arg->l) {
    if (arg->c && fileCount == 1)
      printf("1\n");
    else if (arg->c && fileCount > 1)
      printf("%s:1\n", filename);
    else
      printf("0\n");
  }
  if (arg->c && !arg->l) {
    if (fileCount > 1 && !arg->h) {
      printf("%s:", filename);
    }
    printf("%d\n", *countMatch);
  }
  if (arg->l && *countMatch) {
    printf("%s\n", filename);
  }
  regfree(&regex);
}

void output(arguments *arg, const char *line, const char *filename,
            int numberline, int fileCount, const char *pattern) {
  if (arg->o) {
    regex_t regex;
    regcomp(&regex, pattern, arg->i ? REG_ICASE : REG_EXTENDED);
    regmatch_t coincidence;
    const char *p = line;
    int first_coincidence = 1;
    while (regexec(&regex, p, 1, &coincidence, 0) == 0) {
      if (first_coincidence) {
        first_coincidence = 0;
      }
      if (fileCount > 1 && !arg->h) {
        printf("%s:", filename);
      }
      if (arg->n) {
        printf("%d:", numberline);
      }
      for (int i = coincidence.rm_so; i < coincidence.rm_eo; i++) {
        putchar(p[i]);
      }
      putchar('\n');
      p += coincidence.rm_eo;
      if (*p == '\0') {
        break;
      }
    }
    regfree(&regex);
  } else {
    if (fileCount > 1 && !arg->h) {
      printf("%s:", filename);
    }
    if (arg->n) {
      printf("%d:", numberline);
    }
    printf("%s\n", line);
  }
}
int main(int argc, char **argv) {
  grep(argc, argv);
  return 0;
}
