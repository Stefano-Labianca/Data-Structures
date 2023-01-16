#ifndef _IGRAPH_H
#define _IGRAPH_H

#include "../LinkedList/LinkedList.h"
#include "../Queue/Queue.h"
#include "../PriorityQueue/PriorityQueue.h"

#include <vector>

/**
 * Notazione:
 * Matrice di adiacenza: Dato un grafo G=(N,A), con |N|=n, la matrice di adiacenza e'
 * una matrice quadrata di dimensione n (nxn) t.c. aij = 1 sse il nodo i e' adiacente al
 * nodo j, ovvero se esiste un arco (i,j) € A.
        1  2  3  4
 * 1   0  1  1 (1)--> il nodo 1 e' adiacente al nodo 4
 * 2   1  0  1  0
 * 3   0  0  0  1
 * 4   1  0  0  0

 * Se il grafo e' non orientato la matrice sara' simmetrica rispetto alla diagonale principale
 * (ovvero aij = aji)

 * Se il grafo e' pesato, nella matrice si utilizzano i pesi degli archi al posto
 * degli elementi binari. Se pij e' il peso dell'arco (i,j) allora l'elemento della
 * matrice di adicancenza diventa pij se (i,j) € A, e +inf/-inf se (i,j) € A
 *
 *
 * @tparam TNode
 * @tparam TNodeLabel
 * @tparam TLink
 * @tparam TLinkWeight
 */
template <class TNode, class TNodeLabel, class TLink, class TLinkWeight>
class IGraph
{
    virtual uint32_t getNodeAmount() const = 0;
    virtual uint32_t getLinkAmount() const = 0;

    virtual void create() = 0;

    virtual bool isEmpty() const = 0;
    virtual bool isNodeEnabled(const TNode& node) const = 0;
    virtual bool isLinkActive(const TNode& from, const TNode& to) const = 0;

    virtual TNodeLabel getLabel(const TNode& node) const = 0;
    virtual TLinkWeight getWeight(const TNode& from, const TNode& to) const = 0;

    virtual void addNode(TNode& node, TNodeLabel label) = 0;
    virtual void addNode(TNode& node) = 0;
    virtual void addLink(TNode& from, TNode& to, TLinkWeight weight) = 0;
    virtual void eraseNode(TNode& node) = 0;
    virtual void eraseLink(TNode& from, TNode& to) = 0;

    virtual void setLabel(TNode& node, TNodeLabel label) = 0;
    virtual void setWeight(TNode& from, TNode& to, TLinkWeight weight) = 0;

    virtual LinkedList<uint32_t> getAdjacentNode(const TNode& node) const = 0;

};

#endif // _IGRAPH_H
