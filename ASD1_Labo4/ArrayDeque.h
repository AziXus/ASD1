/**
\file ArrayDeque.h
\author Stéphane Teixeira Carvalho, Diego Villagrasa, Robin Müller
\date 15 avril 2019
Labo 4 : Création d'une classe générique ArrayDeque pour qu'elle passe le codecheck.
Cette classe met en oeuvre le comportement de double-ended queue en utilisant 
un buffer circulaire de capacité variable. 
Les données sont stockées dans un std::vector.
*/

#ifndef ArrayDeque_h
#define ArrayDeque_h

#include <vector>

template<class T>
class ArrayDeque {
public:
    using value_type = T;
    using reference = T&;
    using const_reference = const T&;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;

private:
    std::vector<value_type> buffer;
    size_type debut;
    size_type taille;

public:
    /**
     * Constructeur spécifique de la classe ArrayDeque
     * @param capacity size_t indiquant la capacité de l'ArrayDeque car buffer.size() == buffer.capacity()
     */
    ArrayDeque(size_type capacity = 0) : buffer(capacity), debut(0), taille(0) {}

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
        //Comme dans la donnée on sait que buffer.size() == buffer.capacity() on retourne buffer.size()
        return buffer.size();
    }

    /**
     * Permet de vérifier si l'ArrayDeque est vide
     * @return vrai si vide, faux sinon
     */
    bool empty() const {
        return size() == 0;
    }

    /**
     * Permet de retourner le dernier élément de l'ArrayDeque
     * @return référence de type T sur le dernier élément
     */
    reference back() {
        //ArrayDeque vide, comportement indéterminé
        if (this->empty()) {
            throw;
        }
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
     * Ajoute une valeur en fin de l'ArrayDeque
     * @param val valeur a ajouter a l'ArrayDeque
     */
    void push_back(const_reference val) {
        //Vérification que la taille n'est pas déjà plus grande ou égal à la capacité
        //dans ce cas on l'augmente, sinon nous aurons un dépassement
        if (taille >= this->capacity()) {
            extend();
        }
        buffer.at(index_physique(taille)) = val;
        ++taille;
    }

    /**
     * Supprime la dernière valeur de l'ArrayDeque
     */
    void pop_back() {
        //Si l'ArrayDeque est vide impossible de supprimer
        if (this->empty()) {
            throw;
        }
        //On ne libère pas la memoire, on descend juste la taille
        --taille;
    }

    /**
     * Renvoie la première valeur de l'ArrayDeque
     * @return référence de type T de la première valeur
     */
    reference front() {
        //ArrayDeque vide, comportement indéterminé
        if (this->empty()) {
            throw;
        }
        return buffer.at(debut);
    }

    /**
     * Surcharge pour pouvoir renvoyer la première valeur pour une ArrayDeque constante
     * @return référence constante de la première valeur
     */
    const_reference front() const {
        //ArrayDeque vide, comportement indéterminé
        if (this->empty()) {
            throw;
        }
        return buffer.at(debut);
    }
    
    /**
    * Permet d'ajouter une valeur en début de l'ArrayDeque
    * @param val valeur a ajouter a l'ArrayDeque
    */
    void push_front(const_reference val) {
        //Vérification que la taille n'est pas déjà plus grande ou égal à la capacité
        //dans ce cas on l'augmente, sinon nous aurons un dépassement
        if (taille >= capacity()) {
            extend();
        }
        debut = index_physique(capacity() - 1);
        buffer[debut] = val;
        ++taille;
    }
    
    /**
     * Supprime la première valeur de l'ArrayDeque
     */
    void pop_front() {
        if (this->empty()) {
            //impossible de supprimer
            throw;
        }
        debut = index_physique(1);
        --taille;
    }
    
private:
     /**
     * Calcul l'adresse physique d'une variable dans l'ArrayDeque grâce à une adresse logique
     * @param i_logique indique l'index logigue de la variable
     * @return un size_t donnant l'index physique de la variable
     */
    size_type index_physique(size_type i_logique) const {
        if (debut + i_logique == 0)
            return 0;
        //calcul de l'index physique de la donnée dans l'ArrayDeque
        size_type ip = (debut + i_logique) % capacity();
        if (ip >= 0)
            return ip;
        else
            return ip + capacity();
    }
    
    /**
     * Permet de doubler la capacité de l'ArrayDeque
     */
    void extend() {
        //Créer un nouveau vecteur deux fois plus grand
        size_type capacite;
        if (capacity() == 0)
            capacite = 1;
        else
            capacite = capacity() * 2;

        //Déplace les valeurs dans l'ordre, en commençant depuis 0
        std::vector<value_type> tmp(capacite);
        for (size_type i = 0 ; i < capacity() ; ++i) {
            tmp[i] = std::move(buffer[index_physique(i)]);
        }
        debut = 0;
        //Swap les vecteur car buffer est vide à cause de move
        std::swap(tmp, buffer);
    }
};

#endif /* ArrayDeque_h */
