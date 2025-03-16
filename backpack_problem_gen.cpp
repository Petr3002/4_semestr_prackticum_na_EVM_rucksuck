#include <bits/stdc++.h>

using namespace std;

struct item {
    int v;
    int w;
    item(int vv, int ww){
        v = vv;
        w = ww;
    }
};

int fv(vector<bool>& a1, vector<item>& a, int n) {
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        if (a1[i]) {
            cnt += a[i].v;
        }
    }
    return cnt;
}

int fw(vector<bool>& a1, vector<item>& a, int n) {
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        if (a1[i]) {
            cnt += a[i].w;
        }
    }
    return cnt;
}

bool cmp2(const pair<vector<bool>*, int>& a1, const pair<vector<bool>*, int>& a2) {
    return a1.second > a2.second;
}

bool cmp1(item a, item b) {
    return a.v > b.v;
}

int ham(vector<bool>* a, vector<bool>* b, int n) {
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        cnt += ((*a)[i] != (*b)[i]);
    }
    return cnt;
}

int daddy(vector<pair<vector<bool>*, int>>& b, pair<vector<bool>*, int>& mommy, int n) {
    int ind = 0, max = 0, q;
    for (int i = 0; i < n; i++) {
        q = ham(b[i].first, mommy.first, n);
        if (q > max) {
            max = q;
            ind = i;
        }
    }
    return ind;
}

void g(vector<pair<vector<bool>*, int>>& c, pair<vector<bool>*, int> m, pair<vector<bool>*, int> d, int ind, int n, vector<item>& a) {
    for (int i = 0; i < n; i++) {
        if (i % 2 == 0) {
            (*(c[ind].first))[i] = (*(m.first))[i];
            (*(c[ind + 1].first))[i] = (*(d.first))[i];
        }
        else {
            (*(c[ind].first))[i] = (*(d.first))[i];
            (*(c[ind + 1].first))[i] = (*(m.first))[i];
        }
    }
    c[ind].second = fv(*(c[ind].first), a, n);
    c[ind + 1].second = fv(*(c[ind + 1].first), a, n);
}

int main() {
    string s;
    cout << "Enter file's name: ";
    cin >> s;
    ifstream in;
    in.open(s);
    int nn, n = 0, vv, ww, W;
    in >> nn >> W;
    vector<item> a;
    for (int i = 0; i < nn; i++) {
        in >> vv >> ww;
        if (ww <= W) {
            item q(vv, ww);
            a.emplace_back(q);
            n++;
        }
    }
    int k = (n >= 10 ? 10 : n / 2);

    sort(a.begin(), a.end(), cmp1);

    vector<pair<vector<bool>*, int>> b(k), c(3 * k);
    for (int i = 0; i < k; i++) {
        b[i].first = new vector<bool>(n, false);
        (*(b[i].first))[i] = true;
    }

    for (int i = 0; i < 3 * k; i++) {
        c[i].first = new vector<bool>(n, false);
    }

    int ind, index;
    pair<vector<bool>*, int> mother;
    for (int _ = 0; _ < 100 * n; _++) {
        for (int i = 0; i < k; i++) {
            c[i].first = b[i].first;
            c[i].second = b[i].second;
        }
        ind = k;
        for (int i = 0; i < k; i++) {
            mother.first = b[i].first;
            mother.second = b[i].second;
            index = daddy(b, mother, k);
            g(c, mother, b[index], ind, n, a);
            ind += 2;
        }
        sort(c.begin(), c.end(), cmp2);
        ind = 0;
        index = 0;
        while (ind < k && index < c.size()) {
            if (fw(*(c[index].first), a, n) <= W) {
                b[ind] = c[index];
                ind++;
            }
            index++;
        }
    }

    cout << "Max value is " << b[0].second;
    cout << ", with these items:\n";
    for (int i = 0; i < n; i++) {
        if ((*(b[0].first))[i]) {
            cout << "value: " << a[i].v << ", weight: " << a[i].w << endl;
        }
    }

    for (int i = 0; i < k; i++) {
        delete b[i].first;
    }
    for (int i = 0; i < 3 * k; i++) {
        delete c[i].first;
    }

    return 0;
}