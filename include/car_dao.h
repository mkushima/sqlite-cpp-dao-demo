#ifndef CAR_DAO_H
#define CAR_DAO_H

#include "dao_base.h"
#include "car.h"

class CarDao : public DaoBase {
public:
    explicit CarDao(DatabasePtr db);

    void createTable() override;
    void insertCar(const Car& car);
    std::vector<Car> getCars(const std::string& condition = "");
    void updateCarById(const Car& car);
};

#endif // CAR_DAO_H
