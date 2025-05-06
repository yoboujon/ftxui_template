#ifndef HEADER_LOGGER_FTXUI
#define HEADER_LOGGER_FTXUI

#include <string>
#include <vector>
#include <ostream>
#include <cstdint>

enum class LoggerType : uint8_t
{
    _UNDEFINED,
    PRINT,
    COMMAND,
    // You can add more here
    _COUNT
};

struct LoggerData
{
    std::string str;
    uint64_t epoch;
    LoggerType type;
};

class Logger
{
public:
    static Logger &GetInstance()
    {
        static Logger instance;
        return instance;
    }
    void set_max_size(int size);
    void push_back(std::string str, LoggerType type = LoggerType::_UNDEFINED);
    const std::vector<LoggerData> &get_buffer(void) noexcept;

private:
    Logger();
    ~Logger();
    void update_view();

    size_t _maxSize;
    std::vector<LoggerData> _buffer;
    std::vector<LoggerData> _view;
};

#endif // HEADER_LOGGER_FTXUI
