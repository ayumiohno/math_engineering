#include <algorithm>
#include <iostream>
#include <vector>

void loop(std::vector<std::vector<int>>& rank_first, const std::vector<std::vector<int>>& rank_second, std::vector<int>& result, int choosing)
{
    if (choosing == rank_first.size()) {
        //loop終了
    } else {
        auto target = rank_first.at(choosing).at(0);
        auto lival = std::find(result.begin(), result.end(), target) - result.begin();
        if (lival == result.size()) {
            if (choosing == result.size()) {
                result.push_back(target);
            } else {
                result.at(choosing) = target;
            }
            //std::cout << "choosing: " << choosing << " target: " << target << " no lival" << std::endl;
            loop(rank_first, rank_second, result, result.size());
        } else {
            auto choosing_rank = std::find(rank_second.at(target).begin(), rank_second.at(target).end(), choosing) - rank_second.at(target).begin();
            auto lival_rank = std::find(rank_second.at(target).begin(), rank_second.at(target).end(), lival) - rank_second.at(target).begin();
            //std::cout << "choosing: " << choosing << " target: " << target << " lival: " << lival;
            if (choosing_rank > lival_rank) {
                rank_first.at(choosing).erase(rank_first.at(choosing).begin());
                loop(rank_first, rank_second, result, choosing);
            } else {
                rank_first.at(lival).erase(rank_first.at(lival).begin());
                if (choosing == result.size()) {
                    result.push_back(target);
                } else {
                    result.at(choosing) = target;
                }
                loop(rank_first, rank_second, result, lival);
            }
        }
    }
}


int main()
{
    std::vector<std::vector<int>> rank_first = {{4, 5, 2, 1, 0, 3},
        {0, 2, 5, 4, 1, 3},
        {4, 0, 3, 2, 1, 5},
        {4, 0, 5, 1, 3, 2},
        {0, 2, 1, 5, 4, 3},
		{3, 2, 1, 0, 4, 5}};

    std::vector<std::vector<int>> rank_second = {{2, 5, 3, 1, 4, 0},
        {3, 5, 0, 2, 1, 4},
        {3, 0, 5, 1, 2, 4},
        {5, 4, 1, 0, 3, 2},
        {4, 2, 1, 5, 0, 3},
		{0, 3, 4, 5, 2, 1}};

    std::vector<int> result;

    loop(rank_first, rank_second, result, 0);

    for (auto target : result) {
        std::cout << target << " ";
    }
    std::cout << std::endl;
}
