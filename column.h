#define REALOC_SIZE 256

// STRUCTURES

typedef struct{
    char name[30];
    int log_size, phys_size;
    int* data;
}COLUMN;

// FUNCTIONS
COLUMN *create_column(char *title);
