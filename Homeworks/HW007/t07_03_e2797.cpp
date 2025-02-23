
//
// Created by Volodymyr Avvakumov on 26.10.2024.
//

#include <stdexcept>
#include <iostream>
#include <type_traits>
#include <cmath>

#ifndef LEARNING_LINKEDLIST_H
#define LEARNING_LINKEDLIST_H


/**
 * @brief A templated structure representing a node in the linked list.
 *
 * @tparam var_type The type of the value stored in the node.
 */
template<typename var_type>
struct ListEl{
    bool is_empty;                     /**< Flag indicating if the node is empty (actually useless). */
    var_type var;                      /**< The value stored in the node. */
    ListEl<var_type>* next_pointer;    /**< Pointer to the next node in the list. */
};

/**
 * @brief A templated singly linked list class.
 *
 * Provides functionality to add, check, and remove elements. Supports iteration
 * through the list using a const iterator.
 *
 * @tparam var_type The type of elements stored in the linked list.
 */

template<typename var_type>
class LinkedList {

private:
    int size;                       /**< The number of elements in the list. */
    ListEl<var_type>* first_el;     /**< Pointer to the first element in the list. */


public:

    /**
     * @brief Default constructor.
     *
     * Initializes an empty linked list.
     */
    LinkedList() : first_el(nullptr), size(0) {}

    /**
     * @brief Destructor.
     *
     * Cleans up all nodes in the linked list.
     */
    ~LinkedList();

    /**
     * @brief Adds an element to the linked list.
     *
     * Adds a new element to the end of the list if it doesn't already exist.
     *
     * @param var The element to add.
     */
    int add(var_type var);

    /**
     * @brief Checks if an element exists in the linked list.
     *
     * @param var The element to check for.
     * @return true If the element is present.
     * @return false Otherwise.
     */
    bool is_in(var_type var);

    /**
     * @brief Removes an element from the linked list.
     *
     * Deletes the node containing the specified element.
     *
     * @param var The element to remove.
     * @throws std::logic_error If the element is not found.
     */
    void pop(var_type var);

    /**
     * @brief Overloads the equality operator.
     *
     * Compares the first element of the list with a given value.
     *
     * @tparam name The type of the value to compare.
     * @param var The value to compare with the first element.
     * @return true If the first element is equal to the value.
     * @return false Otherwise.
     */
    template<class name>
    bool operator==(name var){
        return first_el == var;
    }

    /**
     * @brief Overloads the inequality operator.
     *
     * Compares the first element of the list with a given value.
     *
     * @tparam name The type of the value to compare.
     * @param var The value to compare with the first element.
     * @return true If the first element is not equal to the value.
     * @return false Otherwise.
     */
    template<class name>
    bool operator!=(name var){
        return first_el != var;
    }


    /**
     * @brief Prints the contents of the linked list.
     *
     * Iterates through all nodes and prints their values.
     *
     * @param out The output stream to print to. Defaults to std::cout.
     */
    void print(std::ostream& out = std::cout) const;



    /**
     * @brief A constant iterator for the LinkedList.
     *
     * Allows iteration over the linked list without modifying its elements.
     */
    class ConstIterator {
    private:
        const ListEl<var_type>* current; /**< Pointer to the current node in the iteration. */

    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = const var_type;
        using difference_type = std::ptrdiff_t;
        using pointer = const var_type*;
        using reference = const var_type&;

        /**
         * @brief Constructs a ConstIterator.
         *
         * @param ptr Pointer to the starting node.
         */
        ConstIterator(const ListEl<var_type>* ptr) : current(ptr) {}

        /**
         * @brief Checks if two iterators are not equal.
         *
         * @param other The other iterator to compare with.
         * @return true If the iterators point to different nodes.
         * @return false Otherwise.
         */
        bool operator!=(const ConstIterator& other) const {
            return current != other.current;
        }

        /**
         * @brief Dereferences the iterator to access the current element.
         *
         * @return const var_type& Reference to the current element.
         */
        const var_type& operator*() const {
            return current->var;
        }

