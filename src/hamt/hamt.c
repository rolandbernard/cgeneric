
#include <stdalign.h>

#include "hamt.h"

static size_t TYPED(countBits)(uint32_t keymap) {
    keymap = keymap - ((keymap >> 1) & 0x55555555);
    keymap = (keymap & 0x33333333) + ((keymap >> 2) & 0x33333333);
    keymap = (keymap + (keymap >> 4)) & 0x0F0F0F0F;
    return (keymap * 0x01010101) >> 24;
}

static size_t TYPED(align)(size_t size, size_t align) {
    return (size + align - 1) / align * align;
}

static TYPED(HamtNode)* TYPED(createHamtNode)(size_t key_size, size_t tree_size) {
    size_t node_size = TYPED(align)(sizeof(TYPED(HamtNode)), alignof(KEY));
    node_size = TYPED(align)(node_size + key_size * sizeof(KEY), alignof(VALUE));
    node_size = TYPED(align)(node_size + key_size * sizeof(VALUE), alignof(TYPED(HamtNode)*));
    node_size = node_size + tree_size * sizeof(TYPED(HamtNode)*);
    TYPED(HamtNode)* node = ALLOC(char, node_size);
    node->refs = 1;
    return node;
}

static bool TYPED(hamtNodeIsBucket)(TYPED(HamtNode)* node) {
    return node->keymap == 0xffffffff && node->treemap != 0;
}

static size_t TYPED(hamtNodeKeySize)(TYPED(HamtNode)* node) {
    if (TYPED(hamtNodeIsBucket)(node)) {
        return node->treemap;
    } else {
        return TYPED(countBits)(node->keymap);
    }
}

static size_t TYPED(hamtNodeTreeSize)(TYPED(HamtNode)* node) {
    if (node->keymap == 0xffffffff) {
        return 0;
    } else {
        return TYPED(countBits)(node->treemap);
    }
}

static KEY* TYPED(hamtNodeKeys)(TYPED(HamtNode)* node) {
    size_t offset = TYPED(align)(sizeof(TYPED(HamtNode)), alignof(KEY));
    return (KEY*)((void*)node + offset);
}

static VALUE* TYPED(hamtNodeValues)(TYPED(HamtNode)* node, size_t key_size) {
    size_t offset = TYPED(align)(sizeof(TYPED(HamtNode)), alignof(KEY));
    offset = TYPED(align)(offset + key_size * sizeof(KEY), alignof(VALUE));
    return (VALUE*)((void*)node + offset);
}

static TYPED(HamtNode)** TYPED(hamtNodeTrees)(TYPED(HamtNode)* node, size_t key_size) {
    size_t offset = TYPED(align)(sizeof(TYPED(HamtNode)), alignof(KEY));
    offset = TYPED(align)(offset + key_size * sizeof(KEY), alignof(VALUE));
    offset = TYPED(align)(offset + key_size * sizeof(VALUE), alignof(TYPED(HamtNode)*));
    return (TYPED(HamtNode)**)((void*)node + offset);
}

static void TYPED(copyHamtNode)(TYPED(HamtNode)* node) {
    node->refs += 1;
}

static void TYPED(freeHamtNode)(TYPED(HamtNode)* node) {
    node->refs -= 1;
    if (node->refs == 0) {
        size_t key_size = TYPED(hamtNodeKeySize)(node);
        size_t tree_size = TYPED(hamtNodeTreeSize)(node);
        TYPED(HamtNode)** trees = TYPED(hamtNodeTrees)(node, key_size);
        for (size_t i = 0; i < tree_size; i++) {
            TYPED(freeHamtNode)(trees[i]);
        }
        FREE(node);
    }
}

void TYPED(initHamt)(TYPED(Hamt)* table) {
    table->root = NULL;
}

void TYPED(deinitHamt)(TYPED(Hamt)* table) {
    if (table->root != NULL) {
        TYPED(freeHamtNode)(table->root);
        table->root = NULL;
    }
}

void TYPED(copyHamt)(TYPED(Hamt)* destination, TYPED(Hamt)* source) {
    TYPED(deinitHamt)(destination);
    TYPED(copyHamtNode)(source->root);
    destination->root = source->root;
}

