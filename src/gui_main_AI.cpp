/**
 * @file gui_main.cpp
 * @author Writen by Copilot
 * @version 0.1
 * @date 2026-06-02
 * 
 */
#include "../include/connect4.h"
#include "../include/player.h"
#include "../include/AI_player.h"

#include <SFML/Graphics.hpp>

#include <array>
#include <chrono>
#include <future>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace {

constexpr unsigned WINDOW_WIDTH = 1000;
constexpr unsigned WINDOW_HEIGHT = 740;
constexpr float BOARD_LEFT = 35.f;
constexpr float BOARD_TOP = 110.f;
constexpr float CELL_SIZE = 82.f;
constexpr float DISC_RADIUS = 31.f;
constexpr float SIDEBAR_LEFT = 635.f;
constexpr float BUTTON_WIDTH = 325.f;
constexpr float BUTTON_HEIGHT = 42.f;
constexpr float AI_MOVE_DELAY_SECONDS = 0.1f;

const sf::Color BACKGROUND(244, 238, 224);
const sf::Color PANEL(28, 83, 143);
const sf::Color PANEL_LIGHT(239, 248, 255);
const sf::Color TEXT_DARK(31, 37, 41);
const sf::Color TEXT_LIGHT(250, 251, 252);
const sf::Color TOKEN_X(212, 72, 54);
const sf::Color TOKEN_O(241, 181, 53);
const sf::Color EMPTY_SLOT(247, 243, 233);
const sf::Color BUTTON_IDLE(24, 56, 100);
const sf::Color BUTTON_ACTIVE(210, 92, 58);
const sf::Color BUTTON_SOFT(204, 228, 247);
const sf::Color BUTTON_DISABLED(173, 178, 185);

struct Button {
    sf::FloatRect bounds;
    std::string label;
};

sf::Text makeText(const sf::Font &font, const std::string &label, unsigned size,
    const sf::Color &color, float x, float y)
{
    sf::Text text;
    text.setFont(font);
    text.setString(label);
    text.setCharacterSize(size);
    text.setFillColor(color);
    text.setPosition(x, y);
    return text;
}

bool loadFont(sf::Font &font)
{
    static const std::array<std::string, 3> fontPaths = {{
        "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf",
        "/usr/share/fonts/truetype/liberation2/LiberationSans-Regular.ttf",
        "/usr/share/fonts/truetype/freefont/FreeSans.ttf"
    }};

    for (std::array<std::string, 3>::const_iterator it = fontPaths.begin(); it != fontPaths.end(); ++it) {
        if (font.loadFromFile(*it)) {
            return true;
        }
    }
    return false;
}

std::string formatDouble(double value, int precision)
{
    std::ostringstream stream;
    stream << std::fixed << std::setprecision(precision) << value;
    return stream.str();
}

double averageMoveTime(const Player *player)
{
    const std::vector<double> &times = player->getMoveTimes();
    if (times.empty()) {
        return -1.0;
    }

    double total = 0.0;
    for (std::size_t index = 0; index < times.size(); ++index) {
        total += times[index];
    }
    return total / static_cast<double>(times.size());
}

double averageExploredNodes(const AI_player *player)
{
    const std::vector<int> &nodes = player->getExploredNodes();
    if (nodes.empty()) {
        return -1.0;
    }

    int total = 0;
    for (std::size_t index = 0; index < nodes.size(); ++index) {
        total += nodes[index];
    }
    return static_cast<double>(total) / static_cast<double>(nodes.size());
}

std::string modeLabel(int mode)
{
    switch (mode) {
    case 1:
        return "Human vs Human";
    case 2:
        return "Human vs Computer";
    case 3:
        return "Computer vs Human";
    case 4:
        return "Computer vs Computer";
    default:
        return "Unknown mode";
    }
}

class GuiHumanPlayer : public Player
{
public:
    GuiHumanPlayer(Connect4 &board, char token) : Player(board, token) {}

