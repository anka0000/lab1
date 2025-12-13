#include "tour.h"


Database* create_database() {
    Database* db = (Database*)malloc(sizeof(Database));
    if (db) {
        db->head = NULL;
        db->count = 0;
    }
    return db;
}


void free_database(Database* db) {
    if (!db) return;

    Tour* current = db->head;
    while (current) {
        Tour* next = current->next;
        free(current);
        current = next;
    }
    free(db);
}


Tour* create_tour(const char* destination, float price, int duration) {
   Tour* new_tour = (Tour*)malloc(sizeof(Tour));
    if (new_tour) {
        strncpy(new_tour->destination, destination, MAX_DESTINATION_LENGTH - 1);
        new_tour->destination[MAX_DESTINATION_LENGTH - 1] = '\0';
        new_tour->price = price;
        new_tour->duration = duration;
        new_tour->next = NULL;
    }
    return new_tour;
}


void insert_tour(Database* db, Tour* new_tour) {
    if (!db || !new_tour) return;

    if (db->head == NULL) {
        db->head = new_tour;
    } else {
        Tour* current = db->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_tour;
    }
    db->count++;
}
bool load_from_file(Database* db) {
    FILE* file = fopen(FILENAME, "r");
    if (!file) {
       
        return true;
    }
    
    char destination[MAX_DESTINATION_LENGTH];
    float price;
    int duration;
    
    while (fscanf(file, "%99[^|]|%f|%d\n", destination, &price, &duration) == 3) {
        Tour* new_tour = create_tour(destination, price, duration);
        if (new_tour) {
            insert_tour(db, new_tour);
        }
    }
    
    fclose(file);
    return true;
}

bool save_to_file(Database* db) {
    FILE* file = fopen(FILENAME, "w");
    if (!file) {
        printf("Ошибка открытия файла для записи!\n");
        return false;
    }
    
    Tour* current = db->head;
    while (current != NULL) {
        fprintf(file, "%s|%.2f|%d\n", 
                current->destination, 
                current->price, 
                current->duration);
        current = current->next;
    }
    
    fclose(file);
    return true;
}


void display_tours(Database* db) {
    if (!db || db->count == 0) {
        printf("\nСписок туров пуст.\n");
        return;
    }
    
    printf("\n=== СПИСОК ТУРОВ ===\n");
    printf("+----+---------------------------------+-----------+----------+\n");
    printf("| №  | Направление                     | Цена (руб)| Дней     |\n");
    printf("+----+---------------------------------+-----------+----------+\n");
    
    Tour* current = db->head;
    int index = 1;
    while (current != NULL) {
        printf("| %-2d | %-31s | %-9.2f | %-8d |\n", 
               index++, 
               current->destination, 
               current->price, 
               current->duration);
        current = current->next;
    }
    printf("+----+---------------------------------+-----------+----------+\n");
    printf("Всего туров: %d\n", db->count);
}


void remove_tour_by_index(Database* db, int index) {
    if (!db || index < 1 || index > db->count) {
        printf("Неверный индекс!\n");
        return;
    }
    
    Tour* current = db->head;
    Tour* prev = NULL;
    

    if (index == 1) {
        db->head = current->next;
        free(current);
        db->count--;
        printf("Тур успешно удален!\n");
        return;
    }
    

    for (int i = 1; i < index && current != NULL; i++) {
        prev = current;
        current = current->next;
    }
    
    if (current) {
        prev->next = current->next;
        free(current);
        db->count--;
        printf("Тур успешно удален!\n");
    }
}


void add_tour(Database* db) {
    char destination[MAX_DESTINATION_LENGTH];
    float price;
int duration;
    
    printf("\n=== ДОБАВЛЕНИЕ НОВОГО ТУРА ===\n");
    
    printf("Введите направление: ");
    getchar();
    fgets(destination, MAX_DESTINATION_LENGTH, stdin);
    destination[strcspn(destination, "\n")] = 0;
    
    printf("Введите цену (руб): ");
    while (scanf("%f", &price) != 1 || price <= 0) {
        printf("Неверная цена! Введите положительное число: ");
        while (getchar() != '\n');
    }
    
    printf("Введите продолжительность (дней): ");
    while (scanf("%d", &duration) != 1 || duration <= 0) {
        printf("Неверная продолжительность! Введите положительное число: ");
        while (getchar() != '\n');
    }
    
    Tour* new_tour = create_tour(destination, price, duration);
    if (new_tour) {
        insert_tour(db, new_tour);
        printf("Тур успешно добавлен!\n");
    } else {
        printf("Ошибка при добавлении тура!\n");
    }
}


