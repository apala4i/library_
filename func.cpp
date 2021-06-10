#include "func.hpp"

void clear()
{
//    system("clear");
    system("cls");
}

void wait()
{
//    system("sleep .1");
    system("pause");
}

void error_checker(int value)
{
    switch (value)
    {
        case INPUT_ERROR:
        {
            printf("\nОшибка ввода\n");
            break;
        }
        case SIZE_ERROR:
        {
            printf("\nОшибка размерности\n");
            break;
        }
        case EMPTY_FILE:
        {
            printf("\nБиблиотека пуста\n");
            break;
        }
        case BOOK_WAS_NOT_FOUND:
        {
            printf("\nПодходящих книг не было найдено\n");
            break;
        }
        case CHOICE_ERROR:
        {
            printf("Ошибка параметра");
            break;
        }
    }
}

int lex_s_dec(const void *first, const void *second)
{
    return strcmp(((book *)first)->name, ((book *)second)->name);
}

int lex_s_inc(const void *first, const void *second)
{
    return strcmp(((book *)second)->name,((book *)first)->name);
}

int price_s_inc(const void *first, const void *second)
{
    if (((book *)second)->price > ((book *)first) -> price)
        return -1;
    else if (((book *)second)->price < ((book *)first) -> price)
        return 1;
    else
        return 0;
}

int price_s_dec(const void *first, const void *second)
{
    if (((book *)second)->price < ((book *)first) -> price)
        return -1;
    else if (((book *)second)->price > ((book *)first) -> price)
        return 1;
    else
        return 0;
}

int find_max(char *file_name)
{
    unsigned long long size = 0;
    FILE *input = fopen(file_name, "rb");
    size_find(input, &size);
    if (size == 0)
    {
        return EMPTY_FILE;
    }
    book find = { 0 };
    char name[30];
    float answer = 0;
    for (int i = 0; i < size; i++)
    {
        get_struct_by_pos(input, i, &find);
        if (find.price > answer)
        {
            strcpy(name, find.name);
            answer = find.price;
        }
    }
    printf("Максимальная цена %.2f у книги под названием %s\n\n", answer, name);
    fclose(input);
    return STABLE_WORK;
}

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
    if (*choice <= 0 || getchar() != '\n')
    {
        *choice = 0;
        while (getchar() != '\n');
        return INPUT_ERROR;
    }
    return STABLE_WORK;
}

int add_book(char *file_name)
{
    book new_book;
    char buf[BUF_SIZE] = {0};

    // name input
    puts("Введите название");
    scanf("%[^\n]", buf);
    while(getchar() != '\n');
    if (strlen(buf) > MAX_NAME_SIZE || strlen(buf) == 0)
    {
        return INPUT_ERROR;
    }
    strcpy(new_book.name, buf);

    // genre input
    buf[0] = 0;
    puts("Введите жанр книги");
    scanf("%[^\n]", buf);
    while(getchar() != '\n');
    if (strlen(buf) > MAX_GENRE_SIZE || strlen(buf) == 0)
    {
        return INPUT_ERROR;
    }
    strcpy(new_book.genre, buf);

    // price input
    buf[0] = 0;
    puts("Введите цену книги");
    scanf("%[^\n]", buf);
    while(getchar() != '\n');
    if (atof(buf) <= 0)
    {
        return INPUT_ERROR;
    }
    new_book.price = (float)atof(buf);

    // count input
    buf[0] = 0;
    puts("Введите количество");
    scanf("%[^\n]", buf);
    while(getchar() != '\n');
    if (atoi(buf) <= 0)
    {
        return INPUT_ERROR;
    }
    new_book.count = atoi(buf);

    // code_number input
    buf[0] = 0;
    puts("Введите код товара");
    scanf("%[^\n]", buf);
    while(getchar() != '\n');
    if (atoi(buf) <= 0)
    {
        return INPUT_ERROR;
    }
    new_book.code_number = atoi(buf);

    FILE *input_file = fopen(file_name, "rb+");
    fseek(input_file, 0L, SEEK_END);
    fwrite(&new_book, sizeof (book), 1, input_file);
    puts("Данные о книге успешно записаны!");
    fclose(input_file);
    return STABLE_WORK;
}

int print_book(char *file_name)
{
    FILE *input_file = fopen(file_name, "rb+");

    unsigned long long size;
    size_find(input_file,&size);
    if (size == 0)
    {
        fclose(input_file);
        return EMPTY_FILE;
    }
    book *books = (book *)malloc(sizeof (book) * size);
    fread(books, sizeof (book), size, input_file);
    fclose(input_file);

    puts("----------------------------------------------------------------------------------------------------------");
    printf("%5s|%30s|%30s|%10s|%10s|%15s|\n","NUM", "NAME","GENRE", "PRICE", "COUNT", "PRODUCT CODE");
    puts("----------------------------------------------------------------------------------------------------------");
    for (int i = 0; i < size; i++)
    {
        printf("%5d|%30s|%30s|%10.2f|%10d|%15d|\n",i, books[i].name, books[i].genre, books[i].price,
               books[i].count, books[i].code_number);
        puts("----------------------------------------------------------------------------------------------------------");

    }
    fclose(input_file);
    free(books);
    return STABLE_WORK;
}

