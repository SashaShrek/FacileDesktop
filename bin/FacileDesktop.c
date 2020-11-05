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
    GtkComboBoxText *textTask;
    GtkComboBoxText *textDate;
    GtkComboBoxText *textTime;
} elements;
//

//Прототипы функций
static GtkWidget* create_window(void);
void click_buttons(GtkButton *button, gpointer data);
void add_signals(void);
void select_element_task(GtkComboBox *comboBox, gpointer data);
void select_element_date(GtkComboBox *comboBox, gpointer data);
void select_element_time(GtkComboBox *comboBox, gpointer data);
void load_tasks(void);
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
    load_tasks();//Загрузка задач, если они есть

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
    elements.textTask = GTK_COMBO_BOX_TEXT(gtk_builder_get_object(builder, "textTask"));
    elements.textDate = GTK_COMBO_BOX_TEXT(gtk_builder_get_object(builder, "textDate"));
    elements.textTime = GTK_COMBO_BOX_TEXT(gtk_builder_get_object(builder, "textTime"));

    if(!window || !elements.doneTask || !elements.addTask || !elements.settings){
        g_critical("Не могу получить объект окна или кнопки");
    }

    add_signals();//Добавление сигналов

    g_object_unref(builder);

    return window;
}

//Обработчик сигнала Готово
void click_buttons(GtkButton *button, gpointer data){
    int indexTask = gtk_combo_box_get_active(GTK_COMBO_BOX(elements.textTask));
    int indexDate = gtk_combo_box_get_active(GTK_COMBO_BOX(elements.textDate));
    int indexTime = gtk_combo_box_get_active(GTK_COMBO_BOX(elements.textTime));
    if(indexTask < 0 || indexDate < 0 || indexTime < 0){
      return ;
    }
    gtk_combo_box_text_remove(elements.textTask, indexTask);
    gtk_combo_box_text_remove(elements.textDate, indexDate);
    gtk_combo_box_text_remove(elements.textTime, indexTime);
//
    GtkTreeModel *model = gtk_combo_box_get_model(GTK_COMBO_BOX(elements.textTask));
    short count = gtk_tree_model_iter_n_children(model, 0);
//
    char *task[count * 3];
    short i = 0, l = 0;
    while(i < count){
      gtk_combo_box_set_active(GTK_COMBO_BOX(elements.textTask), i);
      task[l] = gtk_combo_box_text_get_active_text(elements.textTask);
      l++;
      task[l] = gtk_combo_box_text_get_active_text(elements.textDate);
      l++;
      task[l] = gtk_combo_box_text_get_active_text(elements.textTime);
      l++;
      i++;
    }
    char *outcome = get_path_file("/..Conf/tasks.conf");
    FILE *fp = fopen(outcome, "w");
    if(fp != NULL){
      i = 0;
      while(i < count * 3){
        fprintf(fp, "%s\n", task[i]);
        i++;
      }
      fclose(fp);
    }
    free(outcome);
}

//Выбор елементов. Синхрон
void select_element_task(GtkComboBox *comboBox, gpointer data){
  short index = gtk_combo_box_get_active(comboBox);
  gtk_combo_box_set_active(GTK_COMBO_BOX(elements.textDate), index);
  gtk_combo_box_set_active(GTK_COMBO_BOX(elements.textTime), index);
}

void select_element_date(GtkComboBox *comboBox, gpointer data){
  short index = gtk_combo_box_get_active(comboBox);
  gtk_combo_box_set_active(GTK_COMBO_BOX(elements.textTask), index);
  gtk_combo_box_set_active(GTK_COMBO_BOX(elements.textTime), index);
}

void select_element_time(GtkComboBox *comboBox, gpointer data){
  short index = gtk_combo_box_get_active(comboBox);
  gtk_combo_box_set_active(GTK_COMBO_BOX(elements.textTask), index);
  gtk_combo_box_set_active(GTK_COMBO_BOX(elements.textDate), index);
}
//

//Добавление сигналов
void add_signals(void){
    g_signal_connect(G_OBJECT(elements.doneTask), "clicked", G_CALLBACK(click_buttons), 0);
    g_signal_connect(G_OBJECT(elements.addTask), "clicked", G_CALLBACK(create_window_addTask), &elements);
    g_signal_connect(G_OBJECT(elements.settings), "clicked", G_CALLBACK(create_window_settings), NULL);
    g_signal_connect(G_OBJECT(elements.textTask), "changed", G_CALLBACK(select_element_task), 0);
    g_signal_connect(G_OBJECT(elements.textDate), "changed", G_CALLBACK(select_element_date), 0);
    g_signal_connect(G_OBJECT(elements.textTime), "changed", G_CALLBACK(select_element_time), 0);
}

//Загрузка задач, если они есть
void load_tasks(void){
  char *outcome = get_path_file("/..Conf/tasks.conf");
  FILE *fp = fopen(outcome, "r");
  if(fp != NULL){
    long sizeFile = get_size_file(fp);
    short lineCount = 0;
    while(!feof(fp)){
      if(fgetc(fp) == '\n'){
        lineCount++;
      }
    }
    rewind(fp);
    char s[lineCount][sizeFile + 1];
    short i = 0;
    while(i < lineCount){
      fscanf(fp, "%s", s[i]);
      i++;
    }
    i = 0;
    short maxLine = lineCount / 3, l = 0, k = 0;
    while(i < maxLine){//Заполнение ComboBox`ов
      while(l < 3 * (i + 1)){
        switch(k){
          case 0:
            gtk_combo_box_text_append_text(elements.textTask, s[l]);
          break;
          case 1:
            gtk_combo_box_text_append_text(elements.textDate, s[l]);
          break;
          case 2:
            gtk_combo_box_text_append_text(elements.textTime, s[l]);
          break;
        }
        k++;
        l++;
      }
      k = 0;
      i++;
    }
    fclose(fp);
  }
  free(outcome);
}
