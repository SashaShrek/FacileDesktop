#include "hOnPass.h"
#include <gtk/gtk.h>
#include <stdio.h>

#define PATH_CONF "Conf/pass.conf"

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
gchar* concat(gchar *str1, const gchar *str2);

//Создание окна установки пароля
void create_window_onpass(GtkSwitch *switchPass){
    GtkBuilder *builder = NULL;
    GError *error = NULL;

    builder = gtk_builder_new();
    if(!gtk_builder_add_from_file(builder, "OnPassGUI.ui", &error)){
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
        GtkDialogFlags flags = GTK_DIALOG_DESTROY_WITH_PARENT;
        GtkWidget *dialog = gtk_message_dialog_new (NULL,
                                        flags,
                                        GTK_MESSAGE_ERROR,
                                        GTK_BUTTONS_CLOSE,
                                        "Пароль должен быть не менее 4 символов в длину!");
        gtk_dialog_run (GTK_DIALOG (dialog));
        gtk_widget_destroy (dialog);
        return ;
    }
    const gchar *textPass = gtk_entry_get_text(onPassElems.password);
    FILE *fp = fopen(PATH_CONF, "a");
    if(fp != NULL){
      gchar *str = "pass:";
      gchar *s = concat(str, textPass);
      fputs(s, fp);
      fclose(fp);
      *s = 0;
      free(s);
    }
    gtk_widget_destroy(GTK_WIDGET(onPassElems.window));
}

//Нажатие кнопки отмена
void click_cancel(GtkButton *button, gpointer data){
    gtk_switch_set_state(GTK_SWITCH(data), FALSE);
    gtk_widget_destroy(GTK_WIDGET(onPassElems.window));
}

//Объединение строк
gchar* concat(gchar *str1, const gchar *str2){
  int size_1 = strlen(str1);
  int size_2 = strlen(str2);
  gchar *all = malloc(sizeof(size_1 + size_2 + 1));
  memcpy(all, str1, size_1);
  memcpy(all + size_1, str2, size_2);
  return all;
}
