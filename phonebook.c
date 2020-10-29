#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INITIAL_SIZE 10
#define INCREMENTAL_SIZE 5

typedef struct
{
    char name[80];
    long number;
} PhoneEntry;

typedef struct
{
    PhoneEntry *entries;
    int size;
    int total;

} PhoneBook;

PhoneBook *pbook;

PhoneBook *createPhoneBook()
{
    PhoneBook *pb = (PhoneBook *)malloc(sizeof(PhoneBook));
    pb->size = INITIAL_SIZE;
    pb->total = 0;
    pb->entries = (PhoneEntry *)malloc(sizeof(PhoneEntry) * INITIAL_SIZE);
    return pb;
}
void dropPhoneBook(PhoneBook *book)
{
    free(book);
}

PhoneEntry *getPhoneNumber(char *name, PhoneBook *book)
{
    for (int i = 0; i < book->total; i++)
    {
        if (strcmp(book->entries[i].name, name) == 0)
        {
            return &book->entries[i];
        }
    }
    return NULL;
}

void addPhoneNumber(char *name, long number, PhoneBook *book)
{
    if (book->total >= book->size)
    {
        book->entries = (PhoneEntry *)realloc(book->entries, sizeof(PhoneEntry)*(book->size + INCREMENTAL_SIZE));
        book->size += INCREMENTAL_SIZE;
        printf("increased size\n");
    }
    if (getPhoneNumber(name, book) == NULL)
    {
        strcpy(book->entries[book->total].name, name);
        book->entries[book->total].number = number;
        book->total++;
    }
    else
    {
        for (int i = 0; i < book->size; i++)
        {
            if (strcmp(book->entries[i].name, name) == 0)
            {
                book->entries[i].number = number;
                printf("dupplicated\n");
            }
        }
    }
}

void printPhoneBook(PhoneBook *book)
{
    for (int i = 0; i < book->total; i++)
    {
        printf("Name: %s\n", book->entries[i].name);
        printf("Phone: %ld\n", book->entries[i].number);
    }
    printf("size: %d\n", book->size);
    printf("total: %d\n", book->total);
}

int main()
{
    pbook = createPhoneBook();
    addPhoneNumber("1", 11, pbook);
    addPhoneNumber("2", 21, pbook);
    addPhoneNumber("2", 22, pbook);
    addPhoneNumber("3", 31, pbook);
    addPhoneNumber("3", 32, pbook);
    addPhoneNumber("3", 33, pbook);
    addPhoneNumber("4", 41, pbook);
    addPhoneNumber("4", 42, pbook);
    addPhoneNumber("4", 43, pbook);
    addPhoneNumber("4", 44, pbook);
    addPhoneNumber("a", 1, pbook);
    addPhoneNumber("b", 2, pbook);
    addPhoneNumber("c", 3, pbook);
    addPhoneNumber("d", 4, pbook);
    addPhoneNumber("e", 5, pbook);
    addPhoneNumber("f", 6, pbook);
    addPhoneNumber("5", 52, pbook);
    addPhoneNumber("5", 53, pbook);
    addPhoneNumber("5", 54, pbook);
    addPhoneNumber("5", 55, pbook);
    printf("start listing:\n");
    printPhoneBook(pbook);
    return 0;
}