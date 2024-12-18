#ifndef GERER_PARK_H_INCLUDED
#define GERER_PARK_H_INCLUDED

#define MAX_NAME_LEN 50
#define MAX_LOCATION_LEN 100

// Define the Parking structure
typedef struct {
    int id;                          // Unique ID for each parking
    char name[MAX_NAME_LEN];         // Name of the parking
    char location[MAX_LOCATION_LEN]; // Location
    char type[20];                   // Type of parking (e.g., public, private)
    int capacity;                    // Number of spaces
    int is_24_hours;                 // 1 if open 24/7, 0 otherwise
    int open_hour;                   // Opening hour if not 24/7 (e.g., 9 for 9 AM)
    int close_hour;                  // Closing hour if not 24/7 (e.g., 17 for 5 PM)
    float hourly_rate;               // Hourly rate for parking
} Parking;

// Function declarations
int ajouter_park(const char *filename, Parking p);
int modifier_park(const char *filename, int id, Parking new_p);
int supprime_park(const char *filename, int id);
Parking chercher_park(const char *filename, int id);

#endif // GERER_PARK_H_INCLUDED