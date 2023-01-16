#ifndef _GRAPH_H
#define _GRAPH_H

#include "IGraph.h"
#include <string>
#include <iostream>
#include <limits>


/**
 * Descrive un generico arco di un grafo. Dato che la classe Graph rappresenta un grafo
 * orientato e pesato, allora l'arco avra' un nodo di partenza e un nodo di arrivo.
 *
 * @tparam TGraphNode: Tipo del nodo di arrivo e di partenza dell'arco
 */
template <class TGraphNode>
class Link
{
    public:
        TGraphNode from; // Nodo di partenza dell'arco
        TGraphNode to; // Nodo di arrivo dall'arco
};



/**
 * Contiene delle informazioni aggiuntive su un arco, ovvero un flag che indica se e' attivo o
 * meno e infine il suo peso.
 *
 * @tparam TLinkWeight : Tipo del peso dell'arco
 */
template <class TLinkWeight>
class LinkInfo
{
    public:
        bool linkExists; // Se e' true, allora abbiano un arco attivo, altrimenti e' inattivo
        TLinkWeight weight; // Peso dell'arco

    public:
        LinkInfo();

};

/**
 * Costruttore che crea un arco non attivo
 *
 * @tparam TLinkWeight : Tipo del peso dell'arco
 */
template<class TLinkWeight>
LinkInfo<TLinkWeight>::LinkInfo()
{
    this->linkExists = false;
}




/**
 * Descrive un nodo di un grafo identificato con un id univoco di tipo intero
 *
 */
class GraphNode
{
    private:
        uint32_t _id; // Id univoco del nodo.

    public:
        GraphNode();
        GraphNode(uint32_t id);

        uint32_t getId() const;
        void setId(uint32_t id);

        bool operator==(const GraphNode& node) const;
        GraphNode& operator=(const GraphNode& node);
};

/**
 * Costuttore che crea un nodo con id pari a 0
 */
GraphNode::GraphNode()
{
    this->_id = 0;
}


/**
 * Costruttore che crea un nodo con un id pari al valore passato
 * ad id.
 *
 * @param id: Id del nodo.
 */
GraphNode::GraphNode(uint32_t id)
{
    this->_id = id;
}

/**
 * Restituisce l'id del nodo.
 * @return Id del nodo
 */
uint32_t GraphNode::getId() const
{
    return this->_id;
}

/**
 * Imposta l'id di un nodo.
 *
 * @param id : Id del nodo
 */
void GraphNode::setId(uint32_t id)
{
    this->_id = id;
}

bool GraphNode::operator==(const GraphNode& node) const
{
    return (node._id == this->_id);
}

GraphNode& GraphNode::operator=(const GraphNode& node)
{
    if (this != &node)
    {
        this->_id = node._id;
    }

    return *this;
}



/**
 * Contiene informazioni aggiuntive ad un nodo del grafo.
 * Tra le informazioni aggiuntive vengono indicate se il nodo e' attivo, la sua
 * etichetta e una lista archi uscenti da esso.
 *
 * @tparam TNodeLabel : Tipo dell'etichetta
 * @tparam TLinkWeight : Tipo del peso dell'arco
 */
template <class TNodeLabel, class TLinkWeight>
class GraphNodeInfo
{
    public:
        /**
         * Definisce se il nodo e' attivo o meno. True mi dice che e'
         * attivo, altrimenti e' inattivo se ha false.
         */
        bool isEnabled;
        TNodeLabel label; // Etichetta del nodo
        LinkInfo<TLinkWeight>* adjacencyMatrixCols; // Archi uscenti dal nodo

    public:
        GraphNodeInfo();
        ~GraphNodeInfo();
};


/**
 * Crea un nodo inattivo.
 *
 * @tparam TNodeLabel : Tipo dell'etichetta
 * @tparam TLinkWeight : Tipo del peso dell'arco
 */
template<class TNodeLabel, class TLinkWeight>
GraphNodeInfo<TNodeLabel, TLinkWeight>::GraphNodeInfo()
{
    this->isEnabled = false;
    /**
     * Essendo inattivo, non possiede etichetta o archi uscenti.
     * L'array adjacencyMatrixCols verra' creato non appena il nodo sara' attivo
     */
}

/**
 * Distruttore
 *
 * @tparam TNodeLabel : Tipo dell'etichetta
 * @tparam TLinkWeight : Tipo del peso dell'arco
 */
template<class TNodeLabel, class TLinkWeight>
GraphNodeInfo<TNodeLabel, TLinkWeight>::~GraphNodeInfo()
{
    if (this->isEnabled)
    {
        delete[] this->adjacencyMatrixCols;
        this->adjacencyMatrixCols = nullptr;
    }
}






/**
 * Class che descrive un grafo pesato e orientato attraverso una matrice di adiacenza.
 * Al suo interno troviamo: il numero massimo di nodi ammessi, il numero corrente di nodi
 * nel grafo e il numero di archi presenti nel grafo.
 *
 * @tparam TNodeLabel : Tipo dell'etichetta
 * @tparam TLinkWeight : Tipo del peso dell'arco
 */
template <class TNodeLabel, class TLinkWeight>
class Graph : public IGraph<GraphNode, TNodeLabel, Link<GraphNode>, TLinkWeight>
{
    public:
        typedef Link<GraphNode> Link;
        typedef LinkedList<uint32_t> GraphNodeList;
        typedef LinkedList<Link> LinkList;