        /**
         * @brief Advances the iterator to the next element.
         *
         * @return ConstIterator& Reference to the updated iterator.
         */
        ConstIterator& operator++() {
            if(current != nullptr){
                current = current->next_pointer;
            }
            return *this;
        }
    };

    /**
     * @brief Returns an iterator to the beginning of the list.
     *
     * @return ConstIterator An iterator pointing to the first element.
     */
    ConstIterator begin() const {
        return ConstIterator(first_el);
    }

    /**
     * @brief Returns an iterator to the end of the list.
     *
     * @return ConstIterator An iterator pointing past the last element.
     */

    ConstIterator end() const {
        return ConstIterator(nullptr);
    }


protected:
    /**
     * @brief Finds the element with the given value and its preceding element.
     *
     * Searches the list for the specified value and sets pointers to the previous
     * and target elements.
     *
     * @param var The value to search for.
     * @param previous_element Reference to a pointer that will point to the preceding element.
     * @param element_to_delete Reference to a pointer that will point to the target element.
     * @throws std::logic_error If the element is not found.
     */
    void find_element_with_var(var_type var, ListEl<var_type>*& previous_element, ListEl<var_type>*& element_to_delete) const;

    /**
     * @brief Overloads the insertion operator to print the LinkedList.
     *
     * @param out The output stream.
     * @param lst The LinkedList to print.
     * @return std::ostream& The output stream.
     */
    friend std::ostream& operator <<(std::ostream& out,const LinkedList& lst){
        lst.print(out);
        return out;
    }


    template <typename T>
    friend class HashSet;
}; // End of the class

// methods implementation
template<typename var_type>
LinkedList<var_type>::~LinkedList(){
    ListEl<var_type>* curr_el = first_el;
    while (curr_el != nullptr){
        ListEl<var_type>* temp = curr_el;
        curr_el = curr_el->next_pointer;
        delete temp;
    }
}


template<typename var_type>
int LinkedList<var_type>::add(var_type var){
    if(is_in(var))  return 0;
    ListEl<var_type>* new_el = new ListEl<var_type>;
    new_el -> var = var;
    new_el -> next_pointer = nullptr;
    new_el ->is_empty = false;
    if (size == 0){
        first_el = new_el;
    } else {
        ListEl<var_type>* curr_el = first_el;
        while (curr_el -> next_pointer != nullptr){
            curr_el = curr_el -> next_pointer;
        }
        curr_el -> next_pointer = new_el;
    }

    size ++;
    return 1;

}

template<typename var_type>
bool LinkedList<var_type>::is_in(var_type var){
    if (size == 0){
        return false;
    } else {

        ListEl<var_type>* curr_el = first_el;
        // while current element exists
        while (curr_el != nullptr){
            if (curr_el->var == var && !curr_el->is_empty) return true;
            curr_el = curr_el->next_pointer;
        }
        return false;



    }
}


template<typename var_type>
void LinkedList<var_type>::pop(var_type var){
    if (!is_in(var)){
        throw std::logic_error("this variable isn't here!!!");
    }

    if (size == 1){
        delete first_el;
        first_el = nullptr;
    } else if (first_el->var == var){
        ListEl<var_type>* temp = first_el;
        first_el = first_el->next_pointer;
        delete temp;
    } else {
        ListEl<var_type>* previous_element = nullptr;
        ListEl<var_type>* element_to_delete = nullptr;
        find_element_with_var(var, previous_element, element_to_delete);

        if (element_to_delete != nullptr && previous_element != nullptr){
            previous_element->next_pointer = element_to_delete->next_pointer;
            delete element_to_delete;
        }
    }

    size--;
}

template<typename var_type>
void LinkedList<var_type>::print(std::ostream& out) const{
    ListEl<var_type>* curr_el = first_el;
    while (curr_el != nullptr){
        out << curr_el -> var << ' ';
        curr_el = curr_el ->next_pointer;
    }
}

