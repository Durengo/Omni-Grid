#include "Checkers.h"

#include <random>

#include <durlib.h>

#include "GameLogicImplementation/GameConfiguration.h"
#include "Games/Checkers/CheckersPieces.h"
#include "Games/Checkers/CheckersStateCheck.h"
#include "Player/Piece.h"
#include "Player/Player.h"
#include "GameLogicImplementation/PieceRules.h"
#include "User/Score.h"

namespace OGRID
{

    bool Checkers::TryMakeMove(unsigned char &row, unsigned char &col)
    {
        // if for some reason the selected piece is still not reset after a move, reset it.
        if (m_SelectedPiece != nullptr && m_SelectedPiece->GetOwner()->GetSide() != m_currentPlayer->GetSide())
        {
            m_SelectedPiece = nullptr;
        }

        // If there is your piece at the selected position, select it
        Piece *piece = GetGrid()->GetPieceAt(row, col);
        if (piece != nullptr)
        {
            if (piece->GetOwner() != m_currentPlayer)
            {
                CLI_WARN("Not your piece.");
                return false;
            }

            m_SelectedPiece = piece;
            return false;
        }

        // If there is no piece selected, and you tried to move, return
        if (m_SelectedPiece == nullptr)
        {
            CLI_WARN("No piece selected.");
            return false;
        }

        std::pair<int, int> coords = GetPiecePosition(m_SelectedPiece);
        if (coords.first == -1 && coords.second == -1)
        {
            CLI_WARN("Piece coords not found.");
            return false;
        }

        // Try to move the piece
        if (m_SelectedPiece->isValidMove(GetGameConfiguration()->grid, coords.first, coords.second, col, row))
        {
            // Set the piece at the new position
            GetGameConfiguration()->grid->SetPieceAt(row, col, m_SelectedPiece);

            // Set the old position to nullptr
            GetGameConfiguration()->grid->SetPieceAt(coords.second, coords.first, nullptr, true);

            // Remove the old piece from the piece manager
            RemovePieceFromPieceManager(coords);

            // Update the piece manager
            SetPiecePosition(m_SelectedPiece, std::pair<int, int>(col, row));

            // If not a super piece
            // And has reached board end as white
            // or black
            if (!IsSuperPiece(m_SelectedPiece) &&
                ((row == 0 && m_SelectedPiece->GetOwner()->GetSide() == 0) ||
                 (row == GetGameConfiguration()->grid->GetRows() - 1 && m_SelectedPiece->GetOwner()->GetSide() == 1)))
            {
                AddAsSuperPiece(m_SelectedPiece);
            }

            // Reset the selected piece
            m_SelectedPiece = nullptr;

            return true;
        }

        // If every move failed, try to attack
        bool canContinue = false;
        if (m_SelectedPiece->isValidAttack(GetGameConfiguration()->grid, coords.first, coords.second, col, row, canContinue))
        {
            // Set the piece at the new position
            GetGameConfiguration()->grid->SetPieceAt(row, col, m_SelectedPiece);

            // Set the old position to nullptr
            GetGameConfiguration()->grid->SetPieceAt(coords.second, coords.first, nullptr, true);

            // Remove the old piece from the piece manager
            RemovePieceFromPieceManager(coords);

            // Update the piece manager
            SetPiecePosition(m_SelectedPiece, std::pair<int, int>(col, row));

            int deltaX = coords.first < col ? 1 : -1;
            int deltaY = coords.second < row ? 1 : -1;

            GetGameConfiguration()->grid->SetPieceAt(row - deltaY, col - deltaX, nullptr, true);
            delete GetGameConfiguration()->grid->GetPieceAt(row - deltaY, col - deltaX);

            // If not a super piece
            // And has reached board end as white
            // or black
            if (!IsSuperPiece(m_SelectedPiece) &&
                ((row == 0 && m_SelectedPiece->GetOwner()->GetSide() == 0) ||
                 (row == GetGameConfiguration()->grid->GetRows() - 1 && m_SelectedPiece->GetOwner()->GetSide() == 1)))
            {
                AddAsSuperPiece(m_SelectedPiece);
            }

            // Cleanup piece manager and supers
            for (auto each : m_Pieces)
            {
                if (each.second == nullptr)
                {
                    m_Pieces.erase(each.first);
                }
            }
            for (auto each : m_Supers)
            {
                if (each == nullptr)
                {
                    m_Supers.erase(std::remove(m_Supers.begin(), m_Supers.end(), each), m_Supers.end());
                }
            }

            if (canContinue)
            {
                // If you can continue attacking
                // Don't end turn
                return false;
            }
            else
            {
                // If you can't continue attacking
                // Reset the selected piece
                m_SelectedPiece = nullptr;
                // End turn
                return true;
            }
        }
        return false;
    }

