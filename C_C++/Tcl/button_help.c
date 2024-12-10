// @BAKE gcc $@ -o $*.out $(pkg-config --cflags --libs tcl tk)
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <tcl.h>
#include <tk.h>

// our button callback
static
int Tcl_baah(ClientData clientData, Tcl_Interp * interp, int argc, const char * * argv) {
    puts("BAAAAAAAH");
    return TCL_OK;
}

static
void tcl_run(void) {
    Tcl_Interp * interp = Tcl_CreateInterp();
    Tcl_Init(interp);
    Tk_Init(interp);

    Tcl_CreateCommand(interp, "baah", Tcl_baah, (ClientData)NULL, (void (*)())NULL);

    /* if only it were past 2023 we could have #embed!
     * oh wait...
     */
    int result = Tcl_EvalFile(interp, "button_help.tcl");
    if (result == TCL_ERROR) {
        fprintf(stderr, "Tcl script execution failed: %s\n", Tcl_GetStringResult(interp));
        exit(1);
    }

    Tk_MainLoop();
}

signed main() {
    pthread_t tcl_thread;
    pthread_create(&tcl_thread, NULL, (void *(*)(void*))tcl_run, (void*)NULL);

    // whatever you want
    while (1) { ; }
}
