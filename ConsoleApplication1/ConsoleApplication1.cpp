// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define kLIST_SIZE 10
#define kMAX_NUMEBER 10




void print_list(int* list) {
	for (int i = 0; i < kLIST_SIZE; i++) {
		printf("%d, ", list[i]);
	}

	printf("\n");
}

int seq_search(int *list, int num) {
	int index = -1;
	for (int i = 0; i < kLIST_SIZE; i++) {
		if (list[i] == num)return i;
	}
}

int binary_search(int *list, int start, int end, int num) {
	int middle = (start + end) / 2;
	if (list[middle] == num) {
		return middle;
	}
	if (start == end) return -1;

	if (num > middle) {
		return binary_search(list, middle + 1, end, num);

	}

	

	if (num < middle) {
		return binary_search(list, start, middle-1, num);



	}





}
void sel_sort(int *list) {

	for (int i = 0; i < kLIST_SIZE; i++) {
		int smallest_index = i;
		for (int j = i+1; j < kLIST_SIZE; j++) {

			if (list[smallest_index] > list[j]) {

				smallest_index = j;

			}


		}
		//swap
		int t = list[smallest_index];
		list[smallest_index] = list[i];
		list[i] = t;

		
	}




}




int main()
{
	srand(time(0));
	int list[kLIST_SIZE];


	for (int i = 0; i < kLIST_SIZE; i++) {
		list[i] = (rand())%(kMAX_NUMEBER);
	}
	print_list(list);


	sel_sort(list);

	print_list(list);

	int index  = binary_search(list, 0, kLIST_SIZE, 1);
	printf("\n%d\n", index);
}
