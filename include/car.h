#ifndef CAR_H
#define CAR_H

#include <iostream>
#include <string>

class Car {
public:
    Car(const std::string& make, const std::string& model, const uint32_t& year, int64_t id = 0)
        : m_make(make), m_model(model), m_year(year), m_id(id) {}

    inline std::string make() const {
        return m_make;
    }

    inline std::string model() const {
        return m_model;
    }

    inline uint32_t year() const {
        return m_year;
    }

    inline int64_t id() const {
        return m_id;
    }

    friend std::ostream& operator<<(std::ostream& os, const Car& obj)
    {
        os << "Car(id: " << obj.m_id
            << ", make: " << obj.m_make
            << ", model: " << obj.m_model
            << ", year: " << obj.m_year
            << ")";
        return os;
    }

private:
    std::string m_make;
    std::string m_model;
    uint32_t m_year;
    int64_t m_id;
};

#endif // CAR_H
