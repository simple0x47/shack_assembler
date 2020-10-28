#include <stdio.h>
#include <stdlib.h>

#include "general_types.h"

int create_array_list(t_array_list** buffer) {
	return create_custom_array_list(buffer, LIST, DEFAULT_ARRAY_LIST_STEP, DEFAULT_ARRAY_LIST_STEP);
}

int create_hash_map(t_array_list** buffer) {
	return create_custom_array_list(buffer, MAP, DEFAULT_ARRAY_LIST_STEP, DEFAULT_ARRAY_LIST_STEP);
}

int create_custom_array_list(t_array_list** buffer, t_array_list_type type, size_t starting_capacity, size_t capacity_steps) {
	if (type < 0) {
		return -1;
	}
	
	if (starting_capacity <= 0) {
		return -1;
	}

	if (capacity_steps <= 0) {
		return -1;
	}
	
	t_array_list* array_list = malloc(sizeof(t_array_list));

	if (array_list == NULL) {
		return -1;
	}

	array_list->item = malloc(sizeof(void*) * starting_capacity);

	if (array_list->item == NULL) {
		return -1;
	}

	array_list->type = type;
	array_list->capacity = starting_capacity;
	array_list->increase_step = capacity_steps;
	array_list->length = 0L;

	*(buffer) = array_list;

	return 1;
}

int increment_array_list_capacity(t_array_list* array_list) {
	if (array_list == NULL) {
		return -1;
	}

	size_t new_capacity = (array_list->capacity) + (array_list->increase_step);
	void** new_item_buffer = realloc(array_list->item, sizeof(void*) * new_capacity);

	if (new_item_buffer == NULL) {
	    printf("Failed\n");
		return -1;
	}

	array_list->item = new_item_buffer;
	array_list->capacity = new_capacity;

	return 1;
}

int add_item_to_array_list(t_array_list* array_list, void* item) {
	if (array_list == NULL) {
		return -1;
	}

	if (item == NULL) {
		return -1;
	}

	if (has_item_array_list(array_list, item) > 0) {
		return -1;
	}

	if ((array_list->capacity) <= (array_list->length)) {
		if (increment_array_list_capacity(array_list) < 0) {
			return -1;
		}
	}

	*(array_list->item + (array_list->length)) = item;
	array_list->length += 1;

	return 1;
}

int add_entry_to_array_list(t_array_list* array_list, void* key, size_t key_length, void* value, size_t value_length) {
	if (array_list == NULL) {
		return -1;
	}

	if (key == NULL) {
		return -1;
	}

	if (key_length <= 0) {
		return -1;
	}

	if (value == NULL) {
		return -1;
	}

	if (value_length <= 0) {
		return -1;
	}

	t_map_entry* entry = malloc(sizeof(t_map_entry));

	if (entry == NULL) {
		return -1;
	}

	entry->key = key;
	entry->key_length = key_length;
	entry->value = value;
	entry->value_length = value_length;
	
	return add_item_to_array_list(array_list, entry);
}

int has_item_array_list(t_array_list* array_list, void* item) {
	if (array_list == NULL) {
		return -1;
	}

	if (item == NULL) {
		return -1;
	}

	for (size_t i = 0; i < (array_list->length); i++) {
        if (item == (array_list->item[i])) {
            return 1;
        }
	}

	return 0;
}

int contains_str_key_array_list(t_array_list* array_list, const char* key, size_t key_length) {
    if (array_list == NULL) {
        return -1;
    }

    if (array_list->type != MAP) {
        return -1;
    }

    if (key == NULL) {
        return -1;
    }

    if (key_length <= 0) {
        return -1;
    }

    for (int i = 0; i < array_list->length; i++) {
        t_map_entry* entry = *(array_list->item + i);

        if (entry->key_length == key_length) {
            char* entry_key = (char*)entry->key;

            for (int j = 0; j < key_length; j++) {
                if (key[j] == entry_key[j]) {
                    /* Detect if this is the last character */
                    if ((j + 1) == key_length) {
                        return 1;
                    }
                }
                else {
                    break;
                }
            }
        }
    }

    return 0;
}

int contains_key_array_list(t_array_list* array_list, void* key, size_t key_length) {
	if (array_list == NULL) {
		return -1;
	}

	if (array_list->type != MAP) {
		return -1;
	}

	if (key == NULL) {
		return -1;
	}

	if (key_length <= 0) {
		return -1;
	}

	for (int i = 0; i < array_list->length; i++) {
		t_map_entry* entry = *(array_list->item + i);

		if (entry->key_length == key_length) {
			for (int j = 0; j < key_length; j++) {
				if (entry->key == key) {
					return 1;
				}
			}
		}
	}

	return 0;
}

