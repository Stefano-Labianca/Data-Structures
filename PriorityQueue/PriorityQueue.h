#ifndef _PRIORITYQUEUE_H
#define _PRIORITYQUEUE_H

#include "IPriorityQueue.h"

/**
 * Classe che realizza la coda con priorità
 *
 * @tparam T : Tipo di dato contenuto nella coda con priorita'
 */
template <class T>
class PriorityQueue : public IPriorityQueue<T, std::size_t>
{
    public:
        typedef typename IPriorityQueue<T, std::size_t>::Type Type;
        typedef typename IPriorityQueue<T, std::size_t>::Iterator Iterator;

    private:
        std::size_t _DEFAULT_SIZE = 16ULL; // Lunghezza massima di default della coda

        std::size_t _length; // Lunghezza massima della coda
        std::size_t _currentSize; // Indica il numero di elementi presenti nella coda
        Type* _heap; // Array heap

    private:
        void _swap(std::size_t childIndex, std::size_t parentIndex);
        void _fixUp();
        void _fixDown(std::size_t startPos, std::size_t endPos);

    public:
        PriorityQueue();
        PriorityQueue(size_t size);
        ~PriorityQueue();

        bool isEmpty() const;
        Type min() const;

        void insert(const Type& value);
        void deleteMin();
        void clear();


        template <class V>
        friend std::ostream& operator<<(std::ostream&, const PriorityQueue<V>& pQUeue);
};


/**
 * Crea una coda con priorita' con dimensioni pari a quelle di default (16)
 *
 * @tparam T : Tipo di dato contenuto nella coda con priorita'
 */
template <class T>
PriorityQueue<T>::PriorityQueue()
{
    this->_heap = new Type[this->_DEFAULT_SIZE];
    this->_length = this->_DEFAULT_SIZE;
    this->_currentSize = 0;
}

/**
 * Crea una coda con priorita' vuota con dimensioni custom pari a size.
 * Se size e' uguale a zero, allora la coda con priorita' avra' dimensioni di default (16)
 *
 * @tparam T : Tipo di dato contenuto nella coda con priorita'
 * @param size : Dimensioni custom della coda con priorita'
 */
template <class T>
PriorityQueue<T>::PriorityQueue(size_t size)
{
    if (size == 0)
    {
        this->_heap = new Type[this->_DEFAULT_SIZE];
        this->_length = this->_DEFAULT_SIZE;
    }
    
    else
    {
        this->_heap = new Type[size];
        this->_length = size;
    }

    this->_currentSize = 0;
}

/**
 * Distuttore
 *
 * @tparam T : Tipo di dato contenuto nella coda con priorita'
 */
template<class T>
PriorityQueue<T>::~PriorityQueue()
{
    delete[] this->_heap;
    this->_heap = nullptr;

    this->_length = 0;
    this->_currentSize = 0;
}

/**
 * Restituisce true se la coda con priorita' e' vuota, altrimenti false.
 *
 * @tparam T: Tipo di dato contenuto nella coda con priorita'
 * @return True se e' vuota, altrimenti false
 */
template<class T>
bool PriorityQueue<T>::isEmpty() const
{
    return (this->_currentSize == 0);
}

/**
 * Restituisce il valore minimo della coda
 *
 * @tparam T: Tipo di dato contenuto nella coda con priorita'
 * @return Valore minimo della coda
 */
template<class T>
typename PriorityQueue<T>::Type PriorityQueue<T>::min() const
{
    if (!this->isEmpty())
    {
        return this->_heap[0];
    }
}

/**
 * Inserisce un nuovo elemento.
 *
 * @tparam T: Tipo di dato contenuto nella coda con priorita'
 * @param value: Valore da inserire
 */
template <class T>
void PriorityQueue<T>::insert(const Type& value)
{
    if (this->_currentSize < this->_length)
    {
        this->_heap[this->_currentSize] = value;
        this->_currentSize++;
        this->_fixUp();
    }
}


/**
 * Elimina l'elemento con valore minimo, cioe' quello con priorita' piu' alta.
 *
 * @tparam T: Tipo di dato contenuto nella coda con priorita'
 */
