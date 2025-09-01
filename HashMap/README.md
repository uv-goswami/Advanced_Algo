# HashMap
A hash map (Hash Table) is a data structure that maps unique keys to some values. This allows fast retrieval, insertion, and deletion (in constant time). It links each key with a value. Instead of searching through the whole data, the hash map tells exactly where the value is stored.

## Key Features:
- **Key-value pairs**: Each element in a hash map is a pair of a unique key and its corresponding value.
- **Efficient Lookup**: Using a hash function, finding elements becomes fast as the hash function tells where the element is.
- **No Ordering**: A hash map doesn’t necessarily store the values in a particular order.
- **Uniqueness**: Keys must be unique.

---

## Common Synonyms:
- Hash Tables
- Associative Arrays
- Dictionaries (in Python)

---

## Step-wise Working:
1. **Initialize the Map**: Create an empty structure to hold key-value pairs.
2. **Compute the hash**: For any key `K`, compute its hash using a hash function `h(K)`.
3. **Determine the Index**: Convert the hash code into a valid index of the array.
4. **Insert(K, V)**: Check if any key at the index matches `K`. If yes, update the value to `V`. If no, store the new pair `(K, V)` at that index. Increment the total number of stored pairs.
5. After insertion, compute the load factor:
```

Load factor = total pairs / array size

```
If it exceeds a threshold (e.g., 0.75), trigger resizing.
6. **Resize and Rehash**:
- Create a new internal array with a larger size.
- For each existing `(K, V)` pair: Recompute the hash and insert the pair into the new array.
7. **Lookup Key**: Compute the index using the hash function, search for key `K` at that index.
8. **Delete key**: Compute the index using the hash function, search for key `K` at that index. If found, remove the pair and decrement the total count.
9. **Iterate over All Pairs**: Traverse the internal structure. For each stored `(K, V)` pair, yield it for processing.

---

## Pseudocode:
```

HashMap\_Insert(K,V):
index = Hash(K) mod tableSize
for each (key, value) in Table\[index]:
If key == K:
value = V
Return
Append (K,V) to Table\[index]
Count = Count + 1

````

---

## unordered_map:
In C++ we implement hash maps via the `unordered_map` data structure.

### Key points:
- Provides average O(1) time complexity for search, insertion, and deletion.
- Organizes elements into indices based on their hash values.
- Does not maintain keys in any sorted order—element order is unpredictable.
- Only unique keys are allowed; inserting the same key updates its value.

### Syntax:
```cpp
#include <unordered_map>
std::unordered_map<KeyType, ValueType> myMap;

// Example:
std::unordered_map<string, int> population = {{"Delhi", 10}, {"Jaipur", 9}};
````

---

## Supported Operations and Functions

| Operation  | Description                                 |
| ---------- | ------------------------------------------- |
| `insert()` | Add key-value pairs                         |
| `[]`       | Insert/update/access value by key           |
| `at()`     | Access value (throws if key not present)    |
| `erase()`  | Remove elements (by key or iterator)        |
| `find()`   | Get iterator to key-value pair (or `end()`) |
| `size()`   | Number of elements in the map               |
| `empty()`  | Check if the map is empty                   |
| `clear()`  | Remove all elements                         |
| `count()`  | 1 if key present, 0 otherwise               |

---

## Hash Function:

The hash function converts a key into a numerical value.

---

## Collision Resolution in Hash Tables:

Collisions occur when two different keys hash to the same index. There are two ways to solve this:

### 1. Separate Chaining:

* Each index contains a linked list.
* All key-value pairs that hash to the same index are stored in that list.
* Average-case lookup goes through only one list, which is short if the hash function is good and the load factor is low.

### 2. Open Addressing:

* All the elements are stored in the hash table itself.

  * **Linear Probing**: Try the next empty slot.
  * **Quadratic Probing**: Try slots in a quadratic sequence. Here we calculate the indices from a quadratic hashing function.
  * **Double Hashing**: Use a second hash function to determine the step size.

---

## Time Complexity Analysis

### Hash Map Operations Complexity

| Operation               | Average Case | Worst Case |
| ----------------------- | ------------ | ---------- |
| Search (`find`)         | O(1)         | O(n)       |
| Insert (`[]`, `insert`) | O(1)         | O(n)       |
| Delete (`erase`)        | O(1)         | O(n)       |
| Traverse                | O(n)         | O(n)       |

* **Average O(1)**: If the hash function distributes keys well and the load factor is kept low.
* **Worst-case O(n)**: If all keys hash to the same bucket (pathological collisions), all operations degenerate to scanning a linked list—rare but possible, especially with poor hash functions or malicious input.

---

## Space Complexity:

* **O(n)**, where `n` is the number of key-value pairs used.
* **Extra Overhead**: Hash maps use arrays and may store chains for collision, so they consume more memory than trees.
* **Resizing**: As elements are added, the map resizes, doubling the index count. This can be expensive when the map grows often.

