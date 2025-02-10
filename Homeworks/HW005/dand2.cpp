#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>

using namespace std;

typedef long long ll;

struct dand {
    ll all_time = 0;
    ll time_to_grow;
    ll distance;
};


double eaten(double allowed, ll v, ll d, const vector<dand>& dands) {
    double current_time = 0.0;
    double pos = 0.0;
    for (const auto &flower : dands) {

        double travel_time = ((double)flower.distance - pos) / static_cast<double>(v);
        double arrival_time = current_time + travel_time;


        if (arrival_time < (double)flower.time_to_grow) {
            arrival_time = (double)flower.time_to_grow;
        }


        current_time = arrival_time + (double)d;


        pos = (double)flower.distance;
    }


    double return_time = pos / static_cast<double>(v);
    current_time += return_time;

    return current_time;
}


double find_time(ll v, ll d, const vector<dand>& dands) {

    double l = 0;
    double r = 24 * 60;
//    double ans = r;

    double m = l + (r - l) / 2.0;
    while (l < r) {

        if (eaten(m, v, d, dands) <= m) {
//            ans = m;
            r = m - 1;
        } else {
            l = m + 1;
        }
        m = l + (r - l) / 2.0;
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
        cin >> timeStr;
        int hh = stoi(timeStr.substr(0, 2));
        int mm = stoi(timeStr.substr(3, 2));
        dandelions[i].time_to_grow = hh * 60 + mm;
    }

    if (N == 0) {
        cout << "00:00" << "\n";
        return 0;
    }


    double total_time = find_time(v_max, d, dandelions);

    total_time = std::ceil(total_time);


    int total_time2 = (int)total_time;

    int hh = total_time2 / 60;
    int mm = total_time2 % 60;
    printf("%02d:%02d", hh, mm);

    return 0;
}