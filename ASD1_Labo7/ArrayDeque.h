/**
\file ArrayDeque.h
\author Stéphane Teixeira Carvalho, Diego Villagrasa, Robin Müller
\date 13 Mai 2019
Labo 7 : Création d'une classe générique ArrayDeque pour qu'elle passe le codecheck.
Cette classe met en oeuvre le comportement d'une double-ended queue en utilisant 
un buffer circulaire de capacité variable. 
Les données sont stockées dans un tableau buffer alloué dynamiquement. 
L'allocation et la construction sont séparées, de sorte que la capacité non utilisée n'est pas construite.
Destruction et libération de la mémoire le sont également.
Toutes les méthodes et constructeurs doivent offrir des garanties fortes.
*/
#ifndef ArrayDeque_h
#define ArrayDeque_h

#include <algorithm>
#include <stdexcept>

template < class T >
class ArrayDeque
{
public:
    using value_type = T;
    using reference = T&;
    using const_reference = const T&;
    using rvalue_reference = T&&;
    using pointer = T*;

    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;

private:
    pointer buffer;
    size_type capacite;
    size_type debut;
    size_type taille;

    /**
    * Calcul l'adresse physique d'une variable dans l'ArrayDeque grâce à une adresse logique
    * @param i_logique indique l'index logigue de la variable
    * @return un size_t donnant l'index physique de la variable
    */
    size_type index_physique(size_type i_logique) const {
        if (debut + i_logique == 0)
            return 0;
        //calcul de l'index physique de la donnée dans l'ArrayDeque
        size_type ip = (debut + i_logique) % capacite;
        if (ip >= 0)
            return ip;
        else
            return ip + capacite;
    }

    /**
     * Permet de doubler la capacité de l'ArrayDeque
     */
    void extend() {
        size_type newCapacity = capacite == 0 ? 1 : capacite * 2;
        //Création d'un ArrayDeque temporaire pour la garantie forte
        ArrayDeque tmp(newCapacity);

        for (size_type i = 0; i < taille; ++i) {
            new(tmp.buffer + i) value_type(std::move(buffer[index_physique(i)]));
            //Chaque nouvel élément fait augmenter la taille du tableau
            ++tmp.taille;
        }

        std::swap(tmp.buffer, buffer);
        std::swap(tmp.capacite, capacite);
        std::swap(tmp.debut, debut);
    }

public:
     /**
     * Constructeur spécifique de la classe ArrayDeque
     * @param cap size_t indiquant la capacité de l'ArrayDeque
     */
    ArrayDeque(size_type cap = 0) : debut(0), taille(0), capacite(cap)
    {
        //Allocation dynamique de la mémoire en fonction de la capacite
        buffer = capacite != 0 ?
                 (pointer) ::operator new(capacite * sizeof(value_type))
                               : nullptr;
    }
    
    /**
     * Constructeur par copie de la classe ArrayDeque
     * @param rhs ArrayDeque de laquelle il faut copier les valeurs
     */
    ArrayDeque(const ArrayDeque& rhs) : ArrayDeque(rhs.capacite) {
        debut = rhs.debut;
        for (size_type i = 0; i < rhs.taille; ++i) {
            new(buffer + index_physique(i)) value_type(rhs.at(i));
            ++taille;
        }
    }
    
    /**
     * Surcharge de l'opérateur d'affectation pour permettre d'affecter un ArrayDeque
     * @param rhs ArrayDeque du quel prendre les valeurs
     * @return l'ArrayDeque avec les valeurs de rhs
     */
    ArrayDeque& operator=(const ArrayDeque& rhs) {
        //Appel du constructeur par copie
        ArrayDeque tmp = rhs;

        std::swap(buffer, tmp.buffer);

        return *this;
    }
    /**
     * Destructeur de l'ArrayDeque
     */
    ~ArrayDeque() {
        for (size_type i = 0; i < taille; ++i) {
            buffer[index_physique(i)].~value_type();
        }

        ::operator delete(buffer);
    }

    /**
     * Retourne la taille de l'ArrayDeque
     * @return size_t donnant la taille de l'ArrayDeque
     */
    size_type size() const {
        return taille;
    }

    /**
     * Retourne la capacité de l'ArrayDeque
     * @return size_t indiquant la capacité de l'ArrayDeque
     */
    size_type capacity() const {
        return capacite;
    }

    /**
     * Permet de vérifier si l'ArrayDeque est vide
     * @return vrai si vide, faux sinon
     */
    bool empty() const {
        return taille == 0;
    }

