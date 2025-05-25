#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>
#include <set>
#include <queue>
#include "pattern.cpp"

using namespace std;

void bfs(int N) {
    pattern P;
    P.push_back({0, 0});
    vector<pattern> vec;
    vec.push_back(P);
    for (int i = 1; i <= N - 1; ++i) {
        vector<pattern> new_vec;
        for (auto P: vec) {
            vector<pattern> vec2 = P.extend();
            for (auto Q: vec2) new_vec.push_back(Q);
        }
        sort(new_vec.begin(), new_vec.end());
        new_vec.resize(unique(new_vec.begin(), new_vec.end()) - new_vec.begin());
        // cout << i + 1 << ' ' << new_vec.size() << endl;
        vec = new_vec;
    }
    cout << vec.size() << "\n";
    for (int i = 0; i < vec.size(); ++i) {
        cout << i << '\n';
        vec[i].print();
        cout << '\n';
    }
}

void bfs_acyclic(int N) {
    pattern P;
    P.push_back({0, 0});
    vector<pattern> vec;
    vec.push_back(P);
    for (int i = 1; i <= N - 1; ++i) {
        vector<pattern> new_vec;
        for (auto P: vec) {
            vector<pattern> vec2 = P.extend_acyclic();
            for (auto Q: vec2) new_vec.push_back(Q);
        }
        sort(new_vec.begin(), new_vec.end());
        new_vec.resize(unique(new_vec.begin(), new_vec.end()) - new_vec.begin());
        // cout << i + 1 << ' ' << new_vec.size() << endl;
        vec = new_vec;
    }
    cout << vec.size() << "\n";
    for (int i = 0; i < vec.size(); ++i) {
        cout << i << '\n';
        vec[i].print();
        cout << '\n';
    }
}

void search_Pach_Tardos(int N) {
    pattern P;
    P.push_back({0, 0});
    queue<pattern> q;
    set<pattern> st;
    q.push(P);
    st.insert(P);
    int cnt[N + 1]{};
    vector<pattern> res[N + 1];
    while (!q.empty()) {
        P = q.front(); q.pop();
        if (P.size() > N) continue;
        cnt[P.size()]++;
        res[P.size()].push_back(P);
        vector<pattern> vec = P.extend_const();
        for (pattern Q: vec) {
            if (Q.size() <= N && !st.count(Q)) {
                q.push(Q);
                st.insert(Q);
            }
        }
        vector<pattern> vec2 = P.extend_log();
        for (pattern Q: vec2) {
            if (Q.size() <= N && !st.count(Q)) {
                q.push(Q);
                st.insert(Q);
            }
        }
    }
    for (int i = 1; i <= N; ++i) {
        sort(res[i].begin(), res[i].end());
        for (auto P: res[i]) {
            P.print();
            cout << '\n';
        }
    }
}

void _main(){
    int n; cin >> n;
    search_Pach_Tardos(n);
    return;
}

int main(){
    ios_base::sync_with_stdio(0),cin.tie(0);
    _main();
}
