#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>
#include <set>
#include <queue>

using namespace std;

// using pattern = vector<pair<int,int>>;

struct pattern: vector<pair<int,int>> {
    void sort() {
        std::sort(begin(), end());
    }
    bool have(int i, int j) {
        return std::find(begin(), end(), pair<int,int>(i, j)) != end();
    }
    bool cmp (pattern o) {
        vector<pair<int,int>> vec1 = *this, vec2 = o;
        return vec1 < vec2;
    }
    void shift() {
        vector<int> X, Y;
        for (auto &[x, y]: *this) {
            X.push_back(x);
            Y.push_back(y);
        }
        std::sort(X.begin(), X.end());
        std::sort(Y.begin(), Y.end());
        X.resize(unique(X.begin(), X.end()) - X.begin());
        Y.resize(unique(Y.begin(), Y.end()) - Y.begin());
        for (auto &[x, y]: *this) {
            x = lower_bound(X.begin(), X.end(), x) - X.begin();
            y = lower_bound(Y.begin(), Y.end(), y) - Y.begin();
        }
    }
    pair<int,int> dimension() {
        int max_x = -1, max_y = -1;
        for (auto &[x, y]: *this) {
            max_x = max(max_x, x);
            max_y = max(max_y, y);
        }
        return {max_x + 1, max_y + 1};
    }
    void rotate() {
        shift();
        auto [n, m] = dimension();
        for (auto &[x, y]: *this) {
            int nx = y, ny = n - 1 - x;
            x = nx, y = ny;
        }
        sort();
    }
    void flip() {
        shift();
        auto [n, m] = dimension();
        for (auto &[x, y]: *this) {
            y = m - 1 - y;
        }
        sort();
    }
    void canonical() {
        sort();
        shift();
        pattern res = *this;
        for (int i: {0, 1}) {
            for (int j: {0, 1, 2, 3}) {
                if ((*this) < res) res = *this;
                rotate();
            }
            flip();
        }
        *this = res;
    }
    bool operator < (const pattern &o) const {
        pattern P = *this, Q = o;
        // P.canonical(), Q.canonical();
        if (P.dimension() < Q.dimension()) return true;
        if (P.dimension() == Q.dimension() && P.cmp(Q)) return true;
        return false;
    }
    void print() {
        auto [n, m] = dimension();
        sort();
        cout << n << ' ' << m << '\n';
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                cout << (binary_search(begin(), end(), pair<int,int>(i, j)) ? '#' : '.');
            }
            cout << '\n';
        }
    }
    vector<pattern> extend() {
        shift();
        sort();
        auto [n, m] = dimension();
        vector<pattern> res;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (!have(i, j)) {
                    pattern new_P = *this;
                    new_P.push_back({i, j});
                    new_P.canonical();
                    res.push_back(new_P);
                }
            }
        }
        for (int i = 0; i <= n; ++i) {
            for (int j = 0; j <= m; ++j) {
                pattern new_P = *this;
                for (auto &[x, y]: new_P) {
                    if (y >= j) ++y;
                }
                new_P.push_back({i, j});
                new_P.canonical();
                res.push_back(new_P);
                new_P = *this;
                for (auto &[x, y]: new_P) {
                    if (x >= i) ++x;
                }
                new_P.push_back({i, j});
                new_P.canonical();
                res.push_back(new_P);
            }
        }
        for (int i = 0; i <= n; ++i) {
            for (int j = 0; j <= m; ++j) {
                pattern new_P = *this;
                for (auto &[x, y]: new_P) {
                    if (x >= i) ++x;
                    if (y >= j) ++y;
                }
                new_P.push_back({i, j});
                new_P.canonical();
                res.push_back(new_P);
            }
        }
        std::sort(res.begin(), res.end());
        res.resize(unique(res.begin(), res.end()) - res.begin());
        return res;
    }
    vector<pattern> extend_acyclic() {
        shift();
        sort();
        auto [n, m] = dimension();
        vector<pattern> res;
        for (int i = 0; i <= n; ++i) {
            for (int j = 0; j <= m; ++j) {
                pattern new_P = *this;
                for (auto &[x, y]: new_P) {
                    if (y >= j) ++y;
                }
                new_P.push_back({i, j});
                new_P.canonical();
                res.push_back(new_P);
                new_P = *this;
                for (auto &[x, y]: new_P) {
                    if (x >= i) ++x;
                }
                new_P.push_back({i, j});
                new_P.canonical();
                res.push_back(new_P);
            }
        }
        for (int i = 0; i <= n; ++i) {
            for (int j = 0; j <= m; ++j) {
                pattern new_P = *this;
                for (auto &[x, y]: new_P) {
                    if (x >= i) ++x;
                    if (y >= j) ++y;
                }
                new_P.push_back({i, j});
                new_P.canonical();
                res.push_back(new_P);
            }
        }
        std::sort(res.begin(), res.end());
        res.resize(unique(res.begin(), res.end()) - res.begin());
        return res;
    }
    vector<pattern> extend_const() {
        shift();
        sort();
        auto [n, m] = dimension();
        vector<pattern> res;
        for (int i = 0; i < n; ++i) {
            if (have(i, 0)) {
                pattern new_P = *this;
                new_P.push_back({i, -1});
                new_P.canonical();
                res.push_back(new_P);
            }
            if (have(i, m - 1)) {
                pattern new_P = *this;
                new_P.push_back({i, m});
                new_P.canonical();
                res.push_back(new_P);
            }
        }
        for (int j = 0; j < m; ++j) {
            if (have(0, j)) {
                pattern new_P = *this;
                new_P.push_back({-1, j});
                new_P.canonical();
                res.push_back(new_P);
            }
            if (have(n - 1, j)) {
                pattern new_P = *this;
                new_P.push_back({n, j});
                new_P.canonical();
                res.push_back(new_P);
            }
        }
        for (auto &[x, y]: *this) {
            pattern new_P = *this;
            new_P.erase(std::find(new_P.begin(), new_P.end(), pair<int, int>(x, y)));
            new_P.canonical();
            res.push_back(new_P);
        }
        std::sort(res.begin(), res.end());
        res.resize(unique(res.begin(), res.end()) - res.begin());
        return res;
    }
    vector<pattern> extend_log() {
        shift();
        sort();
        auto [n, m] = dimension();
        vector<pattern> res;
        // [PT06] type 1
        for (int i = 0; i < n; ++i) {
            {
                pattern new_P = *this;
                new_P.push_back({i, -1});
                new_P.canonical();
                res.push_back(new_P);
            }
            {
                pattern new_P = *this;
                new_P.push_back({i, m});
                new_P.canonical();
                res.push_back(new_P);
            }
        }
        for (int j = 0; j < m; ++j) {
            {
                pattern new_P = *this;
                new_P.push_back({-1, j});
                new_P.canonical();
                res.push_back(new_P);
            }
            {
                pattern new_P = *this;
                new_P.push_back({n, j});
                new_P.canonical();
                res.push_back(new_P);
            }
        }
        // [PT06] type 2
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (have(i, j) && have(i, j + 1)) {
                    for (int ii = 0; ii < n; ++ii) {
                        if (have(ii, j) || have(ii, j + 1)) {
                            pattern new_P = *this;
                            for (auto &[x, y]: new_P) {
                                if (y > j) ++y;
                            }
                            new_P.push_back({ii, j + 1});
                            new_P.canonical();
                            res.push_back(new_P);
                        }
                    }
                }
            }
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (have(i, j) && have(i + 1, j)) {
                    for (int jj = 0; jj < m; ++jj) {
                        if (have(i, jj) || have(i + 1, jj)) {
                            pattern new_P = *this;
                            for (auto &[x, y]: new_P) {
                                if (x > i) ++x;
                            }
                            new_P.push_back({i + 1, jj});
                            new_P.canonical();
                            res.push_back(new_P);
                        }
                    }
                }
            }
        }
        // [PT06] type 3
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (have(i, j) && have(i, j + 1)) {
                    for (int ii = 0; ii < n; ++ii) {
                        for (int iii = 0; iii < n; ++iii) {
                            if (have(ii, j) && have(iii, j + 1)) {
                                pattern new_P = *this;
                                for (auto &[x, y]: new_P) {
                                    if (y > j) y += 2;
                                }
                                new_P.push_back({ii, j + 1});
                                new_P.push_back({iii, j + 2});
                                new_P.canonical();
                                res.push_back(new_P);
                            }
                        }
                    }
                }
            }
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (have(i, j) && have(i + 1, j)) {
                    for (int jj = 0; jj < m; ++jj) {
                        for (int jjj = 0; jjj < m; ++jjj) {
                            if (have(i, jj) && have(i + 1, jjj)) {
                                pattern new_P = *this;
                                for (auto &[x, y]: new_P) {
                                    if (x > i) x += 2;
                                }
                                new_P.push_back({i + 1, jj});
                                new_P.push_back({i + 2, jjj});
                                new_P.canonical();
                                res.push_back(new_P);
                            }
                        }
                    }
                }
            }
        }
        std::sort(res.begin(), res.end());
        res.resize(unique(res.begin(), res.end()) - res.begin());
        return res;
    }
};

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

