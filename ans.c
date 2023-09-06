#include <stdio.h>
#include <stdlib.h>

// 定义链表节点
struct Node {
    int data;
    struct Node* next;
};

// 插入节点到链表尾部
void insert(struct Node** head, int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = NULL;

    if (*head == NULL) {
        *head = newNode;
    } else {
        struct Node* current = *head;
        while (current->next) {
            current = current->next;
        }
        current->next = newNode;
    }
}

// 反转链表
void reverse(struct Node** head) {
    struct Node* prev = NULL;
    struct Node* current = *head;
    struct Node* nextNode = NULL;

    while (current) {
        nextNode = current->next;
        current->next = prev;
        prev = current;
        current = nextNode;
    }

    *head = prev;
}

// 打印链表元素
void printList(struct Node* head) {
    struct Node* current = head;
    while (current) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

struct Node* addLists(struct Node* list1, struct Node* list2) {
    reverse(&list1);
    reverse(&list2);

    struct Node* result = NULL;
    struct Node* current1 = list1;
    struct Node* current2 = list2;
    int carry = 0;

    while (current1 || current2) {
        int value1 = (current1) ? current1->data : 0;
        int value2 = (current2) ? current2->data : 0;

        int sum = value1 + value2 + carry;
        carry = sum / 10;
        int digit = sum % 10;

        insert(&result, digit);

        if (current1) current1 = current1->next;
        if (current2) current2 = current2->next;
    }

    if (carry > 0) {
        insert(&result, carry);
    }

    reverse(&result);

    return result;
}

int main() {
    struct Node* list1 = NULL;
    struct Node* list2 = NULL;

    // 从文件读取粒子数据到链表list1
    FILE *file = fopen("dataset/dataset_120.txt", "r");
    if (file) {
        char ch;
        while (fscanf(file, "%c", &ch) != EOF) {
            int value = ch - '0'; // 将字符转换为整数
            insert(&list1, value);
        }
        fclose(file);
    } else {
        printf("Cannot open file\n");
        return 1;
    }

    // 复制list1到list2并移除2
    struct Node* current = list1;
    while (current) {
        if (current->data != 2) {
            insert(&list2, current->data);
        }
        current = current->next;
    }

    printf("orig: ");
    printList(list1);

    printf("after remove 2: ");
    printList(list2);

    // 相加數字序列
    struct Node* sumList = addLists(list1, list2);
    printf("sum two list : ");
    printList(sumList);

    // 释放链表内存
    while (list1) {
        struct Node* temp = list1;
        list1 = list1->next;
        free(temp);
    }

    while (list2) {
        struct Node* temp = list2;
        list2 = list2->next;
        free(temp);
    }

    while (sumList) {
        struct Node* temp = sumList;
        sumList = sumList->next;
        free(temp);
    }

    return 0;
}
