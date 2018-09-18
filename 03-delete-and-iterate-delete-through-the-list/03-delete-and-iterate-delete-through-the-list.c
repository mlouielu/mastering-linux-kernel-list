#include <stdio.h>
#include <stdlib.h>
#include "list.h"

struct data {
	struct list_head list;
	int value;
};

int main() {
	// Init
	LIST_HEAD(data_q);
	struct data *d, *tmp;
	struct data *data1 = malloc(sizeof(struct data));
	struct data *data2 = malloc(sizeof(struct data));
	struct data *data3 = malloc(sizeof(struct data));

	// Add item into `data_q`
	data1->value = 10;
	data2->value = 20;
	data3->value = 30;

	// 10
	list_add_tail(&data1->list, &data_q);

	// 10 -> 20
	list_add_tail(&data2->list, &data_q);

	// 10 -> 20 -> 30
	list_add_tail(&data3->list, &data_q);


	// Delete one item in the list
	// This will print out:
	// 10
	// 30
	list_del(&data2->list);
	list_for_each_entry(d, &data_q, list) {
		printf("%d\n", d->value);
	}

	// Iterate delete list item
	// MUST USE list_for_each_entry_safe OR
	//          list_for_each_safe
	list_for_each_entry_safe(d, tmp, &data_q, list) {
		list_del(&d->list);
	}

	// Should print nothing
	list_for_each_entry(d, &data_q, list) {
		printf("%d\n", d->value);
	}


	// If not using *_safe iterate, then it will get a seg fault
	// Because it didn't use a temporary data to save the next entry
	// When we perform list_del(&d->list), its next,prev will change to
	// LIST_POISON1 and LIST_POISON2, which is not a valid address.
	// So at next round of list_del, it will perform on the LIST_POISON1,
	// causing a segment fault
	list_add_tail(&data1->list, &data_q);
	list_add_tail(&data2->list, &data_q);
	list_add_tail(&data3->list, &data_q);
	list_for_each_entry(d, &data_q, list) {
		list_del(&d->list);
	}
}
