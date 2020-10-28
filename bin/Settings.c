#include "hSettings.h"
#include "hOnPass.h"
#include "hOnSync.h"
#include <gtk/gtk.h>
#include <stdio.h>
#include "hBook.h"
#include <openssl/md5.h>

#define PATH_CONF "Conf/pass.conf"

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
    if(!gtk_builder_add_from_file(builder, "SettingsGUI.ui", &error)){
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

    FILE *file = fopen(PATH_CONF, "r");
    if(file != NULL){
      gtk_switch_set_state(settingsElements.switchPass, get_target(file, "pass"));
      fclose(file);
    }

    gtk_widget_show(window);
}

//Открытие окна установки пароля
void switch_usePass(GtkSwitch *switchPass, gpointer data){
    gboolean onOrOff = gtk_switch_get_state(switchPass);
    FILE *fp = fopen(PATH_CONF, "r");
    if(onOrOff == TRUE){
        if(fp == NULL){
          create_window_onpass(switchPass);
        }
    }else{
      if(fp != NULL){
        fclose(fp);
        if(remove(PATH_CONF)){
          g_critical("Невозможно удалить файл");
          return ;
        }
      }
    }
}

//Окно синхронизации
void switch_useSync(GtkSwitch *switchSync, gpointer data){
    gboolean onOrOff = gtk_switch_get_state(switchSync);
    if(onOrOff == TRUE){
        create_window_onsync(switchSync);
    }
}
