#include <iostream>
#include <unistd.h>
#include <thread>
#include <fstream>

using namespace std;

struct Turing
{
  char kryptis;
	char esamas_simbolis;
	char naujas_simbolis;
	string nauja_busena;
  string busena;
};

void Readfromfile(int &veiksmas, int &galvute, string &juosta, Turing T[])
{
    ifstream read("2.txt");
    read >> galvute;
    read >> juosta;
      while (!read.eof())
    {
        read >> T[veiksmas].busena;
        read >> T[veiksmas].esamas_simbolis;
        read >> T[veiksmas].naujas_simbolis;
        read >> T[veiksmas].kryptis;
        read >> T[veiksmas].nauja_busena;
        veiksmas++;
    }
}

void Turingmachine(string bus, int veiksmas, int galvute, string juosta, Turing T[])
{
  while (galvute >= 0)
    {
        for (int i=0; i<veiksmas; i++)
        {
            if(T[i].busena == bus)
            {
                if(T[i].esamas_simbolis == juosta[galvute])
                {
                    if(T[i].naujas_simbolis != '*')
                    {
                        juosta[galvute] = T[i].naujas_simbolis;
                    }
                    if(T[i].kryptis == 'R')
                    {
                        galvute++;
                    }
                    if(T[i].kryptis == 'L')
                    {
                        galvute--;
                    }
                    bus = T[i].nauja_busena;
                    cout << juosta << endl;
                    usleep(30000);
                }
            }
        }
    }
}

int main()
{
    Turing T[100000];
    string juosta, bus;
    bus='0';
    int galvute;
    int veiksmas = 0;

    Readfromfile(veiksmas,galvute,juosta,T);
    thread t1(Turingmachine,bus,veiksmas,galvute,juosta,T);
    t1.join();
    return 0;
}
