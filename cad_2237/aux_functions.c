#include <stdlib.h>
#include "aux_functions.h"
#include <string.h>
#include <stdio.h>

int args_to_table(const char *argv[], int row, int* cube){

	int number;

	number = atoi(argv[row]);// get the cube from string to integer //
	if(strlen(argv[row]) != 6){
		return 1;
	}

	for (int i = 0; i < 6; i++) {
		*(cube + 5 - i) = number % 10;// setting cube to the table //
		number = number / 10;// i am doing it from the end -> start //
	}
	return 0;

}

void intersect_2(int *first_cube, int *second_cube, int *intersect){

	// calculating intersection by doing bitwise multiplication //
	for (int i = 0; i < 6; i++) {
		*(intersect + i) = (*(first_cube + i)) * (*(second_cube + i));
	}
}

int valid_cube(int *cube){
	// if 1st&2nd or 3rd&4th or 5th and 6th bits are both 0 then cube is invalid //
	for (int i = 0; i < 3; i++) {
		if ((*(cube + (2 * i)) == 0) && (*(cube + (2 * i) + 1) == 0)) {
			return 1;// Cube is not valid //
		}
	}

	return 0;// Cube is valid //

}

int distance(int *intersect){

	int result = 0;
	// calclating the number of 00s and thats the distance //
	for (int i = 0; i < 3; i++) {
		if ((*(intersect + (2 * i)) == 0) && (*(intersect + (2 * i) + 1) == 0)) {
			result = result + 1;
		}
	}

	return result;

}

void supercube(int *first_cube, int *second_cube, int *super_cube) {

	int result;
	// bitwise addition //
	for (int i = 0; i < 6; i++) {
		result = (*(first_cube + i)) + (*(second_cube + i));
		if (result == 2) {// cause we use ints if both cubes are 1 we set value to 1 instead of 2 //
			result = 1;
		}
		*(super_cube + i) = result;
	}
}

int cube_cover(int *first_cube, int *second_cube){
	// checking if first_cube is bigger than second or not //
	for (int i = 0; i < 6; i++) {
		if ((*(first_cube + i)) < (*(second_cube + i))) {
			return 1;
		}
	}

	return 0;
}

int cubes_sharp(int *first_cube, int *second_cube, int *result_cubes){

	int *dummy_cubes = NULL;
	int result = 0;

	dummy_cubes = (int *)malloc(3 * (6 * sizeof(int)));
	// calculating sharp function according to standard format //
	for (int j = 0; j < 3; j++) {
		for (int i = 0; i < 6; i++) {
			if ((i == (2 * j)) || (i == ((2 * j) + 1))) {
				if (*(second_cube + i)) {
					*(dummy_cubes + (6 * j) + i) = 0;
				}
				else{
					*(dummy_cubes + (6 * j) + i) = *(first_cube + i);
				}
			}
			else{
				*(dummy_cubes + (6 * j) + i) = *(first_cube + i);
			}
		}
	}
	// checking and returning only the valid results //
	for (int j = 0; j < 3; j++) {
		if (valid_cube((dummy_cubes + (6 * j))) == 0) {
			for (int i = 0; i < 6; i++) {
				*(result_cubes +(result * 6) + i) = *(dummy_cubes + (6 * j) + i);
			}
			result = result + 1;
		}
	}

	free(dummy_cubes);
	return result;
}

int cubes_equal(int *first_cube, int *second_cube) {
	// if the first qube is bigger than the second return 0, else return 1 //
	for (int i = 0; i < 6; i++) {
		if (*(first_cube + i) != *(second_cube + i)) {
			return 0;
		}
	}

	return 1;

}

