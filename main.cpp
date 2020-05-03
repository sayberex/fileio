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

    //----------------------------[ofstream]----------------------------
    ofile.precision(12);
    ofile << idata << endl
          << bdata << endl
          << ddata << endl
          << sdata << endl;
    //----------------------------[ofstream]----------------------------



    //----------------------------[ifstream]----------------------------
    ifile >> _idata
          >> _bdata
          >> _ddata
          >> _sdata;
    //----------------------------[ifstream]----------------------------


    cout.precision(12);
    cout << _idata << endl
         << _bdata << endl
         << _ddata << endl
         << _sdata << endl;



    //----------------------------[fstream]-----------------------------
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
    //----------------------------[fstream]-----------------------------



    //----------------------------[char I/O]-----------------------------
    string ffile2_name("c:\\data3.txt");
    //fstream   ffile2(ffile2_name, std::ios::in | std::ios::out);
    fstream     ffile2;
    bool        bwriteOK=false;
    char ffile2_arr[10] = {0,1,2,3,4,5,6,7,8,9};
    char ffile2_arr_in[10];

    cout << "trying to open file " << ffile2_name << endl;
    ffile2.open(ffile2_name, ios::in | ios::out);
    if (!ffile2.is_open())
    {
        cout << "file " << ffile2_name << " doesn't exist creating file" << endl;
        ffile2.clear();                         //clear all state flags
        ffile2.open(ffile2_name, ios::out);     //create new file
        ffile2.close();
        ffile2.open(ffile2_name, ios::in | ios::out);
    } else
    {

        cout << "file " << ffile2_name << " opened successfully" << endl;
    }

    if (ffile2.is_open())
    {
        //cout << ffile2.rdstate() << endl;
        ffile2 << ffile2_arr[0] << ffile2_arr[1] << ffile2_arr[2] << ffile2_arr[3];
        ffile2.put(ffile2_arr[4]).put(ffile2_arr[5]).put(ffile2_arr[6]).put(ffile2_arr[7]).put(ffile2_arr[8]);
        ffile2.put(ffile2_arr[9]);

        bwriteOK = true;
    } else {
        cerr << "failed to open " << ffile2_name << " for in/out" << endl;
    }

     if (bwriteOK)
     {
         char ch=0;
         int  indx=0;
         ffile2.seekg(ios::beg);
         cout << "ffile2.rdstate() = " << ffile2.rdstate() << endl;
         while (!ffile2.eof())
         {
             cout << ffile2.get() << ' ';
         }


         for (int i = 0; i < sizeof(ffile2_arr_in); i++)
         {

         }
     }
    ffile2.close();
    //---------------------------------------------------------------



    std::cout << "Terminated..." << std::endl;
    return 0;
}
