#include "column.h"

COLUMN** create_dataframe(int num_columns);

void fill_data_frame(COLUMN **dataframe,int num_columns, int rows);
void hard_fill_data_frame(COLUMN **dataframe,int num_columns, int rows);

void display_data_frame(COLUMN **dataframe,int num_columns, int num_rows, int num_columns_to_display, int num_rows_to_display);
void rename_column(COLUMN** dataframe,int num_columns,int rows);
void search_dataFrame_for_value(COLUMN** dataframe, int num_columns, int rows);
void replace_value(COLUMN** dataframe, int num_columns, int rows);
void access_value(COLUMN** dataframe, int num_columns, int rows);
void display_names(COLUMN** dataframe, int num_column);
void number_of_cells_equal(COLUMN** dataframe, int num_column, int rows);
void number_of_cells_greater(COLUMN** dataframe, int num_columns, int rows);
void number_of_cells_smaller(COLUMN** dataframe, int num_columns, int rows);
void delete_row_dataframe(COLUMN** dataframe, int num_columns, int* rows);
void add_row(COLUMN** dataframe, int num_columns, int* num_rows);
void delete_column_dataframe(COLUMN** dataframe, int* num_columns, int rows);
void add_column(COLUMN*** dataframe, int* num_columns, int rows);


//MENU
void main_menu(COLUMN**dataframe, int num_rows, int num_cols);
//SUB MENUS
void menu_filling(COLUMN**dataframe, int num_rows, int num_cols);
void menu_displaying(COLUMN** dataframe,int num_rows,int num_cols);
void usual_operations_menu(COLUMN** dataframe,int num_rows,int num_cols);
void statistics_menu(COLUMN **dataframe,int num_rows,int num_cols);
#ifndef PROJECT_C_DATAFRAME_DATAFRAME_H
#define PROJECT_C_DATAFRAME_DATAFRAME_H

#endif //PROJECT_C_DATAFRAME_DATAFRAME_H
