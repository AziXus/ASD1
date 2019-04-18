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
#include <type_traits>
#include <stdexcept>

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

        //Effectue une copie complete d'une Node
        void deepNodeCopy(Node* n){
            if(n == nullptr)
               return;
            deepNodeCopy(n->nxt);

            //Workaround pour PUSH une rvalue
            value_type tmp = n->val; //Copie la valeur
            push(std::move(tmp)); //Move la valeur pour passer en rvalue
        }

    public:
        StackList() {
            topNode = nullptr;
        }

        StackList(const StackList<value_type>& rhs) {
                topNode = nullptr;
                Node* currentNode = rhs.topNode->nxt;
                StackList<value_type> temp;
                temp.topNode = new Node{nullptr, rhs.topNode->val};
                Node* currentTopNode = temp.topNode;
                while(currentNode != nullptr) {
                    Node* node = new(std::nothrow) Node{nullptr, currentNode->val};
                    currentTopNode->nxt = node;

                    currentNode = currentNode->nxt;
                    currentTopNode = currentTopNode->nxt;
                }
                topNode = temp.topNode;
                temp.topNode =nullptr;
            //deepNodeCopy(rhs.topNode);
        }

        ~StackList() {
            while(topNode != nullptr) {
                Node* tmp = topNode->nxt;
                delete topNode;
                topNode = tmp;
            }
        }

        bool empty() const {
            return topNode == nullptr;
        }

        void push(value_type&& val) {
//            try {
                Node* node = new(std::nothrow) Node {topNode, val};
                if (node != nullptr)
                    topNode = node;
//            } catch(...) {
//                std::cout << "catch" << std::endl;
//            }

        }


        void pop() {
            if (empty())
                throw StackEmptyException();

            Node* tmp = topNode->nxt;
            delete topNode;
            topNode = tmp;
        }

        reference& top() {
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
            try{
                Node* oldNode = topNode;
                Node* currentNode = rhs.topNode->nxt;
                StackList<value_type> temp(rhs);
                /*temp.topNode = new Node{nullptr, rhs.topNode->val};
                Node* currentTopNode = temp.topNode;
                while(currentNode != nullptr) {
                    delete currentTopNode->nxt;

                    Node* node = new(std::nothrow) Node{nullptr, currentNode->val};
                    currentTopNode->nxt = node;

                    currentNode = currentNode->nxt;
                    currentTopNode = currentTopNode->nxt;
                }*/
                topNode = temp.topNode;
                temp.topNode = nullptr; 

            //Si tout a fonctionner, on vide la pile originale
            currentNode = oldNode;
            while(currentNode != nullptr) {
                Node* tmp = currentNode->nxt;
                delete currentNode;
                currentNode = tmp;
            }  
            temp.~StackList();
            return *this;
            }
            catch(...){
                
                return *this;
                throw;
            };
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