    /**
     * Permet de retourner le dernier élément de l'ArrayDeque
     * @return référence de type T sur le dernier élément
     */
    reference back() {
        //ArrayDeque vide, comportement indéterminé
        if (this->empty())
            throw;

        return buffer[index_physique(taille - 1)];
    }

    /**
     * Fonction back surchargée pour pouvoir l'utiliser avec une ArrayDeque constante
     * @return référence constante de type T du dernier élément
     */
    const_reference back() const {
        //ArrayDeque vide, comportement indéterminé
        if (this->empty()) {
            throw;
        }

        return buffer[index_physique(taille - 1)];
    }
    
    /**
     * Retourne la valeur contenue à une position donnée
     * @param n size_t indiquant la position de la valeur
     * @return référence donnant la valeur en position n
     */
    reference at(size_type n) {
        //ArrayDeque vide, comportement indéterminé
        if (this->empty())
            throw;

        return buffer[index_physique(n)];
    }

    /**
     * Retourne la valeur contenue à une position donnée
     * Une surcharge de la fonction a du être faite pour l'utiliser sur une ArrayDeque constante 
     * @param n size_t indiquant la position de la valeur
     * @return référence donnant la valeur en position n
     */
    const_reference at(size_type n) const {
        //ArrayDeque vide, comportement indéterminé
        if (this->empty()) {
            throw;
        }

        return buffer[index_physique(n)];
    }

    /**
     * Renvoie la première valeur de l'ArrayDeque
     * @return référence de type T de la première valeur
     */
    reference front() {
        //ArrayDeque vide, comportement indéterminé
        if (this->empty())
            throw;

        return buffer[debut];
    }

    /**
     * Surcharge de front pour pouvoir renvoyer la première valeur pour une ArrayDeque constante
     * @return référence constante de la première valeur
     */
    const_reference front() const {
        //ArrayDeque vide, comportement indéterminé
        if (this->empty())
            throw;

        return buffer[debut];
    }

    /**
     * Ajoute une valeur en fin de l'ArrayDeque
     * @param val reference constante de la valeur a ajouter a l'ArrayDeque
     */
    void push_back(const_reference val) {
        //Vérification que la taille n'est pas déjà plus grande ou égal à la capacité
        //dans ce cas on l'augmente, sinon nous aurons un dépassement
        if (taille >= capacite)
            extend();

        new(buffer + index_physique(taille)) value_type(val);
        ++taille;
    }
    
    /**
     * Ajoute une valeur en fin de l'ArrayDeque
     * Surcharge pour l'utilisation de valeur avec des doubles références(rvalue)
     * @param val valeur a ajouter a l'ArrayDeque
     */
    void push_back(rvalue_reference val) {
        //Vérification que la taille n'est pas déjà plus grande ou égal à la capacité
        //dans ce cas on l'augmente, sinon nous aurons un dépassement
        if (taille >= capacite)
            extend();

        new(buffer + index_physique(taille)) value_type(std::move(val));
        ++taille;
    }

    /**
     * Supprime la dernière valeur de l'ArrayDeque
     */
    void pop_back() {
        //Si l'ArrayDeque est vide impossible de supprimer
        if (this->empty())
            throw;

        buffer[index_physique(taille - 1)].~value_type();
        --taille;
    }

    /**
    * Permet d'ajouter une valeur en début de l'ArrayDeque
    * @param val valeur a ajouter à l'ArrayDeque
    */
    void push_front(const_reference val) {
        //Vérification que la taille n'est pas déjà plus grande ou égal à la capacité
        //dans ce cas on l'augmente, sinon nous aurons un dépassement
        if (taille >= capacite)
            extend();

        //Ameliorer ?
        new(buffer + index_physique(capacite - 1)) value_type(val);
        debut = index_physique(capacite - 1);
        ++taille;
    }

    /**
    * Permet d'ajouter une valeur en début de l'ArrayDeque
    * Surcharge pour l'utilisation de valeur avec des doubles références(rvalue)
    * @param val valeur a ajouter a l'ArrayDeque
    */
    void push_front(rvalue_reference val) {
        //Vérification que la taille n'est pas déjà plus grande ou égal à la capacité
        //dans ce cas on l'augmente, sinon nous aurons un dépassement
        if (taille >= capacite)
            extend();

        new(buffer + index_physique(capacite - 1)) value_type(std::move(val));
        debut = index_physique(capacite - 1);
        ++taille;
    }

    /**
     * Supprime la première valeur de l'ArrayDeque
     */
    void pop_front() {
        //impossible de supprimer
        if (this->empty())
            throw;

        buffer[debut].~value_type();
        debut = index_physique(1);
        --taille;
    }

};

#endif /* ArrayDeque_hpp */