//protected:
template<typename var_type>
void LinkedList<var_type>::find_element_with_var(var_type var, ListEl<var_type>*& previous_element, ListEl<var_type>*& element_to_delete) const {
    if (size == 0){
        throw std::logic_error("no elements here!!!");
    }

    previous_element = nullptr;
    element_to_delete = nullptr;
    ListEl<var_type>* curr_el = first_el;

    while (curr_el != nullptr){
        if (curr_el->var == var && !curr_el->is_empty){
            element_to_delete = curr_el;
            break;
        }
        previous_element = curr_el;
        curr_el = curr_el->next_pointer;
    }

    if (element_to_delete == nullptr){
        throw std::logic_error("Element not found!");
    }
}

#endif //LEARNING_LINKEDLIST_H




#ifndef LEARNING_HASHSET_H
#define LEARNING_HASHSET_H


/**
 * @brief A templated HashSet class implementing a hash set using separate chaining.
 *
 * This class provides functionality to add, check and remove elements from the set.
 * It automatically resizes when the occupancy exceeds 75% to maintain efficiency.
 *
 * @tparam var_type The type of elements stored in the HashSet.
 */
template<typename var_type>
class HashSet {
protected:
    int real_size;                 /**< The current size of the hash table. */
    int element_count;             /**< The number of elements currently in the hash set. */
    int curr_pow_for_primes;       /**< The current power used to determine the next prime size. */

    LinkedList<var_type>* element_arr; /**< Array of linked lists for separate chaining. */

public:

    /**
     * @brief Default constructor.
     *
     * Initializes the hash set with a default size and sets up the linked lists.
     */
    HashSet();

    /**
     * @brief Destructor.
     *
     * Cleans up the allocated memory for the hash table.
     */
    ~HashSet(){
        delete[] element_arr;
    }


    /**
     * @brief Adds an element to the HashSet.
     *
     * If the occupancy exceeds 75%, the hash table is resized to maintain performance.
     *
     * @param var The element to be added.
     */
    void add(var_type var);

    /**
     * @brief Checks if an element exists in the HashSet.
     *
     * @param var The element to check for.
     * @return true If the element is present.
     * @return false Otherwise.
     */
    bool is_in(var_type var);

    /**
     * @brief Removes an element from the HashSet.
     *
     * Deletes the element by finding its hash and removing it from the corresponding linked list.
     *
     * @param var The element to be removed.
     * @throws std::logic_error If the element is not found.
     */
    void pop(var_type var);

    /**
     * @brief Retrieves the number of elements in the HashSet.
     *
     * @return int The count of elements.
     */
    int getSize(){
        return element_count;
    }

    /**
     * @brief Prints the contents of the HashSet.
     *
     * Iterates through all linked lists and prints their elements.
     *
     * @param out The output stream to print to. Defaults to std::cout.
     */
    void print(std::ostream& out = std::cout) const;


protected:

    /**
     * @brief Computes the hash for integral types.
     *
     * Uses bitwise operations to generate a hash value for integers.
     *
     * @tparam T Integral type.
     * @param value The value to hash.
     * @return long long int The computed hash.
     */
    template <typename T>
    typename std::enable_if<std::is_integral<T>::value, long long int>::type
    getHash(T value);

    /**
     * @brief Computes the hash for floating-point types.
     *
     * Processes the binary representation of floating-point numbers to generate a hash.
     *
     * @tparam T Floating-point type.
     * @param value The value to hash.
     * @return long long int The computed hash.
     */
    template <typename T>
    typename std::enable_if<std::is_floating_point<T>::value, long long int>::type
    getHash(T value);


    /**
     * @brief Computes the hash for pointer types.
     *
     * Hashes the memory address of the pointer.
     *
     * @tparam T Pointer type.
     * @param value The pointer to hash.
     * @return long long int The computed hash.
     */
    template <typename T>
    typename std::enable_if<std::is_pointer<T>::value, long long int>::type
    getHash(T value);

