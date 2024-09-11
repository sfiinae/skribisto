#pragma once

#include <QList>

class Root {
public:
    // Default constructor
    Root() = default;

    // Constructor with all members
    Root(int id, int book, const QList<int>& recent_books)
        : id(id), book(book), recent_books(recent_books) {}

    // Getters
    int getId() const { return id; }
    int getBook() const { return book; }
    const QList<int>& getRecentBooks() const { return recent_books; }

    // Setters
    void setId(int id) { this->id = id; }
    void setBook(int book) { this->book = book; }
    void setRecentBooks(const QList<int>& recent_books) { this->recent_books = recent_books; }

private:
    int id{};
    int book{};
    QList<int> recent_books;
};