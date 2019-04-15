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
     * @param capacity size_t indiquant la capacité du tableau car buffer.size() == buffer.capacity()
     */
    ArrayDeque(size_type capacity = 0) : buffer(capacity), debut(0), taille(0) {}

    /**
     * Retourne la taille du tableau
     * @return size_t donnant la taille du tableau
     */
    size_type size() const {
        return taille;
    }

    /**
     * Retourne la capacité du tableau
     * @return size_t indiquant la capacité du tableau
     */
    size_type capacity() const {
        //Comme dans la donnée on sait que buffer.size() == buffer.capacity() on retourne buffer.size()
        return buffer.size();
    }

    /**
     * Permet de vérifier si le tableau est vide
     * @return vrai si vide, faux sinon
     */
    bool empty() const {
        return size() == 0;
    }

    /**
     * Permet de retourner le dernier élément du tableau
     * @return référence de type T sur le dernier élément
     */
    reference back() {
        //tableau vide, comportement indéterminé
        if (this->empty()) {
            throw;
        }
        return buffer[index_physique(taille - 1)];
    }

    /**
     * Fonction back surchargée pour pouvoir l'utiliser avec un tableau constant
     * @return référence constante de type T du dernier élément
     */
    const_reference back() const {
        //tableau vide, comportement indéterminé
        if (this->empty()) {
            throw;
        }
        return buffer[index_physique(taille - 1)];
    }

    /**
     * Ajoute une valeur en fin de tableau
     * @param val valeur à ajouter au tableau
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
     * Supprime la dernière valeur du tableau
     */
    void pop_back() {
        //Si le tableau est vide impossible de supprimer
        if (this->empty()) {
            throw;
        }
        //On ne libère pas la memoire, on descend juste la taille
        --taille;
    }

    /**
     * Renvoie la première valeur du tableau
     * @return référence de type T de la première valeur
     */
    reference front() {
        //tableau vide, comportement indéterminé
        if (this->empty()) {
            throw;
        }
        return buffer.at(debut);
    }

    /**
     * Surcharge pour pouvoir renvoyer la première valeur pour un tableau constant
     * @return référence constante de la première valeur
     */
    const_reference front() const {
        //tableau vide, comportement indéterminé
        if (this->empty()) {
            throw;
        }
        return buffer.at(debut);
    }
    
    /**
    * Permet d'ajouter une valeur en début de tableau
    * @param val valeur à ajouter au tableau
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
     * Supprime la première valeur du tableau
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
     * Calcul l'adresse physique d'une variable dans un tableau grâce à une adresse logique
     * @param i_logique indique l'index logigue de la variable
     * @return un size_t donnant l'index physique de la variable
     */
    size_type index_physique(size_type i_logique) const {
        if (debut + i_logique == 0)
            return 0;
        //calcul de l'index physique de la donnée dans le tableau
        size_type ip = (debut + i_logique) % capacity();
        if (ip >= 0)
            return ip;
        else
            return ip + capacity();
    }
    
    /**
     * Permet de doubler la capacité du tableau 
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