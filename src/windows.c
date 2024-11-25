#include "windows.h"
#include "interface.h"

// Declare windows here

GtkWidget* current_window = NULL;
void windows_init(void)
{
    // Add window initialization of each window here
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