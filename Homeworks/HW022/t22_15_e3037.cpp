#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <stack>

using namespace std;




class Graph{
private:
    int size;
    std::vector<std::vector<int>> children;
    std::vector<bool> sharing_roots;
    std::vector<bool> admin_agree;
public:
    explicit Graph(int n)
    {
        children.resize(n+1);
        sharing_roots.resize(n+1, false);
        admin_agree.resize(n+1, false);
        size = n;

    }

    ~Graph() = default;


    void add(int v, int e)
    {
        children[v].push_back(e);
    }

    void f_1(int id) // admin gives rights
    {
        admin_agree[id] = true;

    }

    void f_2(int id) //admin takes away rights
    {
        admin_agree[id] = false;
    }

    void f_3(int id) // id shares his rights ONLY with his children
    {
        sharing_roots[id] = true;
    }

    void f_4(int id) // f_3 than f_3 for each child and so on so force
     {

            vector<bool> visited(size+1, false);
            stack<int> st;
            st.push(id);
            visited[id] = true;
            sharing_roots[id] = true;

            while (!st.empty()) {
                int u = st.top(); st.pop();
                for (int v : children[u]) {
                    if (!visited[v]) {
                        visited[v] = true;
                        sharing_roots[v] = true;
                        st.push(v);
                    }
                }
            }
        }

    void f_5(int id) //
    {
        sharing_roots[id] = false;
    }

    void final()
    {
        std::vector<bool> has_roots(this->size + 1, false);

        std::queue<int> q;

        for (int i = 1; i < size+1; i++)
        {
            if(admin_agree[i])
            {
                has_roots[i] = true;
                q.push(i);
            }
        }

        while(!q.empty())
        {
            int curr = q.front(); q.pop();

            if (!sharing_roots[curr])
                continue;

            for(int child: children[curr])
            {
                if (!has_roots[child]) // !visited
                {
                    has_roots[child] = true;
                    q.push(child);
                }

            }
        }

        for (int i = 1; i < size + 1; i++)
        {
            cout << has_roots[i] << " ";
        }

    }



};


int main(){
    int n, m;
    cin >> n >> m;

    Graph g(n);


    int b1, b2;

    for(int i = 0; i < m; i++)
    {
        cin >> b1 >> b2;
        g.add(b1, b2);

    }

    cin >> m;

    for (int i = 0; i < m; i++)
    {
        cin >> b1 >> b2;

        switch (b1)
        {
            case(1):
                g.f_1(b2);
                break;

            case(2):
                g.f_2(b2);
                break;

            case(3):
                g.f_3(b2);
                break;

            case(4):
                g.f_4(b2);
                break;

            case(5):
                g.f_5(b2);
                break;

        }


    }

    g.final();


}