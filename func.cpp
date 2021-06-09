#include "func.hpp"

void size_find(FILE *file_name, unsigned long long *size)
{
    long int current = ftell(file_name);
    fseek(file_name, 0L, SEEK_END);
    *size = (ftell(file_name) / sizeof (book));
    fseek(file_name, current, SEEK_SET);
}

int get_struct_by_pos(FILE *file, const int position, book *new_book)
{
    unsigned int current_poz;
    current_poz = ftell(file);
    fseek(file, sizeof (book) * position, SEEK_SET);
    if (fread(new_book, sizeof (book), 1, file) != 1)
        return INPUT_ERROR;
    fseek(file, current_poz, SEEK_SET);
    return STABLE_WORK;
}

int put_struct_by_pos(FILE *file, const int position, book *new_book)
{
    unsigned int current_poz;
    current_poz = ftell(file);
    fseek(file, sizeof (book) * position, SEEK_SET);
    if (fwrite(new_book, sizeof (book), 1, file) != 1)
        return INPUT_ERROR;
    fseek(file, current_poz, SEEK_SET);
    return STABLE_WORK;
}

int get_choice(int *choice)
{
    char buf[2] = {0};
    buf[0] = (char)getchar();
    *choice = atoi(buf);
    if (getchar() != '\n' || *choice <= 0)
    {
        *choice = 0;
        while (getchar() != '\n');
        return INPUT_ERROR;
    }
    return STABLE_WORK;
}

int add_book(char *file_name)
{
    FILE *input_file = fopen(file_name, "rb+");
    if (file_name == NULL)
        return FILE_DOES_NOT_EXIST;

    book new_book;
    char buf[BUF_SIZE] = {0};

    // name input
    puts("Введите название");
    scanf("%[^\n]", buf);
    getchar();
    if (strlen(buf) > MAX_NAME_SIZE || strlen(buf) == 0)
    {
        fclose(input_file);
        return INPUT_ERROR;
    }
    strcpy(new_book.name, buf);

    // genre input
    buf[0] = 0;
    puts("Введите жанр книги");
    scanf("%[^\n]", buf);
    getchar();
    if (strlen(buf) > MAX_GENRE_SIZE || strlen(buf) == 0)
    {
        fclose(input_file);
        return INPUT_ERROR;
    }
    strcpy(new_book.genre, buf);

    // price input
    buf[0] = 0;
    puts("Введите цену книги");
    scanf("%[^\n]", buf);
    getchar();
    if (atoi(buf) <= 0)
    {
        fclose(input_file);
        return INPUT_ERROR;
    }
    new_book.price = atoi(buf);

    // count input
    buf[0] = 0;
    puts("Введите количество");
    scanf("%[^\n]", buf);
    getchar();
    if (atoi(buf) <= 0)
    {
        fclose(input_file);
        return INPUT_ERROR;
    }
    new_book.count = atoi(buf);

    // code_number input
    buf[0] = 0;
    puts("Введите код товара");
    scanf("%[^\n]", buf);
    getchar();
    if (atoi(buf) <= 0)
    {
        fclose(input_file);
        return INPUT_ERROR;
    }
    new_book.code_number = atoi(buf);

    fseek(input_file, 0L, SEEK_END);
    fwrite(&new_book, sizeof new_book, 1, input_file);
    puts("Данные о книге успешно записаны!");
    fclose(input_file);
    return STABLE_WORK;
}

int print_book(char *file_name)
{
    FILE *input_file = fopen(file_name, "rb+");
    if (file_name == NULL)
        return FILE_DOES_NOT_EXIST;

    book new_book;
    int size = 0;
    fseek(input_file, 0L, SEEK_END);
    size = ftell(input_file) / sizeof (book);
    fseek(input_file, 0L, SEEK_SET);
    if (size == 0)
    {
        fclose(input_file);
        return EMPTY_FILE;
    }
    puts("----------------------------------------------------------------------------------------------------------");
    printf("%5s|%30s|%30s|%10s|%10s|%15s|\n","NUM", "NAME","GENRE", "PRICE", "COUNT", "PRODUCT CODE");
    puts("----------------------------------------------------------------------------------------------------------");
    for (int i = 0; i < size; i++)
    {
        get_struct_by_pos(input_file, i, &new_book);
        printf("%5d|%30s|%30s|%10d|%10d|%15d|\n",i, new_book.name, new_book.genre, new_book.price,
               new_book.count, new_book.code_number);
        puts("----------------------------------------------------------------------------------------------------------");

    }
    fclose(input_file);
    return STABLE_WORK;
}

int del_book(char *file_name, int *remove_index)
{
    FILE *input_file = fopen(file_name, "rb");
    if (input_file == NULL)
        return FILE_DOES_NOT_EXIST;
    unsigned long long size = 0;

    size_find(input_file, &size);
    if (size == 0)
    {
        fclose(input_file);
        return EMPTY_FILE;
    }

    if (*remove_index >= size || *remove_index < 0)
    {
        fclose(input_file);
        return SIZE_ERROR;
    }

    FILE *edited_file = fopen("new.bin", "wb");
    book current_book;
    for (int i = 0; i < size; i++)
    {
        if (i != *remove_index)
        {
            get_struct_by_pos(input_file, i, &current_book);
            fwrite(&current_book, sizeof (book), 1, edited_file);
        }
    }
    fclose(input_file);
    fclose(edited_file);
    remove(file_name);
    rename("new.bin", file_name);

    return STABLE_WORK;
}

