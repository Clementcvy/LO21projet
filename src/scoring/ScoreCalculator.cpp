#include "scoring/ScoreCalculator.h"
#include "scoring/LandscapeScoreCalculator.h"
#include "scoring/AnimalCardScoreCalculator.h"
#include "scoring/NatureSpiritScoreCalculator.h"

namespace harmonies
{
    namespace scoring
    {
        model::ScoreReport calculateTotalScore(const model::Player& player)
        {
            model::ScoreReport report;
            const auto* board = player.getBoard();
            
            if (board == nullptr)
            {
                return report;
            }

            model::ScoreReport landscapeReport = LandscapeScoreReport(*board);
            report.addTreeScore(landscapeReport.getTreeScore());
            report.addMountainScore(landscapeReport.getMountainScore());
            report.addFieldScore(landscapeReport.getFieldScore());
            report.addBuildingScore(landscapeReport.getBuildingScore());
            report.addWaterScore(landscapeReport.getWaterScore());

            std::size_t totalAnimalScore = 0;
            const model::PlayerCardCollection *animalCards = player.getAnimalCards();
            if (animalCards != nullptr)
            {
                const std::vector<model::AnimalCard> &cards = animalCards->getCards();
                for (std::size_t i = 0; i < cards.size(); ++i)
                {
                    totalAnimalScore += AnimalCardScoreCalculator(cards[i]);
                }
            }
            report.addAnimalsScore(totalAnimalScore);

            const std::vector<model::NatureSpiritCard> &natureSpiritCards = player.getNatureSpiritCards();
            for (std::size_t i = 0; i < natureSpiritCards.size(); ++i)
            {
                std::size_t spiritScore = NatureSpiritScoreCalculator(natureSpiritCards[i], *board);
                report.addSpiritScore(spiritScore);
            }

            return report;
        }
    }
}
