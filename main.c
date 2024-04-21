#include <stdio.h>
#include "column.h"

int main() {
    COLUMN *mycol = create_column("My column");
    insert_value(mycol, 23);
    insert_value(mycol, 23);
    insert_value(mycol, 8765);
    print_col(mycol);
    printf("%d", number_of_value_equal(mycol,23));
    return 0;
}