---
<p align="center">
<img src="https://github.com/uv-goswami/Advanced_Algo/blob/2eae3be1981e16f03064e0ac00f1af44c32658cc/HashMap/hash_map.png" alt="Kruskal" height="575px"/>
</p>
---

## Typical Code Examples

### Declaration and Initialization:

```cpp
#include <unordered_map>
using namespace std;

unordered_map<string, int> population = {{"Delhi", 10}, {"Jaipur", 9}};
```

### Insertion/Update:

```cpp
population["Delhi"] = 11; // Update
population.insert({{"Chandigarh", 3}, {"Noida", 6}});
```

### Access:

```cpp
cout << "Delhi Population: " << population["Delhi"];
```

### Check Existence:

```cpp
if (population.find("Shimla") == population.end()) {
  return false;
}

if (population.count("Delhi")) {
  return true;
}
```

### Deletion:

```cpp
population.erase("Noida");
population.clear();    // Remove all elements
```

### Traversal:

```cpp
for (const auto& [name, count] : population) {
  cout << name << ": " << count << endl;
}
```

---

## Advantages of Hash Map

| Advantage                   | Explanation                                                                                 |
| --------------------------- | ------------------------------------------------------------------------------------------- |
| Fast access (O(1) average)  | Most lookups, inserts, and deletes are done in constant time, allowing speedy operations.   |
| Efficiency for big data     | Scales well for large data sets where other structures (like trees or lists) would be slow. |
| Flexible key types          | Supports any data type as key if hash and equality are well-defined.                        |
| Ease of use (STL)           | Simple API for insertion, lookup, deletion, etc.; keys can be strings, numbers, or objects. |
| Adaptable memory allocation | Grows/shrinks dynamically as needed, with allocator support.                                |
| No need for pre-sorting     | Unlike ordered containers, no sort order is required, handy for purely key-based data use.  |
| Dynamic resizing            | Automatically manages storage and buckets.                                                  |

---

## Disadvantages of Hash Map

| Limitation                       | Explanation                                                                                     |
| -------------------------------- | ----------------------------------------------------------------------------------------------- |
| No ordering                      | Elements are not sorted by keys or insertion—making sorted iteration or range queries difficult |
| Can degrade to O(n)              | Worst-case time complexity degrades to O(N) if there are many collisions                        |
| More memory use                  | Uses more memory than trees or arrays, due to bucket overhead and separate storage              |
| Requires good hash function      | Poor hash functions or poorly chosen keys undermine performance and cause clustering            |
| Iterator invalidation            | Inserting or rehashing invalidates iterators, making certain patterns unsafe                    |
| Not thread-safe                  | Like all standard STL containers, not inherently safe for concurrent access                     |
| No duplicate keys                | Only one value per key; for multiple values, see `unordered_multimap`                           |
| Potential for hard-to-debug bugs | Custom keys require careful `operator==` and hash function definitions                          |

---

## When to Use Hash Maps vs. Other STL Containers

| Scenario                               | Use Hash Map?            | Consider Instead           |
| -------------------------------------- | ------------------------ | -------------------------- |
| Need fast lookup by key                | Yes (`unordered_map`)    |                            |
| Need sorted data (e.g., for iteration) | No                       | Use `map` (Red-Black Tree) |
| Need duplicate keys                    | No                       | Use `unordered_multimap`   |
| Concerns about worst-case time         | Caution                  | Use `map`                  |
| Memory overhead is critical            | Maybe not                | `map` may use less memory  |
| Iteration order matters                | No                       | Use `map` / `vector`       |
| Keys are complex types                 | If hash/equality defined |                            |

---

## Comparison Table

| Container       | Ordering | Search Time       | Memory Use | Underlying Structure |
| --------------- | -------- | ----------------- | ---------- | -------------------- |
| `unordered_map` | None     | Avg O(1), WC O(N) | High       | Hash Table           |
| `map`           | Sorted   | O(log n)          | Medium     | Red-Black Tree       |
| `vector`        | None     | O(n)              | Low        | Dynamic Array        |
| `set`           | Sorted   | O(log n)          | Medium     | Balanced Tree (BST)  |

* **For fast, unordered key access**: `unordered_map`
* **For sorted key access and range queries**: `map`
* **For multi-value keys**: `unordered_multimap` or `multimap`
* **For simple lists**: `vector` or `list`

---

## Real-World Application and Use Cases

1. **Compilers**: As symbol tables mapping variable names to their properties.
2. **Database systems**: As indexes to quickly find records by key.
3. **Web servers**: Mapping URLs.
4. **Routing tables**: Mapping network addresses to specific connections.
5. **Game development**: Tracking entities keyed by IDs.
6. **Blockchain and cryptography**: Quick lookup for block or signature verification.
7. **Spam filtering**: Hash-based data summaries.

