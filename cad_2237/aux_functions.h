#ifndef MYAUXFUNCTIONS
#define MYAUXFUNCTIONS


#include <stdlib.h>
#include <string.h>

typedef struct queues{
	int node;
	struct queues *next;
} queue;

typedef struct list_lists{
	struct list_lists *next;
	struct SOPS *sum;
}list_list;

typedef struct SOPS{
	int *cube;
	struct SOPS *next;
}SOP;

int args_to_table(const char *argv[], int row, int* cube);

void intersect_2(int *first_cube, int *second_cube, int *intersect);

int valid_cube(int *cube);

int distance(int *intersect);

void supercube(int *first_cube, int *second_cube, int *super_cube);

int cube_cover(int *first_cube, int *second_cube);

int cubes_sharp(int *first_cube, int *second_cube, int *result_cubes);

int cubes_equal(int *first_cube, int *second_cube);

int unique(int total_cubes, int *cubes, int *unique_cubes);

int absorption(int unique_num, int *unique_cubes, int *final_cubes);

queue *init_queue();

void add_queue(int node, queue *head);

queue *remove_from_queue(queue *head);

void queue_destroy(queue *head);

int cubes_to_table(const char *argv[], int row, int* cube);

int args_cover(int *first_cube, int *second_cube, int size);

void sub_and_invert(int *first_cube, int *second_cube, int *result, int size);

int args_equal(int *first_cube, int *second_cube , int size);

int kernels(list_list **head, int *func, int func_size, int loop, int cube_size);

int cubes(int *func, int *C, int func_size, int cube_size);

#endif
