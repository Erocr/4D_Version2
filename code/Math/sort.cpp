#include "Math/sort.hpp"

template<typename T>
vector<T> quicksort(vector<pair<int, T>>& not_sorted) {
	if (not_sorted.size() == 2) {
		if (not_sorted[0].first > not_sorted[1].first) {
			return { not_sorted[1].second, not_sorted[0].second };
		}
		return { not_sorted[0].second, not_sorted[1].second };
	}
	else if (not_sorted.size() == 1) {
		return { not_sorted[0].second };
	}
	vector<pair<int, T>> leftside(not_sorted.size());
	vector<pair<int, T>> rightside(not_sorted.size());
	int p1 = 0, p2 = 0;
	pair<int, T> pivot = not_sorted[0];
	for (int i = 1; i < not_sorted.size(); i++) {
		if (not_sorted[i].first > pivot.first) {
			rightside[p2] = not_sorted[i];
			p2++;
		}
		else if (not_sorted[i].first < pivot.first) {
			leftside[p1] = not_sorted[i];
			p1++;
		}
		else {
			if (p2 > p1) {
				leftside[p1] = not_sorted[i];
				p1++;
			}
			else {
				rightside[p2] = not_sorted[i];
				p2++;
			}
		}
	}
	leftside.resize(p1);
	rightside.resize(p2);
	vector<T> res_leftside = quicksort<T>(leftside);
	vector<T> res_rightside = quicksort<T>(rightside);
	vector<T> sorted(not_sorted.size());
	for (int i = 0; i < res_leftside.size(); i++) {
		sorted[i] = res_leftside[i];
	}
	sorted[res_leftside.size()] = pivot.second;
	for (int i = 0; i < res_rightside.size(); i++) {
		sorted[res_leftside.size() + 1 + i] = res_rightside[i];
	}
	return sorted;
}

template <typename T>
int find_max_pow_10(const vector<pair<int, T>> & elements) {
	int max_pow_10 = 0;
	int pow_10;
	for (pair<int, T> const &elt : elements) {
		pow_10 = int(log10(elt.first));
		if (pow_10 > max_pow_10) max_pow_10 = pow_10;
	}
	return max_pow_10;
}

template <typename T>
vector<T> radixsort(vector<pair<int, T>>& not_sorted, int max_pow_10) {
	if (max_pow_10 == -1) {
		max_pow_10 = find_max_pow_10(not_sorted);
	} 
	if (max_pow_10 == 0 or not_sorted.size() <= 1) {
		vector<T> res(not_sorted.size());
		for (int i = 0; i < not_sorted.size(); i++) {
			res[i] = not_sorted[i].second;
		}
		return res;
	}
	vector<vector<pair<int, T>>> sorted(10, vector<pair<int, T>>(0));
	int factor = pow(10, max_pow_10);
	for (pair<int, T> const &elt : not_sorted) {
		sorted[elt.first / factor].push_back(pair<int, T>(elt.first%factor, elt.second));
	}
	vector<T> res;
	vector<T> to_add;
	for (int i = 0; i < 10; i++) {
		if (sorted[i].size() == 0) {
			continue;
		}
		else if (sorted[i].size() == 1) {
			res.push_back(sorted[i][0].second);
		}
		else {
			to_add = radixsort<T>(sorted[i], max_pow_10 - 1);
			for (int j = 0; j < to_add.size(); j++) {
				res.push_back(to_add[j]);
			}
		}
	}
	return res;
}

template<typename T>
void draw_vector_pairs(vector<pair<int, T>> to_draw) {
	for (int i = 0; i < to_draw.size(); i++) {
		cout << to_draw[i].first << " " << to_draw[i].second << "\n";
	}
}