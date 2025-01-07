#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <locale.h>

#define NUM_ATHLETES 15
#define NUM_STAGES 4

// Функция для вывода заголовка
void printHeader() {
    printf("+-------------------------------------------------------------------------------------+\n");
    printf("|                                 КУРСОВОЙ ПРОЕКТ                                      |\n");
    printf("|                                                                                      |\n");
    printf("| ТЕМА: ДВУМЕРНЫЕ МАССИВЫ, ПОСТРОЕНИЕ ПРОГРАММЫ ВЫЧИСЛЕНИЯ                             |\n");
    printf("| (И АНАЛИЗА) РЕЗУЛЬТАТОВ СОРЕВНОВАНИЙ ПО ВИДАМ СПОРТА (БИАТЛОН)                       |\n");
    printf("|                                                                                      |\n");
    printf("| ВЫПОЛНИЛ:          ОВЧИННИКОВ Н.И                                                    |\n");
    printf("| ГРУППА:           БОИС-242                                                           |\n");
    printf("+-------------------------------------------------------------------------------------+\n");
}

// Функция для заполнения таблицы случайными числами
void fillTable(int table[NUM_ATHLETES][NUM_STAGES + 2]) {
    for (int i = 0; i < NUM_ATHLETES; i++) {
        for (int j = 0; j < NUM_STAGES; j++) {
            table[i][j] = rand() % 1000 + 1500; // Время от 1500 до 2499 секунд
        }
        table[i][NUM_STAGES] = rand() % 6; // Промахи лежа
        table[i][NUM_STAGES + 1] = rand() % 6; // Промахи стоя
    }
}

// Функция для вывода таблицы
void printTable(int table[NUM_ATHLETES][NUM_STAGES + 2]) {
    printf("Исходная таблица соревнований:\n");
    printf("Спортсмен | Этап 1 | Этап 2 | Этап 3 | Этап 4 | Промахи (лежа) | Промахи (стоя)\n");
    for (int i = 0; i < NUM_ATHLETES; i++) {
        printf("%9d |", i + 1);
        for (int j = 0; j < NUM_STAGES + 2; j++) {
            printf(" %6d |", table[i][j]);
        }
        printf("\n");
    }
}

// Функция для вычисления результатов
void calculateResults(int table[NUM_ATHLETES][NUM_STAGES + 2], int results[NUM_ATHLETES][4]) {
    for (int i = 0; i < NUM_ATHLETES; i++) {
        int total_time = 0;
        for (int j = 0; j < NUM_STAGES; j++) {
            total_time += table[i][j];
        }
        int penalty_time = (table[i][NUM_STAGES] + table[i][NUM_STAGES + 1]) * 150; // 150 секунд за каждый промах
        results[i][0] = total_time + penalty_time; // Итоговое время
        results[i][1] = i; // Индекс спортсмена для сортировки
        results[i][2] = table[i][NUM_STAGES]; // Промахи лежа
        results[i][3] = table[i][NUM_STAGES + 1]; // Промахи стоя
    }
}

// Функция для сортировки результатов
void sortResults(int results[NUM_ATHLETES][4]) {
    for (int i = 0; i < NUM_ATHLETES - 1; i++) {
        for (int j = 0; j < NUM_ATHLETES - i - 1; j++) {
            if (results[j][0] > results[j + 1][0]) {
                // Сортировка по итоговому времени
                for (int k = 0; k < 4; k++) {
                    int temp = results[j][k];
                    results[j][k] = results[j + 1][k];
                    results[j + 1][k] = temp;
                }
            }
        }
    }
}

// Функция для нахождения лучшего или худшего спортсмена
void findAthleteByCriteria(int results[NUM_ATHLETES][4], const char* criteria) {
    if (strcmp(criteria, "лучший") == 0) {
        printf("\nЛучший спортсмен:\n");
                printf("Спортсмен | Итоговое время | Промахи (лежа) | Промахи (стоя)\n");
        printf("%9d | %14d | %14d | %12d\n", results[0][1] + 1, results[0][0], results[0][2], results[0][3]);
    } else if (strcmp(criteria, "худший") == 0) {
        printf("\nХудший спортсмен:\n");
        printf("Спортсмен | Итоговое время | Промахи (лежа) | Промахи (стоя)\n");
        printf("%9d | %14d | %14d | %12d\n", results[NUM_ATHLETES - 1][1] + 1, results[NUM_ATHLETES - 1][0], results[NUM_ATHLETES - 1][2], results[NUM_ATHLETES - 1][3]);
    } else {
        printf("Некорректный критерий поиска.\n");
    }
}

