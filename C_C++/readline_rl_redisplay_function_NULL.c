// @BAKE gcc $@ -o rl.out $(pkg-config --libs readline) -g
#include <stdio.h>
#include <readline/readline.h>

int main(void) {
    /* Variable: rl_voidfunc_t * rl_redisplay_function
     *  If non-zero, Readline will call indirectly through this pointer to update
     *  the display with the current contents of the editing buffer.
     *  By default, it is set to rl_redisplay,
     *  the default Readline redisplay function (see Redisplay).
     */
    rl_redisplay_function = NULL;
    // The above documentation quote is correct, but forgets to add "else segfault"

    char * input = readline("> ");
    puts(input);
}
