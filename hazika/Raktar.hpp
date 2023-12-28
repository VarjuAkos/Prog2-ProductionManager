//
// Created by varju on 2022.05.01..
//

#ifndef HAZI_RAKTAR_HPP
#define HAZI_RAKTAR_HPP
#include "Vektor.hpp"
#include <iostream>
#include <fstream>
#include <math.h>
//#include "Pair.hpp"
#include "memtrace.h"

class Raktar{
private:
    Vektor<Termek*> termektarolo;
    Vektor<Felkesz*> felkesztarolo;
    Vektor<Alapanyag*> alapanyagtarolo;
public:
    ///eddig ez jo
    Raktar(char const * filename){
        std::ifstream is(filename);
        if(!is.is_open())
            throw "File megnyitasa sikertelen\n";
        int dbalapanyag;
        is>>dbalapanyag;
        for(int i=0;i<dbalapanyag;i++){
            ///hogy adok erteket a alapanyagtarolonak?
            int cikk; is>>cikk;
            std::string nev; is>>nev;
            double mennyiseg; is>>mennyiseg;
            double ar;is>>ar;
            auto* uj = new Alapanyag (cikk,nev,mennyiseg,ar);
            alapanyagtarolo.push_back(uj);
        }
        int dbfelkesz; is>>dbfelkesz;
        for(int i=0;i<dbfelkesz;i++){
            int cikk;is>>cikk;
            std::string nev;is>>nev;
            double mennyiseg; is>>mennyiseg;
            double buildtime; is>>buildtime;
            Vektor<std::pair<Alapanyag*,int>> uj;
            size_t meret; is>>meret;
            for(size_t i=0;i<meret;i++){
                int cikk; is>>cikk;
                int db;is>>db;
                std::pair<Alapanyag*,int> ujtag(alapanyagkeres(cikk),db);
                uj.push_back(ujtag);
            }
            auto * ujfelkesz=new Felkesz(cikk,nev,mennyiseg,buildtime,uj);
            felkesztarolo.push_back(ujfelkesz);
        }
        int dbtermek; is>>dbtermek;
        for(int i=0;i<dbtermek;i++){
            int cikk;is>>cikk;
            std::string name; is>>name;
            double mennyiseg;is>>mennyiseg;
            double buildtime;is>>buildtime;
            double eladar;is>>eladar;
            Vektor<std::pair<Hozzavalo*,int>> uj;
            size_t meret;is>>meret;
            for(size_t i=0;i<meret;i++){
                int cikk; is>>cikk;
                int db;is>>db;
                ///kene olyan tagfv ami hozzavalo* al ter vissza
                std::pair<Hozzavalo*,int> ujtag(hozzavalokeres(cikk),db);
                uj.push_back(ujtag);
            }
            auto *ujtermek=new Termek(cikk,name,mennyiseg,buildtime,eladar,uj);
            termektarolo.push_back(ujtermek);
        }
        ///bezar
        is.close();
    }
    ~Raktar(){
        for(size_t i=0;i<termektarolo.size();i++)
            delete termektarolo[i];
        for(size_t i=0;i<felkesztarolo.size();i++)
            delete felkesztarolo[i];
        for(size_t i=0;i<alapanyagtarolo.size();i++)
            delete alapanyagtarolo[i];
    }