    /**
     * @brief Computes the hash for std::string.
     *
     * Processes each character in the string to generate a hash.
     *
     * @param value The string to hash.
     * @return long long int The computed hash.
     */
    long long int getHash(const std::string& value) const;

    /**
     * @brief Calculates the current occupancy of the hash table.
     *
     * Determines the percentage of filled elements relative to the total size.
     *
     * @return float The occupancy percentage.
     */
    float get_occupancy(){
        if (HashSet<var_type>::real_size == 0) return 0;
        return ((float)HashSet<var_type>::element_count / HashSet<var_type>::real_size) * 100;
    }

    /**
     * @brief Resizes the hash table by creating a new array with a larger prime size.
     *
     * Allocates a new array, rehashes existing elements and replaces the old array.
     */
    void create_new_elements_arr();

    /**
     * @brief Copies all elements from the old hash table to the new one.
     *
     * Rehashes each element and inserts it into the appropriate linked list in the new array.
     *
     * @param new_lst Pointer to the new array of linked lists.
     * @param new_size The size of the new array.
     */
    void copy_list(LinkedList<var_type>* new_lst, int new_size);


    /**
     * @brief Finds the next prime number for resizing the hash table.
     *
     * Searches for prime numbers within the range [2^k, 2^(k+1)-1]. If no prime is found,
     * it increments k and searches the next range.
     *
     * @return long long The next prime number to be used as the new size.
     */
    long long next_prime();

    /**
     * @brief Checks if a number is prime.
     *
     * Uses trial division to determine if a number is prime.
     *
     * @param num The number to check.
     * @return true If the number is prime.
     * @return false Otherwise.
     */
    static bool is_prime(long long num);

    /**
     * @brief Overloads the insertion operator to print the HashSet.
     *
     * @param out The output stream.
     * @param set The HashSet to print.
     * @return std::ostream& The output stream.
     */
    friend std::ostream& operator <<(std::ostream& out,const HashSet& set){
        set.print(out);
        return out;
    }
}; // End of the class

// methods implementation

template<typename var_type>
HashSet<var_type>::HashSet() {
    real_size = 5;
    element_count = 0;
    curr_pow_for_primes = 3;
    element_arr = new LinkedList<var_type>[real_size];
    for (int i = 0; i < 5; i++) element_arr[i].first_el = nullptr;
}


template<typename var_type>
void HashSet<var_type>::add(var_type var){

    if (get_occupancy() > 75)
        create_new_elements_arr();

//    std::cout << var << " hash started" << std::endl;
    long long int  hash = HashSet<var_type>::getHash(var);

    if (hash < 0) hash = -hash;

    int position = hash % real_size;

    element_count += element_arr[position].add(var);
}

template<typename var_type>
bool HashSet<var_type>::is_in(var_type var){
    long long hash = getHash(var);

    if(hash < 0)
        hash = -hash;

    long long position = hash % real_size;

    return element_arr[position].is_in(var);
}

template<typename var_type>
void HashSet<var_type>::pop(var_type var){

    int hash = HashSet<var_type>::getHash(var);
    int position = hash % HashSet<var_type>::real_size;
    // if element_arr[i] is not empty, overloaded operator, look to LinkedList.h
    if (HashSet<var_type>::element_arr[position] != nullptr){
        element_arr[position].pop(var);
        element_count --;
    } else{
        throw std::logic_error("no elements here!!!");
    }
}

template<typename var_type>
void HashSet<var_type>::print(std::ostream& out) const {
    for (int i = 0; i < real_size; i++) {
        if (element_arr[i] == nullptr) continue;
        out << element_arr[i] << " ";
    }
}


//protected

//hash functions

template<typename var_type>
template <typename T>
typename std::enable_if<std::is_integral<T>::value, long long int>::type
HashSet<var_type>::getHash(T value) {
    // hash function works only for positive nums
    if (value < 0) {
        value = -value;
    }
    long long int result = 0;
    while (value) {
        result = (result << 5) | (result >> (sizeof(long long int) * 8 - 5));
        result ^= (value & 0xFF);
        value >>= 8;
    }


    return result;
}


