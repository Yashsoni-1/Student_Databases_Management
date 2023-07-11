//
//  Student.hpp
//  Student_Database_Mangament
//
//  Created by Yash soni on 06/07/23.
//

#ifndef Student_hpp
#define Student_hpp
#include <string>



class student
{
private:
    char Student_Name[50];
    char Student_Grade;
    int Roll_No;
    int Social_Studies_Marks, Statistics_Marks, Maths_Marks,
    English_Marks, Computer_Marks;
    double Student_Percentage;
    bool flag;
    
    void calculate_grade();
public:
    student();
    int get_student_roll_no();
    void get_data();
    void tabular_display();
    bool is_duplicate();
    bool set_data();
    bool show_student_record(int, bool);
    void writeStudentRecordInFile();
    void update_student_record(int);
    void deleteStudentRecord(int);
    void showResultMenu();
    void displayClassResult();
};

#endif /* Student_hpp */
