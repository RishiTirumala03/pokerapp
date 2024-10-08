#include "Gui.h"

//#define DEBUG

static gboolean on_delete_event (GtkWidget *widget, GdkEvent  *event, gpointer data){
  g_print ("delete event occurred\n"); 
  gtk_main_quit();
  return TRUE;
}

void on_button_clicked(GtkWidget *widget, gpointer *data)
{
    g_print ("Button clicked!\n");
    GtkWidget *second_window;
    second_window = gtk_window_new(GTK_WINDOW_TOPLEVEL) ;
    gtk_window_set_title(GTK_WINDOW(second_window), "Let's Play Poker! ");
    
    /* center the window */
    gtk_window_set_position(GTK_WINDOW(second_window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(second_window), 400, 400);
    gtk_container_set_border_width (GTK_CONTAINER(second_window), 10);
    
    /*register event handlers*/
   g_signal_connect(second_window, "delete_event", G_CALLBACK(on_delete_event), NULL) ; 
   gtk_widget_set_events(second_window, GDK_BUTTON_PRESS_MASK) ; 
   
     /*show the window*/
     gtk_widget_show_all(second_window) ; 
     //gtk_widget_hide(GTK_WIDGET(data)) ; 
    
}
/*
#ifdef DEBUG
int main (int argc, char *argv[])
{
 
    gtk_init(&argc, &argv) ;
    GtkWidget *window;
    GtkWidget *button;
    GtkWidget *alignment;
    
   //*create a new window 
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL) ;
    gtk_window_set_title(GTK_WINDOW(window), "Let's Play Poker! ");
    
    //* center the window 
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);
    gtk_container_set_border_width (GTK_CONTAINER(window), 10);

   
   //* create a new button 
    button = gtk_button_new_with_label("Start Game");
    gtk_widget_set_size_request(button, 150, 50);
    alignment = gtk_alignment_new(0.5, 0.5, 0, 0);
    gtk_container_add(GTK_CONTAINER(alignment), button);
    
    //* connect shutdown button with function terminating this server 
    g_signal_connect(button, "clicked", G_CALLBACK(on_button_clicked), NULL);
    
    gtk_container_add(GTK_CONTAINER(window), alignment);
    
    //*register event handlers
   g_signal_connect(window, "delete_event", G_CALLBACK(on_delete_event), NULL) ; 
   gtk_widget_set_events(window, GDK_BUTTON_PRESS_MASK) ; 
    
   //*show the window
   gtk_widget_show_all(window) ; 
   gtk_main() ; 

   return 0 ;
}
#endif
*/
