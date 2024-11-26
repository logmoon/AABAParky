#include "windows.h"
#include "interface.h"

// Declare windows here
GtkWidget* AABAwindowSupprimer = NULL;
GtkWidget* AABAwindowAjouter = NULL;
GtkWidget* AABAwindowModifier = NULL;
GtkWidget* AABAwindowGererParking = NULL;
GtkWidget* AABAwindowAttribuerAgent = NULL;

GtkWidget* current_window = NULL;
void windows_init(void)
{
    // Add window initialization of each window here
    AABAwindowSupprimer = create_AABAwindowSupprimer();
    AABAwindowAjouter = create_AABAwindowAjouter();
    AABAwindowModifier = create_AABAwindowModifier();
    AABAwindowGererParking = create_AABAwindowGererParking();
    AABAwindowAttribuerAgent = create_AABAwindowAttribuerAgent();

    // Connect destroy signal
    g_signal_connect(G_OBJECT(AABAwindowSupprimer), "destroy", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(G_OBJECT(AABAwindowAjouter), "destroy", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(G_OBJECT(AABAwindowModifier), "destroy", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(G_OBJECT(AABAwindowGererParking), "destroy", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(G_OBJECT(AABAwindowAttribuerAgent), "destroy", G_CALLBACK(gtk_main_quit), NULL);
    
    // Hide all windows initially, except for the main window
    gtk_widget_hide(AABAwindowSupprimer);
    gtk_widget_hide(AABAwindowAjouter);
    gtk_widget_hide(AABAwindowModifier);
    gtk_widget_hide(AABAwindowGererParking);
    gtk_widget_hide(AABAwindowAttribuerAgent);
}
void windows_show_window(GtkWidget* window)
{
    if (current_window != NULL)
    {
        gtk_widget_hide(current_window);
    }
    current_window = window;
    gtk_widget_show(window);
}