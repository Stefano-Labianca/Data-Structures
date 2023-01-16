#ifndef _DICTIONARY_H
#define _DICTIONARY_H

#include "IDictionary.h"
#include "../LinkedList/LinkedList.h"

/**
 * Classe che rappresenta una coppia chiave-valore.
 *
 * @tparam Key: Tipo di dato della chiave
 * @tparam Value: Tipo di dato da associare alla chiave
 */
template <class Key, class Value>
class Pair : public IPair<Key, Value>
{
    private:
        Key _key; // Chiave
        Value _value; // Valore

    public:
        Pair(Key k, Value v);
        Pair(const Pair<Key, Value>& source);

        void setKey(Key key);
        Key getKey();

        void setValue(Value value);
        Value getValue();

        Pair<Key, Value>& operator=(const Pair<Key,Value>& pair);
        bool operator==(const Pair<Key,Value>& pair);

        template<class Key1, class Value1>
        friend std::ostream& operator<<(std::ostream& out, const Pair<Key1,Value1>& pair);
};

/**
 * Crea una coppia chiave-valore
 *
 * @tparam Key : Tipo della chiave
 * @tparam Value : Tipo del valore associato alla chiave
 * @param k : Chiave
 * @param v : Valore
 */
template <class Key, class Value>
Pair<Key, Value>::Pair(Key k, Value v)
{
    this->_key = k;
    this->_value = v;
}

/**
 * Costruttore di copia
 *
 * @tparam Key : Tipo della chiave
 * @tparam Value : Tipo del valore associato alla chiave
 * @param source : Associazione da copiare
 */
template <class Key, class Value>
Pair<Key, Value>::Pair(const Pair<Key, Value>& source)
{
    this->_key = source._key;
    this->_value = source._value;
}

/**
 * Imposta una chiave
 *
 * @tparam Key : Tipo della chiave
 * @tparam Value : Tipo del valore associato alla chiave
 * @param key : Chiave da aggiornare
 */
template <class Key, class Value>
void Pair<Key, Value>::setKey(Key key)
{
    this->_key = key;
}

/**
 * Restituisce la chiave
 *
 * @tparam Key : Tipo della chiave
 * @tparam Value : Tipo del valore associato alla chiave
 * @return Chiave
 */
template <class Key, class Value>
Key Pair<Key, Value>::getKey()
{
    return this->_key;
}

/**
 * Imposta un valore
 *
 * @tparam Key : Tipo della chiave
 * @tparam Value : Tipo del valore associato alla chiave
 * @param value Valore da aggiornare
 */
template <class Key, class Value>
void Pair<Key, Value>::setValue(Value value)
{
    this->_value = value;
}

/**
 * Restituisce un valore
 *
 * @tparam Key : Tipo della chiave
 * @tparam Value : Tipo del valore associato alla chiave
 * @return Valore
 */
template <class Key, class Value>
Value Pair<Key, Value>::getValue()
{
    return this->_value;
}

template <class Key, class Value>
Pair<Key, Value>& Pair<Key, Value>::operator=(const Pair<Key, Value>& pair)
{
    if (this != *pair)
    {
        this->_key = pair._key;
        this->_value = pair._value;
    }

    return *this;
}

template <class Key, class Value>
bool Pair<Key, Value>::operator==(const Pair<Key, Value>& pair)
{
    if ((pair._key == this->_key) && (pair._value == this->_value))
    {
        return true;
    }

    return false;
}

template <class Key1, class Value1>
std::ostream &operator<<(std::ostream& out, const Pair<Key1, Value1> &pair)
{

    out << "{ \"" << pair._key << "\": " << pair._value << " }";
    return out;
}


/**
 * Struttura dati che realizza il dizionario con l'utilizzo della
 * tabella hash.
 *
 * La funzione hash utilizzata e' la DJB2
 *
 * @tparam Key: Tipo di dato della chiave
 * @tparam Value: Tipo di dato del valore da associare alla chiave
 */
template <class Key, class Value>
class Dictionary : public IDictionary<Key, Value>
{
    private:
        Pair<Key, Value>** _dict; // Dizionario simulato come una tabella hash

