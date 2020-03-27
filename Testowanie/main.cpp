#include <iostream>
#include <cmath>
#include <time.h>

using namespace std;

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
    if(left < right) {
        int mid = (right+left)/2;
        MergeSort(Table, left, mid);
        MergeSort(Table, mid+1, right);
        Merge(Table, left, mid, right);
    }
}

int Border(int Table[], int left, int right){
    int pivot = Table[(left+right)/2];
    while (true)
    {
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

void heapify(int Table[], int Size, int root)
{
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

void Heapsort(int Table[], int left, int right)
{
    for (int root = right / 2 - 1; root >= 0; root--) heapify(Table, right, root);
    for (int root = right-1; root>=left; root--){
        swap(Table[left], Table[root]);
        heapify(Table, root, left);
    }
}


int main()
{
    srand (time(NULL));
    int Size = 10000;
    int *Tab = new int [Size];
    //=============
    //    TEST
    //=============
    for(int j=0; j<2; j++){
        for (int i=0; i<Size; i++) Tab[i] = rand();
        if(j==0) MergeSort(Tab, 0, Size-1);
        if(j==1) Quicksort(Tab, 0, Size-1);
        if(j==2) Heapsort(Tab, 0, Size-1);

        for (int i=1; i<Size; i++){
            if(!(Tab[i]>=Tab[i-1])){cout<< "\nError detected: "<<Tab[i-1]<<"<"<<Tab[i];}
        }
    }
    delete [] Tab;
    return 0;
}
