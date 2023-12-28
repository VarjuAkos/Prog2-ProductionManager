#include <iostream>
#include "Classok.hpp"
#include "Raktar.hpp"
#include "Pair.hpp"
#include "memtrace.h"
int main() {
    Raktar fo("adatok.txt");

    int utasitas=0;
    do {
        if(utasitas!=6)
            fo.fomenukiir();
        std::cin>>utasitas;
        switch (utasitas) {
            case 1://Keresés
                std::cout<<"---KERESES---"<<std::endl;
                fo.menu_1();
                break;
            case 2://Listázás
                std::cout<<"---LISTAZAS---"<<std::endl;
                fo.menu_2();
                break;
            case 3://Leltar/Hozzaad
                std::cout<<"---HOZZAADAS/RAKTAR MODOSIT---"<<std::endl;
                fo.menu_3();
                break;
            case 4://Összeszerelés
                std::cout<<"---OSSZESZEREL---"<<std::endl;
                fo.menu_4();

                break;
            case 5://Gyártás/Eladás
                fo.menu_5();
                //;
                break;
            case 6://kilépés mentés
                std::cout<<"kilepes mentes"<<std::endl;
                fo.mentes("adatok.txt");
                break;
            default:
                std::cout<<"kilepes mentes"<<std::endl;
                fo.mentes("adatok.txt");
                utasitas=6;
                break;
        }
    } while (utasitas !=6);

    return 0;
}
