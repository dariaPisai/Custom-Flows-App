#include<iostream>
#include<vector>
#include<string>


using namespace std;

class Step {
public:
    std::string type;
    string className = "Step";

    Step() {}

    virtual void inputAttributes() = 0;

    string getClassName() {
        return className;
    }

    virtual void getFlow( vector<Step*> Steps) {}

    virtual float getNumberInput () const{
        return 0.0;
    }

    virtual void displayAttributes() const = 0;

    virtual void display() = 0;

    virtual ~Step() {}
};

class Title: public Step{

    private:
    string title;
    string subtitle;
    string className = "Title";

    public:

    string getClassName() {
        return className;
    }

     void inputAttributes() override {
        cout << "Title: ";
        cin >> title;
        cout << "Subtitle: ";
        cin.ignore(); // Ignore newline left in buffer
        getline(cin, subtitle);
    }

    Title() {
        type = "Title";
    }

    void display() override {
        cout << "Type: " << type << endl;
    }

    void displayAttributes() const override {
        cout << "Title: " << title << endl;
        cout << "Subtitle: " << subtitle << endl;
    }

    ~Title() {}

};

class Text: public Step{

    private:
    string title;
    string copy;
    string className = "Text";

    public:

    Text() {
        type = "Text";
    }

    string getClassName() {
        return className;
    }

    void inputAttributes() override {
        cout << "Title: ";
        cin >> title;
        cout << "Copy: ";
        cin.ignore(); // Ignore newline left in buffer
        getline(cin, copy);
    }

    void display() override {
        cout << "Type: " << type << endl;
    }

    void displayAttributes() const override {
        cout << "Title: " << title << endl;
        cout << "Copy: " << copy << endl;
    }

    ~Text() {}

};

class Text_Input: public Step{

    private:
    string description;
    string textInput;
    string className = "Text Input";

    public:

    Text_Input() {
        type = "Text Input";
    }

    string getClassName() {
        return className;
    }

    void inputAttributes() override {
        cout << "Description: ";
        cin >> description;
        cout << "Text Input: ";
        cin.ignore(); // Ignore newline left in buffer
        getline(cin, textInput);
    }

     void displayAttributes() const override {
        cout << "Description: " << description << endl;
        cout << "Text Input: " << textInput << endl;
    }

    void display() override {
        cout << "Type: " << type << endl;
    }

    ~Text_Input() {}
};

class Number_Input: public Step{

    private:
    string description;
    float numberInput;
    string stringInput;
    string className = "Number Input";

    public:

    Number_Input() {
        type = "Number Input";
    }

    string getClassName() {
        return className;
    }

    void inputAttributes() override {
        cout << "Description: ";
        cin >> description;
        cout << "Number input: ";
        cin.ignore(); // Ignore newline left in buffer
        getline(cin, stringInput);
        numberInput = stof(stringInput);
    }

     void displayAttributes() const override {
        cout << "Description: " << description << endl;
        cout << "Number Input: " << numberInput << endl;
    }

    float   getNumberInput() const override{
        return numberInput;
    }

    void display() override {
        cout << "Type: " << type << endl;
    }

    ~Number_Input() {}
};

class Calculus : public Step{

    private:
    vector<Step*> Steps;
    int stepsCounter;
    string operation;
    string className = "Calculus";


    public:


    Calculus() {
        type = "Calculus";
    }

    string getClassName() {
        return className;
    }


    void inputAttributes() override {}

    

    float performOperation (float a, float b, string op) const {
        if (op == "+") {
            return a + b;
        } else if (op == "-") {
            return a - b;
        } else if (op == "*") {
            return a * b;
        } else if (op == "/") {
            if (b == 0) {
                cout << "Error: Division by zero is not allowed." << endl;
                return NAN; // Not a Number
            }
            return a / b;
        } else if (op == "min") {
            return min(a, b);
        } else if (op == "max") {
            return max(a, b);
        } else {
            cout << "Error: Invalid operation!" << endl;
            return NAN; // Not a Number
        }
    }

    void display() override {
        cout << "Type: " << type << endl;
    }

    void getFlow (vector<Step*> Steps) override {
        this->Steps = Steps;
    }

    

