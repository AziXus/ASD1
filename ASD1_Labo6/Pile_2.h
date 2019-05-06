/**
\file Pile.h
\author Stéphane Teixeira Carvalho, Diego Villagrasa, Robin Müller
\date 06 mai 2019
Labo 6 : Création d'une classe générique Pile pour qu'elle passe le codecheck.
Cette classe met en oeuvre le comportement d'une stack (pile) en utilisant le concept d'allocation dynamique.
L'allocation est effectuée avec ::operator new tandis que la construction utilise le new (ptr) ou ptr est un pointeur vers un emplacement mémoire déjà réservé.
*/
#ifndef Pile_hpp
#define Pile_hpp

#include <ostream>

// Forward declarations
template <typename T> class Pile;
template <typename T> std::ostream& operator<<( std::ostream& os,
                                                const Pile<T>& p);

// Type Pile
template <typename T>
class Pile {
    friend std::ostream& operator<< <>( std::ostream& os,
                                        const Pile<T>& p);

public:
    using value_type = T;
    using pointer = value_type*;
    using reference = value_type&;
    using const_reference = const value_type&;

private:
    pointer donnees;
    size_t taille;
    const size_t CAPACITE;

public:
    /**
     * Constructeur spécifique de la classe Pile n'indiquant que la capacité
     * @param _capacite size_t indiquant la capacite de la pile
     */
    Pile(size_t _capacite)
            : taille(0), CAPACITE(_capacite)
    {
        //allocation en mémoire de la place que va prendre la pile
        donnees = (pointer)::operator new(CAPACITE * sizeof(value_type));
    }
            
    /**
     * Destructeur de la classe Pile
     */
    ~Pile()
    {
        //destruction des valeurs contenues dans la pile
        for (unsigned i = 0 ; i < taille; ++i) {
            donnees[i].~value_type();
        }
        //libère la mémoire utilisée par la pile
        ::operator delete(donnees);
    }
    
    /**
     * Constucteur par copie de la classe Pile
     * @param other Pile allant être copié
     */
    Pile(const Pile& other)
            : taille(other.taille), CAPACITE(other.CAPACITE)
    {
        //Allocation de la place en mémoire que va prendre la pile
        donnees = (pointer)::operator new(CAPACITE * sizeof(value_type));
        for(unsigned i = 0; i < taille; ++i) {
            //on crée les objets de type value_type avec les valeurs de other
            new(donnees + i) value_type(other.donnees[i]);
        }
    }

    /**
     * Permet d'ajouter une nouvelle valeur à la pile
     * @param v valeur de type value_type à ajouter
     */
    void empiler(const value_type& v)
    {
        //créer un nouvel objet de type value_type en mémoire selon la taille
        new(donnees + taille) value_type(v);
        ++taille;
    }

    /**
     * Enlève la valeur au sommet de la pile. Fait appel au destructeur de value_type
     */
    void depiler()
    {
        donnees[taille - 1].~value_type();
        --taille;
    }

    /**
     * Permet de donner la valeur du sommet de la pile
     * @return const_reference étant la valeur au sommet de la pile
     */
    const_reference sommet() const
    {
        return donnees[taille - 1];
    }

};

// ne pas modifier
template <typename T>
std::ostream& operator<<( std::ostream& os,
                          const Pile<T>& p)
{
    os << "Pile(" << p.taille << "/" << p.CAPACITE << "): ";
    size_t i = p.taille;
    while(i > 0)
        os << p.donnees[--i] << " ";
    return os;
}

#endif /* Pile_hpp */