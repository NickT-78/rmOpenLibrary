#include <QtTest/QtTest>
#include "domain/ISearchRepository.hpp"

using namespace rmol::domain;

class TestSearchQuery : public QObject {
    Q_OBJECT
private slots:
    void defaultSortIsRelevance() {
        SearchQuery q;
        QCOMPARE(q.sort, SortKey::Relevance);
    }
    void filtersAreOptionalByDefault() {
        SearchQuery q;
        QVERIFY(!q.filters.ebookAccessOnly.has_value());
    }
};

QTEST_MAIN(TestSearchQuery)
#include "test_searchquery.moc"