int change_book(char *file_name)
{
    FILE *input_file = fopen(file_name, "rb+");
    if (input_file == NULL)
        return FILE_DOES_NOT_EXIST;
    unsigned long long size = 0;

    size_find(input_file, &size);
    if (size == 0)
    {
        fclose(input_file);
        return EMPTY_FILE;
    }

    int change_index = 0;
    puts("Введите индекс изменяемой книги.\nПервая книга имеет индекс 0.");
    if (scanf("%d", &change_index) != 1)
    {
        fclose(input_file);
        return INPUT_ERROR;
    }
    while (getchar() != '\n');
    if (change_index >= size || change_index < 0)
    {
        fclose(input_file);
        return SIZE_ERROR;
    }

    book changed_book = {0};
    get_struct_by_pos(input_file, change_index, &changed_book);
    puts("Выберите пункт, который необходимо изменить");
    printf("1) Имя (исходное имя %s)\n", changed_book.name);
    printf("2) Жанр (исходный жанр %s)\n", changed_book.genre);
    printf("3) Цена (исходная цена %d)\n", changed_book.price);
    printf("4) Количество (исходное количество %d)\n", changed_book.count);
    printf("5) Номер товара (исходный код товара %d)\n", changed_book.code_number);
    int choice = 0;
    if (scanf("%d", &choice) != 1)
    {
        fclose(input_file);
        return INPUT_ERROR;
    }
    while (getchar() != '\n');
    char buf[BUF_SIZE] = {0};
    switch (choice)
    {
        case 1:
        {
            puts("Введите название\n");
            scanf("%[^\n]", buf);
            getchar();
            if (strlen(buf) > MAX_NAME_SIZE || strlen(buf) == 0)
            {
                fclose(input_file);
                return INPUT_ERROR;
            }
            strcpy(changed_book.name, buf);
            break;
        }
        case 2:
        {
            buf[0];
            puts("Введите жанр книги\n");
            scanf("%[^\n]", buf);
            getchar();
            if (strlen(buf) > MAX_GENRE_SIZE || strlen(buf) == 0)
            {
                fclose(input_file);
                return INPUT_ERROR;
            }
            strcpy(changed_book.genre, buf);
            break;
        }
        case 3:
        {
            puts("Введите цену книги\n");
            scanf("%[^\n]", buf);
            getchar();
            if (atoi(buf) <= 0)
            {
                fclose(input_file);
                return INPUT_ERROR;
            }
            changed_book.price = atoi(buf);
            break;
        }
        case 4:
        {
            puts("Введите количество\n");
            scanf("%[^\n]", buf);
            getchar();
            if (atoi(buf) <= 0)
            {
                fclose(input_file);
                return INPUT_ERROR;
            }
            changed_book.count = atoi(buf);
            break;
        }
        case 5:
        {
            puts("Введите код товара\n");
            scanf("%[^\n]", buf);
            getchar();
            if (atoi(buf) <= 0)
            {
                fclose(input_file);
                return INPUT_ERROR;
            }
            changed_book.code_number = atoi(buf);
            break;
        }
        default:
        {
            fclose(input_file);
            return CHOICE_ERROR;
        }
    }
    put_struct_by_pos(input_file, change_index, &changed_book);
    puts("Изменения успешно внесены!");
    fclose(input_file);
    return STABLE_WORK;
}

int find_book(char *file_name)
{
    FILE *input_file = fopen(file_name, "rb+");
    if (input_file == NULL)
        return FILE_DOES_NOT_EXIST;
    unsigned long long size = 0;

    size_find(input_file, &size);
    if (size == 0)
    {
        fclose(input_file);
        return EMPTY_FILE;
    }

    char buf[BUF_SIZE] = {0};
    puts("Введите название книги, которую необходимо найти\n");
    scanf("%[^\n]", buf);
    getchar();

    if (strlen(buf) > MAX_NAME_SIZE || strlen(buf) == 0)
    {
        fclose(input_file);
        return INPUT_ERROR;
    }
    int flag = 0;

    book search_book;
    for (int i = 0; i < size; i++)
    {
        get_struct_by_pos(input_file, i, &search_book);
        if (!strcmp(search_book.name, buf))
        {
            flag++;
            printf("Найдена %d книга с подходящим именем:\n", flag);
            printf("1) Имя %s\n", search_book.name);
            printf("2) Жанр %s\n", search_book.genre);
            printf("3) Цена %d\n", search_book.price);
            printf("4) Количество %d\n", search_book.count);
            printf("5) Номер товара %d\n", search_book.code_number);
        }
    }
    if (!flag)
    {
        fclose(input_file);
        return BOOK_WAS_NOT_FOUND;
    }
    printf("\nПоиск закончен\n\n", flag);
    fclose(input_file);
    return STABLE_WORK;
}

int buy_book(char *file_name)
{
    FILE *input_file = fopen(file_name, "rb+");
    if (input_file == NULL)
        return FILE_DOES_NOT_EXIST;
    unsigned long long size = 0;

    size_find(input_file, &size);
    if (size == 0)
    {
        fclose(input_file);
        return EMPTY_FILE;
    }

    int buy_index = 0;
    puts("Введите индекс купленной книги.\nПервая книга имеет индекс 0.");
    if (scanf("%d", &buy_index) != 1)
    {
        fclose(input_file);
        return INPUT_ERROR;
    }
    while (getchar() != '\n');
    if (buy_index >= size || buy_index < 0)
    {
        fclose(input_file);
        return SIZE_ERROR;
    }

    book purchased_book = {0};
    get_struct_by_pos(input_file, buy_index, &purchased_book);

    if (purchased_book.count > 1)
    {
        purchased_book.count -= 1;
        put_struct_by_pos(input_file, buy_index, &purchased_book);
        fclose(input_file);
        puts("Книга куплена, изменения внесены.\n");
    }
    else
    {
        fclose(input_file);
        del_book(file_name, &buy_index);
        printf("Книга куплена, но её больше нет в наличии, поэтому она была удалена\n");
    }
    return STABLE_WORK;
}