    bool Checkers::IsWinningCondition()
    {
        switch (m_currentGameState->CheckWin(GetGameConfiguration()->grid))
        {
        case -1:
            return false;
        default:
            m_winner = m_currentPlayer;

            if (m_winner == m_User->GetPlayer())
            {
                m_User->GetScore()->AddWin();
            }
            else
            {
                m_User->GetScore()->AddLoss();
            }

            return true;
        }
    }

    bool Checkers::IsDrawCondition()
    {
        // Never
        return false;
    }

    void Checkers::SetupPlayers()
    {
        std::vector<int> totalValidSides = {0, 1};

        if (m_randomizeTurnOrder)
        {
            std::vector<int> shuffledMoveTypes = totalValidSides;
            std::random_device rd;
            auto rng = std::default_random_engine{rd()};
            std::shuffle(shuffledMoveTypes.begin(), shuffledMoveTypes.end(), rng);

            for (int i = 0; i < GetGameConfiguration()->playerPairs.size(); i++)
            {
                GetGameConfiguration()->playerPairs[i].ptr->SetSide(shuffledMoveTypes[i % shuffledMoveTypes.size()]);
            }

            std::stable_sort(GetGameConfiguration()->playerPairs.begin(), GetGameConfiguration()->playerPairs.end(),
                             [](const OGRID::PlayerNameAndPtr &a, const OGRID::PlayerNameAndPtr &b)
                             {
                                 return a.ptr->GetSide() == 0;
                             });
        }
        else
        {
            for (int i = 0; i < GetGameConfiguration()->playerPairs.size(); i++)
            {
                GetGameConfiguration()->playerPairs[i].ptr->SetSide(totalValidSides[i % totalValidSides.size()]);
            }

            std::stable_sort(GetGameConfiguration()->playerPairs.begin(), GetGameConfiguration()->playerPairs.end(),
                             [](const OGRID::PlayerNameAndPtr &a, const OGRID::PlayerNameAndPtr &b)
                             {
                                 return a.ptr->GetSide() == 0;
                             });
        }

        m_currentPlayer = GetGameConfiguration()->playerPairs[0].ptr;

        SetupBoard();
    }

    void Checkers::Initialize(OGRID::User *user)
    {
        m_User = user;
        m_currentGameState = new GameStateChecker(new CheckersStateCheck());

        m_guiInfo = *new GUIInfo();
        m_guiInfo.windowName = "Checkers";
        m_guiInfo.width = 800;
        m_guiInfo.height = 600;
        m_guiInfo.targetFPS = 60;
        m_guiInfo.lineThickness = 2.5f;
        m_guiInfo.margin = 30.0f;

        auto *p1 = new OGRID::Player(m_User->GetUserName(), OGRID::Human);
        m_User->SetPlayer(p1);
        auto *p2 = new OGRID::Player("Player2", OGRID::Human);

        int choice = 0;
        while (choice == 0)
        {
            CLI_TRACE("\n1. Start as WHITE\n2. Start as BLACK\n3. Random");
            choice = DURLIB::GIBI(1, 3);
        }

        if (choice == 1)
        {
            SetRandomizeTurnOrder(false);
            SetGameConfiguration(OGRID::GameConfigurationBuilder()
                                     .setGameName("Checkers")
                                     .setGameDescription("Checkers Game")
                                     .setGrid(8, 8)
                                     .setMaxPlayers(2)
                                     .addPlayer(p1)
                                     .addPlayer(p2)
                                     .build());
        }
        else if (choice == 2)
        {
            SetRandomizeTurnOrder(false);
            SetGameConfiguration(OGRID::GameConfigurationBuilder()
                                     .setGameName("Checkers")
                                     .setGameDescription("Checkers Game")
                                     .setGrid(8, 8)
                                     .setMaxPlayers(2)
                                     .addPlayer(p2)
                                     .addPlayer(p1)
                                     .build());
        }
        else if (choice == 3)
        {
            SetRandomizeTurnOrder(true);
            SetGameConfiguration(OGRID::GameConfigurationBuilder()
                                     .setGameName("Checkers")
                                     .setGameDescription("Checkers Game")
                                     .setGrid(8, 8)
                                     .setMaxPlayers(2)
                                     .addPlayer(p1)
                                     .addPlayer(p2)
                                     .build());
        }
    }

