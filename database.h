#ifndef DATABASE_H
#define DATABASE_H

#define MAX 100

// Структура для времени
typedef struct {
    int hours;
    int minutes;
} Time;

// Структура для даты
typedef struct {
    int day;
    int month;
    int year;
} Date;

// Структура для даты и времени сеанса
typedef struct {
    Date date;
    Time time;
} DateTime;

// Структура для киносеанса
typedef struct {
    char film_name[50];          // Название фильма
    DateTime session_time;       // Дата и время сеанса
    int duration_hours;          // Часы продолжительности
    int duration_minutes;        // Минуты продолжительности
    char genre[20];              // Жанр фильма
    double budget;               // Бюджет фильма (в млн)
} FilmSession;

// Функции работы с базой данных

// Добавление нового сеанса
int add_session(FilmSession* arr, int* size);

// Вывод одного сеанса
void print_session(FilmSession session);

// Вывод всех сеансов
int print_all(FilmSession* arr, int size);

// Редактирование записи
int edit_session(FilmSession* arr, int size);

// Поиск по названию фильма
int search_session(FilmSession* arr, int size);

// Меню сортировки
int sort_array(FilmSession* arr, int size);

// Сортировка по названию фильма
void sort_by_name(FilmSession* arr, int size);

// Сортировка по жанру
void sort_by_genre(FilmSession* arr, int size);

// Сортировка по дате сеанса
void sort_by_date(FilmSession* arr, int size);

#endif
