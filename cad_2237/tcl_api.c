#include <stdlib.h>
#include <tcl/tcl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "tcl_api.h"
#include "aux_functions.h"

int *graph_table = NULL;
int size;


//void free_table() {
// 	if (graph_table != NULL) {
// 		free(graph_table);
// 	}
// 	return;
// }

static int myls(ClientData clientData,Tcl_Interp *interp,int argc,const char *argv[]){

	int status;


	if ( fork() == 0 ){
        execv( "/bin/ls", (char * const*)argv ); // child: call execv with the path and the args //
	}
    else {
        wait( &status );        // parent: wait for the child (not really necessary) //
	}

	return 0;
}
/* same thing with ls */
static int myless(ClientData clientData,Tcl_Interp *interp,int argc,const char *argv[]){

	int status;

	if ( fork() == 0 ){
        execv( "/bin/less", (char * const*)argv ); // child: call execv with the path and the args //
	}
    else {
        wait( &status ); // parent: wait for the child (not really necessary) //
	}

	return 0;
}

int Tcl_AppInit(Tcl_Interp *interp){		/* Interpreter for application. */

	// sourcing the init.tcl script?? //

	// initialising the interpreter //

	Tcl_CreateCommand(interp, "ls", myls, NULL, NULL);

	Tcl_CreateCommand(interp, "less", myless, NULL, NULL);

	Tcl_CreateCommand(interp, "cube_intersect_2", cube_intersect_2, NULL, NULL);

	Tcl_CreateCommand(interp, "supercube_2", supercube_2, NULL, NULL);

	Tcl_CreateCommand(interp, "distance_2", distance_2, NULL, NULL);

	Tcl_CreateCommand(interp, "cube_cover_2", cube_cover_2, NULL, NULL);

	Tcl_CreateCommand(interp, "sharp_2", sharp_2, NULL, NULL);

	Tcl_CreateCommand(interp, "sharp", sharp, NULL, NULL);

	Tcl_CreateCommand(interp, "off_f", off_f, NULL, NULL);

	Tcl_CreateCommand(interp, "read_graph", read_graph, NULL, NULL);

	Tcl_CreateCommand(interp, "write_graph", write_graph, NULL, NULL);

	Tcl_CreateCommand(interp, "draw_graph", draw_graph, NULL, NULL);

	Tcl_CreateCommand(interp, "graph_critical_path", graph_critical_path, NULL, NULL);

	Tcl_CreateCommand(interp, "alg_division", alg_division, NULL, NULL);

	Tcl_CreateCommand(interp, "r_kernels", r_kernels, NULL, NULL);

	/*if i use tcl_init it sources a tcl script that contains an already completed
	version of ls but it doesnt solve at all the problem with less.*/
	// if (Tcl_Init(interp) != TCL_OK) {
	// 	return EXIT_FAILURE;
	// }
	/*extentions dont work yet(ls  returns with error
	while less doesnt even begin to work T_T)!!*/
	//NOTE: the statement inside the if had a problem with the comparison and
	//thats why it failed all the time...


    /*
     * Call Tcl_CreateCommand for application-specific commands, if they
     * weren't already created by the init procedures called above.
     */

    return TCL_OK;
}

static int cube_intersect_2(ClientData clientData,Tcl_Interp *interp,int argc,const char *argv[]){

	int *first_cube = NULL;
	int *second_cube = NULL;
	int *intersect = NULL;



	if (argc!=3) {
		printf("WRONG NUMBER OF ARGUMENTS\n");
		return 0;
	}

	first_cube = (int *)malloc(6 * sizeof(int));
	second_cube = (int *)malloc(6 * sizeof(int));
	intersect = (int *)malloc(6 * sizeof(int));
	// initialising the arguments //
	if(args_to_table(argv, 1, first_cube)){
		printf("WRONG ARGUMENT TYPE\n");
		free(first_cube);
		free(second_cube);
		free(intersect);

		return 0;
	}
	if(args_to_table(argv, 2, second_cube)){
		printf("WRONG ARGUMENT TYPE\n");
		free(first_cube);
		free(second_cube);
		free(intersect);

		return 0;
	}

	intersect_2(first_cube, second_cube, intersect);

	// checking if the intersection is valid //
	if (valid_cube(intersect)) {
		printf("Cubes have no valid intersect\n");
	}
	else{
		printf("The intersect of the cubes is: ");
		for (int i = 0; i < 6; i++) {
			printf("%d", *(intersect + i));
		}
		printf("\n");
	}

	free(first_cube);
	free(second_cube);
	free(intersect);

	return 0;
}

