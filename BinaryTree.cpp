#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_SIZE 50

typedef struct {
    char word[MAX_WORD_SIZE];
} NodeData;

typedef struct TreeNode {
    NodeData data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

typedef struct {
    TreeNode* root;
} BinaryTree;

TreeNode* buildTree(FILE* in) {
    char str[MAX_WORD_SIZE];
    int cnt = fscanf(in, "%s", str);
    if (cnt != 1 || strcmp(str, "@") == 0) {
        return NULL;
    }
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    strcpy(node->data.word, str);
    node->left = buildTree(in);
    node->right = buildTree(in);
    return node;
}

void visit(TreeNode* node) {
    printf("%s ", node->data.word);
}

void preOrder(TreeNode* node, int level) {
    if (node != NULL) {
        printf("%s (level %d)\n", node->data.word, level);
        preOrder(node->left, level + 1);
        preOrder(node->right, level + 1);
    }
}

void inOrder(TreeNode* node) {
    if (node != NULL) {
        inOrder(node->left);
        visit(node);
        inOrder(node->right);
    }
}

void postOrder(TreeNode* node) {
    if (node != NULL) {
        postOrder(node->left);
        postOrder(node->right);
        visit(node);
    }
}

int countNodes(TreeNode* node) {
    if (node == NULL) {
        return 0;
    }
    return 1 + countNodes(node->left) + countNodes(node->right);
}

int main() {
    FILE* file = fopen("Names.txt", "r");
    if (file == NULL) {
        printf("Error: Unable to open file.\n");
        return 1;
    }

    BinaryTree bt;
    bt.root = buildTree(file);
    fclose(file);

    if (bt.root == NULL) {
        printf("The tree is empty.\n");
        return 0;
    }

    printf("Pre-order Traversal with Levels:\n");
    preOrder(bt.root, 1);
    printf("\n");

    printf("In-order Traversal:\n");
    inOrder(bt.root);
    printf("\n\n");

    printf("Post-order Traversal:\n");
    postOrder(bt.root);
    printf("\n\n");

    int totalNodes = countNodes(bt.root);
    printf("There are %d nodes in the tree.\n", totalNodes);

    return 0;
}

