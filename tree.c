#include <stdio.h>
#include <stdlib.h>

int nodeCount = 0;

typedef struct TreeNode
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

// 트리를 중위 표현식으로 출력하는데 사용하는 함수입니다.
void inorder(TreeNode *root)
{
    if (root)
    {
        // 방문한 노드수를 카운트 합니다.
        nodeCount++;
        // 중위 이기에 L V R 순서로 출력/실행 합니다.
        inorder(root->left);
        printf("%d ", root->key);
        inorder(root->right);
    }
}

// 바이너리 검색 트리에 재귀 방식으로 노드를 추가하는 함수입니다.
TreeNode *insert_node(TreeNode *node, int key)
{
    // 방문한 노드수를 카운트 합니다.
    nodeCount++;
    // 빈공간일 경우 새로운 노드를 추가합니다.
    if (node == NULL)
        return new_node(key);

    // 그렇지 않으면 순환적으로 트리를 내려가 빈 공간을 찾습니다.
    if (key < node->key)
        node->left = insert_node(node->left, key);
    else if (key > node->key)
        node->right = insert_node(node->right, key);

    // 변경된 트리를 반환합니다.
    return node;
}

// 바이너리 검색 트리에 반복적인 방식으로 노드를 추가하는 함수입니다.
TreeNode *insert_node_I(TreeNode *node, int key)
{
    TreeNode *newNode = new_node(key);
    if (node == NULL)
        return newNode;

    TreeNode *current = node;
    TreeNode *parent = NULL;

    while (current)
    {
        // 방문한 노드수를 카운트 합니다.
        nodeCount++;
        // 비어있는 곳을 찾아 부모 노드에 저장해 둡니다.
        parent = current;
        if (key < current->key)
            current = current->left;
        else if (key > current->key)
            current = current->right;
        else
        {
            // 중복되는 노드는 넘어갑니다.
            free(newNode);
            return node;
        }
    }
    // 비어 있는 곳(부모 노드)의 값에 따라 작다면 왼쪽 아니면 오른쪽에 넣어줍니다.
    if (key < parent->key)
        parent->left = newNode;
    else
        parent->right = newNode;

    return node;
}

// 반복적인 탐색 함수 입니다.
TreeNode *search(TreeNode *node, int key)
{
    while (node != NULL)
    {
        // 방문한 노드수를 카운트 합니다.
        nodeCount++;
        // 반복적인 방식(key 값이 작다면 왼쪽 아니면 오른쪽으로 옮기는 것을 반복)으로 key값을 가진 노드를 찾습니다.
        if (key == node->key)
            return node;
        else if (key < node->key)
            node = node->left;
        else
            node = node->right;
    }
    return NULL; // 탐색에 실패했을 경우 NULL 반환
}

// delete 함수를 사용할때 사용하는 함수로 가장 비슷한 값을 찾기위해 사용되는 함수입니다.
TreeNode *min_value_node(TreeNode *node)
{
    TreeNode *current = node;

    // 비슷한 값을 받을려는 노드에서 오른쪽으로 한번 왔으므로 왼쪽 밑의 노드를 찾아 삭제 할려는 값과 비슷한 값을 찾습니다.
    while (current->left != NULL)
        current = current->left;

    return current;
}

// 재귀 방식으로 노드를 삭제하는 함수입니다.
TreeNode *delete_node(TreeNode *root, int key)
{
    // 움직인 노드수를 카운트 합니다.
    nodeCount++;
    if (root == NULL)
        return root;

    // key값이 작으면 왼쪽 에 있다보고 왼쪽 노드로 넘어갑니다.
    if (key < root->key)
        root->left = delete_node(root->left, key);
    // key의 값이 반대로 크면 오른쪽 노드에 있다보고 오른쪽 으로 이동합니다.
    else if (key > root->key)
        root->right = delete_node(root->right, key);
    // 키와 루트가 같을시 동일한 값이므로 넘어갑니다.
    else
    {
        // 삭제할 노드를 찾았을 경우
        if (root->left == NULL)
        {
            TreeNode *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            TreeNode *temp = root->left;
            free(root);
            return temp;
        }
        // 자식이 2개의 경우 적자(가장 비슷한 값)을 찾아줍니다.
        TreeNode *temp = min_value_node(root->right); // 오른쪽으로 한번 가고 제일 왼쪽으로가는 방식으로 비슷한 값을 찾습니다.

        // 가장 비슷한 값을 삭제할 root에 있는 key 에 대입해 줍니다.
        root->key = temp->key;
        // 오른쪽 노드를 찾아줍니다.
        root->right = delete_node(root->right, temp->key);
    }
    return root;
}

