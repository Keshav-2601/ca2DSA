#include "BinaryTree.h";
template <typename K, typename V>
class TreeMap {
private:
    struct KeyValuePair {
        K key;
        V value;

        KeyValuePair(K key, V value) : key(key), value(value) {
        
        }
        bool operator<(const KeyValuePair& other) const {
            return key < other.key;
        }
        bool operator==(const KeyValuePair& other) const {
            return key == other.key;
        }
    };
    BinaryTree<KeyValuePair> tree;
public:
    TreeMap();
    void clear();
    bool containsKey(K key);
    V& get(K key);
    BinaryTree<K>* keySet();
    void put(K key, V value);
    int size();
    bool removeKey(K key);
    V& operator[](K key);
};

template <typename K, typename V>
TreeMap<K, V>::TreeMap() : tree(){

}

template <typename K, typename V>
void TreeMap<K, V>::clear() {
    tree.clear();
}

template <typename K, typename V>
bool TreeMap<K, V>::containsKey(K key) {
    KeyValuePair kvp(key, V());
    try {
        tree.get(kvp);
        return true;
    }
    catch (std::logic_error&) {
        return false;
    }
}

template <typename K, typename V>
V& TreeMap<K, V>::get(K key) {
    KeyValuePair kvp(key, V());
    return tree.get(kvp).value;
}

template <typename K, typename V>
BinaryTree<K>* TreeMap<K, V>::keySet() {
    auto array = tree.toArray();
    int count = tree.count();
    BinaryTree<K>* keyTree = new BinaryTree<K>();

    for (int i = 0; i < count; i++) {
        keyTree->add(array[i].key);
    }

    delete[] array;
    return keyTree;
}

template <typename K, typename V>
void TreeMap<K, V>::put(K key, V value) {
    KeyValuePair kvp(key, value);

    if (containsKey(key)) {
        get(key) = value;
    }
    else {
        tree.add(kvp);
    }
}

template <typename K, typename V>
int TreeMap<K, V>::size() {
    return tree.count();
}

template <typename K, typename V>
bool TreeMap<K, V>::removeKey(K key) {
    KeyValuePair kvp(key, V());
    return tree.remove(kvp);
}
template <typename K, typename V>
V& TreeMap<K, V>::operator[](K key) {
    if (!containsKey(key)) {
        put(key, V());  
    }
    return get(key);
}
