#ifndef FILEIO_H
#define FILEIO_H

#include "database.h"

// Загрузка из файла с тестовыми данными
int load_from_file(FilmSession* arr, int* size, char* filename);

// Сохранение всего массива в файл
int save_to_file(FilmSession* arr, int size, char* filename);

#endif
