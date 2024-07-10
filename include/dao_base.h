#ifndef DAO_BASE_H
#define DAO_BASE_H

#include <vector>

#include <SQLiteCpp/SQLiteCpp.h>

// Type alias for shared pointer to SQLite::Database
using DatabasePtr = std::shared_ptr<SQLite::Database>;

class DaoBase {
public:
    explicit DaoBase(DatabasePtr db);

    virtual ~DaoBase() = default;

    virtual void createTable() = 0;

    void deleteItems(const std::string& condition = "");

    int64_t getCount(const std::string& condition = "");

protected:
    void updateQueryWithCondtion(
        std::string& query_str,
        const std::string& condition
    );

    DatabasePtr m_db;
    std::string m_table_name;
};

#endif // DAO_BASE_H