    private:
        const int _INFINITY = INT_MAX; // Costante utile per l'algoritmo di Disjkstra
        const int _NON_EXISTING = -2; // Costante utile per l'algoritmo di Disjkstra

        GraphNodeInfo<TNodeLabel, TLinkWeight>* _adjacencyMatrixRows; // Contiene i nodi presenti nel grafo.
        uint32_t _gSize; // Numero massimo di nodi inseribili nel grafo.
        uint32_t _nodeAmount; // Numero di nodi presenti attualmente nel grafo
        uint32_t _linkAmount; // Numero di archi presenti attualmente nel grafo

    private:
        void _dfs(const GraphNode& start, bool* isVisited) const;
        void _dfsWalk(const GraphNode& start, const GraphNode& end, bool* isVisited, bool& endWalk, GraphNodeList& walkList);

    public:
        Graph(uint32_t size);
        ~Graph();

        uint32_t getNodeAmount() const;
        uint32_t getLinkAmount() const;

        void create();

        bool isEmpty() const;
        bool isNodeEnabled(const GraphNode& node) const;
        bool isLinkActive(const GraphNode& from, const GraphNode& to) const;

        TNodeLabel getLabel(const GraphNode& node) const;
        TLinkWeight getWeight(const GraphNode& from, const GraphNode& to) const;

        void addNode(GraphNode& node, TNodeLabel label);
        void addNode(GraphNode& node);
        void addLink(GraphNode& from, GraphNode& to, TLinkWeight weight);

        void eraseNode(GraphNode& node);
        void eraseLink(GraphNode& from, GraphNode& to);

        void setLabel(GraphNode& node, TNodeLabel label);
        void setWeight(GraphNode& from, GraphNode& to, TLinkWeight weight);

        GraphNodeList getAdjacentToANode(const GraphNode& node) const;
        GraphNodeList getAdjacentFromANode(const GraphNode& node) const;

        uint32_t getDegreeTo(const GraphNode& node) const;
        uint32_t getDegreeFrom(const GraphNode& node) const;

        double getDegreeToAvg() const;
        double getDegreeFromAvg() const;

        GraphNodeList getAdjacentNode(const GraphNode& node) const;
        GraphNodeList getAllNodes() const;

        void bfs(const GraphNode& start) const;
        void dfs(const GraphNode& start) const;
        void dijkstra(const GraphNode& start) const;

        GraphNodeList dfsWalk(const GraphNode& start, const GraphNode& end);
        GraphNodeList getSameReachableNodes(const GraphNode& node);

        template <class TypeNodeLabel, class TypeLinkWeight>
        friend std::ostream& operator<<(std::ostream&, Graph<TypeNodeLabel, TypeLinkWeight>& graph);

};


/**
 * Costruisce una matrice di adiacenza con un numero di righe pari a size.
 *
 * @tparam TNodeLabel : Tipo dell'etichetta
 * @tparam TLinkWeight : Tipo del peso dell'arco
 * @param size : Numero di righe della matrice
 */
template <class TNodeLabel, class TLinkWeight>
Graph<TNodeLabel, TLinkWeight>::Graph(uint32_t size)
{
    this->_gSize = size;
    this->_nodeAmount = 0;
    this->_linkAmount = 0;

    // Creo la matrice di adiacenza allocandoli le prime size righe.
    this->_adjacencyMatrixRows = new GraphNodeInfo<TNodeLabel, TLinkWeight>[this->_gSize]();


    // Alloco le colonne
    for (uint32_t i = 0; i < this->_gSize; i++)
    {
        this->_adjacencyMatrixRows[i].adjacencyMatrixCols = nullptr;
    }
}

/**
 * Distruttore
 *
 * @tparam TNodeLabel : Tipo dell'etichetta
 * @tparam TLinkWeight : Tipo del peso dell'arco
 */
template <class TNodeLabel, class TLinkWeight>
Graph<TNodeLabel, TLinkWeight>::~Graph()
{
    for (uint32_t i = 0; i < this->_gSize; i++)
    {
        if (this->_adjacencyMatrixRows[i].adjacencyMatrixCols != nullptr)
        {
            delete[] this->_adjacencyMatrixRows[i].adjacencyMatrixCols;
            this->_adjacencyMatrixRows[i].adjacencyMatrixCols = nullptr;
        }
    }

    delete[] this->_adjacencyMatrixRows;
}

/**
 * Restituisce il numero di nodi attualmente presente nel grafo
 *
 * @tparam TNodeLabel : Tipo dell'etichetta
 * @tparam TLinkWeight : Tipo del peso dell'arco
 * @return Numero di nodi presenti nel grafo
 */
template <class TNodeLabel, class TLinkWeight>
uint32_t Graph<TNodeLabel, TLinkWeight>::getNodeAmount() const
{
    return this->_nodeAmount;
}

/**
 * Restituisce il numero di archi attualmente presente nel grafo
 *
 * @tparam TNodeLabel : Tipo dell'etichetta
 * @tparam TLinkWeight : Tipo del peso dell'arco
 * @return Numero di archi presenti nel grafo
 */
template <class TNodeLabel, class TLinkWeight>
uint32_t Graph<TNodeLabel, TLinkWeight>::getLinkAmount() const
{
    return this->_linkAmount;
}