int unique(int total_cubes, int *cubes, int *unique_cubes) {

	int unique_num = 0;
	// checking for unique cubes. if a cube is repeated we make him invalid //
	for (int j = 0; j < total_cubes; j++) {
		for (int i = j + 1; i < total_cubes; i++) {
			if(cubes_equal((cubes + 6 * j), (cubes + (6 * i)))){
				*(cubes + (6 * i)) = 0;
				*(cubes + (6 * i) + 1) = 0;
			}
		}
	}
	// here we return only the valid(unique) cubes //
	for (int j = 0; j < total_cubes; j++) {
		if (valid_cube((cubes + (6 * j))) == 0) {
			for (int i = 0; i < 6; i++) {
				*(unique_cubes + (unique_num * 6) + i) = *(cubes + (6 * j) + i);
			}
			unique_num = unique_num + 1;
		}
	}
	return unique_num;
}

int absorption(int unique_num, int *unique_cubes, int *final_cubes){

	int absorbed = 0;
	// we check if a unique cube is bigger than another unique cube and if it is //
	// we make the smaller one invalid //
	for (int j = 0; j < unique_num; j++) {
		for (int i = 0; i < unique_num; i++) {
			if (i != j) {
				if (!cube_cover((unique_cubes + (6 * j)), (unique_cubes + (6 * i)))) {
					*(unique_cubes + (6 * i)) = 0;
					*(unique_cubes + (6 * i) + 1) = 0;
				}
			}
		}
	}
	// we return the valid(prime) cubes //
	for (int j = 0; j < unique_num; j++) {
		if (valid_cube((unique_cubes + (6 * j))) == 0) {
			for (int i = 0; i < 6; i++) {
				*(final_cubes + (absorbed * 6) + i) = *(unique_cubes + (6 * j) + i);
			}
			absorbed = absorbed + 1;
		}
	}

	return absorbed;
}


queue *init_queue(){
	queue *head;
	head = (queue *) malloc(sizeof(queue));
	head->node = -1;
	head->next = NULL;
	return head;
}

void add_queue(int node, queue *head) {
	queue *insert, *previous;

	insert = (queue *) malloc(sizeof(queue));
	insert->node = node;
	insert->next = NULL;

	previous = head;
	while(previous->next != NULL){
		previous = previous->next;
	}
	previous->next = insert;
}

queue *remove_from_queue(queue *head){
	queue *removed;

	if (head->next == NULL) {
		return NULL;
	}
	removed = head->next;
	head->next = removed->next;
	return removed;
}

void queue_destroy(queue *head) {
	free(head);
}


int cubes_to_table(const char *argv[], int row, int* cube){

	int size;
	long long number;

	number = atoll(argv[row]);// get the cube from string to integer //
	size = strlen(argv[row]);

	for (int i = 0; i < size; i++) {
		*(cube + size - 1 - i) = number % 10;// setting cube to the table //
		number = number / 10;// i am doing it from the end -> start //
	}
	return 0;

}

int args_equal(int *first_cube, int *second_cube , int size) {
	// if the first qube is bigger than the second return 0, else return 1 //
	for (int i = 0; i < size; i++) {
		if (*(first_cube + i) != *(second_cube + i)) {
			return 0;
		}
	}

	return 1;

}

int args_cover(int *first_cube, int *second_cube, int size){
	// checking if first_cube is bigger than second or not //
	for (int i = 0; i < size; i++) {
		if ((*(first_cube + i)) < (*(second_cube + i))) {
			return 1;
		}
	}

	return 0;
}
//used for alg_division. if second cube can be divided by first cube then we
//subtract and then we invert the result.
void sub_and_invert(int *first_cube, int *second_cube, int *result, int size) {

	for (int i = 0; i < size; i++) {
		*(result + i) = *(first_cube + i) - *(second_cube + i);
		if (*(result + i) == 1) {
			*(result + i) = 0;
		}
		else {
			*(result + i) = 1;
		}
	}
}

