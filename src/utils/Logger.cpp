#include "Logger.h"

#include <iostream>
#include <ostream>
#include <string>

void Logger::log(string message) {
    log(message, this->level);
}

void Logger::log(string message, Level level) {
    if (level < this->level) {
        return;
    }
    cout << "[" << name << "] " << LEVEL_TO_COLOR(level) << LEVEL_TO_STRING(level) << RESET_COLOR << ": " << message << endl;
}

void Logger::debug(string message) {
    log(message, DEBUG);
}

void Logger::info(string message) {
    log(message, INFO);
}

void Logger::warn(string message) {
    log(message, WARN);
}

void Logger::error(string message) {
    log(message, ERROR);
}

void Logger::fatal(string message) {
    log(message, FATAL);
}

basic_ostream<char>& Logger::stream(Level level) {
    cout << "[" << name << "] " << LEVEL_TO_STRING(level) << ": ";
    return cout;
}
