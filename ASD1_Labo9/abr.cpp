/**
 \file abr.cpp
 \author Stéphane Teixeira Carvalho, Diego Villagrasa, Robin Müller
 \date 29 Mai 2019
 Labo 9 : Mettre en place les fonctions dans une classe BinarySearchTree pour passer le codecheck 2.
 */

//
//  Binary Search Tree
//
//  Copyright (c) 2017 Olivier Cuisenaire. All rights reserved.
//

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <queue>
#include <cassert>
#include <stdexcept>

using namespace std;

template < typename T >
class BinarySearchTree {
public:
  
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;

private:
  /**
   *  @brief Noeud de l'arbre.
   *
   * contient une cle et les liens vers les sous-arbres droit et gauche.
   */
  struct Node {
    const value_type key; // clé non modifiable
    Node* right;          // sous arbre avec des cles plus grandes
    Node* left;           // sous arbre avec des cles plus petites
    size_t nbElements;    // nombre de noeuds dans le sous arbre dont
                          // ce noeud est la racine
    
    Node(const_reference key)  // seul constructeur disponible. key est obligatoire
    : key(key), right(nullptr), left(nullptr), nbElements(1)
    {
      cout << "(C" << key << ") ";
    }
    ~Node()               // destructeur
    {
      cout << "(D" << key << ") ";
    }
    Node() = delete;             // pas de construction par défaut
    Node(const Node&) = delete;  // pas de construction par copie
    Node(Node&&) = delete;       // pas de construction par déplacement
  };
  
  /**
   *  @brief  Racine de l'arbre. nullptr si l'arbre est vide
   */
  Node* _root;
  
public:
  /**
   *  @brief Constructeur par défaut. Construit un arbre vide
   */
  BinarySearchTree() : _root(nullptr) {}

private:
  /**
   * Copie la node et sous-nodes vers une autre node.
   * @param newNode Nouvelle Node à créer
   * @param srcNode Node et sous-nodes à copier
   */
   void copyBinarySearchTree(Node*& newNode, Node*& srcNode) {
      if (srcNode == nullptr)
        return;

      newNode = new Node(srcNode->key);
      newNode->nbElements = srcNode->nbElements;

      copyBinarySearchTree(newNode->left, srcNode->left);
      copyBinarySearchTree(newNode->right, srcNode->right);
   }

public:
  /**
   *  @brief Constucteur de copie.
   *
   *  @param other le BinarySearchTree à copier
   *
   */
  BinarySearchTree( BinarySearchTree& other ) : BinarySearchTree() {
      copyBinarySearchTree(_root, other._root);
  }
  
  /**
   *  @brief Opérateur d'affectation par copie.
   *
   *  @param other le BinarySearchTree à copier
   *
   */
  BinarySearchTree& operator= ( const BinarySearchTree& other ) {
    BinarySearchTree tmp(const_cast<BinarySearchTree&>(other));

    this->swap(tmp);
    return *this;
  }
  
  /**
   *  @brief Echange le contenu avec un autre BST
   *
   *  @param other le BST avec lequel on echange le contenu
   *
   */
  void swap(BinarySearchTree& other ) noexcept {
    if (other._root == _root)
      return;

    Node* tmp = other._root;
    other._root = this->_root;
    this->_root = tmp;
  }
  
  /**
   *  @brief constructeur de copie par déplacement
   *
   *  @param other le BST dont on vole le contenu
   *
   */
  BinarySearchTree( BinarySearchTree&& other ) noexcept {
    _root = nullptr;
    swap(other);
  }
  
  /**
   *  @brief Opérateur d'affectation par déplacement.
   *
   *  @param other le BST dont on vole le contenu
   *
   */
  BinarySearchTree& operator= ( BinarySearchTree&& other ) noexcept {
    this->swap(other);

    return *this;
  }
  
