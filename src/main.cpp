#include <SQLiteCpp/SQLiteCpp.h>
#include "car_dao.h"
#include <iostream>

int main() {
    DatabasePtr db = std::make_shared<SQLite::Database>(
        "test.db",
        SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE
    );
    CarDao car_dao(db);

    Car car1("Toyota", "Camry", 2020);
    Car car2("Honda", "Accord", 2019);

    car_dao.insertCar(car1);
    car_dao.insertCar(car2);

    {
        auto cars = car_dao.getCars();
        for (const auto& car : cars) {
            std::cout << car << std::endl;
        }

        int64_t count = car_dao.getCount();
        std::cout << "count: " << count << std::endl;
    }

    std::cout << "============================================" << std::endl;

    {
        auto cars = car_dao.getCars("make = 'Toyota'");
        for (const auto& car : cars) {
            std::cout << car << std::endl;
        }

        int64_t count = car_dao.getCount("make = 'Toyota'");
        std::cout << "count: " << count << std::endl;
    }

    {
        Car car3("VW", "Polo", 2021, 2);
        car_dao.updateCarById(car3);
    }

    // car_dao.deleteItems();
    // car_dao.deleteItems("make = 'Toyota'");

    return 0;
}