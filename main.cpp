#include "func.hpp"

int main(int argc, char **argv)
{
    // language localization
    system("chcp 65001");
    system("cls");
    setbuf(stdout, nullptr);
    if (argc != 2)
    {
        printf("Wrong param count");
        return WRONG_PARAM;
    }

    // check file existing
    if (strstr(argv[1], ".bin") == NULL)
    {
        puts("Неверный формат файла.");
        return WRONG_TYPE;
    }
    FILE *check = fopen(argv[1], "r");
    if (check == NULL)
    {
        printf("Создана новая библиотека %s\n", argv[1]);
        check = fopen(argv[1], "wb");
        fclose(check);
    }
    else
        fclose(check);

    int choice = 0;
    while (choice != 9)
    {
        error_checker(print_book(argv[1]));
        puts("Выберите необходимое действие:");
        puts("1) Добавить книгу");
        puts("2) Удалить книгу");
        puts("3) Изменить книгу");
        puts("4) Поиск книги по названию");
        puts("5) Купить книгу");
        puts("6) Сортировка по цене");
        puts("7) Поиск максимальной цены");
        puts("8) Сортировка по имени");
        puts("9) Выход");

        get_choice(&choice);
        switch (choice)
        {
            case 1:
            {
                clear();
                system("cls");
                error_checker(add_book(argv[1]));
                wait();
                clear();
                break;
            }
            case 2:
            {
                int remove_index = 0;
                puts("Введите индекс удаляемой книги.\nПервая книга имеет индекс 0.");
                if (scanf("%d", &remove_index) != 1)
                {
                    printf("Ошибка ввода");
                    break;
                }
                while (getchar() != '\n');
                error_checker(del_book(argv[1], &remove_index));
                wait();
                clear();
                break;
            }
            case 3:
            {
                error_checker (change_book(argv[1]));
                wait();
                clear();
                break;
            }
            case 4:

            {
                error_checker(find_book(argv[1]));
                wait();
                clear();
                break;
            }
            case 5:
            {
                error_checker(buy_book(argv[1]));
                wait();
                clear();
                break;
            }
            case 6:
            {
                clear();
                error_checker(price_sort(argv[1]));
                wait();
                clear();
                break;
            }
            case 7:
            {
                error_checker(find_max(argv[1]));
                wait();
                clear();
                break;
            }
            case 8:
            {
                clear();
                error_checker(lex_sort(argv[1]));
                wait();
                clear();
                break;
            }
            case 9:
            {
                clear();
                puts("До свидания!");
                return STABLE_WORK;
            }
            default:
            {
                clear();
                puts("\nВведён неизвестный параметр, попробуйте снова.\n");
                wait();
                clear();
            }
        }
    }
}