int del_book(char *file_name, const int *remove_index)
{
    FILE *input_file = fopen(file_name, "rb");
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
    book *books = (book *) malloc(size * sizeof (book));
    fread(books, sizeof (book), size, input_file);
    fclose(input_file);
    for (int i = *remove_index; i < size; i++)
    {
        books[i] = books[i + 1];
    }
    FILE *res_file = fopen(file_name, "wb");
    fwrite(books, sizeof (book), size - 1, res_file);
    fclose(res_file);
    free(books);
    return STABLE_WORK;
}

int change_book(char *file_name)
{
    FILE *input_file = fopen(file_name, "rb+");
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
        while(getchar() != '\n');
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
    printf("3) Цена (исходная цена %.2f)\n", changed_book.price);
    printf("4) Количество (исходное количество %d)\n", changed_book.count);
    printf("5) Номер товара (исходный код товара %d)\n", changed_book.code_number);
    int choice = 0;
    if (scanf("%d", &choice) != 1)
    {
        while(getchar() != '\n');
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
            while(getchar() != '\n');
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
            while(getchar() != '\n');
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
            while(getchar() != '\n');
            if (atof(buf) <= 0)
            {
                fclose(input_file);
                return INPUT_ERROR;
            }
            changed_book.price = atof(buf);
            break;
        }
        case 4:
        {
            puts("Введите количество\n");
            scanf("%[^\n]", buf);
            while(getchar() != '\n');
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
            while(getchar() != '\n');
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
    unsigned long long size = 0;

    size_find(input_file, &size);
    if (size == 0)
    {
        fclose(input_file);
        return EMPTY_FILE;
    }
    book *books = (book *) malloc(sizeof (book) * size);
    fread(books, sizeof (book), size, input_file);
    fclose(input_file);

    char *buf = (char *) calloc(BUF_SIZE, sizeof(char));
    puts("Введите название книги, которую необходимо найти\n");
    scanf("%[^\n]", buf);
    while(getchar() != '\n');

    if (strlen(buf) > MAX_NAME_SIZE || strlen(buf) == 0)
    {
        return INPUT_ERROR;
    }
    int flag = 0;

    for (int i = 0; i < size; i++)
    {
        if (!strcmp(buf, books[i].name))
        {
            flag++;
            printf("Найдена %d книга с подходящим именем:\n", flag);
            printf("1) Имя %s\n", books[i].name);
            printf("2) Жанр %s\n", books[i].genre);
            printf("3) Цена %.2f руб\n", books[i].price);
            printf("4) Количество %d\n", books[i].count);
            printf("5) Номер товара %d\n", books[i].code_number);
        }
    }
    free(books);
    free(buf);
    if (!flag)
    {
        return BOOK_WAS_NOT_FOUND;
    }
    printf("\n\nПоиск закончен\n\n", flag);
    return STABLE_WORK;
}

int buy_book(char *file_name)
{
    FILE *input_file = fopen(file_name, "rb+");
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

int lex_sort(char *file_name)
{
    FILE *input_file = fopen(file_name, "rb");
    unsigned long long size;
    size_find(input_file, &size);
    if (size == 0)
    {
        fclose(input_file);
        return SIZE_ERROR;
    }
    book *books = (book *)malloc(sizeof (book) * size);
    fread(books, sizeof(book) * size, size, input_file);
    fclose(input_file);

    printf("Выберите сортировку:\n1) По возрастанию\n2) По убыванию\n");
    int choice;
    scanf("%d", &choice);
    while(getchar() != '\n');
    if (choice != 1 && choice != 2)
        return INPUT_ERROR;
    if (choice == 2)
        qsort(books, size, sizeof (book), lex_s_dec);
    else
        qsort(books, size, sizeof (book), lex_s_inc);
    FILE *input = fopen(file_name, "wb");
    fwrite(books, sizeof (book), size, input);
    free(books);
    fclose(input_file);
    printf("Библиотека успешно отсортирована.\n");
    return STABLE_WORK;
}

int price_sort(char *file_name)
{
    FILE *input_file = fopen(file_name, "rb");
    unsigned long long size;
    size_find(input_file, &size);
    if (size == 0)
    {
        return SIZE_ERROR;
    }
    book *books = (book *)malloc(sizeof (book) * size);
    fread(books, sizeof(book) * size, size, input_file);
    fclose(input_file);

    printf("Выберите сортировку:\n1) По возрастанию\n2) По убыванию\n");
    int choice;
    scanf("%d", &choice);
    while(getchar() != '\n');
    if (choice != 1 && choice != 2)
        return INPUT_ERROR;
    if (choice == 2)
        qsort(books, size, sizeof (book), price_s_dec);
    else
        qsort(books, size, sizeof (book), price_s_inc);
    FILE *input = fopen(file_name, "wb");
    fwrite(books, sizeof (book), size, input);
    free(books);
    fclose(input_file);
    printf("Библиотека успешно отсортирована.\n");
    return STABLE_WORK;
}