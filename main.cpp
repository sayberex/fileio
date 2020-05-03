#include <iostream>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <array>
#include <vector>

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



    cout << endl << "----------------------------[char I/O]-----------------------------" << endl;
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
             //do not forget also about peek wich extracts sym but do not increment input stream indicator
             cout << ffile2.get() << ' ';
         }


         for (int i = 0; i < sizeof(ffile2_arr_in); i++)
         {

         }
     }
    ffile2.close();
    cout << endl << "----------------------------[char I/O]-----------------------------" << endl;



    cout << endl << "----------------------------[bulk I/O]-----------------------------" << endl;
    string ffile3_name("c:\\data4.txt");
    fstream   ffile3(ffile3_name, std::ios::in | std::ios::out);
    char ffile3_arr[10] = {0,1,2,3,4,5,6,7,8,9};
    char ffile3_arr_in[10] = {0,0,0,0,0,0,0,0,0,0};;

    auto print_ffile3_arr_in = [&](){
        for (int i = 0; i < sizeof(ffile3_arr_in); i++) { cout << char(ffile3_arr_in[i] /*+ 0x30*/) << ' ';}
        cout << endl;
    };

    if(!ffile3) cerr << "failed to open " << ffile3_name << endl;

    ffile3.write(ffile3_arr, sizeof(ffile3_arr));           ffile3 << '\n';
    ffile3.write(ffile3_arr, sizeof(ffile3_arr));           ffile3 << '\n';



    ffile3.seekg(ios::beg);
    ffile3.read(ffile3_arr_in , sizeof(ffile3_arr_in));
    cout << "num of chars readed from file = " << ffile3.gcount() << endl;
    transform(begin(ffile3_arr_in), end(ffile3_arr_in),
              begin(ffile3_arr_in),
              [](char arg) { return arg +=0x30;});
    print_ffile3_arr_in();

    cout << endl << "----------------------------[bulk I/O]-----------------------------" << endl;


    cout << endl << "----------------------------[text I/O]-----------------------------" << endl;
    string    ffile4_name("c:\\data5.txt");
    fstream   ffile4(ffile4_name, std::ios::in | std::ios::out);
    string    content="0123456789";
    #define CHR_RCV_BUF_SIZE 1024u
    char      cRcvData[CHR_RCV_BUF_SIZE];
    string    strRcvdata;

    if (!ffile4) cerr << "can't open file " << ffile4_name << endl;

    ffile4  << content << endl
            << content << endl
            << content << endl;


    // read from file first approach
    ffile4.seekg(ios::beg);
    // get can be also used for this purposes but still there is a difference beetwen them
    // while (ffile4.get(cRcvData, CHR_RCV_BUF_SIZE))
    while (ffile4.getline(cRcvData, CHR_RCV_BUF_SIZE))
    {
        cout << "amount of data being read for this iteration = " << ffile4.gcount() << ' ';
        cRcvData[ffile4.gcount()] = 0;
        puts(cRcvData);
    }

    // read from file second approach
    ffile4.clear();
    ffile4.seekg(ios::beg);
    while(ffile4 >> strRcvdata) { cout << strRcvdata << endl;}

    //ignore skeep char sequence till specefied character
    ffile4.clear();
    ffile4.seekg(ios::beg);
    ffile4.ignore(1024,'6');
    cout << ffile4.tellg() << endl;
    ffile4 >> strRcvdata;  cout << strRcvdata << endl;
    //cout << ffile4.tellg() << endl;
    //cout << std::numeric_limits<std::streamsize>::max() << endl;
    cout << endl << "----------------------------[text I/O]-----------------------------" << endl;

    //positioning iterators
    std::cout << "Terminated..." << std::endl;
    return 0;
}
