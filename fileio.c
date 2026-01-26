#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "database.h"

int load_from_file(FilmSession* arr, int* size, char* filename) {
    FILE* f = fopen(filename, "rb");
    if (!f) {
        printf("Файл не найден, создаю данные...\n");
        strcpy(arr[0].film_name, "Интерстеллар");
        arr[0].session_time.date.day = 10;
        arr[0].session_time.date.month = 12;
        arr[0].session_time.date.year = 2024;
        arr[0].session_time.time.hours = 19;
        arr[0].session_time.time.minutes = 30;
        arr[0].duration_hours = 2;
        arr[0].duration_minutes = 49;
        strcpy(arr[0].genre, "фантастика");
        arr[0].budget = 165.0;

        strcpy(arr[1].film_name, "Криминальное чтиво");
        arr[1].session_time.date.day = 15;
        arr[1].session_time.date.month = 12;
        arr[1].session_time.date.year = 2024;
        arr[1].session_time.time.hours = 20;
        arr[1].session_time.time.minutes = 15;
        arr[1].duration_hours = 2;
        arr[1].duration_minutes = 34;
        strcpy(arr[1].genre, "криминал");
        arr[1].budget = 8.5;

        *size = 2;
        save_to_file(arr, *size, filename);
        return 2;
    }

    *size = 0;
    while (fread(&arr[*size], sizeof(FilmSession), 1, f) == 1) {
        (*size)++;
        if (*size >= MAX) break;
    }

    fclose(f);
    return *size;
}

int save_to_file(FilmSession* arr, int size, char* filename) {
    if (size == 0) return 0;

    FILE* f = fopen(filename, "wb");
    if (!f) return 0;

    int saved = 0;
    for (int i = 0; i < size; i++) {
        if (fwrite(&arr[i], sizeof(FilmSession), 1, f) == 1) {
            saved++;
        }
    }

    fclose(f);
    return saved;
}
