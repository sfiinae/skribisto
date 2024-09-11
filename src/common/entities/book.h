#pragma once

#include <QString>
#include <QList>
#include <optional>

class Book {
public:
    // Default constructor
    Book() = default;

    // Constructor for non-optional members
    Book(int id, const QString& title)
        : id(id), title(title) {}

    // Constructor for all members
    Book(int id, const QString& title, const std::optional<QList<int>>& scenes)
        : id(id), title(title), scenes(scenes) {}

    // Getters
    int getId() const { return id; }
    const QString& getTitle() const { return title; }
    const std::optional<QList<int>>& getScenes() const { return scenes; }

    // Setters
    void setId(int id) { this->id = id; }
    void setTitle(const QString& title) { this->title = title; }
    void setScenes(const std::optional<QList<int>>& scenes) { this->scenes = scenes; }

private:
    int id{};
    QString title;
    std::optional<QList<int>> scenes;
};