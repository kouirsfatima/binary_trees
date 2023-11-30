#include "binary_trees.h"

/**
 * enqueue - Add an element to the end of the queue
 * @queue: A pointer to the queue where the element should be added
 * @address: A pointer to the data (in this case, a memory address) to be added
 * Return: (void)
 */
void enqueue(Queue *queue, const void *address)
{
	Node *new;

	if (!queue)
		return;
	new = malloc(sizeof(Node));
	if (new)
	{
		new->btree_node = address;
		new->next = NULL;
		if (!queue->front) /* if queue is empty */
			queue->front = queue->rear = new;
		else
		{
			queue->rear->next = new;
			queue->rear = new;
		}
	}
}

/**
 * dequeue - Remove and return the front element from the queue.
 * @queue: A pointer to the queue from which an element should be removed
 * Return: the memory address that is stored in the queue
 */
const void *dequeue(Queue *queue)
{
	Node *tmp;
	const void *address;

	if (!queue || !queue->front)
		return (NULL);
	tmp = queue->front;
	queue->front = queue->front->next;
	if (queue->front == NULL) /* if no element been in queue */
		queue->rear = NULL;
	address = tmp->btree_node;
	free(tmp);
	return (address);
}

/**
 * free2 - rees the memory allocated for a Queue and its associated Nodes
 * @queue: A pointer to the Queue to be deallocated.
 * Return: (void)
 */
void free2(Queue *queue)
{
	Node *tmp;

	if (!queue)
		return;
	tmp = queue->front;
	while (queue->front)
	{
		tmp = queue->front;
		queue->front = queue->front->next;
		free(tmp);
	}
	free(queue);
}

/**
 * binary_tree_is_complete - checks if a binary tree is complete
 * using level-order traversal
 * @tree: a pointer to the root node of the tree to check
 * Return: 1 if the tree is complete otherwise 0
 */
int binary_tree_is_complete(const binary_tree_t *tree)
{
	Queue *queue;
	int flag = 0;
	const binary_tree_t *btree_node, *left, *right;

	if (tree == NULL)
		return (0);
	queue = malloc(sizeof(Queue));
	if (!queue)
		return (0);
	queue->front = queue->rear = NULL;
	enqueue(queue, tree);
	while (queue->front)
	{
		btree_node = dequeue(queue);
		left = btree_node->left, right = btree_node->right;
		if (left)
		{
			if (flag == 1)
			{
				free2(queue);
				return (0);
			}
			enqueue(queue, left);
		}
		else
			flag = 1;
		if (right)
		{
			if (flag == 1)
			{
				free2(queue);
				return (0);
			}
			enqueue(queue, right);
		}
		else
			flag = 1;
	}
	free2(queue);
	return (1);
}
