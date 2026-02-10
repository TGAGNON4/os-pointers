// compile: g++ -std=c++14 -o pointers pointers.cpp
#include <iostream>
#include <string>

typedef struct Student {
    int id;
    char *f_name;
    char *l_name;
    int n_assignments;
    double *grades;
} Student;

int promptInt(std::string message, int min, int max);
double promptDouble(std::string message, double min, double max);
void calculateStudentAverage(void *object, double *avg);

int main(int argc, char **argv)
{
    Student student;
    double average;

    // Sequence of user input -> store in fields of `student`
    // get student's id number
    student.id = promptInt("Please enter the student's id number: ", 0, 999999999); // 0 -> any 9 digit number

    // get student's first name
    student.f_name = new char[128];
    std::cout << "Please enter the student's first name: ";
    std::cin >> student.f_name; // takes in any character array that is less than 128 characters

    // get student's last name
    student.l_name = new char[128];
    std::cout << "Please enter the student's last name: ";
    std::cin >> student.l_name; // takes in any character array that is less than 128 characters

    // get number of assignments
    student.n_assignments = promptInt("Please enter how many assignments were graded: ", 1, 134217728); // 1 -> specified max
    std::cout << std::endl; // new line

    // get all assignment grades
    int i = 0;
    student.grades = new double[student.n_assignments + 1];
    for(i = 0; i < student.n_assignments; i++){
        student.grades[i] = promptDouble("Please enter grade for assignment " + std::to_string(i) + ": ", 0.0, 100.0);
    }
    student.grades[i] = -1.0; // end signifier for calculateStudentAverage

    // print out student name and id number info
    std::cout << std::endl << "Student: " << student.f_name << " " << student.l_name << " [" << student.id << "]" << std::endl;

    // Call `CalculateStudentAverage(???, ???)`
    //calculateStudentAverage();
    // Output `average`
    average = 0;
    calculateStudentAverage(student.grades, &average);
    std::cout << "  Average grade: " << ((int)(average * 10 + 0.5) / 10.0) << std::endl; // round and keep one decimal place for avg

    delete[] student.f_name;
    delete[] student.l_name;
    delete[] student.grades;

    return 0;
}

/*
   message: text to output as the prompt
   min: minimum value to accept as a valid int
   max: maximum value to accept as a valid int
*/
int promptInt(std::string message, int min, int max)
{
    // Code to prompt user for an int
    std::string ans;
    int value;

    while(true){
        // prompt for user input
        std::cout << message;
        std::cin >> ans; // store user input

        try {
            // converting string input into integer
            size_t size_of_int = 0;
            value = std::stoi(ans, &size_of_int);

            // catches the "6A" input as stod would convert input to 6 without this catch
            // also checks if the answer is within min and max
            if(size_of_int != ans.length() || (value < min || value > max)){
                std::cout << "Sorry, I cannot understand your answer" << std::endl;
            }
            else {
                return value;
            }
        }
        // any errors in converting to a integer will be caught here
        catch (...){
            std::cout << "Sorry, I cannot understand your answer" << std::endl;
        }
    }
}

/*
   message: text to output as the prompt
   min: minimum value to accept as a valid double
   max: maximum value to accept as a valid double
*/
double promptDouble(std::string message, double min, double max)
{
    // Code to prompt user for a double
    std::string ans;
    double value;

    while(true){
        // prompt for user input
        std::cout << message;
        std::cin >> ans; // store user input

        try {
            // converting string input into double
            size_t size_of_double = 0;
            value = std::stod(ans, &size_of_double);

            // catches the "6A" input as stod would convert input to 6.0 without this catch
            // also checks if the answer is within min and max
            if(size_of_double != ans.length() || (value < min || value > max)){
                std::cout << "Sorry, I cannot understand your answer" << std::endl;
            }
            else {
                return value;
            }
        }
        // any errors in converting to a double will be caught here
        catch (...){
            std::cout << "Sorry, I cannot understand your answer" << std::endl;
        }
    }
}

/*
   object: pointer to anything - your choice! (but choose something that will be helpful)
   avg: pointer to a double (can store a value here)
*/
void calculateStudentAverage(void *object, double *avg)
{
    // Code to calculate and store average grade

    // *object will be a double array that holds the grades with a -1 to signify the last element
    int i = 0;
    while(true) {
        if(*((double *)object + i) == -1.0){
            break; // reached the end of the array
        }
        else{
            *avg = *avg + *((double *)object + i); // sum test scores into avg by incrementing pointer by i
        }
        i = i + 1;
    }
    *avg = *avg / i; // calculate avg as i = number of assignments
}
