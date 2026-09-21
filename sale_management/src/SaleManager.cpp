#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <string>
#include <limits>
#include "SaleManager.h"




void SaleManager::run()
{
    int choice = 0;
    do
    {
        std::cout << "\n+------------------------------------------+\n";
        std::cout << "|             SALE MANAGEMENT             |\n";
        std::cout << "+------------------------------------------+\n";
        std::cout << "| 1 | Receipt Management                  |\n";
        std::cout << "| 2 | Sale Reports                        |\n";
        std::cout << "| 3 | Back                                |\n";
        std::cout << "+------------------------------------------+\n";
        std::cout << "Choose option: ";
        if (!(std::cin >> choice))
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid option. Please enter a number.\n";
            continue;
        }

        switch (choice)
        {
        case 1:
        {
            int receiptChoice = 0;
            do
            {
                std::cout << "\n+------------------------------------------+\n";
                std::cout << "|           RECEIPT MANAGEMENT            |\n";
                std::cout << "+------------------------------------------+\n";
                std::cout << "| 1 | View All Receipts                   |\n";
                std::cout << "| 2 | Search Receipt by ID                |\n";
                std::cout << "| 3 | Search Receipt by Order ID          |\n";
                std::cout << "| 4 | Search Receipt by Date              |\n";
                std::cout << "| 5 | Back                                |\n";
                std::cout << "+------------------------------------------+\n";
                std::cout << "Choose option: ";
                if (!(std::cin >> receiptChoice))
                {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Invalid option. Please enter a number.\n";
                    continue;
                }

                switch (receiptChoice)
                {
                case 1:
                    Receipt::viewFromFile("data/receipts.txt");
                    break;
                case 2:
                    Sale::searchReceiptById();
                    break;
                case 3:
                    Sale::searchReceiptByOrderId();
                    break;
                case 4:
                    Sale::searchReceiptByDate();
                    break;
                case 5:
                    break;
                default:
                    std::cout << "Invalid option. Please try again.\n";
                }
            } while (receiptChoice != 5);
            break;
        }
        case 2:
        {
            int reportChoice = 0;
            do
            {
                std::cout << "\n+------------------------------------------+\n";
                std::cout << "|              SALE REPORTS               |\n";
                std::cout << "+------------------------------------------+\n";
                std::cout << "| 1 | View All Sales                      |\n";
                std::cout << "| 2 | View Sale by ID                     |\n";
                std::cout << "| 3 | View Sale by Date                   |\n";
                std::cout << "| 4 | Back                                |\n";
                std::cout << "+------------------------------------------+\n";
                std::cout << "Choose option: ";
                if (!(std::cin >> reportChoice))
                {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Invalid option. Please enter a number.\n";
                    continue;
                }

                switch (reportChoice)
                {
                case 1:
                    Sale::viewSalesFromFile("data/orders.txt");
                    break;
                case 2:
                    Sale::searchSaleById();
                    break;
                case 3:
                    Sale::searchSaleByDate();
                    break;
                case 4:
                    break;
                default:
                    std::cout << "Invalid option. Please try again.\n";
                }
            } while (reportChoice != 4);
            break;
        }
        case 3:
            break;
        default:
            std::cout << "Invalid option. Please try again.\n";
        }
    } while (choice != 3);
}