template<typename var_type>
template <typename T>
typename std::enable_if<std::is_floating_point<T>::value, long long int>::type
HashSet<var_type>::getHash(T value) {
    long long int result = 0;
    unsigned char* bytePtr = reinterpret_cast<unsigned char*>(&value);
    for (size_t i = 0; i < sizeof(T); ++i) {
        result = (result << 5) | (result >> (sizeof(long long int) * 8 - 5));
        result ^= bytePtr[i];
    }


    return result;
}

template<typename var_type>
template <typename T>
typename std::enable_if<std::is_pointer<T>::value, long long int>::type
HashSet<var_type>::getHash(T value) {
    long long int result = 0;
    uintptr_t ptr = reinterpret_cast<uintptr_t>(value);
    unsigned char* bytePtr = reinterpret_cast<unsigned char*>(&ptr);
    for (size_t i = 0; i < sizeof(ptr); ++i) {
        result = (result << 5) | (result >> (sizeof(long long int) * 8 - 5));
        result ^= bytePtr[i];
    }


    return result;
}

template<typename var_type>
long long int HashSet<var_type>::getHash(const std::string& value) const {
    long long int result = 0;
    for (char c : value) {

        result = (result << 5) | (result >> (sizeof(long long int) * 8 - 5));
        result ^= static_cast<unsigned char>(c);
    }


    return result;
}

// puffer scaling functions
template<typename var_type>
void HashSet<var_type>::create_new_elements_arr() {
    long long new_size = HashSet<var_type>::next_prime();

    LinkedList<var_type>* new_element_arr = new LinkedList<var_type>[new_size];
    HashSet<var_type>::copy_list(new_element_arr, new_size);

    delete[] HashSet<var_type>::element_arr;

    element_arr = new_element_arr;
    HashSet<var_type>::real_size = new_size;
}

template<typename var_type>
void HashSet<var_type>::copy_list(LinkedList<var_type>* new_lst, int new_size){
    // running through all buckets
    for (int i = 0; i < real_size; i ++){
        // if there is at least one element |look at the LinkedList|
        if (HashSet<var_type>::element_arr[i] != nullptr){
            // for all element in linked list
            for (auto element: element_arr[i]){

                long long int  hash = HashSet<var_type>::getHash(element);

                if (hash < 0) hash = -hash;

                int position = hash % new_size;

                new_lst[position].add(element);

            }
        }
    }
}

template<typename var_type>
long long HashSet<var_type>::next_prime(){
    long long min_lim = pow(2, curr_pow_for_primes);
    long long max_lim = pow(2, curr_pow_for_primes+1);

    long long middle = (min_lim + max_lim) / 2;

    for (long long i = middle; i < max_lim - 1; i++){
        if (HashSet<var_type>::is_prime(middle - i)){
            curr_pow_for_primes ++;
            return middle - i;
        }
        if (HashSet<var_type>::is_prime(middle + i)){
            curr_pow_for_primes ++;
            return middle + i;
        }
    }
    // if no primes from 2^k-1 to 2^k;
    curr_pow_for_primes ++;
    return HashSet<var_type>::next_prime();
}

template<typename var_type>
bool HashSet<var_type>::is_prime(long long num) {
    if (num < 2) return false;
    if (num == 2 || num == 3) return true;
    if (num % 2 == 0 || num % 3 == 0) return false;

    int sqrt_num = static_cast<long long>(std::sqrt(num));
    for (long long i = 5; i <= sqrt_num; i += 6) {
        if (num % i == 0 || num % (i + 2) == 0)
            return false;
    }
    return true;
}
#endif //LEARNING_HASHSET_H



int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);

    HashSet<int> set;
    int n;
    std::cin >> n;
    int buffer;
    for (int i = 0; i < n; i++){
        std::cin >> buffer;
        set.add(buffer);
    }
//    std::cout << set << std::endl;
    std::cout << set.getSize() << std::endl;




}