static int supercube_2(ClientData clientData,Tcl_Interp *interp,int argc,const char *argv[]){

	int *first_cube = NULL;
	int *second_cube = NULL;
	int *super_cube = NULL;



	if (argc!=3) {
		printf("WRONG NUMBER OF ARGUMENTS\n");
		return 0;
	}

	first_cube = (int *)malloc(6 * sizeof(int));
	second_cube = (int *)malloc(6 * sizeof(int));
	super_cube = (int *)malloc(6 * sizeof(int));
	// initialising the arguments //

	if(args_to_table(argv, 1, first_cube)){
		printf("WRONG ARGUMENT TYPE\n");
		free(first_cube);
		free(second_cube);
		free(super_cube);

		return 0;
	}
	if(args_to_table(argv, 2, second_cube)){
		printf("WRONG ARGUMENT TYPE\n");
		free(first_cube);
		free(second_cube);
		free(super_cube);

		return 0;
	}

	supercube(first_cube, second_cube, super_cube);
	printf("The supercube_2 results is:\n");
	for (int i = 0; i < 6; i++) {
		printf("%d", *(super_cube + i));
	}
	printf("\n");

	free(first_cube);
	free(second_cube);
	free(super_cube);

	return 0;
}

static int distance_2(ClientData clientData,Tcl_Interp *interp,int argc,const char *argv[]){

	int *first_cube = NULL;
	int *second_cube = NULL;
	int *intersect = NULL;
	int result;



	if (argc!=3) {
		printf("WRONG NUMBER OF ARGUMENTS\n");
		return 0;
	}

	first_cube = (int *)malloc(6 * sizeof(int));
	second_cube = (int *)malloc(6 * sizeof(int));
	intersect = (int *)malloc(6 * sizeof(int));
	// initialising the arguments //

	if(args_to_table(argv, 1, first_cube)){
		printf("WRONG ARGUMENT TYPE\n");
		free(first_cube);
		free(second_cube);
		free(intersect);

		return 0;
	}
	if(args_to_table(argv, 2, second_cube)){
		printf("WRONG ARGUMENT TYPE\n");
		free(first_cube);
		free(second_cube);
		free(intersect);

		return 0;
	}

	intersect_2(first_cube, second_cube, intersect);
	result = distance(intersect);
	printf("Cubes have %d distance\n", result);

	free(first_cube);
	free(second_cube);
	free(intersect);

	return 0;
}

static int cube_cover_2(ClientData clientData,Tcl_Interp *interp,int argc,const char *argv[]){

	int *first_cube = NULL;
	int *second_cube = NULL;



	if (argc!=3) {
		printf("WRONG NUMBER OF ARGUMENTS\n");
		return 0;
	}

	first_cube = (int *)malloc(6 * sizeof(int));
	second_cube = (int *)malloc(6 * sizeof(int));
	// initialising the arguments //

	if(args_to_table(argv, 1, first_cube)){
		printf("WRONG ARGUMENT TYPE\n");
		free(first_cube);
		free(second_cube);

		return 0;
	}
	if(args_to_table(argv, 2, second_cube)){
		printf("WRONG ARGUMENT TYPE\n");
		free(first_cube);
		free(second_cube);

		return 0;
	}

	if(cube_cover(first_cube, second_cube)){
		printf("first_cube is not biger than the second_cube\n");
	}
	else{
		printf("first_cube > second_cube\n");

	}



	free(first_cube);
	free(second_cube);

	return 0;
}

