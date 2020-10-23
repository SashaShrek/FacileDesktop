#include "hSettings.h"
#include "hOnPass.h"
#include <gtk/gtk.h>

struct SettingsElements{
    GtkSwitch *switchPass;
} settingsElements;

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
    
    if(!window || !settingsElements.switchPass){
        g_critical("Не могу получить объект окна или переключателя");
    }

    g_object_unref(builder);

    gtk_widget_show(window);
}

//Открытие окна установки пароля
void switch_usePass(GtkSwitch *switchPass, gpointer data){
    gboolean onOroff = gtk_switch_get_state(switchPass);
    if(onOroff == TRUE){
        create_window_onpass(switchPass);
    }
}