static size_t TYPED(sizeOfHamtNode)(TYPED(HamtNode)* node) {
    size_t key_size = TYPED(hamtNodeKeySize)(node);
    size_t tree_size = TYPED(hamtNodeTreeSize)(node);
    TYPED(HamtNode)** trees = TYPED(hamtNodeTrees)(node, key_size);
    size_t size = key_size;
    for (size_t i = 0; i < tree_size; i++) {
        size += TYPED(sizeOfHamtNode)(trees[i]);
    }
    return size;
}

size_t TYPED(sizeOfHamt)(TYPED(Hamt)* table) {
    if (table->root == NULL) {
        return 0;
    } else {
        return TYPED(sizeOfHamtNode)(table->root);
    }
}

static uint32_t TYPED(hamtLevelIndex)(uint64_t hash, size_t depth) {
    return (hash >> (5 * depth)) & 0x1f;
}

static TYPED(HamtNode)* TYPED(mergeHamtNode)(KEY key1, VALUE value1, uint64_t hash1, KEY key2, VALUE value2, uint64_t hash2, size_t depth) {
    if (hash1 == hash2) {
        TYPED(HamtNode)* node = TYPED(createHamtNode)(2, 0);
        node->keymap = 0xffffffff;
        node->treemap = 2;
        KEY* keys = TYPED(hamtNodeKeys)(node);
        VALUE* values = TYPED(hamtNodeValues)(node, 2);
        keys[0] = key1;
        keys[1] = key2;
        values[0] = value1;
        values[1] = value2;
        return node;
    } else {
        uint32_t idx_mask1 = 1 << TYPED(hamtLevelIndex)(hash1, depth);
        uint32_t idx_mask2 = 1 << TYPED(hamtLevelIndex)(hash2, depth);
        if (idx_mask1 == idx_mask2) {
            TYPED(HamtNode)* node = TYPED(createHamtNode)(0, 1);
            node->keymap = 0;
            node->treemap = idx_mask1;
            TYPED(HamtNode)** trees = TYPED(hamtNodeTrees)(node, 2);
            trees[0] = TYPED(mergeHamtNode)(key1, value1, hash1, key2, value2, hash2, depth + 1);
            return node;
        } else {
            TYPED(HamtNode)* node = TYPED(createHamtNode)(2, 0);
            node->keymap = idx_mask1 | idx_mask2;
            node->treemap = 0;
            KEY* keys = TYPED(hamtNodeKeys)(node);
            VALUE* values = TYPED(hamtNodeValues)(node, 2);
            size_t first = idx_mask1 < idx_mask2 ? 0 : 1;
            keys[first] = key1;
            keys[1 - first] = key2;
            values[first] = value1;
            values[1 - first] = value2;
            return node;
        }
    }
}

