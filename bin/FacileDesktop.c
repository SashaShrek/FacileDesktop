#include <gtk/gtk.h>
#include <stdio.h>
#include "Settings.h"

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
    gtk_main();
    return 0;
}

//Создание главного окна из файла .ui
static GtkWidget* create_window(void){
    GtkWidget *window;
    GtkBuilder *builder;
    GError *error = NULL;

    builder = gtk_builder_new();
    if(!gtk_builder_add_from_file(builder, "MainGUI.ui", &error)){
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

//Обработчик сигналов
void click_buttons(GtkButton *button, gpointer data){
    GtkDialogFlags flags = GTK_DIALOG_DESTROY_WITH_PARENT;
    GtkWidget *dialog = gtk_message_dialog_new (NULL,
                                    flags,
                                    GTK_MESSAGE_ERROR,
                                    GTK_BUTTONS_CLOSE,
                                    "Привет! Скоро здесь будет функция");
    gtk_dialog_run (GTK_DIALOG (dialog));
    gtk_widget_destroy (dialog);
}



//Добавление сигналов
void add_signals(void){
    g_signal_connect(G_OBJECT(elements.doneTask), "clicked", G_CALLBACK(click_buttons), NULL);
    g_signal_connect(G_OBJECT(elements.addTask), "clicked", G_CALLBACK(click_buttons), NULL);
    g_signal_connect(G_OBJECT(elements.settings), "clicked", G_CALLBACK(create_window_settings), NULL);
}