template <class TNodeLabel, class TLinkWeight>
void Graph<TNodeLabel, TLinkWeight>::create() { }


/**
 * Restituisce true se il grafo e' vuoto, altrimenti false.
 *
 * @tparam TNodeLabel : Tipo dell'etichetta
 * @tparam TLinkWeight : Tipo del peso dell'arco
 * @return True se il grafo e' vuoto, altrimenti false.
 */
template <class TNodeLabel, class TLinkWeight>
bool Graph<TNodeLabel, TLinkWeight>::isEmpty() const
{
    return (this->_nodeAmount == 0);
}

/**
 * Restituisce true se il nodo e' attivo, altrimenti false.
 *
 * @tparam TNodeLabel : Tipo dell'etichetta
 * @tparam TLinkWeight : Tipo del peso dell'arco
 * @return True se il nodo e' attivo, altrimenti false.
 */
template <class TNodeLabel, class TLinkWeight>
bool Graph<TNodeLabel, TLinkWeight>::isNodeEnabled(const GraphNode& node) const
{
    uint32_t id = node.getId();

    return (this->_adjacencyMatrixRows[id].isEnabled);
}

/**
 * Restituisce true se l'arco e' attivo, altrimenti false.
 *
 * @tparam TNodeLabel : Tipo dell'etichetta
 * @tparam TLinkWeight : Tipo del peso dell'arco
 *
 * @param from : Nodo di partenza
 * @param to: Nodo di arrivo
 *
 * @return True se l'arco e' attivo, altrimenti false.
 */
template <class TNodeLabel, class TLinkWeight>
bool Graph<TNodeLabel, TLinkWeight>::isLinkActive(const GraphNode& from, const GraphNode& to) const
{
    if (!this->isNodeEnabled(from) || !this->isNodeEnabled(to))
    {
        return false;
    }

    uint32_t fromId = from.getId();
    uint32_t toId = to.getId();

    return this->_adjacencyMatrixRows[fromId].adjacencyMatrixCols[toId].linkExists;
}

/**
 * Restituisce l'etichetta contenuta nel nodo.
 *
 * @tparam TNodeLabel : Tipo dell'etichetta
 * @tparam TLinkWeight : Tipo del peso dell'arco
 * @param node : Nodo a cui leggere l'etichetta
 * @return Etichetta del nodo.
 */
template <class TNodeLabel, class TLinkWeight>
TNodeLabel Graph<TNodeLabel, TLinkWeight>::getLabel(const GraphNode& node) const
{
    if (this->isNodeEnabled(node))
    {
        uint32_t id = node.getId();
        this->_adjacencyMatrixRows[id].label;
    }

}

/**
 * Restituisce il peso dell'arco.
 *
 * @tparam TNodeLabel : Tipo dell'etichetta
 * @tparam TLinkWeight : Tipo del peso dell'arco
 * @param from: Nodo di partenza
 * @param to: Nodo di arrivo
 * @return Peso dell'arco che va da from a to
 */
template <class TNodeLabel, class TLinkWeight>
TLinkWeight Graph<TNodeLabel, TLinkWeight>::getWeight(const GraphNode& from, const GraphNode& to) const
{
    if (this->isNodeEnabled(from) && this->isNodeEnabled(to))
    {
        uint32_t fromId = from.getId();
        uint32_t toId = to.getId();

        bool linkFlag = this->_adjacencyMatrixRows[fromId].adjacencyMatrixCols[toId].linkExists;

        if (linkFlag)
        {
            return this->_adjacencyMatrixRows[fromId].adjacencyMatrixCols[toId].weight;
        }
    }
}


/**
 * Aggiungo un nodo nel grafo con una sua etichetta.
 *
 * Se ho raggiunto il limite massimo di nodi, il nuovo nodo non verra'
 * inserito nel grafo
 *
 * @tparam TNodeLabel : Tipo dell'etichetta
 * @tparam TLinkWeight : Tipo del peso dell'arco
 * @param node : Nodo da aggiungere
 * @param label : Etichetta del nodo
 */
template <class TNodeLabel, class TLinkWeight>
void Graph<TNodeLabel, TLinkWeight>::addNode(GraphNode& node, TNodeLabel label)
{
    if (this->_nodeAmount >= this->_gSize)
    {
        return; // Ho superato il numero massimo di nodi consentiti
    }

    for (uint32_t i = 0; i < this->_gSize; i++)
    {
        if (!this->_adjacencyMatrixRows[i].isEnabled)
        {
            // Ho una riga della matrice di adiacenza libera

            node.setId(i);
            this->_adjacencyMatrixRows[i].isEnabled = true;
            this->_adjacencyMatrixRows[i].label = label;

            // Alloco dello spazio per le colonne della riga di adiacenza
            this->_adjacencyMatrixRows[i].adjacencyMatrixCols = new LinkInfo<TLinkWeight>[this->_gSize]();
            this->_nodeAmount++;

            break;
        }
    }
}


/**
 * Aggiungo un nodo nel grafo senza specificare un'etichetta
 *
 * @tparam TNodeLabel : Tipo dell'etichetta
 * @tparam TLinkWeight : Tipo del peso dell'arco
 * @param node : Nodo da aggiungere
 */