static bool TYPED(putInHamtNode)(TYPED(HamtNode)** node_ref, KEY key, VALUE value, uint64_t hash, size_t depth, bool allow_reuse) {
    TYPED(HamtNode)* node = *node_ref;
    allow_reuse = allow_reuse && node->refs == 1;
    size_t key_size = TYPED(hamtNodeKeySize)(node);
    size_t tree_size = TYPED(hamtNodeTreeSize)(node);
    KEY* keys = TYPED(hamtNodeKeys)(node);
    VALUE* values = TYPED(hamtNodeValues)(node, key_size);
    TYPED(HamtNode)** trees = TYPED(hamtNodeTrees)(node, key_size);
    if (TYPED(hamtNodeIsBucket)(node)) {
        for (size_t i = 0; i < key_size; i++) {
            if (EQUALS(key, keys[i])) {
                if (allow_reuse) {
                    values[i] = value;
                } else {
                    TYPED(HamtNode)* new_node = TYPED(createHamtNode)(key_size, 0);
                    new_node->keymap = node->keymap;
                    new_node->treemap = node->treemap;
                    KEY* new_keys = TYPED(hamtNodeKeys)(new_node);
                    VALUE* new_values = TYPED(hamtNodeValues)(new_node, key_size);
                    memcpy(new_keys, keys, key_size * sizeof(KEY));
                    memcpy(new_values, values, key_size * sizeof(VALUE));
                    values[i] = value;
                    TYPED(freeHamtNode)(node);
                    *node_ref = new_node;
                }
                return false;
            }
        }
        TYPED(HamtNode)* new_node = TYPED(createHamtNode)(key_size + 1, 0);
        new_node->keymap = node->keymap;
        new_node->treemap = node->treemap + 1;
        KEY* new_keys = TYPED(hamtNodeKeys)(new_node);
        VALUE* new_values = TYPED(hamtNodeValues)(new_node, key_size + 1);
        memcpy(new_keys, keys, key_size * sizeof(KEY));
        memcpy(new_values, values, key_size * sizeof(VALUE));
        keys[key_size] = key;
        values[key_size] = value;
        TYPED(freeHamtNode)(node);
        *node_ref = new_node;
        return true;
    } else {
        uint32_t idx_mask = 1 << TYPED(hamtLevelIndex)(hash, depth);
        if ((node->keymap & idx_mask) != 0) {
            uint32_t idx = TYPED(countBits)(node->keymap & (idx_mask - 1));
            if (EQUALS(key, keys[idx])) {
                if (allow_reuse) {
                    values[idx] = value;
                } else {
                    TYPED(HamtNode)* new_node = TYPED(createHamtNode)(key_size, tree_size);
                    new_node->keymap = node->keymap;
                    new_node->treemap = node->treemap;
                    KEY* new_keys = TYPED(hamtNodeKeys)(new_node);
                    VALUE* new_values = TYPED(hamtNodeValues)(new_node, key_size);
                    TYPED(HamtNode)** new_trees = TYPED(hamtNodeTrees)(new_node, key_size);
                    memcpy(new_keys, keys, key_size * sizeof(KEY));
                    memcpy(new_values, values, key_size * sizeof(VALUE));
                    memcpy(new_trees, trees, tree_size * sizeof(TYPED(HamtNode)*));
                    values[idx] = value;
                    for (size_t i = 0; i < tree_size; i++) {
                        TYPED(copyHamtNode)(new_trees[i]);
                    }
                    TYPED(freeHamtNode)(node);
                    *node_ref = new_node;
                }
                return false;
            } else {
                TYPED(HamtNode)* new_tree = TYPED(mergeHamtNode)(key, value, hash, keys[idx], values[idx], HASH(keys[idx]), depth + 1);
                size_t new_idx = TYPED(countBits)(node->treemap & (idx_mask - 1));
                if (allow_reuse) {
                    node->keymap &= ~idx_mask;
                    node->treemap |= idx_mask;
                    KEY* new_keys = TYPED(hamtNodeKeys)(node);
                    VALUE* new_values = TYPED(hamtNodeValues)(node, key_size - 1);
                    TYPED(HamtNode)** new_trees = TYPED(hamtNodeTrees)(node, key_size - 1);
                    memmove(new_keys, keys, idx * sizeof(KEY));
                    memmove(new_keys + idx, keys + idx + 1, (key_size - 1 - idx) * sizeof(KEY));
                    memmove(new_values, values, idx * sizeof(KEY));
                    memmove(
                        new_values + idx, values + idx + 1, (key_size - 1 - idx) * sizeof(VALUE)
                    );
                    memmove(new_trees, trees, new_idx * sizeof(TYPED(HamtNode)*));
                    memmove(
                        new_trees + new_idx + 1, trees + new_idx,
                        (tree_size - new_idx) * sizeof(TYPED(HamtNode)*)
                    );
                    new_trees[new_idx] = new_tree;
                } else {
                    TYPED(HamtNode)* new_node = TYPED(createHamtNode)(key_size - 1, tree_size + 1);
                    new_node->keymap = node->keymap & ~idx_mask;
                    new_node->treemap = node->treemap | idx_mask;
                    KEY* new_keys = TYPED(hamtNodeKeys)(new_node);
                    VALUE* new_values = TYPED(hamtNodeValues)(new_node, key_size - 1);
                    TYPED(HamtNode)** new_trees = TYPED(hamtNodeTrees)(new_node, key_size - 1);
                    memcpy(new_keys, keys, idx * sizeof(KEY));
                    memcpy(new_keys + idx, keys + idx + 1, (key_size - 1 - idx) * sizeof(KEY));
                    memcpy(new_values, values, idx * sizeof(KEY));
                    memcpy(
                        new_values + idx, values + idx + 1, (key_size - 1 - idx) * sizeof(VALUE)
                    );
                    memcpy(new_trees, trees, new_idx * sizeof(TYPED(HamtNode)*));
                    memcpy(
                        new_trees + new_idx + 1, trees + new_idx,
                        (tree_size - new_idx) * sizeof(TYPED(HamtNode)*)
                    );
                    new_trees[new_idx] = new_tree;
                    for (size_t i = 0; i < tree_size; i++) {
                        if (i != new_idx) {
                            TYPED(copyHamtNode)(new_trees[i]);
                        }
                    }
                    TYPED(freeHamtNode)(node);
                    *node_ref = new_node;
                }
                return true;
            }
        } else if ((node->treemap & idx_mask) != 0) {
            uint32_t idx = TYPED(countBits)(node->treemap & (idx_mask - 1));
            TYPED(HamtNode)* new_tree = trees[idx];
            bool result = TYPED(putInHamtNode)(&new_tree, key, value, hash, depth + 1, allow_reuse);
            if (allow_reuse) {
                TYPED(freeHamtNode)(trees[idx]);
                trees[idx] = new_tree;
            } else {
                TYPED(HamtNode)* new_node = TYPED(createHamtNode)(key_size, tree_size);
                new_node->keymap = node->keymap;
                new_node->treemap = node->treemap;
                KEY* new_keys = TYPED(hamtNodeKeys)(new_node);
                VALUE* new_values = TYPED(hamtNodeValues)(new_node, key_size);
                TYPED(HamtNode)** new_trees = TYPED(hamtNodeTrees)(new_node, key_size);
                memcpy(new_keys, keys, key_size * sizeof(KEY));
                memcpy(new_values, values, key_size * sizeof(VALUE));
                memcpy(new_trees, trees, tree_size * sizeof(TYPED(HamtNode)*));
                new_trees[idx] = new_tree;
                for (size_t i = 0; i < tree_size; i++) {
                    if (i != idx) {
                        TYPED(copyHamtNode)(new_trees[i]);
                    }
                }
                TYPED(freeHamtNode)(node);
                *node_ref = new_node;
            }
            return result;
        } else {
            uint32_t idx = TYPED(countBits)(node->keymap & (idx_mask - 1));
            TYPED(HamtNode)* new_node = TYPED(createHamtNode)(key_size + 1, tree_size);
            new_node->keymap = node->keymap | idx_mask;
            new_node->treemap = node->treemap;
            KEY* new_keys = TYPED(hamtNodeKeys)(new_node);
            VALUE* new_values = TYPED(hamtNodeValues)(new_node, key_size + 1);
            TYPED(HamtNode)** new_trees = TYPED(hamtNodeTrees)(new_node, key_size + 1);
            memcpy(new_keys, keys, idx * sizeof(KEY));
            memcpy(new_keys + idx + 1, keys + idx, (key_size - idx) * sizeof(KEY));
            memcpy(new_values, values, idx * sizeof(KEY));
            memcpy(new_values + idx + 1, values + idx, (key_size - idx) * sizeof(VALUE));
            memcpy(new_trees, trees, tree_size * sizeof(TYPED(HamtNode)*));
            new_keys[idx] = key;
            new_values[idx] = value;
            for (size_t i = 0; i < tree_size; i++) {
                TYPED(copyHamtNode)(new_trees[i]);
            }
            TYPED(freeHamtNode)(node);
            *node_ref = new_node;
            return true;
        }
    }
}

