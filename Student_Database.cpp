//
//  Student_Database.cpp
//  Student_Database_Mangament
//
//  Created by Yash soni on 06/07/23.
//

#include "Student_Database.hpp"
#include <iostream>
#include <memory>
#include <iomanip>
#include <fstream>


StudentDatabase::StudentDatabase() {}
StudentDatabase::~StudentDatabase() {}

void StudentDatabase::start()
{
    std::cout << "\n\n\n\t\t\t======== WELCOME TO STUDENT DATABASE MANAGEMENT AND RESULT CALCULATION SYSTEM ========\n";
    
    char ch;
    student std;
    
    do
    {
        std::cout << "\n\n\n\t\t\t\t\t\t ------ HOME SCREEN ------ \n\n ";
        std::cout << "\n\n\t1. Result Calculation System";
        std::cout << "\n\n\t2. Student Database Management System";
        std::cout << "\n\n\t3. Exit";
        std::cout << "\n\n\n\n\tPlease Select Your Option <1-3> ";
        std::cin >> ch;
        
        switch (ch)
        {
            case '1': std.showResultMenu();
                break;
            case '2': entryMenu();
                break;
            case '3':
                break;
            default:
                std::cout << '\a';
        }
        
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
    } while (ch != '3');
}


void StudentDatabase::entryMenu()
{
    char choice;
    int num;
    student std;
    
    system("clear");
    std::cout << "\n\n\n\t\t\t=====  STUDENT DATABASE MANAGEMENT SYSTEM MENU =====\n\n";
    std::cout << "\n\n\t1. CREATE STUDENT RECORD";
    std::cout << "\n\n\t2. SHOW RECORD OF ALL STUDENTS";
    std::cout << "\n\n\t3. SEARCH STUDENT RECORD";
    std::cout << "\n\n\t4. UPDATE STUDENT RECORD";
    std::cout << "\n\n\t5. DELETE STUDENT RECORD";
    std::cout << "\n\n\t6. BACK TO HOME SCREEN";
    std::cout << "\n\n\n\n\tPlease Select Your Option (1-6) ";
    std::cin >> choice;
    
    switch (choice)
    {
        case '1':
            std.writeStudentRecordInFile();
            break;
        case '2':
            displayAll();
            break;
        case '3':
            std::cout << "\n\n\tPlease Enter the Roll No(XXXX) ";
            std::cin >> num;
            std.show_student_record(num, true);
            break;
        case '4':
            std::cout << "\n\n\tPlease Enter the Roll No(XXXX) ";
            std::cin >> num;
            std.update_student_record(num);
            break;
        case '5':
            std::cout << "\n\n\tPlease Enter the Roll No(XXXX) ";
            std::cin >> num;
            std.deleteStudentRecord(num);
            break;
        case '6':
            break;
        default:
            std::cout << '\a';
    }
    
}



void StudentDatabase::displayAll()
{
    student st;
    std::ifstream is("student.dat", std::ios::binary);
    if(!is)
    {
        std::cout << "\nCouldn't load the file\n";
        is.close();
        return;
    }
    
    std::cout << "\n\n\n\t\t----- DISPLAY ALL RECORDS -----\n\n";
    
    while (is.read(reinterpret_cast<char *>(&st), sizeof(student))) {
        st.get_data();
        std::cout << "\n\n" << std::setfill('=') << std::setw(50) << "=\n";
    }
    is.close();
}