  //
  // @brief Destructeur
  //
  // Ne pas modifier mais écrire la fonction
  // récursive privée deleteSubTree(Node*)
  //
  ~BinarySearchTree() {
    deleteSubTree( _root );
  }
  
private:
  //
  // @brief Fonction détruisant (delete) un sous arbre
  //
  // @param r la racine du sous arbre à détruire.
  //          peut éventuellement valoir nullpt
  //
  static void deleteSubTree(Node* r) noexcept {
      if (r == nullptr)
          return;

      deleteSubTree(r->left);
      deleteSubTree(r->right);

      delete r;
  }

public:
  //
  // @brief Insertion d'une cle dans l'arbre
  //
  // @param key la clé à insérer.
  //
  // Ne pas modifier mais écrire la fonction
  // récursive privée insert(Node*&,const_reference)
  //
  void insert( const_reference key) {
    insert(_root,key);
  }
  
private:
  //
  // @brief Insertion d'une cle dans un sous-arbre
  //
  // @param r la racine du sous-arbre dans lequel
  //          insérer la cle.
  // @param key la clé à insérer.
  //  
  // @remark en moyenne, O(log(n))
  //         au pire, O(n) si l’arbre est dégénéré
  //
  // @return vrai si la cle est inseree. faux si elle etait deja presente.
  //
  // Si la cle est deja presente, cette fonction ne fait rien.
  // x peut éventuellement valoir nullptr en entrée.
  // la fonction peut modifier x, reçu par référence, si nécessaire
  //
  static bool insert(Node*& r, const_reference key) {
    //Si la racine est null on est arrivé enfin de l'arbre et on créer la feuille
    if(r == nullptr)
    {
      r = new Node(key);
      return true;
    }
    //Si la clé à ajouter est plus petite que la clé de la racine on va l'ajouter à la branche gauche
    else if(key < r->key)
    {
      //On lance l'insertion de la clé à gauche de la racine
      if(insert(r->left, key)){
        //Si la clé a été ajouté on incrémente le nombre d'élément de la racine
       r->nbElements++;
       return true;
      }
    }
    //Si la clé à ajouter est plus grande que la clé de la racine on va l'ajouter à la branche droite
    else if(key > r->key)
    {
      //On lance l'insertion de la clé à droite de la racine
      if(insert(r->right, key)){
          //Si la clé a été ajouté on incrémente le nombre d'élément de la racine
         r->nbElements++;
         return true;
      }
    }
    //L'élément n'a pas été ajouté ce qui veut dire qu'il est déjà dans l'arbre
    return false;
  }
  
public:
  //
  // @brief Recherche d'une cle.
  //
  // @param key la cle a rechercher
  //
  // @return vrai si la cle trouvee, faux sinon.
  //
  // Ne pas modifier mais écrire la fonction
  // récursive privée contains(Node*,const_reference)
  //
  bool contains( const_reference key ) const noexcept {
    return contains(_root,key);
  }
  
private:
  //
  // @brief Recherche d'une cle dans un sous-arbre
  //
  // @param key la cle a rechercher
  // @param r   la racine du sous-arbre
  //  
  // @remark en moyenne, O(log(n))
  //         au pire, O(n) si l’arbre est dégénéré
  //
  // @return vrai si la cle trouvee, faux sinon.
  //
  static bool contains(Node* r, const_reference key) noexcept {
    //Si la racine est null cela signife que la clé est introuvable
    if(r == nullptr)
      return false;
    //Si la clé est plus petite que la clé de la racine on va continuer le parcours dans la branche gauche
    else if(key < r->key){
      if(!contains(r->left, key))
         //Si la valeur n'a pas été trouvée on retourne false
         return false;
    }
    else if(key > r->key){
      //Si la clé est plus grande que la clé de la racine on va continuer le parcours dans la branche droite
      if(!contains(r->right, key))
         return false;
    }
    //Si la fonction contains n'est entrée dans aucunes des conditions cela signifie que la valeur à été trouvée
    return true;
  }

private:
    //
    // @brief Recherche de la cle minimale.
    //
    // @return une const reference a la cle minimale
    Node* minElement() const {
        return minElement(_root);
    }

   //
  // @brief Recherche de l'élément minimale.
  //
  // @return Pointeur sur l'élément
  //
   static Node* minElement(Node* r){
      if(r->left == nullptr)
         return r;
      else
         return minElement(r->left);
   }

public:
  //
  // @brief Recherche de la cle minimale.
  //
  // @return une const reference a la cle minimale
  const_reference min() const {
    return minElement()->key;
  }


  //
  // @brief Supprime le plus petit element de l'arbre.
  //
  // @exception std::logic_error si necessaire
  //
  // vous pouvez mettre en oeuvre de manière iterative ou recursive a choix
  //
  void deleteMin() {
    deleteMin(_root);
  }

private:
  //
  // @brief Supprime le plus petit element de l'arbre.
  //
  // @exception std::logic_error si necessaire
   static Node* deleteMin(Node* r){
      if(r == nullptr)
         throw logic_error("Arbre Vide");
      else if(r->left == nullptr){
         Node* tmp = r->right;
         delete r;
         r = nullptr;
         return tmp;
      }
      r->left = deleteMin(r->left);
      r->nbElements--;
      return r;
   }


public:
  
