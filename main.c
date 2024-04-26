#include <stdio.h>
#include "dataFrame.h"

int main() {
    int num_col,rows;
    printf("how many columns \n");
    scanf("%d",&num_col);;
    printf("how many rows \n");
    scanf("%d",&rows);;
    COLUMN **dataFrame=create_dataframe(num_col);
    main_menu(dataFrame,rows,num_col);
    return 0;
}