#include <stdio.h>
#include <stdlib.h>
#include <ucontext.h>

/**
 * example taken straight from Wikipedia: http://en.wikipedia.org/wiki/Setcontext
 */

/**
 * the iterator function. 
 */

void loop(ucontext_t *loop_context,
          ucontext_t *other_context,
          int *i_from_iterator)
{
    int i;
    for (i=0; i<10; ++i)
    {
        *i_from_iterator = i;
        swapcontext(loop_context, other_context);
    }
}

int main(void)
{
    ucontext_t main_context1, main_context2, loop_context;
    char iterator_stack[SIGSTKSZ];
    volatile int iterator_finished;
    volatile int i_from_iterator;

    loop_context.uc_link = &main_context1;
    loop_context.uc_stack.ss_sp = iterator_stack;
    loop_context.uc_stack.ss_size = sizeof(iterator_stack);
    getcontext(&loop_context);

    makecontext(&loop_context, loop, 3, &loop_context, &main_context2, &i_from_iterator);
    iterator_finished = 0;

    getcontext(&main_context1);

    if(!iterator_finished)
    {
        iterator_finished = 1;
        while(1)
        {
            swapcontext(&main_context2, &loop_context);
            printf("%d\n", i_from_iterator);
        }
    }
    return 0;
}
