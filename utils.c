#include <stdio.h>
#include "database.h"

// Функция для вывода фильмов, начинающихся после 18:00
// и продолжительностью более 1 часа 40 минут (вариант 12)
void show_late_long_films(FilmSession* arr, int size) {
    int count = 0;
    printf("\nФильмы после 18:00 и длительностью > 1ч 40мин:\n");

    for (int i = 0; i < size; i++) {
        // Проверяем время начала (после 18:00)
        int starts_after_18 = (arr[i].session_time.time.hours >= 18);
        
        // Проверяем продолжительность (более 1 часа 40 минут = 100 минут)
        int duration_minutes = arr[i].duration_hours * 60 + arr[i].duration_minutes;
        int longer_than_100 = (duration_minutes > 100);
        
        if (starts_after_18 && longer_than_100) {
            printf("%d. ", i+1);
            print_session(arr[i]);
            count++;
        }
    }

    if (count == 0) {
        printf("Не найдено\n");
    }
}
