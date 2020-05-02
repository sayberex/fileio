#include <iostream>
#include <fstream>

using namespace std;

typedef struct
{
    char    chData;
    int     intData;
} TData;

const int       idata = 10;
const bool      bdata = true;
const double    ddata = 0.12345678;
//const TData     dData[2] = {{'a', 100}, {'b', 200}};
const string    sdata = "str data";

      int       _idata;
      bool      _bdata;
      double    _ddata;
//      TData     dData[2] = {{'a', 100}, {'b', 200}};
      string    _sdata;



int main() {
    ofstream    ofile("c:\\data.txt");
    ifstream    ifile("c:\\data.txt");
    fstream     ffile("c:\\data2.txt", std::ios::in | std::ios::out);

    if (!ofile) cerr << "can't open file for output";
    if (!ifile) cerr << "can't open file for inout";
    if (!ffile) cerr << "can't open file for inout/output";

    //---------------------------------------------------------------
    ofile.precision(12);
    ofile << idata << endl
          << bdata << endl
          << ddata << endl
          << sdata << endl;
    //---------------------------------------------------------------



    //---------------------------------------------------------------
    ifile >> _idata
          >> _bdata
          >> _ddata
          >> _sdata;
    //---------------------------------------------------------------


    cout.precision(12);
    cout << _idata << endl
         << _bdata << endl
         << _ddata << endl
         << _sdata << endl;



    //---------------------------------------------------------------
    ffile.precision(12);
    ffile << idata << endl
          << bdata << endl
          << ddata << endl
          << sdata << endl;

    ffile >> _idata
          >> _bdata
          >> _ddata
          >> _sdata;

    cout.precision(12);
    cout << _idata << endl
         << _bdata << endl
         << _ddata << endl
         << _sdata << endl;
    //---------------------------------------------------------------
    std::cout << "Terminated..." << std::endl;
    return 0;
}
