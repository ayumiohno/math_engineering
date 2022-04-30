#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

bool loop(int u, std::vector<int> &u_1, std::vector<int> &v_1,
          std::vector<int> path_pre, std::vector<int> &matches,
          const std::vector<std::pair<int, int>> &edges) {
  auto where = edges.begin();
  while ((where = std::find_if(
              where, edges.end(), [&](const std::pair<int, int> e) {
                return e.first == u &&
                       !std::any_of(
                           matches.begin(), matches.end(),
                           [&](const int m) { return edges.at(m) == e; }) &&
                       !std::any_of(path_pre.begin(), path_pre.end(),
                                    [&](const int p) {
                                      return edges.at(p).second == e.second;
                                    });
              })) != edges.end()) {
    auto path = path_pre;
    path.push_back(where - edges.begin());
    auto v_elem = (*where).second;

    auto is_v0 = !any_of(v_1.begin(), v_1.end(),
                         [&](const int v1_elem) { return v1_elem == v_elem; });

    std::cout << "serching u: " << u << " connected v: " << v_elem << std::endl;
    if (is_v0) {
      // u_1,v_1更新
      u_1.push_back(edges.at(path.at(0)).first);
      v_1.push_back(v_elem);

      auto p_size = path.size();
      std::cout << "found zoukadou. path_size: " << p_size << std::endl;

      // matches^pathを消す
      for (std::size_t i = 1; i < p_size; i += 2) {
        matches.erase(std::find(matches.begin(), matches.end(), path.at(i)));
        std::cout << "delete match: " << edges.at(path.at(i)).first << " "
                  << edges.at(path.at(i)).second << std::endl;
      }
      // path/matchesを加える
      for (std::size_t i = 0; i < p_size; i += 2) {
        matches.push_back(path.at(i));
        std::cout << "add match: " << edges.at(path.at(i)).first << " "
                  << edges.at(path.at(i)).second << std::endl;
      }
      return true; //増加道が見つかった
    } else {
      auto itr_match =
          std::find_if(matches.begin(), matches.end(), [&](const int m) {
            return edges.at(m).second == v_elem;
          });

      if (itr_match == matches.end()) {
        std::cout << "ikidomari" << std::endl;
        continue; //行き止まり
      } else {
        path.push_back(*itr_match);
        std::cout << "next u: " << edges.at(*itr_match).first << std::endl;
        if (loop(edges.at(*itr_match).first, u_1, v_1, path, matches, edges)) {
          break;
        };
      }
    }
    where += 1;
  }

  std::cout << "ikidomari" << std::endl;
  return false; //行き止まり
}

int main() {
  std::vector<std::pair<int, int>> edges;
  edges.push_back({0, 0});
  edges.push_back({0, 2});
  edges.push_back({0, 3});
  edges.push_back({1, 0});
  edges.push_back({1, 1});
  edges.push_back({1, 7});
  edges.push_back({2, 0});
  edges.push_back({2, 2});
  edges.push_back({3, 2});
  edges.push_back({3, 3});
  edges.push_back({4, 2});
  edges.push_back({4, 3});
  edges.push_back({5, 1});
  edges.push_back({5, 6});
  edges.push_back({6, 4});
  edges.push_back({6, 5});
  edges.push_back({6, 9});
  edges.push_back({7, 4});
  edges.push_back({7, 5});
  edges.push_back({7, 7});
  edges.push_back({7, 9});
  edges.push_back({8, 8});
  edges.push_back({9, 3});
  edges.push_back({9, 8});

  std::vector<int> matches = {};
  std::vector<int> path = {};
  std::vector<int> u_1 = {};
  std::vector<int> v_1 = {};
  std::vector<int> u_all = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

  // U_0からV_0へたどり着けるか

  bool is_found = true;

  while (is_found) {
    is_found = false;
    for (auto u : u_all) {
      if (!std::any_of(u_1.begin(), u_1.end(),
                       [&](int u1) { return u == u1; })) {
        if (loop(u, u_1, v_1, path, matches, edges)) {
          is_found = true;
          std::cout << "next u0" << std::endl;
          break;
        }
      }
    }
  }

  std::cout << matches.size() << std::endl;
}
