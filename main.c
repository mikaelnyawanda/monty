#include "monty.h"
#include <sys/types.h>

#ifndef ssize_t
typedef long ssize_t;
#endif

int global_mode = STACK_MODE; /* Define global_mode, STACK_MODE by default */

/* Function prototypes */
void check_usage(int argc);
void execute_line(char *line, stack_t **stack, unsigned int line_number);
void select_opcode(char *opcode, stack_t **stack, unsigned int line_number);
void free_stack(stack_t *stack);
ssize_t getline(char **lineptr, size_t *n, FILE *stream);

/**
 * main - Monty bytecode interpreter entry point
 * @argc: Argument count
 * @argv: Argument vector
 * Return: EXIT_SUCCESS on success, EXIT_FAILURE on error
 */
int main(int argc, char **argv)
{
    FILE *file;
    stack_t *stack = NULL;
    unsigned int line_number = 0;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    check_usage(argc);
    file = fopen(argv[1], "r");
    if (!file)
    {
        fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }
    while ((read = getline(&line, &len, file)) != -1)
    {
        line_number++;
        execute_line(line, &stack, line_number);
    }
    free(line);
    fclose(file);
    free_stack(stack);
    return (EXIT_SUCCESS);
}

/**
 * execute_line - Processes each line and executes the opcode
 * @line: Line from bytecode file
 * @stack: Double pointer to the stack
 * @line_number: Line number of bytecode
 */
void execute_line(char *line, stack_t **stack, unsigned int line_number)
{
    char *opcode;

    opcode = strtok(line, " \n\t");
    if (!opcode || opcode[0] == '#')
        return;
    select_opcode(opcode, stack, line_number);
}

/**
 * check_usage - Verifies if usage of program is correct
 * @argc: Argument count
 */
void check_usage(int argc)
{
    if (argc != 2)
    {
        fprintf(stderr, "USAGE: monty file\n");
        exit(EXIT_FAILURE);
    }
}

/**
 * select_opcode - Selects the correct opcode function to execute
 * @opcode: Opcode string
 * @stack: Double pointer to the stack
 * @line_number: Line number of bytecode
 */
void select_opcode(char *opcode, stack_t **stack, unsigned int line_number)
{
    instruction_t opcodes[] = {
        {"push", opcode_push}, {"pall", opcode_pall},
        {"pint", opcode_pint}, {"pop", opcode_pop},
        {"swap", opcode_swap}, {"add", opcode_add},
        {"nop", opcode_nop}, {"sub", opcode_sub},
        {"div", opcode_div}, {"mul", opcode_mul},
        {"mod", opcode_mod}, {"pchar", opcode_pchar},
        {"pstr", opcode_pstr}, {"rotl", opcode_rotl},
        {"rotr", opcode_rotr}, {"stack", opcode_stack},
        {"queue", opcode_queue}, {NULL, NULL}
    };
    int i = 0;

    while (opcodes[i].opcode)
    {
        if (strcmp(opcode, opcodes[i].opcode) == 0)
        {
            opcodes[i].f(stack, line_number);
            return;
        }
        i++;
    }
    fprintf(stderr, "L%u: unknown instruction %s\n", line_number, opcode);
    exit(EXIT_FAILURE);
}

/**
 * free_stack - Frees a stack
 * @stack: Pointer to the stack to free
 */
void free_stack(stack_t *stack)
{
    stack_t *temp;

    while (stack)
    {
        temp = stack;
        stack = stack->next;
        free(temp);
    }
}
