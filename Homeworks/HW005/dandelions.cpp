#include <iostream>
#include <vector>
#include <queue>

using namespace std;

typedef long long ll;


struct dand{
    ll all_time = 0;
    ll time_to_grow;

    ll distance;

    bool operator>(const dand& other) const {
        return all_time > other.all_time;
    }
};


//int eaten(ll v, ll d, vector<dand>& dands, int time);

int eaten(int time);


ll find_time(ll v, ll d, vector<dand>& dands){
    int needed; // all dandelions;
    int l = 0;
    int r = 24*60;
    while (r - l < 0.0000006){
        int m = l + (r-l) / 2;
        if (eaten(m) < needed){
            l = m + 1;
        } else {
            r = m ;
        }
    }
    return l;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int v_max, d;
    cin >> v_max >> d;

    int N;
    cin >> N;
    vector<dand> dandelions(N);

    for (int i = 0; i < N; i++) {
        cin >> dandelions[i].distance;
        string timeStr;
        cin >> timeStr; // формат "hh:mm"
        int hh = stoi(timeStr.substr(0, 2));
        int mm = stoi(timeStr.substr(3, 2));
        dandelions[i].time_to_grow = hh * 60 + mm;
    }



    return 0;
}