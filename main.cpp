#include <iostream>
#include <fstream>
#include "include/rapidjson/filereadstream.h"
#include "include/rapidjson/document.h"
#include "include/rapidjson/writer.h"
#include "include/rapidjson/stringbuffer.h"
#include <cstdio>
#include <vector>
#define RAPIDJSON_HAS_STDSTRING 1
using namespace std;

vector<int> makeVectorToBeSorted(const string jsonString) {
    FILE* fp = fopen("../YouTubeDataset_withChannelElapsed.json", "rb"); // non-Windows use "r"
    char readBuffer[65536];
    rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));
    rapidjson::Document d;
    d.ParseStream(is);
    // At this point we have a parsed document.
    vector<int> v;
    for (int i = 0; i < d.Size() - 1; i++) {
        rapidjson::Value &firstValue = d[i];
        string s = firstValue[jsonString].GetString();
        int count = stol(s);
        v.push_back(count);
    }
    fclose(fp);
    return v;
}

void initializeAllVectors(vector<int>& v, vector<int>& v2, vector<int>& v3, vector<int>& v4, vector<string>& Ids) {
    FILE* fp = fopen("../YouTubeDataset_withChannelElapsed.json", "rb"); // non-Windows use "r"
    char readBuffer[65536];
    rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));
    rapidjson::Document d;
    d.ParseStream(is);
    // At this point we have a parsed document.
    for (int i = 0; i < d.Size() - 1; i++) {
        rapidjson::Value &firstValue = d[i];
        string s = firstValue["videoLikeCount"].GetString();
        int count = stol(s);

        string s2 = firstValue["videoDislikeCount"].GetString();
        int count2 = stol(s2);

        string s3 = firstValue["channelCommentCount"].GetString();
        int count3 = stol(s3);

        string s4 = firstValue["videoViewCount"].GetString();
        int count4 = stol(s4);

        string s5 = firstValue["channelId"].GetString();

        v.push_back(count);
        v2.push_back(count2);
        v3.push_back(count3);
        v4.push_back(count4);
        Ids.push_back(s5);
    }
    fclose(fp);
    return;
}

void merge(vector<int>& v, int l, int m, int r, vector<int>& index) {

    //defines the length of the sub-array
    int n1 = m - l + 1;
    int n2 = r - m;

    // Create temp arrays to hold left and right sub-arrays
    int L[n1], R[n2];
    int LForIndex[n1], RForIndex[n2];

    // Copy data to temp arrays L[] and R[]
    for (int i = 0; i < n1; i++) {
        L[i] = v.at(l + i);
        LForIndex[i] = index.at(l + i);
    }
    for (int j = 0; j < n2; j++) {
        R[j] = v.at(m + 1 + j);
        RForIndex[j] = index.at(m + 1 + j);
    }

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
            index[k] = LForIndex[lIndex];
            lIndex++;
        }
        else {
            v[k] = R[rIndex];
            index[k] = RForIndex[rIndex];
            rIndex++;
        }
        k++;
    }

    // Copy the remaining elements of
    // L[], if there are any
    while (lIndex < n1) {
        v.at(k) = L[lIndex];
        index.at(k) = LForIndex[lIndex];
        lIndex++;
        k++;
    }

    // Copy the remaining elements of
    // R[], if there are any
    while (rIndex < n2) {
        v.at(k) = R[rIndex];
        index.at(k) = RForIndex[rIndex];
        rIndex++;
        k++;
    }
    return;
}


void mergeSort(vector<int>& arr,int l, int r, vector<int>& index){
    if(l >= r){
        return;//returns recursively
    }
    int m = l + (r-l)/2;
    mergeSort(arr,l,m, index);
    mergeSort(arr,m+1,r, index);
    merge(arr,l,m,r, index);
}

void maxHeapify(vector<int>& v, int n, int i, vector<int>& index)
{
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int maxChild = i;
    if (left < n && v[left] > v[maxChild])
        maxChild = left;
    if (right < n && v[right] > v[maxChild])
        maxChild = right;
    if (maxChild != i)
    {
        swap(v[i], v[maxChild]);
        swap(index[i], index[maxChild]);
        maxHeapify(v, n, maxChild, index);
    }
}
void heapSort(vector<int>& v, vector<int>& index)
{
    int heapSize = v.size();
    //Build heap from vector
    for (int i = heapSize / 2; i >= 0; i--)
        maxHeapify(v, heapSize, i, index);
    //Extract max from heap
    for (int i = heapSize - 1; i > 0; i--)
    {
        swap(v[i], v[0]);
        swap(index[i], index[0]);
        heapSize--;
        maxHeapify(v, heapSize, 0, index);
    }
    return;
}