    void Checkers::OnGUIUpdateGrid()
    {
        for (int i = 0; i < GetGameConfiguration()->grid->GetRows(); i++)
        {
            for (int j = 0; j < GetGameConfiguration()->grid->GetCols(); j++)
            {
                if (i % 2 == 0)
                {
                    if (j % 2 != 0)
                    {
                        DrawCell(i, j);
                    }
                }
                else
                {
                    if (j % 2 == 0)
                    {
                        DrawCell(i, j);
                    }
                }

                Piece *piece = GetGrid()->GetPieceAt(i, j);
                if (piece == nullptr)
                {
                    continue;
                }

                bool blinking = false;
                bool super = false;

                if (piece->GetOwner() == m_currentPlayer && m_SelectedPiece == piece)
                {
                    blinking = true;
                }

                if (IsSuperPiece(piece))
                {
                    super = true;
                }

                if (piece->GetOwner()->GetSide() == 0)
                {
                    DrawPiece(i, j, WHITE, blinking, super);
                }
                else if (piece->GetOwner()->GetSide() == 1)
                {
                    DrawPiece(i, j, BLACK, blinking, super);
                }
                else
                {
                    throw std::runtime_error("Invalid cell type.");
                }
            }
        }
    }

    void Checkers::OnGUIUpdateGridHover(Vector2 cell)
    {
        // Nothing for now
    }

    void Checkers::SetupBoard()
    {
        m_Pieces.clear();
        m_Supers.clear();

        // Add pieces to the board
        for (int row = 0; row < GetGameConfiguration()->grid->GetRows(); row++)
        {
            for (int col = 0; col < GetGameConfiguration()->grid->GetCols(); col++)
            {
                if (row % 2 == 0)
                {
                    if (col % 2 != 0)
                    {
                        if (row > 4)
                        {
                            GetGrid()->SetPieceAt(row, col, new WhitePieceCheckers(GetGameConfiguration()->playerPairs[0].ptr));
                            AddPieceToPieceManager(GetGrid()->GetPieceAt(row, col), std::pair<int, int>(col, row));
                        }
                        else if (row < 3)
                        {
                            GetGrid()->SetPieceAt(row, col, new BlackPieceCheckers(GetGameConfiguration()->playerPairs[1].ptr));
                            AddPieceToPieceManager(GetGrid()->GetPieceAt(row, col), std::pair<int, int>(col, row));
                        }
                    }
                }
                else
                {
                    if (col % 2 == 0)
                    {
                        if (row > 4)
                        {
                            GetGrid()->SetPieceAt(row, col, new WhitePieceCheckers(GetGameConfiguration()->playerPairs[0].ptr));
                            AddPieceToPieceManager(GetGrid()->GetPieceAt(row, col), std::pair<int, int>(col, row));
                        }
                        else if (row < 3)
                        {
                            GetGrid()->SetPieceAt(row, col, new BlackPieceCheckers(GetGameConfiguration()->playerPairs[1].ptr));
                            AddPieceToPieceManager(GetGrid()->GetPieceAt(row, col), std::pair<int, int>(col, row));
                        }
                    }
                }
            }
        }
    }