        int _DEFAULT_DICT_SIZE = 11ULL; // Dimensioni di default del dizionario
        int _size; // Dimensioni massime del dizionario
        uint32_t _pairsAmount; // Numero di elementi nel dizionario

    private:
        uint32_t _hash(const std::string& key); // djb2 hash function
        void _resize();

    public:
        Dictionary();
        Dictionary(int size);
        ~Dictionary();

        bool isEmpty() const;
        int search(const Key& key);

        bool has(const Key& key);
        Pair<Key, Value>* get(const Key& key);

        void insert(const Key& key, const Value& value);
        void erase(const Key& key);
        void update(const Key& key, const Value& value);

        bool isSubset(Dictionary<Key, Value>& dictionary);

        LinkedList<Key>* keys();
        LinkedList<Value>* values();

        Pair<Key, Value>* operator[](Key key);

        template <class K, class V>
        friend std::ostream& operator<<(std::ostream& out, const Dictionary<K, V>& dictionary);
};

/**
 * Crea un dizionario vuoto con le dimensioni di default pari a 11
 *
 * @tparam Key : Tipo della chiave
 * @tparam Value : Tipo del valore associato alla chiave
 */
template <class Key, class Value>
Dictionary<Key, Value>::Dictionary()
{
    this->_size = this->_DEFAULT_DICT_SIZE;
    this->_pairsAmount = 0;

    this->_dict = new Pair<Key, Value>*[this->_DEFAULT_DICT_SIZE];

    for(std::size_t i = 0; i < this->_size; i++)
    {
        this->_dict[i] = nullptr;
    }
}

/**
 * Crea un dizionario con dimensioni pari a size.
 * Se size e' zero allora il dizionario avra' le dimensioni di default 11.
 *
 * @tparam Key : Tipo della chiave
 * @tparam Value : Tipo del valore associato alla chiave
 * @param size : Dimensioni del dizionario
 */
template <class Key, class Value>
Dictionary<Key, Value>::Dictionary(int size)
{
    if (size == 0)
    {
        this->_size = this->_DEFAULT_DICT_SIZE;
        this->_dict = new Pair<Key, Value>*[this->_DEFAULT_DICT_SIZE];
    }

    else
    {
        this->_size = size;
        this->_dict = new Pair<Key, Value>*[size];
    }

    this->_pairsAmount = 0;

    for(std::size_t i = 0; i < this->_size; i++)
    {
        this->_dict[i] = nullptr;
    }
}

/**
 * Distruttore
 *
 * @tparam Key : Tipo della chiave
 * @tparam Value : Tipo del valore associato alla chiave
 */
template<class Key, class Value>
Dictionary<Key, Value>::~Dictionary()
{
    for (std::size_t i = 0; i < this->_size; i++)
    {
        if (this->_dict[i])
        {
            delete this->_dict[i];
        }
    }

    delete[] this->_dict;

    this->_size = 0;
    this->_pairsAmount = 0;
}

/**
 * Restituisce true se il dizionario e' vuoto, altrimenti false.
 *
 * @tparam Key: Tipo di dato della chiave
 * @tparam Value: Tipo di dato del valore associato alla chiave
 *
 * @return True se e' vuoto, altrimenti false.
 */
template <class Key, class Value>
bool Dictionary<Key, Value>::isEmpty() const
{
    return (this->_pairsAmount == 0);
}

/**
 * Restituisce l'indice associato ad una coppia chiave-valore.
 * Se la coppia chiave-valore non esiste, restituisce -1.
 *
 * @tparam Key: Tipo di dato della chiave
 * @tparam Value: Tipo di dato del valore associato alla chiave
 *
 * @param key: Chiave da trovare l'indice
 * @return Indice della coppia chiave-valore, oppure -1.
 */
