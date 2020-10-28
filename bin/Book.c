#include <string.h>
#include <gtk/gtk.h>
#include <stdio.h>
#include "hBook.h"

//Проверка на существование
int get_target(FILE *file, char *target){
  gchar *str = malloc(sizeof(*str));
  fscanf(file, "%s", str);
  gchar targetStr[strlen(str)];
  int i = 0;
  while(str[i] != ':'){
    targetStr[i] = str[i];
    i++;
  }
  
  if(strcmp(targetStr, target) == 0){
    return 1;
  }
  free(str);
  return 0;
}
