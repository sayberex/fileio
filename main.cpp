#include <iostream>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <array>
#include <vector>
#include <sstream>
#include <io.h>

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



    cout << endl << "-----------------[positioning and stream iterators]----------------" << endl;
    string    ffile5_name("c:\\data6.txt");
    fstream   ffile5(ffile5_name, std::ios::in | std::ios::out);
    string    content2="0123456789";
    //#define CHR_RCV_BUF_SIZE 1024u
    //char      cRcvData[CHR_RCV_BUF_SIZE];
    //string    strRcvdata;
    char filebuffer[1024];

    istream_iterator<char> in_begin(ffile5);
    ostream_iterator<char> out_egin(ffile5);

    istream_iterator<char> in_end();
    ostream_iterator<char> out_end();

    if (!ffile5) cerr << "can't open file " << ffile5_name << endl;

    cout << "position of in/out indicators before file write      = " << ffile5.tellg() << '/' << ffile5.tellp() << endl;
    ffile5  << content2 << endl;
    cout << "position of in/out indicators after write 10 sym     = " << ffile5.tellg() << '/' << ffile5.tellp() << endl;

    //seekp and seeg sets both indicators
    ffile5.seekg(ios::beg);
    cout << "position of in/out indicators after seekg            = " << ffile5.tellg() << '/' << ffile5.tellp() << endl;
    //cout << "position of input indicator before file write      = " << ffile5.tellg() << endl;

    //move in/out pointer to char '3'
    ffile5.ignore(std::numeric_limits<std::streamsize>::max(), '3');
    cout << "position of in/out indicators after ignore(x,'3')    = " << ffile5.tellg() << '/' << ffile5.tellp() << endl;
    cout << "current sym is = " << std::hex << std::showbase <<ffile5.peek() << endl;

    cout << *(in_begin++) << *(in_begin++) << endl;

    copy(istream_iterator<char>(ffile5), istream_iterator<char>(), begin(filebuffer));
    puts(filebuffer);

    cout << endl << "-----------------[positioning and stream iterators]----------------" << endl;

    /*
     * https://www.drdobbs.com/cpp/iterators-and-iostreams/232600539
     * #include <iostream>
#include <fstream>
#include <iterator>
using namespace std;

int main(int argc, char* argv[])
{
    ofstream temp_out("temp.dat", std::ios_base::binary );
    for ( int i = 0 ; i < 256 ; i++ )
        temp_out.put( (char) i );
    temp_out.close();
    ifstream temp_in("temp.dat", std::ios_base::binary );
    char last = -1;
    int count = 0;
    istream_iterator<char> ii( temp_in );
    while ( ii != std::istream_iterator<char>() ) {
        char c = *ii++;
        count++;
        if ( c != char(last+1) )
            cout << "Error on character number: " << (int) last << endl;
        last = c;
    }
    cout << "Count: " << count << endl;
    return 0;
}

     istreambuf_iterator<char> jj(temp_in.rdbuf());
while ( ii != std::istreambuf_iterator<char>() ) {
     */


    cout.unsetf(ios::showbase | ios::hex);
    cout << endl << "-------------------[read whole file into string]-------------------" << endl;
    string    ffile6_name("c:\\data7.txt");
    ifstream  ffile6(ffile6_name);
    string    file6_content;
    stringstream file6_content2;
    if (!ffile6) cerr << "can not open file = " << ffile4_name << endl;

    //get file size
    ffile6.seekg(0, ios::end);   int size = ffile6.tellg();   cout << "filze size = " << size << endl;   ffile6.seekg(ios::beg);
    //in oreder to avoid a lot of relocation during file reading process allocate memory in order to fit whole file size
    file6_content.reserve(size);

    // Сброс данного флага необходим для отключения пропуска пробельных символов при форматном вводе через поток.
    ffile6.unsetf(ios::skipws); //  it is necessary yo let receive space characters during format input
    file6_content.assign(istream_iterator<char>(ffile6), istream_iterator<char>());
    cout << file6_content << endl;

    // read into stream
    ffile6.clear();
    ffile6.seekg(ios::beg);
    file6_content2 << ffile6.rdbuf();
    cout << file6_content2.str();
    cout << endl << "-------------------[read whole file into string]-------------------" << endl;


    cout << endl << "-------------------[read whole file into vector]-------------------" << endl;
    string   ffile7_name("c:\\data7.txt");
    ifstream ffile7(ffile7_name);

    vector<string> lines;
    ffile7.clear();
    ffile7.seekg(0, ios::beg);
    istream_iterator<string> it(ffile7);
    istream_iterator<string> it_eof;


    while (it != it_eof) { lines.push_back(*it++); }
    for (auto el : lines) {cout << el << endl; }

    cout << endl << "-------------------[read whole file into vector]-------------------" << endl;

    std::cout << "Terminated..." << std::endl;
    return 0;
}
