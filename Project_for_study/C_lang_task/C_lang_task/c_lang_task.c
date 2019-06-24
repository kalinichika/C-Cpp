#include "c_lang_task.h"
#include "stdio.h"
#include "stdlib.h"
#include <string.h>


void print_number_table(short col, short row) {
    printf(" ");

    for(int j = 0; j < col*2-1; j++) {
        printf("*");
    }
    printf("\n");
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            printf("|%d", rand() % 9 + 0);
        }
        printf("|\n");
        if (i<row-1) printf("|");
        for (int j = 0; (j < col-1)&(i<row-1); j++) {
            printf("-+");
        }
        if (i<row-1) printf("-|\n");
    }
    printf(" ");
    for (int j = 0; j < col*2-1; j++) {
        printf("*");
    }
    printf("\n");
}

void write_nils_to_head_file(const char* full_fname, int N) {
    FILE *fp;
    fp = fopen(full_fname, "w");
    if (fp == NULL)
      {
        printf("Error: Failed to create file. Task 2.");
        fclose (fp);
        return;
      }
    //char c = 0x0;
    for (int i = 0; i < N; i++) fputc(0x00,fp);
    fclose(fp);
}

void write_ones_to_tail_file(const char* full_fname, int N) {
    FILE *fp;
    fp = fopen(full_fname, "a");
    if (fp == NULL) {
        printf("Error: Failed to create file. Task 3.");
        fclose (fp);
        return;
    }
    //char c = 0xff;
    for (int i = 0; i < N; i++) fputc(0xff,fp);

    fclose(fp);
}

void Init_file (const char* full_fname){
    FILE *fp;
    fp = fopen(full_fname, "w");
    if (fp == NULL) {
        printf("Error: Failed to create file. Task 4.");
        fclose (fp);
        return;
    }

    fprintf(fp, "Hello, World!\n"
                "I am a good girl.\n"
                "My name is Viktoriya.\n"
                "I study in Moscow.\n"
                "I study in the Russian Technological University.\n"
                "I am very happy!\n");
    fclose(fp);
    printf(     "Text in file:\n\n"
                "Hello, World!\n"
                "I am a good girl.\n"
                "My name is Viktoriya.\n"
                "I study in Moscow.\n"
                "I study in the Russian Technological University.\n"
                "I am very happy!\n");

}

int read_i_string_from_file(const char* full_fname, int i, char* out_str, int max_sz) {
    int i_str=1;
    int c;
    FILE *fp;
    fp = fopen(full_fname, "r");

    if (fp == NULL) {
        printf("File not found. Task 4.\n");
        return -1;
      }
    else printf("\nFile open.\n");

    while (i_str <  i) {
         c=fgetc(fp);
         if (c=='\n') {
             i_str++;
         }
         if (feof(fp)) {
             printf("Not enough lines %d in file. Task 4.",i);
             return -1;
         }
    }
    int j = 0;
    out_str[j]=fgetc(fp);
    j++;
    while((!feof(fp))&(j<max_sz)&(out_str[j-1]!='\n')){
        out_str[j]=fgetc(fp);
        j++;
    }
    out_str[j-1]='\0';

    fclose(fp);
    return j;
}

void TEST_memcpy_and_memset(void) {
    printf("\n\nTASK_5:\n");

    int *arr_int = (int*)malloc(40*sizeof(int));
    double *arr_double = (double*)malloc(20*sizeof(double));
    char *arr_char = (char*)malloc(80*sizeof(char));

    memset(arr_char,0x01,80*sizeof(char));
    for (int j=0; j<40; j=j+1){
        memset(arr_int+j,0x0,4);
        memset(arr_int+j,0x01,1);
    }
    memset(arr_double,0x0,20*sizeof(double));

    for (int j=0;j<10;j++) printf("%c ",arr_char[j]);
    printf("\n");
    for (int j=0;j<10;j++) printf("%d ",arr_int[j]);
    printf("\n");
    for (int j=0;j<10;j++) printf("%f ",arr_double[j]);
    printf("\n");

    memcpy(arr_char,arr_int,80*sizeof(char));
    memcpy(arr_int,arr_double,40*sizeof(int));
    memcpy(arr_double,arr_char,80*sizeof(char));

    for (int j=0;j<10;j++) printf("%c ",arr_char[j]);
    printf("\n");
    for (int j=0;j<10;j++) printf("%d ",arr_int[j]);
    printf("\n");
    for (int j=0;j<10;j++) printf("%f ",arr_double[j]);
    printf("\n");
}

void TEST_read_i_string_from_file(void) {
    printf("\nTASK_4,6:\n");

    const char* full_fname_str = "/home/student/Projects/c_lang_task/Text.txt";
    Init_file(full_fname_str);
    int i = 3;

    int max_sz = 27;
    char* str;
    str = (char*)malloc(sizeof(char)*max_sz);
    int size_str = read_i_string_from_file(full_fname_str, i, str, max_sz);
    printf("String %d (max_sz = %d): %s", i, max_sz, str);
    printf("\nSize string = %d\n", size_str);
    free(str);

    max_sz = 8;
    str = (char*)malloc(sizeof(char)*max_sz);
    size_str = read_i_string_from_file(full_fname_str, i, str, max_sz);
    printf("String %d (max_sz = %d): %s", i, max_sz, str);
    printf("\nSize string = %d\n", size_str);

    i=10;
    size_str = read_i_string_from_file(full_fname_str, i, str, max_sz);
    printf("\nSize string = %d\n", size_str);

    printf("\nString %d (max_sz = %d): %s", i, max_sz, str);

}


int main() {
    //Task 1
    printf("\nTASK_1:\n");
    printf("\nTable_1:\n");
    print_number_table(3, 6);
    printf("\nTable_2:\n");
    print_number_table(5, 2);
    printf("\nTable_3:\n");
    print_number_table(12,4);

    //Task 2, 3
    const char* full_fname = "/home/student/Projects/c_lang_task/File.txt";
    write_nils_to_head_file(full_fname, 5);
    write_ones_to_tail_file(full_fname, 7);

    //Task 5
    TEST_memcpy_and_memset();

    //Task 6
    TEST_read_i_string_from_file();

    printf("\n\nThe END.\n");
}
