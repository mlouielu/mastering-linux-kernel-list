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

	// Iterate through the list by `list_for_each`
	struct list_head *pos;
	struct data *entry;
	list_for_each(pos, &data_q) {
		entry = list_entry(pos, struct data, list);
		printf("%d\n", entry->value);
	}

	// Iterate through the list by `list_for_each_entry`
	list_for_each_entry(entry, &data_q, list) {
		printf("%d\n", entry->value);
	}
}
