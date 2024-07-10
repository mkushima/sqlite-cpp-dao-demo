#include "dao_base.h"

DaoBase::DaoBase(DatabasePtr db) 
    : m_db(db)
{

}

// ----------------------------------------------------------------------------

void
DaoBase::deleteItems(const std::string& condition)
{
    std::string query_str("DELETE FROM " + m_table_name);
    updateQueryWithCondtion(query_str, condition);

    m_db->exec(query_str);
}

// ----------------------------------------------------------------------------

int64_t
DaoBase::getCount(const std::string& condition)
{
    int64_t count = 0;
    std::string query_str = "SELECT COUNT(*) FROM " + m_table_name;
    updateQueryWithCondtion(query_str, condition);

    SQLite::Statement query(*m_db, query_str);

    if (query.executeStep()) {
        count = query.getColumn(0).getInt64();
    }

    return count;
}

// ----------------------------------------------------------------------------

void
DaoBase::updateQueryWithCondtion(
    std::string& query_str,
    const std::string& condition
)
{
    if ( condition != "" )
    {
        query_str += " WHERE " + condition;
    }
}

// ----------------------------------------------------------------------------
