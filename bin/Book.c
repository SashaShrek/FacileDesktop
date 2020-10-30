#include <stdio.h>
#include <string.h>
#include <gtk/gtk.h>
#include <stdlib.h>
#include "hBook.h"

char* get_path_file(char *nameFileConf){
  const char *pathDir = g_get_home_dir();
  size_t sizePathDir = strlen(pathDir);
  size_t sizeNameFileConf = strlen(nameFileConf);
  char *outcome = (char*)calloc(sizePathDir + sizeNameFileConf, sizeof(char));
  strncpy(outcome, pathDir, sizePathDir);
  strncpy(outcome + sizePathDir, nameFileConf, sizeNameFileConf);
  return outcome;
}

void show_message(char *text){
  GtkDialogFlags flags = GTK_DIALOG_DESTROY_WITH_PARENT;
  GtkWidget *dialog = gtk_message_dialog_new (NULL,
                                  flags,
                                  GTK_MESSAGE_ERROR,
                                  GTK_BUTTONS_CLOSE,
                                  text);
  gtk_dialog_run (GTK_DIALOG (dialog));
  gtk_widget_destroy (dialog);
}
