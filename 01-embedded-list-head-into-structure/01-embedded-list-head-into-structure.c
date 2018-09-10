#include <stdio.h>
#include <stdlib.h>
#include "list.h"

struct data {
	struct list_head list;
	int value;
};

int main() {
	struct list_head data_q;

	// Init
	INIT_LIST_HEAD(&data_q);
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

	// Iterate through data_q
	struct data *d;
	list_for_each_entry(d, &data_q, list) {
		printf("%d\n", d->value);
	}
}
