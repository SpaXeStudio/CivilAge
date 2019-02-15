#include "logger.h"

namespace civilage { namespace log {

bool LoggingTarget::WriteMessage(const std::string &)
{
    return true;
}


bool stdoutLogger::WriteMessage(const std::string &body)
{
    std::cerr << body << std::endl;

    return std::cout.good();
}


FileLogger::FileLogger(const char *filename)
{
    file_.open(filename, std::ios_base::app);
}

FileLogger::~FileLogger()
{
    file_.close();
}

bool FileLogger::WriteMessage(const std::string &body)
{
    if (!file_.is_open()) {
        return false;
    }

    file_ << body << std::endl;

    return file_.good();
}

void Logger::Init() {
    if (!targets_.empty()) {
        qDebug() << "Deleting" << targets_.size() << "logging targets";
    }

    targets_ = std::list<std::shared_ptr<LoggingTarget>>();

    qInstallMessageHandler(Logger::MessageHandler);
}

void Logger::AddTarget(const std::shared_ptr<LoggingTarget> &t)
{
    targets_.push_back(t);
}

void Logger::MessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    // may want to check if targets_ is empty before continuing

    std::time_t t = std::time(nullptr);
    std::tm *now = std::localtime(&t);
    if (now == nullptr) {
        std::tm ttn = std::tm();
        ttn.tm_sec  = 0;
        ttn.tm_min  = 0;
        ttn.tm_hour = 0;

        now = &ttn;
    }

    const char *prefix;

    switch (type) {
    case QtMsgType::QtDebugMsg:
        prefix = "DEB";
        break;
    case QtMsgType::QtInfoMsg:
        prefix = "INF";
        break;
    case QtMsgType::QtWarningMsg:
        prefix = "WRN";
        break;
    case QtMsgType::QtCriticalMsg:
        prefix = "CRI";
        break;
    case QtMsgType::QtFatalMsg:
        prefix = "FAT";
        break;
    }

    std::string body = msg.toStdString();
    std::size_t len;

    char *message;

    if (context.category != nullptr && strcmp(context.category, "default") != 0) {
        len =
                8                           // time format
                + 6                         // additional chars: "[ ]: \0"
                + 3                         // prefix
                + body.size()               // body
                + strlen(context.category); // category

        message = new char[len];
        snprintf(message, len, "[%02i:%02i:%02i %s]%s: %s",
                    now->tm_hour, now->tm_min, now->tm_sec, prefix, context.category, body.c_str()
        );
    } else {
        len =
                8              // time format
                + 4            // additional chars: "[ ]\0"
                + 3            // prefix
                + body.size(); // body

        message = new char[len];
        snprintf(message, len, "[%02i:%02i:%02i %s]%s",
                    now->tm_hour, now->tm_min, now->tm_sec, prefix, body.c_str()
        );
    }

    for (auto &target : targets_) {
        target->WriteMessage(message);
    }

    delete[] message;
}

std::list<std::shared_ptr<LoggingTarget>> Logger::targets_;

} // namespace logging
} // namespace civilage