  //
  // @brief Supprime l'element de cle key de l'arbre.
  //
  // @param key l'element a supprimer
  //
  // si l'element n'est pas present, la fonction ne modifie pas
  // l'arbre mais retourne false. Si l'element est present, elle
  // retourne vrai
  //
  // Ne pas modifier mais écrire la fonction
  // récursive privée deleteElement(Node*&,const_reference)
  //
  bool deleteElement( const_reference key) noexcept {
    return deleteElement( _root, key );
  }
  
private:
  //
  // @brief Supprime l'element de cle key du sous arbre.
  //
  // @param r la racine du sous arbre
  // @param key l'element a supprimer
  //
  // si l'element n'est pas present, la fonction ne modifie pas
  // l'arbre mais retourne false. Si l'element est present, elle
  // retourne vrai
  //
  static bool deleteElement( Node*& r, const_reference key) noexcept {
      Node* el = deleteEl(r, key);
      //printf("%d", el->key);
      return el != nullptr;
  }

  // @brief Fonction recursive qui supprime l'element de cle key du sous arbre.
  //
  // @param r la racine du sous arbre
  // @param key l'element a supprimer
  //
  static Node* deleteEl( Node*& r, const_reference key) noexcept {
   if(r == nullptr)

      return r;
   if(!contains(r, key))
      return nullptr;
   if(key < r->key){
      r->left = deleteEl(r->left, key);
      r->nbElements--;
      if(r->left == nullptr)
         return nullptr;
   }
   else if(key > r->key){
      r->right = deleteEl(r->right, key);
      r->nbElements--;
      if(r->right == nullptr)
         return nullptr;
   }
   
   else{//Elément trouvé
      r->nbElements--;
      if(r->right == nullptr){
         delete r;
         return r->left;
      }
      else if(r->left == nullptr){
         delete r;
         return r->right;
      }
      else{ //Suppression de Hibbard
         Node* m = minElement(r->right);
         value_type tmpR = r->key;
         reference a = const_cast <reference> (r->key);
         reference b = const_cast <reference> (m->key);
         a = b;
         b = tmpR;
         deleteMin(r->right);
      }
   }
   return r;
  }

  
  
public:
  //
  // @brief taille de l'arbre
  //
  // @return le nombre d'elements de l'arbre
  //
  size_t size() const noexcept {
    return _root->nbElements;
  }
  
  //
  // @brief cle en position n
  //
  // @return une reference a la cle en position n par ordre croissant des
  // elements
  //
  // @exception std::logic_error si nécessaire
  //  
  // @remark
  //
  // ajoutez le code de gestion des exceptions, puis mettez en oeuvre
  // la fonction recursive nth_element(Node*, n)
  //
  const_reference nth_element(size_t n) const {
    if(_root != nullptr){
        return nth_element(_root, n);
    }
    return -1;
  }
  
private:
/**
 * Fonction permettant de trouver la valeur du noeud n de l'arbre. Les valeurs sont trouvées dans l'ordre croissant.
 * @param r la racine du sous arbre 
 * @param nodesVisited size_t en référence permettant de savoir le nombre de node qui ont été visité
 * @param n la position n du node désiré
 * @return le noeud voulu ou nullptr si le n était trop grand
 */
 static Node* findNodeN(Node* r, size_t& nodesVisited, size_t n) {
    if(r->left) {
        Node* temp = findNodeN(r->left, nodesVisited, n);
        if(temp)
            return temp;
    }
    if(nodesVisited == n)
        return r;
    ++nodesVisited;
    if(r->right){
        Node* temp = findNodeN(r->right, nodesVisited, n);
        if(temp)
            return temp;
    }
    return nullptr;
  }
  
