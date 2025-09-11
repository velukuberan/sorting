void calculate_memory_usage(int length);
int* input_data_from_console(int);
void print_data_to_console(int*, int);
int* fill_random_data(int);
float time_diff(struct timeval, struct timeval);

typedef struct {
    int *values;
    int *used;
    int capacity;
} HashSet;

HashSet* create_hashset(int);
int hash_function(int, int);
int hashset_contains(HashSet *, int);
void hashset_add(HashSet *, int);
void free_hashset(HashSet *);
int* fill_unique_random_data_hashset(int);
