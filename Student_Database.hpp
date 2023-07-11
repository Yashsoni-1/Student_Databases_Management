//
//  Student_Database.hpp
//  Student_Database_Mangament
//
//  Created by Yash soni on 06/07/23.
//

#ifndef Student_Database_hpp
#define Student_Database_hpp

#include "Student.hpp"


class StudentDatabase {
public:
    StudentDatabase() ;
    ~StudentDatabase() ;
    
    void start();
    void entryMenu();
    void displayAll();
};

#endif /* Student_Database_hpp */