    void displayAttributes() const override {
        string string;
        int firstPosition;
        int secondPosition;
        float result;

        fflush(stdin);

        do{

        cout << "You need to introduce the position of one of your previous Number Input steps: "<< endl ;
        getline(cin, string);
        firstPosition = stoi(string);
        cout << "You need to introduce the position of another one of your previous Number Input steps: " << endl ;
        cin >> secondPosition;

        cout << "For the operations field you can choose from the following options: " <<endl;
        cout << "1. Addition (type in '+')" << endl;
        cout << "2. Subtraction (type in '-')" << endl;
        cout << "3. Multiplication (type in '*')" << endl;
        cout << "4. Division (type in '/')" << endl;
        cout << "5. Minimum (type in 'min')" << endl;
        cout << "6. Maximum (type in 'max')" << endl;

        cin >> string;

        

        if(Steps[firstPosition - 1]->getClassName() == "Number Input" && Steps[secondPosition - 1]->getClassName() == "Number Input"){

            cout << "***" << endl;
            result = performOperation(Steps[firstPosition - 1]->getNumberInput(), Steps[secondPosition - 1]->getNumberInput(), string);
            cout << "Result: " << result <<endl;
            break;

        } else {
            cout << "Try again!!!" << endl;
        }

        }while(1);

        
    }

    

    ~Calculus() {}
};

class Display: public Step{

    private: 
    int step;
    string stringStep;
    string className = "Display";
    vector<Step*> Steps;

    public:

    Display() {
        type = "Display";
    }

    string getClassName() {
        return className;
    }

    void inputAttributes() override {
        cout << "Step: ";
        cin >> stringStep;
        step = stof(stringStep);
    }

    void getFlow (vector<Step*> Steps) override {
        this->Steps = Steps;
    }

    void display() override {
        cout << "Type: " << type << endl;
    }

    void displayAttributes() const override {
        cout << "Step: " << step << endl;
    }

    ~Display() {}
};

class Text_File : public Step{

    private:
    string description;
    string fileName;
    string className = "Text File";

    public:

    Text_File() {
        type = "Text File";

    }

    string getClassName() {
        return className;
    }

    void inputAttributes() override {
        cout << "Description: ";
        cin >> description;
        cout << "File Name: ";
        cin.ignore(); // Ignore newline left in buffer
        getline(cin, fileName);
    }

    void display() override {
        cout << "Type: " << type << endl;
    }

    void displayAttributes() const override {
        cout << "Description: " << description << endl;
        cout << "File Name: " << fileName << endl;
    }

    ~Text_File() {}
};

class CSV_File : public Step{

    private:
    string description;
    string fileName;
    string className = "CSV File";

    public:

    CSV_File() {
        type = "CSV File";
    }

    string getClassName() {
        return className;
    }

    void inputAttributes() override {
        cout << "Description: ";
        cin >> description;
        cout << "File Name: ";
        cin.ignore(); // Ignore newline left in buffer
        getline(cin, fileName);
    }

    void display() override {
        cout << "Type: " << type << endl;
    }

    void displayAttributes() const override {
        cout << "Description: " << description << endl;
        cout << "File Name: " << fileName << endl;
    }

    ~CSV_File() {}
};

class Output : public Step{

    private:
    int step;
    string stringStep;
    string fileName;
    string title;
    string description;
    string className = "Output";

    public:

    Output() {
        type = "Output";
    }

    string getClassName() {
        return className;
    }

    void inputAttributes() override {
        cout << "Step: ";
        cin >> stringStep;
        cin.ignore();
        step = stof(stringStep);
      
        cout << "File Name: ";
        cin.ignore(); // Ignore newline left in buffer
        getline(cin, fileName);

        cout << "Title: ";
        cin.ignore();
        getline(cin, title);

        cout << "Description: ";
        cin.ignore();
        getline(cin, description);
    }

    void display() override {
        cout << "Type: " << type << endl;
    }

    void displayAttributes() const override {
        cout << "Step: " << step << endl;
        cout << "Title: " << title << endl;
        cout << "File Name: " << fileName << endl;
        cout << "Description: " << description << endl;
    }

    ~Output() {}
};

class End : public Step{

    private:
    string className = "End";

    public:

    End() {
        type = "End";
    }

    string getClassName() {
        return className;
    }

    void inputAttributes() override {};

    void display() override {
        cout << "Type: " << type << endl;
    }

    void displayAttributes() const override {};

    ~End() {}
};


class Flow{
private:
    std::vector<Step*> steps; // Vector of Step pointers

public:
    Flow() {}
    ~Flow() {
        for (Step* step : steps) {
            delete step;
        }
    }

    void addStep(Step* step) {
        steps.push_back(step);
    }

