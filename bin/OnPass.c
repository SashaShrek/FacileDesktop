#include "hOnPass.h"
#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include "hBook.h"

//Хранение данных
struct OnPassElems{
    GtkWidget *window;
    GtkButton *donePass;
    GtkButton *closeWindowPass;
    GtkEntry *password;
} onPassElems;

//Прототипы функций
void click_done_task(GtkButton *button, gpointer data);
void click_cancel(GtkButton *button, gpointer data);

//Создание окна установки пароля
void create_window_onpass(GtkSwitch *switchPass){
    GtkBuilder *builder = NULL;
    GError *error = NULL;

    builder = gtk_builder_new();
    if(!gtk_builder_add_from_file(builder, "/usr/local/bin/OnPassGUI.ui", &error)){
        g_critical("Невозможно загрузить файл: %s", error->message);
        g_error_free(error);
    }

    onPassElems.window = GTK_WIDGET(gtk_builder_get_object(builder, "onPass"));
    onPassElems.donePass = GTK_BUTTON(gtk_builder_get_object(builder, "donePass"));
    g_signal_connect(G_OBJECT(onPassElems.donePass), "clicked", G_CALLBACK(click_done_task), NULL);
    onPassElems.password = GTK_ENTRY(gtk_builder_get_object(builder, "password"));
    onPassElems.closeWindowPass = GTK_BUTTON(gtk_builder_get_object(builder, "closeWindowPass"));
    g_signal_connect(G_OBJECT(onPassElems.closeWindowPass), "clicked", G_CALLBACK(click_cancel), switchPass);

    if(!onPassElems.window || !onPassElems.donePass || !onPassElems.password){
        g_critical("Не могу получить объект окна или других элементов");
    }
    g_object_unref(builder);
    gtk_widget_show(onPassElems.window);
}

//Нажатие кнопки Подтвердить
void click_done_task(GtkButton *button, gpointer data){
    guint16 lengthTextPass = gtk_entry_get_text_length(onPassElems.password);
    if(lengthTextPass < 4){
        show_message("Пароль должен быть не менее 4 символов в длину!");
        return ;
    }
    const gchar *textPass = gtk_entry_get_text(onPassElems.password);
    const gchar *path = g_get_home_dir();
    gchar *nameFile = "/..Conf/pass.conf";
    gchar *all = malloc(strlen(path) + strlen(nameFile) + 1);
    memcpy(all, path, strlen(path));
    memcpy(all + strlen(path), nameFile, strlen(nameFile));
    FILE *fp = fopen(all, "w");
    if(fp != NULL){
      int a = 0;
      short i = 0, max = strlen(textPass);
      for(i; i < max; i++){
        a += textPass[i] << 3;
      }
      char *str;
      sprintf(str, "%d", a);
      fputs(str, fp);
      fclose(fp);
    }else{
      g_critical("Не могу создать файл!");
    }
    free(all);
    gtk_widget_destroy(GTK_WIDGET(onPassElems.window));
}

//Нажатие кнопки отмена
void click_cancel(GtkButton *button, gpointer data){
    gtk_switch_set_state(GTK_SWITCH(data), FALSE);
    gtk_widget_destroy(GTK_WIDGET(onPassElems.window));
}
