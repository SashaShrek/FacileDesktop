#include "hPass.h"
#include <stdio.h>
#include <gtk/gtk.h>
#include <stdlib.h>
#include "hBook.h"

//Данные и структуры
struct PassElements{
  GtkWidget *window;
  GtkEntry *password;
  GtkButton *donePass;
  GtkButton *cancelPass;
} passElems;

//Прототипы функций
void click_done(GtkButton *button, gpointer data);
void click_exit(GtkButton *button, gpointer data);

//Создание окна с вводом пароля
void create_window_pass(void){
  GError *error = NULL;
  GtkBuilder *builder;

  builder = gtk_builder_new();
  if(!gtk_builder_add_from_file(builder, "/usr/local/bin/PassGUI.ui", &error)){
    g_critical("Не могу загрузить файл passGUI.ui", error->message);
    g_error_free(error);
  }

  passElems.window = GTK_WIDGET(gtk_builder_get_object(builder, "passGUI"));
  passElems.password = GTK_ENTRY(gtk_builder_get_object(builder, "password"));
  passElems.donePass = GTK_BUTTON(gtk_builder_get_object(builder, "donePass"));
  g_signal_connect(G_OBJECT(passElems.donePass), "clicked", G_CALLBACK(click_done), 0);
  passElems.cancelPass = GTK_BUTTON(gtk_builder_get_object(builder, "cancelPass"));
  g_signal_connect(G_OBJECT(passElems.cancelPass), "clicked", G_CALLBACK(click_exit), 0);

  g_object_unref(builder);
  gtk_widget_show(passElems.window);
}

//Подтверждение пароля
void click_done(GtkButton *button, gpointer data){
  const gchar *textPass = gtk_entry_get_text(passElems.password);

  gchar *all = get_path_file("/..Conf/pass.conf");
  FILE *fp = fopen(all, "r");
  if(fp != NULL){
    gchar *password = (gchar*)calloc(4, sizeof(gchar));
    fscanf(fp, "%s", password);
    int str = 0;
    short i = 0, max = strlen(textPass);
    for(i; i < max; i++){
      str += textPass[i] << 3;
    }
    int intPassword = atoi(password);
    //!strcmp(textPass, password)
    if(intPassword == str){
      gtk_widget_destroy(passElems.window);
    }else{
      gtk_entry_set_text(passElems.password, "");
      show_message("Неверные данные! Попробуйте ещё раз");
    }
    free(password);
    fclose(fp);
  }
  free(all);
}

//Отмена ввода пароля
void click_exit(GtkButton *button, gpointer data){
  gtk_main_quit();
}