static int sharp_2(ClientData clientData,Tcl_Interp *interp,int argc,const char *argv[]){

	int *first_cube = NULL;
	int *second_cube = NULL;
	int *result_cubes = NULL;
	int valid_num;



	if (argc!=3) {
		printf("WRONG NUMBER OF ARGUMENTS\n");
		return 0;
	}

	first_cube = (int *)malloc(6 * sizeof(int));
	second_cube = (int *)malloc(6 * sizeof(int));
	result_cubes = (int *)malloc(3 * (6 * sizeof(int)));

	// initialising the arguments //

	if(args_to_table(argv, 1, first_cube)){
		printf("WRONG ARGUMENT TYPE\n");
		free(first_cube);
		free(second_cube);
		free(result_cubes);

		return 0;
	}
	if(args_to_table(argv, 2, second_cube)){
		printf("WRONG ARGUMENT TYPE\n");
		free(first_cube);
		free(second_cube);
		free(result_cubes);

		return 0;
	}

	valid_num = cubes_sharp(first_cube, second_cube, result_cubes);
	printf("The result of our sharp_2 is:\n");
	for (int j = 0; j < valid_num; j++) {
		for (int i = 0; i < 6; i++) {
			printf("%d", *(result_cubes + (6 * j) + i));
		}
		printf("\n");
	}


	free(first_cube);
	free(second_cube);
	free(result_cubes);

	return 0;
}

static int sharp(ClientData clientData,Tcl_Interp *interp,int argc,const char *argv[]){

	int func_size, valid_num, total_valid, unique_num, absorbed;
	int *first_cube = NULL;
	int *second_cube = NULL;
	int *result_cubes = NULL;
	int *unique_cubes = NULL;
	int *intersected = NULL;
	int *total_cubes = NULL;
	int *final_cubes = NULL;


	if (argc<3) {
		printf("WRONG NUMBER OF ARGUMENTS\n");
		return 0;
	}

	func_size = argc - 2;

	first_cube = (int *)malloc(6 * sizeof(int));
	second_cube = (int *)malloc(6 * sizeof(int));
	result_cubes = (int *)malloc(3 * 6 * sizeof(int));
	intersected = (int *)malloc(6 * sizeof(int));
	total_cubes = (int *)malloc(6 * sizeof(int));

	// initialising the arguments //

	if(args_to_table(argv, 1, first_cube)){
		printf("WRONG ARGUMENT TYPE\n");
		free(first_cube);
		free(second_cube);
		free(result_cubes);
		free(intersected);
		free(total_cubes);
		return 0;
	}
	// args_to_table(argv, 2, second_cube);

	total_valid = 0;

	for (int i = 0; i < func_size; i++) {
		//calclating sharp_2 functions //
		if(args_to_table(argv, (2 + i), second_cube)){
			printf("WRONG ARGUMENT TYPE\n");
			free(first_cube);
			free(second_cube);
			free(result_cubes);
			free(intersected);
			free(total_cubes);
			return 0;
		}
		valid_num = cubes_sharp(first_cube, second_cube, result_cubes);
		if (valid_num != 0) {
			if (!total_valid) {// for the first iteration //
				// just copy the sharp results to the total_cubes //
				total_cubes = (int *)realloc(total_cubes, valid_num * (6 * sizeof(int)));
				for (int k = 0; k < valid_num; k++) {
					for (int l = 0; l < 6; l++) {
						*(total_cubes + (6 * k) + l) = *(result_cubes + (6 * k) + l);
					}
				}
				total_valid = total_valid + valid_num;
			}
			else {// every other iteration //
				//calculating intersections //
				intersected = (int *)realloc(intersected, valid_num * total_valid * (6 * sizeof(int)));
				for (int k = 0; k < total_valid; k++) {
					for (int l = 0; l < valid_num; l++) {
						intersect_2((total_cubes + (k * 6)), (result_cubes + (l * 6)), (intersected + (((k * valid_num) + l) * 6)));
					}
				}
				//copy the results to the total_cubes //
				total_cubes = (int *)realloc(total_cubes, valid_num * total_valid * (6 * sizeof(int)));
				for (int k = 0; k < valid_num * total_valid; k++) {
					for (int l = 0; l < 6; l++) {
						*(total_cubes + (6 * k) + l) = *(intersected + (6 * k) + l);
					}
				}
				total_valid = total_valid * valid_num;
			}
		}
		else{
			break;
		}

	}
	if (valid_num == 0) {
		printf("There is no sharp function result\n");
	}
	else{

		unique_cubes = (int *)malloc(total_valid * 6 * sizeof(int));
		// returning the unique cubes and their number //
		unique_num = unique(total_valid, total_cubes, unique_cubes);


		final_cubes = (int *)malloc(unique_num * 6 * sizeof(int));
		// returning the essential cubes and their number //
		absorbed = absorption(unique_num, unique_cubes, final_cubes);

		printf("The result of our sharp function is:\n");
		for (int j = 0; j < absorbed; j++) {
			for (int i = 0; i < 6; i++) {
				printf("%d", *(final_cubes + (6 * j) + i));
			}
			printf("\n");
		}
	}

	free(first_cube);
	free(second_cube);
	free(result_cubes);
	free(intersected);
	free(total_cubes);
	free(unique_cubes);
	free(final_cubes);

	return 0;
}


