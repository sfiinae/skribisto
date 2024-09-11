#pragma once

#include <QString>
#include <optional>

class Author {
public:
    // Default constructor
    Author() = default;

    // Constructor for non-optional members
    Author(int id, const QString& uuid, const QString& name)
        : id(id), uuid(uuid), name(name) {}

    // Getters
    int getId() const { return id; }
    const QString& getUuid() const { return uuid; }
    const QString& getName() const { return name; }

    // Setters
    void setId(int id) { this->id = id; }
    void setUuid(const QString& uuid) { this->uuid = uuid; }
    void setName(const QString& name) { this->name = name; }

private:
    int id{};
    QString uuid;
    QString name;
};