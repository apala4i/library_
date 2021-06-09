#include "func.hpp"

int main(int argc, char **argv)
{
    // language localization
    system("chcp 65001");
    system("cls");
    setbuf(stdout, NULL);

    // param count check
    if (argc != 2)
    {
        printf("Wrong param count");
        return WRONG_PARAM;
    }

    // check file existing
    FILE *check = fopen(argv[1], "r");
    if (check == NULL)
    {
        check = fopen(argv[1], "wb");
        fclose(check);
    }
    else
        fclose(check);

    int choice = 0;
    while (choice != 7)
    {
        puts("Выберите необходимое действие:");
        puts("1) Вывести список книг");
        puts("2) Добавить книгу");
        puts("3) Удалить книгу");
        puts("4) Изменить книгу");
        puts("5) Поиск книги по названию");
        puts("6) Купить книгу");
        puts("7) Выход");

        get_choice(&choice);
        switch (choice)
        {
            case 1:
            {
                system("cls");
                switch (print_book(argv[1]))
                {
                    case EMPTY_FILE:
                    {
                        puts("Библиотека пуста.");
                        break;
                    }
                    case FILE_DOES_NOT_EXIST:
                    {
                        puts("Указанного файла не существует");
                        break;
                    }
                }
                break;
            }
            case 2:
            {
                system("cls");
                switch (add_book(argv[1]))
                {
                    case EMPTY_FILE:
                    {
                        puts("Библиотека пуста.");
                        break;
                    }
                    case INPUT_ERROR:
                    {
                        puts("Ошибка ввода.");
                        break;
                    }
                    case SIZE_ERROR:
                    {
                        puts("Такого индекса нет.");
                        break;
                    }
                    case FILE_DOES_NOT_EXIST:
                    {
                        puts("Указанного файла не существует");
                        break;
                    }
                }
                break;
            }
            case 3:
            {
                system("cls");
                int remove_index = 0;
                puts("Введите индекс удаляемой книги.\nПервая книга имеет индекс 0.");
                if (scanf("%d", &remove_index) != 1)
                {
                    printf("Ошибка ввода");
                    break;
                }
                while (getchar() != '\n');
                switch (del_book(argv[1], &remove_index))
                {
                    case EMPTY_FILE:
                    {
                        puts("Библиотека пуста.");
                        break;
                    }
                    case SIZE_ERROR:
                    {
                        puts("Такого индекса нет.");
                        break;
                    }
                    case FILE_DOES_NOT_EXIST:
                    {
                        puts("Указанного файла не существует");
                        break;
                    }
                    default:
                    {
                        printf("%d книга успешно удалена!\n\n", remove_index);
                        break;
                    }
                }
                break;
            }
            case 4:
            {
                system("cls");
                switch (change_book(argv[1]))
                {
                    case EMPTY_FILE:
                    {
                        puts("Библиотека пуста.");
                        break;
                    }
                    case SIZE_ERROR:
                    {
                        puts("Такого индекса нет.");
                        break;
                    }
                    case FILE_DOES_NOT_EXIST:
                    {
                        puts("Указанного файла не существует");
                        break;
                    }
                    case INPUT_ERROR:
                    {
                        puts("Ошибка ввода");
                        break;
                    }
                    case CHOICE_ERROR:
                    {
                        puts("Такого пункта нет");
                        break;
                    }
                }
                break;
            }
            case 5:

            {
                system("cls");
                switch (find_book(argv[1]))
                {
                    case EMPTY_FILE:
                    {
                        puts("Библиотека пуста.");
                        break;
                    }
                    case SIZE_ERROR:
                    {
                        puts("Такого индекса нет.");
                        break;
                    }
                    case FILE_DOES_NOT_EXIST:
                    {
                        puts("Указанного файла не существует");
                        break;
                    }
                    case INPUT_ERROR:
                    {
                        puts("Недопустимый формат названия");
                        break;
                    }
                    case BOOK_WAS_NOT_FOUND:
                    {
                        puts("Нет подходящих книг.\n");
                        break;
                    }
                }
                break;
            }
            case 6:
            {
                switch (buy_book(argv[1]))
                {
                    case EMPTY_FILE:
                    {
                        puts("Библиотека пуста.");
                        break;
                    }
                    case SIZE_ERROR:
                    {
                        puts("Такого индекса нет.");
                        break;
                    }
                    case FILE_DOES_NOT_EXIST:
                    {
                        puts("Указанного файла не существует");
                        break;
                    }
                    case INPUT_ERROR:
                    {
                        puts("Ошибка ввода");
                        break;
                    }
                }
                break;
            }
            case 7:
            {
                puts("До свидания!");
                return STABLE_WORK;
            }
            default:
            {
                puts("\nВведён неизвестный параметр, попробуйте снова.\n");
            }
        }
    }
}