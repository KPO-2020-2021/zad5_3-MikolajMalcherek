#ifndef ELEMENT_SCENY_HH
#define ELEMENT_SCENY_HH

#include <memory>
#include <string>
// Tworzymy klase macierzysta, ktora bedzie klasa wirtualna,z ktorej beda dziedziczyly klasy przeskod oraz dron


class Element_Sceny
{
public:

 // tworzymy wirtualna metode, do ktorej przypisujemy 0, co oznacza ze dla klasy Element_Sceny jest ona "zmyslona" ale inne klasy dziedziczace beda mialy ta metode
 virtual bool sprawdzanie_zderzenia(shared_ptr <Element_Sceny> przedmiot_zderzenia)=0;  


    virtual std::string wysylanie_nazwy() const=0;
    virtual void zapis()=0;
    virtual Vector3D wysylanie_wspol_srodka() const=0;
    virtual double obszar_promienia()=0; // obliczanie obszaru srona, sluzy do stowrzenia funkcji zapobiegania kolizji
};



#endif