int kernels(list_list **head, int *func, int func_size, int loop, int cube_size){
	int ret_val, func_new_size, flag;
	int *C = NULL;
	int *Cnew = NULL;
	int *result = NULL;
	int *func_new = NULL;
	list_list *new_head, *dummy;
	SOP *newsop, *dummysop;

	C = (int *)malloc(cube_size * sizeof(int));
	Cnew = (int *)malloc(cube_size * sizeof(int));
	result = (int *)malloc(cube_size * sizeof(int));
	func_new = (int *)malloc(cube_size * sizeof(int));
	*head = (list_list *)malloc(sizeof(list_list));
	(*head)->next = NULL;
	(*head)->sum = NULL;
	new_head = NULL;

	for (int i = loop; i < (cube_size/2); i++) {
		//initialising the C iterating every possible cube(a,b,etc) contained
		//in our function
		for (int j = 0; j < (cube_size/2); j++) {
			if (j == i) {
				*(C + 2*j) = 0;
				*(C + 2*j + 1) = 1;
			} else {
				*(C + 2*j) = 1;
				*(C + 2*j + 1) = 1;
			}
		}

		ret_val = cubes(func, C, func_size, cube_size);
		if (ret_val > 1) {
			//calculating fnew=f/c;
			func_new_size = 0;
			for (int j = 0; j < func_size; j++) {
				// checking if the func can be divided by the divider and if it can we calculate the Q
				if (args_cover(C, (func + (j * cube_size)), cube_size) == 0) {
					sub_and_invert(C, (func + (j * cube_size)), result, cube_size);
					func_new_size = func_new_size + 1;
					func_new = (int *)realloc(func_new, func_new_size * cube_size * sizeof(int));
					for (int l = 0; l < cube_size; l++) {
						*(func_new + ((func_new_size - 1) * cube_size) + l) = *(result + l);
					}
				}
			}
			//calculating the next c such as retval_new = retval
			flag = 0;
			for (int j = i + 1; j < (cube_size/2); j++) {
				for (int k = 0; k < (cube_size/2); k++) {
					if (k == j) {
						*(Cnew + 2*k) = 0;
						*(Cnew + 2*k + 1) = 1;
					} else {
						*(Cnew + 2*k) = 1;
						*(Cnew + 2*k + 1) = 1;
					}
				}
				if (cubes(func_new, Cnew, func_new_size, cube_size) == ret_val) {
					*(C + 2*j) = 0;
					flag = 1;
				}
			}
			//calculating fnew=f/Cnew;
			if (flag == 1) {
				func_new_size = 0;
				for (int j = 0; j < func_size; j++) {
					// checking if the func can be divided by the divider and if it can we calculate the Q
					if (args_cover(C, (func + (j * cube_size)), cube_size) == 0) {
						sub_and_invert(C, (func + (j * cube_size)), result, cube_size);
						func_new_size = func_new_size + 1;
						func_new = (int *)realloc(func_new, func_new_size * cube_size * sizeof(int));
						for (int l = 0; l < cube_size; l++) {
							*(func_new + ((func_new_size - 1) * cube_size) + l) = *(result + l);
						}
					}
				}
			}
			//recursion kernels(f/c)
			kernels(&new_head, func_new, func_new_size, i + 1, cube_size);

			//K = K + Knew
			dummy = *head;
			while (dummy->next != NULL) {
				dummy = dummy->next;
			}
			dummy->next = new_head;
		}
	}
	//K = K + f
	for (int i = 0; i < func_size; i++) {
		dummysop = (*head)->sum;
		newsop = (SOP *)malloc(sizeof(SOP));
		newsop->cube = (int *)malloc(cube_size * sizeof(int));
		for (int j = 0; j < cube_size; j++) {
			*(newsop->cube + j) = *(func + (i * cube_size) + j);
		}
		if (dummysop == NULL) {
			(*head)->sum = newsop;
		}
		else{
			while (dummysop->next != NULL) {
				dummysop = dummysop->next;
			}
			dummysop->next = newsop;
		}
	}
	free(C);
	free(Cnew);
	free(result);
	free(func_new);
	return(0);
}

int cubes(int *func, int *C, int func_size, int cube_size){
	int ret_val = 0;

	for (int i = 0; i < func_size; i++) {
		if (args_cover(C, (func + (i * cube_size)), cube_size) == 0) {
			ret_val = ret_val + 1;
		}
	}
	return ret_val;
}
