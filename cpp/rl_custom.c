#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

int show_help(int state, int end)
{
    printf("\nNeed some help with: %s ?\n", rl_line_buffer);
        rl_on_new_line();
        return 0;
}

int main(int argc, char **argv)
{
        char *bindstr = "\"?\": custom_dumi";
        char *line;
        char *input;

        rl_add_defun("custom_dumi", (rl_command_func_t *)show_help, -1);
        line = malloc(1 + strlen(bindstr));
        strcpy(line, bindstr);

        rl_parse_and_bind(line);

        free(line);

        while (TRUE)
        {
                input = readline("rl: ");
                printf("%sn", input);
        }
}