void amano_hina_is_the_goat(){
    int n; cin >> n;
    bfs(n);
    return;
    /*
    pattern P;
    P.push_back({0, 0});
    P.push_back({0, 1});
    P.push_back({1, 0});
    P.push_back({1, 2});
    P.shift();
    //P.print();
    P.rotate();
    //P.print();
    P.flip();
    //P.print();
    P.canonical();
    //P.print();
    vector<pattern> vec = P.extend();
    for (auto Q: vec) {
        Q.print();
        cout << "\n";
    }
    */
    pattern P;
    P.push_back({0, 0});
    queue<pattern> q;
    set<pattern> st;
    q.push(P);
    st.insert(P);
    const int N = 7;
    int cnt[N + 1]{};
    while (!q.empty()) {
        P = q.front(); q.pop();
        if (P.size() > N) continue;
        cnt[P.size()]++;
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
        cout << i << ' ' << cnt[i] << "\n";
    }
    /*
    for (int i = 1; i <= 6; ++i) {
        vector<pattern> new_vec;
        for (auto P: vec) {
            vector<pattern> vec2 = P.extend();
            for (auto Q: vec2) new_vec.push_back(Q);
        }
        sort(new_vec.begin(), new_vec.end());
        new_vec.resize(unique(new_vec.begin(), new_vec.end()) - new_vec.begin());
        cout << i + 1 << ' ' << new_vec.size() << "\n";
        
        for (auto P: new_vec) {
            P.print();
            cout << "\n";
        }
        
        vec = new_vec;
    }
    */
}

signed main(){
    ios_base::sync_with_stdio(0),cin.tie(0);
    int t=1; //cin >> t;
    while(t--) amano_hina_is_the_goat();
}
