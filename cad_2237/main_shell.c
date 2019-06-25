#include <stdlib.h>
#include <tcl/tcl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "readline_api.h"
#include "aux_functions.h"

Tcl_Interp *interp = NULL;



int main (int argc ,char *argv[]) {


	Tcl_FindExecutable(argv[0]);
	interp = Tcl_CreateInterp();
	Tcl_AppInit(interp);
	char *text = NULL; // readline result //
	char *textexpansion; // readline result history expanded //
	int expansionresult;
	HIST_ENTRY **the_history_list; // readline commands history list -NULL terminated //
	char command[LINE_MAX]; // current command //
	unsigned long i;
	char *tcl_result;




	// Readline Initialisation //
	rl_completion_entry_function= NULL; // use rl_filename_completion_function(), the default filename completer //
	rl_attempted_completion_function= custom_completer;
	rl_completion_append_character= '\0';
	using_history(); // initialise history functions //
	while (1){
		text = readline("PR> ");
		if (text != NULL){
			text = stripwhite(text);
			expansionresult= history_expand(text, &textexpansion);
			if ((expansionresult== 0) || // no expansion //
			(expansionresult== 2)) // do not execute //
			{
				add_history(text);
				strcpy(command, text); // store command //
			}
			else{
				add_history(textexpansion);
				strcpy(command, textexpansion); // store command //
			}
			free(textexpansion);
			free(text);
		}


	// handle two basic commands: history and quit //
		if (strcmp(command, "quit") == 0){
			strcpy(command,"exit");
		}
		if (strcmp(command, "history") == 0){
			the_history_list= history_list(); // get history list //
			if (the_history_list!= NULL)	{
				i= 0;
				while (*(the_history_list+ i) != NULL) // history list -NULL terminated //
				{
					printf("%ld: %s\n", (i+ history_base), (*(the_history_list + i))->line);
					i++;
				}
			}
		}
		// else give the command handling to tcl //
		else {
			if (strcmp(command, "exit") == 0) {
				//
			}
			Tcl_Eval(interp, command);
			tcl_result = (char *)Tcl_GetStringResult(interp);
			// if the function is one of the basic tcl functions we have to //
			// print the result else nothing appears on our screen //
			if(strcmp(tcl_result,"")!= 0){
				printf("%s\n",tcl_result );

			}
		}

	}


    return 0;// just for compiler warnings //
}
