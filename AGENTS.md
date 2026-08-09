# Agent Guide — Cafe Management System (C++)

## Project Overview
A console-based cafe management system written in C++. The full project is planned as **4 modules**: Menu Management, Staff Management, Sale Management, and Financial Management. Currently only **Menu Management** is implemented; the other three are planned modules to build.

- **Menu Management** — implemented. Manages menu items (products), persists them to `data/menu.txt`. Ordering (`placeOrder`, `Order`, order history) is intentionally NOT part of this module — it belongs to Sale Management.
- **Staff Management** — planned. Staff CRUD + profiles and login/roles (basic role-based access).
- **Sale Management** — planned. Records sales, sale history/reports, payment/discount handling. Will reuse/refactor the existing `placeOrder` and `Order` code from the menu module.
- **Financial Management** — planned. Revenue totals, expenses, profit calculation, simple reports.

The UI is terminal-based with fixed-width ASCII tables (centered via `centerText`, column widths in `TableFormat.h`).

## Tech Stack
- Language: C++17
- Build: single command with `g++` (no Makefile/CMake)
- Persistence: plain-text CSV-style files under `data/`
- Platform: Windows (PowerShell shell)

## Project Structure
```
├── includes/          # Header files (declarations, inline impl)
│   ├── Category.h     # Hardcoded menu categories (MEN_CATEGORY)
│   ├── Filehandler.h  # File read/write helpers (inline static methods)
│   ├── Menu.h         # Menuitems class + serialization (tofile/fromfile)
│   ├── MenuManager.h  # Business-logic function declarations
│   ├── MenuUI.h       # UI/table/input helper declarations
│   ├── Order.h        # Order class + serialization
│   └── TableFormat.h  # Column widths, file-path constants, centerText()
├── src/
│   ├── main.cpp       # Entry point; menu loop and switch dispatch
│   ├── MenuManager.cpp# add/show/update/delete items, placeOrder
│   └── MenuUI.cpp     # UI helpers, input prompts, validation
├── data/
│   ├── menu.txt       # Menu persistence (CSV per line)
│   └── order.txt      # Order persistence (CSV per line)
├── README.md          # Known bugs / TODO notes
└── AGENTS.md          # This file

# Planned additions (when Staff/Sale/Financial are built)
#   includes/Staff.h  StaffManager.h  Sale.h  SaleManager.h  FinanceManager.h ...
#   src/StaffManager.cpp  SaleManager.cpp  FinanceManager.cpp
#   data/staff.txt  sales.txt  finance.txt  ...
```

## Build & Run
```powershell
# From the project root
g++ -std=c++17 src/main.cpp src/MenuManager.cpp src/MenuUI.cpp -o cafe_system.exe
.\cafe_system.exe
```
Always compile after changing any source/header to catch errors. Several `.exe` files already exist and are gitignored. When new modules are added, extend the `g++` command with their `.cpp` files.

## Data File Formats
- `menu.txt` — one item per line:
  `id,name,price,stock,category`
  Example: `1,Ice Coffee,2.50,10,Drink`
- `order.txt` — one order per line:
  `orderId,menuItemsId,quantity,totalPrice`
  Example: `1,2,3,7.2`

### Planned formats (design before implementing)
- `staff.txt` — `staffId,name,role,password,phone,salary` (per feature spec)
- `sales.txt` — sale record with `saleId,itemId,quantity,total,paymentMethod,discount,date`
- `finance.txt` — expense/income ledger entries: `entryId,type(income|expense),amount,description,date`
Revenue = sum of sales/orders; profit = revenue − expenses. Keep these formats documented here and update both serializer and deserializer together.

## Key Conventions
- Naming: PascalCase classes (`Menuitems`, `Order`, and future `Staff`, `Sale`, `FinanceEntry`), camelCase methods, `menuItems`/`menuitems` used interchangeably for the menu vector (do not rename casually).
- `Menuitems` class is in `Menu.h`; store only `Menuitems` objects in the menu vector (no pointers).
- File paths are constants in `TableFormat.h`: `MENU_FILE`, `ORDER_FILE`. Add `STAFF_FILE`, `SALES_FILE`, `FINANCE_FILE` there as new modules are built.
- All file I/O goes through `FileHandler` static methods; never write to files directly in the menu-loop functions.
- CSV serialization methods: `tofile()/fromfile()` (menu), `toFile()/fromFile()` (order). Note the different casing.
- Categories come from `MEN_CATEGORY` in `Category.h` — add new categories there.
- `addMenuItems` reloads `menu.txt` into a local `menuitems` vector, so a newly added item must be pushed into **both** the passed-in `menuItems` and the local `menuitems` before calling `FileHandler::saveMenuToFile` (see the recent fix at src/MenuManager.cpp:45-50).
- Menu IDs are only unique *within a category* (duplicate IDs across categories are allowed).
- In `main.cpp`, `nextOrderId` is derived from loaded orders; never reset it.
- The main menu (`showMenuFeature`) will grow a top-level feature switch (1=Menu, 2=Staff, 3=Sales, 4=Finance) plus login/role gating once Staff is built.

## Known Issues (see also README.md)
1. `updateMenuItem` and `deleteMenuItem` modify the in-memory vector but do **not** save back to `menu.txt`. Persistence must be added if updates/deletes should survive restarts.
2. Order history output is wrong (README.md, Sale Management scope). `Order::display()` uses table columns intended for menu items, and `placeOrder` prints an "Id items not found" message inside the loop even on success.

## Planned Module Specs (build targets)
1. **Staff Management**: staff CRUD (add/list/update/delete staff with id, name, role, phone, salary) + login/password with role-based access. Staff stored in `data/staff.txt`; role decides which features a user can use.
2. **Sale Management**: record sales (reuse/refactor `placeOrder`), show sale history, support payment method and discount on the total.
3. **Financial Management**: sum revenue from sales/orders, add expense tracking, compute profit (revenue − expenses), and show a simple daily/total summary report.

## Guardrails for Agents
- Prefer editing existing files over creating new ones; keep the flat structure.
- Do not add comments unless asked (repo code has minimal comments).
- Keep the fixed-width column layout (`W_ID`, `W_NAME`, etc.) consistent when touching tables.
- After any change to data formats, update both the serializer and deserializer (and the format docs above).
- Follow the existing pattern when adding modules: `class` header in `includes/`, logic `.cpp` in `src/`, FileHandler I/O, CSV format in `data/`.
- Rebuild and run the program to verify console behavior after changes.
