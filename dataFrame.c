#include "dataFrame.h"
#define REALOC_SIZE 256
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


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

void rename_column(COLUMN** dataframe){
    int column_to_rename;
    char title;
    printf("Which column would you like to rename ? \n");
    scanf("%d",&column_to_rename);
    printf("What would you like to rename it ? \n");
    scanf("%s",title);
    dataframe[column_to_rename]->name=&title;
}

void search_dataFrame_for_value(COLUMN** dataframe, int num_columns, int rows){
    int value;
    printf("Enter the value to search for : \n");
    scanf("%d",&value);
    int found=0;
    for (int i=0;i<rows;i++){
        for(int j=0;j<num_columns;j++){
            if(dataframe[j]->data[i]==value){
                printf("The value was found in column %d and row %d\n",j,i);
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
    printf("Enter the value to replace : \n");
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

void display_names(COLUMN** dataframe, int num_columns, int rows){
    for(int j=0;j<num_columns;j++){
        printf("%s",dataframe[j]->name);
    }
}

void number_of_cells_equal(COLUMN** dataframe, int num_columns, int rows){
    int value;
    int count =0;
    int *ptrcount=&count;
    printf("Enter the value to look for: \n");
    scanf("%d",&value);
    for (int i=0;i<rows;i++){
        for(int j=0;j<num_columns;j++){
            if(dataframe[j]->data[i]==value){
                (*ptrcount)++;
            }
        }
    }
    printf("There is %d cells equal to %d \n",*ptrcount,value);
}

void number_of_cells_smaller(COLUMN** dataframe, int num_columns, int rows){
    int value;
    int count =0;
    int *ptrcount=&count;
    printf("Enter the value to look for: \n");
    scanf("%d",&value);
    for (int i=0;i<rows;i++){
        for(int j=0;j<num_columns;j++){
            if(dataframe[j]->data[i]<value){
                (*ptrcount)++;
            }
        }
    }
    printf("There is %d cells smaller than %d \n",*ptrcount,value);
}

void number_of_cells_greater(COLUMN** dataframe, int num_columns, int rows){
    int value;
    int count =0;
    int *ptrcount=&count;
    printf("Enter the value to look for: \n");
    scanf("%d",&value);
    for (int i=0;i<rows;i++){
        for(int j=0;j<num_columns;j++){
            if(dataframe[j]->data[i]>value){
                (*ptrcount)++;
            }
        }
    }
    printf("There is %d cells greater than %d \n",*ptrcount,value);
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

        }
    }

}