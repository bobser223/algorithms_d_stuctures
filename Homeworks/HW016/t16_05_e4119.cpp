#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <sstream>

struct Node {
    std::string directory;
    std::map<std::string, Node*> children;

    explicit Node(std::string dir): directory(std::move(dir)){}

    ~Node() {
        for (auto& [name, child] : children) {
            delete child;
        }
    }


    Node* ensureChild(const std::string& name) {
        if (!children.contains(name)) {
            children[name] = new Node{name};
        }
        return children[name];
    }
};

class Tree {
public:
    Node* root;

    Tree()
            : root(new Node{"ROOT"})
    {}

    ~Tree() {
        delete root;
    }


    void add(const std::vector<std::string>& dirs) {
        Node* curr = root;
        for (auto const& dir : dirs) {
            curr = curr->ensureChild(dir);
        }
    }


    void print(Node* n = nullptr, int depth = 0) const {
        if (!n) n = root;
        else{
            std::cout << std::string(depth - 1, ' ') << n->directory << "\n";
        }
        for (auto& [name, child] : n->children) {
            print(child, depth+1);
        }
    }
};

int main() {
    Tree t;
    int n;
    std::cin >> n;
    std::string path;
    while (n--) {
        std::cin >> path;
        std::vector<std::string> dirs;
        std::stringstream ss(path);
        std::string token;

        while (std::getline(ss, token, '\\')) {
            dirs.push_back(token);
        }
        t.add(dirs);
    }


    t.print();
}
