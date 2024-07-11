#!/usr/bin/env python3
"""
Create DAO files from a CSV file specifying attributes

This script will generate the header and source files based on the provided CSV file
and the Jinja2 templates.

CSV File Format Explanation:
    The CSV file should contain three columns for each attribute of the class.
    - Attribute Name: The name of the attribute as it will appear in your class
        and the corresponding SQL table.
    - SQL Type: This is the SQL data type for the attribute.
        Allowed types are INTEGER, REAL, and TEXT.
    - C++ Type: This is the C++ data type for the attribute.
        Allowed types are std::string, uint32_t, int32_t, int64_t, and double.

Here is an example of a CSV file named `car.csv`:

```
make,TEXT,std::string
model,TEXT,std::string
year,INTEGER,int32_t
```

Usage:
    generate_files.py -i path/to/your/csvfile.csv
"""
import argparse

import csv
from pathlib import Path

from jinja2 import Environment, FileSystemLoader

ALLOWED_CPP_TYPES = ['std::string', 'uint32_t', 'int32_t', 'int64_t', 'double']
ALLOWED_SQL_TYPES = ['INTEGER', 'REAL', 'TEXT']

# TODO: 'cpp_type' needs to support char*
# TODO: 'sql_type' needs to support BLOB

def get_args():
    """Parse command line arguments."""

    parser = argparse.ArgumentParser(
        prog='dao_creator',
        description='Create DAO files from a CSV file specifying attributes.\n\n'
                    'CSV File Format:\n'
                    'The CSV file should contain three columns:\n'
                    '1. Attribute Name: The name of the attribute.\n'
                    '2. SQL Type: The SQL data type (INTEGER, REAL, TEXT).\n'
                    '3. C++ Type: The C++ data type (std::string, uint32_t, int32_t, int64_t, double).\n\n'
                    'Example CSV File:\n'
                    'make,TEXT,std::string\n'
                    'model,TEXT,std::string\n'
                    'year,INTEGER,int32_t\n',
        formatter_class=argparse.RawTextHelpFormatter
    )

    parser.add_argument(
        "-i", "--input",
        help="Path to a csv file to create DAO files",
        required=True,
        type=str
    )

    return parser.parse_args()

def parse_csv(file_path):
    """Parse the input CSV file to extract attribute information.

    Args:
        file_path (str): Path to the CSV file.

    Returns:
        list: List of dictionaries containing attribute information.

    Raises:
        ValueError: If the CSV file contains invalid rows or unsupported types.
    """
    attributes = []

    with open(file_path, mode='r') as csv_file:
        csv_reader = csv.reader(csv_file)

        for row in csv_reader:
            if len(row) != 3:
                raise ValueError(f"Invalid row: {row}")

            attribute_name, sql_type, cpp_type = row

            if cpp_type not in ALLOWED_CPP_TYPES:
                raise ValueError(f"Invalid C++ type '{cpp_type}' in row: {row}")

            if sql_type not in ALLOWED_SQL_TYPES:
                raise ValueError(f"Invalid SQL type '{sql_type}' in row: {row}")

            attributes.append({
                'name': attribute_name,
                'sql_type': sql_type,
                'cpp_type': cpp_type
            })
    
    return attributes

def generate_file(template_name, output_path, context):
    """Generate a file from a Jinja2 template.

    Args:
        template_name (str): Name of the Jinja2 template file.
        output_path (str): Path to the output file.
        context (dict): Context dictionary for rendering the template.
    """
    env = Environment(loader=FileSystemLoader('.'), trim_blocks=True, lstrip_blocks=True)
    template = env.get_template(template_name)

    output = template.render(context)

    with open(output_path, 'w') as f:
        f.write(output)


def main():
    """Main function to parse arguments, read the CSV file, and generate the files."""
    args = get_args()
    input_file = args.input

    # class_file = Path(input_file).stem + '.h'
    class_name = Path(input_file).stem.title()

    attributes = parse_csv(input_file)

    context = {
        'class_name': class_name,
        'attributes': attributes
    }

    generate_file('class_template.jinja2', f'{class_name.lower()}.h', context)
    generate_file('class_dao_h_template.jinja2', f'{class_name.lower()}_dao.h', context)
    generate_file('class_dao_cpp_template.jinja2', f'{class_name.lower()}_dao.cpp', context)

if __name__ == "__main__":
    main()
