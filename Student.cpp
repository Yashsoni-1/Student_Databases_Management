//
//  Student.cpp
//  Student_Database_Mangament
//
//  Created by Yash soni on 06/07/23.
//

#include "Student.hpp"
#include <iostream>
#include <fstream>
#include <vector>

int roll_no_entered = 0;
int roll_no_got = 0;


student::student()
{
    std::ofstream os("student.dat", std::ios::binary | std::ios::app);
    os.close();
    
    std::ofstream os2("DuplicateCheckingFile.txt", std::ios::app);
    os2.close();
}

bool student::set_data()
{
    std::cout << "\n\tEnter the roll no of the student(XXXX): ";
    std::cin >> Roll_No;
    roll_no_entered =  Roll_No;
    if(roll_no_got != roll_no_entered && is_duplicate())
    {
        std::cout << "\n\tError duplicate record...\n";
        return false;
    }
    
    std::cout << "\n\tEnter the name of the student: ";
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.getline(Student_Name, 15, '\n');
    std::cout << "\n\tEnter the marks of the Social_Studies out of 100: ";
    std::cin >> Social_Studies_Marks;
    std::cout << "\n\tEnter the marks of the Statistics out of 100: ";
    std::cin >> Statistics_Marks;
    std::cout << "\n\tEnter the marks of the Maths out of 100: ";
    std::cin >> Maths_Marks;
    std::cout << "\n\tEnter the marks of the English out of 100: ";
    std::cin >> English_Marks;
    std::cout << "\n\tEnter the marks of the Computer out of 100: ";
    std::cin >> Computer_Marks;
    calculate_grade();
    
    return true;
}

void student::writeStudentRecordInFile()
{
    if(!set_data()) {
        std::cout << "\n\tRecord not created...\n";
        return;
    }
    
    std::ofstream os("student.dat", std::ios::binary | std::ios::app);
    os.write(reinterpret_cast<char *>(this), sizeof(student));
    os.close();
    std::cout << "\n\tRecord created successfully...\n\n";
    
}
void student::get_data()
{
    std::cout << "\n\tRoll Number of student = " << Roll_No;
    std::cout << "\n\tName of student = " << Student_Name;
    std::cout << "\n\tMarks in Social Studies = " << Social_Studies_Marks;
    std::cout << "\n\tMarks in Statistics = " << Statistics_Marks;
    std::cout << "\n\tMarks in Maths = " << Maths_Marks;
    std::cout << "\n\tMarks in English = " << English_Marks;
    std::cout << "\n\tMarks in Computer = " << Computer_Marks;
    std::cout << "\n\tPercentage of student = " << Student_Percentage;
    std::cout << "\n\tGrade of student = " << Student_Grade;
}

int student::get_student_roll_no()
{
    return Roll_No;
}

bool student::is_duplicate()
{
    std::ifstream is("DuplicateCheckingFile.txt");
    int current_roll_no;
    while (!is.eof()) {
        is >> current_roll_no;
        if(current_roll_no == Roll_No){
            is.close();
            return true;
        }
    }
    is.close();
    std::ofstream os("DuplicateCheckingFile.txt", std::ios::app);
    os << '\n' << Roll_No;
    os.close();
    
    return false;
}

void delete_from_duplicate_file(int roll_no)
{
    std::ifstream is("DuplicateCheckingFile.txt");
    int current_roll_no;
    std::vector<int> vec;
    
    while (!is.eof()) {
        is >> current_roll_no;
        vec.push_back(current_roll_no);
    }
    is.close();
    
    std::ofstream os("DuplicateCheckingFile.txt");
    
    for(int i: vec) {
        if(i == roll_no)
            continue;
        os << '\n' << i;
    }
    
    os.close();
}

void student::calculate_grade()
{
    Student_Percentage = (Maths_Marks + Statistics_Marks + English_Marks
                          + Social_Studies_Marks + Computer_Marks)/5.0f;
    if(Student_Percentage > 90)
        Student_Grade = 'A';
    else if(Student_Percentage > 80)
        Student_Grade = 'B';
    else if(Student_Percentage > 70)
        Student_Grade = 'C';
    else if(Student_Percentage > 60)
        Student_Grade = 'D';
    else
        Student_Grade = 'E';
}



