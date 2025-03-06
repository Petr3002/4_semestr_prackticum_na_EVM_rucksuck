#include <bits/stdc++.h>

using namespace std;

struct item {
    int v;
    int w;
    double cost;
    item(int vv, int ww){
        v = vv;
        w = ww;
        cost = ((double) v) / ((double) w);
    }
};

bool cmp(item a, item b) {
    return a.cost > b.cost;
}

int main() {
    string s;
    cin >> s;
    ifstream in;
    in.open(s);
    int n, vv, ww, W;
    in >> n >> W;
    vector<item> a;
    for (int i = 0; i < n; i++) {
        in >> vv >> ww;
        item q(vv, ww);
        a.push_back(q);
    }
    sort(a.begin(), a.end(), cmp);

    int v = 0, w = 0, v1, w1;
    vector<bool> items;
    for (int i = 0; i < n - 1; i++) {
        v1 = v + a[i].v;
        w1 = w + a[i].w;
        if ((w1 > W) or ((v1 + ((double) (W - w1)) * a[i + 1].cost) < (v + ((double) (W - w)) * a[i + 1].cost))) {
            items.push_back(false);
        } else {
            v = v1;
            w = w1;
            items.push_back(true);
        }
    }
    cout << "Total value: " << v << "\nFor this we need those items: \n";
    int cnt = 1;
    for (int i = 0; i < n; i++) {
        if (items[i]) {
            cout << cnt++ << ") value = " << a[i].v << ", weight = " << a[i].w << endl;
        }
    }
    return 0;
}