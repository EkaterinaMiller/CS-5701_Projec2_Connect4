#ifndef STATES_H
#define STATES_H
#include <iostream>
enum State {START, SETUP, GAME, RESULT};
enum Mode{UKN, HvsH, HvsA, AvsH, AvsA};
const std::string MODE[]{"MODE: choose one", "MODE: Human vs Human", "MODE: Human vs AI", "MODE: AI vs Human", "MODE: AI vs AI"};

#endif