void student::update_student_record(int roll_no)
{
    bool found = false;
    bool is_data_set = false;
    std::fstream fs("student.dat", std::ios::binary | std::ios::in | std::ios::out );
    if(!fs)
    {
        std::cout << "\n\tCouldn't open the file...\n";
        return;
    }
    roll_no_got = roll_no;
    while (!fs.eof() && !found) {
        fs.read(reinterpret_cast<char *>(this), sizeof(*this));
        if(get_student_roll_no() == roll_no)
        {
            get_data();
            std::cout << "\n\n\tPlease Enter The New Details of student\n";
            is_data_set = set_data();
            if(is_data_set)
            {
                int pos = (-1)*static_cast<int>(sizeof(*this));
                fs.seekp(pos, std::ios::cur);
                fs.write(reinterpret_cast<char *>(this), sizeof(student));
            }
            found = true;
        }
    }
    if(!is_data_set)
        std::cout << "\n\tCouldn't update the record...\n\n";
    if(!found)
        std::cout << "\n\tRecord does not exists...\n";
    
    if(is_data_set && found && roll_no != roll_no_entered)
    {
        delete_from_duplicate_file(roll_no);
    }
    roll_no_entered = 0;
    roll_no_got = 0;
}


void student::deleteStudentRecord(int roll_no)
{
    bool is_present = false;
    std::ifstream is("student.dat", std::ios::binary);
    if(!is)
    {
        std::cout << "\n\tFile cannot be opened...\n";
        return;
    }
    
    while (is.read(reinterpret_cast<char *>(this), sizeof(student))) {
        if(get_student_roll_no() == roll_no)
            is_present = true;
    }
    
    if(!is_present)
    {
        std::cout << "\n\n\tNo record found!! \n";
        return;
    }
    
    std::ofstream os("temp.dat", std::ios::binary);
    is.seekg(0, std::ios::beg);
    
    while (is.read(reinterpret_cast<char *>(this), sizeof(student))) {
        if(get_student_roll_no() != roll_no)
            os.write(reinterpret_cast<char *>(this), sizeof(student));
    }
    
    is.close();
    os.close();
    
    remove("student.dat");
    rename("temp.dat", "student.dat");
    delete_from_duplicate_file(roll_no);
    std::cout << "\n\tStudent record deleted...\n\n";
}


bool student::show_student_record(int roll_no, bool is_single = false)
{
    bool flag = false;
    std::ifstream is("student.dat", std::ios::binary);
    if(!is)
    {
        std::cout << "\tFile cannot be opened...\n";
        return false;
    }
    
    if(is_single)
        std::cout << "\n\n\n\t--- STUDENT RECORD ---\n";
    
    while (is.read(reinterpret_cast<char *>(this), sizeof(student))) {
        if(get_student_roll_no() == roll_no)
        {
            get_data();
            flag = true;
        }
    }
    
    is.close();
    
    if(!flag)
    {
        std::cout << "\n\tRecord does not exists...\n";
        return false;
    }
    
    return true;
}

void student::showResultMenu()
{
    char ch;
    int num;
    
    std::cout << "\n\n\n\t---- RESULT MENU ----";
    std::cout << "\n\n\n\t1. Class Result";
    std::cout << "\n\n\n\t2. Student Report Card";
    std::cout << "\n\n\n\t3. Back to Main Menu";
    std::cout << "\n\n\n\n\tPlease Select Your Option <1-3> ";
    std::cin >> ch;
    
    switch (ch)
    {
        case '1': displayClassResult();
            break;
        case '2':
            std::cout << "\n\n\tPlease Enter the Roll No(XXXX) ";
            std::cin >> num;
            show_student_record(num, true);
            break;
        case '3':
            break;
        default:
            std::cout << '\a';
    }
    
}

void student::tabular_display()
{
    std::cout<< std::setfill(' ') << std::setw(6) << Roll_No << '|'
    << std::left << std::setw(15) << Student_Name << '|'
    << std::setw(6) << Social_Studies_Marks << '|'
    << std::setw(6) << Statistics_Marks << '|'
    << std::setw(6) << Maths_Marks << '|'
    << std::setw(6) << English_Marks << '|'
    << std::setw(8) << Computer_Marks << '|'
    << std::setw(8) << Student_Percentage << '|'
    << std::setw(8) << Student_Grade << "|\n";
}


void student::displayClassResult()
{
    std::ifstream is("student.dat", std::ios::binary);
    if(!is)
    {
        std::cout << "\n\tFile cannot be opened\n";
        return;
    }
    
    std::cout << "\n\n\n";
    std::cout << std::setfill('-') << std::setw(78) << '-' << "\n" ;
    std::cout<< std::setfill(' ') << std::left << std::setw(6) << "Roll" << '|'
    << std::setw(15) << "  Name" << '|'
    << std::setw(6) << "SocS" << '|'
    << std::setw(6) << "Stat" << '|'
    << std::setw(6) << "Mat" << '|'
    << std::setw(6) << "Eng" << '|'
    << std::setw(8) << "Com" << '|'
    << std::setw(8) << "%age"<< '|'
    << std::setw(8) << "Grd" << "|\n";
    
    std::cout << std::setfill('-') << std::setw(78) << '-' << "\n";
    
    while (is.read(reinterpret_cast<char *>(this), sizeof(student))) {
        tabular_display();
        std::cout << std::setfill('-') << std::setw(78) << '-' << "\n";
    }
    
    is.close();
}

