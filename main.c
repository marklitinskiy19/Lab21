#include <stdio.h>
#include <locale.h>
#include "database.h"
#include "fileio.h"
#include "utils.h"

int main() {
    setlocale(LC_ALL, "Russian");

    FilmSession sessions[MAX];
    int count = 0;
    int choice;
    int result;

    do {
        printf("\n=== БАЗА ДАННЫХ КИНОСЕАНСОВ ===\n");
        printf("1. Загрузить из файла\n");
        printf("2. Добавить сеанс\n");
        printf("3. Показать все сеансы\n");
        printf("4. Изменить запись\n");
        printf("5. Поиск по названию\n");
        printf("6. Сортировка\n");
        printf("7. Сохранить в файл\n");
        printf("8. Фильмы после 18:00 (>1ч40мин)\n");
        printf("9. Выход\n");
        printf("Выбор: ");
        scanf("%d", &choice);
        clear_buffer();

        switch(choice) {
            case 1:
                result = load_from_file(sessions, &count, "films.bin");
                printf("Загружено: %d\n", result);
                break;
            case 2:
                if (add_session(sessions, &count))
                    printf("Добавлено\n");
                break;
            case 3:
                result = print_all(sessions, count);
                printf("Всего: %d\n", result);
                break;
            case 4:
                if (edit_session(sessions, count))
                    printf("Изменено\n");
                break;
            case 5:
                result = search_session(sessions, count);
                printf("Найдено: %d\n", result);
                break;
            case 6:
                if (sort_array(sessions, count))
                    printf("Отсортировано\n");
                break;
            case 7:
                result = save_to_file(sessions, count, "new_films.bin");
                printf("Сохранено: %d\n", result);
                break;
            case 8:
                show_late_long_films(sessions, count);
                break;
            case 9:
                printf("Выход\n");
                break;
            default:
                printf("Неверный выбор\n");
        }
    } while(choice != 9);

    return 0;
}