    void mentes(char const * filename){
        std::ofstream os(filename);
        if(!os.is_open())
            throw "File megnyitasa sikertelen\n";
        os<<alapanyagtarolo.size()<<std::endl;
        for(size_t i=0;i<alapanyagtarolo.size();i++){
            os<<alapanyagtarolo[i]->getcikkszam()<<" "<<alapanyagtarolo[i]->getNev()<<" "<<alapanyagtarolo[i]->getRaktaron()<<" "<<alapanyagtarolo[i]->getar()<<std::endl;
        }
        os<<felkesztarolo.size()<<std::endl;
        for(size_t i=0;i<felkesztarolo.size();i++){
            os<<felkesztarolo[i]->getcikkszam()<<" "<<felkesztarolo[i]->getNev()<<" "<<felkesztarolo[i]->getRaktaron()<<" "<<felkesztarolo[i]->getBuildtime()
            <<" "<<felkesztarolo[i]->getHozzavalok().size();
            for(size_t j=0;j<felkesztarolo[i]->getHozzavalok().size();j++)
                os<<" "<<felkesztarolo[i]->getHozzavalok()[j].first->getCikk()<<" "<<felkesztarolo[i]->getHozzavalok()[j].second;
            os<<std::endl;
        }
        os<<termektarolo.size()<<std::endl;
        for(size_t i=0;i<termektarolo.size();i++){
            os<<termektarolo[i]->getcikkszam()<<" "<<termektarolo[i]->getNev()<<" "<<termektarolo[i]->getRaktaron()
            <<" "<<termektarolo[i]->getBuildtime()<<" "<<termektarolo[i]->getEladar()<<" "<<termektarolo[i]->getHozzavalok().size();
            for(size_t j=0;j<termektarolo[i]->getHozzavalok().size();j++)
                os<<" "<<termektarolo[i]->getHozzavalok()[j].first->getCikk()<<" "<<termektarolo[i]->getHozzavalok()[j].second;
            os<<std::endl;
        }
        os.close();
    }

