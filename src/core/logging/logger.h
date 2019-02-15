#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <fstream>
#include <list>
#include <memory>
#include <ctime>

#include <QDebug>
#include <QString>

namespace civilage { namespace log {

// TODO: LoggableBuffer class

class LoggingTarget {
public:
    virtual ~LoggingTarget() { }

    virtual bool WriteMessage(const std::string &);
};

class stdoutLogger : public LoggingTarget {
public:
    bool WriteMessage(const std::string &body) override;
};

class FileLogger : public LoggingTarget {
public:
    FileLogger(const char *filename = "log.log");
    ~FileLogger() override;

    bool WriteMessage(const std::string &body) override;

private:
    std::ofstream file_;
};

// TODO: BufferLogger class

class Logger
{
public:
    static void Init();
    static void AddTarget(const std::shared_ptr<LoggingTarget> &t);

private:
    static void MessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg);

private:
    static std::list<std::shared_ptr<LoggingTarget>> targets_;
};

} // namespace log
} // namespace civilage

#endif // LOGGER_H
