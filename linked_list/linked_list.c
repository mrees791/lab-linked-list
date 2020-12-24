#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"

list_t *create_list() {
	list_t *list = malloc(sizeof(list_t));

	list->first = NULL;
	list->last = NULL;
	list->size = 0;

	return list;
}

void free_list(list_t *list) {
	while (list->size > 0) {
		list_remove(list, 0);
	}
	free(list);
}

node_t *node_get_recursive(list_t *list, node_t *node, int currentIndex,
		int desiredIndex) {
	if (currentIndex == desiredIndex) {
		return node;
	} else if (currentIndex < desiredIndex) {
		return node_get_recursive(list, node->next, ++currentIndex,
				desiredIndex);
	}
	return NULL;
}

node_t *node_get(list_t *list, int desiredIndex) {
	if (list->size == 0 || desiredIndex > list_size(list)) {
		return NULL;
	}
	return node_get_recursive(list, list->first, 0, desiredIndex);
}

int list_size(list_t *list) {
	return list->size;
}

void append_node(list_t *list, node_t *newNode, node_t *oldNode) {
	if (oldNode->next == NULL) {
		oldNode->next = newNode;
	} else {
		append_node(list, newNode, oldNode->next);
	}
}

void list_append(list_t *list, int item) {
	if (list_size(list) == 0) {
		node_t *node = malloc(sizeof(node_t));
		node->data = item;
		list->first = node;
		list->last = node;
	} else {
		node_t *node = malloc(sizeof(node_t));
		node->data = item;
		append_node(list, node, list->first);
		list->last = node;
	}
	list->size += 1;
}

bool list_insert(list_t *list, int item, int index) {
	if (index < 0 || list_size(list) == 0 || index >= list_size(list)) {
		return false;
	}
	bool firstItem = index == 0;
	bool lastItem = index == (list_size(list) - 1);
	bool appendItem = index == list_size(list);

	if (appendItem) {
		list_append(list, item);
	} else {
		node_t *node = malloc(sizeof(node_t));
		node->data = item;
		if (firstItem) {
			if (list_size(list) > 1) {
				node->next = list->first;
				list->first = node;
			} else {
				list->first = node;
				list->last = node;
			}
		} else if (lastItem) {
			node_t *preNode = node_get(list, list_size(list) - 2);
			node_t *lastNode = preNode->next;
			preNode->next = node;
			node->next = lastNode;
		} else {
			node_t *preNode = node_get(list, index - 1);
			node_t *postNode = preNode->next;
			preNode->next = node;
			node->next = postNode;
		}
	}

	list->size += 1;
	return true;
}

bool list_remove(list_t *list, int index) {
	if (index < 0 || list_size(list) == 0) {
		return false;
	}
	bool firstItem = index == 0;
	bool lastItem = index == list_size(list) - 1;
	if (firstItem) {
		if (list_size(list) > 1) {
			node_t *node = list->first;
			node_t *new_first = node->next;
			list->first = new_first;
		} else {
			list->first = NULL;
			list->last = NULL;
		}
	} else if (lastItem) {
		node_t *preNode = node_get(list, index - 1);
		preNode->next = NULL;
		list->last = preNode;
	} else {
		node_t *preNode = node_get(list, index - 1);
		node_t *node = preNode->next;
		node_t *postNode = node->next;
		preNode->next = postNode;
		node = NULL;
	}
	list->size -= 1;
	return true;
}

int list_find(list_t *list, int item) {
	return node_find(list, list->first, item, 0);
}

int node_find(list_t *list, node_t *node, int item, int currentIndex) {
	if (node == NULL) {
		return -1;
	}
	if (node->data == item) {
		return currentIndex;
	} else {
		if (node->next == NULL) {
			return -1;
		} else {
			return node_find(list, node->next, item, ++currentIndex);
		}
	}
}

int list_get(list_t *list, int index) {
	node_t *node = node_get(list, index);
	return node != NULL ? node->data : -1;
}
