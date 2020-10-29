#include "hSettings.h"
#include "hOnPass.h"
#include "hOnSync.h"
#include <gtk/gtk.h>
#include <stdio.h>
#include <string.h>

struct SettingsElements{
    GtkSwitch *switchPass;
    GtkSwitch *switchSync;
} settingsElements;

//Прототипы функций
void switch_usePass(GtkSwitch *switchPass, gpointer data);
void switch_useSync(GtkSwitch *switchSync, gpointer data);

//Создание окна настроек
void create_window_settings(GtkButton *button, gpointer data){
    GtkWidget *window = NULL;
    GError *error = NULL;
    GtkBuilder *builder = NULL;

    builder = gtk_builder_new();
    if(!gtk_builder_add_from_file(builder, "/usr/local/bin/SettingsGUI.ui", &error)){
        g_critical("Невозможно загрузить файл: %s", error->message);
        g_error_free(error);
    }

    window = GTK_WIDGET(gtk_builder_get_object(builder, "settingsWindow"));
    settingsElements.switchPass = GTK_SWITCH(gtk_builder_get_object(builder, "usePass"));
    g_signal_connect(G_OBJECT(settingsElements.switchPass), "notify::active", G_CALLBACK(switch_usePass), NULL);
    settingsElements.switchSync = GTK_SWITCH(gtk_builder_get_object(builder, "useSync"));
    g_signal_connect(G_OBJECT(settingsElements.switchSync), "notify::active", G_CALLBACK(switch_useSync), NULL);

    if(!window || !settingsElements.switchPass || !settingsElements.switchSync){
        g_critical("Не могу получить объект окна или переключателя");
    }

    g_object_unref(builder);

    const gchar *path = g_get_home_dir();
    gchar *nameFile = "/Conf/pass.conf";
    size_t size_path = strlen(path);
    size_t size_nameFile = strlen(nameFile);
    gchar *all = (gchar*)calloc(size_path + size_nameFile, sizeof(gchar));
    strncpy(all, path, size_path);
    strncpy(all + size_path, nameFile, size_nameFile);
    FILE *file = fopen(all, "r");
    if(file != NULL){
      gtk_switch_set_state(settingsElements.switchPass, 1);
      fclose(file);
    }
    free(all);
    gtk_widget_show(window);
}

//Открытие окна установки пароля
void switch_usePass(GtkSwitch *switchPass, gpointer data){
    gboolean onOrOff = gtk_switch_get_state(switchPass);

    const gchar *path = g_get_home_dir();
    gchar *nameFile = "/Conf/pass.conf";
    size_t size_path = strlen(path);
    size_t size_nameFile = strlen(nameFile);
    gchar *outcome = (gchar*)calloc(size_path + size_nameFile, sizeof(gchar));
    strncpy(outcome, path, size_path);
    strncpy(outcome + size_path, nameFile, size_nameFile);
    FILE *fp = fopen(outcome, "r");
    if(onOrOff == TRUE){
        if(fp == NULL){
          create_window_onpass(switchPass);
        }
    }else{
      if(fp != NULL){
        fclose(fp);
        if(remove(outcome)){
          free(outcome);
          g_critical("Невозможно удалить файл");
          return ;
        }
      }
    }
    free(outcome);
}

//Окно синхронизации
void switch_useSync(GtkSwitch *switchSync, gpointer data){
    gboolean onOrOff = gtk_switch_get_state(switchSync);
    if(onOrOff == TRUE){
        create_window_onsync(switchSync);
    }
}
