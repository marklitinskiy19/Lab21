@echo off
echo Компиляция проекта База данных киносеансов...
gcc -std=c99 -o cinema.exe main.c database.c fileio.c utils.c
if %errorlevel% equ 0 (
    echo Компиляция успешно завершена!
    echo Для запуска программы введите: cinema.exe
) else (
    echo Ошибка компиляции!
pause
)
