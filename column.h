//
// Created by ASUS on 09/04/2024.
//

typedef struct {
    char* name;
    int log_size, phys_size;
    int* data;
}COLUMN;




//Basic functions
COLUMN* create_column(char* title);
int insert_value(COLUMN*col, int value);
void delete_column(COLUMN *col);
void delete_row(COLUMN** dataframe, int num_columns, int row,int max_row);
void print_col(COLUMN *col);
int value_at_position(COLUMN*col,int pos);
int number_of_value_greater(COLUMN*col, int value);
int number_of_value_less(COLUMN*col, int value);
int number_of_value_equal(COLUMN*col, int value);



#ifndef PROJECT_C_DATAFRAME_COLUMN_H
#define PROJECT_C_DATAFRAME_COLUMN_H

#endif //PROJECT_C_DATAFRAME_COLUMN_H