template <class TNodeLabel, class TLinkWeight>
void Graph<TNodeLabel, TLinkWeight>::addNode(GraphNode& node)
{
    if (this->_nodeAmount >= this->_gSize)
    {
        return; // Ho superato il numero massimo di nodi consentiti
    }

    for (uint32_t i = 0; i < this->_gSize; i++)
    {
        if (!this->_adjacencyMatrixRows[i].isEnabled)
        {
            // Ho una riga della matrice di adiacenza libera

            node.setId(i);
            this->_adjacencyMatrixRows[i].isEnabled = true;

            // Alloco dello spazio per le colonne della riga di adiacenza
            this->_adjacencyMatrixRows[i].adjacencyMatrixCols = new LinkInfo<TLinkWeight>[this->_gSize]();
            this->_nodeAmount++;

            break;
        }
    }
}

/**
 * Collega due nodi con un arco di peso weight
 *
 * @tparam TNodeLabel : Tipo dell'etichetta
 * @tparam TLinkWeight : Tipo del peso dell'arco
 * @param from : Nodo di partenza
 * @param to : Nodo di arrivo
 * @param weight : Peso arco
 */
template <class TNodeLabel, class TLinkWeight>
void Graph<TNodeLabel, TLinkWeight>::addLink(GraphNode& from, GraphNode& to, TLinkWeight weight)
{
    // Verifico se i nodi dati esistono
    if (!this->isNodeEnabled(from) || !this->isNodeEnabled(to))
    {
        return;
    }


    // Non sono ammessi pesi negativi
    if (weight < 0)
    {
        return;
    }

    uint32_t fromId = from.getId();
    uint32_t toId = to.getId();

    this->_adjacencyMatrixRows[fromId].adjacencyMatrixCols[toId].linkExists = true;
    this->_adjacencyMatrixRows[fromId].adjacencyMatrixCols[toId].weight = weight;

    this->_linkAmount++;
}


/**
 * Elimina un nodo dal grafo
 *
 * @tparam TNodeLabel : Tipo dell'etichetta
 * @tparam TLinkWeight : Tipo del peso dell'arco
 * @param node : Nodo da cancellare
 */
template <class TNodeLabel, class TLinkWeight>
void Graph<TNodeLabel, TLinkWeight>::eraseNode(GraphNode& node)
{
    if (!this->isNodeEnabled(node))
    {
        return;
    }

    // Disabilito il nodo
    uint32_t idToRemove = node.getId();
    this->_adjacencyMatrixRows[idToRemove].isEnabled = false;

    // Elimino tutti gli archi entranti nel nodo da cancellare
    for (uint32_t i = 0; i < this->_gSize; i++)
    {
        if (this->_adjacencyMatrixRows[i].isEnabled)
        {
            if (this->_adjacencyMatrixRows[i].adjacencyMatrixCols[idToRemove].linkExists)
            {
                this->_adjacencyMatrixRows[i].adjacencyMatrixCols[idToRemove].linkExists = false;
                this->_linkAmount--;
            }
        }
    }

    // Elimino tutti gli archi uscenti dal nodo da cancellare
    for (uint32_t j = 0; j < this->_gSize; j++)
    {
        if (this->_adjacencyMatrixRows[idToRemove].adjacencyMatrixCols[j].linkExists)
        {
            this->_linkAmount--;
        }
    }

    delete[] this->_adjacencyMatrixRows[idToRemove].adjacencyMatrixCols;
    this->_adjacencyMatrixRows[idToRemove].adjacencyMatrixCols = nullptr;
}


/**
 * Cancella un arco che va da from a to.
 *
 * @tparam TNodeLabel : Tipo dell'etichetta
 * @tparam TLinkWeight : Tipo del peso dell'arco
 * @param from : Nodo di partenza
 * @param to : Nodo di arrivo
 */
template <class TNodeLabel, class TLinkWeight>
void Graph<TNodeLabel, TLinkWeight>::eraseLink(GraphNode& from, GraphNode& to)
{
    if (!this->isNodeEnabled(from) || !this->isNodeEnabled(to))
    {
        return;
    }

    uint32_t fromId = from.getId();
    uint32_t toId = to.getId();

    this->_adjacencyMatrixRows[fromId].adjacencyMatrixCols[toId].linkExists = false;
    this->_linkAmount--;
}


/**
 * Imposta un'etichetta ad un nodo
 *
 * @tparam TNodeLabel : Tipo dell'etichetta
 * @tparam TLinkWeight : Tipo del peso dell'arco
 * @param node : Nodo a cui aggiungere un'etichetta
 * @param label : Etichetta da aggiungere
 */
template <class TNodeLabel, class TLinkWeight>
void Graph<TNodeLabel, TLinkWeight>::setLabel(GraphNode& node, TNodeLabel label)
{
    if (!this->isNodeEnabled(node))
    {
        return;
    }

    this->_adjacencyMatrixRows[node.getId()].label = label;
}


/**
 * Imposta un peso di un arco che collega due nodi
 *
 * @tparam TNodeLabel : Tipo dell'etichetta
 * @tparam TLinkWeight : Tipo del peso dell'arco
 * @param from : Nodo di partenza
 * @param to : Nodo di arrivo
 * @param weight : Peso dell'arco
 */
