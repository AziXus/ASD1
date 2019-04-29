/**
\file ArrayDeque.h
\author Stéphane Teixeira Carvalho, Diego Villagrasa, Robin Müller
\date 29 avril 2019
Labo 5 : Création d'une classe générique StackList pour qu'elle passe le codecheck.
Cette classe met en oeuvre le comportement d'une stack (pile) en utilisant une liste simplement chainé.
*/

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

    public:
        /**
         * Constructeur sans paramètre de la classe StackList créant une StackList vide
         */
        StackList() {
            topNode = nullptr;
        }

        /**
         * Constructeur par copie de la classe StackList
         * @param rhs StackList à copier
         */
        StackList(const StackList<value_type>& rhs) : StackList() {
            if (!rhs.empty()) {
                StackList<value_type> temp; //StackList temporaire pour permettre une garantie forte
                temp.topNode = new Node{nullptr, rhs.topNode->val};

                Node* currentNode = rhs.topNode->nxt;
                Node* currentTopNode = temp.topNode;
                //Parcours la StackList RHS et ajoute les éléments à this
                while(currentNode != nullptr) {
                    currentTopNode->nxt = new Node{nullptr, currentNode->val};;

                    currentNode = currentNode->nxt;
                    currentTopNode = currentTopNode->nxt;
                }

                //On echange les deux topNodes afin de créer le lien de this et supprimer le lien de temp
                std::swap(topNode, temp.topNode);
            }
        }

        /**
         * Surcharge de l'opérateur d'affectation par copie pour la classe StackList
         * @param rhs StackList à copier
         * @return la nouvelle StackList copiée
         */
        StackList& operator=(const StackList& rhs) {
            //Appel du constructeur par copie
            StackList<value_type> temp = rhs;

            //On echange les deux topNodes afin de supprimer les anciennes nodes lors de la destruction de temp
            std::swap(topNode, temp.topNode);

            return *this;
        }

        /**
         * Destructeur de la classe StackList libérant la mémoire des nodes.
         */
        ~StackList() {
            while(topNode != nullptr) {
                Node* tmp = topNode->nxt;
                delete topNode;
                topNode = tmp;
            }
        }

        /**
         * Indique si la StackList est vide
         * @return true si vide, false sinon
         */
        bool empty() const {
            return topNode == nullptr;
        }

        /**
         * Ajoute une nouvelle valeur à la StackList
         * @param val const_reference étant la valeur à ajouter
         */
        void push(const_reference val) {
            Node* node = new(std::nothrow) Node {topNode, val};
            if (node != nullptr)
                topNode = node;
        }

        /**
         * Retire le dernier élément de la StackList
         */
        void pop() {
            if (empty())
                throw StackEmptyException();

            Node* tmp = topNode->nxt;
            delete topNode;
            topNode = tmp;
        }

        /**
         * Obtient le dernier élément de la StackList
         * @return reference vers le dernier élément
         */
        reference top() {
            if (empty())
                throw StackEmptyException();

            return topNode->val;
        }

        /**
         * Obtient le dernier élément de la StackList
         * Surcharge de la fonction pour une StackList constante
         * @return const_reference vers le dernier élément
         */
        const_reference top() const {
            if (empty())
                throw StackEmptyException();

            return topNode->val;
        }
    };
}

#endif /* StackList_h */