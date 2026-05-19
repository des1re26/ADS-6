// Copyright 2022 NNTU-CS
#ifndef TPQUEUE_H
#define TPQUEUE_H

struct SYM {
    char ch;
    int prior;
};

template <typename T>
class TPQueue {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& item) : data(item), next(nullptr) {}
    };

    Node* head;

public:
    TPQueue() : head(nullptr) {}

    TPQueue(const TPQueue&) = delete;
    TPQueue& operator=(const TPQueue&) = delete;

    ~TPQueue() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void push(const T& item) {
        Node* newNode = new Node(item);

        if (!head || item.prior > head->data.prior) {
            newNode->next = head;
            head = newNode;
            return;
        }

        Node* current = head;
        while (current->next && current->next->data.prior >= item.prior) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }

    T pop() {
        if (!head) {
            return T{};
        }
        Node* temp = head;
        T result = head->data;
        head = head->next;
        delete temp;
        return result;
    }

    bool isEmpty() const {
        return head == nullptr;
    }
};

#endif // TPQUEUE_H
