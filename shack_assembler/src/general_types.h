#pragma once

#include <stddef.h>

#define DEFAULT_ARRAY_LIST_STEP 16

struct map_entry {
	void* key;
	size_t key_length;
	void* value;
	size_t value_length;
};

typedef struct map_entry t_map_entry;

enum array_list_type {
	LIST,
	MAP,
};

typedef enum array_list_type t_array_list_type;

struct array_list {
	t_array_list_type type;
	void** item;
	size_t capacity;
	size_t increase_step;
	size_t length;
};

typedef struct array_list t_array_list;

int create_array_list(t_array_list** buffer);
int create_hash_map(t_array_list** buffer);
int create_custom_array_list(t_array_list** buffer, t_array_list_type type, size_t starting_capacity, size_t capacity_steps);

int increment_array_list_capacity(t_array_list* array_list);

int add_item_to_array_list(t_array_list* array_list, void* item);
int add_entry_to_array_list(t_array_list* array_list, void* key, size_t key_length, void* value, size_t value_length);

int has_item_array_list(t_array_list* array_list, void* item);
int contains_str_key_array_list(t_array_list* array_list, const char* key, size_t key_length);
int contains_key_array_list(t_array_list* array_list, void* key, size_t key_length);
int contains_value_array_list(t_array_list* array_list, void* value, size_t value_length);

size_t get_item_index_from_array_list(t_array_list* array_list, void* item);
void* get_value_with_str_key_from_array_list(t_array_list* array_list, const char* key, size_t key_length);
void* get_value_with_key_from_array_list(t_array_list* array_list, void* key, size_t key_length);
void* get_item_from_array_list(t_array_list* array_list, size_t index);

int remove_entry_from_array_list(t_array_list* array_list, void* key, size_t key_length);
int remove_item_from_array_list(t_array_list* array_list, void* item);

void dispose_array_list(t_array_list* array_list);