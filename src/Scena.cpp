#include "Scena.hh"
#include "Plaskowyz.hh"
#include "lacze_do_gnuplota.hh"
#include "Rampa.hh"
#include "Gora.hh"
#include "Element_Sceny.hh"

using namespace std;

Scena::Scena()
{

    Lacze.ZmienTrybRys(PzG::TR_3D);

    Lacze.UstawZakresY(-500,500);
    Lacze.UstawZakresX(-500,500);
    Lacze.UstawZakresZ(-500,500);

    numer_drona=0;
    numer_elementu=6;
   

    double tablica_wymiarow[3]={1000,1000,0};
    Vector3D wymiary_spodu(tablica_wymiarow);
    spod = new Plaszczyzna(wymiary_spodu,25);

    bool zderzenie=false;
    Vector3D srodek_przeszkody;
    for(int i=0 ; i<4 ; i++)
    {

    srodek_przeszkody[0]=rand()%450-225;
    srodek_przeszkody[1]=rand()%450-225;
    srodek_przeszkody[2]=50;
    Lista_przeszkod.push_front(std::make_shared<Plaskowyz>(srodek_przeszkody, 100, 150 , 100 , "../dat/Plaskowyz1.dat"));

    srodek_przeszkody[0]=rand()%450-225;
    srodek_przeszkody[1]=rand()%450-225;
    srodek_przeszkody[2]=50;
    Lista_przeszkod.push_front(std::make_shared<Gora>(srodek_przeszkody, 150, 80 , 100 , "../dat/Gora1.dat"));
    
    srodek_przeszkody[0]=rand()%450-225;
    srodek_przeszkody[1]=rand()%450-225;
    srodek_przeszkody[2]=50;
    Lista_przeszkod.push_front(std::make_shared<Rampa>(srodek_przeszkody, 230, 150 , 100 , "../dat/Rampa1.dat"));



    


for(std::list<std::shared_ptr<Element_Sceny>>::const_iterator a=Lista_przeszkod.begin() ; a != Lista_przeszkod.end(); a++)
{
               if ((*Lista_przeszkod.begin())->sprawdzanie_zderzenia(*a))
      {
        zderzenie = true;
      }
    
    if (zderzenie)
    {
      i--;
      Lista_przeszkod.erase(Lista_przeszkod.begin());
    }
 
                zderzenie=false;
    }

       
    for(std::list<std::shared_ptr<Element_Sceny>>::const_iterator zmwsk=Lista_przeszkod.begin() ; zmwsk != Lista_przeszkod.end(); zmwsk++)
    {
        Lacze.DodajNazwePliku((*zmwsk)->wysylanie_nazwy().c_str());
        (*zmwsk)->zapis();
        cout << (*zmwsk)->wysylanie_nazwy() << " " << (*zmwsk)->obszar_promienia() << endl;
    } 
}

    Lacze.DodajNazwePliku(spod->wyslij_nazwe().c_str());
    spod->zapisz();

    zderzenie=false;

    for(int i=0; i<ILOSC_DRONOW; i++)
{
    double polozenie[3]={(double)(rand()%900-450),(double)(rand()%900-450),15}; // losujemy pozycje startowa drona
    Lista_dronow.push_front(std::make_shared<Dron>(i, Lacze , Vector3D(polozenie)));

    for (std::list<std::shared_ptr<Element_Sceny>>::const_iterator zmwsk = Lista_przeszkod.begin(); zmwsk != Lista_przeszkod.end(); zmwsk++)
    {
      if ((*Lista_dronow.begin())->sprawdzanie_zderzenia(*zmwsk))
      {
        zderzenie = true;
      }
    }
    if (zderzenie)
    {
      i--;
      Lista_dronow.erase(Lista_dronow.begin());
    }
    else
    {
      Lista_przeszkod.push_front(*Lista_dronow.begin());
      cout << (*Lista_dronow.begin())->wysylanie_nazwy() << " " << (*Lista_dronow.begin())->obszar_promienia() << endl;
      (*Lista_dronow.begin())->zapis();
      numer_drona++;
    }
    zderzenie = false;
}


    Lacze.Rysuj();
}