static int off_f(ClientData clientData,Tcl_Interp *interp,int argc,const char *argv[]){

	int func_size, valid_num, total_valid, unique_num, absorbed;
	int *first_cube = NULL;
	int *second_cube = NULL;
	int *result_cubes = NULL;
	int *unique_cubes = NULL;
	int *total_cubes = NULL;
	int *intersected = NULL;
	int *final_cubes = NULL;

	if (argc<2) {
		printf("WRONG NUMBER OF ARGUMENTS\n");
		return 0;
	}

	func_size = argc - 1;

	first_cube = (int *)malloc(6 * sizeof(int));
	for (int i = 0; i < 6; i++) {
		*(first_cube + i) = 1;
	}
	second_cube = (int *)malloc(6 * sizeof(int));
	result_cubes = (int *)malloc(3 * 6 * sizeof(int));
	intersected = (int *)malloc(6 * sizeof(int));
	total_cubes = (int *)malloc(6 * sizeof(int));


	// args_to_table(argv, 1, second_cube);

	total_valid = 0;

	for (int i = 0; i < func_size; i++) {
		if(args_to_table(argv, (1 + i), second_cube)){
			printf("WRONG ARGUMENT TYPE\n");
			free(first_cube);
			free(second_cube);
			free(result_cubes);
			free(intersected);
			free(total_cubes);
			return 0;
		}
		valid_num = cubes_sharp(first_cube, second_cube, result_cubes);
		if (valid_num != 0) {
			if (!total_valid) {
				total_cubes = (int *)realloc(total_cubes, valid_num * (6 * sizeof(int)));
				for (int k = 0; k < valid_num; k++) {
					for (int l = 0; l < 6; l++) {
						*(total_cubes + (6 * k) + l) = *(result_cubes + (6 * k) + l);
					}
				}
				total_valid = total_valid + valid_num;
			}
			else {
				intersected = (int *)realloc(intersected, valid_num * total_valid * (6 * sizeof(int)));
				for (int k = 0; k < total_valid; k++) {
					for (int l = 0; l < valid_num; l++) {
						intersect_2((total_cubes + (k * 6)), (result_cubes + (l * 6)), (intersected + (((k * valid_num) + l) * 6)));
					}
				}
				total_cubes = (int *)realloc(total_cubes, valid_num * total_valid * (6 * sizeof(int)));
				for (int k = 0; k < valid_num * total_valid; k++) {
					for (int l = 0; l < 6; l++) {
						*(total_cubes + (6 * k) + l) = *(intersected + (6 * k) + l);
					}
				}
				total_valid = total_valid * valid_num;
			}
		}
		else{
			break;
		}

	}
	if (valid_num == 0) {
		printf("There is no offset\n");
	}
	else{

		unique_cubes = (int *)malloc(total_valid * 6 * sizeof(int));

		unique_num = unique(total_valid, total_cubes, unique_cubes);


		final_cubes = (int *)malloc(unique_num * 6 * sizeof(int));

		absorbed = absorption(unique_num, unique_cubes, final_cubes);

		printf("The result of our sharp function is:\n");
		for (int j = 0; j < absorbed; j++) {
			for (int i = 0; i < 6; i++) {
				printf("%d", *(final_cubes + (6 * j) + i));
			}
			printf("\n");
		}
	}

	free(first_cube);
	free(second_cube);
	free(result_cubes);
	free(intersected);
	free(total_cubes);
	free(unique_cubes);
	free(final_cubes);

	return 0;
}

