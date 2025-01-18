#include <iostream>


void merge_sort(int* arr, int size) {    
    if ( size ==1 ) {
        return;
    }
    if (size == 2) {
        if (arr[0] > arr[1]) {
            int t = arr[0];
            arr[0] = arr[1];
            arr[1] = t;
        }
        return;
    }
    int right = size - 1; //2 index
    
    int middle = right / 2; //1  index
    int* arr1 = arr;
    int* arr2 = reinterpret_cast<int*>(
        (reinterpret_cast<long long>(arr) +((middle+1) * sizeof(int)) )
        );
    merge_sort(arr1, middle + 1);
    merge_sort(arr2, right - middle);
        
    int* resArr = new int[size];
    int count1 = 0, count2 = 0;
    do {                             
        if (arr1[count1] < arr2[count2]) {            
            resArr[count1 + count2] = arr1[count1];
            
            if (count1 < middle) {
                  ++count1;
            }
            else {
                ++count1;
                int countForFor = right - middle - count2;
                for (int j = 0; j < countForFor; ++j) {
                    resArr[count1 + count2] = arr2[count2];
                    ++count2;
                }
                break;
            }
        }
        else if(arr1[count1] > arr2[count2]){
            resArr[count1 + count2] = arr2[count2];
            
            if (count2 < right - middle - 1) {
                ++count2;
            }
            else {
                ++count2;
                int countForFor = middle - count1 + 1;                
                for (int j = 0; j < countForFor; ++j) {
                    resArr[count1 + count2] = arr1[count1];
                    ++count1;
                }
                break;
            }
        }
        else { // arr1[count1] == arr2[count2]
            resArr[count1 + count2] = arr1[count1];
            ++count1;
            resArr[count1 + count2] = arr2[count2];
            ++count2;
            if (count1 > middle) {
                int countForFor = right - middle - count2;
                for (int j = 0; j < countForFor; ++j) {
                    resArr[count1 + count2] = arr2[count2];
                    ++count2;
                }
                break;
            }
            if (count2 > right - middle - 1) {
                int countForFor = middle - count1 + 1;
                for (int j = 0; j < countForFor; ++j) {
                    resArr[count1 + count2] = arr1[count1];
                    ++count1;
                }
                break;
            }
        }
    } while (count1 + count2 < size-1);
    for (int j = 0; j < size; ++j) {
        arr[j] = resArr[j];
    }    
    delete[] resArr;
}



int main()
{
    setlocale(LC_ALL, "Russian");
    //const int SIZE = 10;
    const int SIZE = 18;
    //int arr[SIZE]{ 3, 43, 38, 29, 18, 72, 57, 61, 2, 33 };
    int arr[SIZE]{24, 66, 20, 79, 30, 16, 19, 62, 94, 59, 0, 7, 59, 90, 84, 60, 95, 62};

    std::cout << "Исходный массив: ";
    for (int i = 0; i < SIZE; ++i) std::cout << arr[i] << "  ";
    std::cout << "\nОтсортированный массив: ";
    merge_sort(arr, SIZE);
    for (int i = 0; i < SIZE; ++i) std::cout << arr[i] << "  ";
}
