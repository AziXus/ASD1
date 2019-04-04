/*Complétez la classe générique ArrayDeque pour qu'elle passe ce codecheck.

Cette classe met en oeuvre le comportement de double-ended queue en utilisant un buffer circulaire de capacité variable. Les données sont stockées dans un std::vector que vous redimensionnerez quand c'est nécessaire. Maintenez en permanence les relations

buffer.size() == buffer.capacity()

et

this->capacity() == buffer.size()

Vous ne pouvez ajouter aucun attribut privé à la classe ni modifier les attributs et le constructeur fourni. Vous ne pouvez ajouter comme méthodes publiques que celles nécessaires pour passer les tests d'API. Vous pouvez ajouter toute méthode privée dont vous auriez besoin

Pour ce laboratoire, il n'est pas nécessaire de générer des exceptions. En cas de mauvaise utilisation, le comportement est non spécifié.

Complete the following file:

uniquement vector.at, vector.size
on double la capacité lorsque que nécessaire en créant un nouveau vect puis on swap



size DONE
capacity DONE
empty DONE

back() DONE
front()

push_back
pop_back

push_front
pop_front
*/


#ifndef ArrayDeque_hpp
#define ArrayDeque_hpp

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
    ArrayDeque(size_type capacity = 0) : debut(0), taille(0), buffer(capacity) {
    }

    size_type size() const {
        return taille;
    }

    size_type capacity() const {
        return buffer.size();
    }

    bool empty() const {
        return size() == 0;
    }

    reference back() {
        if (this->empty()) {
            throw;
        }
        return buffer[index_physique(taille - 1)];
    }

    const_reference back() const {
        if (this->empty()) {
            throw;
        }
        return buffer[index_physique(taille - 1)];
    }

    size_type index_physique(size_type i_logique) const {
        if (debut + i_logique == 0)
            return 0;
        size_type ip = (debut + i_logique) % capacity();
        if (ip >= 0)
            return ip;
        else
            return ip + capacity();
    }

    void extend() {
        //Créer un nouveau vecteur deux fois plus grand
        //Copier les valeurs dans le nouveau vecteur
        //Swap les vecteur
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
        std::swap(tmp, buffer);
    }

    void push_back(const_reference val) {
        if (taille >= this->capacity()) {
            extend();
        }
        buffer.at(index_physique(taille)) = val;
        ++taille;
    }

    void pop_back() {
        if (this->empty()) {
            //impossible de supprimer
            return;
        }
        //On ne libere pas la memoire
        --taille;
    }

    reference front() {
        if (this->empty()) {
            //pas d'elem, on throw
            throw;
        }

        return buffer.at(debut);
    }

    const_reference front() const {
        if (this->empty()) {
            //pas d'elem, on throw
            throw;
        }

        return buffer.at(debut);
    }

    void push_front(const_reference val) {
        if (taille >= capacity()) {
            extend();
        }

        debut = index_physique(capacity() - 1);
        buffer[debut] = val;
        ++taille;
    }

    void pop_front() {
        if (this->empty()) {
            //impossible de supprimer
            return;
        }
        debut = index_physique(1);
        --taille;
    }

    void shift(size_type amount) {

    }
};

#endif /* ArrayDeque_hpp */