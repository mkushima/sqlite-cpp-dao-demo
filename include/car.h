#ifndef CAR_H
#define CAR_H

#include <iostream>
#include <string>

class Car {
public:
    Car(const std::string& make, const std::string& model, int year, int id = 0)
        : m_make(make), m_model(model), m_year(year), m_id(id) {}
    
    inline std::string make() const {
        return m_make;
    }

    inline std::string model() const {
        return m_model;
    }

    inline int year() const {
        return m_year;
    }

    inline int id() const {
        return m_id;
    }

    friend std::ostream& operator<<(std::ostream& os, const Car& car)
    {
        os << "Car(id: " << car.m_id
            << ", make: " << car.m_make
            << ", model: " << car.m_model
            << ", year: " << car.m_year
            << ")";
        return os;
    }

private:
    std::string m_make;
    std::string m_model;
    int m_year;
    int m_id;
};

#endif // CAR_H
