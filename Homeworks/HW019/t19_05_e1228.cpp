#include <iostream>
#include <vector>
#include <string>

struct bucket {
    std::string value;
    int priority;
    bucket(std::string s, int p): value(std::move(s)), priority(p) {}
};

class min_heap {
private:
    std::vector<bucket> HEAP;
    int SIZE;

    void sift_up(int idx) {
        while (idx > 1) {
            int parent = idx / 2;
            if (HEAP[idx].priority < HEAP[parent].priority) {
                std::swap(HEAP[idx], HEAP[parent]);
                idx = parent;
            } else break;
        }
    }

    void sift_down(int idx = 1) {
        while (2*idx <= SIZE) {
            int left  = 2*idx;
            int right = left + 1;
            int min_kid = left;
            if (right <= SIZE && HEAP[right].priority < HEAP[left].priority) {
                min_kid = right;
            }
            if (HEAP[min_kid].priority < HEAP[idx].priority) {
                std::swap(HEAP[min_kid], HEAP[idx]);
                idx = min_kid;
            } else {
                break;
            }
        }
    }

public:
    min_heap(): SIZE(0) {
        HEAP.emplace_back("DUMMY", -1);
    }

    void insert(const std::string& s, int pr) {
        HEAP.emplace_back(s, pr);
        ++SIZE;
        sift_up(SIZE);
    }

    int pop() {
        int res = HEAP[1].priority;
        HEAP[1] = HEAP.back();
        HEAP.pop_back();
        --SIZE;
        if (SIZE >= 1) sift_down();
        return res;
    }

    int size() const { return SIZE; }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;
    min_heap hp;

    for (int i = 0; i < n; i++) {
        int x;
        std::cin >> x;
        hp.insert("x", x);
    }

    long long result = 0;
    while (hp.size() > 1) {
        int a = hp.pop();
        int b = hp.pop();
        result += (long long)a + b;
        hp.insert("x", a + b);
    }

    std::cout << result << "\n";
    return 0;
}
