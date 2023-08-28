#include "author/author_dto.h"
#include "author/commands/create_author_command_handler.h"
#include "author/commands/remove_author_command_handler.h"
#include "author/queries/get_author_query_handler.h"
#include "automapper/automapper.h"
#include "dummy_author_repository.h"
#include "dummy_book_repository.h"
#include <QDate>
#include <QDateTime>
#include <QDebug>
#include <QHash>
#include <QList>
#include <QTime>
#include <QVariant>
#include <QtTest>

using namespace Application::Features::Author::Queries;
using namespace Application::Features::Author::Commands;
using namespace Contracts::DTO::Author;

class UseCases : public QObject
{
    Q_OBJECT

  public:
    UseCases();
    ~UseCases();

  public slots:

  private Q_SLOTS:

    void initTestCase();
    void cleanupTestCase();
    void init();
    void cleanup();

    // void createTag();
    void getAuthor();
    void addAuthor();
    void removeAuthor();

  private:
};

UseCases::UseCases()
{
}

UseCases::~UseCases()
{
}

void UseCases::initTestCase()
{
    AutoMapper::AutoMapper::registerMapping<Domain::Author, AuthorDTO>(true);
    AutoMapper::AutoMapper::registerMapping<CreateAuthorDTO, Domain::Author>();
}

void UseCases::cleanupTestCase()
{
}

void UseCases::init()
{
}

void UseCases::cleanup()
{
}

// ----------------------------------------------------------

void UseCases::getAuthor()
{
    DummyAuthorRepository *repository(new DummyAuthorRepository(this));

    QUuid uuid = QUuid::createUuid();
    Domain::Author author(1, uuid, QDateTime(), QDateTime(), "test");

    repository->fillGet(author);

    GetAuthorQueryHandler handler(repository);
    GetAuthorQuery request;
    request.id = 1;

    QPromise<Result<void>> progressPromise;
    Result<AuthorDTO> dtoResult = handler.handle(progressPromise, request);

    if (!dtoResult)
    {
        qDebug() << dtoResult.error().message() << dtoResult.error().data();
    }
    QVERIFY(dtoResult.isSuccess());

    QCOMPARE(dtoResult.value().id(), 1);
    QCOMPARE(dtoResult.value().name(), "test");
}

// ----------------------------------------------------------

// ----------------------------------------------------------

void UseCases::addAuthor()
{
    DummyAuthorRepository *repository(new DummyAuthorRepository(this));
    DummyBookRepository *ownerRepository(new DummyBookRepository(this));

    Domain::Book book(0, QUuid::createUuid(), QDateTime(), QDateTime(), "test", QList<Domain::Chapter>(),
                      Domain::Author());

    ownerRepository->fillGet(book);
    ownerRepository->fillAuthor(Domain::Author());

    // Create an AuthorDTO to add
    CreateAuthorDTO dto;

    dto.setName("new author");
    dto.setBookId(0);

    // prefill the dummy repo:
    auto author = AutoMapper::AutoMapper::map<CreateAuthorDTO, Domain::Author>(dto);
    author.setUuid(QUuid::createUuid());
    repository->fillAdd(author);
    repository->fillGetAll(QList<Domain::Author>() << author);

    Domain::Book book2(0, QUuid::createUuid(), QDateTime(), QDateTime(), "test", QList<Domain::Chapter>(), author);

    ownerRepository->fillUpdate(book2);

    // Invoke the CreateAuthorCommandHandler with the DTO
    CreateAuthorCommandHandler handler(repository, ownerRepository);
    CreateAuthorCommand command;
    command.req = dto;

    QPromise<Result<void>> progressPromise;
    Result<AuthorDTO> result = handler.handle(progressPromise, command);

    if (!result)
    {
        qDebug() << result.error().message() << result.error().data();
    }
    QVERIFY(result.isSuccess());
}

// ----------------------------------------------------------

void UseCases::removeAuthor()
{
    DummyAuthorRepository *repository(new DummyAuthorRepository(this));

    // Add an author to the repository
    AuthorDTO dto;

    dto.setId(1);
    dto.setUuid(QUuid::createUuid());
    dto.setName("test");
    auto author = AutoMapper::AutoMapper::map<AuthorDTO, Domain::Author>(dto);
    repository->fillRemove(author.id());
    repository->fillGet(author);

    // Remove the author
    RemoveAuthorCommandHandler handler(repository);
    RemoveAuthorCommand command;
    command.id = author.id();

    QPromise<Result<void>> progressPromise;
    Result<int> result = handler.handle(progressPromise, command);

    if (!result)
    {
        qDebug() << result.error().message() << result.error().data();
    }
    QVERIFY(result.isSuccess());
}

QTEST_MAIN(UseCases)

#include "tst_usecases.moc"
