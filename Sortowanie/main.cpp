#include <iostream>
#include <Sorter.h>
#include <dirent.h>


using namespace std;

int main()
{
    Sorter *wsk;
    remove("ToExcel.txt");
    int Elements[5] = {10000,50000,100000,500000,1000000};
    float Sorted[8] = {0,0.25,0.5,0.75,0.95,0.99,0.997,1};

    for( int a = 0; a < 5; a++){
        for ( int b = 0; b < 8; b++ ){
            cout << Elements[a]<<" "<<Sorted[b] << endl;
            wsk = new Sorter(Elements[a],Sorted[b]);
            wsk->TestAndSave();
            delete wsk;
        }
    }
    cout << "Complete!" << endl;
    return 0;
}
