#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include "windows.h"
#include "gerer_park.h"
#include "utils.h"

void
on_AABAbuttonGPAjouter_clicked         (GtkButton       *button,
                                        gpointer         user_data)
{
    windows_show_window(AABAwindowAjouter);
}
void
on_AABAbuttonAjouterEnregistrer_clicked
                                        (GtkWidget       *widget,
                                        gpointer         user_data)
{
    Parking parking = {0};
    GtkWidget* name_entry = lookup_widget(widget, "AABAentryAjouterNom");
    GtkWidget* location_entry = lookup_widget(widget, "AABAtextviewAjouterLocalization");
    GtkWidget* type_combo = lookup_widget(widget, "AABAcomboboxAjouterType");
    GtkWidget* capacity_spin = lookup_widget(widget, "AABAspinbuttonNombreDePlaces");
    GtkWidget* is_24_hours_check = lookup_widget(widget, "AABAcheckbuttonAjouter247");
    GtkWidget* open_hour_combo = lookup_widget(widget, "AABAcomboboxAjouterOuv");
    GtkWidget* close_hour_combo = lookup_widget(widget, "AABAcomboboxAjouterFerm");
    GtkWidget* hourly_rate_spin = lookup_widget(widget, "AABAspinbuttonAjouterTarif");

    // Retrieve the values from the different widget types
    const char *name = gtk_entry_get_text(GTK_ENTRY(name_entry));

    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(location_entry));
    GtkTextIter start, end;
    gtk_text_buffer_get_bounds(buffer, &start, &end);
    char *location = gtk_text_buffer_get_text(buffer, &start, &end, FALSE);

    char *type = get_combo_box_text(type_combo);
    int capacity = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(capacity_spin));
    int is_24_hours = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(is_24_hours_check));
    int open_hour = gtk_combo_box_get_active(GTK_COMBO_BOX(open_hour_combo));
    int close_hour = gtk_combo_box_get_active(GTK_COMBO_BOX(close_hour_combo));
    float hourly_rate = gtk_spin_button_get_value(GTK_SPIN_BUTTON(hourly_rate_spin));

    // Assign the values to the Parking struct
    strncpy(parking.name, name, MAX_NAME_LEN - 1);
    strncpy(parking.location, location, MAX_LOCATION_LEN - 1); g_free(location);
    if (type)
    {
        strncpy(parking.type, type, sizeof(parking.type) - 1);
        g_free(type);
    }
    parking.capacity = capacity;
    parking.is_24_hours = is_24_hours;
    parking.open_hour = open_hour;
    parking.close_hour = close_hour;
    parking.hourly_rate = hourly_rate;

    ajouter_park("/home/amen/Projects/AABAParky/parkings.txt", parking);
}