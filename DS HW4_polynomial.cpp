#include <iostream>
#include <vector>
#include <map>
#include <chrono>

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
public:
    LinkedList() {
        head_ptr = nullptr;
        tail_ptr = nullptr;
    }

    ~LinkedList() {
        Node* current = head_ptr;
        while (current != nullptr) {
            Node* nextNode = current->next;
            delete current;
            current = nextNode;
        }
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
    }

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
            if(current1->m_coef == 0){
                current1 = current1->next;
                continue;
            }
            Node* current2 = list2.head_ptr;
            while (current2 != nullptr) {
                if(current2->m_coef == 0){
                    current2 = current2->next;
                    continue;
                }
                double newCoef = current1->m_coef * current2->m_coef;
                double newExp = current1->m_exp + current2->m_exp;

                appendNode(newCoef, newExp);
                current2 = current2->next;
            }
            current1 = current1->next;
        }
    }
    void mergeTerms() {
        Node* current1 = head_ptr;
        while (current1 != nullptr) {
            Node* current2 = current1->next;
            Node* prev2 = current1;
            while (current2 != nullptr) {
                if (current1->m_exp == current2->m_exp) {
                    current1->m_coef += current2->m_coef;
                    current2->m_coef = 0;
                }
                prev2 = current2;
                current2 = current2->next;
            }
            current1 = current1->next;
        }

        // Remove nodes with a coefficient of 0
        Node* current = head_ptr;
        Node* prev = nullptr;
        while (current != nullptr) {
            if (current->m_coef == 0) {
                if (prev == nullptr) {
                    head_ptr = current->next;
                } else {
                    prev->next = current->next;
                }
                delete current;
                current = prev->next;
            } else {
                prev = current;
                current = current->next;
            }
        }

        Node* now = head_ptr;
        while (now != nullptr) {
            Node* next = now->next;
            while (next != nullptr) {
                if (now->m_exp < next->m_exp) {
                    // Swap nodes
                    double temp_coef = now->m_coef;
                    double temp_exp = now->m_exp;
                    now->m_coef = next->m_coef;
                    now->m_exp = next->m_exp;
                    next->m_coef = temp_coef;
                    next->m_exp = temp_exp;
                }
                next = next->next;
            }
            now = now->next;
        }
    }
};



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
    list_1.mergeTerms();

    LinkedList list_2;
    std::cout << "Enter the number of terms for list 2: ";
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        double coef, exp;
        std::cout << "Enter coefficient and exponent for term " << i + 1 << ": ";
        std::cin >> coef >> exp;
        list_2.appendNode(coef, exp);
    }
    list_2.mergeTerms();

    std::cout << std::endl;

    LinkedList list_3;

    auto start_time = std::chrono::steady_clock::now();
    list_3.multiplyList(list_1, list_2);
    list_3.mergeTerms();
    auto end_time = std::chrono::steady_clock::now();

    std::chrono::duration<double> t = end_time - start_time;
    double duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(t).count();

    std::cout << "List 1:" << std::endl;
    list_1.displayList();
    std::cout << "List 2:" << std::endl;
    list_2.displayList();
    std::cout << "List 3:" << std::endl;
    list_3.displayList();

    std::cout << "t = " << 1000 * t.count() << std::endl;
    // system("pause");
    return 0;
}