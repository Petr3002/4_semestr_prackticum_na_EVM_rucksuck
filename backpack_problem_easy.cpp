#include <bits/stdc++.h>
#include <vector>

using namespace std;

struct item{
    int w;
    int v;
    item(int value, int weight){
        v = value;
        w = weight;
    }
};

bool cmp(const item a, const item b) {
    return a.v / a.w > b.v / b.w;
}

int main() {
    string s;
    cin >> s;
    ifstream in;
    in.open(s);
    int n, W;
    in >> n >> W;
    vector<item> items;
    int v, w;
    for(int i = 0; i < n; i++){
        in >> v >> w;
        items.emplace_back(v, w);
    }
    sort(items.begin(), items.end(), cmp);
    vector<item> taken_items;
    int total_weight = 0;
    int total_value = 0;
    for(int i = 0; i < n; i++){
        if(total_weight + items[i].w <= W){
            taken_items.emplace_back(items[i].v, items[i].w);
            total_weight += items[i].w;
            total_value += items[i].v;
        }
    }
    cout << "We can reach total value of " << total_value << " with total weight of " << total_weight << endl << "For this we need followed items:" << endl;
    for(item it: taken_items){
        cout << "Value: " << it.v << ", weight: " << it.w << endl;
    }
    cout << "Answer: " << total_value;
    return 0;
};
