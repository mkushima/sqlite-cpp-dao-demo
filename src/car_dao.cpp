#include "car_dao.h"

constexpr const char* TABLE_NAME = "car";

// ----------------------------------------------------------------------------

CarDao::CarDao(DatabasePtr db)
    : DaoBase(db)
{
    m_db = db;
    m_table_name = TABLE_NAME;
    createTable();
}

// ----------------------------------------------------------------------------

void
CarDao::createTable()
{
    std::string query_str =
        "CREATE TABLE IF NOT EXISTS " + m_table_name +
        " (id INTEGER PRIMARY KEY, "
        "make TEXT, "
        "model TEXT, "
        "year INTEGER)";

    m_db->exec(query_str);
}

// ----------------------------------------------------------------------------

void
CarDao::insertCar(const Car& car)
{
    SQLite::Statement query(
        *m_db,
        "INSERT INTO " + m_table_name +
        " (make, model, year) VALUES (:make, :model, :year)"
    );

    query.bind(":make", car.make());
    query.bind(":model", car.model());
    query.bind(":year", car.year());

    query.exec();
}

// ----------------------------------------------------------------------------

std::vector<Car>
CarDao::getCars(const std::string& condition)
{
    std::vector<Car> cars;
    std::string query_str = "SELECT id, make, model, year FROM " + m_table_name;
    updateQueryWithCondtion(query_str, condition);

    SQLite::Statement query(*m_db, query_str);

    while (query.executeStep())
    {
        int id = query.getColumn("id");
        std::string make = query.getColumn("make");
        std::string model = query.getColumn("model");
        int year = query.getColumn("year");
        cars.emplace_back(make, model, year, id);
    }

    return cars;
}

// ----------------------------------------------------------------------------

void
CarDao::updateCarById(const Car& car)
{
    SQLite::Statement query(
        *m_db, 
        "UPDATE " + m_table_name +
        " SET make = :make, model = :model, year = :year WHERE id = :id"
    );

    query.bind(":make", car.make());
    query.bind(":model", car.model());
    query.bind(":year", car.year());
    query.bind(":id", car.id());

    query.exec();
}

// ----------------------------------------------------------------------------
