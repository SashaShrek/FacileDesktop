#pragma once
#include <gtk/gtk.h>

struct OnPassElems;

void create_window_onpass(GtkSwitch *switchPass);
void click_done_task(GtkButton *button, gpointer data);
void click_cancel(GtkButton *button, gpointer data);