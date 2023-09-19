#include <stdio.h>
#include <stdlib.h>

struct Node {
    double Value;
    struct Node* LeftNode;
    struct Node* RightNode;
};

struct BST {
    struct Node* root;
};

struct Node* createNode(double value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->Value = value;
    newNode->LeftNode = NULL;
    newNode->RightNode = NULL;
    return newNode;
}

struct BST* generateBST(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return NULL;
    }

    struct BST* bst = (struct BST*)malloc(sizeof(struct BST));
    bst->root = NULL;

    double value;
    fscanf(file, "%lf", &value);
    bst->root = createNode(value);

    while (fscanf(file, "%lf", &value) != EOF) {
        struct Node* currentNode = bst->root;
        while (1) {
            if (value < currentNode->Value) {
                if (currentNode->LeftNode == NULL) {
                    currentNode->LeftNode = createNode(value);
                    break;
                }
                else {
                    currentNode = currentNode->LeftNode;
                }
            }
            else if (value > currentNode->Value) {
                if (currentNode->RightNode == NULL) {
                    currentNode->RightNode = createNode(value);
                    break;
                }
                else {
                    currentNode = currentNode->RightNode;
                }
            }
            else {
                printf("Duplicate value found: %lf\n", value);
                break;
            }
        }
    }

    fclose(file);
    return bst;
}

void addNode(struct BST* bst, double value) {
    struct Node* newNode = createNode(value);

    if (bst->root == NULL) {
        bst->root = newNode;
        return;
    }

    struct Node* currentNode = bst->root;
    while (1) {
        if (value < currentNode->Value) {
            if (currentNode->LeftNode == NULL) {
                currentNode->LeftNode = newNode;
                break;
            }
            else {
                currentNode = currentNode->LeftNode;
            }
        }
        else if (value > currentNode->Value) {
            if (currentNode->RightNode == NULL) {
                currentNode->RightNode = newNode;
                break;
            }
            else {
                currentNode = currentNode->RightNode;
            }
        }
        else {
            printf("Duplicate value found: %lf\n", value);
            free(newNode);
            break;
        }
    }
}

struct Node* searchNode(struct Node* currentNode, double value) {
    if (currentNode == NULL || currentNode->Value == value) {
        return currentNode;
    }

    if (value < currentNode->Value) {
        return searchNode(currentNode->LeftNode, value);
    }
    else {
        return searchNode(currentNode->RightNode, value);
    }
}

struct Node* findMinValueNode(struct Node* node) {
    struct Node* current = node;
    while (current->LeftNode != NULL) {
        current = current->LeftNode;
    }
    return current;
}

struct Node* removeNode(struct Node* root, double value) {
    if (root == NULL) {
        return root;
    }

    if (value < root->Value) {
        root->LeftNode = removeNode(root->LeftNode, value);
    }
    else if (value > root->Value) {
        root->RightNode = removeNode(root->RightNode, value);
    }
    else {
        if (root->LeftNode == NULL) {
            struct Node* temp = root->RightNode;
            free(root);
            return temp;
        }
        else if (root->RightNode == NULL) {
            struct Node* temp = root->LeftNode;
            free(root);
            return temp;
        }

        struct Node* temp = findMinValueNode(root->RightNode);
        root->Value = temp->Value;
        root->RightNode = removeNode(root->RightNode, temp->Value);
    }
    return root;
}

int countNodes(struct Node* node) {
    if (node == NULL) {
        return 0;
    }
    return 1 + countNodes(node->LeftNode) + countNodes(node->RightNode);
}

int getMaxDepth(struct Node* node) {
    if (node == NULL) {
        return 0;
    }
    int leftDepth = getMaxDepth(node->LeftNode);
    int rightDepth = getMaxDepth(node->RightNode);
    return 1 + (leftDepth > rightDepth ? leftDepth : rightDepth);
}

int countLeafNodes(struct Node* node) {
    if (node == NULL) {
        return 0;
    }
    if (node->LeftNode == NULL && node->RightNode == NULL) {
        return 1;
    }
    return countLeafNodes(node->LeftNode) + countLeafNodes(node->RightNode);
}

void printInorder(struct Node* node) {
    if (node == NULL) {
        return;
    }
    printInorder(node->LeftNode);
    printf("%lf ", node->Value);
    printInorder(node->RightNode);
}

void printPreorder(struct Node* node) {
    if (node == NULL) {
        return;
    }
    printf("%lf ", node->Value);
    printPreorder(node->LeftNode);
    printPreorder(node->RightNode);
}

void printPostorder(struct Node* node) {
    if (node == NULL) {
        return;
    }
    printPostorder(node->LeftNode);
    printPostorder(node->RightNode);
    printf("%lf ", node->Value);
}

void printGivenLevel(struct Node* node, int level) {
    if (node == NULL)
        return;
    if (level == 1)
        printf("%.2f ", node->Value);
    else if (level > 1) {
        printGivenLevel(node->LeftNode, level - 1);
        printGivenLevel(node->RightNode, level - 1);
    }
}

void printLevelOrder(struct Node* root) {
    int height = getMaxDepth(root);
    for (int i = 1; i <= height; i++) {
        printGivenLevel(root, i);
    }
}

void printTree(struct BST* bst) {
    int choice;
    printf("Choose a traversal method:\n");
    printf("1. Inorder\n");
    printf("2. Preorder\n");
    printf("3. Postorder\n");
    printf("4. Levelorder\n");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            printf("Inorder traversal: ");
            printInorder(bst->root);
            break;
        case 2:
            printf("Preorder traversal: ");
            printPreorder(bst->root);
            break;
        case 3:
            printf("Postorder traversal: ");
            printPostorder(bst->root);
            break;
        case 4:
            printf("Levelorder traversal: ");
            printLevelOrder(bst->root);
            break;
        default:
            printf("Invalid choice.\n");
            return;
    }
    printf("\n");
}

int main() {
    struct BST* bst = generateBST("input.txt");
    if (bst == NULL) {
        return 1;
    }

    int choice;
    double value;
    struct Node* result;

    while (1) {
        printf("Menu:\n");
        printf("1. Add Node\n");
        printf("2. Remove Node\n");
        printf("3. Search Node\n");
        printf("4. Count Nodes\n");
        printf("5. Get Max Depth\n");
        printf("6. Count Leaf Nodes\n");
        printf("7. Print Tree\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the value to add: ");
                scanf("%lf", &value);
                addNode(bst, value);
                break;
            case 2:
                printf("Enter the value to remove: ");
                scanf("%lf", &value);
                bst->root = removeNode(bst->root, value);
                break;
            case 3:
                printf("Enter the value to search: ");
                scanf("%lf", &value);
                result = searchNode(bst->root, value);
                if (result != NULL) {
                    printf("Node with value %lf found.\n", value);
                }
                else {
                    printf("Node with value %lf not found.\n", value);
                }
                break;
            case 4:
                printf("Total number of nodes: %d\n", countNodes(bst->root));
                break;
            case 5:
                printf("Maximum depth of the tree: %d\n", getMaxDepth(bst->root));
                break;
            case 6:
                printf("Number of leaf nodes: %d\n", countLeafNodes(bst->root));
                break;
            case 7:
                printTree(bst);
                break;
            case 8:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice.\n");
                break;
        }
        printf("\n");
    }

    return 0;
}
