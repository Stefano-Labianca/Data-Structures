## Soluzioni delle tracce di ASD

### util_n_tree

#### Traccia

> Realizzare e completare in C++ la seguente classe che implementa metodi operanti su un albero n-ario. 
> Prevedere una funzione main che contenga una procedura di inserimento automatico e successivamente il
> test dei metodi implementati.

```c++
template<class _value_type>
class util_n_tree{
    /* Restituisce il numero di foglie presenti nell’albero n-ario T */
    int n_leaf(const tree< _value_type > &T);
    /* Restituisce il numero di nodi in T di livello k */
    int n_level(const tree< _value_type > &T, int k);
};
```

#### Soluzione

- **File**: **_Tree.h_**
- `n_leaf -> getLeafAmount(Iterator root)`;
- `n_level -> nodesPerLevel(uint32_t level)`;


### even_father

#### Traccia

> Realizzare in C++ una funzione che conti il numero di nodi, in un albero n-ario 
> di interi, che hanno come padre un nodo con valore pari.

```c++
int even_father(const Tree<T>& tree, typename Tree<T>::Iterator root);
```

#### Soluzione

- **File**: **_even_father.h_**


### eo_strings

#### Traccia

> Una struttura dati acquisisce stringhe che vanno inserite in due liste secondo il seguente schema: le stringhe
> con un numero pari di caratteri vengono memorizzate in una lista, le restanti nell’altra lista. La struttura
> dati mette a disposizione una serie di metodi che permettono di conoscere e cambiare il suo stato.
>
> Realizzare in C++ la seguente classe che implementa la struttura appena descritta.

```c++
class eo_strings {
    public:
        // inserisce inserisce una stringa nella corrispondente lista
        void inserisci(string s);
        // rimuove la stringa dalla corrispondente lista
        void rimuovi(string s);
        // rimuove le stringhe di lunghezza pari che iniziano con il carattere c
        void rimuovi(char c);
        // restituisce il numero di stringhe di lunghezza pari
        int freq_pari();
        // visualizza le stringhe di lunghezza dispari ordinate per lunghezza
        void visualizza_dispari();
    
    private:
        List<string> pari;
        List<string> dispari;
};
```

#### Soluzione

- **File**: **_eo_strings.h_**

### zero_one_binary_tree

#### Traccia

> Realizzare e completare in C++ la seguente classe che implementa metodi operanti su un albero binario
> con nodi aventi etichetta di tipo intero. In particolare, ogni nodo dell’albero avrà come etichetta o il valore
> 0 o il valore 1. 
> 
> Prevedere una funzione main che contenga una procedura di inserimento automatico e
> successivamente il test dei metodi implementati.

```c++
template<class _value_type>
class zero_one_binary_tree {
    /** 
    * Stabilisce se l’albero rispetta le propieta' di un albero zero-one, ovvero:
    *   1) la radice ha valore 0;
    *   2) ogni nodo 0, ha come figli due nodi 1;
    *   3) ogni nodo 1, ha come figli due nodi 0.
    */
    bool is_zero_one(const Bintree< _value_type > &B);
    
    /* Restituisce il numero di nodi 0 dell’abero */
    int zero_nodes(const Bintree< _value_type > &B);
};
```

#### Soluzione

- **File**: **_zero_one_binary_tree.h_**


### BST

#### Traccia

> Si ricorda che un albero binario di ricerca (BST) e' una semplice albero binario che rispetta le seguenti
> proprieta':
> - il sottoalbero sinistro di ogni nodo n contiene solo nodi con valori minori del valore del nodo n;
> - il sottoalbero destro di ogni nodo n contiene solo nodi con valori maggiori del valore del nodo n;
> - il sottolabero sinistro e quello destro di ogni nodo sono alberi binari di ricerca.
> Inoltre non sono previsti nodi con valori duplicati.
> 
> Realizzare e completare in C++ la seguente classe che implementa metodi operanti su un generico albero
> binario con nodi aventi etichetta di tipo intero, per stabilire se soddisfa le propriet`a di un BST. Prevedere una
> funzione main che contenga una procedura di inserimento automatico e successivamente il test dei metodi
> implementati per un BST e per un albero binario che non sia un BST.

```c++
class BST {
    public:
        /* stabilisce se l’albero binario rispetta i vincoli di un BST */
        bool is_bst();
        /* inserisce in modo ordinato nel BST il valore passato */
        void insert(int);
        /* verifica se un elemento appartiene al BST */
        bool search(int);
        
    private:
        Bintree<int> T;
}
```

#### Soluzione

- **File**: **_bst.h_**
