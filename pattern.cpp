#include <algorithm>
#include <vector>
#include <utility>
#include <set>
#include <queue>

struct pattern: std::vector<std::pair<int,int>> {
    void sort() {
        std::sort(begin(), end());
    }
    bool have(int i, int j) {
        return std::find(begin(), end(), std::pair<int,int>(i, j)) != end();
    }
    bool cmp (pattern o) {
        std::vector<std::pair<int,int>> vec1 = *this, vec2 = o;
        return vec1 < vec2;
    }
    void shift() {
        std::vector<int> X, Y;
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
    std::pair<int,int> dimension() {
        int max_x = -1, max_y = -1;
        for (auto &[x, y]: *this) {
            max_x = std::max(max_x, x);
            max_y = std::max(max_y, y);
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
        std::cout << n << ' ' << m << '\n';
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                std::cout << (std::binary_search(begin(), end(), std::pair<int,int>(i, j)) ? '#' : '.');
            }
            std::cout << '\n';
        }
    }
    void input() {
        int n, m; std::cin >> n >> m;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                char c; std::cin >> c;
                if (c == '#') push_back({i, j});
            }
        }
    }
    std::vector<pattern> extend() {
        shift();
        sort();
        auto [n, m] = dimension();
        std::vector<pattern> res;
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
    std::vector<pattern> extend_acyclic() {
        shift();
        sort();
        auto [n, m] = dimension();
        std::vector<pattern> res;
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
    std::vector<pattern> extend_const() {
        shift();
        sort();
        auto [n, m] = dimension();
        std::vector<pattern> res;
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
            new_P.erase(std::find(new_P.begin(), new_P.end(), std::pair<int, int>(x, y)));
            new_P.canonical();
            res.push_back(new_P);
        }
        std::sort(res.begin(), res.end());
        res.resize(unique(res.begin(), res.end()) - res.begin());
        return res;
    }
    std::vector<pattern> extend_log() {
        shift();
        sort();
        auto [n, m] = dimension();
        std::vector<pattern> res;
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