  //
  // @brief cle en position n dans un sous arbre
  //
  // @param r la racine du sous arbre. ne peut pas etre nullptr
  // @param n la position n
  //
  // @return une reference a la cle en position n par ordre croissant des
  // elements
  //
  static const_reference nth_element(Node* r, size_t n) noexcept {
    assert(r != nullptr);
    size_t nodesVisited = 0;
    Node* node = findNodeN(r, nodesVisited, n);
    if(node)
        return node->key;
    return -1;
  }
  
public:
  //
  // @brief position d'une cle dans l'ordre croissant des elements de l'arbre
  //
  // @param key la cle dont on cherche le rang
  //
  // @return la position entre 0 et size()-1, size_t(-1) si la cle est absente
  //
  // Ne pas modifier mais écrire la fonction
  // récursive privée rank(Node*,const_reference)
  //
  size_t rank(const_reference key) const noexcept {
    return rank(_root,key);
  }
  
private:
  //
  // @brief position d'une cle dans l'ordre croissant des elements du sous-arbre
  //
  // @param key la cle dont on cherche le rang
  // @param r la racine du sous arbre
  //
  // @return la position entre 0 et size()-1, size_t(-1) si la cle est absente
  //
  static size_t rank(Node* r, const_reference key) noexcept {
      if(r == nullptr)
         return -1;
      if(key < r->key)
         return rank(r->left, key);
      if(key > r->key){
         size_t rankNext = rank(r->right, key);
         return (rankNext == -1 ? -1 : (rankNext + (r->left == nullptr ? 0 : r->left->nbElements) + 1));
      }
      return r->left == nullptr ? 0 : r->left->nbElements;
  }
  
public:
  //
  // @brief linearise l'arbre
  //
  // transforme l'arbre en une liste simplement chainee composee des memes
  // noeuds que precedemment, mais dont les pointeurs left sont tous egaux
  // a nullptr. Cette liste doit toujours respecter les conditions d'un
  // arbre binaire de recherche
  //
  // Ne pas modifier cette fonction qui sert essentiellement a tester la
  // fonction recursive linearize(Node*, Node*&, size_t&) utilisée par
  // la methode publique arborize
  //
  void linearize() noexcept {
    size_t cnt = 0;
    Node* list = nullptr;
    linearize(_root,list,cnt);
    _root = list;
  }
  
private:
  //
  // @brief linearise une sous arbre tree en une liste
  //
  // @param tree pointe vers la racine de l'arbre a lineariser
  // @param list reference a la tete de la liste a creer. sera modifiee
  //             par la fonction pour que list pointe vers le plus petit
  //             element de tree
  // @param cnt  calcule au fure et a mesure le nombre d'elements de la liste
  //             cree. l'effet de la fonction doit etre d'ajouter le nombre
  //             d'elements du sous-arbre de racine tree. Cependant, vous
  //             avez uniquement le droit d'utiliser l'opérateur ++.
  //
  static void linearize(Node* tree, Node*& list, size_t& cnt) noexcept {
       /* si R=nullptr alors
       retourner 0
       N <- linéariser(R.droit, L)
       R.droit = L
       L = R
       N <- N + linéariser(R.gauche, L)
       R.gauche = null */
       if(tree == nullptr){ 
           return;
       }
       else{
          linearize(tree->right, list, cnt);
          tree->right = list;
          list = tree;
          list->nbElements = ++cnt;
          linearize(tree->left, list, cnt);
          tree->left = NULL;
       }
  }
  
public:
  //
  // @brief equilibre l'arbre
  //
  // applique l'algorithme d'equilibrage de l'arbre par linearisation et
  // arborisation
  //
  // Ne pas modifier cette fonction.
  //
  void balance() noexcept {
    size_t cnt = 0;
    Node* list = nullptr;
    linearize(_root,list,cnt);
    arborize(_root,list,cnt);
  }
  
private:
    
   static Node* arb(Node* tree, Node*& list, size_t cnt){
      if(cnt == 0)
         return list;
      std::cout << cnt << std::endl;
      Node* RG = arb(tree, list, (cnt - 1)/2);
      tree = list;
      tree->left = RG;
      list = list->right;
      tree->right = arb(tree, list, cnt/2);
      return tree;
   }
   
  //
  // @brief arborise les cnt premiers elements d'une liste en un arbre
  //
  // @param tree reference dans laquelle il faut ecrire la racine de l'arbre
  //             arborise par la fonction
  // @param list IN - reference a la tete de la liste a parcourir. La liste
  //                  est composee de Node dont le pointer left est nullptr
  //             OUT - debut de la suite de la liste dont on a utilise cnt
  //                   elements
  // @param cnt  nombre d'elements de la liste que l'on doit utiliser pour
  //             arboriser le sous arbre
  //
  static void arborize(Node*& tree, Node*& list, size_t cnt) noexcept {      
      tree = arb(tree, list, cnt);
  }
  
  //
  // @brief Fonction permettant le parcours pré-ordonné de l'arbre de manière recursive 
  //
  // @param R la racine du sous arbre
  // @param f une fonction capable d'être appelée en recevant une cle
  //          en parametre. Pour le noeud n courrant, l'appel sera
  //          f(n->key);
  //
  // @remark O(n) en moyenne et au pire car on passe sur chaque lien du noeud à l'aller et au retour donc au plus 3 * n
  
  template < typename Fn >
  void parcoursPre(Node* R, Fn f){
      if(R != nullptr){
          f(R->key);
          parcoursPre(R->left, f);
          parcoursPre(R->right, f);
      }
  }

