#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void cipherFile(FILE* file, int caesarShift) {
    char symbol;

    while ((symbol = fgetc(file)) != EOF) {
        if (islower(symbol)) {
            symbol = symbol + caesarShift;
            if (symbol > 'z') {
                symbol = symbol - 26;
            }
        } else if (isupper(symbol)) {
            symbol = symbol + caesarShift;
            if (symbol > 'Z') {
                symbol = symbol - 26;
            }
        }

        fputc(symbol, file);
    }
}

void clearFile(const char* filename) {
    FILE* file = fopen(filename, "w");

    fputc('\0', file);

    fclose(file);
}

char path[1024];
int main() {
    int choice = 0;

    while (choice != -1) {
        printf("Выберите пункт:\n");
        printf("1 - Ввести путь к файлу\n");
        printf("2 - Добавить строку в файл\n");
        printf("3 - Код Цезаря\n");
        printf("-1 - Выход\n");

        scanf("%d", &choice);

        char input[10];
        fgets(input, 10, stdin);

        if (input[0] >= -1 && input[0] <= '9') {
        } else {
            printf("n/a\n");
            continue;
        }

        if (choice == 1) {
            printf("Введите путь к файлу: ");
            scanf("%s", path);

            FILE* file = fopen(path, "r");

            if (file == NULL) {
                printf("n/a\n");
            } else {
                int character;
                int is_empty = 1;
                while ((character = fgetc(file)) != EOF) {
                    if (character == '\n') {
                        printf("\n");
                    } else
                        putchar(character);
                    is_empty = 0;
                }
                if (is_empty) printf("n/a\n");
                fclose(file);
            }

        } else if (choice == 2) {
            FILE* file = fopen(path, "a+");

            if (file == NULL) {
                printf("n/a\n");
            } else {
                char string[100];
                printf("Введите строку: ");
                fgets(string, 100, stdin);

                fprintf(file, "%s", string);

                rewind(file);

                int character;
                while ((character = fgetc(file)) != EOF) {
                    printf("%c", character);
                }

                printf("\n");

                fclose(file);
            }
        } else if (choice == 3) {
            char dirPath[100];
            int shift;
            char* buffer = malloc(256);
            fgets(buffer, 256, dir);

            printf("Введите путь к директории: ");
            scanf("%s", dirPath);

            printf("Введите сдвиг: ");
            scanf("%d", &shift);

            FILE* directory = fopen(dirPath, "r");
            if (!directory) {
                printf("Ошибка открытия директории");
                return 1;
            }
            while (fgets(buffer, 256, directory) != NULL) {
                char* filename = strtok(buffer, "\n");

                if (strstr(filename, ".c")) {
                    FILE* file = fopen(filename, "r+");
                    if (!file) {
                        continue;
                    }

                    cipherFile(file, shift);

                    fclose(file);

                } else if (strstr(filename, ".h")) {
                    FILE* file = fopen(filename, "r+");

                    clearFile(filename);

                    fclose(file);
                    free(buffer);

                }
            }
            fclose(directory);
        } else if (choice == -1) {
            break;
        }
    }
    return 0;
}
