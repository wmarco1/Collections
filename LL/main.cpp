#include "pch.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "ll.h"



int main(int argc, char** argv) {
	srand(time(0));
	node *head;

	head = ll_new(1);

	for (int i = 0; i < 10; i++) {
		int r = rand() % 100;
		ll_append_node(head,ll_new(r));
	}

	ll_print(head);
	
	
	system("pause");

	ll_insertion_sort(&head);

	system("pause");

	ll_print(head);

	ll_free(head);

}