    Vektor<Alapanyag*> getAcim(){
        return alapanyagtarolo;
    }
    Vektor<Termek*> getTcim(){
        return termektarolo;
    }
    Vektor<Felkesz*> getFcim(){
        return felkesztarolo;
    }
    ///KERESÉS
    Termek* termekkeres(int cikkszam){
        for(size_t i=0;i<termektarolo.size();i++){
            if((termektarolo[i])->getcikkszam()==cikkszam)
                return termektarolo[i];
        }
        return nullptr;
    }
    Felkesz* felkeszkeres(int cikkszam){
        for(size_t i=0;i<felkesztarolo.size();i++){
            if((felkesztarolo[i])->getcikkszam()==cikkszam)
                return felkesztarolo[i];
        }
        return nullptr;
    }
    Alapanyag* alapanyagkeres(int cikkszam){
        for(size_t i=0;i<alapanyagtarolo.size();i++){
            if((alapanyagtarolo[i])->getcikkszam()==cikkszam)
                return alapanyagtarolo[i];
        }
        return nullptr;
    }
    Hozzavalo* hozzavalokeres(int cikkszam){
        if(alapanyagkeres(cikkszam)!= nullptr)
            return alapanyagkeres(cikkszam);
        else if(felkeszkeres(cikkszam)!= nullptr)
            return felkeszkeres(cikkszam);
        else
            return nullptr;

    }
    ///Listaz
    void alapanyaglistaz(){
        for(size_t i=0;i<alapanyagtarolo.size();i++){
            alapanyagtarolo[i]->kiir();
        }
    }
    void felkeszlistaz(){
        for(size_t i=0;i<felkesztarolo.size();i++){
            felkesztarolo[i]->kiir();
        }
    }
    void termeklistaz(){
        for(size_t i=0;i<termektarolo.size();i++){
            termektarolo[i]->kiir();
        }
    }
    ///----------------------------------------------------------------------------
    static void fomenukiir(){
        std::cout<<"[1]Kereses\n"<<"[2]Listazas\n"<<"[3]Hozzaadas/Raktar modosit\n"<<"[4]Osszeszerel\n"<<"[5]Gyartas/Eladas\n"<<"[6]Mentes es kilepes\n"<<std::endl;
    }
    static void menu_1kiir(){
        std::cout<<"[1]Alapanyag keres\n"<<"[2]Felkesz keres\n"<<"[3]Termek keres\n"<<"[4]Vissza a fomenube"<<std::endl;
    }
    void menu1alapanyagkeres(){
        std::cout<<"Cikkszam:"<<std::endl;
        int cikk=0;
        std::cin>>cikk;
        if(alapanyagkeres(cikk)== nullptr)
            std::cout<<"Nincs ilyen cikkszamu alapanyag."<<std::endl;
        else
            alapanyagkeres(cikk)->kiir();
    }
    void menu1felkeszkeres(){
        std::cout<<"Cikkszam:"<<std::endl;
        int cikk=0;
        std::cin>>cikk;
        if(felkeszkeres(cikk)== nullptr)
            std::cout<<"Nincs ilyen cikkszamu felkesz termek."<<std::endl;
        else {
            felkeszkeres(cikk)->kiir();
            std::cout<<"Szukseges alapanyagok:\n";
            for(size_t i=0;i< felkeszkeres(cikk)->getHozzavalok().size();i++){
                std::cout<<"["<<felkeszkeres(cikk)->getHozzavalok()[i].first->getcikkszam()<<"]\t"<<
                felkeszkeres(cikk)->getHozzavalok()[i].first->getNev()<<"\tFelhasznalt mennyiseg:"<<
                felkeszkeres(cikk)->getHozzavalok()[i].second<<std::endl;
            }

        }
    }
    void menu1termekkeres(){
        std::cout<<"Cikkszam:"<<std::endl;
        int cikk=0;
        std::cin>>cikk;
        auto termek= termekkeres(cikk);
        if(termek== nullptr)
            std::cout<<"Nincs ilyen cikkszamu termek."<<std::endl;
        else{
            termekkeres(cikk)->kiir();
            std::cout<<"Szukseges alapanyagok:\n";
            for(size_t i=0;i<termek->getHozzavalok().size();i++){
                std::cout<<"["<<termek->getHozzavalok()[i].first->getCikk()<<"]\t"<<
                termek->getHozzavalok()[i].first->getNev()<<"\tFelhasznalt mennyiseg:"<<
                termek->getHozzavalok()[i].second<<std::endl;
            }
        }
    }
    void menu_1(){
        int utasitas=0;
        do {
            menu_1kiir();
            std::cin>>utasitas;
            switch (utasitas) {
                case 1://Alapanyag keres
                    menu1alapanyagkeres();
                    break;
                case 2://Felkesz keres
                    menu1felkeszkeres();
                    break;
                case 3://Termek keres
                    menu1termekkeres();
                    break;
                case 4://Vissza a fömenube
                    break;
                default:
                    utasitas=4;
                    break;
            }
        } while (utasitas !=4);

    }
    static void menu_2kiir(){
        std::cout<<"[1]Minden listaz\n"<<"[2]Alapanyag listaz\n"<<"[3]Felkesz listaz\n"<<"[4]Termek listaz\n"<<"[5]Vissza a fomenube"<<std::endl;
    }

