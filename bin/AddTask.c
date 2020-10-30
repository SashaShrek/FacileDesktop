#include "hAddTask.h"
#include <gtk/gtk.h>
#include "hBook.h"

//Структуры и данные
struct AddTaskElements{
    GtkButton *add;
    GtkEntry *textTask;
    GtkCalendar *date;
    GtkEntry *textTime;
} addTaskElements;

//Прототипы функций
void click_addTask(GtkButton *button, gpointer data);

//Создание окна добавления задач
void create_window_addTask(GtkButton *button, gpointer data){
    GtkWidget *window = NULL;
    GError *error = NULL;
    GtkBuilder *builder = NULL;

    builder = gtk_builder_new();
    if(!gtk_builder_add_from_file(builder, "/usr/local/bin/AddTaskGUI.ui", &error)){
        g_critical("Невозможно загрузить файл: %s", error->message);
        g_error_free(error);
    }

    window = GTK_WIDGET(gtk_builder_get_object(builder, "addTaskWindow"));
    addTaskElements.add = GTK_BUTTON(gtk_builder_get_object(builder, "addTask"));
    g_signal_connect(G_OBJECT(addTaskElements.add), "clicked", G_CALLBACK(click_addTask), NULL);
    addTaskElements.textTask = GTK_ENTRY(gtk_builder_get_object(builder, "textTask"));
    addTaskElements.date = GTK_CALENDAR(gtk_builder_get_object(builder, "date"));
    addTaskElements.textTime = GTK_ENTRY(gtk_builder_get_object(builder, "textTime"));

    if(!window){
        g_critical("Не могу получить объект окна");
    }

    g_object_unref(builder);

    gtk_widget_show(window);
}

//Обработчик сигнала
void click_addTask(GtkButton *button, gpointer data){
    show_message("Привет! Скоро здесь будет функция");
}