template<class Key, class Value>
int Dictionary<Key, Value>::search(const Key& key)
{
    uint32_t homeBucket = this->_hash(key) % this->_size;
    uint32_t actualBucket = homeBucket;

    do
    {
        if (this->_dict[actualBucket] == nullptr || this->_dict[actualBucket]->getKey() == key)
        {
            return (int) actualBucket;
        }

        actualBucket = (actualBucket + 1) % this->_size;

    } while (actualBucket != homeBucket);

    // Dizionario pieno, perche' non ho trovato una cella vuota e
    // non ho trovato una cella con chiave uguale al parametro key
    return -1;
}


/**
 * Restituisce true se la chiave key esiste all'interno del dizionario, altrimenti false
 *
 * @tparam Key: Tipo di dato della chiave
 * @tparam Value: Tipo di dato del valore associato alla chiave
 *
 * @param key: Chiave da cercare
 * @return True se la chiave esiste, altrimenti false
 */
template <class Key, class Value>
bool Dictionary<Key, Value>::has(const Key& key)
{
    int index = this->search(key);

    if (index > -1)
    {
        return true;
    }

    return false;
}

/**
 * Restituisce un'associazione chiave-valore, ottenendola attraverso la sua chiave
 *
 * @tparam Key: Tipo di dato della chiave
 * @tparam Value: Tipo di dato del valore associato alla chiave
 *
 * @param key: Chiave dell'associazione
 * @return Associazione chiave-valore
 */
template <class Key, class Value>
Pair<Key, Value>* Dictionary<Key, Value>::get(const Key& key)
{
    int index = this->search(key);

    if (index > -1)
    {
        return this->_dict[index];
    }

    return nullptr;
}


/**
 * Inserisce un' associazione chiave-valore all'interno del dizionario.
 * Se nel dizionario esiste key, allora viene aggiornato il valore a cui
 * e' associata
 *
 * @tparam Key: Tipo di dato della chiave
 * @tparam Value: Tipo di dato del valore associato alla chiave
 *
 * @param key: Chiave da inserire
 * @param value: Valore da associare alla chiave
 */
template <class Key, class Value>
void Dictionary<Key, Value>::insert(const Key &key, const Value &value)
{
    if (this->_pairsAmount + 1 == this->_size)
    {
        this->_resize();
    }

    int calculatedBucket = this->search(key);

    if (calculatedBucket == -1)
    {
        return;
    }

    if (this->_dict[calculatedBucket] == nullptr) // Cella vuota
    {
        this->_dict[calculatedBucket] = new Pair<Key, Value>(key, value);
        this->_pairsAmount++;

        return;
    }

   if (this->_dict[calculatedBucket]->getKey() == key) // Cella piena, sovraccarico
   {
       this->_dict[calculatedBucket]->setValue(value);
       return;
   }

    std::cout << "Dizionario pieno" << std::endl; // Tabella hash piena
    throw "Dizionario pieno";
}

/**
 * Elimina un'associazione chiave-valore dal dizionario
 *
 * @tparam Key: Tipo di dato della chiave
 * @tparam Value: Tipo di dato del valore associato alla chiave
 *
 * @param key: Chiave dell'associazione da eliminare
 */
template <class Key, class Value>
void Dictionary<Key, Value>::erase(const Key& key)
{
    int index = this->search(key);

    if (index > -1)
    {
        delete this->_dict[index];
        this->_dict[index] = nullptr;

        this->_pairsAmount--;
    }
}


/**
 * Aggiorna il valore associato alla chiave key, con un nuovo valore value.
 * Se l'associazione chiave-valore non esiste nel dizionario, allora viene creata.
 *
 * @tparam Key: Tipo di dato della chiave
 * @tparam Value: Tipo di dato del valore associato alla chiave
 *
 * @param key: Chiave a cui aggiornare il valore
 * @param value: Nuovo valore da associare alla chiave
 */
template <class Key, class Value>
void Dictionary<Key, Value>::update(const Key& key, const Value& value)
{
    this->insert(key, value);
}


/**
 * Restituisce true se dictionary e' un sottoinsieme, altrimenti false.
 * La verifica viene fatta solo sui valori e non sulle chiavi
 *
 * @tparam Key: Tipo di dato della chiave
 * @tparam Value: Tipo di dato del valore associato alla chiave
 *
 * @param dictionary: Sottoinsieme da verificare
 * @return True se sono sottoinsiemi, altrimenti false.
 */
