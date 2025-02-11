# SpeedCars 🚗

SpeedCars is a C++ system for managing groups of vehicles, users, and sectors. It allows data registration, vehicle assignment to sectors, handling transfers and queues, generating daily reports, and optimizing operations efficiently.

**Created by Kevin Zambrano 👨‍💻**

## Table of Contents 📖

- [Description](#description)
- [Features](#features)
- [Installation and Usage](#installation-and-usage)
- [Execution Example](#execution-example)
- [Project Structure](#project-structure)
- [Contributing](#contributing)
- [License](#license)

## Description 📝

The SpeedCars project is developed in C++ and uses text files for persistent storage of data (users, vehicles, and sectors). The system features two main menus:

- **Management Menu:** Allows you to register and store data for users, vehicles, and sectors.
- **Daily Service Menu:** Facilitates random distribution of vehicles among sectors, request and management of vehicle transfers, handling waiting queues, changing vehicle sectors, and generating daily reports.

## Features ✨

- **Data Registration:** Persistent storage in text files (`users.txt`, `vehicles.txt`, and `sectors.txt`) 🗃️.
- **Vehicle Distribution:** Random assignment of vehicles to sectors 🎲.
- **Transfer Management:** Request and completion of vehicle transfers between sectors 🔄.
- **Waiting Queues:** Handling of users waiting when no vehicles are available ⏳.
- **Report Generation:** Creation of daily reports summarizing system activity 📊.
- **Interactive Interface:** Console menus that simplify system management and operations 🖥️.

## Installation and Usage 🔧

### Requirements

- A C++ compiler (e.g., g++, clang++) 💻.
- A compatible operating system (Windows, Linux, macOS) 🖥️.

### Compilation

To compile the project, open a terminal in the project folder and run:

```bash
g++ -o speedcars main.cpp

