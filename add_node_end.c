#include "monty.h"

/**
 * add_node_end - Adds a new node at the end of the stack.
 * @stack: Double pointer to the stack.
 * @value: The value to add to the new node.
 */
void add_node_end(stack_t **stack, int value)
{
	stack_t *new_node = malloc(sizeof(stack_t));
	stack_t *last = *stack;

	if (new_node == NULL)
	{
		fprintf(stderr, "Error: malloc failed\n");
		exit(EXIT_FAILURE);
	}

	new_node->n = value;
	new_node->next = NULL;

	if (*stack == NULL)
	{
		new_node->prev = NULL;
		*stack = new_node;
		return;
	}

	while (last->next != NULL)
		last = last->next;

	last->next = new_node;
	new_node->prev = last;
}
