#include <gtk/gtk.h>
#include <stdio.h>
#include "hSettings.h"
#include "hAddTask.h"
#include <string.h>
#include "hPass.h"
#include "hBook.h"
#include <stdlib.h>

//Структуры и данные
struct Elements{
    GtkButton *doneTask;
    GtkButton *addTask;
    GtkButton *settings;
} elements;
//

//Прототипы функций
static GtkWidget* create_window(void);
void click_buttons(GtkButton *button, gpointer data);
void add_signals(void);
//

//Главная функция
int main(int argc, char *argv[]){
    GtkWidget *window;
    gtk_init(&argc, &argv);
    window = create_window();
    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_widget_show(window);

    gchar *all = get_path_file("/..Conf/pass.conf");
    FILE *fp = fopen(all, "r");
    if(fp != NULL){
      fclose(fp);
      create_window_pass();
    }
    free(all);

    gtk_main();
    return 0;
}

//Создание главного окна из файла .ui
static GtkWidget* create_window(void){
    GtkWidget *window;
    GtkBuilder *builder;
    GError *error = NULL;

    builder = gtk_builder_new();
    if(!gtk_builder_add_from_file(builder, "/usr/local/bin/MainGUI.ui", &error)){
      g_critical("Невозможно загрузить файл: %s", error->message);
      g_error_free(error);
    }

    gtk_builder_connect_signals(builder, NULL);

    window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
    elements.doneTask = GTK_BUTTON(gtk_builder_get_object(builder, "doneTask"));
    elements.addTask = GTK_BUTTON(gtk_builder_get_object(builder, "addTask"));
    elements.settings = GTK_BUTTON(gtk_builder_get_object(builder, "settings"));

    if(!window || !elements.doneTask || !elements.addTask || !elements.settings){
        g_critical("Не могу получить объект окна или кнопки");
    }

    add_signals();//Добавление сигналов

    g_object_unref(builder);

    return window;
}

//Обработчик сигнала
void click_buttons(GtkButton *button, gpointer data){
    show_message("Привет! Скоро здесь будет функция");
}



//Добавление сигналов
void add_signals(void){
    g_signal_connect(G_OBJECT(elements.doneTask), "clicked", G_CALLBACK(click_buttons), NULL);
    g_signal_connect(G_OBJECT(elements.addTask), "clicked", G_CALLBACK(create_window_addTask), NULL);
    g_signal_connect(G_OBJECT(elements.settings), "clicked", G_CALLBACK(create_window_settings), NULL);
}
