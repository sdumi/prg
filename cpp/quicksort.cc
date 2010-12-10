/**
 * implements a quick sort algorithm...
 *
 */
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#include <iostream>
using namespace std;

void printData(int data[], int size);
void generateData(int data[], int size);
void quickSort(int data[], int left, int right);
void printCurrentTime();

const int SIZE = 2*1024*1024;
//////////////////////////////////////////////////
//
int main()
{
    int data[SIZE];
    printCurrentTime();
    generateData(data, SIZE);
    printCurrentTime();
    quickSort(data, 0, (SIZE - 1));
    printCurrentTime();
    quickSort(data, 0, (SIZE - 1));
    printCurrentTime();
}

//////////////////////////////////////////////////
//
void printData(int data[], int size)
{
    for (int i = 0; i < size; ++i)
    {
        cout.width(4);
        cout << data[i];
    }
    cout << endl;
}

//////////////////////////////////////////////////
//
void generateData(int data[], int size)
{
    srand(time(NULL));
    for (int i = 0; i < size; ++i)
        data[i] = rand() % 1000;
}

//////////////////////////////////////////////////
//
void printCurrentTime()
{
    struct timeval time;
    struct timezone zone;
    gettimeofday(&time, &zone);
    cout << "(" << time.tv_sec << "," << time.tv_usec << ")" << endl;
}

//////////////////////////////////////////////////
//
void quickSort(int data[], int left, int right)
{
    // nothing to sort in this case...
//    cout << "(" << left << ":" << right << ")";
//    printData(data, SIZE);

    if (left >= right)
    {
//        cout << endl;
        return;
    }
//    cout << " a[l] = " << data[left] << ", a[r] = " << data[right] << endl;


    int pivot = right;
    int old_l = left;
    int old_r = right;
    int cur_l = left;
    int cur_r = right;
    int mid = right;
    --right;

    // search for the pivot position:
    while (left < right)
    {
        if (data[pivot] < data[right])
        {
            --right;
//            cout << "*" << endl;
            continue;
        }
        if (data[pivot] > data[left])
        {
            ++left;
//            cout << "@" << endl;
            continue;
        }
        {
//            cout << "#" << endl;

            int tmp = data[left];
            data[left] = data[right];
            data[right] = tmp;
            //          printData(data, SIZE);
            ++left;
            --right;
//            cout << "{" << left << ":" << right << "::" << pivot << "}"<<endl;
        }
    }
    mid = left;

    if (left <= old_r)
    {
//        cout << "<" << left << "," << right << ">" << "will place pivot: " << data[pivot] << " in position:" << mid << endl;

//        printData(data, SIZE);
//        cout << "[" << left << ":" << right << "::" << pivot << "]"<<endl;
//        if (left != right)
//            mid += 1;
        if (data[pivot] < data[mid])
        {
            int tmp = data[mid];
            data[mid] = data[pivot];
            data[pivot] = tmp;
        }

//        cout << "[" << left << ":" << right << "::" << pivot << "::::" << mid << "]"<<endl;
    }
//    printData(data, SIZE);
//    cout << endl << endl;
//    cout << "will launch quicksort with range: <" << old_l << "," << mid - 1 << ">" << endl;

    quickSort(data, old_l, mid);
//    cout << "will launch quicksort with range: <" << mid+1 << "," << old_r << ">" << endl;
    quickSort(data, mid+1, old_r);
}

