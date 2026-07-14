#pragma once
#include <QString>
#include <QVector>
#include <functional>
#include "Book.hpp"

namespace rmol::domain {

enum class SortKey { Relevance, TitleAsc, AuthorAsc, YearDesc };

struct SearchFilters {
    std::optional<bool> ebookAccessOnly;
    std::optional<int> minYear;
    std::optional<int> maxYear;
};

struct SearchQuery {
    QString text;
    SortKey sort = SortKey::Relevance;
    SearchFilters filters;
    int page = 1;
};

// Port: implemented by data/OpenLibraryRepository. Domain never depends
// on QNetworkAccessManager/curl directly.
class ISearchRepository {
public:
    virtual ~ISearchRepository() = default;
    virtual void search(const SearchQuery& query,
                         std::function<void(QVector<Book>)> onSuccess,
                         std::function<void(QString /*error*/)> onError) = 0;
};

} // namespace rmol::domain
