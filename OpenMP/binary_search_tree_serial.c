#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/time.h>
#include <time.h>

struct node
{
	unsigned int data;
	struct node * left_child;
	struct node * right_child;
};

struct node * create_node(unsigned int data)
{
	struct node * new_node = (struct node *)malloc(sizeof(struct node));
	new_node->data = data;
	new_node->left_child = NULL;
	new_node->right_child = NULL;

	return new_node;
}


bool search(struct node * root, int target) 
{ 
    while (root != NULL) { 
        if (target > root->data) 
            root = root->right_child; 
  
        else if (target < root->data) 
            root = root->left_child; 
        else
            return true; 
    } 
    
    return false; 
} 


void insert(struct node * root, int new_node_data)
{
	struct node * new_node;
	struct node * current;
	struct node * parent;

	new_node = create_node(new_node_data);

	current = root;
	parent = NULL;

	if (root == NULL) {
		root = new_node;
	}

	while (current != NULL) 
	{
		parent = current;	

		if (new_node->data < current->data)
			current = current->left_child;

		else
			current = current->right_child;
	}

	if (new_node->data < parent->data)
		parent->left_child = new_node;

	else
		parent->right_child = new_node;

}

int * generate_leafs(int length)
{
	int * insert_numbers;
	int number;

	insert_numbers = malloc(sizeof(int) * length);

	for (number = 0x0; number < length; number++) 
		insert_numbers[number] = number;

	srand(time(NULL));

	for (number = 0x0; number < length - 0x1; number++)
	{
		int randommized = number + rand() / (RAND_MAX /
								(length - number) + 0x1);
		int temp = insert_numbers[randommized];
		insert_numbers[randommized] = insert_numbers[number];
		insert_numbers[number] = temp;
	}

	return insert_numbers;
}

void fill_tree(struct node * root, int * leafs, int leafs_length)
{
	int leaf;

	for (leaf = 0x0; leaf < leafs_length; leaf++)
		insert(root, leafs[leaf]);
}

void swing_tree(struct node * root)
{
	if (root != NULL)
	{
		printf("[%d]\n", root->data);
		swing_tree(root->left_child);
		swing_tree(root->right_child);
	}

	return;
}

int main(int argc, char ** argv)
{
	int * leafs;

  	struct timeval start;
  	struct timeval stop;
	struct node * root;

	int leafs_length;
	int leaf;
	int result;


	leafs_length = strtol(argv[0x1], NULL, 0xa);
	leafs = generate_leafs(leafs_length);

	root = create_node(leafs_length / 0x2);

	fill_tree(root, leafs, leafs_length);

	gettimeofday(&start, 0x0);
	search(root, 22);
	gettimeofday(&stop, 0x0);

	fprintf(stdout, "> Execution time\t %3.7f\n", (double) (stop.tv_usec - start.tv_usec) / 1000000 + (double)(stop.tv_sec - start.tv_sec));


	/* result = search(root, 10); */
	/* printf("Search result: %d\n", result); */
	/* swing_tree(root); */


	return 0x0;
}
