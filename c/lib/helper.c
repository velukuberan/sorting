#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

int* input_data_from_console(int length)
{
    printf("Input data from Console: \n");

    int *data = calloc(length, sizeof(int));
    if (data == NULL) {
        printf("Memory allocation failed.\n");
        return NULL;
    }

    int i;
    printf("Please input integer numbers\n");
    printf("You will need to input %d integers in total\n\n", length);

    for(i = 0; i < length; i++){
        printf("array [%d]: ", i);
        scanf("%d", &data[i]);
    }

    return data;
}

void print_data_to_console(int *data, int length)
{
    printf("Print data to the Console: \n");

    for(int i = 0; i < length; ++i) {
        printf("%d ", data[i]);
        if ((i+1) % 10 == 0){
            printf("\n");
        }
    }

    printf("\n\n");
}

int* fill_random_data(int length)
{
    printf("Fill Random Data: \n");

    int *data = calloc(length, sizeof(int));
    if (data == NULL) {
        printf("Memory allocation failed.\n");
        return NULL;
    }

    srand(time(NULL));

    for (int i = 0; i < length; i++) {
        data[i] = rand() % 10000;
    }

    return data;
}

typedef struct {
    int *values;
    int *used;
    int capacity;
} HashSet;

HashSet* create_hashset(int capacity) {
    HashSet *set = malloc(sizeof(HashSet));
    set->capacity = capacity * 2; // Load factor of 0.5
    set->values = calloc(set->capacity, sizeof(int));
    set->used = calloc(set->capacity, sizeof(int));
    return set;
}

int hash_function(int value, int capacity) {
    return abs(value) % capacity;
}

int hashset_contains(HashSet *set, int value) {
    int index = hash_function(value, set->capacity);
    int original_index = index;
    
    while (set->used[index]) {
        if (set->values[index] == value) {
            return 1; // Found
        }
        index = (index + 1) % set->capacity;
        if (index == original_index) break; // Full loop
    }
    return 0; // Not found
}

void hashset_add(HashSet *set, int value) {
    int index = hash_function(value, set->capacity);
    
    while (set->used[index]) {
        if (set->values[index] == value) return; // Already exists
        index = (index + 1) % set->capacity;
    }
    
    set->values[index] = value;
    set->used[index] = 1;
}

void free_hashset(HashSet *set) {
    free(set->values);
    free(set->used);
    free(set);
}

int* fill_unique_random_data_hashset(int length)
{
    printf("Generating %d unique random integers using hash set...\n", length);
    
    int *data = calloc(length, sizeof(int));
    if (data == NULL) {
        printf("Memory allocation failed.\n");
        return NULL;
    }
    
    HashSet *seen = create_hashset(length);
    int range = length * 10; // 10x larger range
    int start = -(range / 2);
    
    srand(time(NULL));
    
    for (int i = 0; i < length; i++) {
        int candidate;
        
        do {
            candidate = start + (rand() % range);
        } while (hashset_contains(seen, candidate));
        
        hashset_add(seen, candidate);
        data[i] = candidate;
        
        if ((i + 1) % 100000 == 0) {
            printf("Generated %d numbers...\n", i + 1);
        }
    }
    
    free_hashset(seen);
    printf("Generation complete!\n");
    return data;
}

void calculate_memory_usage(int length) {
    printf("\n=== MEMORY USAGE CALCULATION ===\n");
    printf("For array length: %d\n\n", length);
    
    // 1. Main data array
    size_t data_array_bytes = length * sizeof(int);
    printf("1. Main data array: %zu bytes (%.2f MB)\n", 
           data_array_bytes, (double)data_array_bytes / 1024 / 1024);
    
    // 2. HashSet capacity (2x for load factor 0.5)
    int hashset_capacity = length * 2;
    
    // 3. HashSet values array
    size_t values_array_bytes = hashset_capacity * sizeof(int);
    printf("2. HashSet values array: %zu bytes (%.2f MB)\n", 
           values_array_bytes, (double)values_array_bytes / 1024 / 1024);
    
    // 4. HashSet used array
    size_t used_array_bytes = hashset_capacity * sizeof(int);
    printf("3. HashSet used array: %zu bytes (%.2f MB)\n", 
           used_array_bytes, (double)used_array_bytes / 1024 / 1024);
    
    // 5. HashSet struct
    size_t hashset_struct_bytes = sizeof(HashSet);
    printf("4. HashSet struct: %zu bytes\n", hashset_struct_bytes);
    
    // Total
    size_t total_bytes = data_array_bytes + values_array_bytes + used_array_bytes + hashset_struct_bytes;
    double total_mb = (double)total_bytes / 1024 / 1024;
    double total_gb = total_mb / 1024;
    
    printf("\n=== TOTAL MEMORY USAGE ===\n");
    printf("Total: %zu bytes\n", total_bytes);
    printf("Total: %.2f MB\n", total_mb);
    printf("Total: %.3f GB\n", total_gb);
    
    printf("\n=== BREAKDOWN PERCENTAGES ===\n");
    printf("Main array: %.1f%%\n", ((double)data_array_bytes / total_bytes) * 100);
    printf("HashSet values: %.1f%%\n", ((double)values_array_bytes / total_bytes) * 100);
    printf("HashSet used flags: %.1f%%\n", ((double)used_array_bytes / total_bytes) * 100);
    printf("HashSet struct: %.3f%%\n", ((double)hashset_struct_bytes / total_bytes) * 100);
}

float time_diff(struct timeval start, struct timeval end)
{
    return (end.tv_sec - start.tv_sec) * 1000.0f + (end.tv_usec - start.tv_usec) / 1000.0f;
}

