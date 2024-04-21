#include <stdio.h>
#include "column.h"

int main() {
    int num_col,rows;
    COLUMN *mycol = create_column("My column");
    printf("how many columns \n");
    scanf("%d",&num_col);;
    printf("how many rows \n");
    scanf("%d",&rows);;
    COLUMN **dataFrame=create_dataframe(num_col);
    hard_fill_data_frame(dataFrame,num_col,rows);
    display_data_frame(dataFrame, num_col,rows,num_col,rows);
    return 0;
}