#include <stdio.h>
#include "dataFrame.h"

int main() {
    int num_col,rows;
    printf("How many columns do you want to have: \n");
    scanf("%d",&num_col);;
    printf("How many rows do you want to have: \n");
    scanf("%d",&rows);;
    COLUMN **dataFrame=create_dataframe(num_col);
    menu_filling(dataFrame,rows,num_col);
    main_menu(dataFrame,rows,num_col);
    return 0;
}