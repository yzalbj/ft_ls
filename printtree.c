#include "./includes/ft_ls.h"
#define COUNT 2

void print2DUtil(t_node *root, int space)
{
    // Base case
    if (root == NULL)
        return;

    // Increase distance between levels
    space += COUNT;

    // Process right child first
    print2DUtil(root->right, space);

    // Print current node after space
    // count
    printf("\n");
    for (int i = COUNT; i < space; i++)
        printf(" ");
    printf("%s\n", root->stat->name);

    // Process left child
    print2DUtil(root->left, space);
}

// Wrapper over print2DUtil()
void print2D(t_node *root)
{
   // Pass initial space count as 0
   print2DUtil(root, 0);
}