    void menu_2(){
        int utasitas=0;
        do {
            menu_2kiir();
            std::cin>>utasitas;
            switch (utasitas) {
                case 1://Minden listaz
                    std::cout<<"Alapanyagok:------------------------------------"<<std::endl;
                    alapanyaglistaz();
                    std::cout<<"Felkeszek:--------------------------------------"<<std::endl;
                    felkeszlistaz();
                    std::cout<<"Termekek:---------------------------------------"<<std::endl;
                    termeklistaz();
                    break;
                case 2://Alapanyag listaz
                    alapanyaglistaz();
                    break;
                case 3://Felkesz listaz
                    felkeszlistaz();
                    break;
                case 4://Termek listaz
                    termeklistaz();
                    break;
                case 5://Vissza a fomenube
                    break;
                default:
                    utasitas=5;
                    break;
            }
        } while (utasitas !=5);
    }
    static void hozzaadkiir(){
        std::cout<<"[1]Alapanyag hozzad\n"<<"[2]Felkesz hozzaad\n"<<"[3]Termek hozzaad\n"<<"[4]Vissza"<<std::endl;
    }
    void alapanyaghozzaad(){
        std::cout<<"---ALAPANYAG HOZZAD---\nCikkszam:"<<std::endl;
        int cikk=0;
        std::cin>>cikk;
        if(alapanyagkeres(cikk)== nullptr||felkeszkeres(cikk)== nullptr|| termekkeres(cikk) == nullptr) {
            std::cout<<"Eddig jo\n"<<std::endl;
            std::cout << "Neve:";
            std::string nev;
            std::cin>>nev;
            double mennyiseg=0,ar=0;
            std::cout << "Raktaron/mennyiseg:\n";
            std::cin>>mennyiseg;
            std::cout << "Ar\n";
            std::cin>>ar;
            auto *uj=new Alapanyag(cikk,nev,mennyiseg,ar);
            alapanyagtarolo.push_back(uj);
            ///nem teszi bele
            std::cout<<getAcim().size();
        }
        else
            std::cout<<"Mar letezik ilyen cikkszam."<<std::endl;


    }
    void felkeszhozzaad(){
        std::cout<<"---FELKESZ HOZZAD---\nCikkszam:"<<std::endl;
        int cikk=0;
        std::cin>>cikk;
        if(alapanyagkeres(cikk)== nullptr||felkeszkeres(cikk)== nullptr|| termekkeres(cikk) == nullptr){
            std::cout << "Neve:";
            std::string nev;
            std::cin>>nev;
            double mennyiseg;
            std::cout << "Raktaron/mennyiseg:\n";
            std::cin>>mennyiseg;
            std::cout << "Osszeszerelesi ido:\n";
            double buildtime;
            std::cin>>buildtime;
            Vektor<std::pair<Alapanyag*,int>> uj;
            auto *ujfelkesz=new Felkesz(cikk,nev,mennyiseg,buildtime,uj);
            felkesztarolo.push_back(ujfelkesz);
        }
        else
            std::cout<<"Mar letezik ilyen cikkszam."<<std::endl;
    }
    void termekhozzaad(){
        std::cout<<"---TERMEK HOZZAD---\nCikkszam:"<<std::endl;
        int cikk=0;
        std::cin>>cikk;
        if(alapanyagkeres(cikk)== nullptr||felkeszkeres(cikk)== nullptr|| termekkeres(cikk) == nullptr){
            std::cout << "Neve:";
            std::string nev;
            std::cin>>nev;
            double mennyiseg;
            std::cout << "Raktaron/mennyiseg:\n";
            std::cin>>mennyiseg;
            std::cout << "Osszeszerelesi ido:\n";
            double buildtime;
            std::cin>>buildtime;
            std::cout<<"Eladasi ar:\n";
            double elad;
            std::cin>>elad;
            Vektor<std::pair<Hozzavalo*,int>> uj;
            auto* ujtermek=new Termek(cikk,nev,mennyiseg,buildtime,elad,uj);
            termektarolo.push_back(ujtermek);
        }
        else
            std::cout<<"Mar letezik ilyen cikkszam."<<std::endl;
    }
    void hozzaad(){
        int utasitas=0;
        do {
            hozzaadkiir();
            std::cin>>utasitas;
            switch (utasitas) {
                case 1://Alapanyag hozzad
                    alapanyaghozzaad();
                    break;
                case 2://Felkesz hozzaad
                    felkeszhozzaad();
                    break;
                case 3://Termek hozzaad
                    termekhozzaad();
                case 4://vissza
                    break;
                default:
                    utasitas=4;
                    break;
            }
        } while (utasitas !=4);

    }
    static void menu_3kiir(){
        std::cout<<"[1]Hozzad\n"<<"[2]Ar modosit\n"<<"[3]Raktar modosit\n"<<"[4]Vissza a fomenube"<<std::endl;
    }
    void modosit_ar(){
        alapanyaglistaz();
        std::cout<<"---AR MODOSIT---\n"<<std::endl;
        std::cout<<"Cikkszam:\n";
        int cikk=0;
        std::cin>>cikk;
        if(alapanyagkeres(cikk)== nullptr)
            std::cout<<"Nincs ilyen cikkszamu alapanyag\n";
        else{
            std::cout<<"Uj ar:\n";
            double ujar;
            std::cin>>ujar;
            alapanyagkeres(cikk)->setnar(ujar);
            std::cout<<"---AR MODOSITVA---\n"<<std::endl;
            ///minden hozza kapcsolodo fristese
            for(size_t i=0;i<felkesztarolo.size();i++){
                felkesztarolo[i]->arfrissit();
            }
            for(size_t i=0;i<termektarolo.size();i++){
                termektarolo[i]->arfrissit();
            }
        }
    }
    static int cikkbeolvas(){
        std::cout<<"Cikkszam:\n";
        int cikk;
        std::cin>>cikk;
        return cikk;
    }
    void alapanyagmennyisegmod(){
        alapanyaglistaz();
        int cikk=cikkbeolvas();
        if(alapanyagkeres(cikk)!= nullptr) {
            double ujmenny;
            std::cout << "Uj mennyiseg/raktaron:\n";
            std::cin >> ujmenny;
            alapanyagkeres(cikk)->setmennyiseg(ujmenny);
        }
        else
            std::cout<<"Nincs ilyen cikkszamu alapanyag\n";
    }
    void felkeszmennyisegmod(){
        felkeszlistaz();
        int cikk=cikkbeolvas();
        if(felkeszkeres(cikk)!= nullptr) {
            double ujmenny;
            std::cout << "Uj mennyiseg/raktaron:\n";
            std::cin >> ujmenny;
            felkeszkeres(cikk)->setmennyiseg(ujmenny);
        }
        else
            std::cout<<"Nincs ilyen cikkszamu felkesz\n";

    }
    void termekmennyisegmod(){
        termeklistaz();
        int cikk=cikkbeolvas();
        if(termekkeres(cikk)!= nullptr) {
            double ujmenny;
            std::cout << "Uj mennyiseg/raktaron:\n";
            std::cin >> ujmenny;
            termekkeres(cikk)->setmennyiseg(ujmenny);
        }
        else
            std::cout<<"Nincs ilyen cikkszamu termek\n";
    }
    ///kajak nincs kedvem megirni
    void modosit_mennyiseg(){
        int utasitas=0;
        do {
            std::cout<<"---RAKTAR MODOSIT---\n";
            std::cout<<"[1]Alapanyag mennyisege modosit\n"<<"[2]Felkesz mennyisege modosit\n"<<"[3]Termek mennyisege modosit\n"<<"[4]Vissza"<<std::endl;
            std::cin>>utasitas;
            switch (utasitas) {
                case 1://Alapanyag modosit
                    alapanyagmennyisegmod();
                    break;
                case 2://Felkesz modosit
                    felkeszmennyisegmod();
                    break;
                case 3://Termek modosit
                    termekmennyisegmod();
                    break;
                case 4://Vissza a fomenube
                    break;
                default:
                    utasitas=4;
                    break;
            }
        } while (utasitas !=4);
    }
    void menu_3(){
        int utasitas=0;
        do {
            menu_3kiir();
            std::cin>>utasitas;
            switch (utasitas) {
                case 1://Hozzaad
                    hozzaad();
                    break;
                case 2://Raktar modosit/-ar
                    modosit_ar();
                    break;
                case 3://Raktar modosit/-mennyiseg
                    modosit_mennyiseg();
                    break;
                case 4://Vissza a fomenube
                    break;
                default:
                    utasitas=4;
                    break;
            }
        } while (utasitas !=4);
    }
    static void menu_4kiir(){
        std::cout<<"[1]Felkesz osszeszerel\n"<<"[2]Termek osszeszerel\n"<<"[3]Vissza"<<std::endl;
    }
    ///ez nem müködik
    void felkeszosszeszrel(){
        std::cout<<"---FELKESZ OSSZESZEREL---\n"<<std::endl;
        std::cout<<"Felkesz cikkszama:"<<std::endl;
        int cikk;
        std::cin>>cikk;
        if(felkeszkeres(cikk)!= nullptr){
            std::cout<<"Alapanyagok\n";
            alapanyaglistaz();
            auto felkesz= felkeszkeres(cikk);
            ///törlöm aztan ujra megadom
            felkesz->getHozzavalok().clear();
            ///problemas lehet!!Memoria szivargas
            std::cout<<"Hany alapanyagbol keszul el a felkesz:\n";
            int db; std::cin>>db;
            for(int i=0;i<db;i++){
                std::cout<<"Cikk:\n";
                int alapcikk;std::cin>>alapcikk;
                std::cout<<"Szukseges mennyiseg:\n";
                int mennyiseg; std::cin>>mennyiseg;
                auto *uj=new std::pair<Alapanyag*,int>(alapanyagkeres(alapcikk),mennyiseg);
                felkesz->getHozzavalok().push_back(*uj);
            }
            felkesz->arfrissit();

        }
        else
            std::cout<<"Nincs ilyen cikkszamu felkesz\n";
    }
    void termekosszeszerel(){


    }

