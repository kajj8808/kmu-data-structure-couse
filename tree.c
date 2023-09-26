#include <stdio.h>
#include <stdlib.h>

int nodeCount = 0;

typedef struct
{
    int key;
    struct TreeNode *left, *right;
} TreeNode;

TreeNode *new_node(int item)
{
    TreeNode *temp = (TreeNode *)malloc(sizeof(TreeNode));
    temp->key = item;
    temp->left = temp->right = NULL;
    return temp;
}

// 중위
void inorder(TreeNode *root)
{

    // root node 가 존재할 때 + ( node 가 null 이 아닐때 즉 node 가 존재할 경우)
    if (root)
    {
        nodeCount++;
        // 중위 이기에 L V R 순서로 실행( 출력 )합니다.
        inorder(root->left);
        printf("%d ", root->key);
        inorder(root->right);
    }
}

TreeNode *insert_node(TreeNode *node, int key)
{
    nodeCount++;
    // 트리가 공백이면 새로운 노드를 반환한다.
    if (node == NULL)
        return new_node(key);

    // 그렇지 않으면 순환적으로 트리를 내려간다.
    if (key < node->key)
        node->left = insert_node(node->left, key);
    else if (key > node->key)
        node->right = insert_node(node->right, key);

    // 변경된 루트 포인터를 반환한다.
    return node;
}

TreeNode *insert_node_I(TreeNode *node, int key)
{

    while (1)
    {
        nodeCount++;
        if (key < node->key)
        {
            node = node->left;
        }
        else if (key > node->key)
        {

            node = node->right;
        }

        // 트리가 공백이면 새로운 노드를 반환한다.
        if (node == NULL)
            return new_node(key);
    }
}

// 반복적인 탐색 함수
TreeNode *search(TreeNode *node, int key)
{
    while (node != NULL)
    {
        nodeCount++;
        if (key == node->key)
            return node;
        else if (key < node->key)
            node = node->left;
        else
            node = node->right;
    }
    return NULL; // 탐색에 실패했을 경우 NULL 반환
}

TreeNode *min_value_node(TreeNode *node)
{
    TreeNode *current = node;

    // 맨 왼쪽 단말 노드를 찾으러 내려감
    while (current->left != NULL)
        current = current->left;

    return current;
}

TreeNode *delete_node(TreeNode *root, int key)
{
    nodeCount++;
    if (root == NULL)
        return root;

    // 만약 키가 루트보다 작으면 왼쪽 서브 트리에 있는 것임
    if (key < root->key)
        root->left = delete_node(root->left, key);
    // 만약 키가 루트보다 크면 오른쪽 서브 트리에 있는 것임
    else if (key > root->key)
        root->right = delete_node(root->right, key);
    // 키가 루트와 같으면 이 노드를 삭제하면 됨
    else
    { // 삭제할 노드를 찾았을 경우
        if (root->left == NULL)
        {
            TreeNode *temp = root->right;
            free(root);
            return temp; // 위에 값에 대체 되도록? 자식 2개를 찾는 코드
        }
        else if (root->right == NULL)
        {
            TreeNode *temp = root->left;
            free(root);
            return temp;
        }
        // 자식이 2개의 경우 적자를 찾아줘야 함.
        TreeNode *temp = min_value_node(root->right); // 오른쪽으로 한번 가고 제일 왼쪽으로.

        root->key = temp->key; // 이때 root 는 삭제 할 노드 라고 보면 될듯.
        // 노드를 삭제하고 대치했기 떄문에 오른쪽 값을 찾고 연결시켜줌.
        root->right = delete_node(root->right, temp->key);
    }
    return root;
}

int main()
{
    TreeNode *root = insert_node(NULL, 60);
    root = insert_node(root, 41);
    root = insert_node(root, 74);
    root = insert_node(root, 16);
    root = insert_node(root, 53);
    root = insert_node(root, 65);
    root = insert_node(root, 25);
    root = insert_node(root, 46);
    root = insert_node(root, 55);
    root = insert_node(root, 63);
    root = insert_node(root, 70);
    root = insert_node(root, 42);
    root = insert_node(root, 62);
    root = insert_node(root, 64);
    nodeCount = 0; // count 초기화
    // s
    TreeNode *result = search(root, 25);
    printf("검색 성공: %d\n", result->key);
    printf("방문한 노드의 수: %d\n", nodeCount);
    inorder(root); // 중위 순회
    nodeCount = 0; // count 초기화
    printf("\n");
    printf("\n");
    // i
    insert_node(root, 88);
    printf("방문한 노드의 수: %d\n", nodeCount);
    inorder(root); // 중위 순회
    nodeCount = 0; // count 초기화
    printf("\n");
    printf("\n");

    // d
    delete_node(root, 63);
    printf("방문한 노드의 수: %d\n", nodeCount);
    inorder(root); // 중위 순회
    nodeCount = 0; // count 초기화
    printf("\n");
    printf("\n");

    // t
    inorder(root); // 중위 순회
    printf("\n");
    printf("방문한 노드의 수: %d\n", nodeCount);
    nodeCount = 0; // count 초기화
    printf("\n");

    // I
    insert_node_I(root, 43);
    printf("방문한 노드의 수: %d\n", nodeCount);
    inorder(root); // 중위 순회
    nodeCount = 0; // count 초기화
    printf("\n");
    printf("\n");
    // D

    printf("---------------------------------\n");
    printf("| s\t: 검색\t\t\t|\n");
    printf("| i\t: 노드 추가\t\t|\n");
    printf("| d\t: 노드 삭제\t\t|\n");
    printf("| t\t: 중위 순회\t\t|\n");
    printf("| I\t: 노드 추가(반복)\t|\n");
    printf("| D\t: 노드 삭제(반복)\t|\n");
    printf("| c\t: 종료\t\t\t|\n");
    printf("---------------------------------\n");
    char menu;
    printf("메뉴 입력: ");
    scanf(&menu);
    printf("%c ", menu);
    return 0;
}
