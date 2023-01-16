#include <string>
#include "../SortedLinkedList/SortedLinkedList.h"

using Iterator = LinkedList<std::string>::Iterator;

class eo_strings
{
    private:
        LinkedList<std::string> pari;
        LinkedList<std::string> dispari;

    public:
        // inserisce una stringa nella corrispondente lista
        void inserisci(std::string s);

        // rimuove la stringa dalla corrispondente lista
        void rimuovi(std::string s);

        // rimuove le stringhe di lunghezza pari che iniziano con il carattere c
        void rimuovi(char c);

        // restituisce il numero di stringhe di lunghezza pari
        int freq_pari();

        // visualizza le stringhe di lunghezza dispari ordinate per lunghezza
        void visualizza_dispari();

        // Metodi di supporto per la visualizzazione delle liste contenute

        void mostra_pari_contenuti();
        void mostra_dispari_contenuti();
};


void eo_strings::inserisci(std::string s)
{
    if (s.length() % 2 == 0)
    {
        this->pari.append(s);
        return;
    }

    this->dispari.append(s);
}

void eo_strings::rimuovi(std::string s)
{
    if (s.length() % 2 == 0)
    {
        this->pari.remove(s);
        return;
    }

    this->dispari.remove(s);
}

void eo_strings::rimuovi(char c)
{
    Iterator it = this->pari.begin();

    while (!this->pari.isEnd(it))
    {
        if (it->getNodeValue().at(0) == c)
        {
            this->pari.remove(it);
            return;
        }

        it = it->getNext();
    }
}


int eo_strings::freq_pari()
{
    return this->pari.getSize();
}


void eo_strings::visualizza_dispari()
{
    Iterator q;
    std::string str;

    for (Iterator it = this->dispari.begin(); !this->dispari.isEnd(it); it = it->getNext())
    {
        str = it->getNodeValue();

        if (it != this->dispari.begin())
        {
            q = this->dispari.begin();

            while (q->getNodeValue().length() < str.length())
            {
                q = q->getNext();
            }

            LinkedNode<std::string> pIt(*it);

            this->dispari.insert(q, str);
            this->dispari.remove(it);

            it = &pIt;
        }
    }

    std::cout << this->dispari;
}



void eo_strings::mostra_pari_contenuti()
{
    std::cout << this->pari;
}


void eo_strings::mostra_dispari_contenuti()
{
    std::cout << this->dispari;
}