// interfejs wyswietlajacy sie przy odpaleniu programu
bool Scena::opcje()
{




    std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << std::endl;
    std::cout << "@              Wybierz opcje:              @" << std::endl;
    std::cout << "@    1 -wybierz drona                      @" << std::endl;
    std::cout << "@    2 - dodaj element do sceny            @" << std::endl;
    std::cout << "@    3 - usun element ze sceny             @" << std::endl;
    std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << std::endl;
    int opcja;
    std::cin >> opcja;
    int numer;
    
    switch (opcja)
    {
        case 1:
        {
            for(int i = 0 ; i < (int)Lista_dronow.size();i++)
            {
                cout << i << " lub ";
            }
    std::cin>>numer;
    std::list<std::shared_ptr<Dron>>::const_iterator wsk;
    wsk = Lista_dronow.begin();
    for(int i=0 ; i<numer ; i++)
    {
        wsk++;
    }

    (*wsk)->kierowanie(Lista_przeszkod);
        }
break;
        case 2:
        {
        cout << "Dodawanie elementu do sceny: " << endl;
        cout << "1 - plaskowyz" << endl;
        cout << "2 - gora" << endl;
        cout << "3 - rampa" << endl;
        cin >> numer;
        Vector3D srodek;


    if(numer!=4)
    {
        for(int i=0; i<50 ; i++)
    {
        srodek[0]=rand()%450-225;
        srodek[1]=rand()%450-225;
        srodek[2]=50;
        bool zderzenie = false;
        if(numer==1)
        {
            Lista_przeszkod.push_front(std::make_shared<Plaskowyz>(srodek, 100, 150 , 100 , "../dat/Plaskowyz"+std::to_string(numer_elementu)+".dat"));
        }
        if(numer==2)
        {
            Lista_przeszkod.push_front(std::make_shared<Gora>(srodek, 150, 80 , 100 , "../dat/Gora"+std::to_string(numer_elementu)+".dat"));
        }
        if(numer==3)
        {
            Lista_przeszkod.push_front(std::make_shared<Rampa>(srodek, 230, 150 , 100 , "../dat/Rampa"+std::to_string(numer_elementu)+".dat"));
        }
        numer_elementu++;
         for (std::list<std::shared_ptr<Element_Sceny>>::const_iterator a = Lista_przeszkod.begin(); a != Lista_przeszkod.end(); a++)
        {
          if ((*Lista_przeszkod.begin())->sprawdzanie_zderzenia(*a))
          {
            zderzenie = true;
          }
        }
        if (zderzenie)
        {
          i--;
          Lista_przeszkod.erase(Lista_przeszkod.begin());
        }
        else
        {
          break;
        }
      }
      (*Lista_przeszkod.begin())->zapis();
      Lacze.DodajNazwePliku((*Lista_przeszkod.begin())->wysylanie_nazwy().c_str());
    }
    else
    {
      bool zderzenie = false;
      for (int i = 0; i < 50; i++)
      {
        double pozycja[3] = {(double)(rand() % 440 - 220), (double)(rand() % 440 - 220), 25};

        Lista_dronow.push_front(std::make_shared<Dron>(numer_drona, Lacze, Vector3D(pozycja)));

        for (std::list<std::shared_ptr<Element_Sceny>>::const_iterator a = Lista_przeszkod.begin(); a != Lista_przeszkod.end(); a++)
        {
          if ((*Lista_dronow.begin())->sprawdzanie_zderzenia(*a))
          {
            zderzenie = true;
          }
        }
        if (zderzenie)
        {

          Lista_dronow.erase(Lista_dronow.begin());
        }
        else
        {
          Lista_przeszkod.push_front(*Lista_dronow.begin());
          cout << (*Lista_dronow.begin())->wysylanie_nazwy() << " " << (*Lista_dronow.begin())->obszar_promienia() << endl;
          (*Lista_dronow.begin())->zapis();
          numer_drona++;
          break;
        }
        zderzenie = false;
      }
    }
  }
    //case 2
   
    break;

    case 3:
    {
    int zmienna=0;
    for (std::list<std::shared_ptr<Element_Sceny>>::const_iterator a = Lista_przeszkod.begin(); a != Lista_przeszkod.end(); a++)
    {
      cout << zmienna << ": " << (*a)->wysylanie_nazwy() << endl;
      zmienna++;
    }

    cout << "Podaj numer przeszkody do usuniecia: " << endl;

    int numer_przeszkody;

    cin >> numer_przeszkody;
    std::list<std::shared_ptr<Element_Sceny>>::const_iterator a = Lista_przeszkod.begin();

    for (int j = 0 ; j<numer_przeszkody ; j++)  // przesuwamy sie po elementach listy do momentu spotkania interesujacego nas numeru przeszkody
    {
        a++;
    }
    Lacze.UsunNazwePliku((*a)->wysylanie_nazwy());
    Lista_przeszkod.erase(a); // specjalna funkcja erase 
    }
    break;
}
return true;
}


Scena::~Scena()
{
    free(spod);
}

void Scena::rysowanie()
{
    Lacze.Rysuj();
}