// 노드 삭제함수를 반복적인 방식으로 구현한 함수입니다.
TreeNode *delete_node_D(TreeNode *root, int key)
{
    TreeNode *temp = root;
    TreeNode *parent = NULL;
    /*
        삭제될 노드가 왼쪽에 있는지 오른쪽에 있는지 확인하기 위해 사용합니다.
        왼쪽은 0 오른쪽은 1 입니다. 만약 찾지 못한다면 -1 으로 할당해 줍니다.
    */

    int deleteNodePosition = -1;

    while (temp)
    {
        // 웁직인 노드를 카운트 합니다.
        nodeCount++;
        // 삭제할 값을 찾았을 경우.
        if (temp->key == key)
        {
            // 왼쪽이 비어있을 경우 에는 삭제할 노드가 오른쪽에 있는지 왼쪽에 있는지를 보고 값을 삭제해 주고 노드를 이어줍니다.
            if (temp->left == NULL)
            {
                if (deleteNodePosition == 1)
                {
                    parent->right = temp->right;
                }
                else
                {
                    parent->left = temp->right;
                }
                free(temp);
                break;
            }
            // 오른쪽이 비어있을 경우에도 마찬가지로 노드를 삭제하고 이어줍니다.
            if (temp->right == NULL)
            {
                if (deleteNodePosition == 1)
                {
                    parent->right = temp->left;
                }
                else
                {
                    parent->left = temp->left;
                }
                free(temp);
                break;
            }
            // 오른쪽 왼쪽 둘다 비어있지 않을경우입니다.
            // 가장 비슷한값을 찾습니다.
            TreeNode *current = min_value_node(temp->right);
            // 가장 비슷한 값을 삭제하고자 하는 노드의 값에 대입해줍니다.
            temp->key = current->key;
            // 삭제를 위해 key 를 재활용 합니다. key에 변경된 값을 넣어줍니다.
            key = temp->key;
            // parent 부모 노드를 temp으로 변경하여 가장 밑에 있을 예정인 노드를 찾을 준비를합니다.
            parent = temp;
            // temp 의 오른쪽에서 가장 비슷한 값을 찾았기 때문에 오른쪽으로 한번 옮겨줍니다. 이후 반복적인 방식으로 위에서 삭제가 됩니다.
            temp = temp->right;
        }
        /* 삭제 하고자 하는 temp 를 찾아줍니다. 이떄 왼쪽에 있는지 오른쪽에 있는지를 저장해줍니다. */
        else if (temp->key > key)
        {
            deleteNodePosition = 0;
            parent = temp;
            temp = temp->left;
        }
        else if (temp->key < key)
        {
            deleteNodePosition = 1;
            parent = temp;
            temp = temp->right;
        }
    }

    return root;
}

int main()
{
    // 기본 트리를 생성합니다.
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
    nodeCount = 0; // insert_node 에서 올라간 값을 초기화 시켜줍니다.

    char menu;
    int key;
    printf("---------------------------------\n");
    printf("| s\t: 검색\t\t\t|\n");
    printf("| i\t: 노드 추가\t\t|\n");
    printf("| d\t: 노드 삭제\t\t|\n");
    printf("| t\t: 중위 순회\t\t|\n");
    printf("| I\t: 노드 추가(반복)\t|\n");
    printf("| D\t: 노드 삭제(반복)\t|\n");
    printf("| c\t: 종료\t\t\t|\n");
    printf("---------------------------------\n");

    TreeNode *result;
    while (1)
    {
        printf("메뉴 입력: ");
        scanf(" %c", &menu);
        switch (menu)
        {
        case 's':
            // s
            printf("검색할 값 입력: ");
            scanf(" %d", &key);
            result = search(root, key);
            printf("검색 성공: %d\n", result->key);
            printf("방문한 노드의 수: %d\n", nodeCount);
            inorder(root); // 중위 순회를 하여 현재 값을 확인합니다. 이경우에는 방문한 노드수를 출력하지 않았습니다.
            printf("\n");
            break;
        case 'i':
            // i
            printf("삽입할 값 입력: ");
            scanf(" %d", &key);
            insert_node_I(root, key);
            printf("방문한 노드의 수: %d\n", nodeCount);
            inorder(root); // 중위 순회를 하여 현재 값을 확인합니다. 이경우에는 방문한 노드수를 출력하지 않았습니다.
            printf("\n");
            break;
        case 'd':
            // d
            printf("삭제할 값 입력: ");
            scanf(" %d", &key);
            delete_node(root, key);
            printf("방문한 노드의 수: %d\n", nodeCount);
            inorder(root); // 중위 순회를 하여 현재 값을 확인합니다. 이경우에는 방문한 노드수를 출력하지 않았습니다.
            printf("\n");
            break;
        case 't':
            // t
            inorder(root); // 중위 순회를 하여 현재 값을 확인합니다.
            // 이 경우에는 방문한 노드를 출력합니다.
            printf("\n");
            printf("방문한 노드의 수: %d\n", nodeCount);
            break;
        case 'I':
            // I
            printf("삽입할 값 입력: ");
            scanf(" %d", &key);
            insert_node_I(root, 43);
            printf("방문한 노드의 수: %d\n", nodeCount);
            inorder(root); // 중위 순회를 하여 현재 값을 확인합니다. 이경우에는 방문한 노드수를 출력하지 않았습니다.
            printf("\n");
            break;
        case 'D':
            // D
            printf("삭제할 값 입력: ");
            scanf(" %d", &key);
            delete_node_D(root, 88);
            printf("방문한 노드의 수: %d\n", nodeCount);
            inorder(root); // 중위 순회를 하여 현재 값을 확인합니다. 이경우에는 방문한 노드수를 출력하지 않았습니다.
            printf("\n");
            break;
        case 'c':
            return 0;
            break;
        default:
            break;
        }
        // 노드 카운트를 초기화 시켜줍니다.
        nodeCount = 0;

        printf("\n");
    }

    return 0;
}
