# Austrian Data Generator

## Overview

The Austrian Data Generator is a C++ tool designed to generate realistic Austrian personal data for testing and development purposes. It creates CSV files containing randomly generated names, email addresses, birth dates, passwords, and Austrian phone numbers.

## Features

- Generates the following data:
  - Full names (using common Austrian names)
  - Email addresses (based on generated names)
  - Birth dates (in dd:mm:yyyy format)
  - Secure passwords (12 characters, including symbols and numbers)
  - Austrian phone numbers (without +43 prefix)
- Outputs data in CSV format for easy parsing and integration with other tools
- Customizable number of records to generate

## Requirements

- C++17 compatible compiler (e.g., GCC, Clang)
- Standard C++ libraries

## Compilation

To compile the Austrian Data Generator, use the following command:

```
g++ -std=c++17 austrian_data_generator.cpp -o austrian_data_generator
```

## Usage

1. Run the compiled program:
   ```
   ./austrian_data_generator
   ```

2. When prompted, enter the number of records you want to generate.

3. Enter the desired output filename (without the .csv extension).

4. The program will generate the data and save it to the specified CSV file.

## Output Format

The generated CSV file will have the following columns:

```
Name,Email,BirthDate,Password,Phone
```

Example row:
```
Anna Müller,anna.muller@example.com,15:7:1985,P@ssw0rd123!,06501234567
```

## Notes

- This tool is intended for testing and development purposes only. The generated data is not real and should not be used for any official or production purposes.
- The generated email addresses use a fictional domain (@example.com). Replace this with an appropriate domain if needed.
- Ensure proper security measures when handling the generated data, especially the passwords.
- The birth dates are randomly generated and may not accurately represent Austrian demographic data.

## Customization

You can easily customize the tool by modifying the `firstNames`, `lastNames`, and phone number `prefixes` vectors in the source code to include more varied or specific data.

## License

This tool is provided as-is, without any warranty. Feel free to modify and use it for your development and testing needs.