  //
  // @brief Fonction permettant le parcours symétrique de l'arbre de manière recursive 
  //
  // @param R la racine du sous arbre
  // @param f une fonction capable d'être appelée en recevant une cle
  //          en parametre. Pour le noeud n courrant, l'appel sera
  //          f(n->key);
  //
  // @remark O(n) en moyenne et au pire car on passe sur chaque lien du noeud à l'aller et au retour donc au plus 3 * n
  template < typename Fn >
  void parcoursSym(Node* R, Fn f){
      if(R != nullptr){
          parcoursSym(R->left, f);
          f(R->key);
          parcoursSym(R->right, f);
      }
  }
  
  //
  // @brief Fonction permettant le parcours post-ordonné de l'arbre de manière recursive 
  //
  // @param R la racine du sous arbre
  // @param f une fonction capable d'être appelée en recevant une cle
  //          en parametre. Pour le noeud n courrant, l'appel sera
  //          f(n->key);
  //
  // @remark O(n) en moyenne et au pire car on passe sur chaque lien du noeud à l'aller et au retour donc au plus 3 * n
  template < typename Fn >
  void parcoursPost(Node* R, Fn f){
      if(R != nullptr){
          parcoursPost(R->left, f);
          parcoursPost(R->right, f);
          f(R->key);
      }
  }
  
public:
  //
  // @brief Parcours pre-ordonne de l'arbre
  //
  // @param f une fonction capable d'être appelée en recevant une cle
  //          en parametre. Pour le noeud n courrant, l'appel sera
  //          f(n->key);
  //
  template < typename Fn >
  void visitPre (Fn f) {
      parcoursPre(_root, f);
  }
  
  //
  // @brief Parcours symétrique de l'arbre
  //
  // @param f une fonction capable d'Ãªtre appelée en recevant une cle
  //          en parametre. Pour le noeud n courrant, l'appel sera
  //          f(n->key);
  //
  template < typename Fn >
  void visitSym (Fn f) {
    parcoursSym(_root, f);
  }
  
  //
  // @brief Parcours post-ordonne de l'arbre
  //
  // @param f une fonction capable d'être appelée en recevant une cle
  //          en parametre. Pour le noeud n courrant, l'appel sera
  //          f(n->key);
  //
  template < typename Fn >
  void visitPost (Fn f) {
    parcoursPost(_root, f);
  }
  
  
  //
  // Les fonctions suivantes sont fournies pour permettre de tester votre classe
  // Merci de ne rien modifier au dela de cette ligne
  //
  void display() const {
    stringstream ss1, ss2, ss3;
    displayKeys(ss1);
    displayKeys(ss3);
    displayCounts(ss2);
    string l1, l2;
    
    size_t W = 11;
    while( getline(ss3,l1) )
      if (l1.length() > W) W = l1.length();

    displayKeys(ss1);
    
    cout << "\n";
    cout << "+-" << left << setfill('-') << setw(W) << "-" << "+-" << setw(W) << "-" << setfill(' ') << "+" << endl;
    cout << "| "<< left << setw(W) << "key" << "| " << setw(W) << "nbElements" << "|" << endl;
    cout << "+-" << left << setfill('-') << setw(W) << "-" << "+-" << setw(W) << "-" << setfill(' ') << "+" << endl;
    while( getline(ss1,l1) and getline(ss2, l2) ) {
      cout << "| "<< left << setw(W) << l1 << "| " << setw(W) << l2 << "|" << endl;
    }
    cout << "+-" << left << setfill('-') << setw(W) << "-" << "+-" << setw(W) << "-" << setfill(' ') << "+" << endl;

  }
  
  void displayKeys(ostream& os = cout) const {
    display([](Node* n) -> const_reference { return n->key; }, os);
  }
  
  void displayCounts(ostream& os = cout) const {
    display([](Node* n) -> size_t { return n->nbElements; }, os);
  }
  
  //
  // utilise un parcours de l'arbre en largeur avec
  // un noeud sentinelle newLevel qui traque les
  // changements de niveaux
  //
  template <typename Fn>
  void display (Fn func, ostream& os = cout ) const {
    Node* newLevel = (Node*) -1;
    // addresse non nulle dont on est sur qu'elle ne contient pas
    // vraiment un Node. Utilisée comme sentinelle.
    
    queue<Node*> Q;
    Q.push(_root);
    Q.push(newLevel);
    
    while(!Q.empty()) {
      Node* cur = Q.front();
      Q.pop();
      
      if(cur == newLevel) {
        os << endl;
        if(!Q.empty())
          Q.push(newLevel);
      } else if(cur == nullptr) {
        os << "- ";
      } else {
        os << func(cur) << " ";
        Q.push(cur->left);
        Q.push(cur->right);
      }
    }
  }
};
