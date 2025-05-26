#include <bits/stdc++.h>

using namespace std;

struct item {
    int v;
    int w;
    double cost;
    item(int vv, int ww) {
        v = vv;
        w = ww;
        cost = ((double)v) / ((double)w);
    }
};

bool cmp(item a, item b) {
    return a.cost > b.cost;
}

class thread_pool {
    vector<thread> workers;
    queue<function<void()>> tasks;
    mutex queue_mutex;
    condition_variable condition;
    bool stop;

public:
    explicit thread_pool(size_t numThreads) {
        stop = false;
        for (size_t i = 0; i < numThreads; ++i) {
            workers.emplace_back([this] {
                while (true) {
                    function<void()> task;
                    {
                        unique_lock<mutex> lock(this->queue_mutex);
                        this->condition.wait(lock, [this] { return this->stop or !this->tasks.empty(); });
                        if (this->stop and this->tasks.empty()) return;
                        task = std::move(this->tasks.front());
                        this->tasks.pop();
                    }
                    task();
                }
            });
        }
    }

    void addTask(function<void()> task) {
        {
            unique_lock<mutex> lock(queue_mutex);
            tasks.emplace(std::move(task));
        }
        condition.notify_one();
    }

    ~thread_pool() {
        {
            unique_lock<mutex> lock(queue_mutex);
            stop = true;
        }
        condition.notify_all();
        for (thread &worker : workers) {
            worker.join();
        }
    }
};

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
    vector<bool> items(n, false);
    thread_pool pool(thread::hardware_concurrency());

    for (int i = 0; i < n - 1; i++) {
        pool.addTask([&, i]() {
            v1 = v + a[i].v;
            w1 = w + a[i].w;
            if ((w1 > W) or ((v1 + ((double)(W - w1)) * a[i + 1].cost) < (v + ((double)(W - w)) * a[i + 1].cost))) {
                items[i] = false;
            } else {
                v = v1;
                w = w1;
                items[i] = true;
            }
        });
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
