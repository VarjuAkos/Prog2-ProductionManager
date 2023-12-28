//
// Created by varju on 2022.05.01..
//
/*
#ifndef HAZI_LISTA_HPP
#define HAZI_LISTA_HPP
#include "memtrace.h"
//ez meg soka
template<typename TIPUS>
 struct Lista {
        Lista * kov;
        TIPUS* mit;
        int sum;
        // <- TIPUS itt is érvényes!
};á
 */
/*
struct Elem {
    Hozzavalo* hozzavalo;
public:
    int mennyiseg;
    Hozzavalo* getHozzavalo() const {return hozzavalo;}
    Elem(Hozzavalo* hozzavalo, int mennyiseg) : hozzavalo(hozzavalo), mennyiseg(mennyiseg) {}
};*/
/*
template<typename TIPUS>
class Lista {
private:
    ListaElem * eleje;
    int sum;
public:

    class iterator {

        ListaElem * elem;

    public:
        iterator(ListaElem * elem = NULL)
                : elem(elem) {
        }

        iterator& operator++() {
            if (elem != NULL)
                elem = elem->kov;
            return *this;
        }
        iterator operator++(int) {
            iterator masolat = *this; // !
            ++(*this);
            return masolat;
        }

        TIPUS& operator*() const {
            return elem->adat;
        }

        bool operator==(iterator rhs) const {
            return elem == rhs.elem;
        }
        bool operator!=(iterator rhs) const {
            return elem != rhs.elem;
        }
    };

    iterator begin() {
        return iterator(eleje);
    }

    iterator end() {
        return iterator(NULL);
    }
};
*/
#endif //HAZI_LISTA_HPP
