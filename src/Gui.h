#ifndef GUI_H
#define GUI_H
#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>

static gboolean on_delete_event (GtkWidget *widget, GdkEvent  *event, gpointer   data);
void on_button_clicked(GtkWidget *widget, gpointer *data);

#endif
