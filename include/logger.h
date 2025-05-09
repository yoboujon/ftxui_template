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
    // Add your own type of log here
    _COUNT
};

/**
 * @brief Stored as two vectors in the logger,
 * one that is a general vector, and the other that is shown on the screen.
 */
struct LoggerData
{
    std::string str;
    uint64_t epoch;
    LoggerType type;
};

/**
 * @brief 'Logger' is a general Logger that can be instanciated anywhere as a singleton.
 * It can have a maximum size for its buffer that can be changed on the go.
 * Each LoggerType can be gathered from each data which can lead to multiple ways to print out a log.
 */
class Logger
{
public:
    static Logger &GetInstance()
    {
        static Logger instance;
        return instance;
    }

    /**
     * @brief set the max size for the returned buffer by get_buffer().
     * If it goes beyond the actual stored buffer, it shows only this buffer.
     *
     * @param int the size of the wanted buffer
     */
    void set_max_size(int size);

    /**
     * @brief Adding a log to the buffer. you can add a logger type.
     * The epoch is automatically calculated here.
     *
     * @param std::string the string to put to the buffer
     * @param LoggerType the type of log (default: UNDEFINED)
     */
    void push_back(std::string str, LoggerType type = LoggerType::_UNDEFINED);

    /**
     * @brief Gather the buffer from the size set in set_max_size()
     *
     * @return std::vector<LoggerData>& reference of the data.
     */
    const std::vector<LoggerData> &get_buffer(void) noexcept;

private:
    Logger();
    ~Logger();

    /**
     * @brief Updating the _view buffer with the current size.
     */
    void update_view();

    size_t _maxSize;
    std::vector<LoggerData> _buffer;
    std::vector<LoggerData> _view;
};

#endif // HEADER_LOGGER_FTXUI
