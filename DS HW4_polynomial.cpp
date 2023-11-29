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

    // void multiplyList(const LinkedList& list1, const LinkedList& list2){
    //     Node* current1 = list1.head_ptr;
    //     while (current1 != nullptr) {
    //         Node* current2 = list2.head_ptr;
    //         while (current2 != nullptr) {
    //             double newCoef = current1->m_coef * current2->m_coef;
    //             double newExp = current1->m_exp + current2->m_exp;
    //             appendNode(newCoef, newExp);
    //             current2 = current2->next;
    //         }
    //         current1 = current1->next;
    //     }
    // }
    std::map<double, double> multiplyList(const LinkedList& list1, const LinkedList& list2){
        std::map<double, double> result;
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
                result[newExp] += newCoef;
                current2 = current2->next;
            }
            current1 = current1->next;
        }
        return result;
    }

    void mapToLinkedList(const std::map<double, double>& map) {
        LinkedList result;
        for (auto it = map.rbegin(); it != map.rend(); ++it) {
            result.appendNode(it->second, it->first);
        }
        result.displayList();
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

    LinkedList list_3;

    auto start_time = std::chrono::steady_clock::now();
    
    std::map<double, double> map = list_3.multiplyList(list_1, list_2);
    list_3.mapToLinkedList(map);
    
    auto end_time = std::chrono::steady_clock::now();

    std::chrono::duration<double> t = end_time - start_time;
    double duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(t).count();

    list_3.displayList();

    std::cout << "t = " << 1000 * t.count() << std::endl;
    system("pause");
    return 0;
}