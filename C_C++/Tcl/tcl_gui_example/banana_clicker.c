// @BAKE gcc -o $*.out $@ -std=c23 $(pkg-config --cflags --libs tcl tk)
/* This is an implementation of Banana Clicker in C using a Tcl/Tk GUI.
 * This program is for demonstration purposes and is in the Public Domain.
 *
 * The afore mentioned game was chosen because its extremely simple:
 *  You click the banana on screen and your score goes up by 1.
 *
 * Tcl will be storing no state, it only handles the displaying.
 * This is accomplished by running an interpreter on its own thread.
 * Whenever the state must be updated according to user input,
 *  a callback writes global state.
 * We mark our global state compile-unit local because
 *  that would be the smart thing to do if we had more
 *  than 1 source file (given a more complex task).
 * Alternatively, to handle multiple display instances,
 *  we could employ a map of interpreters and state objects.
 */
#include <stdlib.h>
#include <pthread.h>
#include <tcl.h>
#include <tk.h>



// Our entire inner state. Maps directly to the user score.
static size_t click_counter = 0;



/* To interact with C, we have to define Tcl commands.
 * These behave exactly like regular procedures,
 *  we can call them seamlessly from our front-end script.
 */

// Macros to hide ugly Tcl API implementation details
#define TCL_ARGS ClientData clientData, Tcl_Interp *interp, int argc, const char **argv
#define TCL_EASY_CREATE_COMMAND(c) \
    Tcl_CreateCommand(interp, #c, Tcl_ ## c, (ClientData)NULL, (void (*)(void*))NULL);

static
int Tcl_cIncrementCounter(TCL_ARGS) {
    ++click_counter;
    return TCL_OK;
}

static
int Tcl_cGetCounter(TCL_ARGS) {
    char r[12]; // For simplicity we only account for 11 digits + '\0'
    sprintf(r, "%ld", click_counter);
    /* We have to tell Tcl how to manage the memory.
     * Below I marked `r` as a value Tcl should copy and manage herself.
     * Alternative options would be:
     *  specifying it as static,
     *  or memory returned by `Tcl_Alloc`.
     */
    Tcl_SetResult(interp, r, TCL_VOLATILE);
    return TCL_OK;
}

/* Since I would like this program to fit in a single file,
 *  we define our script as a string.
 * During prototyping one would instead have "gui.tcl" and
 *  call `Tcl_EvalFile` on it.
 * For production, one would embed the script and statically link to Tcl/Tk.
 */
const char * const tcl_script =
    "# @BAKE tclsh $@\n"
    "package require Tk\n"
    "\n"
    "# If not invoked from C tnen run in \"testing\" mode\n"
    "#  Very useful trick for prototyping\n"
    "if {![info exists ::WRAPPED]} {\n"
    "    proc cIncrementCounter {} {}\n"
    "    proc cGetCounter {} { return 0 }\n"
    "}\n"
    "\n"
    "wm title . \"Tcl Banana Clicker\"\n"
    "\n"
    "# Create a terribly illustrated banana\n"
    "canvas .banana -width 600 -height 600\n"
    ".banana create rectangle 100 200 500 300 -fill yellow\n"
    ".banana create rectangle 500 210 540 240 -fill black\n"
    "bind .banana <Button-1> {cIncrementCounter}\n"
    "pack .banana\n"
    "\n"
    "# Create a score message\n"
    "label .score\n"
    ".score configure -font \"TkDefaultFont 20\"\n"
    "pack .score\n"
    "\n"
    "# Loop in an event-driven fashion to query state from C\n"
    "proc updateState {} {\n"
    "    .score configure -text \"Your current score is: [cGetCounter]\"\n"
    "    after 100 updateState\n"
    "}\n"
    "\n"
    "after 100 updateState\n"
    "# Quit if the window is closed\n"
    "bind . <Destroy> {exit}\n"
;

/* As mentioned, the interpreter has to run on its own thread.
 * `Tk_MainLoop` blocks.
 */
static void tcl_run(void);

void tcl_loop(void) {
    pthread_t tcl_thread;
    pthread_create(&tcl_thread, NULL, (void* (*)(void*))tcl_run, (void*)NULL);
}

static
void tcl_run(void) {
    Tcl_Interp * interp = Tcl_CreateInterp();
    if (interp == NULL) {
        fprintf(stderr, "Can't create Tcl interpreter\n");
        exit(1);
    }

    Tcl_Init(interp);
    Tk_Init(interp);

    // Disable our testing trick
    Tcl_SetVar(interp, "WRAPPED", "true", 0); 

    TCL_EASY_CREATE_COMMAND(cIncrementCounter);
    TCL_EASY_CREATE_COMMAND(cGetCounter);

    int result = Tcl_Eval(interp, tcl_script);
    if (result == TCL_ERROR) {
        fprintf(stderr, "Tcl script execution failed: %s\n", Tcl_GetStringResult(interp));
        exit(1);
    }

    Tk_MainLoop();
}

signed main() {
    // Run the front-end first
    tcl_loop();

    /* Wait indefinitely for the front-end.
     * If we had a real game, this would be our main loop.
     * Obviously we could perform arbitrary computations,
     *  and Tcl would read it asynchronously.
     * Since we share our process with the interpreter,
     *  and it binds the window close to the exit system-call,
     *  our program will quit as expected.
     * Alternatively something like `bool do_run` could be updated
     *  for a more graceful shutdown.
     */
    while (true) { ; }

    return 0;
}