//###########################################################################//

static int read_graph(ClientData clientData,Tcl_Interp *interp,int argc,const char *argv[]){

	int v, e, w, *table, count;
	FILE *fp;
	int max, row , column;
	// opening the file, reading and saving all the information on a temporary table //
	// which we allocate with malloc/realloc and we use to initialise our final table //

	if (argc!=2) {
		printf("WRONG NUMBER OF ARGUMENTS\n");
		return 0;
	}

	fp = fopen (argv[1],"r");
	if (fp==NULL){
		printf("ERROR IN FOPEN\n");
	}

	count = 0;
	table = (int *) malloc(3*sizeof(int));
	while (fscanf(fp, " n %d -> n %d %d\n", &v, &e, &w) != EOF) {
		count = count + 1;
		table = (int *) realloc(table, count*3*sizeof(int));
		*(table + ((count - 1)*3)) = v;
		*(table + ((count - 1)*3) + 1) = e;
		*(table + ((count - 1)*3) + 2) = w;
	}

	// calculating the biggest node to know how much memory to allocate for oun nxn table //
	max = -1;
	for (int i = 0; i < count; i++) {
		if (*(table + ((count - 1)*3)) > max) {
			max = *(table + ((count - 1)*3));
		}
		if (*(table + ((count - 1)*3) + 1) > max) {
			max = *(table + ((count - 1)*3) + 1);
		}
	}
	size = max + 1;

	// because we use a global variable for the table so other functions may have //
	// access to it we check if the table is already allocated and if it is we //
	// free the old allocation in order to make a new one //

	if (graph_table != NULL) {
		free(graph_table);
	}

	graph_table = (int *) malloc(size * size * sizeof(int));
	// initialising the table with 0s//
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			*(graph_table + (i * size) + j) = 0;
		}
	}
	// we check the acmes and we put the weights from our helpful table to the global one //
	for (int i = 0; i < count; i++) {
		row = *(table+ ((i * 3)));
		column = *(table+ ((i * 3)) + 1);
		*(graph_table + (row * size) + column) = *(table+ ((i * 3)) + 2);
	}

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			printf("%d ", *(graph_table + (i * size) + j));
		}
		printf("\n");
	}
	fclose(fp);
	free(table);
	return 0;
}

static int write_graph(ClientData clientData,Tcl_Interp *interp,int argc,const char *argv[]){
	FILE *fp;

	if (argc!=2) {
		printf("WRONG NUMBER OF ARGUMENTS\n");
		return 0;
	}

	fp = fopen (argv[1],"w");
	if (fp == NULL){
		perror("ERROR:");
	}

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (*(graph_table + (i * size) + j) > 0) {
				fprintf(fp, "n%d -> n%d %d\n", (int) i, (int) j, *(graph_table + (i * size) + j));
			}
		}
	}
	fclose(fp);

	return 0;
}

