#include <gtk/gtk.h>
#include "hOnSync.h"

struct OnSyncElements{
    GtkWidget *window;
    GtkEntry *facileID;
    GtkEntry *facilePass;
    GtkButton *doneSync;
    GtkButton *cancelSync;
} onSyncElems;

//Прототипы функций
void close_this_window(GtkButton *button, gpointer data);
void done_onsync(GtkButton *button, gpointer data);

//Создание окна
void create_window_onsync(GtkSwitch *switchSync){
    GError *error = NULL;
    GtkBuilder *builder = NULL;
    
    builder = gtk_builder_new();
    if(!gtk_builder_add_from_file(builder, "OnSyncGUI.ui", &error)){
        g_critical("Невозможно загрузить файл OnSyncGUI: %s", error->message);
        g_error_free(error);
    }

    onSyncElems.window = GTK_WIDGET(gtk_builder_get_object(builder, "onSync"));
    onSyncElems.facileID = GTK_ENTRY(gtk_builder_get_object(builder, "facileID"));
    onSyncElems.facilePass = GTK_ENTRY(gtk_builder_get_object(builder, "facilePass"));
    onSyncElems.doneSync = GTK_BUTTON(gtk_builder_get_object(builder, "doneSync"));
    g_signal_connect(G_OBJECT(onSyncElems.doneSync), "clicked", G_CALLBACK(done_onsync), NULL);
    onSyncElems.cancelSync = GTK_BUTTON(gtk_builder_get_object(builder, "cancelSync"));
    g_signal_connect(G_OBJECT(onSyncElems.cancelSync), "clicked", G_CALLBACK(close_this_window), switchSync);

    if(!onSyncElems.window || !onSyncElems.facileID || !onSyncElems.facilePass || !onSyncElems.doneSync || !onSyncElems.cancelSync){
        g_critical("Не могу загрузить объект окна или других элементов!");
    }

    g_object_unref(builder);
    gtk_widget_show(onSyncElems.window);
}

//Нажатие кнопки отмена
void close_this_window(GtkButton *button, gpointer data){
    gtk_switch_set_state(GTK_SWITCH(data), FALSE);
    gtk_widget_destroy(GTK_WIDGET(onSyncElems.window));
}

//Нажатие кнопки готово
void done_onsync(GtkButton *button, gpointer data){
    guint16 lengthFacileId = gtk_entry_get_text_length(onSyncElems.facileID);
    guint16 lengthFacilePass = gtk_entry_get_text_length(onSyncElems.facilePass);
    if(lengthFacileId < 1 || lengthFacilePass < 4){
        GtkDialogFlags flags = GTK_DIALOG_DESTROY_WITH_PARENT;
        GtkWidget *dialog = gtk_message_dialog_new (NULL,
                                        flags,
                                        GTK_MESSAGE_ERROR,
                                        GTK_BUTTONS_CLOSE,
                                        "Слишком короткие данные!");
        gtk_dialog_run (GTK_DIALOG (dialog));
        gtk_widget_destroy (dialog);
        return ;
    }
    const gchar *textFacileID = gtk_entry_get_text(onSyncElems.facileID);
    const gchar *textFacilePass = gtk_entry_get_text(onSyncElems.facilePass);
    //
    gtk_widget_destroy(GTK_WIDGET(onSyncElems.window));
}
