#ifndef MYTCL
#define MYTCL

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

static int myls(ClientData clientData,Tcl_Interp *interp,int argc,const char *argv[]);

static int myless(ClientData clientData,Tcl_Interp *interp,int argc,const char *argv[]);

int Tcl_AppInit(Tcl_Interp *interp);

static int cube_intersect_2(ClientData clientData,Tcl_Interp *interp,int argc,const char *argv[]);

static int supercube_2(ClientData clientData,Tcl_Interp *interp,int argc,const char *argv[]);

static int distance_2(ClientData clientData,Tcl_Interp *interp,int argc,const char *argv[]);

static int cube_cover_2(ClientData clientData,Tcl_Interp *interp,int argc,const char *argv[]);

static int sharp_2(ClientData clientData,Tcl_Interp *interp,int argc,const char *argv[]);

static int sharp(ClientData clientData,Tcl_Interp *interp,int argc,const char *argv[]);

static int off_f(ClientData clientData,Tcl_Interp *interp,int argc,const char *argv[]);

static int read_graph(ClientData clientData,Tcl_Interp *interp,int argc,const char *argv[]);

static int write_graph(ClientData clientData,Tcl_Interp *interp,int argc,const char *argv[]);

static int draw_graph(ClientData clientData,Tcl_Interp *interp,int argc,const char *argv[]);

static int graph_critical_path(ClientData clientData,Tcl_Interp *interp,int argc,const char *argv[]);

static int alg_division(ClientData clientData,Tcl_Interp *interp,int argc,const char *argv[]);

static int r_kernels(ClientData clientData,Tcl_Interp *interp,int argc,const char *argv[]);

#endif
