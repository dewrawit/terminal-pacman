#pragma once

#include <string>
#include <string_view>
#include <fstream>
#include <print>
#include <algorithm>
#include <ranges>
#include <vector>
#include <utility>

class SaveSystem
{
    using SV = std::string_view;
    using PlayerAndScores = std::pair<std::string, int>;

    public:
    SaveSystem() = default;
    void save(SV newName, int newScore)
    {
        std::ifstream inSaveFile ("Leaderboard.txt");

        if(!inSaveFile)
        {
            throw std::runtime_error("Unable to open Leaderboard.txt file");
        }

        std::string name{};
        int score{};

        std::vector<PlayerAndScores> playerScores{};

        //Read file data
        while(inSaveFile >> name >> score)
        {
            playerScores.emplace_back(std::pair{name, score});
        }
        playerScores.emplace_back(std::pair{newName, newScore});
        inSaveFile.close();

        std::ranges::sort(playerScores, 
            [](const PlayerAndScores& ps1, const PlayerAndScores& ps2) -> bool
            {
                int score1 = ps1.second;
                int score2 = ps2.second;

                return score1 > score2; //sort descending
            }
        );

        //Load back into file (clear old content first)
        std::ofstream outSaveFile("Leaderboard.txt", std::ios::out | std::ios::trunc);

        if(!inSaveFile)
        {
            throw std::runtime_error("Unable to open Leaderboard.txt file");
        }

        for(const auto& [name, score] : playerScores)
        {
            outSaveFile << name << ' ' << score << '\n';
        }
        outSaveFile.close();
    }   
    void loadLeaderboard()
    {
        std::fstream saveFile ("Leaderboard.txt");
        std::string name{};
        int score{};

        std::println("==========Leaderboard==========");

        int rank { 1 };
        while(saveFile  >> name >> score)
        {
            println("{}.    {}      {}",rank,name,score);
        }
        ++rank;
    }
};