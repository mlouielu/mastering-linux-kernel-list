#include <stdio.h>
#include <stdlib.h>
#include "list.h"

struct data {
	struct list_head list;
	int value;
};

int main() {
	// Init list_head
	struct list_head data_q;
	INIT_LIST_HEAD(&data_q);

	// Init data_q data
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

	// 30 -> 10 -> 20
	list_add(&data3->list, &data_q);

	// Print out all data
	printf("%d -> %d -> %d\n",
		   container_of(data_q.next, struct data, list)->value,
		   container_of(data_q.next->next, struct data, list)->value,
		   container_of(data_q.next->next->next, struct data, list)->value);
}
