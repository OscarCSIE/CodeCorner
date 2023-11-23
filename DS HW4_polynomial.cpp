#include <iostream>

class Node {
private:
    double m_coef, m_exp;
    Node* next;
    friend class LinkedList;
    friend std::ostream& operator<<(std::ostream& out, const Node* node){
        std::cout << "(" << node->m_coef << "x^" << node->m_exp << ") ";
        return out;
    }
public:
    Node(double coef, double exp){
        m_coef = coef;
        m_exp = exp;
        next = nullptr;
    }
};

class LinkedList {
private:
    Node* head_ptr;
    Node* tail_ptr;
    int termNumber = 0;
    friend LinkedList mergeList();
public:
    LinkedList() {
        head_ptr = nullptr;
        tail_ptr = nullptr;
    }

    void appendNode(const double coef, const double exp) {
        Node* newNode = new Node(coef, exp);
        if (head_ptr == nullptr) {
            head_ptr = newNode;
            tail_ptr = newNode;
        } else {
            tail_ptr->next = newNode;
            tail_ptr = newNode;
        }
        termNumber++;
    }

    // void removeNode(const double coef, const double exp){
    //     Node* current = head_ptr;
    //     if(current->m_coef == coef && current->m_exp == exp) {
    //         head_ptr = head_ptr->next;
    //         return;
    //     }
    //     while(current != nullptr){
    //         if(current->next->m_coef == coef && current->next->m_exp == exp){
    //             current->next = current->next->next;
    //         }
    //         current = current->next;
    //     }
    // }

    // void mergeNodes() {
    //     Node* current = head_ptr;
    //     if (current == nullptr || current->next == nullptr){
    //         return;
    //     }
    //     while(current != nullptr){
    //         Node* target = current->next;
    //         while(target != nullptr){
    //             if(target->m_exp == current->m_exp){
    //                 current->m_coef += target->m_coef;
    //             }else{
    //                 target = target->next;
    //             }
    //         }
    //         current = current->next;
    //     }
    // }

    void displayList() {
        Node* current = head_ptr;
        while (current != nullptr) {
            if(current->m_coef == 0){
                std::cout << "";
            }else if(current->next != nullptr){
                std::cout << current << "+ ";
            }else{
                std::cout << current;
            }
            current = current->next;
        }
        std::cout << std::endl;
    }

    void multiplyList(const LinkedList& list1, const LinkedList& list2){
        Node* current1 = list1.head_ptr;
        while (current1 != nullptr) {
            Node* current2 = list2.head_ptr;
            while (current2 != nullptr) {
                double newCoef = current1->m_coef * current2->m_coef;
                double newExp = current1->m_exp + current2->m_exp;
                appendNode(newCoef, newExp);
                current2 = current2->next;
            }
            current1 = current1->next;
        }
    }

};

LinkedList mergeList(const LinkedList& list){
    LinkedList result;

    result.appendNode(list.head_ptr.m_coef, list.head_ptr.m_exp);

    return result;
}


int main() {
    int m, n;

    LinkedList list_1;
    std::cout << "Enter the number of terms for list 1: ";
    std::cin >> m;
    for (int i = 0; i < m; i++) {
        double coef, exp;
        std::cout << "Enter coefficient and exponent for term " << i + 1 << ": ";
        std::cin >> coef >> exp;
        list_1.appendNode(coef, exp);
    }

    LinkedList list_2;
    std::cout << "Enter the number of terms for list 2: ";
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        double coef, exp;
        std::cout << "Enter coefficient and exponent for term " << i + 1 << ": ";
        std::cin >> coef >> exp;
        list_2.appendNode(coef, exp);
    }
    std::cout << std::endl;

    std::cout << "List 1: ";
    list_1.displayList();
    std::cout << "List 2: ";
    list_2.displayList();

    LinkedList list_3;
    list_3.multiplyList(list_1, list_2);

    std::cout << "Result of multiplication:" << std::endl;
    list_3.displayList();

    return 0;
}
/*
3
2 3
-1 2
4.2 1
5
-3 4
1.5 2
-0.8 1
0 0
-6 -1
*/