static int draw_graph(ClientData clientData,Tcl_Interp *interp,int argc,const char *argv[]){

	FILE *fp;
	char cmd[LINE_MAX];

	if (argc!=2) {
		printf("WRONG NUMBER OF ARGUMENTS\n");
		return 0;
	}
	//empting the string //
	memset(cmd,0,sizeof(cmd));

	fp = fopen (argv[1],"w");
	if (fp == NULL){
		perror("ERROR:");
	}
	fprintf(fp, "digraph {\n\tnode[shape = box,\n\tfillcolor=\"blue\",\n\t");
	fprintf(fp, "style=\"filled\",\n\tfontsize=10,\n\tfontcolor=\"yellow\"]\n");

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (*(graph_table + (i * size) + j) > 0) {
				fprintf(fp, "\tn%d -> n%d[label = \"%d\"];\n", (int) i, (int) j, *(graph_table + (i * size) + j));
			}
		}
	}
	fprintf(fp, "}");
	fclose(fp);
	strcat(cmd, "dotty ");
	strcat(cmd, argv[1]);
	strcat(cmd, "\n");
	system(cmd);

	return 0;
}

static int graph_critical_path(ClientData clientData,Tcl_Interp *interp,int argc,const char *argv[]){

	int counter, weight, max, maxnode, slack;
	int weight_table[size][2];
	int slack_table[size];
	queue *head, *next;
	int *table, *print_table, printsize;

	head = init_queue();
	for (int i = 0; i < size; i++) {
		weight_table[i][0] = -1;
		weight_table[i][1] = 0;
	}
	table = (int *) malloc(size * size * sizeof(int));

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			*(table + (i * size) + j) = *(graph_table + (i * size) + j);
		}
	}

	// scaning for source nodes and putting them on the queue
	for (int i = 0; i < size; i++) {
		counter = 0;
		for (int j = 0; j < size; j++) {
			if (*(table + (j * size) + i) > 0) {
				counter = counter + 1;
			}
		}
		if (counter == 0) {
			add_queue(i, head);
		}
	}
	// step by step remove the 1st, after the head node, and then calculating the
	// critical paths for each node. we find the nodus by scaning the rows for
	// a number > 0. after we finish we check if we can put the next
	// node in the queue and then we go to the next one.
	next = remove_from_queue(head);
	while (next != NULL) {
		for (int i = 0; i < size; i++) {
			if (*(table + (next->node * size) + i) > 0) {
				//calculating weight
				weight = *(table + (next->node * size) + i) + weight_table[next->node][1];
				if (weight > weight_table[i][1]) {
					weight_table[i][1] = weight;
					weight_table[i][0] = next->node;
				}
				//mark the acme so we know we have explore it
				*(table + (next->node * size) + i) = 0;
				counter = 0;
				// if this node has no more incoming acmes then put it in the queue //
				for (int j = 0; j < size; j++) {
					if (*(table + (j * size) + i) > 0) {
						counter = counter + 1;
					}
				}
				if (counter == 0) {
					add_queue(i, head);
				}
			}
		}

		free(next);
		next = remove_from_queue(head);
	}


	max = -1;
	maxnode = -1;
	// finding the node with the max weight.
	for (int i = 0; i < size; i++) {
		printf("node %d\tweigth %d\tprevious node ", (int) i, weight_table[i][1]);
		if (weight_table[i][0] == -1) {
			printf("NONE\n");
		}
		else{
			printf("%d\n", weight_table[i][0]);
		}
		if (weight_table[i][1] > max){
			max = weight_table[i][1];
			maxnode = i;
		}
	}

	print_table = (int *)malloc(sizeof(int));
	printsize = 0;
	//finding the critical path
	while (maxnode != -1) {
		printsize = printsize + 1;
		print_table = (int *)realloc(print_table, printsize * sizeof(int));
		*(print_table + (printsize - 1)) = maxnode;
		maxnode = weight_table[maxnode][0];
	}
	//printing critical path
	printf("critical path is : ");
	printf("%d", *(print_table + (printsize - 1)));
	for (int i = 1; i < printsize; i++) {
		printf("-> %d", *(print_table + (printsize - i - 1)));
	}
	printf("\n");
	free(print_table);

	// initialising the table again //
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			*(table + (i * size) + j) = *(graph_table + (i * size) + j);
		}
	}
	// find the leaf nodes and initialise their slack value//
	for (int i = 0; i < size; i++) {
		counter = 0;
		for (int j = 0; j < size; j++) {
			if (*(table + (i * size) + j) > 0) {
				counter = counter + 1;
			}
		}
		if (counter == 0) {
			add_queue(i, head);
			slack_table[i] = max - weight_table[i][1];
		}
		else{
			slack_table[i] = max;
		}
	}


	next = remove_from_queue(head);
	while (next != NULL) {
		for (int i = 0; i < size; i++) {
			if (*(table + (i * size) + next->node) > 0) {
				// calculating the slack of this node //
				slack = slack_table[next->node] + weight_table[next->node][1] - weight_table[i][1] - *(table + (i * size) + next->node);
				if (slack < slack_table[i]) {
					slack_table[i] = slack;
				}
				*(table + (i * size) + next->node) = 0;
				counter = 0;
				// checking if we can add this node to the queue //
				for (int j = 0; j < size; j++) {
					if (*(table + (i * size) + j) > 0) {
						counter = counter + 1;
					}
				}
				if (counter == 0) {
					add_queue(i, head);
				}
			}
		}

		free(next);
		next = remove_from_queue(head);
	}

	for (int i = 0; i < size; i++) {
		printf("Slack for node %d\tis %d\n", (int) i, slack_table[i]);
	}


	free(table);


	queue_destroy(head);

	return 0;
}


