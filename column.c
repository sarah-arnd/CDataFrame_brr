//
// Created by ASUS on 09/04/2024.
//
#define REALOC_SIZE 256
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "column.h"

COLUMN* create_column(char* title){
    COLUMN* column=(COLUMN*)malloc(sizeof(COLUMN));
    column->data=NULL;
    column->name=title;
    column->phys_size=REALOC_SIZE;
    column->log_size=0;
    return column;
}


int insert_value(COLUMN* col, int value) {
    //check is the data array has been initialized before, if not it does it
    if(col->data==NULL){
        col->data = (int*)malloc(REALOC_SIZE * sizeof(int));
    }
    if (col->log_size >= col->phys_size) {
        // Reallocate memory for the data array if the array is full
        int* new_data = (int*)realloc(col->data, (col->phys_size + REALOC_SIZE) * sizeof(int));
        if (new_data == NULL) {
            //If memory allocation failed
            return 0;
        }
        col->data = new_data;
        col->phys_size += REALOC_SIZE;
    }
    // Add the value to the next available position
    col->data[col->log_size] = value;
    col->log_size++;
    return 1;
}

void delete_column(COLUMN **col){
    free((*col)->data);
    free(*col);
    *col=NULL;
}

void print_col(COLUMN *col){
    for(int i=0;i<col->log_size;i++){
        printf("[%d]  %d\n",i,col->data[i]);
    }
}

int number_of_occurences(COLUMN *col,int value){
    int number_of_occ=0;
    for(int i=0;i<col->log_size;i++){
        if(col->data[i]==value){
            number_of_occ++;
        }
    }
    return number_of_occ;
}

int value_at_position(COLUMN*col,int pos){
    return col->data[pos];
}

int number_of_value_greater(COLUMN*col, int value){
    int nb_of_value=0;
    for(int i=0;i<col->log_size;i++){
        if(col->data[i]>value){
            nb_of_value++;
        }
    }
    return nb_of_value;
}

int number_of_value_less(COLUMN*col, int value){
    int nb_of_value=0;
    for(int i=0;i<col->log_size;i++){
        if(col->data[i]<value){
            nb_of_value++;
        }
    }
    return nb_of_value;
}

int number_of_value_equal(COLUMN*col, int value){
    int nb_of_value=0;
    for(int i=0;i<col->log_size;i++){
        if(col->data[i]==value){
            nb_of_value++;
        }
    }
    return nb_of_value;
}

//CDataFrame
COLUMN** create_dataframe(int num_columns) {
    COLUMN** dataframe = (COLUMN**)malloc(num_columns * sizeof(COLUMN*));
    if (dataframe == NULL) {
        // Memory allocation failed
        return NULL;
    }

    for (int i = 0; i < num_columns; i++) {
        dataframe[i] = create_column(""); // Create an empty column with an empty title
        if (dataframe[i] == NULL) {
            // Error creating column free previously allocated memory
            for (int j = 0; j < i; j++) {
                free(dataframe[j]);
            }
            free(dataframe);
            return NULL;
        }
    }
    return dataframe;
}

void fill_data_frame(COLUMN **dataframe,int num_columns, int rows){
    for (int i=0;i<rows;i++){
        printf("Row %d\n",i);
        for(int j=0;j<num_columns;j++){
            printf("Column %d\n",j);
            printf("Enter the value to add: \n");
            int value;
            scanf("%d",&value);
            insert_value(dataframe[j], value);
        }
    }
}

void hard_fill_data_frame(COLUMN **dataframe,int num_columns, int rows){
    srand(time(NULL));
    for (int i=0;i<rows;i++){
        for(int j=0;j<num_columns;j++){
            int random_value = rand();
            printf("%d  ",random_value);
            insert_value(dataframe[j], random_value);
        }
    }
    printf("The dataFrame has been hard filled\n");
}

void display_data_frame(COLUMN **dataframe,int num_columns, int num_rows,int num_columns_to_display, int num_rows_to_display){
    if(num_columns<num_columns_to_display || num_rows<num_rows_to_display){
        //vérifie que la partie de la dataFrame à afficher est bien dans les limites de la dataFrame
        printf("Invalid bounds\n");
    }
    else{
        for(int i=0;i<num_rows_to_display;i++){
            printf("\nRow %d\n",i);
            for(int j=0;j<num_columns_to_display;j++){
                printf("%d  ",dataframe[j]->data[i]);
            }
        }
    }
}
