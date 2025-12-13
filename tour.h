#ifndef TOUR_H
#define TOUR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_NAME_LENGTH 100
#define MAX_DESTINATION_LENGTH 100
#define FILENAME "tours.txt"


typedef struct Tour {
    char destination[MAX_DESTINATION_LENGTH];
    float price;
    int duration;
    struct Tour* next;
} Tour;


typedef struct {
    Tour* head;
    int count;
} Database;


Database* create_database();
void free_database(Database* db);

bool load_from_file(Database* db);
bool save_to_file(Database* db);

void display_tours(Database* db);
void add_tour(Database* db);
void delete_tour(Database* db);
void edit_tour(Database* db);
void search_tours(Database* db);


Tour* create_tour(const char* destination, float price, int duration);
void insert_tour(Database* db, Tour* new_tour);
void remove_tour_by_index(Database* db, int index);

#endif
