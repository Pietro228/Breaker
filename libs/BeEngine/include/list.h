#pragma once

#include <stdio.h>
#include <stdlib.h>

// Macros

/**
 * Typedef a new list struct.
 *
 * Enter item type without the list pointer. Item type of "char" will automatically become "char*" list.
 * Using pointers as items "char*" will result in a "char**" list.
 *
 * \param name name of the list
 * \param itemType type of the items
 */
#define DEFINE_LIST(name, itemType) \
    typedef struct name {           \
        itemType* items;            \
        size_t size;                \
        size_t _capacity;           \
    } name;

#define LIST_INIT(listStruct)     \
    {                             \
        listStruct.size = 0;      \
        listStruct._capacity = 0; \
        listStruct.items = NULL;  \
    }

/**
 * Allocate a new list struct.
 *
 * Uses malloc to allocate memory.
 *
 * \param type list data type
 * \param size size of list
 */
#define LIST_NEW(listStruct, itemType, _size)                               \
    {                                                                       \
        listStruct.items = (itemType*)malloc(sizeof(itemType) * _size * 2); \
        listStruct.size = _size;                                            \
        listStruct._capacity = _size * 2;                                   \
    }

#define LIST_ADD(listStruct, itemType, itemToAdd)                                                             \
    {                                                                                                         \
        if (listStruct.size + 1 > listStruct._capacity) {                                                     \
            if (listStruct._capacity == 0) listStruct._capacity = 1;                                          \
            listStruct._capacity *= 2;                                                                        \
            listStruct.items = (itemType*)realloc(listStruct.items, sizeof(itemType) * listStruct._capacity); \
        }                                                                                                     \
        listStruct.items[listStruct.size++] = itemToAdd;                                                      \
    }

#define LIST_REMOVE(listStruct, itemType, itemIndex)                                                          \
    {                                                                                                         \
        for (size_t i = itemIndex; i < listStruct.size - 1; i++) {                                            \
            listStruct.items[i] = listStruct.items[i + 1];                                                    \
        }                                                                                                     \
        listStruct.size -= 1;                                                                                 \
        if (listStruct._capacity / 2 >= listStruct.size) {                                                    \
            listStruct._capacity /= 2;                                                                        \
            listStruct.items = (itemType*)realloc(listStruct.items, sizeof(itemType) * listStruct._capacity); \
        }                                                                                                     \
    }

#define LIST_REMOVE_CLEAN(listStruct, itemType, itemIndex)                                                    \
    {                                                                                                         \
        free(listStruct.items[itemIndex]);                                                                    \
        listStruct.items[itemIndex] = NULL;                                                                   \
        for (size_t i = itemIndex; i < listStruct.size - 1; i++) {                                            \
            listStruct.items[i] = listStruct.items[i + 1];                                                    \
        }                                                                                                     \
        listStruct.size -= 1;                                                                                 \
        if (listStruct._capacity / 2 >= listStruct.size) {                                                    \
            listStruct._capacity /= 2;                                                                        \
            listStruct.items = (itemType*)realloc(listStruct.items, sizeof(itemType) * listStruct._capacity); \
        }                                                                                                     \
    }

// TODO: List contains může mít v sobě LIST_FIND_INDEX a nemusí se tak opakovat ta samá logika
#define LIST_CONTAINS(listStruct, itemType, propertyToCheck, valueToCheck) ({ \
    int result = 0;                                                           \
    for (size_t i = 0; i < listStruct.size; i++) {                            \
        if (listStruct.items[i] propertyToCheck == valueToCheck) {            \
            result = 1;                                                       \
            break;                                                            \
        }                                                                     \
    }                                                                         \
    result;                                                                   \
})

#define LIST_FIND_INDEX(listStruct, itemType, propertyToCheck, valueToCheck) ({ \
    size_t index = -1;                                                          \
    for (size_t i = 0; i < listStruct.size; i++) {                              \
        if (listStruct.items[i] propertyToCheck == valueToCheck) {              \
            index = i;                                                          \
            break;                                                              \
        }                                                                       \
    }                                                                           \
    index;                                                                      \
})

#define LIST_CLEAN(listStruct)    \
    {                             \
        free(listStruct.items);   \
        listStruct.items = NULL;  \
        listStruct.size = 0;      \
        listStruct._capacity = 0; \
    }

#define LIST_FOREACH(listStruct, itemType, itemName, iteratorName)                                                                     \
    for (int iteratorName = 0, __##iteratorName##temp = 1; iteratorName < listStruct.size; __##iteratorName##temp = 1, iteratorName++) \
        for (itemType itemName = listStruct.items[iteratorName]; __##iteratorName##temp; __##iteratorName##temp = 0)

// List definitions
DEFINE_LIST(IntList, int);
DEFINE_LIST(CharList, char);
DEFINE_LIST(FloatList, float);