template <class Key, class Value>
bool Dictionary<Key, Value>::isSubset(Dictionary<Key, Value>& dictionary)
{
    if (dictionary._pairsAmount > this->_pairsAmount)
    {
        return false;
    }

    LinkedList<Value>* thisV;
    LinkedList<Value>* v;

    thisV = this->values();
    v = dictionary.values();

    auto thisIt = thisV->begin();
    auto vIt = v->begin();

    while (!v->isEnd(vIt))
    {
        if (thisIt->getNodeValue() != vIt->getNodeValue())
        {
            thisV->~LinkedList();
            v->~LinkedList();

            return false;
        }

        thisIt = thisIt->getNext();
        vIt = vIt->getNext();
    }

    thisV->~LinkedList();
    v->~LinkedList();

    return true;
}



/**
 * Restituisce una lista contentente tutte le chiavi contenuti nel dizionario
 *
 * @tparam Key: Tipo di dato della chiave
 * @tparam Value: Tipo di dato del valore associato alla chiave
 *
 * @return Lista contenente tutte le chiavi nel dizionario
 */
template <class Key, class Value>
LinkedList<Key>* Dictionary<Key, Value>::keys()
{
    LinkedList<Key>* lKeys = new LinkedList<Key>();

    for (int i = 0; i < this->_size; i++)
    {
        if (this->_dict[i] != nullptr)
        {
            lKeys->append(this->_dict[i]->getKey());
        }
    }

    return lKeys;
}

/**
 * Restituisce una lista contentente tutti i valori contenuti nel dizionario
 *
 * @tparam Key: Tipo di dato della chiave
 * @tparam Value: Tipo di dato del valore associato alla chiave
 *
 * @return Lista contenente tutti i valori associati alle chiavi
 */
template <class Key, class Value>
LinkedList<Value>* Dictionary<Key, Value>::values()
{
    LinkedList<Value>* lValues = new LinkedList<Value>();

    for (int i = 0; i < this->_size; i++)
    {
        if (this->_dict[i] != nullptr)
        {
            lValues->append(this->_dict[i]->getValue());
        }
    }

    return lValues;
}


template<class Key, class Value>
Pair<Key, Value> *Dictionary<Key, Value>::operator[](Key key)
{
    return this->get(key);
}


template <class K, class V>
std::ostream& operator<<(std::ostream& out, const Dictionary<K, V>& dictionary)
{
    out << "[ " << std::endl;

    for (int i = 0; i < dictionary._size; i++)
    {
        if (dictionary._dict[i])
        {
            out << "  Index: " << i << " -> " << *(dictionary._dict[i]) << std::endl;
        }
    }

    out << "]" << std::endl;


    return out;
}


/**
 * Implementazione della funzione hash DJB2
 *
 * @param key: Chiave a cui applicare l'hash
 * @return Hashcode a 32-bits
 */
template <class Key, class Value>
uint32_t Dictionary<Key, Value>::_hash(const std::string& key) {
    const unsigned char *chr = (const unsigned char *)key.c_str();
    uint32_t hash = 5381;
    uint32_t c = *chr++;

    while (c)
    {
        hash = ((hash << 5) + hash) ^ c;
        c = *chr++;
    }

    return hash;
}


/**
 * Aumenta di un fattore doppio le dimensioni del dizionario
 *
 * @tparam Key: Tipo di dato della chiave
 * @tparam Value: Tipo di dato del valore associato alla chiave
 */
template <class Key, class Value>
void Dictionary<Key, Value>::_resize()
{
    Pair<Key, Value>** newDict = new Pair<Key, Value>*[this->_size * 2];

    for (int i = 0; i < this->_size * 2; i++)
    {
        newDict[i] = nullptr;
    }

    for (int i = 0; i < this->_size; i++)
    {
        newDict[i] = this->_dict[i];
        this->_dict[i] = nullptr;
    }

    delete[] this->_dict;
    this->_dict = nullptr;

    this->_dict = newDict;
    this->_size *= 2;
}


#endif // _DICTIONARY_H
