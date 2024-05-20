#include "dataFrame.h"
#define REALOC_SIZE 256
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


//CDataFrame
COLUMN** create_dataframe(int num_columns) {
    COLUMN** dataframe = (COLUMN**)malloc(num_columns * sizeof(COLUMN*));
    if (dataframe == NULL) {
        // Memory allocation failed
        return NULL;
    }

    for (int i = 0; i < num_columns; i++) {
        dataframe[i] = create_column("default"); // Create an empty column with an empty title
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
            insert_value(dataframe[j], random_value);
        }
    }
    printf("The dataFrame has been hard filled\n");
}

void display_data_frame(COLUMN **dataframe,int num_columns, int num_rows,int num_columns_to_display, int num_rows_to_display){
    if(num_columns<num_columns_to_display || num_rows<num_rows_to_display || num_columns_to_display<0 || num_rows_to_display<0){
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
    printf("\n");
}

void rename_column(COLUMN** dataframe,int num_columns, int rows) {
    int column_to_rename;
    char new_title[100]; // Assuming a maximum length for the title
    printf("Which column would you like to rename?\n");
    scanf("%d", &column_to_rename);
    printf("What would you like to rename it to?\n");
    scanf("%s", new_title);

    dataframe[column_to_rename]->name=strdup(new_title);
}


void search_dataFrame_for_value(COLUMN** dataframe, int num_columns, int rows){
    int value;
    printf("Enter the value to search for : \n");
    scanf("%d",&value);
    int found=0;
    for (int i=0;i<rows;i++){
        for(int j=0;j<num_columns;j++){
            if(dataframe[i]->data[j]==value){
                printf("The value was found in column %d and row %d\n",i,j);
                found=1;
            }
        }
    }
    if (found==0){
        printf("The value was not found\n");
    }
}

void replace_value(COLUMN** dataframe, int num_columns, int rows){
    int value;
    int value_rows;
    int value_column;
    printf("Enter the new value : \n");
    scanf("%d",&value);
    printf("Enter the row of the value to replace : \n");
    scanf("%d",&value_rows);
    printf("Enter the column of the value to replace : \n");
    scanf("%d",&value_column);
    if (value_rows>rows || value_column>num_columns){
        printf("Invalid indices \n");
    }else{
        dataframe[value_column]->data[value_rows] = value;
    }
}

void access_value(COLUMN** dataframe, int num_columns, int rows){
    int value_rows;
    int value_column;
    printf("Enter the row of the value to access : \n");
    scanf("%d",&value_rows);
    printf("Enter the column of the value to replace : \n");
    scanf("%d",&value_column);
    if (value_rows>=rows || value_column>=num_columns){
        printf("Invalid indices \n");
    }else{
        printf("%d",dataframe[value_column]->data[value_rows]);
    }
}

void display_names(COLUMN** dataframe, int num_columns){
    for(int j=0;j<num_columns;j++){
        printf("%s  ",dataframe[j]->name);
    }
    printf("\n");
}

void number_of_cells_equal(COLUMN** dataframe, int num_columns, int rows){
    int value;
    int count =0;
    printf("Enter the value to look for: \n");
    scanf("%d",&value);
    for (int i=0;i<rows;i++){
        count+= number_of_value_equal(dataframe[i],value);
    }
    printf("There is %d cells equal to %d \n",value);
}

void general_info(COLUMN** dataframe, int num_columns, int rows){
    printf("%d %d ",num_columns,rows);
    float average=0;
    int number_of_cells=num_columns*rows;
    int smallest_value=dataframe[0]->data[0];
    int biggest_value=dataframe[0]->data[0];
    //compute the average value
    for (int i=0;i<rows;i++){
        for(int j=0;j<num_columns;j++){
            average+=dataframe[j]->data[i];
        }
    }
    average=average/number_of_cells;

    //find the smallest value
    for (int i=0;i<rows;i++){
        for(int j=0;j<num_columns;j++){
            if(dataframe[i]->data[j]<smallest_value){
                smallest_value=dataframe[i]->data[j];
            }
        }
    }
    //find the biggest value
    for (int i=0;i<rows;i++){
        for(int j=0;j<num_columns;j++){
            if(dataframe[i]->data[j]>smallest_value){
                biggest_value=dataframe[i]->data[j];
            }
        }
    }
    printf("There are %d values, the average is %.2f, the smallest value is %d, the biggest value is %d\n", number_of_cells, average, smallest_value, biggest_value);

}


void number_of_cells_smaller(COLUMN** dataframe, int num_columns, int rows){
    int value;
    int count =0;
    printf("Enter the value to look for: \n");
    scanf("%d",&value);
    for (int i=0;i<rows;i++){
        count+= number_of_value_less(dataframe[i],value);
    }
    printf("There is %d cells smaller than %d \n",count,value);
}

void number_of_cells_greater(COLUMN** dataframe, int num_columns, int rows){
    int value;
    int count =0;
    printf("Enter the value to look for: \n");
    scanf("%d",&value);
    for (int i=0;i<rows;i++){
        count+=number_of_value_greater(dataframe[i],value);
    }
    printf("There is %d cells greater than %d \n",count,value);
}

void delete_column_dataframe(COLUMN** dataframe, int* num_columns, int rows){
    int col;
    printf("Which column do you want to delete : \n");
    scanf("%d",&col);
    if (col>*num_columns || col<0) return;
    delete_column(dataframe[col]);
    for (int i = col; i < *num_columns - 1; i++) {
        dataframe[i] = dataframe[i + 1];
    }
    *num_columns=*num_columns-1;
}

void add_column(COLUMN*** dataframe, int* num_columns, int rows) {
    char column_title[100];
    printf("Enter the title for the new column: \n");
    scanf("%s", column_title);

    // Create new column
    COLUMN* new_column = create_column(column_title);
    if (new_column == NULL) {
        printf("Memory allocation failed for the new column.\n");
        return;
    }

    // Reallocate the DataFrame to include the new column
    COLUMN** new_dataframe = (COLUMN**)realloc(*dataframe, (*num_columns + 1) * sizeof(COLUMN*));
    if (new_dataframe == NULL) {
        printf("Memory reallocation failed for the DataFrame.\n");
        delete_column(new_column); // Clean up allocated memory for the new column
        return;
    }

    // Add the new column to the DataFrame
    new_dataframe[*num_columns] = new_column;
    *dataframe = new_dataframe;
    (*num_columns)++;

    //initialize the new column with default values
    for (int i = 0; i < rows; i++) {
        insert_value(new_column, 0);
    }

    printf("New column '%s' added successfully.\n", column_title);
}

void add_row(COLUMN** dataframe, int num_columns, int* num_rows) {
    for (int i = 0; i < num_columns; i++) {
        insert_value(dataframe[i], 0); // Initialize the new row with default values (e.g., 0)
    }
    (*num_rows)++;
    printf("New row added successfully.\n");
}

void delete_row_dataframe(COLUMN** dataframe, int num_columns, int* num_rows) {
    int row_to_delete;
    printf("Which row do you want to delete: \n");
    scanf("%d", &row_to_delete);

    if (row_to_delete >= *num_rows || row_to_delete < 0) {
        printf("Invalid row index.\n");
        return;
    }

    for (int i = 0; i < num_columns; i++) {
        for (int j = row_to_delete; j < *num_rows - 1; j++) {
            dataframe[i]->data[j] = dataframe[i]->data[j + 1];
        }
        dataframe[i]->log_size--;
    }

    (*num_rows)--;
    printf("Row %d deleted successfully.\n", row_to_delete);
}

void menu_filling(COLUMN**dataframe, int num_rows, int num_cols){
    int choice=0;
    printf("What functionalities would you like to use : \n"
           "    1)Fill the matrix with manual input\n"
           "    2)Hard fill the matrix\n"
           "    3)Return\n");
    scanf("%d",&choice);
    if(choice>3){
        printf("Invalid input\n");
        menu_filling(dataframe,num_rows,num_cols);
    }else{
        if(choice==1){
            fill_data_frame(dataframe,num_rows,num_cols);
            main_menu(dataframe,num_rows,num_cols);
        }else if(choice==2){
            hard_fill_data_frame(dataframe,num_cols,num_rows);
            main_menu(dataframe,num_rows,num_cols);
        }else if (choice==3){
            main_menu(dataframe,num_rows,num_cols);
        }
    }
}
void menu_displaying(COLUMN **dataframe,int num_rows,int num_cols){
    int choice=0;
    printf("What functionalities would you like to use : \n"
           "    1)Display the entire DataFrame\n"
           "    2)Display a part of the DataFrame rows\n"
           "    3)Display a part of the DataFrame columns\n"
           "    4)Return\n");
    scanf("%d",&choice);
    if(choice>4){
        printf("Invalid input");
        menu_displaying(dataframe, num_rows, num_cols);
    }else{
        if(choice==1){
            display_data_frame(dataframe,num_cols,num_rows,num_cols,num_rows);
            menu_displaying(dataframe, num_rows, num_cols);

        }else if (choice==2){
            int rows_to_display;
            printf("At which rows would you like to stop displaying the dataFrame ? \n");
            scanf("%d",&rows_to_display);
            display_data_frame(dataframe,num_cols,num_rows,num_cols,rows_to_display);
            menu_displaying(dataframe, num_rows, num_cols);

        }else if(choice==3){
            int cols_to_display;
            printf("At which columns would you like to stop displaying the dataFrame ? \n");
            scanf("%d",&cols_to_display);
            display_data_frame(dataframe,num_cols,num_rows,cols_to_display,num_rows);
            menu_displaying(dataframe, num_rows, num_cols);

        }else if(choice==4){
            main_menu(dataframe, num_rows, num_cols);
        }
    }
}
void usual_operations_menu(COLUMN** dataframe,int num_rows,int num_cols){
    int choice=0;
    printf("What functionalities would you like to use : \n"
           "    1)Add a row\n"
           "    2)Delete a row\n"
           "    3)Add a column\n"
           "    4)Delete a column\n"
           "    5)Rename a column\n"
           "    6)Search for a value in the DataFrame\n"
           "    7)Replace a value in the DataFrame\n"
           "    8)Display column names\n"
           "    9)Find a value with its index\n"
           "    10)Return\n");
    scanf("%d",&choice);
    if(choice>10){
        printf("Invalid Input\n");
        usual_operations_menu(dataframe,num_rows, num_cols);
    }else{
        if(choice==1){
            add_row(dataframe, num_cols, &num_rows);
            usual_operations_menu(dataframe, num_rows, num_cols);
        }else if(choice==2){
            delete_row_dataframe(dataframe, num_cols, &num_rows);
            usual_operations_menu(dataframe, num_rows, num_cols);
        }else if(choice==3){
            add_column(&dataframe, &num_cols, num_rows);
            usual_operations_menu(dataframe, num_rows, num_cols);
        }else if (choice==4){
            delete_column_dataframe(dataframe,&num_cols,num_rows);
            usual_operations_menu(dataframe,num_rows,num_cols);
        }else if(choice==5){
            //doesnt work :(
            rename_column(dataframe,num_cols, num_rows);
            usual_operations_menu(dataframe,num_rows,num_cols);
        }else if(choice==6){
            search_dataFrame_for_value( dataframe,num_rows,num_cols);
            usual_operations_menu( dataframe,num_rows,num_cols);
        }else if(choice==7){
            replace_value( dataframe,num_rows,num_cols);
            usual_operations_menu( dataframe,num_rows,num_cols);
        }else if(choice==8){
            display_names(dataframe,num_cols);
            usual_operations_menu( dataframe,num_rows,num_cols);
        }else if(choice==9){
            int i,j;
            printf("In which column is the value: \n");
            scanf(" %d",&i);
            printf("In which row is the value: \n");
            scanf(" %d",&j);
            int val=value_at_position(dataframe[i],j);
            printf("The value at index [%d,%d] is : %d\n",i,j,val);
            usual_operations_menu(dataframe,num_rows,num_cols);
        }else if(choice==10){
            main_menu( dataframe,num_rows,num_cols);
        }
    }
}
void statistics_menu(COLUMN **dataframe,int num_rows,int num_cols){
    int choice=0;
    printf("What functionalities would you like to use : \n"
           "    1)Display the numbers of rows\n"
           "    2)Display the numbers of columns\n"
           "    3)Display the numbers of cells equal to a value\n"
           "    4)Display the numbers of cells greater than a value\n"
           "    5)Display the numbers of cells smaller than a value\n"
           "    6)Display general infos about the dataFrame\n"
           "    7)Return\n");
    scanf("%d",&choice);
    if(choice>7){
        printf("Invalid Input\n");
        statistics_menu(dataframe,num_rows,num_cols);
    }else{
        if(choice==1){
            printf("There is %d rows\n",num_rows);
            statistics_menu(dataframe,num_rows,num_cols);
        }else if(choice==2){
            printf("There is %d columns\n",num_cols);
            statistics_menu(dataframe,num_rows,num_cols);
        }else if(choice==3){
            number_of_cells_equal(dataframe,num_rows,num_cols);
            statistics_menu(dataframe,num_rows,num_cols);
        }else if(choice==4){
            number_of_cells_greater(dataframe,num_rows,num_cols);
            statistics_menu(dataframe,num_rows,num_cols);
        }else if(choice==5){
            number_of_cells_smaller(dataframe,num_rows,num_cols);
            statistics_menu(dataframe,num_rows,num_cols);
        }else if(choice==6){
            general_info(dataframe,num_rows,num_cols);
            statistics_menu(dataframe,num_rows,num_cols);
        }
        else if(choice==7){
            main_menu(dataframe,num_rows,num_cols);
        }
    }

}
void main_menu(COLUMN**dataframe, int num_rows, int num_cols){
    int choice=0;
    printf("What functionalities would you like to use : \n"
           "    1)Filling the matrix\n"
           "    2)Displaying the matrix\n"
           "    3)Perform usual operations\n"
           "    4)Analysis and statistics\n"
           "    5)QUIT\n");
    scanf("%d",&choice);
    if(choice>5){
        printf("invalid input \n");
        main_menu(dataframe,num_rows,num_cols);
    }else{
        if(choice==1){
            menu_filling(dataframe,num_rows,num_cols);
        }else if(choice==2){
            menu_displaying(dataframe,num_rows,num_cols);
        }else if (choice==3){
            usual_operations_menu( dataframe,num_rows,num_cols);
        }else if(choice==4){
            statistics_menu(dataframe,num_rows,num_cols);
        }else if(choice==5){

        }
    }

}