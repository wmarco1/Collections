#pragma once
struct node;

#include <stdlib.h>

typedef struct node{
	node* next;
	int value;
}node;


inline node* ll_init() {
	node* n =(node*) malloc(sizeof(node));
	n->value = -1;
	n->next = NULL;
	return n;
}

inline node* ll_new(int val) {
	node* n=  (node*)malloc(sizeof(node));
	n->value = val;
	n->next = NULL;
	return n;
}

inline node* ll_end(node* n) {
	if (n == NULL)return NULL;

	do {
		if (n->next == NULL)return n;
		n = n->next;
	} while (true);
}

inline void ll_append_node(node *n, node *add) {
	node *end = ll_end(n);
	end->next = add;
	add->next = NULL;
}


inline void ll_append_value(node* n, int val) {
	node* add = ll_new(val);

	ll_append_node(n,add);
}


inline void ll_free(node*n) {

	if (n->next == NULL) {
		free(n);
		return;
	}
		
	ll_free(n->next);

	free(n);

}

inline node* ll_insert_value_sorted(node *n, int val) {
	
	if (n->next == NULL) {
		node* new_node = ll_new(val);
		ll_append_node(n, ll_new(val));
		return new_node;
	}
	if (val > n->value) {// val == 10 > n->value
		node* new_node = ll_new(val);
		node *temp = n->next;
		n->next = new_node;
		n->next->next = temp;
		return new_node;
	}

	return ll_insert_value_sorted(n->next, val);
}
inline void ll_print(node* n) {
	while (n != NULL) {
		printf("%d, ", n->value);
		printf("\n");
		n = n->next;

	}


}


inline node* ll_insert_node_sorted(node *n, node *ins) {
	if (n->next == NULL) {
		n->next = ins;
		return ins;
	}
	if ( ins->value > n->value ) {
		node *temp = n->next;
		n->next = ins;
		ins->next = temp;
		return ins;
	}

	return ll_insert_node_sorted(n->next, ins);
}

inline node* ll_find_smallest_node(node *n) {
	node* smallest_node = n;
	while (n != NULL) {
		if (n->value < smallest_node->value)
			smallest_node = n;
		
	}
	return n;
}
inline node* ll_prev_node(node* start, node* n) {
	if (start == NULL) return NULL;
	if (start->next = n)return start;
	ll_prev_node(start->next, n);


}
inline void ll_insertion(node **head, node *ins) {
	node *t = *head;

	if ((*head)->value >= ins->value || (*head) == NULL) {
		ins->next = *head;
		*head = ins;
	}
	while (t->next != NULL && t->next->value < ins->value) {
		t = t->next;
	}
	ins->next = t->next;
	t->next = ins;

}


inline void ll_insertion_sort(node **head) {
	node *t = *head;
	node *sorted = ll_init();

	while (t != NULL) {
		node *n = t->next;
		ll_insertion(&sorted, t);
		t = n;

	}
	*head = sorted->next;
	sorted->next = NULL;
	free(sorted);
}






