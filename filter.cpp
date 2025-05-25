#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <utility>
#include <set>
#include <queue>
#include <cassert>
#include "pattern.cpp"

using namespace std;



void _main(){
    ifstream in("Pach_Tardos/exclude_Pach_Tardos_weight_8.txt");
    ifstream filter("outstanding_weight_6_patterns/contains_outstanding_pattern_weight_8.txt");

    assert(in && filter);

    vector<pattern> vec;

    int n; in >> n;
    for (int _ = 0; _ < n; ++_) {
    	int id; in >> id;
    	int h, w; in >> h >> w;
    	pattern P;
    	for (int i = 0; i < h; ++i) {
    		string s; in >> s;
    		for (int j = 0; j < w; ++j) {
    			if (s[j] == '#') P.push_back({i, j});
    		}
    	}
    	vec.push_back(P);
    }

    vector<pattern> all_filter;

    /*
    int h, w;
    while (filter >> h >> w) {
		pattern P;
    	for (int i = 0; i < h; ++i) {
    		string s; filter >> s;
    		for (int j = 0; j < w; ++j) {
    			if (s[j] == '#') P.push_back({i, j});
    		}
    	}
    	all_filter.push_back(P);
    }
    */

    filter >> n;
    for (int _ = 0; _ < n; ++_) {
    	int id; filter >> id;
    	int h, w; filter >> h >> w;
    	pattern P;
    	for (int i = 0; i < h; ++i) {
    		string s; filter >> s;
    		for (int j = 0; j < w; ++j) {
    			if (s[j] == '#') P.push_back({i, j});
    		}
    	}
    	all_filter.push_back(P);
    }

    sort(all_filter.begin(), all_filter.end());

    vector<pattern> filtered;

    for (auto P: vec) {
    	if (!binary_search(all_filter.begin(), all_filter.end(), P)) {
    		filtered.push_back(P);
    	}
    }

    sort(filtered.begin(), filtered.end());

    cout << filtered.size() << "\n";
    for (int i = 0; i < filtered.size(); ++i) {
        cout << i << '\n';
        filtered[i].print();
        cout << '\n';
    }
}

int main(){
    ios_base::sync_with_stdio(0),cin.tie(0);
    _main();
}