template <class TNodeLabel, class TLinkWeight>
void Graph<TNodeLabel, TLinkWeight>::setWeight(GraphNode& from, GraphNode& to, TLinkWeight weight)
{
    if (!this->isLinkActive(from, to))
    {
        return;
    }

    if (weight < 0)
    {
        return;
    }

    uint32_t fromId = from.getId();
    uint32_t toId = to.getId();

    this->_adjacencyMatrixRows[fromId].adjacencyMatrixCols[toId].weight = weight;
}

/**
 * Restituisce una lista di id di nodi che sono puntati da node.
 * In altre parole, ho una lista di nodi che sono puntati dal nodo dato.
 *
 * Se node non esiste, allora restituisce una lista vuota.
 *
 * @tparam TNodeLabel : Tipo dell'etichetta
 * @tparam TLinkWeight : Tipo del peso dell'arco
 * @param node : Nodo da cui ricavare la lista
 * @return Lista di id di nodi che sono puntati da node
 */
template <class TNodeLabel, class TLinkWeight>
typename Graph<TNodeLabel, TLinkWeight>::GraphNodeList Graph<TNodeLabel, TLinkWeight>::getAdjacentToANode(const GraphNode& node) const
{
    GraphNodeList nodes;

    if (!this->isNodeEnabled(node))
    {
        return nodes;
    }

    uint32_t id = node.getId();

    for (uint32_t j = 0; j < this->_gSize; j++)
    {
        if (this->_adjacencyMatrixRows[id].adjacencyMatrixCols[j].linkExists)
        {
            nodes.append(j);
        }
    }

    nodes.removeDuplicate();
    return nodes;
}

/**
 * Restituisce una lista di id di nodi che puntano a node.
 * In altre parole, ho una lista di nodi che puntano al nodo dato
 *
 * Se node non esiste, allora restituisce una lista vuota.
 *
 * @tparam TNodeLabel : Tipo dell'etichetta
 * @tparam TLinkWeight : Tipo del peso dell'arco
 * @param node : Nodo da cui ricavare la lista
 * @return Lista di id di nodi che puntano a node
 */
template <class TNodeLabel, class TLinkWeight>
typename Graph<TNodeLabel, TLinkWeight>::GraphNodeList Graph<TNodeLabel, TLinkWeight>::getAdjacentFromANode(const GraphNode& node) const
{
    GraphNodeList nodes;

    if (!this->isNodeEnabled(node))
    {
        return nodes;
    }

    uint32_t id = node.getId();

    for (uint32_t i = 0; i < this->_gSize; i++)
    {
        if (this->_adjacencyMatrixRows[i].isEnabled)
        {
            if (this->_adjacencyMatrixRows[i].adjacencyMatrixCols[id].linkExists)
            {
                nodes.append(i);
            }
        }
    }

    nodes.removeDuplicate();
    return nodes;
}

/**
 * Restituisce il numero di archi uscenti dal nodo
 *
 * @tparam TNodeLabel : Tipo dell'etichetta
 * @tparam TLinkWeight : Tipo del peso dell'arco
 * @param node : Nodo a cui calcolare il numero di archi uscenti
 * @return numero di archi uscenti dal nodo
 */
template <class TNodeLabel, class TLinkWeight>
uint32_t Graph<TNodeLabel, TLinkWeight>::getDegreeTo(const GraphNode& node) const
{
    GraphNodeList nodes = this->getAdjacentToANode(node);
    return nodes.getSize();
}


/**
 * Restituisce il numero di archi entranti nel nodo
 *
 * @tparam TNodeLabel : Tipo dell'etichetta
 * @tparam TLinkWeight : Tipo del peso dell'arco
 * @param node : Nodo a cui calcolare il numero di archi uscenti
 * @return numero di archi entranti nel nodo
 */
template <class TNodeLabel, class TLinkWeight>
uint32_t Graph<TNodeLabel, TLinkWeight>::getDegreeFrom(const GraphNode& node) const
{
    GraphNodeList nodes = this->getAdjacentFromANode(node);
    return nodes.getSize();
}


/**
 * Restituisce il numero medio di archi uscenti presenti nel grafo
 *
 * @tparam TNodeLabel : Tipo dell'etichetta
 * @tparam TLinkWeight : Tipo del peso dell'arco
 * @return numero medio di archi uscenti presenti nel grafo
 */
template <class TNodeLabel, class TLinkWeight>
double Graph<TNodeLabel, TLinkWeight>::getDegreeToAvg() const
{
    double degreeSum = 0.0;

    for (uint32_t i = 0; i < this->_gSize; i++)
    {
        if (this->_adjacencyMatrixRows[i].isEnabled)
        {
            degreeSum += this->getDegreeTo(GraphNode(i));
        }
    }

    return (degreeSum / this->_nodeAmount);
}

/**
 * Restituisce il numero medio di archi entranti presenti nel grafo
 *
 * @tparam TNodeLabel : Tipo dell'etichetta
 * @tparam TLinkWeight : Tipo del peso dell'arco
 * @return numero medio di archi entranti presenti nel grafo
 */
template <class TNodeLabel, class TLinkWeight>
double Graph<TNodeLabel, TLinkWeight>::getDegreeFromAvg() const
{
    double degreeSum = 0.0;

    for (uint32_t i = 0; i < this->_gSize; i++)
    {
        if (this->_adjacencyMatrixRows[i].isEnabled)
        {
            degreeSum += this->getDegreeFrom(GraphNode(i));
        }
    }

    return (degreeSum / this->_nodeAmount);
}