bool TYPED(putInHamt)(TYPED(Hamt)* table, KEY key, VALUE value) {
    return TYPED(putInHamtNode)(&table->root, key, value, HASH(key), 0, true);
}

static bool TYPED(getFromHamtNode)(TYPED(HamtNode)* node, KEY key, VALUE* value, uint64_t hash, size_t depth) {
    size_t key_size = TYPED(hamtNodeKeySize)(node);
    KEY* keys = TYPED(hamtNodeKeys)(node);
    VALUE* values = TYPED(hamtNodeValues)(node, key_size);
    TYPED(HamtNode)** trees = TYPED(hamtNodeTrees)(node, key_size);
    if (TYPED(hamtNodeIsBucket)(node)) {
        for (size_t i = 0; i < key_size; i++) {
            if (EQUALS(key, keys[i])) {
                if (value != NULL) {
                    *value = values[i];
                }
                return true;
            }
        }
        return false;
    } else {
        uint32_t idx_mask = 1 << TYPED(hamtLevelIndex)(hash, depth);
        if ((node->keymap & idx_mask) != 0) {
            uint32_t idx = TYPED(countBits)(node->keymap & (idx_mask - 1));
            if (EQUALS(key, keys[idx])) {
                if (value != NULL) {
                    *value = values[idx];
                }
                return true;
            } else {
                return false;
            }
        } else if ((node->treemap & idx_mask) != 0) {
            uint32_t idx = TYPED(countBits)(node->treemap & (idx_mask - 1));
            return TYPED(getFromHamtNode)(trees[idx], key, value, hash, depth + 1);
        } else {
            return false;
        }
    }
}