template <class T>
void PriorityQueue<T>::deleteMin()
{
    /** *     Albero binario  B :                         Albero binario B dopo la rimozione di 3
     *                  3                     0                      10..5
     *                /    \                                       /     \
     *               5       9                1                  6        9
     *             /   \    /  \                               /   \      /    \
     *            6     8  13   12            2              10    8     13    12
     *          /  \   /                                    /  \
     *        11  18   10                     3            11  18
     *
     *   1   2   3    4    5    6    7    8    9   10             1    2    3    4    5    6    7     8     9   10
     *   3   5   9    6    8   13    12   11  18   10             5    6    9    10   8    13   12    11    19
    * */

    if (this->isEmpty())
    {
        return;
    }

    this->_heap[0] = this->_heap[this->_currentSize - 1];
    this->_currentSize--;

    this->_fixDown(1, this->_currentSize);
}


template <class T>
void PriorityQueue<T>::clear()
{
    while (!this->isEmpty())
    {
        this->deleteMin();
    }
}


template<class V>
std::ostream& operator<<(std::ostream& out, const PriorityQueue<V>& pQueue) {
    out << "[";

    for(std::size_t i = 0; i < pQueue._currentSize; i++)
    {
        if (i + 1 == pQueue._currentSize)
        {
            out << pQueue._heap[i];
        }

        else
        {
            out << pQueue._heap[i] << ", ";
        }

    }

    out << "]";

    return out;
}



/**
 * Effettua uno o piu' scambi foglia-radice per fare in modo che venga rispettata
 * la proprieta' 3 della coda con priorita'
 *
 * @tparam T: Tipo di dato contenuto nella coda con priorita'
 */
template <class T>
void PriorityQueue<T>::_fixUp()
{
    int currentChildPos = this->_currentSize - 1;
    int currentParentPos;

    /**
     * Analizzo l'ultimo elemento inserito nell'albero. se questo non rispetta la proprieta' 3 delle
     * code con priorita' (ovvero deve avere un valore >= a quello del genitore) allora effettuo uno
     * scambio con il genitore
     */

    Type currentChild = this->_heap[currentChildPos];
    Type currentParent;

    if(currentChildPos % 2 == 0)
    {
        currentParentPos = currentChildPos / 2 - 1;
    }

    else
    {
        currentParentPos = currentChildPos / 2;
    }

    currentParent = this->_heap[currentParentPos];

    while((currentChildPos > 0) && (currentChild < currentParent))
    {
        //faccio lo scambio

        Type temp = currentChild;
        this->_heap[currentChildPos] = this->_heap[currentParentPos];
        this->_heap[currentParentPos] = temp;

        currentChildPos = currentParentPos;

        if(currentChildPos % 2 == 0)
        {
            currentParentPos = currentChildPos / 2 - 1;
        }
        else
        {
            currentParentPos = currentChildPos / 2;
        }

        currentChild = this->_heap[currentChildPos];
        currentParent = this->_heap[currentParentPos];
    }
}

/**
 * Per ripristinare i vincoli dello heap quando la priorita' di un nodo si e'
 * ridotta, ci spostiamo nello heap verso il basso, scambiando, se necessario,
 * il nodo in posizione startPos con il minore dei suoi nodi figli e arrestandoci
*  quando il nodo al posto startPos non e' più grande di almeno uno dei suoi figli
 * oppure quando raggiungiamo il fondo dello heap. Si noti che se N e' pari e
 * startPos e' N/2, allora il nodo in posizione startPos ha un solo figlio: questo caso
 * particolare deve essere trattato in modo appropriato.
 *
 * @tparam T: Tipo di dato contenuto nella coda con priorita'
 * @param startPos: Posizione di partenza
 * @param endPos: Posizione finale
 */
template <class T>
void PriorityQueue<T>::_fixDown(std::size_t startPos, std::size_t endPos)
{
    bool isSwaped = true;

    while ((startPos <= endPos / 2) && isSwaped)
    {
        std::size_t j = 2 * startPos;

        if ((j<endPos) && (this->_heap[j - 1] > this->_heap[j]))
        {
            j++;
        }

        isSwaped = (this->_heap[j - 1] < this->_heap[startPos - 1]);

        if (isSwaped)
        {
            Type temp = this->_heap[startPos - 1];
            this->_heap[startPos - 1] = this->_heap[j - 1];
            this->_heap[j - 1] = temp;

            startPos = j;
        }
    }
}

#endif // _PRIORITYQUEUE_H