//alg_division
static int alg_division(ClientData clientData,Tcl_Interp *interp,int argc,const char *argv[]){

	int func_size, div_size, cube_size, q1size, qsize, qnewsize, flag;
	int *func, *divider, *result, *Q1, *Q, *Qnew;

	if (argc < 7) {
		printf("WRONG NUMBER OF ARGUMENTS\n");
		return 0;
	}
	//calculating how many cubes our functions have
	for (int i = 0; i < argc; i++) {
		if (strcmp(argv[i], ")") == 0) {
			func_size = i - 2;
			div_size = argc - i - 3;
			break;
		}
	}
	cube_size = strlen(argv[2]);
	func = (int *)malloc(cube_size * func_size * sizeof(int));
	divider = (int *)malloc(cube_size * div_size * sizeof(int));
	result = (int *)malloc(cube_size * sizeof(int));
	Q1 = (int *)malloc(cube_size * sizeof(int));
	Qnew = (int *)malloc(cube_size * sizeof(int));
	q1size = 0;
	Q = NULL;
	//generating the cube tables
	for (int i = 0; i < func_size; i++) {
		cubes_to_table(argv, (2 + i), (func + i * cube_size));
	}
	for (int i = 0; i < div_size; i++) {
		cubes_to_table(argv, (2 + func_size + 2 + i), (divider + i * cube_size));
	}

	for (int i = 0; i < div_size; i++) {
		for (int j = 0; j < func_size; j++) {
			// checking if the cube can be divided by the divider and if it can we calculate the Q
			if (args_cover((divider + (i * cube_size)), (func + (j * cube_size)), cube_size) == 0) {
				sub_and_invert((divider + (i * cube_size)), (func + (j * cube_size)), result, cube_size);
				q1size = q1size + 1;
				Q1 = (int *)realloc(Q1, q1size * cube_size * sizeof(int));
				for (int k = 0; k < cube_size; k++) {
					*(Q1 + ((q1size - 1) * cube_size) + k) = *(result + k);
				}
			}
		}
		//if this is not our first divide we check for mutual cubes and we keep only those.
		if (Q != NULL) {
			qnewsize = 0;
			Qnew = (int *)realloc(Qnew, cube_size * sizeof(int));
			for (int j = 0; j < qsize; j++) {
				for (int k = 0; k < q1size; k++) {
					if (args_equal((Q + (j * cube_size)), (Q1 + (k * cube_size)), cube_size)) {
						qnewsize = qnewsize + 1;
						Qnew = (int *)realloc(Qnew, qnewsize * cube_size * sizeof(int));
						for (int l = 0; l < cube_size; l++) {
							*(Qnew + ((qnewsize - 1) * cube_size) + l) = *(Q1 + (k * cube_size) + l);
						}
					}
				}
			}
			//coppying the qnew to q
			Q = (int *)realloc(Q, qnewsize * cube_size * sizeof(int));
			for (int j = 0; j < qnewsize; j++) {
				for (int k = 0; k < cube_size; k++) {
					*(Q + (j * cube_size) + k) = *(Qnew + (j * cube_size) + k);
					qsize = qnewsize;
				}
			}
		}
		else {//else we coppy what we found to the Q
			Q = (int *)malloc(q1size * cube_size * sizeof(int));
			for (int j = 0; j < q1size; j++) {
				for (int k = 0; k < cube_size; k++) {
					*(Q + (j * cube_size) + k) = *(Q1 + (j * cube_size) + k);
					qsize = q1size;
				}
			}
		}
		q1size = 0;
		Q1 = (int *)realloc(Q1, q1size);
	}
	printf("F = (");
	for (int i = 0; i < div_size; i++) {
		if (i > 0) {
			printf(" + ");
		}
		for (int j = 0; j < cube_size; j++) {
			printf("%d", *(divider + (i * cube_size) + j));
		}
	}
	printf(")(");
	for (int i = 0; i < qsize; i++) {
		if (i > 0) {
			printf(" + ");
		}
		for (int j = 0; j < cube_size; j++) {
			printf("%d", *(Q + (i * cube_size) + j));
		}
	}
	printf(")");
	result = (int *)realloc(result, qsize * div_size * cube_size * sizeof(int));
	for (int i = 0; i < qsize; i++) {
		for (int j = 0; j < div_size; j++) {
			for (int k = 0; k < cube_size; k++) {
				*(result + (((i * div_size) + j) * cube_size) + k) = (*(Q + (i * cube_size) + k)) * (*(divider + (j * cube_size) + k));
			}
		}
	}

	for (int i = 0; i < func_size; i++) {
		for (int j = 0; j < (qsize * div_size); j++) {
			if (args_equal((func + (i * cube_size)), (result + (j * cube_size)), cube_size)) {
				flag = 1;
				break;
			}
		}
		if (flag == 0) {
			printf(" + ");
			for (int j = 0; j < cube_size; j++) {
				printf("%d", *(func + (i * cube_size) + j));
			}
		}
		flag = 0;
	}
	printf("\n");

	free(func);
	free(divider);
	free(result);
	free(Q1);
	free(Q);
	free(Qnew);
	return 0;
}