// Функция для вывода таблицы результатов
void printResults(int results[NUM_ATHLETES][4]) {
    printf("\nРезультирующая таблица:\n");
    printf("Спортсмен | Итоговое время | Место | Промахи (лежа) | Промахи (стоя)\n");
    for (int i = 0; i < NUM_ATHLETES; i++) {
        printf("%9d | %14d | %5d | %14d | %12d\n", results[i][1] + 1, results[i][0], i + 1, results[i][2], results[i][3]);
    }
}

// Функция для загрузки данных из файла
int loadDataFromFile(int table[NUM_ATHLETES][NUM_STAGES + 2], const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Ошибка при открытии файла.\n");
        return 0;
    }

    for (int i = 0; i < NUM_ATHLETES; i++) {
        for (int j = 0; j < NUM_STAGES + 2; j++) {
            if (fscanf(file, "%d", &table[i][j]) != 1) {
                printf("Ошибка при чтении данных из файла.\n");
                fclose(file);
                return 0;
            }
        }
    }

    fclose(file);
    return 1;
}

// Функция для сохранения данных в файл
void saveDataToFile(int table[NUM_ATHLETES][NUM_STAGES + 2], const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Ошибка при открытии файла для записи.\n");
        return;
    }

    for (int i = 0; i < NUM_ATHLETES; i++) {
        for (int j = 0; j < NUM_STAGES + 2; j++) {
            fprintf(file, "%d ", table[i][j]);
        }
        fprintf(file, "\n");
    }

    fclose(file);
    printf("Данные успешно сохранены в файл %s.\n", filename);
}

// Функция для редактирования результатов спортсмена
void editAthleteScore(int table[NUM_ATHLETES][NUM_STAGES + 2]) {
    int athleteIndex, stage, newScore;
    printf("Введите номер спортсмена (1-%d): ", NUM_ATHLETES);
    scanf("%d", &athleteIndex);
    athleteIndex--; // Преобразование в индекс массива

    if (athleteIndex < 0 || athleteIndex >= NUM_ATHLETES) {
        printf("Некорректный номер спортсмена.\n");
        return;
    }

    printf("Введите номер этапа (1-%d) для редактирования: ", NUM_STAGES);
    scanf("%d", &stage);
    stage--; // Преобразование в индекс массива

    if (stage < 0 || stage >= NUM_STAGES) {
        printf("Некорректный номер этапа.\n");
        return;
    }

    printf("Введите новое значение для этапа %d: ", stage + 1);
    scanf("%d", &newScore);
    table[athleteIndex][stage] = newScore;
    printf("Результат спортсмена %d на этапе %d обновлен.\n", athleteIndex + 1, stage + 1);
}

// Главная функция
int main() {
    // Установка локали на русский
        setlocale(LC_ALL, "ru_RU.UTF-8");
    printHeader();

    srand(time(NULL));
    int table[NUM_ATHLETES][NUM_STAGES + 2];
    int results[NUM_ATHLETES][4];   
    int option;

    while (1) {
        printf("\nМеню:\n");
        printf("1 - Генерация рандомных чисел в таблице\n");
        printf("2 - Сортировка результатов (от 1 до 15 места)\n");
        printf("3 - Показать лучшего спортсмена\n");
        printf("4 - Показать худшего спортсмена\n");
        printf("5 - Изменить результаты спортсмена\n");
        printf("6 - Сохранить данные в файл\n");
        printf("7 - Загрузить данные из файла\n");
        printf("8 - Выход\n");
        printf("Выберите опцию: ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                fillTable(table);
                printTable(table);
                break;
            case 2:
                calculateResults(table, results);
                sortResults(results);
                printResults(results);
                break;
            case 3:
                calculateResults(table, results);
                sortResults(results);
                findAthleteByCriteria(results, "лучший");
                break;
            case 4:
                calculateResults(table, results);
                sortResults(results);
                findAthleteByCriteria(results, "худший");
                break;
            case 5:
                editAthleteScore(table);
                break;
            case 6: {
                char filename[100];
                printf("Введите имя файла для сохранения данных: ");
                scanf("%s", filename);
                saveDataToFile(table, filename);
                break;
            }
            case 7: {
                char filename[100];
                printf("Введите имя файла для загрузки данных: ");
                scanf("%s", filename);
                if (loadDataFromFile(table, filename)) {
                    printf("Данные успешно загружены из файла.\n");
                    calculateResults(table, results);
                    sortResults(results);
                    printResults(results);
                }
                break;
            }
            case 8:
                printf("Выход из программы.\n");
                return 0;
            default:
                printf("Некорректный выбор. Пожалуйста, попробуйте снова.\n");
        }
    }

    return 0;
}


