# SQLite Example with DAO Pattern

This repository provides an example of using the Data Access Object (DAO) pattern to interact with an SQLite database in C++. It includes a Python script to generate DAO files based on a CSV file specifying the database schema.

This project uses [SQLiteCpp](https://github.com/SRombauts/SQLiteCpp), which is a C++ wrapper around the SQLite library, providing a convenient way to interact with SQLite databases in C++ applications.

## Features

- **DAO Pattern**: Separates the data access logic from the business logic.
- **SQLite Integration**: Uses SQLite for database operations.
- **Code Generation**: Python script to generate class and DAO files from a CSV file.

## Requirements

### C++

- C++11 or higher
- SQLite3 library
- CMake

### Python

- Python 3.10 or higher
- Jinja2 library

## Installation

### Clone the Repository

```sh
git clone https://github.com/mkushima/sqlite-cpp-dao-demo
cd sqlite-cpp-dao-demo
```

### Initialize Submodules

```sh
git submodule update --init --recursive
```

### Install Dependencies

#### C++
You need to install the SQLite3 libraries.

```sh
sudo apt-get install libsqlite3-dev
```

#### Python
You can install the required Python library using pip:

```sh
python3.10 -m venv venv
source venv/bin/activate
python -m pip install jinja2
```

## Usage

### Generate DAO Files
The Python script dao_creator.py reads a CSV file specifying the database schema and generates the corresponding class and DAO files.

#### CSV File Format
The CSV file should contain three columns:

- Attribute Name: The name of the attribute.
- SQL Type: The SQL data type (INTEGER, REAL, TEXT).
- C++ Type: The C++ data type (std::string, uint32_t, int32_t, int64_t, double).

Example car.csv:
```
make,TEXT,std::string
model,TEXT,std::string
year,INTEGER,int32_t
```

#### Run the Script
```sh
python dao_creator.py -i path/to/your/car.csv
```

### Build the Project
Use CMake to build the project:

```sh
mkdir build
cd build
cmake ..
make -j5
```