bool TYPED(getFromHamt)(TYPED(Hamt)* table, KEY key, VALUE* value) {
    return TYPED(getFromHamtNode)(table->root, key, value, HASH(key), 0);
}

static bool TYPED(deleteFromHamtNode)(TYPED(HamtNode)** node_ref, KEY key, uint64_t hash, size_t depth, bool allow_reuse) {
    TYPED(HamtNode)* node = *node_ref;
    allow_reuse = allow_reuse && node->refs == 1;
    size_t key_size = TYPED(hamtNodeKeySize)(node);
    size_t tree_size = TYPED(hamtNodeTreeSize)(node);
    KEY* keys = TYPED(hamtNodeKeys)(node);
    VALUE* values = TYPED(hamtNodeValues)(node, key_size);
    TYPED(HamtNode)** trees = TYPED(hamtNodeTrees)(node, key_size);
    if (TYPED(hamtNodeIsBucket)(node)) {
        for (size_t i = 0; i < key_size; i++) {
            if (EQUALS(key, keys[i])) {
                if (key_size == 1) {
                    TYPED(freeHamtNode)(node);
                    *node_ref = NULL;
                } else if (allow_reuse) {
                    node->keymap = node->keymap;
                    node->treemap = node->treemap - 1;
                    KEY* new_keys = TYPED(hamtNodeKeys)(node);
                    VALUE* new_values = TYPED(hamtNodeValues)(node, key_size - 1);
                    TYPED(HamtNode)** new_trees = TYPED(hamtNodeTrees)(node, key_size - 1);
                    memmove(new_keys, keys, i * sizeof(KEY));
                    memmove(new_keys + i, keys + i + 1, (key_size - 1 - i) * sizeof(KEY));
                    memmove(new_values, values, i * sizeof(KEY));
                    memmove(new_values + i, values + i + 1, (key_size - 1 - i) * sizeof(VALUE));
                    memmove(new_trees, trees, tree_size * sizeof(TYPED(HamtNode)*));
                } else {
                    TYPED(HamtNode)* new_node = TYPED(createHamtNode)(key_size - 1, 0);
                    new_node->keymap = node->keymap;
                    new_node->treemap = node->treemap - 1;
                    KEY* new_keys = TYPED(hamtNodeKeys)(new_node);
                    VALUE* new_values = TYPED(hamtNodeValues)(new_node, key_size - 1);
                    memcpy(new_keys, keys, i * sizeof(KEY));
                    memcpy(new_values, values, i * sizeof(VALUE));
                    memcpy(new_keys + i, keys + i + 1, (key_size - 1 - i) * sizeof(KEY));
                    memcpy(new_values + i, values + i + 1, (key_size - 1 - i) * sizeof(VALUE));
                    TYPED(freeHamtNode)(node);
                    *node_ref = new_node;
                }
                return true;
            }
        }
        return false;
    } else {
        uint32_t idx_mask = 1 << TYPED(hamtLevelIndex)(hash, depth);
        if ((node->keymap & idx_mask) != 0) {
            uint32_t idx = TYPED(countBits)(node->keymap & (idx_mask - 1));
            if (EQUALS(key, keys[idx])) {
                if (key_size == 1 && tree_size == 0) {
                    TYPED(freeHamtNode)(node);
                    *node_ref = NULL;
                } else if (allow_reuse) {
                    node->keymap = node->keymap & ~idx_mask;
                    node->treemap = node->treemap;
                    KEY* new_keys = TYPED(hamtNodeKeys)(node);
                    VALUE* new_values = TYPED(hamtNodeValues)(node, key_size - 1);
                    TYPED(HamtNode)** new_trees = TYPED(hamtNodeTrees)(node, key_size - 1);
                    memmove(new_keys, keys, idx * sizeof(KEY));
                    memmove(new_keys + idx, keys + idx + 1, (key_size - 1 - idx) * sizeof(KEY));
                    memmove(new_values, values, idx * sizeof(VALUE));
                    memmove(
                        new_values + idx, values + idx + 1, (key_size - 1 - idx) * sizeof(VALUE)
                    );
                    memmove(new_trees, trees, tree_size * sizeof(TYPED(HamtNode)*));
                } else {
                    TYPED(HamtNode)* new_node = TYPED(createHamtNode)(key_size - 1, tree_size);
                    new_node->keymap = node->keymap & ~idx_mask;
                    new_node->treemap = node->treemap;
                    KEY* new_keys = TYPED(hamtNodeKeys)(new_node);
                    VALUE* new_values = TYPED(hamtNodeValues)(new_node, key_size - 1);
                    TYPED(HamtNode)** new_trees = TYPED(hamtNodeTrees)(new_node, key_size - 1);
                    memcpy(new_keys, keys, idx * sizeof(KEY));
                    memcpy(new_keys + idx, keys + idx + 1, (key_size - 1 - idx) * sizeof(KEY));
                    memcpy(new_values, values, idx * sizeof(VALUE));
                    memcpy(
                        new_values + idx, values + idx + 1, (key_size - 1 - idx) * sizeof(VALUE)
                    );
                    memcpy(new_trees, trees, tree_size * sizeof(TYPED(HamtNode)*));
                    for (size_t i = 0; i < tree_size; i++) {
                        TYPED(copyHamtNode)(new_trees[i]);
                    }
                    TYPED(freeHamtNode)(node);
                    *node_ref = new_node;
                }
                return true;
            } else {
                return false;
            }
        } else if ((node->treemap & idx_mask) != 0) {
            uint32_t idx = TYPED(countBits)(node->treemap & (idx_mask - 1));
            TYPED(HamtNode)* new_tree = trees[idx];
            if (TYPED(deleteFromHamtNode)(&new_tree, key, hash, depth + 1, allow_reuse)) {
                if (new_tree == NULL) {
                    if (key_size == 0 && tree_size == 1) {
                        TYPED(freeHamtNode)(node);
                        *node_ref = NULL;
                    } else if (allow_reuse) {
                        node->keymap = node->keymap;
                        node->treemap = node->treemap & ~idx_mask;
                        memmove(
                            trees + idx, trees + idx + 1,
                            (tree_size - 1 - idx) * sizeof(TYPED(HamtNode)*)
                        );
                    } else {
                        TYPED(HamtNode)* new_node = TYPED(createHamtNode)(key_size, tree_size - 1);
                        new_node->keymap = node->keymap;
                        new_node->treemap = node->treemap & ~idx_mask;
                        KEY* new_keys = TYPED(hamtNodeKeys)(new_node);
                        VALUE* new_values = TYPED(hamtNodeValues)(new_node, key_size);
                        TYPED(HamtNode)** new_trees = TYPED(hamtNodeTrees)(new_node, key_size);
                        memcpy(new_keys, keys, key_size * sizeof(KEY));
                        memcpy(new_values, values, key_size * sizeof(VALUE));
                        memcpy(new_trees, trees, idx * sizeof(TYPED(HamtNode)*));
                        memcpy(
                            new_trees + idx, trees + idx + 1,
                            (tree_size - 1 - idx) * sizeof(TYPED(HamtNode)*)
                        );
                        for (size_t i = 0; i < tree_size - 1; i++) {
                            TYPED(copyHamtNode)(new_trees[i]);
                        }
                        TYPED(freeHamtNode)(node);
                        *node_ref = new_node;
                    }
                } else if (allow_reuse) {
                    TYPED(freeHamtNode)(trees[idx]);
                    trees[idx] = new_tree;
                } else {
                    TYPED(HamtNode)* new_node = TYPED(createHamtNode)(key_size, tree_size);
                    new_node->keymap = node->keymap;
                    new_node->treemap = node->treemap;
                    KEY* new_keys = TYPED(hamtNodeKeys)(new_node);
                    VALUE* new_values = TYPED(hamtNodeValues)(new_node, key_size);
                    TYPED(HamtNode)** new_trees = TYPED(hamtNodeTrees)(new_node, key_size);
                    memcpy(new_keys, keys, key_size * sizeof(KEY));
                    memcpy(new_values, values, key_size * sizeof(VALUE));
                    memcpy(new_trees, trees, tree_size * sizeof(TYPED(HamtNode)*));
                    new_trees[idx] = new_tree;
                    for (size_t i = 0; i < tree_size; i++) {
                        if (i != idx) {
                            TYPED(copyHamtNode)(new_trees[i]);
                        }
                    }
                    TYPED(freeHamtNode)(node);
                    *node_ref = new_node;
                }
                return true;
            } else {
                return false;
            }
        } else {
            return false;
        }
    }
}

bool TYPED(deleteFromHamt)(TYPED(Hamt)* table, KEY key) {
    return TYPED(deleteFromHamtNode)(&table->root, key, HASH(key), 0, true);
}
