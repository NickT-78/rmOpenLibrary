#pragma once
#include <QString>
#include <QStringList>
#include <optional>

namespace rmol::domain {

struct Book {
    QString workKey;          // e.g. "OL15626917W"
    QString title;
    QStringList authors;
    std::optional<int> firstPublishYear;
    QString coverId;
    bool ebookAccess = false; // from OpenLibrary "ebook_access" facet
};

} // namespace rmol::domain
