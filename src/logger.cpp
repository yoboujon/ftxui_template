#include "logger.h"
#include "ui.h"

#include <algorithm>
#include <chrono>

constexpr int MAX_SIZE = 99;

Logger::Logger()
    : _maxSize(MAX_SIZE), _buffer({})
{
}

Logger::~Logger()
{
}

void Logger::set_max_size(int size)
{
    if (size == _maxSize)
        return;
    _maxSize = size;
    update_view();
}

void Logger::push_back(std::string str, LoggerType type)
{
    const uint64_t now = static_cast<uint64_t>(std::chrono::system_clock::now().time_since_epoch() / std::chrono::milliseconds(1));
    _buffer.push_back({str, now, type});
    update_view();
    UserInterface::GetInstance().update();
}

void Logger::update_view()
{
    typename std::vector<LoggerData>::iterator itBegin = _buffer.begin();
    if (_buffer.size() >= _maxSize)
        itBegin = _buffer.end() - _maxSize;

    _view.clear();
    std::copy(itBegin, _buffer.end(), std::back_inserter(_view));
}

// Getters
const std::vector<LoggerData> &Logger::get_buffer(void) noexcept { return _view; }
