//
// Created by varju on 2022.05.01..
//

#ifndef HAZI_CLASSOK_HPP
#define HAZI_CLASSOK_HPP
#include <string.h>
#include <iostream>
#include "Vektor.hpp"
#include "memtrace.h"


class Hozzavalo{
protected:
    int cikkszam;
    std::string nev;
    double mennyiseg;
    double buildtime;
    double ar;
public:

    Hozzavalo(int cikknum,std::string &name,double amount,double buildtime,double price):cikkszam(cikknum),nev(name),mennyiseg(amount),buildtime(buildtime),ar(price){
    }
    virtual double getar()const=0;
    double getRaktaron(){
        return mennyiseg;
    }
    void setRaktaron(double raktaron){
        mennyiseg=raktaron;
    }
    std::string getNev(){
        return nev;
    }
    int getCikk(){
        return cikkszam;
    }
    double getBuildtime(){
        return buildtime;
    }

    //virtual void kiir()=default;
    //virtual void elad()=default;

};
class Alapanyag:public Hozzavalo{
public:
    //konstrukt
    Alapanyag(int cikknum,std::string& name,double amount,double price) : Hozzavalo(cikknum,name,amount, 0, price){}

    int getcikkszam()const{
        return cikkszam;
    }
    double getar()const{
        return ar;
    }
    void kiir(){
        std::cout<<"["<<cikkszam<<"]\t"<<nev<<"\tAr:"<<ar<<"\tRaktaron:"<<mennyiseg<<std::endl;
    }
    void setnar(double price){
        ar=price;
    }
    void setmennyiseg(double sum){
        mennyiseg=sum;
    }
    ~Alapanyag(){}

};
class Felkesz :public Hozzavalo{
    ///pairral
    Vektor<std::pair<Alapanyag*,int>> hozzavalok;


public:
    Felkesz(int cikknum,std::string name,double amount, double build, const Vektor<std::pair<Alapanyag*,int>>& hozzavalokvector): Hozzavalo(cikknum,name,amount,build,0),
                                                                                                                     hozzavalok(hozzavalokvector){
        for(size_t i=0;i<hozzavalok.size();i++){
            ar+=(hozzavalok[i].first)->getar()*(hozzavalok[i].second);
        }
    }
    int getcikkszam()const{
        return cikkszam;
    }
    void kiir(){
        std::cout<<"["<<cikkszam<<"]\t"<<nev<<"\tAnyagkoltseg:"<<ar<<"\tRaktaron:"<<mennyiseg<<"\tOsszeszerelesi ido:"<<buildtime<<std::endl;
    }
    double getar()const{
        return ar;
    }
    void setmennyiseg(double sum){
        mennyiseg=sum;
    }
    void setHozzavalok(Vektor<std::pair<Alapanyag*,int>> uj){
        hozzavalok=uj;
    }
    Vektor<std::pair<Alapanyag*,int>> getHozzavalok(){
        return hozzavalok;
    }
    void arfrissit(){
        ar=0;
        for(size_t i=0;i<hozzavalok.size();i++){
            ar+=(hozzavalok[i].first)->getar()*(hozzavalok[i].second);
        }
    }

};
class Termek{
    Vektor<std::pair<Hozzavalo*,int>> hozzavalok;
private:
    int cikkszam;
    std::string nev;
    double mennyiseg;
    double buildtime;
    double eladasiar;
    double koltseg;
public:
    Termek(int cikk,std::string name,double sum,double time,double elad,const Vektor<std::pair<Hozzavalo*,int>>& tarol):
    cikkszam(cikk),nev(name),mennyiseg(sum),buildtime(time),eladasiar(elad),koltseg(0), hozzavalok(tarol){

        for(size_t i=0;i<hozzavalok.size();i++){
            koltseg+=(hozzavalok[i].first)->getar()*hozzavalok[i].second;
        }
    }
    int getcikkszam()const{
        return cikkszam;
    }
    void kiir(){
        std::cout<<"["<<cikkszam<<"]\t"<<nev<<"\tEladasi ar:"<<eladasiar<<"\tKoltseg:"<<koltseg<<"\tRaktaron:"<<mennyiseg<<"\tOsszeszerelesi ido:"<<buildtime<<std::endl;

    }
    void setmennyiseg(double sum){
        mennyiseg=sum;
    }
    void arfrissit(){
        koltseg=0;
        for(size_t i=0;i<hozzavalok.size();i++){
            koltseg+=(hozzavalok[i].first)->getar()*hozzavalok[i].second;
        }
    }
    Vektor<std::pair<Hozzavalo*,int>> getHozzavalok(){
        return hozzavalok;
    }
    double getRaktaron(){
        return mennyiseg;
    }
    double getBuildtime(){
        return buildtime;
    }
    double getEladar(){
        return eladasiar;
    }
    std::string getNev(){
        return nev;
    }


};
struct Par {
    Hozzavalo* hozzavalo;
public:
    int mennyiseg;
    Hozzavalo* getHozzavalo() const {return hozzavalo;}
    Par(Hozzavalo* hozzavalo, int mennyiseg) : hozzavalo(hozzavalo), mennyiseg(mennyiseg) {}

};

#endif //HAZI_CLASSOK_HPP
