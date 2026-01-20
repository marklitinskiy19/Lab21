#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "database.h"

// Очистка буфера ввода
void clear_buffer() {
    while (getchar() != '\n');
}

// Добавление нового сеанса
int add_session(FilmSession* arr, int* size) {
    if (*size >= MAX) {
        printf("Достигнут лимит записей!\n");
        return 0;
    }

    FilmSession new_session;
    
    printf("Название фильма: ");
    scanf("%s", new_session.film_name);
    
    printf("Дата сеанса (дд мм гггг): ");
    scanf("%d %d %d", &new_session.session_time.date.day, 
                      &new_session.session_time.date.month, 
                      &new_session.session_time.date.year);
    
    printf("Время сеанса (часы минуты): ");
    scanf("%d %d", &new_session.session_time.time.hours, 
                   &new_session.session_time.time.minutes);
    
    printf("Продолжительность сеанса (часы минуты): ");
    scanf("%d %d", &new_session.duration_hours, &new_session.duration_minutes);
    
    printf("Жанр: ");
    scanf("%s", new_session.genre);
    
    printf("Бюджет фильма: ");
    scanf("%lf", &new_session.budget);
    
    arr[*size] = new_session;
    (*size)++;
    
    return 1;
}

// Вывод одного сеанса
void print_session(FilmSession session) {
    printf("%-20s | %02d.%02d.%04d %02d:%02d | %dч %02dмин | %-15s | %.2f млн\n",
           session.film_name,
           session.session_time.date.day,
           session.session_time.date.month,
           session.session_time.date.year,
           session.session_time.time.hours,
           session.session_time.time.minutes,
           session.duration_hours,
           session.duration_minutes,
           session.genre,
           session.budget);
}

// Вывод всех сеансов
int print_all(FilmSession* arr, int size) {
    if (size == 0) {
        printf("Нет записей о сеансах\n");
        return 0;
    }
    
    printf("\n=== Список всех сеансов ===\n");
    
    for (int i = 0; i < size; i++) {
        printf("%d. ", i+1);
        print_session(arr[i]);
    }
    
    return size;
}

// Редактирование записи
int edit_session(FilmSession* arr, int size) {
    if (size == 0) {
        printf("Нет записей для редактирования\n");
        return 0;
    }
    
    int index;
    print_all(arr, size);
    printf("Введите номер записи для редактирования: ");
    scanf("%d", &index);
    
    if (index < 1 || index > size) {
        printf("Неверный номер\n");
        return 0;
    }
    
    index--;
    
    printf("Редактирование записи: %s\n", arr[index].film_name);
    
    printf("Новое название фильма: ");
    scanf("%s", arr[index].film_name);
    
    printf("Новая дата сеанса (дд мм гггг): ");
    scanf("%d %d %d", &arr[index].session_time.date.day, 
                      &arr[index].session_time.date.month, 
                      &arr[index].session_time.date.year);
    
    printf("Новое время сеанса (часы минуты): ");
    scanf("%d %d", &arr[index].session_time.time.hours, 
                   &arr[index].session_time.time.minutes);
    
    printf("Новая продолжительность (часы минуты): ");
    scanf("%d %d", &arr[index].duration_hours, &arr[index].duration_minutes);
    
    printf("Новый жанр: ");
    scanf("%s", arr[index].genre);
    
    printf("Новый бюджет: ");
    scanf("%lf", &arr[index].budget);
    
    return 1;
}

// Поиск по названию фильма
int search_session(FilmSession* arr, int size) {
    if (size == 0) {
        printf("Нет записей для поиска\n");
        return 0;
    }
    
    char search_term[50];
    printf("Введите название фильма для поиска: ");
    scanf("%s", search_term);
    
    int found = 0;
    printf("\nРезультаты поиска:\n");
    
    for (int i = 0; i < size; i++) {
        if (strstr(arr[i].film_name, search_term) != NULL) {
            printf("%d. ", ++found);
            print_session(arr[i]);
        }
    }
    
    if (found == 0) {
        printf("Ничего не найдено\n");
    }
    
    return found;
}

// Сортировка пузырьком по названию фильма
void sort_by_name(FilmSession* arr, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (strcmp(arr[j].film_name, arr[j+1].film_name) > 0) {
                // Обмен местами
                FilmSession temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

// Сортировка пузырьком по жанру
void sort_by_genre(FilmSession* arr, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (strcmp(arr[j].genre, arr[j+1].genre) > 0) {
                FilmSession temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

// Сортировка пузырьком по дате сеанса
void sort_by_date(FilmSession* arr, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            // Сравниваем год
            if (arr[j].session_time.date.year > arr[j+1].session_time.date.year) {
                FilmSession temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
            // Если год одинаковый, сравниваем месяц
            else if (arr[j].session_time.date.year == arr[j+1].session_time.date.year) {
                if (arr[j].session_time.date.month > arr[j+1].session_time.date.month) {
                    FilmSession temp = arr[j];
                    arr[j] = arr[j+1];
                    arr[j+1] = temp;
                }
                // Если месяц одинаковый, сравниваем день
                else if (arr[j].session_time.date.month == arr[j+1].session_time.date.month) {
                    if (arr[j].session_time.date.day > arr[j+1].session_time.date.day) {
                        FilmSession temp = arr[j];
                        arr[j] = arr[j+1];
                        arr[j+1] = temp;
                    }
                }
            }
        }
    }
}

// Обновленная функция sort_array
int sort_array(FilmSession* arr, int size) {
    int choice;
    printf("1. По названию фильма\n2. По жанру\n3. По дате сеанса\nВыбор: ");
    scanf("%d", &choice);

    switch(choice) {
        case 1:
            sort_by_name(arr, size);
            break;
        case 2:
            sort_by_genre(arr, size);
            break;
        case 3:
            sort_by_date(arr, size);
            break;
        default:
            return 0;
    }

    return 1;
}
