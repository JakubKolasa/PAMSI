#include "Sorter.h"

void Merge(int MainTable[], int left, int mid, int right){
    int leftTableSize = mid-left+1;
    int rightTableSize = right-mid;
    int LeftTable [leftTableSize];
    int RightTable[rightTableSize];
    int i,j;

    for(i = 0; i<leftTableSize; i++) LeftTable[i] = MainTable[left+i];
    for(j = 0; j<rightTableSize; j++) RightTable[j] = MainTable[mid+j+1];

    int position = left;
    for(i = 0, j = 0; i < leftTableSize &&  j < rightTableSize; position++){
        if(LeftTable[i] <= RightTable[j]){
            MainTable[position] = LeftTable[i];
            i++;
        }else{
            MainTable[position] = RightTable[j];
            j++;
        }
    }
    for(; i<leftTableSize; i++, position++) MainTable[position] = LeftTable[i];
    for(; j<rightTableSize; j++, position++) MainTable[position] = RightTable[j];
}

void MergeSort(int Table[], int left, int right){
    if(left < right){
        int mid = (right+left)/2;
        MergeSort(Table, left, mid);
        MergeSort(Table, mid+1, right);
        Merge(Table, left, mid, right);
    }
}

int Border(int Table[], int left, int right){
    int pivot = Table[(left+right)/2];
    while (true){
        while (Table[right] > pivot) right--;
        while (Table[left] < pivot) left++;
        if (left < right){ swap(Table[left],Table[right]); left++; right--;}
        else return right;
    }
}

void Quicksort(int Table[], int left, int right){
    if (left < right){
        int pivot = Border(Table,left,right);
        Quicksort(Table, left, pivot);
        Quicksort(Table, pivot+1, right);
    }
}

void heapify(int Table[], int Size, int root){
    int left = 2*root + 1;
    int right = 2*root + 2;
    int N = root;

    if (left < Size && Table[left] > Table[N])   N = left;
    if (right < Size && Table[right] > Table[N]) N = right;
    if (N != root){
        swap(Table[root], Table[N]);
        heapify(Table, Size, N);
    }
}

void Heapsort(int Table[], int left, int right){
    int root;
    for (root = right/2-1; root >= 0; root--) heapify(Table, right, root);
    for (root = right-1; root>=left; root--){
        swap(Table[left], Table[root]);
        heapify(Table, root, left);
    }
}


Sorter::Sorter(int TableSize, float AlreadySorted)
{
    _Elements = TableSize;
    _AlreadySorted = AlreadySorted;

    if ( AlreadySorted == 1 ) {
        for(int a = 0; a < 100 ; a++ ){
        _Tables[a] = new int [TableSize];
        _TablesCopy[a] = new int [TableSize];
        for(int i = 0; i<TableSize; i++ )
            _Tables[a][i]=TableSize-i;
            }
    }
    else{
        int HowManySorted = TableSize * AlreadySorted;
        for(int a = 0; a < 100 ; a++ ){
            _Tables[a] = new int [TableSize];
            _TablesCopy[a] = new int [TableSize];
            for( int i = 0; i<TableSize; i++ )
                if ( i <= HowManySorted ) _Tables[a][i] = i;
                else  _Tables[a][i] = rand()+HowManySorted;
        }
    }
}

void Sorter::TestAndSave(){
    ofstream file("ToExcel.csv", ios::app);
    int Size = _Elements;
    if(_AlreadySorted == 0) file << "All random";
    else if (_AlreadySorted == 1) file << "Sorted and reversed";
    else file << _AlreadySorted*100<<" %";
    //Was sorted [%];n;Quicksort;Mergesort;Heapsort [ms]
    file <<";"<< Size<<";"<<TestQuicksort()<<";"<<TestMergeSort()<<";"<<TestHeapsort()<<endl;
}

int Sorter::TestQuicksort(){
    for(int a = 0; a<100; a++){
        for(int b = 0; b<_Elements; b++) _TablesCopy[a][b] = _Tables[a][b];}
    chrono::steady_clock::time_point Start = chrono::steady_clock::now();
    //==========
    for(int a=0; a<100; a++) Quicksort(_TablesCopy[a],0,_Elements-1);
    //==========
    chrono::steady_clock::time_point End = chrono::steady_clock::now();
    return chrono::duration_cast<chrono::milliseconds>(End - Start).count();
}

int Sorter::TestMergeSort(){
    for(int a = 0; a<100; a++){
        for(int b = 0; b<_Elements; b++) _TablesCopy[a][b] = _Tables[a][b];}
    chrono::steady_clock::time_point Start = chrono::steady_clock::now();
    //==========
    for(int a=0; a<100; a++) MergeSort(_TablesCopy[a],0,_Elements-1);
    //==========
    chrono::steady_clock::time_point End = chrono::steady_clock::now();
    return chrono::duration_cast<chrono::milliseconds>(End - Start).count();
}

int Sorter::TestHeapsort(){
    for(int a = 0; a<100; a++){
        for(int b = 0; b<_Elements; b++) _TablesCopy[a][b] = _Tables[a][b];}
    chrono::steady_clock::time_point Start = chrono::steady_clock::now();
    //==========
    for(int a=0; a<100; a++) Heapsort(_TablesCopy[a],0,_Elements);
    //==========
    chrono::steady_clock::time_point End = chrono::steady_clock::now();
    return chrono::duration_cast<chrono::milliseconds>(End - Start).count();
}


