#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INITIAL_SIZE 10
#define INCREMENTAL_SIZE 5
long valuetmp;
typedef struct
{
    void *key;
    void *value;
} Entry;

typedef struct
{
    Entry *entries;
    int size, total;
    Entry (*makeNode)(void *, void *);
    int (*compare)(void *, void *);
} SymbolTable;

Entry makePhone(void *name, void *phone)
{

    Entry result;
    result.key = strdup((char *)name); //tạo 1 vùng bộ nhớ mới có cùng kích thước với name và cpy value của name sang

    result.value = malloc(sizeof(int));
    memcpy(result.value, phone, sizeof(int));
    return result;
}

int comparePhone(void *key1, void *key2)
{
    return strcmp((char *)key1, (char *)key2);
}

SymbolTable* createSymbolTable(
                            Entry (*makeNode)(void *, void *),
                            int (*compare)(void *, void *)
                            )
{
    SymbolTable *table=(SymbolTable*)malloc(sizeof(SymbolTable));
    table->size=INITIAL_SIZE;
    table->total=0;
    table->entries=(Entry*)malloc(sizeof(Entry)*INITIAL_SIZE);
    table->makeNode=makeNode;
    table->compare=compare;
    return table;
}

void dropSymbolTable(SymbolTable *table)
{
    free(table);
}

Entry *getEntry(void *key, SymbolTable* table)
{
    for (int i = 0; i < table->total; i++)
    {
        if(comparePhone(table->entries[i].key,key)==0)
            return &table->entries[i];
    }
    return NULL;
}

void addEntry(void *key, void *value, SymbolTable *table)
{
    if (table->total >= table->size)
    {
        table->entries = (Entry *)realloc(table->entries, sizeof(Entry)*(table->size + INCREMENTAL_SIZE));
        table->size += INCREMENTAL_SIZE;
        printf("increased size\n");
    }
    if (getEntry(key, table) == NULL)
    {
        table->entries[table->total]=makePhone(key,value);
        table->total++;
    }
    else
        memcpy(getEntry(key, table)->value,value,sizeof(int));

    //printf("done add\n");
}

void printPhonetable(SymbolTable *table)
{
    for (int i = 0; i < table->total; i++)
    {
        printf("Name: %s\n",(char*) table->entries[i].key);
        //printf("Phone: %d\n",atoi((char*)table->entries[i].value));
        printf("phone %d\n",*(long*)table->entries[i].value);
    }
    printf("size: %d\n", table->size);
    printf("total: %d\n", table->total);
}
void* longtovoid(long i)
{
    valuetmp=i;
    return &valuetmp;
}
int main()
{       
    SymbolTable *ptable=createSymbolTable(makePhone,comparePhone);
    FILE *input=fopen("text.txt","r");
    if(input==NULL)
    {    
        printf("cant open file\n");
        return 0;
    }
    while(!feof(input))
    {
        char key[100];
        long value;
        fscanf(input,"%s %d\n",key,&value);
        addEntry(key,&value,ptable);
    }
    printf("start listing:\n");
    printPhonetable(ptable);
    return 0;

}