/**
 * Restituisce una lista contenente tutti gli id dei nodi adiacenti a node:
 *
 * @tparam TNodeLabel : Tipo dell'etichetta
 * @tparam TLinkWeight : Tipo del peso dell'arco
 * @param node : Nodo a cui trovare i suoi vicini
 * @return Lista di id di nodi adiacenti a node
 */
template <class TNodeLabel, class TLinkWeight>
typename Graph<TNodeLabel, TLinkWeight>::GraphNodeList Graph<TNodeLabel, TLinkWeight>::getAdjacentNode(const GraphNode& node) const
{
    GraphNodeList nodesTo = this->getAdjacentToANode(node);
    GraphNodeList nodesFrom = this->getAdjacentFromANode(node);
    GraphNodeList adjacentNodes;

    GraphNodeList::Iterator it = nodesTo.begin();

    while (!nodesTo.isEnd(it))
    {
        adjacentNodes.append(it->getNodeValue());
        it = it->getNext();
    }

    it = nodesFrom.begin();

    while (!nodesFrom.isEnd(it))
    {
        adjacentNodes.append(it->getNodeValue());
        it = it->getNext();
    }

    adjacentNodes.removeDuplicate();
    return adjacentNodes;
}

/**
 * Restituisce una lista contenente gli id di tutti i nodi presenti
 * nel grafo
 *
 * @tparam TNodeLabel : Tipo dell'etichetta
 * @tparam TLinkWeight : Tipo del peso dell'arco
 * @return Lista degli id di tutti i nodi del grafo
 */
template <class TNodeLabel, class TLinkWeight>
typename Graph<TNodeLabel, TLinkWeight>::GraphNodeList Graph<TNodeLabel, TLinkWeight>::getAllNodes() const
{
    GraphNodeList nodes;

    for (uint32_t i = 0; i < this->_gSize; i++)
    {
        if (this->_adjacencyMatrixRows[i].isEnabled)
        {
            nodes.append(i);
        }
    }

    return nodes;
}


/**
 * Visito il grafo tramite l'algoritmo Breadth-First-Search (BFS).
 *
 * @tparam TNodeLabel : Tipo dell'etichetta
 * @tparam TLinkWeight : Tipo del peso dell'arco
 * @param start : Nodo di partenza della visita
 */
template <class TNodeLabel, class TLinkWeight>
void Graph<TNodeLabel, TLinkWeight>::bfs(const GraphNode& start) const
{
    if (this->isEmpty())
    {
        return;
    }

    if (!this->isNodeEnabled(start))
    {
        return;
    }

    // Inserisco il nodo di partenza nella coda

    Queue<GraphNode> queue;
    queue.enqueue(start);

    bool isVisited[this->_gSize];

    for (uint32_t i = 0; i < this->_gSize; i++)
    {
        isVisited[i] = false;
    }

    isVisited[start.getId()] = true;

    // Vado a visitare tutti i nodi del grafo
    while (!queue.isEmpty())
    {
        GraphNode node = queue.top();
        queue.dequeue();

        GraphNodeList adj = this->getAdjacentToANode(node);
        std::cout << "Nodo: " << node.getId() << " --> ";

        /**
         * Visito tutti i vicini del nodo e, una volta visitati, vado al vicino successivo
         * Tutti i nodi non visitati, dopo averli visitati, verranno messi in coda per
         * poi essere visitati successivamente
         */

        for (auto it = adj.begin(); !adj.isEnd(it); it = it->getNext())
        {
            std::cout << "(" << node.getId() << "," << it->getNodeValue() << ") ";

            if (isVisited[it->getNodeValue()] == false)
            {
                isVisited[it->getNodeValue()] = true;
                queue.enqueue(it->getNodeValue()); // Metto in coda tutti i vicini del nodo in cui mi trovo attualmente
            }
        }

        std::cout << std::endl;
    }
}


/**
 * Visito il grafo tramite l'algoritmo Depth-First-Search (DFS).
 * L'algoritmo attua la previsita del grafo.
 *
 * @tparam TNodeLabel : Tipo dell'etichetta
 * @tparam TLinkWeight : Tipo del peso dell'arco
 * @param start : Nodo di partenza della visita
 */
template <class TNodeLabel, class TLinkWeight>
void Graph<TNodeLabel, TLinkWeight>::dfs(const GraphNode& start) const
{
    /**
     * L'array ha dimensioni uguali a quelle del numero massimo di nodi consentiti
     * nel grafo.
     *
     * Il suo scopo e' quello di fornire supporto alla chiamta ricorsiva del metodo
     * privata _dfs(const GraphNode& start, bool* isVisited)
     *
     * Al suo interno troviamo solo valori booleani dove, ogni cella mi dice se il nodo e'
     * stato visitato o meno. Se in una posizione i, il valore e' false, allora il nodo non e'
     * stato visitato o scoperto mentre, se ha valore true, il nodo e' stato scoperto.
     */
    bool isVisited[this->_gSize];

    for (uint32_t i = 0; i < this->_gSize; i++)
    {
        isVisited[i] = false;
    }

    this->_dfs(start, isVisited);
}


