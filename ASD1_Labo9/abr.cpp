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
  BinarySearchTree() : _root(nullptr)
  {
    /* ... */
  }
  
  /**
   *  @brief Constucteur de copie.
   *
   *  @param other le BinarySearchTree à copier
   *
   */
  BinarySearchTree( BinarySearchTree& other ) {
    /* ... */
  }
  
  /**
   *  @brief Opérateur d'affectation par copie.
   *
   *  @param other le BinarySearchTree à copier
   *
   */
  BinarySearchTree& operator= ( const BinarySearchTree& other ) {
    /* ... */
    return *this;
  }
  
  /**
   *  @brief Echange le contenu avec un autre BST
   *
   *  @param other le BST avec lequel on echange le contenu
   *
   */
  void swap(BinarySearchTree& other ) noexcept {
    /* ... */
  }
  
  /**
   *  @brief constructeur de copie par déplacement
   *
   *  @param other le BST dont on vole le contenu
   *
   */
  BinarySearchTree( BinarySearchTree&& other ) noexcept {
    /* ... */
  }
  
  /**
   *  @brief Opérateur d'affectation par déplacement.
   *
   *  @param other le BST dont on vole le contenu
   *
   */
  BinarySearchTree& operator= ( BinarySearchTree&& other ) noexcept {
    /* ... */
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
  //          peut éventuellement valoir nullptr
  //
  static void deleteSubTree(Node* r) noexcept {
    /* ... */
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
  // @return vrai si la cle est inseree. faux si elle etait deja presente.
  //
  // Si la cle est deja presente, cette fonction ne fait rien.
  // x peut éventuellement valoir nullptr en entrée.
  // la fonction peut modifier x, reçu par référence, si nécessaire
  //
  static bool insert(Node*& r, const_reference key) {
    /*
    si R est nul, alors
    R ← créer une feuille contenant E
    sinon si E.clé < R.clé, alors
    insérer( E, R.gauche )
    sinon, si E.clé > R.clé , alors
    insérer( E, R.droit )
    sinon // R.clé vaut E.clé
    l’élément est déjà présent dans l’arbre
    fin si
    */
    if(r == nullptr)
    {
      r = new Node(key);
      return true;
    }
    else if(key < (*r).key)
    {
      if(insert((*r).left, key)){
       (*r).nbElements++;
       return true;
      }
    }
    else if(key > (*r).key)
    {
      if(insert((*r).right, key)){
         (*r).nbElements++;
      //(*r).nbElements = (*r).left->nbElements + (*r).right->nbElements;
         return true;
      }
    }
    
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
  // @return vrai si la cle trouvee, faux sinon.
  //
  static bool contains(Node* r, const_reference key) noexcept {
    /*
    si R est nul, alors
   signaler que C est introuvable
   sinon si C < R.clé, alors
   chercher( C, R.gauche )
   sinon, si C > R.clé , alors
   chercher( C, R.droit )
   sinon // R.clé vaut C
   retourner R
   fin si
    */
    if(r == nullptr)
      return false;
    else if(key < (*r).key){
      if(!contains((*r).left, key))
         return false;
    }
    else if(key > (*r).key){
      if(!contains((*r).right, key))
         return false;
    }
    return true;
  }
  
public:
  //
  // @brief Recherche de la cle minimale.
  //
  // @return une const reference a la cle minimale
  //
  // @exception std::logic_error si necessaire
  //
  // vous pouvez mettre en oeuvre de manière iterative ou recursive a choix
  //
  const_reference min() const {
    /* ... */
  }
  
  //
  // @brief Supprime le plus petit element de l'arbre.
  //
  // @exception std::logic_error si necessaire
  //
  // vous pouvez mettre en oeuvre de manière iterative ou recursive a choix
  //
  void deleteMin() {
    /* ... */
  }
  
  
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
    /* ... */
    return false;
  }
  
public:
  //
  // @brief taille de l'arbre
  //
  // @return le nombre d'elements de l'arbre
  //
  size_t size() const noexcept {
    /* ... */
    return 0;
  }
  
  //
  // @brief cle en position n
  //
  // @return une reference a la cle en position n par ordre croissant des
  // elements
  //
  // @exception std::logic_error si nécessaire
  //
  // ajoutez le code de gestion des exceptions, puis mettez en oeuvre
  // la fonction recursive nth_element(Node*, n)
  //
  const_reference nth_element(size_t n) const {
    /* ... */
    return nth_element(_root,n);
  }
  
private:
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
    /* ... */
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
    /* ... */
    return -1;
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
       if(tree == nullptr){}
       else{
          linearize((*tree).right, list, ++cnt);
          (*tree).right = list;
          list = tree;
          linearize((*tree).left, list, ++cnt);
          (*tree).left = NULL;
          cnt++;
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
    /*
    si R n’est pas un arbre vide, alors
    traiter R
    parcours pré-ordonné( R.gauche )
    parcours pré-ordonné( R.droit )
    fin si
    */
    /*auto node = (*this)._root;
    while(node != nullptr){
      f(node->key);
      //parcourt tout les éléments de gauche de l'arbre
      if(node->left != nullptr){
         auto nodeL = node->left;
         while(nodeL != nullptr){
            f(nodeL->key);
            node  = nodeL;
            nodeL = nodeL->left;
         }
         if(node->right != nullptr)
         {
            node = node->right;
         }
      }
      else{
         if(node->right != nullptr){
            auto nodeL = node->left;
            while(nodeL != nullptr){
               f(nodeL->key);
               node  = nodeL;
               nodeL = nodeL->left;
            }
            if(node->right != nullptr)
            {
               node = node->right;
            }
         }
      }
    }
      auto nodeR = node->right;*/
    //}
    /*node = (*this)._root;
    while(node != nullptr){
      node = node->right;
      f(node->key);
    }*/
    /*if(f() != null)
    {
       fn((*this)._root->key);
       visipre();
    }*/
    
    queue<Node*> Q;
    Q.push(_root);
    Node* cur = Q.front();
    //Q.push(newLevel);
    
    while(cur->left != nullptr){
        Q.push(cur->left);
        cur = cur->left;
    }
    
    while(!Q.empty()) {
      cur = Q.front();
      Q.pop();
      f(cur->key);
      auto nodeR = cur->right;
      while(nodeR != nullptr){
        Q.push(nodeR);
        nodeR = nodeR->left;
      }
    }

      /*if(cur == newLevel) {
        std::cout << "Fist" << std::endl;
        if(!Q.empty())
          Q.push(newLevel);
      } else if(cur == nullptr) {
        std::cout << "- ";
        else if(cur->right != nullptr){
        std::cout << "R";
        f(cur->right->key);
        Q.push(cur->right);
      }
      } else if(){
        std::cout << "Left ->" << cur->key << std::endl;
        //f(cur->left->key);
       
      } 
      else{
         std::cout << "Pop" << std::endl;
         Q.pop();
      }
      cur = Q.back();
      std::cout << "back ->" << cur->key << std::endl;
    }*/
    
  }
  
  //
  // @brief Parcours symétrique de l'arbre
  //
  // @param f une fonction capable d'être appelée en recevant une cle
  //          en parametre. Pour le noeud n courrant, l'appel sera
  //          f(n->key);
  //
  template < typename Fn >
  void visitSym (Fn f) {
    /* ... */
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
    /* ... */
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