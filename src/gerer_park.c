#include <stdio.h>
#include <string.h>
#include "gerer_park.h"

// Add a new parking record to the file
int ajouter_park(const char *filename, Parking p) {
    FILE *f = fopen(filename, "a");
    if (f != NULL) {
        fprintf(f, "%d %s %s %s %d %d %d %d %.2f\n",
                p.id, p.name, p.location, p.type, p.capacity,
                p.is_24_hours, p.open_hour, p.close_hour, p.hourly_rate);
        fclose(f);
        return 1;
    }
    return 0;
}

// Modify an existing parking record based on ID
int modifier_park(const char *filename, int id, Parking new_p) {
    int found = 0;
    Parking p;
    FILE *f = fopen(filename, "r");
    FILE *temp = fopen("temp.txt", "w");
    if (f == NULL || temp == NULL) {
        return 0;
    }

    while (fscanf(f, "%d %49s %99s %19s %d %d %d %d %f\n",
                  &p.id, p.name, p.location, p.type, &p.capacity,
                  &p.is_24_hours, &p.open_hour, &p.close_hour, &p.hourly_rate) != EOF) {
        if (p.id == id) {
            fprintf(temp, "%d %s %s %s %d %d %d %d %.2f\n",
                    new_p.id, new_p.name, new_p.location, new_p.type,
                    new_p.capacity, new_p.is_24_hours, new_p.open_hour,
                    new_p.close_hour, new_p.hourly_rate);
            found = 1;
        } else {
            fprintf(temp, "%d %s %s %s %d %d %d %d %.2f\n",
                    p.id, p.name, p.location, p.type, p.capacity,
                    p.is_24_hours, p.open_hour, p.close_hour, p.hourly_rate);
        }
    }
    fclose(f);
    fclose(temp);

    remove(filename);
    rename("temp.txt", filename);

    return found;
}

// Delete a parking record based on ID
int supprimer_park(const char *filename, int id) {
    int found = 0;
    Parking p;
    FILE *f = fopen(filename, "r");
    FILE *temp = fopen("temp.txt", "w");
    if (f == NULL || temp == NULL) {
        return 0;
    }

    while (fscanf(f, "%d %49s %99s %19s %d %d %d %d %f\n",
                  &p.id, p.name, p.location, p.type, &p.capacity,
                  &p.is_24_hours, &p.open_hour, &p.close_hour, &p.hourly_rate) != EOF) {
        if (p.id != id) {
            fprintf(temp, "%d %s %s %s %d %d %d %d %.2f\n",
                    p.id, p.name, p.location, p.type, p.capacity,
                    p.is_24_hours, p.open_hour, p.close_hour, p.hourly_rate);
        } else {
            found = 1;
        }
    }
    fclose(f);
    fclose(temp);

    remove(filename);
    rename("temp.txt", filename);

    return found;
}

// Search for a parking record by ID
Parking chercher_park(const char *filename, int id) {
    Parking p;
    p.id = -1; // Default to -1 if not found
    FILE *f = fopen(filename, "r");
    if (f != NULL) {
        while (fscanf(f, "%d %49s %99s %19s %d %d %d %d %f\n",
                      &p.id, p.name, p.location, p.type, &p.capacity,
                      &p.is_24_hours, &p.open_hour, &p.close_hour, &p.hourly_rate) != EOF) {
            if (p.id == id) {
                fclose(f);
                return p;
            }
        }
        fclose(f);
    }
    p.id = -1; // Not found
    return p;
}