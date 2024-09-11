#pragma once

#include <QString>
#include <QDateTime>

class Scene {
public:
    // Default constructor
    Scene() = default;

    // Constructor with all members
    Scene(int id, const QString& title, const QString& label, const QString& content, int word_count, const QDateTime& deadline, bool completed)
        : id(id), title(title), label(label), content(content), word_count(word_count), deadline(deadline), completed(completed) {}

    // Getters
    int getId() const { return id; }
    const QString& getTitle() const { return title; }
    const QString& getLabel() const { return label; }
    const QString& getContent() const { return content; }
    int getWordCount() const { return word_count; }
    const QDateTime& getDeadline() const { return deadline; }
    bool isCompleted() const { return completed; }

    // Setters
    void setId(int id) { this->id = id; }
    void setTitle(const QString& title) { this->title = title; }
    void setLabel(const QString& label) { this->label = label; }
    void setContent(const QString& content) { this->content = content; }
    void setWordCount(int word_count) { this->word_count = word_count; }
    void setDeadline(const QDateTime& deadline) { this->deadline = deadline; }
    void setCompleted(bool completed) { this->completed = completed; }

private:
    int id{};
    QString title;
    QString label;
    QString content;
    int word_count{};
    QDateTime deadline;
    bool completed{};
};