static int r_kernels(ClientData clientData,Tcl_Interp *interp,int argc,const char *argv[]){
	int func_size, cube_size;
	int *func = NULL;
	int *K = NULL;
	list_list *head = NULL;
	list_list *freing = NULL;
	SOP *freesop = NULL;

	if (argc < 4) {
		printf("Too few arguments\n");
		return(0);
	}

	func_size = argc - 3;
	cube_size = strlen(argv[2]);
	func = (int *)malloc(func_size * cube_size * sizeof(int));
	K = (int *)malloc(cube_size * sizeof(int));
	head = NULL;
	//initialising func table
	for (int i = 0; i < func_size; i++) {
		cubes_to_table(argv, (2 + i), (func + i * cube_size));
	}

	kernels(&head, func, func_size, 0, cube_size);

	//print the result
	printf("G = {");
	for (list_list *i = head; i != NULL; i = i->next) {
		printf("(");
		for (SOP *j = i->sum; j != NULL; j = j->next) {
			for (int k = 0; k < cube_size; k++) {
				printf("%d", *(j->cube + k));
			}
			if (j->next != NULL) {
				printf(" + ");
			}
		}
		printf(")");
		if (i->next != NULL) {
			printf(",");
		}
	}
	printf("}\n");
	//freeing mem
	for (list_list *i = head; i != NULL;) {
		for (SOP *j = i->sum; j != NULL;) {
			freesop = j;
			j = j->next;
			free(freesop->cube);
			free(freesop);
		}
		freing = i;
		i = i->next;
		free(freing);
	}
	free(K);
	free(func);
	return(0);
}
