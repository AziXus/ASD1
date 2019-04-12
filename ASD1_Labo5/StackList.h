//
//  StackList.h
//

//Pile mise en oeuvre au moyen d'une liste simplement chainée
//Compléter le code suivant sans ajouter d'attributs privés et sans utiliser le type T autrement que via les types value_type, reference et const_reference
//
//Vous devez mettre en oeuvre le constructeur par défaut, le destructeur, les méthodes push, pop, top et empty, ainsi que le constructeur de copie et l'opérateur d'affectation par copie. Quand c'est pertinent, il faut lever l'exception StackEmptyException
//
//Cette classe doit offrir garanties faible et forte pour toutes ses fonctionalités

#ifndef StackList_h
#define StackList_h

#include <utility>
#include <algorithm>

namespace asd1 {

    class StackEmptyException { };

    template<typename T>
    class StackList {
    public:
        using value_type = T;
        using reference = T&;
        using const_reference = const T&;

    private:
        struct Node {
            Node* nxt;
            value_type val;
        };
        Node* topNode;

    public:
        StackList() {
            topNode = nullptr;
        }

        ~StackList() {
            while(topNode != nullptr)
                delete topNode;
        }

        bool empty() const {
            return topNode == nullptr;
        }

        void push(value_type val) {
            topNode = new Node{topNode, val};
        }

        void pop() {
            if (empty())
                throw StackEmptyException();

            Node* tmp = topNode->nxt;
            delete topNode;
            topNode = tmp;
        }

        reference top() {
            if (empty())
                throw StackEmptyException();

            return topNode->val;
        }

        const_reference& top() const {
            if (empty())
                throw StackEmptyException();

            return topNode->val;
        }

        StackList& operator=(const StackList& rhs) {
            Node* currentNode = rhs.topNode;
            while(this->topNode != nullptr)
                this->pop();
            while(currentNode != nullptr)
            {
                *this->topNode->nxt = currentNode->nxt;
                //this->push(currentNode->val);
                currentNode = currentNode->nxt;
            }
            /*Node* currentNode = *this.topNode;
            while(currentNode != nullptr)
            {
                this->push(currentNode->val);
                currentNode = currentNode->nxt;
            }*/
            /*StackList<int> temp;
            Node* currentNode = *this.topNode;
            while(this->topNode != nullptr)
            {
                temp.topNode = currentNode;
                currentNode = currentNode->nxt;
            }*/
            
               
            return *this;
        }





// A compléter sans ajouter d'attributs privés et sans utiliser le type T
// autrement que via les types value_type, reference et const_reference
//
// vous devez mettre en oeuvre le constructeur par défaut, le destructeur,
// les méthodes push, pop, top et empty, ainsi que le constructeur de copie
// et l'opérateur d'affectation par copie. Quand c'est pertinent, il faut
// lever l'exception StackEmptyException
//
// Cette classe doit offrir garanties faible et forte pour toutes ses
// fonctionalités
    };
}

#endif /* StackList_h */