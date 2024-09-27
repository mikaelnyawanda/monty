#include "monty.h"

/**
 * opcode_mul - Multiplies the second top element of the stack with the top.
 * @stack: Double pointer to the stack.
 * @line_number: Line number of the bytecode file.
 */
void opcode_mul(stack_t **stack, unsigned int line_number)
{
	stack_t *temp;

	if (!*stack || !(*stack)->next)
	{
		fprintf(stderr, "L%u: can't mul, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}

	temp = *stack;
	(*stack)->next->n *= temp->n;
	*stack = (*stack)->next;
	free(temp);
}
