#include <iostream>
#include <cstring>
#include <cstdio>

#define STABLE_WORK 0
#define WRONG_PARAM 1
#define INPUT_ERROR 2
#define SIZE_ERROR 3
#define CHOICE_ERROR 4
#define BOOK_WAS_NOT_FOUND 5
#define MAX_NAME_SIZE 30
#define MAX_GENRE_SIZE 30

#define FILE_DOES_NOT_EXIST -1
#define BUF_SIZE 40
#define EMPTY_FILE -2


typedef struct
{
    char name[MAX_NAME_SIZE + 1];
    char genre[MAX_GENRE_SIZE + 1];
    int price;
    int count;
    int code_number;
} book;
int print_book(char file_name[]);
int add_book(char file_name[]);
int get_choice(int *choice);
int get_struct_by_pos(FILE *file, const int position, book *new_book);
int put_struct_by_pos(FILE *file, const int position, book *new_book);
int del_book(char *file_name, int *remove_index);
int find_book(char *file_name);
int change_book(char *file_name);
int buy_book(char *file_name);
void size_find(FILE *file_name,  unsigned long long *size);