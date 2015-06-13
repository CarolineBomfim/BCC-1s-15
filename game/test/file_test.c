#include <stdio.h>

int main(int argc, char **argv) {
  printf("File read: %s\n", argv[1]);
  FILE *arquivo;
  arquivo = fopen(argv[1], "r");
  printf("Arquivo carregado\n");
  char *a;
  while(1) {
    fscanf(arquivo, "%s", a);
    if(a == NULL) {
      break;
    }
    printf("%s\n", a);
  }
  fclose(arquivo);
  return 0;
}