/**
 * Attua l'algoritmo di Dijkstra per trovare un albero di copertura minima all'interno
 * del grafo.
 * Se il vettore di padri e' vuoto, allora
 *
 * @tparam TNodeLabel : Tipo dell'etichetta
 * @tparam TLinkWeight : Tipo del peso dell'arco
 * @param start : Nodo di partenza
 */
template <class TNodeLabel, class TLinkWeight>
void Graph<TNodeLabel, TLinkWeight>::dijkstra(const GraphNode& start) const
{
    std::vector<int> spt(this->_gSize);                   // shortest path tree rappresentato con vettori di padri
    for(int i = 0; i < this->_gSize; i++)
    {
        spt[i] = this->_NON_EXISTING;
    }

    if(!this->isNodeEnabled(start))
    {
        std::cout << "[Nodo vuoto]" << std::endl;
        return;
    }

    if(this->isEmpty())
    {
        std::cout << "[Grafo vuoto]" << std::endl;
        return;
    }


    TLinkWeight distances[this->_gSize];          // Contiene per ogni nodo i il valore della lunghezza del cammino minimo da r a i

    // Struttura dati che contiene i nodi da processare
    // gli elementi della coda con priorità S sono nodi del grafo e le loro priorità corrispondono alla distanza da r.
    PriorityQueue<int> S;

    bool Smember[this->_gSize];    // Smember[i]=true significa che il nodo i dovrà essere processato perche' è contenuto in S
    for(int i = 0; i < this->_gSize; i++)
    {
        Smember[i]=false;
    }

    //uso la struttura dati booleana Smember perchè il tipo dato priority queue non prevede una funzione di ricerca

    GraphNodeList currentAdjacentList;
    int i;  //indice generico
    int u,v; //id di nodi

    for(i = 0;i<this->_gSize;i++)
    {
        if(this->_adjacencyMatrixRows[i].isEnabled)
        {
            distances[i] = this->_INFINITY;
        }
        else
        {
            distances[i] = this->_NON_EXISTING;
        }
    }

    spt[start.getId()] = -1;
    distances[start.getId()] = 0;
    S.insert((int) start.getId());
    Smember[start.getId()] = true;

    // Il ciclo si ripete finchè esistono nodi da processare
    while(!S.isEmpty())
    {
        u = S.min();       //recupero dalla priority queue il prossimo elemento da processare
        S.deleteMin();       //lo tolgo dalla priority queue perchè ora lo si processa
        Smember[u] = false;

        currentAdjacentList = this->getAdjacentToANode(GraphNode(u));

        //sfoglio gli adiacenti di u
        for(auto pos=currentAdjacentList.begin(); !currentAdjacentList.isEnd(pos); pos = pos->getNext())
        {
            v = (int) pos->getNodeValue();
            TLinkWeight actualWeight = distances[u] + this->getWeight(GraphNode(u), GraphNode(v));  // _adjacencyMatrixRows[u].adjacencyMatrixCols[v].weight;

            if(distances[v] == this->_INFINITY || actualWeight < distances[v] )
            {
                //in questo caso si è appena trovato che la distanza da r a v (calcolata con actualWeight) è minore della precedente distanza da r a v.
                //quindi aggiorniamo il valore distances[v]
                spt[v] = u;
                distances[v] = actualWeight;

                //la lunghezza del cammino minimo da r a v (ovvero dv) è stata modificata:
                //il nodo v viene inserito nuovamente in S (se assente) perché è possibile che v
                //possa ora essere un nodo intermedio più conveniente per raggiungere altri nodi.
                if(Smember[v] == false)
                {
                    S.insert(v);
                    Smember[v]=true;
                }
            }
        }
    }

    std::cout << "SPT" << std::endl;
    std::cout << "Leggenda: " << "(id_partenza, id_arrivo, costo)" << std::endl;
    std::cout << "Parteza algoritmo: " << start.getId() << std::endl;

    for (int j = 0; j < this->_gSize; j++)
    {
        if (spt[j] != -1)
        {
            std::cout << "(" << spt[j] << ", " << j << ", " << distances[j] << ")" << std::endl;
        }
    }
}




/**
 * Permette di trovare un cammino da un nodo start verso un nodo end all'interno del grafo
 *
 * @tparam TNodeLabel : Tipo dell'etichetta
 * @tparam TLinkWeight : Tipo del peso dell'arco
 * @param start : Nodo di partenza
 * @param end : Nodo di arrivo
 * @return Lista di nodi percorsi nel cammino
 */
template <class TNodeLabel, class TLinkWeight>
typename Graph<TNodeLabel, TLinkWeight>::GraphNodeList Graph<TNodeLabel, TLinkWeight>::dfsWalk(const GraphNode& start, const GraphNode& end)
{
    GraphNodeList walkList;
    bool visitedNodes[this->_gSize];
    for(int i = 0; i < this->_gSize; i++)
    {
        visitedNodes[i] = false;
    }

    bool endWalk = false;
    this->_dfsWalk(start, end, visitedNodes, endWalk, walkList);

    return walkList;
}

/**
 * Restituisce una lista di nodi, raggiungibili da node e che abbiano la sua stessa etichetta
 *
 * @tparam TNodeLabel : Tipo dell'etichetta
 * @tparam TLinkWeight : Tipo del peso dell'arco
 * @param node : Nodo di partenza
 * @return Lista contenente i nodi raggiungibili da node e che abbiano la sua stessa etichetta
 */
