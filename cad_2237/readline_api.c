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

char *custom_names[] = {
	"after",		"append",			"apply",		"array",
	"binary",		"break",			"catch",		"cd",
	"chan",			"clock",			"close",		"concat",
	"continue",		"coroutine",		"dict",			"encoding",
	"eof",			"error",			"eval",			"exec",
	"exit",			"expr",				"fblocked",		"fconfigure",
	"fcopy",		"file",				"fileevent",	"flush",
	"for",			"foreach",			"format",		"gets",
	"glob",			"history",			"if",			"incr",
	"info",			"join",				"lappend",		"lassign",
	"lindex",		"less",				"linsert",		"list",
	"llength",		"lmap",				"load",			"lrange",
	"lreplace",		"lrepeat",			"lreverse",		"ls",
	"lsearch",		"lset",				"lsort",		"namespace",
	"oo::object",	"oo::objdefine",	"oo::define",	"oo::copy",
	"oo::class",	"open",				"package",		"pid",
	"proc",			"puts",				"pwd",			"quit",
	"read",			"regexp",			"regsub",		"rename",
	"return",		"scan",				"seek",			"set",
	"socket",		"source",			"split",		"string",
	"subst",		"switch",			"tell",			"throw",
	"time",			"trace",			"try",			"unload",
	"unset",		"update",			"uplevel",		"upvar",
	"variable",		"vwait",			"while",		"yieldto",
	"zlib",		  	"cube_intersect_2", "distance_2", 	"cube_cover_2",
	"supercube_2", 	"sharp_2",			"sharp",		"off_f",
	"read_graph",	"write_graph",		"draw_graph",	"graph_critical_path",
	"alg_division",	"r_kernels",		NULL
};

/*how my custom completer works

	If there are no possible completions, we should return NULL.

	If there is one possible completion, we should return an array containing
	that completion, followed by a NULL value.

	If there are two or more possibilities, we should return an array containing
	the longest common prefix of all the options, followed by each of the
	possible completions, followed by a NULL value.

more specifically:
	By pressing tab readline isolates the word to be completed and calls custom_completer
	which the calls rl_completion_matches() to generate a list of possible
	completions. It then either lists the possible completions, inserts the
	possible completions, or actually performs the completion, depending on
	which behavior is desired.

	The internal function rl_completion_matches() uses an application-supplied
	generator function to generate the list of possible matches, and then
	returns the array of these matches. The caller should place the address of
	its generator function in rl_completion_entry_function.

	The generator function is called repeatedly from rl_completion_matches(),
	returning a string each time. The arguments to the generator function are
	text and state. text is the partial word to be completed. state is zero the
	first time the function is called, allowing the generator to perform any
	necessary initialization, and a positive non-zero integer for each subsequent
	call. The generator function returns (char *)NULL to inform
	rl_completion_matches() that there are no more possibilities left. Usually
	the generator function computes the list of possible completions when state
	is zero, and returns them one at a time on subsequent calls. Each string
	the generator function returns as a match must be allocated with malloc();
	Readline frees the strings when it has finished with them.

	*/


char *character_name_generator(const char *text, int state){
    static int i, length;// static variables so their values dont change between the subsequent calls //
    char *name;

	// initialising the values the first time we enter this function for every //
	// completion try //
	if (!state) {
        i = 0;
        length = strlen(text);
    }
// while loop which scans the namelist with the 1++ step and returns the completion //
// string if it matches //
    while ((name = custom_names[i++])) {
        if (strncmp(name, text, length) == 0) {
            return strdup(name);
        }
    }

    return NULL;
}

//
char **custom_completer(const char *text, int start, int end){

	if(!start){

		return rl_completion_matches(text, character_name_generator);
	}

	return NULL;
}

// removes a whitespace from the end of the string //
char *stripwhite(char *string){
register char *s, *t;

for (s = string; whitespace (*s); s++){
	if (*s == 0){
		return (s);

	}
}

t = s + strlen (s) - 1;
while (t > s && whitespace (*t)){
	t--;
	*++t = '\0';

}

return s;
}
