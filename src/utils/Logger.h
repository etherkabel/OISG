#include <ostream>
#include <string>

#define LEVEL_TO_STRING(e) \
    ((e) == Logger::DEBUG ? "DEBUG" : \
     (e) == Logger::INFO ?  "INFO " : \
     (e) == Logger::WARN ?  "WARN " : \
     (e) == Logger::ERROR ? "ERROR" : \
     (e) == Logger::FATAL ? "FATAL" : " UNK ")

#define LEVEL_TO_COLOR(e) \
    ((e) == Logger::INFO ?  "\e[0;32m" : \
     (e) == Logger::WARN ?  "\e[0;33m" : \
     (e) == Logger::ERROR ? "\e[0;31m" : \
     (e) == Logger::FATAL ? "\e[0;31m" : "")

#define RESET_COLOR "\e[0m"


using namespace std;

class Logger {
public:
    enum Level {
        DEBUG = 0,
        INFO,
        WARN,
        ERROR,
        FATAL
    };

    Logger(string name) : name(name), level(INFO) {}
    Logger(string name, Level level) : name(name), level(level) {}

    void log(string message);
    void log(string message, Level level);

    void debug(string message);
    void info(string message);
    void warn(string message);
    void error(string message);
    void fatal(string message);

    basic_ostream<char>& stream(Level level);

    void setLevel(Level level) { this->level = level; }
    Level getLevel() { return level; }

private:
    string name;
    Level level;
};