template <class TNodeLabel, class TLinkWeight>
typename Graph<TNodeLabel, TLinkWeight>::GraphNodeList Graph<TNodeLabel, TLinkWeight>::getSameReachableNodes(const GraphNode& node)
{
    GraphNodeList outList;

    if(!this->isNodeEnabled(node))
    {
        return outList;
    }

    if(this->isEmpty())
    {
        return outList;
    }

    TNodeLabel startingNodeLabel = this->_adjacencyMatrixRows[node.getId()].label;

    for(int i = 0; i < this->_gSize;i++)
    {
        if(this->_adjacencyMatrixRows[i].isEnabled && i != node.getId() && this->_adjacencyMatrixRows[i].label == startingNodeLabel)
        {
            if(!this->dfsWalk(node, GraphNode(i)).isEmpty())
            {
                outList.append(i);
            }
        }
    }

    return outList;
}




/**
 * Metodo privato di supporto per ricerca di un cammino da un nodo u verso un nodo v
 * del grafo tramite l'algoritmo Depth-First-Search (DFS).
 * L'algoritmo attua la previsita del grafo.
 *
 * @tparam TNodeLabel : Tipo dell'etichetta
 * @tparam TLinkWeight : Tipo del peso dell'arco

 * @param start : Nodo di partenza
 * @param end : Nodo di arrivo
 * @param isVisited : Array booleano
 * @param endWalk : Flag che segnala se ho raggiunto la fine del cammino
 * @param walkList : Lista di nodi percorsi
 */
template <class TNodeLabel, class TLinkWeight>
void Graph<TNodeLabel, TLinkWeight>::_dfsWalk(const GraphNode& start, const GraphNode& end, bool* isVisited, bool& endWalk, GraphNodeList& walkList)
{
    int idFirstNode = start.getId();
    int idSecondNode;

    isVisited[idFirstNode] = true;
    walkList.append(idFirstNode);

    auto adjacentNodeToList = this->getAdjacentToANode(GraphNode(idFirstNode));

    for (auto p = adjacentNodeToList.begin(); !adjacentNodeToList.isEnd(p) && !endWalk; p = p->getNext())
    {
        idSecondNode = p->getNodeValue();

        if(idSecondNode == end.getId())
        {
            endWalk = true;
            walkList.append(idSecondNode);
        }

        else if(isVisited[idSecondNode] == false)
        {
            this->_dfsWalk(GraphNode(idSecondNode), end, isVisited, endWalk, walkList);
        }
    }

    if(endWalk == false)
    {
        auto d = walkList.find(idFirstNode);
        if(d != nullptr)
        {
            walkList.remove(d);
        }
    }
}



/**
 * Metodo privato di supporto per la visita del grafo tramite l'algoritmo Depth-First-Search (DFS).
 * L'algoritmo attua la previsita del grafo.
 *
 * @tparam TNodeLabel : Tipo dell'etichetta
 * @tparam TLinkWeight : Tipo del peso dell'arco
 * @param start : Nodo di partenza della visita
 * @param isVisited : Array booleano di supporto alla chiamata
 */
template <class TNodeLabel, class TLinkWeight>
void Graph<TNodeLabel, TLinkWeight>::_dfs(const GraphNode& start, bool* isVisited) const
{
    isVisited[start.getId()] = true;
    std::cout << "Nodo: " << start.getId() << " --> "; // Previsita

    GraphNodeList adj = this->getAdjacentToANode(start);
    for (auto it = adj.begin(); !adj.isEnd(it); it = it->getNext())
    {
        std::cout << "(" << start.getId() << "," << it->getNodeValue() << ") ";

        if (!isVisited[it->getNodeValue()])
        {
            std::cout << std::endl;
            this->_dfs(GraphNode(it->getNodeValue()), isVisited);

            if (!adj.isEnd(it->getNext()))
            {
                std::cout << std::endl << "Nodo: " << start.getId() << " --> ";
            }
        }
    }

    // Decommentala per avere la postvisita, commentanto la riga con il commento "Previsita"
    //    std::cout << "Nodo: " << start.getId() << " --> "; // Postvisita
}


template <class TypeNodeLabel, class TypeLinkWeight>
std::ostream& operator<<(std::ostream& out, Graph<TypeNodeLabel, TypeLinkWeight>& graph)
{
    if(graph.isEmpty())
    {
        out << "[grafo vuoto]";
        out << std::endl << std::endl;
        return out;
    }

    for(uint32_t i = 0; i < graph._gSize; i++)
    {
        if(graph._adjacencyMatrixRows[i].isEnabled)
        {
            out << std::endl << "[t, " << graph._adjacencyMatrixRows[i].label << "]--->\t";

            for(uint32_t j=0; j< graph._gSize; j++)
            {
                if(graph._adjacencyMatrixRows[i].adjacencyMatrixCols[j].linkExists)
                {
                    out << "[t, " << graph._adjacencyMatrixRows[i].adjacencyMatrixCols[j].weight << "]\t";
                }

                else
                {
                    out << "[f, ]\t";
                }
            }
        }

        else
        {
            if(graph._adjacencyMatrixRows[i].adjacencyMatrixCols == nullptr)
            {
                out << std::endl << "[f,  ]-/-> ";
            }
        }
    }

    out << std::endl << std::endl;
    return out;
}

#endif // _GRAPH_H
