#include <iostream>
#include <fstream>
#include "include/rapidjson/filereadstream.h"
#include "include/rapidjson/document.h"
#include "include/rapidjson/writer.h"
#include "include/rapidjson/stringbuffer.h"
#include <cstdio>
#include <vector>
using namespace std;

void merge(vector<int>& v, int l, int m, int r) {

    //defines the length of the sub-array
    int n1 = m - l + 1;
    int n2 = r - m;

    // Create temp arrays to hold left and right sub-arrays
    int L[n1], R[n2];

    // Copy data to temp arrays L[] and R[]
    for (int i = 0; i < n1; i++)
        L[i] = v.at(l + i);
    for (int j = 0; j < n2; j++)
        R[j] = v.at(m + 1 + j);

    //Index of first subarray
    int lIndex = 0;

    //Index of second subarray
    int rIndex = 0;

    //index of merged subarray
    int k = l;

    //check the arrays for which values are greater, and swap when appropriate. Then, merge the two sub arrays
    //n1 size of sub array 1
    //n2 size of sub array 2
    while (lIndex < n1 && rIndex < n2) {
        //iterate i and j separately
        if (L[lIndex] <= R[rIndex]) {
            v[k] = L[lIndex];
            lIndex++;
        }
        else {
            v[k] = R[rIndex];
            rIndex++;
        }
        k++;
    }

    // Copy the remaining elements of
    // L[], if there are any
    while (lIndex < n1) {
        v.at(k) = L[lIndex];
        lIndex++;
        k++;
    }

    // Copy the remaining elements of
    // R[], if there are any
    while (rIndex < n2) {
        v.at(k) = R[rIndex];
        rIndex++;
        k++;
    }
    return;
}


void mergeSort(vector<int>& arr,int l, int r){
    if(l >= r){
        return;//returns recursively
    }
    int m = l + (r-l)/2;
    mergeSort(arr,l,m);
    mergeSort(arr,m+1,r);
    merge(arr,l,m,r);
}

int main() {
//    auto v = makeLikeCountVector();
//    cout << v.size();
//    auto& a = v;
//    mergeSort(a, 0, v.size()-1);
//    printVector(v);

    int  firstSelector;
    string jsonToSearch = "";

    cout << "Please Select an Option" << endl;
    cout << "--------------------------" << endl;
    cout << "1. Search for number of likes" << endl;
    cout << "2. Search for number of dislikes" << endl;
    cout << "3. Search for number of comments" << endl;
    cout << "4. Search for number of views" << endl;

    cin >> firstSelector;

    if (firstSelector == 0) {
        return 0;
    }
    else if (firstSelector == 1) {
        jsonToSearch = "videoLikeCount";
    }
    else if (firstSelector == 2) {
        jsonToSearch = "videoDislikeCount";
    }
    else if (firstSelector == 3) {
        jsonToSearch = "channelCommentCount";
    }
    else if (firstSelector == 4) {
        jsonToSearch = "videoViewCount";
    }
    else {
        return 0;
    }

    int sortSelector;

    cout << "Please Select a Sorting Algorithm" << endl;
    cout << "-------------------------------------" << endl;
    cout << "1. Merge Sort" << endl;
    cout << "2. Heap Sort" << endl;

    cin >> sortSelector;
    bool isMergeSort;


    if (sortSelector == 1) {
        isMergeSort = true;
    }
    else if (sortSelector == 2) {
        isMergeSort = false;
    }
    else {
        return 0;
    }

    int ascOrDesc;

    cout << "Please Select How you would like the Data to be Displayed" << endl;
    cout << "------------------------------------------------------------" << endl;
    cout << "1. Ascending" << endl;
    cout << "2. Descending" << endl;

    cin >> ascOrDesc;
    bool isAsc;

    if (sortSelector == 1) {
        isAsc = true;
    }
    else if (sortSelector == 2) {
        isAsc = false;
    }
    else {
        return 0;
    }
    int b = 5;

    return 0;
}