    void executeFlow() {
        if (steps.empty()) {
            cout << "No steps available!" << endl;
            return;
        }

        do {
            cout << "Available steps:\n";
            for (size_t i = 0; i < steps.size(); ++i) {
                cout << i + 1 << ". ";
                steps[i]->display();
            }

            int choice;
            cout << "Choose a step (enter the step number): ";
            cin >> choice;

            if (choice > 0 && choice <= static_cast<int>(steps.size())) {
                cout << "Selected Step: " << choice << endl;
                if(steps[choice - 1]->getClassName() == "Display" || steps[choice - 1]->getClassName() == "Calculus") {
                    steps[choice - 1]->getFlow(steps);
                }
                steps[choice - 1]->inputAttributes();
                steps[choice - 1]->displayAttributes();
               
            } else {
                cout << "Invalid choice!" << endl;
            }

            char character;
            cout << "Do you want to continue? Y/N" << endl;
            cin >> character;

            if (character == 'y' || character == 'Y'){
                continue;
            } else if (character == 'n' || character == 'N') {
                break; // Exit loop if 'n' or 'N' is entered
            }

        } while (true); // Loop indefinitely until 'n' or 'N' is entered
    }
};

int main() {

    string userTitle, userSubtitle;

    Title* step1 = new Title();
    Text* step2 = new Text();
    Text_Input* step3 = new Text_Input();
    Number_Input* step4 = new Number_Input();
    Calculus* step5 = new Calculus();
    Display* step6 = new Display();
    Text_File* step7 = new Text_File();
    CSV_File* step8 = new CSV_File();
    Output* step9 = new Output();
    End* step10 = new End();

    Flow flow1;

    flow1.addStep(step1);
    flow1.addStep(step2);
    flow1.addStep(step3);
    flow1.addStep(step4);
    flow1.addStep(step5);
    flow1.addStep(step6);
    flow1.addStep(step7);
    flow1.addStep(step8);
    flow1.addStep(step9);
    flow1.addStep(step10);

    // Execute the predefined flow (Flow1)
    flow1.executeFlow();

    // Additional flows customized by users
    std::vector<Flow> customizedFlows;

    int numCustomFlows;
    std::cout << "Enter the number of custom flows to create: ";
    std::cin >> numCustomFlows;

    for (int i = 0; i < numCustomFlows; ++i) {
        Flow customFlow;

        int numSteps;
        std::cout << "Enter the number of steps for custom flow " << i + 1 << ": ";
        std::cin >> numSteps;

        std::cout << "Available steps:\n";
        std::cout << "1. Title\n";
        std::cout << "2. Text\n";
        std::cout << "3. Text Input\n";
        std::cout << "4. Number Input\n";
        std::cout << "5. Calculus\n";
        std::cout << "6. Display\n";
        std::cout << "7. Text File\n";
        std::cout << "8. CSV File\n";
        std::cout << "9. Output\n";
        std::cout << "10. End\n";

        for (int j = 0; j < numSteps; ++j) {

            int stepChoice;
            std::cout << "Choose step " << j + 1 << " for custom flow " << i + 1 << ": ";
            std::cin >> stepChoice;

             // Create steps based on user input and add them to customFlow using customFlow.addStep(step);

            Step* newStep = nullptr;

            switch (stepChoice) {
                case 1:
                    newStep = new Title();
                    break;
                case 2:
                    newStep = new Text();
                    break;
                case 3:
                    newStep = new Text_Input();
                    break;
                case 4:
                    newStep = new Number_Input();
                    break;
                case 5:
                    newStep = new Calculus();
                    break;
                case 6:
                    newStep = new Display();
                    break;
                case 7:
                    newStep = new Text_File();
                    break;
                case 8:
                    newStep = new CSV_File();
                    break;
                case 9:
                    newStep = new Output();
                    break;
                case 10:
                    newStep = new End();
                    break;
                default:
                    cout << "Invalid choice!" << endl;
                    break;
            }

            
            if (newStep != nullptr) {
                customFlow.addStep(newStep);
            }
        }

        // Execute custom flow
        customFlow.executeFlow();

        // Store the custom flow in the vector of customized flows
        customizedFlows.push_back(customFlow);

    }


    // Clean up memory
    delete step1;
    delete step2;
    delete step3;
    delete step4;
    delete step5;
    delete step6;
    delete step7;
    delete step8;
    delete step9;
    delete step10;

return 0;

}
