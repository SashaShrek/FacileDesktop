#include "hAddTask.h"
#include <gtk/gtk.h>
#include "hBook.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

//Структуры и данные
struct AddTaskElements{
    GtkWidget *window;
    GtkButton *add;
    GtkEntry *textTask;
    GtkCalendar *date;
    GtkEntry *textTime;
} addTaskElements;

struct Elements{
    GtkButton *doneTask;
    GtkButton *addTask;
    GtkButton *settings;
    GtkComboBoxText *textTask;
    GtkComboBoxText *textDate;
    GtkComboBoxText *textTime;
};

//Прототипы функций
void click_addTask(GtkButton *button, gpointer data);
void load_date(void);
void get_time_today(int *iYear, short *iMonth, short *iDay);

//Создание окна добавления задач
void create_window_addTask(GtkButton *button, gpointer data){
    GError *error = NULL;
    GtkBuilder *builder = NULL;

    builder = gtk_builder_new();
    if(!gtk_builder_add_from_file(builder, "/usr/local/bin/AddTaskGUI.ui", &error)){
        g_critical("Невозможно загрузить файл: %s", error->message);
        g_error_free(error);
    }

    addTaskElements.window = GTK_WIDGET(gtk_builder_get_object(builder, "addTaskWindow"));
    addTaskElements.add = GTK_BUTTON(gtk_builder_get_object(builder, "addTask"));
    g_signal_connect(G_OBJECT(addTaskElements.add), "clicked", G_CALLBACK(click_addTask), data);
    addTaskElements.textTask = GTK_ENTRY(gtk_builder_get_object(builder, "textTask"));
    addTaskElements.date = GTK_CALENDAR(gtk_builder_get_object(builder, "date"));
    addTaskElements.textTime = GTK_ENTRY(gtk_builder_get_object(builder, "textTime"));

    if(!addTaskElements.window){
        g_critical("Не могу получить объект окна");
    }

    g_object_unref(builder);

    gtk_widget_show(addTaskElements.window);

    load_date();
}

//Обработчик сигнала
void click_addTask(GtkButton *button, gpointer data){
    guint textTaskLength = gtk_entry_get_text_length(addTaskElements.textTask);
    guint timeLength = gtk_entry_get_text_length(addTaskElements.textTime);
    if(textTaskLength == 0 || timeLength == 0){
      show_message("Поля не должны быть пустыми!");
      return ;
    }
    const char *task[3];
    task[0] = gtk_entry_get_text(addTaskElements.textTask);
    if(timeLength < 5){
      show_message("Время должно быть типа: 02:56");
      return ;
    }
    const char *str = gtk_entry_get_text(addTaskElements.textTime);
    if(str[2] != ':'){
      show_message("Неверный формат! Время должно быть типа: 02:56");
      return ;
    }
    task[2] = str;
    guint *year = (guint*)calloc(1, sizeof(guint));
    guint *month = (guint*)calloc(1, sizeof(guint));
    guint *day = (guint*)calloc(1, sizeof(guint));
    gtk_calendar_get_date(addTaskElements.date, year, month, day);
    int todayYear = 0;
    short todayMonth = 0, todayDay = 0;
    get_time_today(&todayYear, &todayMonth, &todayDay);
    if(todayYear != 0 && todayDay != 0){
      if(*year < todayYear || *month < todayMonth || *day < todayDay){
        show_message("Выберите корректную дату!");
        return ;
      }
    }
    *month += 1;
    char *tYear = (char*)calloc(sizeof(guint), sizeof(char));
    char *tMonth = (char*)calloc(sizeof(guint), sizeof(char));
    char *tDay = (char*)calloc(sizeof(guint), sizeof(char));
    sprintf(tYear, "%d", *year);
    sprintf(tMonth, "%d", *month);
    sprintf(tDay, "%d", *day);
    size_t sizeYear = strlen(tYear);
    size_t sizeMonth = strlen(tMonth);
    size_t sizeDay = strlen(tDay);
    size_t allSize = sizeYear + sizeMonth + sizeDay + 2;
    char *str1 = (char*)calloc(allSize, sizeof(char));
    memcpy(str1, tDay, sizeDay);
    memcpy(str1 + sizeDay, ".", 1);
    memcpy(str1 + sizeDay + 1, tMonth, sizeMonth);
    memcpy(str1 + sizeDay + sizeMonth + 1, ".", 1);
    memcpy(str1 + sizeDay + sizeMonth + 2, tYear, sizeYear);
    task[1] = str1;
    struct Elements *elems = data;
    gtk_combo_box_text_append_text(elems->textTask, task[0]);
    gtk_combo_box_text_append_text(elems->textDate, task[1]);
    gtk_combo_box_text_append_text(elems->textTime, task[2]);

    char *outcome = get_path_file("/..Conf/tasks.conf");
    FILE *fp = fopen(outcome, "a");
    if(fp != NULL){
      int i = 0;
      while(i < 3){
        fprintf(fp, "%s\n", task[i]);
        i++;
      }
      fclose(fp);
    }
    free(outcome);
    free(year);
    free(month);
    free(day);
    free(tYear);
    free(tMonth);
    free(tDay);
    free(str1);
    gtk_widget_destroy(addTaskElements.window);
}

//Загрузка даты
void load_date(void){
  int iYear = 0;
  short iMonth = 0, iDay = 0;
  get_time_today(&iYear, &iMonth, &iDay);
  if(iYear == 0 || iDay == 0){
    return ;
  }
  gtk_calendar_select_month(addTaskElements.date, iMonth, iYear);
  gtk_calendar_select_day(addTaskElements.date, iDay);
}

//Получение сегодняшней даты
void get_time_today(int *iYear, short *iMonth, short *iDay){
  time_t calendarTime = time(0);
  if(calendarTime == -1){
    g_critical("Не могу получить время!");
    return ;
  }
  struct tm *localTime = localtime(&calendarTime);
  char *year = (char*)malloc(sizeof(char));
  char *month = (char*)malloc(sizeof(char));
  char *day = (char*)malloc(sizeof(char));
  strftime(year, sizeof(year), "%Y", localTime);
  strftime(month, sizeof(month), "%m", localTime);
  strftime(day, sizeof(day), "%d", localTime);
  *iYear = atoi(year);
  *iMonth = atoi(month);
  *iMonth -= 1;
  *iDay = atoi(day);
  free(day);
  free(month);
  free(year);
}
