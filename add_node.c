#include "monty.h"

/**
 * add_node - Adds a new node at the beginning of the stack.
 * @stack: Double pointer to the stack.
 * @value: The value to add to the new node.
 */
void add_node(stack_t **stack, int value)
{
	stack_t *new_node = malloc(sizeof(stack_t));

	if (new_node == NULL)
	{
		fprintf(stderr, "Error: malloc failed\n");
		exit(EXIT_FAILURE);
	}

	new_node->n = value;
	new_node->prev = NULL;
	new_node->next = *stack;
	if (*stack != NULL)
		(*stack)->prev = new_node;
	*stack = new_node;
}