    void Checkers::AddAsSuperPiece(Piece *piece)
    {
        piece->AddMoveRule(new SuperCheckersMoveRule());
        piece->AddAttackRule(new JumpSuperCheckersAttackRule());
        m_Supers.push_back(piece);
    }

    void Checkers::RemoveSuperPiece(Piece *piece)
    {
        m_Supers.erase(std::remove(m_Supers.begin(), m_Supers.end(), piece), m_Supers.end());
    }

    bool Checkers::IsSuperPiece(Piece *piece)
    {

        return std::find(m_Supers.begin(), m_Supers.end(), piece) != m_Supers.end();
    }

    void Checkers::DrawPiece(int row, int col, Color color, bool blinking = false, bool super = false)
    {
        // Use the same margin for consistency
        float padding = m_guiInfo.margin;

        // Calculate offsets for non-square windows (same as in DrawGrid)
        float xOffset = (m_guiInfo.width - (m_guiInfo.cellSize * GetGrid()->GetCols())) / 2.0f;
        float yOffset = (m_guiInfo.height - (m_guiInfo.cellSize * GetGrid()->GetRows())) / 2.0f;
        xOffset = std::max(xOffset, padding);
        yOffset = std::max(yOffset, padding);

        // Calculate the center of the circle
        float centerX = xOffset + (col + 0.5f) * m_guiInfo.cellSize;
        float centerY = yOffset + (row + 0.5f) * m_guiInfo.cellSize;

        // Calculate the radius of the circle based on cell size and padding
        float radius = m_guiInfo.cellSize / 2.0f;

        if (blinking)
        {
            if (alpha == 1.0f || alpha == 0.0f)
            {
                // Invert the speed
                alphaSpeed = -alphaSpeed;
            }
            alpha += alphaSpeed;
            alpha = std::clamp(alpha, 0.0f, 1.0f);
            DrawCircleV(Vector2{centerX, centerY}, radius, Fade(color, alpha));
        }
        else
        {
            DrawCircleV(Vector2{centerX, centerY}, radius, color);
        }

        if (super)
        {
            DrawCircleV(Vector2{centerX, centerY}, radius / 2.0f, GOLD);
        }
    }

    void Checkers::DrawCell(int row, int col)
    {
        // Use the same margin for consistency
        float padding = m_guiInfo.margin;

        // Calculate offsets for non-square windows (same as in DrawGrid)
        float xOffset = (m_guiInfo.width - (m_guiInfo.cellSize * GetGrid()->GetCols())) / 2.0f;
        float yOffset = (m_guiInfo.height - (m_guiInfo.cellSize * GetGrid()->GetRows())) / 2.0f;
        xOffset = std::max(xOffset, padding);
        yOffset = std::max(yOffset, padding);

        // Calculate cell position
        float X = xOffset + col * m_guiInfo.cellSize;
        float Y = yOffset + row * m_guiInfo.cellSize;
        DrawRectangle(X, Y, m_guiInfo.cellSize, m_guiInfo.cellSize, BEIGE);
    }

    void Checkers::AddPieceToPieceManager(Piece *piece, std::pair<int, int> position)
    {
        m_Pieces[position] = piece;
    }

    void Checkers::RemovePieceFromPieceManager(Piece *piece)
    {
        for (auto each : m_Pieces)
        {
            if (each.second == piece)
            {
                m_Pieces[each.first] = nullptr;
                m_Pieces.erase(each.first);
                return;
            }
        }
    }

    void Checkers::RemovePieceFromPieceManager(std::pair<int, int> position)
    {
        m_Pieces[position] = nullptr;
        m_Pieces.erase(position);
    }

    std::pair<int, int> Checkers::GetPiecePosition(Piece *piece)
    {
        for (auto each : m_Pieces)
        {
            if (each.second == piece)
            {
                return each.first;
            }
        }
        return std::pair<int, int>(-1, -1);
    }

    void Checkers::SetPiecePosition(Piece *piece, std::pair<int, int> position)
    {
        m_Pieces[position] = piece;
    }
}
