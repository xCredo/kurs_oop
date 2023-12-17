#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>

const std::string names[] = {"Владислав", "Елизабет", "Михаил", "Ольга", "Виталя", "Анна", "Георгий", "Софья", "Борис", "Изобелла"};
const std::string groups[] = {"Группа ИС-241", "Группа ИС-242", "Группа ИС-243"};
const int ages[] = {18, 19, 20, 21};

int getRandomNumber(int min, int max) {
    static const double fraction = 1.0 / (RAND_MAX + 1.0);
    return min + static_cast<int>((max - min + 1) * (std::rand() * fraction));
}

void writeOutputToFile(const std::string& filename, const std::string& content) {
    std::ofstream outputFile(filename);
    if (outputFile.is_open()) {
        outputFile << content;
        outputFile.close();
        std::cout << "Output written to file: " << filename << "\n";
    } 
    
    else {
        std::cerr << "Unable to open file: " << filename << "\n";
    }
}

class Student {
public:
    Student(const std::string& name, int age, const std::string& group)
        : name(name), age(age), group(group) {}

    std::string getName() const {
        return name;
    }

    int getAge() const {
        return age;
    }

    std::string getGroup() const {
        return group;
    }

private:
    std::string name;
    int age;
    std::string group;
};

class PaidStudent : public Student {
public:
    PaidStudent(const std::string& name, int age, const std::string& group, const std::string& major)
        : Student(name, age, group), major(major) {}

    std::string getMajor() const {
        return major;
    }

private:
    std::string major;
};

class BudgetStudent : public Student {
public:
    BudgetStudent(const std::string& name, int age, const std::string& group, const std::string& previousEducation)
        : Student(name, age, group), previousEducation(previousEducation) {}

    std::string getPreviousEducation() const {
        return previousEducation;
    }

private:
    std::string previousEducation;
};

int main() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    int choice;
    std::cout << "Choose an option:\n";
    std::cout << "1. Generate random students\n";
    std::cout << "2. Enter students manually\n";
    std::cout << "Choice: ";
    std::cin >> choice;

    if (choice == 1 || choice == 2) {
        int numStudents;
        if (choice == 1) {
            numStudents = getRandomNumber(1, 30);
        } 
        
        else {
            std::cout << "Enter the number of students: ";
            std::cin >> numStudents;
        }

        std::string paidOutputContent = "Paid Student Details:\n";
        paidOutputContent += "\n\n--------------------------\n\n";

        std::string budgetOutputContent = "Budget Student Details:\n";
        budgetOutputContent += "\n\n--------------------------\n\n";

        std::string studentsOutputContent = "Students Details:\n";
        studentsOutputContent += "\n\n--------------------------\n\n";

        for (int i = 0; i < numStudents; ++i) {
            std::string name = names[getRandomNumber(0, 9)];
            int age = ages[getRandomNumber(0, 3)];
            std::string group = groups[getRandomNumber(0, 2)];
            std::string previousEducation = (age >= 20) ? "College" : "High School";

            if (getRandomNumber(0, 1) == 0) {
                std::string major = "Engineering";
                PaidStudent paidStudent(name, age, group, major);
                paidOutputContent += std::to_string(i+1) + ".\n";
                paidOutputContent += "Name: " + paidStudent.getName() + "\n";
                paidOutputContent += "Age: " + std::to_string(paidStudent.getAge()) + "\n";
                paidOutputContent += "Group: " + paidStudent.getGroup() + "\n";
                paidOutputContent += "Major: " + major + "\n";
                paidOutputContent += "--------------------------\n\n";
                studentsOutputContent += std::to_string(i+1) + "\n";
                studentsOutputContent += "Name: " + paidStudent.getName() + "\n";
                studentsOutputContent += "Age: " + std::to_string(paidStudent.getAge()) + "\n";
                studentsOutputContent += "Group: " + paidStudent.getGroup() + "\n";
                studentsOutputContent += "Major: " + major + "\n";
                studentsOutputContent += "--------------------------\n";
            } 
            
            else {
                BudgetStudent budgetStudent(name, age, group, previousEducation);
                budgetOutputContent += std::to_string(i+1) + ".\n";
                budgetOutputContent += "Name: " + budgetStudent.getName() + "\n";
                budgetOutputContent += "Age: " + std::to_string(budgetStudent.getAge()) + "\n";
                budgetOutputContent += "Group: " + budgetStudent.getGroup() + "\n";
                budgetOutputContent += "Previous Education: " + previousEducation + "\n";
                budgetOutputContent += "--------------------------\n\n";
                studentsOutputContent += std::to_string(i+1) + "\n";
                studentsOutputContent += "Name: " + budgetStudent.getName() + "\n";
                studentsOutputContent += "Age: " + std::to_string(budgetStudent.getAge()) + "\n";
                studentsOutputContent += "Group: " + budgetStudent.getGroup() + "\n";
                studentsOutputContent += "Previous Education: " + previousEducation + "\n";
                studentsOutputContent += "--------------------------\n";
            }
        }

        if (choice == 1 || choice == 2) {
            writeOutputToFile("budget_students.txt", budgetOutputContent);
            writeOutputToFile("paid_students.txt", paidOutputContent);
            writeOutputToFile("students.txt", studentsOutputContent);

        }
    } 
    
    else {
        std::cout << "Invalid choice. Exiting...\n";
        return 1;
    }

    return 0;
}