    virtual void makeaMove(int, int) override {}

    bool makeGuiMove(int column)
    {
        std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
        if (!mConnectBoard.placeToken(mToken, column)) {
            return false;
        }
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        std::chrono::duration<double, std::milli> elapsed = end - start;
        mMoveTimes.push_back(elapsed.count());
        return true;
    }
};

struct GameSession {
    Connect4 game;
    Player *players[2];
    bool aiPlayers[2];
    int turn;
    int mode;
    int depth;
    bool pruning;
    bool finished;
    std::string statusMessage;
    std::string resultMessage;

    GameSession() : players{NULL, NULL}, aiPlayers{false, false}, turn(0), mode(1), depth(10), pruning(false), finished(false)
    {
        statusMessage = "Setup: choose mode and options, then click Start.";
        resultMessage.clear();
    }

    ~GameSession()
    {
        clearPlayers();
    }

    void clearPlayers()
    {
        delete players[0];
        delete players[1];
        players[0] = NULL;
        players[1] = NULL;
        aiPlayers[0] = false;
        aiPlayers[1] = false;
    }

    bool hasActiveGame() const
    {
        return players[0] != NULL && players[1] != NULL;
    }

    void stop()
    {
        clearPlayers();
        game = Connect4();
        turn = 0;
        finished = false;
        resultMessage.clear();
        statusMessage = "Game stopped. Choose mode and options, then click Start.";
    }

    void updateTurnStatus()
    {
        if (!hasActiveGame()) {
            statusMessage = "Setup: choose mode and options, then click Start.";
            return;
        }
        statusMessage = currentPlayerIsAI() ? "AI is thinking..." : "Your turn";
    }

    void start(int selectedMode, int selectedDepth, bool usePruning)
    {
        clearPlayers();
        game = Connect4();
        mode = selectedMode;
        depth = selectedDepth;
        pruning = usePruning;
        turn = 0;
        finished = false;
        resultMessage.clear();

        switch (mode) {
        case 1:
            players[0] = new GuiHumanPlayer(game, 'X');
            players[1] = new GuiHumanPlayer(game, 'O');
            aiPlayers[0] = false;
            aiPlayers[1] = false;
            break;
        case 2:
            players[0] = new GuiHumanPlayer(game, 'X');
            players[1] = new AI_player(game, 'O', 'X', depth, pruning);
            aiPlayers[0] = false;
            aiPlayers[1] = true;
            break;
        case 3:
            players[0] = new AI_player(game, 'X', 'O', depth, pruning);
            players[1] = new GuiHumanPlayer(game, 'O');
            aiPlayers[0] = true;
            aiPlayers[1] = false;
            break;
        case 4:
            players[0] = new AI_player(game, 'X', 'O', depth, pruning);
            players[1] = new AI_player(game, 'O', 'X', depth, pruning);
            aiPlayers[0] = true;
            aiPlayers[1] = true;
            break;
        default:
            players[0] = new GuiHumanPlayer(game, 'X');
            players[1] = new GuiHumanPlayer(game, 'O');
            aiPlayers[0] = false;
            aiPlayers[1] = false;
            mode = 1;
            break;
        }

        updateTurnStatus();
    }

    bool currentPlayerIsAI() const
    {
        if (!hasActiveGame()) {
            return false;
        }
        return aiPlayers[turn];
    }

    Player *currentPlayer() const
    {
        if (!hasActiveGame()) {
            return NULL;
        }
        return players[turn];
    }

    void finishTurn()
    {
        const char token = players[turn]->getToken();
        if (game.isWin(token)) {
            finished = true;
            resultMessage = token == 'X' ? "Red player won!" : "Yellow player won!";
            statusMessage = "Press R to restart or click a mode to begin again.";
            return;
        }

        if (game.isFull()) {
            finished = true;
            resultMessage = "It is a tie!";
            statusMessage = "Press R to restart or click a mode to begin again.";
            return;
        }

        turn = (turn + 1) % 2;
        updateTurnStatus();
    }