    void menu_4(){
        int utasitas=0;
        do {
            menu_4kiir();
            std::cin>>utasitas;
            switch (utasitas) {
                case 1://Felkesz osszeszerel
                    felkeszosszeszrel();
                    break;
                case 2://Termek osszeszerel
                    termekosszeszerel();
                    break;
                case 3://Vissza a fomenube
                    break;
                default:
                    utasitas=3;
                    break;
            }
        } while (utasitas !=3);
    }
    static void menu_5kiir(){
        std::cout<<"---GYARTAS/ELADAS---"<<std::endl;
        std::cout<<"[1]Termek gyartas\n"<<"[2]Felkesz gyartas\n"<<"[3]Termek elad\n"<<"[4]Vissza"<<std::endl;
    }
    static void gyart(double dbszam,Termek *termek,double *tomb,size_t meret){
        termek->setmennyiseg(termek->getRaktaron()+dbszam);
        for(size_t i=0;i<termek->getHozzavalok().size();i++){
            termek->getHozzavalok()[i].first->setRaktaron(termek->getHozzavalok()[i].first->getRaktaron()-tomb[i]);
        }
    }
    static void gyartfelkesz(double dbszam,Felkesz *termek,double *tomb,size_t meret) {
        termek->setmennyiseg(termek->getRaktaron() + dbszam);
        for (size_t i = 0; i < termek->getHozzavalok().size(); i++) {
            termek->getHozzavalok()[i].first->setRaktaron(termek->getHozzavalok()[i].first->getRaktaron() - tomb[i]);
        }
    }
    static void anyagkoltsegkiir(Termek* termek,double *tomb,double db){
        std::cout<<"Anyagkoltseg:"<<std::endl;
        for(size_t i=0;i<termek->getHozzavalok().size();i++) {
            tomb[i] = db * termek->getHozzavalok()[i].second;
            std::cout << "[" << termek->getHozzavalok()[i].first->getCikk() << "]\t"<< termek->getHozzavalok()[i].first->getNev() << "\t\tFelhasznalt:" << tomb[i]
                      <<"="<<db<<"*"<<tomb[i]/db<<"\tRaktaron:"<<
                      termek->getHozzavalok()[i].first->getRaktaron();
            if((termek->getHozzavalok()[i].first->getRaktaron()-tomb[i])<0)
                std::cout<<"\tHianyzik:"<<abs(termek->getHozzavalok()[i].first->getRaktaron()-tomb[i])<< std::endl;
            else
                std::cout<<"\tHianyzik:"<<"0"<< std::endl;
        }
    }
    static void anyagkoltsegkiir2(Felkesz* felkesz,double* tomb,double db){
        std::cout<<"Anyagkoltseg:"<<std::endl;
        for(size_t i=0;i<felkesz->getHozzavalok().size();i++) {
            tomb[i] = db * felkesz->getHozzavalok()[i].second;
            std::cout << "[" << felkesz->getHozzavalok()[i].first->getCikk() << "]\t"<< felkesz->getHozzavalok()[i].first->getNev() << "\t\tFelhasznalt:" << tomb[i]
            <<"="<<db<<"*"<<tomb[i]/db<<"\tRaktaron:"<<
            felkesz->getHozzavalok()[i].first->getRaktaron();
            if((felkesz->getHozzavalok()[i].first->getRaktaron()-tomb[i])<0)
                std::cout<<"\tHianyzik:"<<abs(felkesz->getHozzavalok()[i].first->getRaktaron()-tomb[i])<< std::endl;
            else
                std::cout<<"\tHianyzik:"<<"0"<< std::endl;
        }
    }
    static void szuksegeskiir(Termek* termek,double *tomb){
        std::cout<<"Szuksegesek:"<<std::endl;
        for(size_t i=0;i<termek->getHozzavalok().size();i++){
            if((termek->getHozzavalok()[i].first->getRaktaron()-tomb[i])<0){
                std::cout<<"["<<termek->getHozzavalok()[i].first->getCikk()<<"]\t"<<termek->getHozzavalok()[i].first->getNev()<<"\tHianyzik:"
                         <<abs(termek->getHozzavalok()[i].first->getRaktaron()-tomb[i])<<"\tFt/egyseg:"<<termek->getHozzavalok()[i].first->getar()<<
                         "\tOsszesen:"<<abs(termek->getHozzavalok()[i].first->getRaktaron()-tomb[i])*termek->getHozzavalok()[i].first->getar()<<std::endl;
            }
            else
                i++;
        }
    }
    static void szuksegeskiir2(Felkesz* termek,double *felhasznal){
        std::cout<<"Szuksegesek:"<<std::endl;
        for(size_t i=0;i<termek->getHozzavalok().size();i++){
            if((termek->getHozzavalok()[i].first->getRaktaron()-felhasznal[i])<0){
                std::cout<<"["<<termek->getHozzavalok()[i].first->getCikk()<<"]\t"<<termek->getHozzavalok()[i].first->getNev()<<"\tHianyzik:"
                         <<abs(termek->getHozzavalok()[i].first->getRaktaron()-felhasznal[i])<<"\tFt/egyseg:"<<termek->getHozzavalok()[i].first->getar()<<
                         "\tOsszesen:"<<abs(termek->getHozzavalok()[i].first->getRaktaron()-felhasznal[i])*termek->getHozzavalok()[i].first->getar()<<std::endl;
            }
            else
                i++;
        }
    }
    void termekgyartas(){
        std::cout<<"---TERMEK GYARTAS---"<<std::endl;
        termeklistaz();
        std::cout<<"Cikkszam:\n";
        int cikk;std::cin>>cikk;
        if(termekkeres(cikk)!= nullptr){
            std::cout<<"Gyartani kivant mennyiseg:"<<std::endl;
            double db;std::cin>>db;
            auto termek= termekkeres(cikk);
            ///anyagkoltseg kiirasa
            double tomb[termek->getHozzavalok().size()];
            anyagkoltsegkiir(termek,tomb,db);
            ///Hianyzok kiirasa
            szuksegeskiir(termek,tomb);
            std::cout<<"Beszerzi:\n[1]Igen\n[2]Nem\n";
            int utasitas; std::cin>>utasitas;
            double koltseg=0;
            double munkaigeny=0;
            if(utasitas==1){
                if(utasitas==1) {
                    for (size_t i = 0; i < termek->getHozzavalok().size(); i++) {
                        if ((termek->getHozzavalok()[i].first->getRaktaron()-tomb[i]) < 0) {
                            koltseg += abs((termek->getHozzavalok()[i].first->getRaktaron()-tomb[i]) *termek->getHozzavalok()[i].first->getar());
                            termek->getHozzavalok()[i].first->setRaktaron(tomb[i]);
                        }
                        munkaigeny += termek->getHozzavalok()[i].first->getBuildtime() * db;
                    }
                }
            }
            ///itt pedig gyartunk
            gyart(db,termek,tomb,termek->getHozzavalok().size());
            munkaigeny+=termek->getBuildtime()*db;
            std::cout<<"Koltseg:"<<koltseg<<"Ft"<<std::endl;
            std::cout<<"Szukseges munkaido:"<<munkaigeny<<"perc"<<std::endl;
        }else
            std::cout<<"Nincs ilyen cikkszamu Termek\n";
    }
    void felkeszgyartas(){
        std::cout<<"---FELKESZ GYARTAS---"<<std::endl;
        felkeszlistaz();
        std::cout<<"Cikkszam:"<<std::endl;
        int cikk; std::cin>>cikk;
        if(felkeszkeres(cikk)!= nullptr){
            std::cout<<"Gyartani kivant mennyiseg:"<<std::endl;
            double db;std::cin>>db;
            auto felkesz= felkeszkeres(cikk);
            double tomb[felkesz->getHozzavalok().size()];
            anyagkoltsegkiir2(felkesz,tomb,db);
            szuksegeskiir2(felkesz,tomb);
            std::cout<<"Beszerzi:\n[1]Igen\n[2]Nem\n";
            int utasitas; std::cin>>utasitas;
            double koltseg=0;
            double munkaigeny=0;
            //itt szamol
            if(utasitas==1) {
                for (size_t i = 0; i < felkesz->getHozzavalok().size(); i++) {
                    if ((felkesz->getHozzavalok()[i].first->getRaktaron()-tomb[i]) < 0) {
                        koltseg += abs((felkesz->getHozzavalok()[i].first->getRaktaron()-tomb[i]) *felkesz->getHozzavalok()[i].first->getar());
                        felkesz->getHozzavalok()[i].first->setRaktaron(tomb[i]);
                    }
                    munkaigeny += felkesz->getHozzavalok()[i].first->getBuildtime() * db;
                }
            }
            gyartfelkesz(db,felkesz,tomb,felkesz->getHozzavalok().size());
            munkaigeny+=felkesz->getBuildtime()*db;
            std::cout<<"Koltseg:"<<koltseg<<"Ft"<<std::endl;
            std::cout<<"Szukseges munkaido:"<<munkaigeny<<"perc"<<std::endl;
        }else
            std::cout<<"Nincs ilyen cikkszamu felkesz"<<std::endl;
    }
    void elad(){
        std::cout<<"---ELAD---\nCikkszam:"<<std::endl;
        termeklistaz();
        int cikk; std::cin>>cikk;
        auto termek= termekkeres(cikk);
        if(termek!= nullptr) {
            termek->kiir();
            std::cout << "Eladni kivant mennyiseg:\n";
            double elad;
            std::cin >> elad;
            if (elad > termek->getRaktaron())
                std::cout << "Sikertelen, nincs ennyi a raktaron" << std::endl;
            else {
                termek->setmennyiseg(termek->getRaktaron() - elad);
                std::cout<<"Sikeres eladas.\tBevetel:"<<elad*termek->getEladar()<<std::endl;
            }
        }else
            std::cout<<"Nincs ilyen cikkszamu termek"<<std::endl;
    }
    void menu_5(){
        int utasitas=0;
        do {
            menu_5kiir();
            std::cin>>utasitas;
            switch (utasitas) {
                case 1://Termek gyart
                    termekgyartas();
                    break;
                case 2://felkesz gyart
                    felkeszgyartas();
                    break;
                case 3://elad
                elad();
                    break;
                case 4://Vissza a fomenube
                    break;
                default:
                    utasitas=4;
                    break;
            }
        } while (utasitas !=4);
    }
};
#endif //HAZI_RAKTAR_HPP
