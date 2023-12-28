//
// Created by varju on 2022.05.01..
//
/*
#ifndef HAZI_PAIR_HPP
#define HAZI_PAIR_HPP
#include <iostream>
//#include "Classok.hpp"
#include "Raktar.hpp"
#include "memtrace.h"
 */
/*
struct Par {
    Hozzavalo* hozzavalo;
public:
    int mennyiseg;
    Hozzavalo* getHozzavalo() const {return hozzavalo;}
    Par(Hozzavalo* hozzavalo, int mennyiseg) : hozzavalo(hozzavalo), mennyiseg(mennyiseg) {}

};

*/
/*
void fomenukiir(){
    std::cout<<"[1]Kereses\n"<<"[2]Listazas\n"<<"[3]Hozzaadas/Raktar modosit\n"<<"[4]Osszeszerel\n"<<"[5]Gyartas/Eladas\n"<<"[6]Mentes es kilepes\n"<<std::endl;
}
void menu_1kiir(){
    std::cout<<"[1]Alapanyag keres\n"<<"[2]Felkesz keres\n"<<"[3]Termek keres\n"<<"[4]Vissza a fomenube"<<std::endl;
}
void menu1alapanyagkeres(Raktar main){
    std::cout<<"Cikkszam:"<<std::endl;
    int cikk=0;
    std::cin>>cikk;
    if(main.alapanyagkeres(cikk)== nullptr)
        std::cout<<"Nincs ilyen cikkszamu alapanyag."<<std::endl;
    else
        main.alapanyagkeres(cikk)->kiir();
}
void menu1felkeszkeres(Raktar main){
    std::cout<<"Cikkszam:"<<std::endl;
    int cikk=0;
    std::cin>>cikk;
    if(main.felkeszkeres(cikk)== nullptr)
        std::cout<<"Nincs ilyen cikkszamu felkesz termek."<<std::endl;
    else
        main.felkeszkeres(cikk)->kiir();

}
void menu1termekkeres(Raktar main){
    std::cout<<"Cikkszam:"<<std::endl;
    int cikk=0;
    std::cin>>cikk;
    if(main.termekkeres(cikk)== nullptr)
        std::cout<<"Nincs ilyen cikkszamu termek."<<std::endl;
    else
        main.termekkeres(cikk)->kiir();
}

void menu_1(const Raktar& main){
    int utasitas=0;

    do {
            menu_1kiir();
            std::cin>>utasitas;
        switch (utasitas) {
            case 1://Alapanyag keres
                menu1alapanyagkeres(main);
                break;
            case 2://Felkesz keres
                menu1felkeszkeres(main);
                break;
            case 3://Termek keres
                menu1termekkeres(main);
                break;
            case 4://Vissza a fömenube
                break;
            default:
                utasitas=4;
                break;
        }
    } while (utasitas !=4);

}
void menu_2kiir(){
    std::cout<<"[1]Minden listaz\n"<<"[2]Alapanyag listaz\n"<<"[3]Felkesz listaz\n"<<"[4]Termek listaz\n"<<"[5]Vissza a fomenube"<<std::endl;
}

void menu_2(Raktar main){
    int utasitas=0;
    do {
        menu_2kiir();
        std::cin>>utasitas;
        switch (utasitas) {
            case 1://Minden listaz
                main.alapanyaglistaz();
                main.felkeszlistaz();
                main.termeklistaz();
                break;
            case 2://Alapanyag listaz
                main.alapanyaglistaz();
                break;
            case 3://Felkesz listaz
                main.felkeszlistaz();
                break;
            case 4://Termek listaz
                main.termeklistaz();
                break;
            case 5://Vissza a fomenube
                break;
            default:
                utasitas=5;
                break;
        }
    } while (utasitas !=5);
}
void hozzaadkiir(){
    std::cout<<"[1]Alapanyag hozzad\n"<<"[2]Felkesz hozzaad\n"<<"[3]Termek hozzaad\n"<<"[4]Vissza"<<std::endl;
}
void alapanyaghozzaad(Raktar& main){
    std::cout<<"---ALAPANYAG HOZZAD---\nCikkszam:"<<std::endl;
    int cikk=0;
    std::cin>>cikk;
    if(main.alapanyagkeres(cikk)== nullptr||main.felkeszkeres(cikk)== nullptr|| main.termekkeres(cikk) == nullptr) {
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
        main.getAcim().push_back(uj);
        ///nem teszi bele
        std::cout<<main.getAcim().size();
    }
    else
        std::cout<<"Mar letezik ilyen cikkszam."<<std::endl;


}
void hozzaad(Raktar main){
    int utasitas=0;
    do {
        hozzaadkiir();
        std::cin>>utasitas;
        switch (utasitas) {
            case 1://Alapanyag hozzad
                alapanyaghozzaad(main);
                break;
            case 2://Felkesz hozzaad
                main.alapanyaglistaz();
                break;
            case 3://Termek hozzaad
                main.felkeszlistaz();
            case 4://vissza

                break;
            default:
                utasitas=4;
                break;
        }
    } while (utasitas !=4);

}
void menu_3kiir(){
    std::cout<<"[1]Hozzad\n"<<"[2]Raktar modosit/-ar,-mennyiseg\n"<<"[3]Vissza a fomenube"<<std::endl;

}
void menu_3(Raktar main){
    int utasitas=0;
    do {
        menu_3kiir();
        std::cin>>utasitas;
        switch (utasitas) {
            case 1://Hozzaad
                hozzaad(main);
                break;
            case 2://Raktar modosit/-ar,-mennyiseg
                main.alapanyaglistaz();
                break;
            case 3://Vissza a fomenube
                break;
            default:
                utasitas=3;
                break;
        }
    } while (utasitas !=3);
}
*/
//#endif //HAZI_PAIR_HPP
