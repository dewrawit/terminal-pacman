#pragma once

#include <string>
#include <string_view>
#include <fstream>
#include <print>
#include <algorithm>
#include <ranges>
#include <vector>
#include <utility>
#include <format>

class SaveSystem
{
    using SV = std::string_view;
    using PlayerAndScores = std::pair<std::string, int>;

    const std::string saveFileName {"saveSystem/Leaderboard.txt"};

    public:
    SaveSystem() = default;
    int getHighScore() const 
    {
        //First row is the highest score
        std::ifstream inSaveFile { saveFileName };

        if(inSaveFile)
        {
            [[maybe_unused]] std::string name{};
            int score{};

            inSaveFile >> name >> score;

            inSaveFile.close();
            return score;
        }
        else
        {
            return 0;
        }
    }
    void save(SV newName, int newScore) const
    {
        std::ifstream inSaveFile { saveFileName };

        std::vector<PlayerAndScores> playerScores{};

        //If file doesn't open then it's the first play so leaderboard is not created yet
        if(inSaveFile)
        {
            //Read file data
            std::string name{};
            int score{};
            while(inSaveFile >> name >> score)
            {
                playerScores.emplace_back(std::pair{name, score});
            }
            inSaveFile.close();
        }

        playerScores.emplace_back(std::pair{newName, newScore});
        
        std::ranges::sort(playerScores, 
            [](const PlayerAndScores& ps1, const PlayerAndScores& ps2) -> bool
            {
                int score1 = ps1.second;
                int score2 = ps2.second;

                return score1 > score2; //sort descending
            }
        );

        //Load back into file (clear old content first)
        std::ofstream outSaveFile { saveFileName, std::ios::out | std::ios::trunc };

        if(!outSaveFile)
        {
            throw std::runtime_error(std::format("Unable to open {} file", saveFileName));
        }

        for(const auto& [name, score] : playerScores)
        {
            outSaveFile << name << ' ' << score << '\n';
        }
        outSaveFile.close();
    }   
    void loadLeaderboard() const
    {
        std::ifstream saveFile { saveFileName };

        if(!saveFile)
        {
            throw std::runtime_error(std::format("Unable to open {} file", saveFileName));
        }

        std::string name{};
        int score{};

        std::println("==========Leaderboard==========");

        int rank { 1 };
        while(saveFile  >> name >> score)
        {
            std::println("{}.    {}         {}",rank,name,score);
            ++rank;
        }     

        std::println("===============================");
    }
};