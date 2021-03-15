#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <stdlib.h>

typedef unsigned char byte;

byte* getBestPermutation(byte* numbers, byte size);
void sortArrayIncreasing(byte* arr, byte size);
byte findCeil(byte* arr, byte first, byte l, byte h);
void copyArray(byte* arr1, byte* arr2);
void swap(byte* number1, byte* number2);
int calcValueOfPerm(byte* numbers);
void displaySolution(byte* numbers, int value);
int getInput(byte* numbers);

int main(){

    while(1){
        byte numbers[9];

        if(getInput(numbers) == -1){
            break;
        }

        byte* best_solution;
        best_solution = (byte*)malloc(9);
        best_solution = getBestPermutation(numbers, sizeof(numbers)/sizeof(numbers[0]));

        int best_value = calcValueOfPerm(best_solution);

        displaySolution(best_solution, best_value);
    }
    return 0;
}

byte* getBestPermutation(byte* numbers, byte size){
    bool isDone = false;
    byte ceil_index;
    byte l, h;

    byte* closest_perm;
    closest_perm = (byte*)malloc(9*sizeof(char));

    copyArray(numbers, closest_perm);

    int current_value = 0;
    int closest_value = 0;
    sortArrayIncreasing(numbers, size);

    while(!isDone){
        int i;

        //Find next non-increasing number
        for(i = size - 2; i >= 0; --i){
            if(numbers[i] < numbers[i+1]){
                break;
            }
        }

        //Done, when there is no no-increasing number
        if(i == -1){
            isDone = true;
        }

        else{
            l = i+1;
            h = size - 1;
            //Find next biggest number and swap it with the first non-decreasing number
            ceil_index = findCeil(numbers, numbers[i], l, h);
            swap(&numbers[i], &numbers[ceil_index]);

            while(l < h){
                swap(&numbers[l], &numbers[h]);

                l++;
                h--;
            }
            
            //Caluculate the number of the given permutation
            current_value = calcValueOfPerm(numbers);

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
                swap(&arr[j], &arr[j+1]);
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
}

void swap(byte* number1, byte* number2){
    byte tmp;
    tmp = *number1;
    *number1 = *number2;
    *number2 = tmp;
}

int calcValueOfPerm(byte* numbers){
    int current_value = numbers[0] + numbers[1] + numbers[2];
    current_value += 10 * (numbers[3] + numbers[4] + numbers[5]);
    current_value += 100 * (numbers[6] + numbers[7] + numbers[8]);

    return current_value;
}

int getInput(byte* numbers){
    char input;
    printf("Do you want to quit? [y or n]\n");
    scanf(" %c", &input);
    
    if(input == 'y' || input == 'Y'){
        return -1;
    }

    else{

        for (int i = 1; i <= 9; i++) {
            system("cls");
            printf("\nNumber %d: ", i);
            scanf(" %c", &numbers[i-1]);
            numbers[i-1] -= 48;
            if(numbers[i-1] < 0 && numbers[i-1] > 9){
                numbers[i-1] = 1;
            }
        }

        return 0;    
    }
}

void displaySolution(byte* numbers, int value){
    system("cls");
    printf("%d|%d|%d\n", numbers[6], numbers[3], numbers[0]);
    printf("%d|%d|%d\n", numbers[7], numbers[4], numbers[1]);
    printf("%d|%d|%d\n", numbers[8], numbers[5], numbers[2]);
    printf("________\n");
    printf("%d\n", value);
}