#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned char byte;

byte* getBestPermutation(byte* numbers, byte size);
void sortArrayIncreasing(byte* arr, byte size);
byte findCeil(byte* arr, byte first, byte l, byte h);
void copyArray(byte* arr1, byte* arr2);

int main(){

    byte numbers[9] = {1,2,3,4,5,6,7,8,9};

    byte* best_solution;
    best_solution = (byte*)malloc(9);
    best_solution = getBestPermutation(numbers, sizeof(numbers)/sizeof(numbers[0]));

    int best_value = best_solution[0] + best_solution[1] + best_solution[2];
    best_value += 10 * (best_solution[3] + best_solution[4] + best_solution[5]);
    best_value += 100 * (best_solution[6] + best_solution[7] + best_solution[8]);

    printf("%d|%d|%d\n", best_solution[6], best_solution[3], best_solution[0]);
    printf("%d|%d|%d\n", best_solution[7], best_solution[4], best_solution[1]);
    printf("%d|%d|%d\n", best_solution[8], best_solution[5], best_solution[2]);
    printf("________\n");
    printf("%d\n", best_value);

    system("pause");

    return 0;
}

byte* getBestPermutation(byte* numbers, byte size){
    int tmp;
    bool isDone = false;
    byte ceil_index;
    byte l, h;

    byte* closest_perm;
    closest_perm = (byte*)malloc(9*sizeof(char));

    int current_value = 0;
    int closest_value = 0;
    sortArrayIncreasing(numbers, size);

    while(!isDone){
        int i;
        for(i = size - 2; i >= 0; --i){
            if(numbers[i] < numbers[i+1]){
                break;
            }
        }

        if(i == -1){
            isDone = true;
        }
        else{
            l = i+1;
            h = size - 1;
            ceil_index = findCeil(numbers, numbers[i], l, h);
            tmp = numbers[i];
            numbers[i] = numbers[ceil_index];
            numbers[ceil_index] = tmp;

            while(l < h){
                tmp = numbers[l];
                numbers[l] = numbers[h];
                numbers[h] = tmp;
                l++;
                h--;
            }
            
            current_value = numbers[0] + numbers[1] + numbers[2];
            current_value += 10 * (numbers[3] + numbers[4] + numbers[5]);
            current_value += 100 * (numbers[6] + numbers[7] + numbers[8]);

            //printf("%d\n", current_value);

            if((current_value <= 1000) && (current_value > closest_value)){
                closest_value = current_value;
                copyArray(numbers, closest_perm);
            }
            
        }
    }
    return closest_perm;
}

void sortArrayIncreasing(byte* arr, byte size){
    int tmp;

    for(int i = 0; i < size; i++){
        for(int j = 0; j < size - 1; j++){
            if(arr[j] > arr[j+1]){
                tmp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = arr[j];
            }
        }
    }
}


byte findCeil(byte* arr, byte first, byte l, byte h){
    byte ceil_i = l;

    for(byte i = l+1; i <= h; i++){
        if(arr[i] > first && arr[i] < arr[ceil_i]){
            ceil_i = i;
        }
    }

    return ceil_i;
}

void copyArray(byte* arr1, byte* arr2){
    int size = sizeof(arr1)/sizeof(arr1[0]) + 1;
    for (int i = 0; i < size; i++){
        *(arr2 + i) = *(arr1 + i);
    }
    //eins zu wenig
}