#include "monty.h"

/**
 * opcode_div - Divides the second top element of the stack by the top element.
 * @stack: Double pointer to the stack.
 * @line_number: Line number of the bytecode file.
 */
void opcode_div(stack_t **stack, unsigned int line_number)
{
	stack_t *temp;

	if (!*stack || !(*stack)->next)
	{
		fprintf(stderr, "L%u: can't div, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}

	if ((*stack)->n == 0)
	{
		fprintf(stderr, "L%u: division by zero\n", line_number);
		exit(EXIT_FAILURE);
	}

	temp = *stack;
	(*stack)->next->n /= temp->n;
	*stack = (*stack)->next;
	free(temp);
}