void delete_tour(Database* db) {
    if (!db || db->count == 0) {
        printf("\nСписок туров пуст.\n");
        return;
    }
    
    display_tours(db);
    
    int index;
    printf("\nВведите номер тура для удаления: ");
    while (scanf("%d", &index) != 1 || index < 1 || index > db->count) {
        printf("Неверный номер! Введите число от 1 до %d: ", db->count);
        while (getchar() != '\n');
    }
    
    remove_tour_by_index(db, index);
}


void edit_tour(Database* db) {
    if (!db || db->count == 0) {
        printf("\nСписок туров пуст.\n");
        return;
    }
    
    display_tours(db);
    
    int index;
    printf("\nВведите номер тура для редактирования: ");
    while (scanf("%d", &index) != 1 || index < 1 || index > db->count) {
        printf("Неверный номер! Введите число от 1 до %d: ", db->count);
        while (getchar() != '\n');
    }
    
    Tour* current = db->head;
    for (int i = 1; i < index && current != NULL; i++) {
        current = current->next;
    }
    
    if (!current) {
        printf("Ошибка: тур не найден!\n");
        return;
    }
    
    printf("\n=== РЕДАКТИРОВАНИЕ ТУРА ===\n");
    printf("Текущие данные:\n");
    printf("Направление: %s\n", current->destination);
    printf("Цена: %.2f руб\n", current->price);
    printf("Длительность: %d дней\n", current->duration);
    
    printf("\nВведите новые данные (оставьте пустым для сохранения текущего):\n");
    
    getchar();
    
    char new_destination[MAX_DESTINATION_LENGTH];
    printf("Новое направление: ");
    fgets(new_destination, MAX_DESTINATION_LENGTH, stdin);
    if (strlen(new_destination) > 1) {
        new_destination[strcspn(new_destination, "\n")] = 0;
        strcpy(current->destination, new_destination);
    }
    
    char price_input[20];
    printf("Новая цена: ");
    fgets(price_input, sizeof(price_input), stdin);
    if (strlen(price_input) > 1) {
        float new_price = atof(price_input);
        if (new_price > 0) {
            current->price = new_price;
        }
    }
    
    char duration_input[20];
    printf("Новая длительность: ");
    fgets(duration_input, sizeof(duration_input), stdin);
    if (strlen(duration_input) > 1) {
        int new_duration = atoi(duration_input);
        if (new_duration > 0) {
            current->duration = new_duration;
        }
    }
    
    printf("Тур успешно отредактирован!\n");
}


void search_tours(Database* db) {
    if (!db || db->count == 0) {
        printf("\nСписок туров пуст.\n");
        return;
    }
    
    int choice;
    printf("\n=== ПОИСК ТУРОВ ===\n");
    printf("1. По направлению\n");
    printf("2. По максимальной цене\n");
    printf("3. По минимальной длительности\n");
    printf("Выберите критерий поиска: ");
    scanf("%d", &choice);
    
    getchar();
    
    bool found = false;
    Tour* current = db->head;
    int index = 1;
    
    printf("\n=== РЕЗУЛЬТАТЫ ПОИСКА ===\n");
printf("+----+---------------------------------+-----------+----------+\n");
    printf("| №  | Направление                     | Цена (руб)| Дней     |\n");
    printf("+----+---------------------------------+-----------+----------+\n");
    
    switch (choice) {
        case 1: {
            char search_destination[MAX_DESTINATION_LENGTH];
            printf("Введите направление для поиска: ");
            fgets(search_destination, MAX_DESTINATION_LENGTH, stdin);
            search_destination[strcspn(search_destination, "\n")] = 0;
            
            while (current != NULL) {
                if (strstr(current->destination, search_destination) != NULL) {
                    printf("| %-2d | %-31s | %-9.2f | %-8d |\n", 
                           index, current->destination, current->price, current->duration);
                    found = true;
                }
                current = current->next;
                index++;
            }
            break;
        }
        case 2: {
            float max_price;
            printf("Введите максимальную цену: ");
            scanf("%f", &max_price);
            
            while (current != NULL) {
                if (current->price <= max_price) {
                    printf("| %-2d | %-31s | %-9.2f | %-8d |\n", 
                           index, current->destination, current->price, current->duration);
                    found = true;
                }
                current = current->next;
                index++;
            }
            break;
        }
        case 3: {
            int min_duration;
            printf("Введите минимальную длительность (дней): ");
            scanf("%d", &min_duration);
            
            while (current != NULL) {
                if (current->duration >= min_duration) {
                    printf("| %-2d | %-31s | %-9.2f | %-8d |\n", 
                           index, current->destination, current->price, current->duration);
                    found = true;
                }
                current = current->next;
                index++;
            }
            break;
        }
        default:
            printf("Неверный выбор!\n");
            return;
    }
    
    printf("+----+---------------------------------+-----------+----------+\n");
    
    if (!found) {
        printf("Туры по заданным критериям не найдены.\n");
    }
}