int contains_value_array_list(t_array_list* array_list, void* value, size_t value_length) {
	if (array_list == NULL) {
		return -1;
	}
	
	if (array_list->type != MAP) {
		return -1;
	}

	if (value == NULL) {
		return -1;
	}

	if (value_length <= 0) {
		return -1;
	}

	for (int i = 0; i < array_list->length; i++) {
		t_map_entry* entry = *(array_list->item + i);

		if (entry->value_length == value_length) {
			for (int j = 0; j < value_length; j++) {
				if (entry->value == value) {
					return 1;
				}
			}
		}
	}

	return 0;
}

size_t get_item_index_from_array_list(t_array_list* array_list, void* item) {
	if (array_list == NULL) {
		return -1;
	}

	if (item == NULL) {
		return -1;
	}

	if (!has_item_array_list(array_list, item)) {
		return -1;
	}

	for (size_t i = 0; i < array_list->length; i++) {
		if (item == *(array_list->item + i)) {
			return i;
		}
	}

	return -1;
}

void* get_value_with_str_key_from_array_list(t_array_list* array_list, const char* key, size_t key_length) {
    if (array_list == NULL) {
        return NULL;
    }

    if (array_list->type != MAP) {
        return NULL;
    }

    if (key == NULL) {
        return NULL;
    }

    if (key_length <= 0) {
        return NULL;
    }

    for (int i = 0; i < array_list->length; i++) {
        t_map_entry* entry = *(array_list->item + i);

        if (entry->key_length == key_length) {
            char* entry_key = (char*)entry->key;

            for (int j = 0; j < key_length; j++) {
                if (key[j] == entry_key[j]) {
                    /* Detect if this is the last character */
                    if ((j + 1) == key_length) {
                        return entry->value;
                    }
                }
                else {
                    break;
                }
            }
        }
    }

    return NULL;
}

void* get_value_with_key_from_array_list(t_array_list* array_list, void* key, size_t key_length) {
	if (array_list == NULL) {
		return NULL;
	}

	if (array_list->type != MAP) {
		return NULL;
	}

	if (key == NULL) {
		return NULL;
	}

	if (!contains_key_array_list(array_list, key, key_length)) {
		return NULL;
	}

	for (size_t i = 0; i < array_list->length; i++) {
		t_map_entry* entry = *(array_list->item + i);

		if (entry->key_length == key_length) {
			if (entry->key == key) {
				return entry->value;
			}
		}
	}

	return NULL;
}

void* get_item_from_array_list(t_array_list* array_list, size_t index) {
	if (array_list == NULL) {
		return NULL;
	}

	if (index < 0) {
		return NULL;
	}

	if (index >= array_list->length) {
		return NULL;
	}

	return *(array_list->item + index);
}

int remove_entry_from_array_list(t_array_list* array_list, void* key, size_t key_length) {
	if (array_list == NULL) {
		return -1;
	}

	if (array_list->type != MAP) {
		return -1;
	}

	if (key == NULL) {
		return -1;
	}

	if (key_length <= 0) {
		return -1;
	}

	if (contains_key_array_list(array_list, key, key_length) <= 0) {
		return -1;
	}

	for (size_t i = 0; i < array_list->length; i++) {
		t_map_entry* entry = *(array_list->item + i);

		if (entry->key == key) {
			return remove_item_from_array_list(array_list, entry);
		}
	}

	return -1;
}

int remove_item_from_array_list(t_array_list* array_list, void* item) {
	if (array_list == NULL) {
		return -1;
	}

	if (item == NULL) {
		return -1;
	}

	if (!has_item_array_list(array_list, item)) {
		return -1;
	}

	size_t item_index = get_item_index_from_array_list(array_list, item);

	for (size_t i = item_index; i < array_list->length; i++) {
		if ((i + 1) == array_list->length) {
			*(array_list->item + i) = NULL;
		}
		else {
			*(array_list->item + i) = *(array_list->item + i + 1);
		}
	}

	array_list->length -= 1;

	return 1;
}

void dispose_array_list(t_array_list* array_list) {
	if (array_list == NULL) {
		return;
	}

	free(array_list);
}