vector<int> createIndexVector(vector<int> v) {
    vector<int> b;
    for (int i = 0; i < v.size(); ++i) {
        b.push_back(i);
    }
    return b;
}

void printVectorAsc(vector<int> v, vector<int> index, vector<string> Ids, string descriptor) {
    for (int i = 0; i < v.size(); ++i) {
        cout << "Video URL: https://www.youtube.com/watch?v=" + Ids.at(index.at(i)) + " " + descriptor + " Count: " << v.at(i) << endl;
    }
    return;
}

void printVectorDesc(vector<int> v, vector<int> index, vector<string> Ids, string descriptor) {
    for (int i = v.size() - 1; i >= 0; i--) {
        cout << "Video URL: https://www.youtube.com/watch?v=" + Ids.at(index.at(i)) + " " + descriptor + " Count: " << v.at(i) << endl;
    }
    return;
}

int main() {
//    auto v = makeLikeCountVector();
//    cout << v.size();
//    auto& a = v;
//    mergeSort(a, 0, v.size()-1);
//    printVector(v);
cout << "Please Wait as Values Are Read From Data Set..." << endl;
    vector<int> likes;
    vector<int> dislikes;
    vector<int> comments;
    vector<int> views;
    vector<string> channelIds;
    auto& a = likes;
    auto& a2 = dislikes;
    auto& a3 = comments;
    auto& a4 = views;
    auto& Ids = channelIds;

    initializeAllVectors(a, a2, a3, a4, Ids);

    while (true) {
        int firstSelector;
        string jsonToSearch = "";
        string descriptor = "";

        cout << "Please Select an Option" << endl;
        cout << "--------------------------" << endl;
        cout << "0. Exit" << endl;
        cout << "1. Search for number of likes" << endl;
        cout << "2. Search for number of dislikes" << endl;
        cout << "3. Search for number of comments" << endl;
        cout << "4. Search for number of views" << endl;

        cin >> firstSelector;
        vector<int> indexVector = createIndexVector(views);
        auto& indexReference = indexVector;
        vector<int> v;

        if (firstSelector == 0) {
            return 0;
        } else if (firstSelector == 1) {
            v = likes;
            jsonToSearch = "videoLikeCount";
            descriptor = "Like";
        } else if (firstSelector == 2) {
            v = dislikes;
            jsonToSearch = "videoDislikeCount";
            descriptor = "Dislike";
        } else if (firstSelector == 3) {
            v = comments;
            jsonToSearch = "channelCommentCount";
            descriptor = "Comment";
        } else if (firstSelector == 4) {
            v = views;
            jsonToSearch = "videoViewCount";
            descriptor = "View";
        } else {
            cout << "please choose valid selection" << endl;
            return 0;
        }

        auto &a = v;

        int sortSelector;

        cout << "Please Select a Sorting Algorithm" << endl;
        cout << "-------------------------------------" << endl;
        cout << "1. Merge Sort" << endl;
        cout << "2. Heap Sort" << endl;

        cin >> sortSelector;
        bool isMergeSort;


        if (sortSelector == 1) {
            isMergeSort = true;
        } else if (sortSelector == 2) {
            isMergeSort = false;
        } else {
            cout << "please choose valid selection" << endl;
            return 0;
        }

        if (isMergeSort) {
            mergeSort(a, 0, v.size() - 1, indexReference);
        } else {
            heapSort(a, indexReference);
        }

        int ascOrDesc;

        cout << "Please Select How you would like the Data to be Displayed" << endl;
        cout << "------------------------------------------------------------" << endl;
        cout << "1. Ascending" << endl;
        cout << "2. Descending" << endl;

        cin >> ascOrDesc;
        bool isAsc;

        if (ascOrDesc == 1) {
            isAsc = true;
        } else if (ascOrDesc == 2) {
            isAsc = false;
        } else {
            cout << "please choose valid selection" << endl;
            return 0;
        }

        if (isAsc) {
            printVectorAsc(v, indexVector, channelIds, descriptor);
        } else {
            printVectorDesc(v, indexVector, channelIds, descriptor);
        }

        indexVector.clear();

    }
    return 0;
}