    bool makeHumanMove(int column)
    {
        if (finished || currentPlayerIsAI() || !game.isColumnAvailable(column)) {
            return false;
        }

        GuiHumanPlayer *humanPlayer = static_cast<GuiHumanPlayer *>(players[turn]);
        if (!humanPlayer->makeGuiMove(column)) {
            return false;
        }

        finishTurn();
        return true;
    }

    void makeAIMove()
    {
        if (finished || !currentPlayerIsAI()) {
            return;
        }

        players[turn]->makeaMove(0, NUM_COL - 1);
        finishTurn();
    }

    std::vector<std::string> buildStats() const
    {
        std::vector<std::string> lines;
        if (!hasActiveGame()) {
            return lines;
        }
        lines.push_back(std::string("Red player avg move: ")
            + (averageMoveTime(players[0]) < 0.0 ? std::string("n/a") : formatDouble(averageMoveTime(players[0]), 2) + " ms"));
        lines.push_back(std::string("Yellow player avg move: ")
            + (averageMoveTime(players[1]) < 0.0 ? std::string("n/a") : formatDouble(averageMoveTime(players[1]), 2) + " ms"));

        if (aiPlayers[0]) {
            const AI_player *aiPlayer = static_cast<const AI_player *>(players[0]);
            lines.push_back(std::string("AI (red) avg nodes: ")
                + (averageExploredNodes(aiPlayer) < 0.0 ? std::string("n/a") : formatDouble(averageExploredNodes(aiPlayer), 1)));
        }
        if (aiPlayers[1]) {
            const AI_player *aiPlayer = static_cast<const AI_player *>(players[1]);
            lines.push_back(std::string("AI (yellow) avg nodes: ")
                + (averageExploredNodes(aiPlayer) < 0.0 ? std::string("n/a") : formatDouble(averageExploredNodes(aiPlayer), 1)));
        }

        return lines;
    }
};

