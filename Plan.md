# Cafe Management System - Development Plan

## 1. Goal

This project has four main modules: Menu Management, Staff Management, Sale Management, and Financial Management. Each module stores a large amount of data. The goal of this plan is to build one shared infrastructure that all four modules reuse, so that we do not need to fix the same problems again when we create the next feature.

## 2. Current State

1. Menu Management is complete. It has the MenuItem class with getters, setters, and both constructors. It supports full CRUD operations saved to data/menu.txt. It can also export data to data/menu_export.csv and open the file automatically in Excel.
2. Staff Management, Sale Management, and Financial Management are still empty stubs.
3. The shared folder is empty but is already connected to the build system through the Makefile.
4. Several bugs were found and fixed during Menu Management development. These must not happen again:
   - Infinite loop when input ends unexpectedly (EOF).
   - Excel export failed because of forward slashes in the file path.
   - Data files were saved to the wrong folder when the program was started by double-clicking the exe file.

## 3. Architecture

All four modules follow the same data flow:

1. The user enters data through the console.
2. The data is stored in memory using a Model class inside a vector.
3. Every create, update, or delete operation immediately saves all records to a text file in the data folder. This text file is the single source of truth.
4. Export to Excel is a separate, one-way operation. It creates a CSV file for viewing only. The program never reads data back from the CSV file.

## 4. Phase 1 - Shared Infrastructure

Create the following new files. They contain all common logic used by every module.

File: shared/include/InputHelper.h
- Provides readInt, readDouble, and readLine functions.
- Repeats the question when the user enters invalid input.
- Ends safely when the input stream closes, instead of looping forever.

File: shared/include/StorageHelper.h and shared/src/StorageHelper.cpp
- Resolves the data folder path based on the location of the running exe file, so files are always saved in the same place.
- Provides functions to read all lines from a file and write all lines to a file.
- Creates the data folder automatically if it does not exist.
- Provides a helper to split pipe-separated lines into values.

File: shared/include/CsvExporter.h and shared/src/CsvExporter.cpp
- Provides one export function used by every module.
- Handles UTF-8 byte order mark, comma quoting inside values, backslash path fix, and automatic opening in Excel after export.

## 5. Phase 2 - Refactor Menu Management

Modify menu_management/src/MenuManager.cpp so that it uses the three shared helpers instead of its own inline logic. The behavior stays exactly the same, but the code becomes shorter and easier to maintain.

After refactoring, run a full test: add, view, update, and delete an item, then export and confirm that Excel opens automatically.

## 6. Phase 3 - Remaining Modules

Build each remaining module by repeating the same pattern. Each module gets one Model class and one Manager class.

Staff Management:
- Model class name: Staff.
- Data file: data/staff.txt.
- Fields: id, name, role, phone, salary.

Sale Management:
- Model class name: Sale.
- Data file: data/sale.txt.
- Fields: id, date, itemId, itemName, quantity, unitPrice, total.
- Note: at sale time, the item name and unit price are copied into the sale record. Later changes to menu prices do not corrupt old sale records.

Financial Management:
- Model class name: FinanceRecord.
- Data file: data/finance.txt.
- Fields: id, date, type (income or expense), description, amount.

Recommended build order: Staff first, then Sale, then Finance, because Finance can calculate totals from Sale records.

## 7. Rules for Every Model Class

1. Private member variables are declared above public members.
2. Both a default constructor and a parameterized constructor are required.
3. Every field has a getter and a setter.
4. A toFileString method converts the object into one pipe-separated line for saving.

## 8. Conventions for Every Manager Class

1. The submenu style matches the main menu style, with equal sign banners and numbered options. The last option always returns to the previous menu.
2. Data is saved to the text file after every create, update, and delete operation.
3. New record IDs use the highest existing ID plus one.
4. Update and delete operations find records by ID and show an error message when the ID does not exist.
5. Export is write-only. The application never reads from CSV files.
6. Changes never touch folders belonging to other modules.

## 9. Decisions

1. Data files are stored next to the exe file, so the program works even when started by double-clicking.
2. Field definitions follow the tables in section 6.
3. Build order: Phase 1 and Phase 2 now, then Staff, Sale, and Finance later.

## 10. Build Commands

Use mingw32-make clean followed by mingw32-make to rebuild. Note that the Makefile does not track header dependencies, so header changes require a clean rebuild.
