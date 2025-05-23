#include <map>
#include <vector>

#define SHIT_RETURN -100500
#define SOMETHING 100500


using std::map;
using std::vector;


struct Item{
    int position, priority;

    Item() = default;

    Item(int pos, int prior): position(pos), priority(prior) {}
    Item(size_t pos, int prior): position(pos), priority(prior) {}

};




class min_heap{
private:
    vector<int> heap;
    map<int, Item> items;
    size_t heap_size;

    int get_min_child(int parent){
        int left  = parent*2;
        int right = parent*2 + 1;
        if (right > (int)heap_size)
            return left;
        return (items[heap[left]].priority < items[heap[right]].priority
                ? left : right);
    }

    void swap_nodes(int i, int j) {
        int key_i = heap[i], key_j = heap[j];
        std::swap(heap[i], heap[j]);
        items[key_i].position = j;
        items[key_j].position = i;
    }

    void sift_up(int curr){
        while(curr != 1){
            int parent = curr / 2;

            if (items[heap[parent]].priority > items[heap[curr]].priority){
                swap_nodes(curr, parent);

                curr = parent;
            } else {
                break;
            }
        }
    }

    void sift_down(int curr){


        while(curr*2 <= heap_size){
            int min_child = get_min_child(curr);
            if (items[heap[curr]].priority > items[heap[min_child]].priority ){
                swap_nodes(curr, min_child);
                curr = min_child;
            } else {
                break;
            }
        }
    }


public:
    min_heap(){
        heap_size = 0;
        heap.push_back(SOMETHING);
    }

    min_heap(std::initializer_list<std::pair<int, int>>& il){
        heap.push_back(SOMETHING);
        heap_size = 0;
        for (auto& [key, priority]: il)
            push(key, priority);
    }

    void push(int key, int priority){
        heap.push_back(key);
        heap_size++;
        items[key] = {heap_size, priority};
        sift_up(static_cast<int>(heap_size));
    }

    int get_minimum(){
        if (heap_size){

            int min_key = heap[1];
            swap_nodes(1, heap_size);
            heap.pop_back();
            items.erase(min_key);
            heap_size--;
            sift_down(1);
            return min_key;

        }
        return SHIT_RETURN;
    }

    void update_priority(int key, int new_priority){
        int old_priority = items[key].priority;
        items[key].priority = new_priority;

        if (old_priority < new_priority){
            sift_down(items[key].position);
        } else {
            sift_up(items[key].position);
        }
    }
};