void drawButton(sf::RenderWindow &window, const sf::Font &font, const Button &button,
    bool active, bool accent, bool enabled)
{
    sf::RectangleShape rect(sf::Vector2f(button.bounds.width, button.bounds.height));
    rect.setPosition(button.bounds.left, button.bounds.top);
    rect.setFillColor(enabled ? (active ? BUTTON_ACTIVE : (accent ? BUTTON_SOFT : BUTTON_IDLE)) : BUTTON_DISABLED);
    rect.setOutlineThickness(2.f);
    rect.setOutlineColor(enabled ? (active ? TEXT_LIGHT : PANEL) : sf::Color(130, 135, 140));
    window.draw(rect);

    sf::Text text = makeText(font, button.label, 17,
        enabled ? (active || !accent ? TEXT_LIGHT : TEXT_DARK) : sf::Color(95, 99, 104),
        button.bounds.left + 14.f, button.bounds.top + 10.f);
    window.draw(text);
}

} // namespace

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Connect 4 GUI", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);

    sf::Font font;
    if (!loadFont(font)) {
        std::cerr << "Unable to load a system font for the GUI. Install DejaVu Sans or Liberation Sans." << std::endl;
        return 1;
    }

    GameSession session;
    sf::Clock aiClock;
    bool aiThinking = false;
    std::future<void> aiFuture;
    bool gameStarted = false;

    int selectedMode = 1;
    int selectedDepth = 6;
    bool selectedPruning = false;

    std::array<std::array<char, NUM_COL>, NUM_ROW> cachedBoard = session.game.getBoard();
    std::vector<std::string> cachedStats = session.buildStats();
    std::string cachedResult = session.resultMessage;
    std::string cachedStatus = session.statusMessage;
    bool cachedFinished = session.finished;
    bool cachedCurrentIsAI = session.currentPlayerIsAI();
    int cachedMode = selectedMode;
    int cachedDepth = selectedDepth;
    bool cachedPruning = selectedPruning;

    const auto refreshCache = [&]() {
        cachedBoard = session.game.getBoard();
        cachedStats = session.buildStats();
        cachedResult = session.resultMessage;
        cachedStatus = session.statusMessage;
        cachedFinished = session.finished;
        cachedCurrentIsAI = gameStarted && session.currentPlayerIsAI();
        cachedMode = selectedMode;
        cachedDepth = selectedDepth;
        cachedPruning = selectedPruning;
    };

    const std::array<Button, 4> modeButtons = {{
        {sf::FloatRect(SIDEBAR_LEFT, 110.f, BUTTON_WIDTH, BUTTON_HEIGHT), "Human vs Human"},
        {sf::FloatRect(SIDEBAR_LEFT, 164.f, BUTTON_WIDTH, BUTTON_HEIGHT), "Human vs Computer"},
        {sf::FloatRect(SIDEBAR_LEFT, 218.f, BUTTON_WIDTH, BUTTON_HEIGHT), "Computer vs Human"},
        {sf::FloatRect(SIDEBAR_LEFT, 272.f, BUTTON_WIDTH, BUTTON_HEIGHT), "Computer vs Computer"}
    }};
    const Button depthDown = {sf::FloatRect(SIDEBAR_LEFT, 360.f, 58.f, 42.f), " -"};
    const Button depthUp = {sf::FloatRect(SIDEBAR_LEFT + 204.f, 360.f, 58.f, 42.f), " +"};
    const Button pruningButton = {sf::FloatRect(SIDEBAR_LEFT, 430.f, BUTTON_WIDTH, BUTTON_HEIGHT), "Toggle alpha-beta pruning"};
    const Button startButton = {sf::FloatRect(SIDEBAR_LEFT, 490.f, 156.f, BUTTON_HEIGHT), "   Start game"};
    const Button stopButton = {sf::FloatRect(SIDEBAR_LEFT + 169.f, 490.f, 156.f, BUTTON_HEIGHT), "  Restart game"};
    const sf::FloatRect boardRect(BOARD_LEFT, BOARD_TOP, NUM_COL * CELL_SIZE, NUM_ROW * CELL_SIZE);

    refreshCache();

    while (window.isOpen()) {
        if (aiThinking && aiFuture.valid()
            && aiFuture.wait_for(std::chrono::milliseconds(0)) == std::future_status::ready) {
            aiFuture.get();
            aiThinking = false;
            refreshCache();
        }

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                }
                if (event.key.code == sf::Keyboard::R && gameStarted && !aiThinking) {
                    session.start(selectedMode, selectedDepth, selectedPruning);
                    aiClock.restart();
                    refreshCache();
                }
            }

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                const sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                const bool setupEditable = !gameStarted && !aiThinking;
                const bool aiOptionsEnabled = setupEditable && cachedMode != 1;

                for (std::size_t index = 0; index < modeButtons.size(); ++index) {
                    if (setupEditable && modeButtons[index].bounds.contains(mouse)) {
                        selectedMode = static_cast<int>(index) + 1;
                        refreshCache();
                    }
                }

                if (aiOptionsEnabled && depthDown.bounds.contains(mouse)) {
                    selectedDepth = selectedDepth > 1 ? selectedDepth - 1 : 1;
                    refreshCache();
                }
                if (aiOptionsEnabled && depthUp.bounds.contains(mouse)) {
                    selectedDepth = selectedDepth < 20 ? selectedDepth + 1 : 20;
                    refreshCache();
                }
                if (aiOptionsEnabled && pruningButton.bounds.contains(mouse)) {
                    selectedPruning = !selectedPruning;
                    refreshCache();
                }

                if (!aiThinking && !gameStarted && startButton.bounds.contains(mouse)) {
                    session.start(selectedMode, selectedDepth, selectedPruning);
                    gameStarted = true;
                    aiClock.restart();
                    refreshCache();
                }

                if (!aiThinking && gameStarted && stopButton.bounds.contains(mouse)) {
                    session.stop();
                    gameStarted = false;
                    refreshCache();
                }

                if (gameStarted && !aiThinking && !session.finished && !session.currentPlayerIsAI() && boardRect.contains(mouse)) {
                    const int column = static_cast<int>((mouse.x - BOARD_LEFT) / CELL_SIZE);
                    if (column >= 0 && column < NUM_COL) {
                        session.makeHumanMove(column);
                        aiClock.restart();
                        refreshCache();
                    }
                }
            }
        }

        if (gameStarted && !aiThinking && !session.finished && session.currentPlayerIsAI()
            && aiClock.getElapsedTime().asSeconds() >= AI_MOVE_DELAY_SECONDS) {
            aiThinking = true;
            aiFuture = std::async(std::launch::async, [&session]() {
                session.makeAIMove();
            });
            aiClock.restart();
        }

        window.clear(BACKGROUND);

        sf::RectangleShape sidebar(sf::Vector2f(345.f, WINDOW_HEIGHT - 30.f));
        sidebar.setPosition(SIDEBAR_LEFT - 12.f, 15.f);
        sidebar.setFillColor(PANEL_LIGHT);
        sidebar.setOutlineThickness(3.f);
        sidebar.setOutlineColor(PANEL);
        window.draw(sidebar);

        sf::Text title = makeText(font, "Connect 4", 32, TEXT_DARK, SIDEBAR_LEFT+60, 40.f);
        window.draw(title);
        sf::Text subtitle = makeText(font, "Choose mode below", 16, PANEL, SIDEBAR_LEFT+60, 75.f);
        window.draw(subtitle);

        for (std::size_t index = 0; index < modeButtons.size(); ++index) {
            drawButton(window, font, modeButtons[index], cachedMode == static_cast<int>(index) + 1, false, !gameStarted && !aiThinking);
        }

        const bool aiOptionsEnabled = !gameStarted && cachedMode != 1;

        sf::Text depthLabel = makeText(font, "Level(AI depth)", 20,
            aiOptionsEnabled ? TEXT_DARK : sf::Color(125, 130, 136), SIDEBAR_LEFT, 332.f);
        window.draw(depthLabel);
        drawButton(window, font, depthDown, false, false, aiOptionsEnabled && !aiThinking);
        drawButton(window, font, depthUp, false, false, aiOptionsEnabled && !aiThinking);

        sf::RectangleShape depthValue(sf::Vector2f(136.f, 42.f));
        depthValue.setPosition(SIDEBAR_LEFT + 64.f, 360.f);
        depthValue.setFillColor(aiOptionsEnabled ? sf::Color::White : sf::Color(225, 228, 232));
        depthValue.setOutlineThickness(2.f);
        depthValue.setOutlineColor(aiOptionsEnabled ? PANEL : sf::Color(130, 135, 140));
        window.draw(depthValue);
        sf::Text depthText = makeText(font, formatDouble(static_cast<double>(cachedDepth), 0), 22,
            aiOptionsEnabled ? TEXT_DARK : sf::Color(125, 130, 136), SIDEBAR_LEFT + 124.f, 368.f);
        window.draw(depthText);

        drawButton(window, font, pruningButton, cachedPruning, true, aiOptionsEnabled && !aiThinking);

        drawButton(window, font, startButton, false, true, !gameStarted && !aiThinking);
        drawButton(window, font, stopButton, false, false, gameStarted && !aiThinking);

        const std::string topPrompt = !gameStarted
            ? "Choose mode and parameters, then click Start game"
            : (cachedFinished
                ? cachedStatus
                : (aiThinking || cachedCurrentIsAI ? "AI is thinking..." : "Your turn"));
        sf::Text turnText = makeText(font, topPrompt, 19, TEXT_DARK, BOARD_LEFT, 30.f);
        window.draw(turnText);

        sf::Text hotkeysText = makeText(font, "R: restart active game   ESC: close", 14, PANEL, SIDEBAR_LEFT, 582.f);
        window.draw(hotkeysText);

        sf::Text disabledHint = makeText(font,
            (cachedMode == 1) ? "AI settings disabled in Human vs Human" : "", 14,
            sf::Color(120, 125, 130), SIDEBAR_LEFT, 604.f);
        window.draw(disabledHint);

        if (!cachedResult.empty()) {
            const sf::Color winColor = cachedResult.find("Red") == 0 ? TOKEN_X
                : (cachedResult.find("Yellow") == 0 ? TOKEN_O : BUTTON_ACTIVE);
            sf::Text result = makeText(font, cachedResult, 22, winColor, BOARD_LEFT, BOARD_TOP + NUM_ROW * CELL_SIZE + 44.f);
            window.draw(result);
        }

        for (std::size_t index = 0; index < cachedStats.size(); ++index) {
            sf::Text stat = makeText(font, cachedStats[index], 15, TEXT_DARK, SIDEBAR_LEFT, 650.f + 20.f * static_cast<float>(index));
            window.draw(stat);
        }

        sf::Text footer = makeText(font, "Click \"Restart game\" to start over.", 14, PANEL,
            BOARD_LEFT, 700.f);
        window.draw(footer);

        sf::Text modeText = makeText(font, std::string("Current mode: ") + modeLabel(cachedMode), 18,
            TEXT_DARK, BOARD_LEFT, BOARD_TOP + NUM_ROW * CELL_SIZE + 14.f);
        window.draw(modeText);

        sf::RectangleShape boardBackground(sf::Vector2f(NUM_COL * CELL_SIZE, NUM_ROW * CELL_SIZE));
        boardBackground.setPosition(BOARD_LEFT, BOARD_TOP);
        boardBackground.setFillColor(PANEL);
        boardBackground.setOutlineThickness(4.f);
        boardBackground.setOutlineColor(TEXT_DARK);
        window.draw(boardBackground);

        const sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        int hoverColumn = -1;
        if (gameStarted && !aiThinking && !cachedFinished && !cachedCurrentIsAI && boardRect.contains(mouse)) {
            hoverColumn = static_cast<int>((mouse.x - BOARD_LEFT) / CELL_SIZE);
        }

        for (int row = 0; row < NUM_ROW; ++row) {
            for (int column = 0; column < NUM_COL; ++column) {
                sf::CircleShape slot(DISC_RADIUS);
                slot.setPosition(BOARD_LEFT + column * CELL_SIZE + 10.f, BOARD_TOP + row * CELL_SIZE + 10.f);
                slot.setFillColor(EMPTY_SLOT);

                if (gameStarted && hoverColumn == column && !aiThinking && session.game.isColumnAvailable(column)) {
                    slot.setOutlineThickness(3.f);
                    const Player *player = session.currentPlayer();
                    slot.setOutlineColor((player && player->getToken() == 'X') ? TOKEN_X : TOKEN_O);
                }

                if (cachedBoard[row][column] == 'X') {
                    slot.setFillColor(TOKEN_X);
                    slot.setOutlineThickness(0.f);
                } else if (cachedBoard[row][column] == 'O') {
                    slot.setFillColor(TOKEN_O);
                    slot.setOutlineThickness(0.f);
                }

                window.draw(slot);
            }
        }

        for (int column = 0; column < NUM_COL; ++column) {
            sf::Text number = makeText(font, formatDouble(static_cast<double>(column + 1), 0), 18, TEXT_DARK,
                BOARD_LEFT + column * CELL_SIZE + 35.f, BOARD_TOP - 30.f);
            window.draw(number);
        }

        window.display();
    }

    return 0;
}
