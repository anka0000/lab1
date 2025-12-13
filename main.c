#include "tour.h"

void display_menu() {
    printf("\n=== ТУРОПЕРАТОР - УПРАВЛЕНИЕ БАЗОЙ ДАННЫХ ===\n");
    printf("1. Показать все туры\n");
    printf("2. Добавить новый тур\n");
    printf("3. Удалить тур\n");
    printf("4. Редактировать тур\n");
    printf("5. Поиск туров\n");
    printf("6. Сохранить изменения в файл\n");
    printf("0. Выход\n");
    printf("Выберите действие: ");
}

int main() {
    Database* db = create_database();
    if (!db) {
        printf("Ошибка создания базы данных!\n");
        return 1;
    }
    

    if (!load_from_file(db)) {
        printf("Ошибка загрузки данных из файла!\n");
        free_database(db);
        return 1;
    }
    
    printf("Добро пожаловать в систему управления туроператором!\n");
    printf("Загружено туров: %d\n", db->count);
    
    int choice;
    bool running = true;
    
    while (running) {
        display_menu();
        
        if (scanf("%d", &choice) != 1) {
            printf("Неверный ввод! Пожалуйста, введите число.\n");
            while (getchar() != '\n');
            continue;
        }
        
        switch (choice) {
            case 0:
                printf("Сохранение данных...\n");
                save_to_file(db);
                printf("Все изменения сохранены. До свидания!\n");
                running = false;
                break;
            case 1:
                display_tours(db);
                break;
            case 2:
                add_tour(db);
                break;
            case 3:
                delete_tour(db);
                break;
            case 4:
                edit_tour(db);
                break;
            case 5:
                search_tours(db);
                break;
            case 6:
                if (save_to_file(db)) {
                    printf("Данные успешно сохранены в файл!\n");
                }
                break;
            default:
                printf("Неверный выбор! Пожалуйста, выберите действие из меню.\n");
                break;
        }
    }
    
    free_database(db);
    return 0;
}
