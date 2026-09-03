#include <iostream>
#include <string>

#include "model/Player.h"
#include "model/BoardSide.h"
#include "model/ScoreReport.h"
#include "model/TokenType.h"
#include "scoring/ScoreCalculator.h"
#include "utils/hexCoord.h"

using harmonies::model::BoardSide;
using harmonies::model::Player;
using harmonies::model::ScoreReport;
using harmonies::model::TokenType;
using harmonies::scoring::calculateTotalScore;
using harmonies::utils::HexCoord;

namespace
{
    void check(bool condition, const std::string &message, int &failures)
    {
        if (condition)
        {
            std::cout << "[PASS] " << message << '\n';
        }
        else
        {
            std::cout << "[FAIL] " << message << '\n';
            ++failures;
        }
    }
}

int main()
{
    int failures = 0;

    std::cout << "--- Testing ScoreCalculator ---\n";

    {
        Player player("Peilin", BoardSide::A);
        ScoreReport report = calculateTotalScore(player);

        check(report.getTreeScore() == 0,
              "An empty player assets calculation should return 0 tree score",
              failures);
        check(report.getAnimalsScore() == 0,
              "An empty player assets calculation should return 0 animals score",
              failures);
        check(report.getSpiritScore() == 0,
              "An empty player assets calculation should return 0 spirit score",
              failures);
        check(report.getTotalScore() == 0,
              "An empty player board should sum up to exactly 0 total points",
              failures);
    }

    {
        Player player("Alice", BoardSide::A);
        player.getBoard()->placeToken(HexCoord(-2, 0), TokenType::BrownEarth);
        player.getBoard()->placeToken(HexCoord(-2, 0), TokenType::BrownEarth);
        player.getBoard()->placeToken(HexCoord(-2, 0), TokenType::GreenTree);
        player.getBoard()->placeToken(HexCoord(0, 0), TokenType::BlueWater);
        player.getBoard()->placeToken(HexCoord(1, 0), TokenType::BlueWater);
        player.getBoard()->placeToken(HexCoord(2, 0), TokenType::BlueWater);

        ScoreReport report = calculateTotalScore(player);

        check(report.getTreeScore() == 7,
              "Landscape tree points should be reported as tree score",
              failures);
        check(report.getWaterScore() == 5,
              "Landscape river points should be reported as water score",
              failures);
        check(report.getTotalScore() == 12,
              "The detailed score report should still preserve the total score",
              failures);
    }

    std::cout << "\nFailures: " << failures << '\n';
    return failures == 0 ? 0 : 1;
}
