//
// Created by varju on 2022.05.01..
//

#ifndef HAZI_VEKTOR_HPP
#define HAZI_VEKTOR_HPP
#include "Classok.hpp"
//#include "memtrace.h"

template<typename TIPUS>
class Vektor {
    TIPUS *adat;
    size_t meret;
public:
    //kon
    explicit Vektor(size_t meret = 0) :
            adat(new TIPUS[meret]),
            meret(meret) {
    }
    //dtor
    ~Vektor(){
        delete [] adat;
    }
    ///Vektor<TIPUS>
    //cpy

    Vektor(Vektor const& masik){
        meret=masik.meret;
        adat=new TIPUS[meret];
        for(size_t i=0;i<meret;i++)
            adat[i]=(masik.adat)[i];
    }
    //op=
    Vektor& operator=(Vektor const & masik){
        if(this!=&masik){
            delete [] adat;
            adat=new TIPUS[meret];
            for(size_t i=0;i<meret;i++)
                adat[i]=(masik.adat)[i];
        }
        return *this;
    }

    size_t size() const {
        return meret;
    }

    TIPUS& operator[](size_t index) {
        return adat[index];
    }

    TIPUS const& operator[](size_t index) const {
        return adat[index];
    }

    void push_back(TIPUS const& uj_ertek) {
        auto *uj_adat = new TIPUS[meret + 1];
        for(size_t i = 0; i < meret; ++i)
            uj_adat[i] = adat[i];
        uj_adat[meret] = uj_ertek;
        delete[] adat;
        adat = uj_adat;
        ++meret;
    }
    ///Ez jó? Laci check pls
    void clear(){
        meret=0;
    }
};



#endif //HAZI_VEKTOR_HPP
