#include<iostream>
#include<vector>
#include<string>
#include<typeinfo>
#include<algorithm>
#include<cctype>
#include<fstream>
#include<limits>
#include <unordered_map>


using namespace std;


//main step class

class Step {
private:
int countErr = 0;

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

    int getcountErr() {
        return countErr;
    }

    void displayErrors(){
        cout << "\n\n ---------------------Error---------------------\n\n";
        countErr ++;
    };

    virtual void addText() = 0;

    virtual ~Step() {}
};

//title class, the user adds title and subtitle

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
        try {
            cout << "Title: ";
            cin >> title;

            if(typeid(title)!=typeid(string)){
                throw "Title is string!";
            }

            cout << "Subtitle: ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            getline(cin, subtitle);

            if(typeid(subtitle)!=typeid(string)){
                throw "Subtitle is string!";
            }
            
        } catch (const string e) {
            displayErrors();
            cerr << "Error: " << e << endl;
            //cin.clear(); // Clear the error flag
            //cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            // You can choose to rethrow the exception if needed
            // throw; 
        }
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

    void addText() override {}

    ~Title() {}

};


//text class

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
        cin.ignore(); 
        getline(cin, copy);
    }

    void display() override {
        cout << "Type: " << type << endl;
    }

    void displayAttributes() const override {
        cout << "Title: " << title << endl;
        cout << "Copy: " << copy << endl;
    }

    void addText() override {}

    ~Text() {}

};

//text input class
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
        cin.ignore(); 
        getline(cin, textInput);
    }

     void displayAttributes() const override {
        cout << "Description: " << description << endl;
        cout << "Text Input: " << textInput << endl;
    }

    void display() override {
        cout << "Type: " << type << endl;
    }

    void addText() override{}

    ~Text_Input() {}
};

//number input class

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
       try {
            std::cout << "Description: ";
            std::cin >> description;

            std::cout << "Number input: ";
            std::cin >> stringInput;

            size_t pos;
            numberInput = std::stof(stringInput, &pos);

            if (pos != stringInput.length()) {
                throw std::invalid_argument("Invalid input. Please enter a valid number.");
            }

        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            displayErrors();
        }
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

    void addText() override {}

    ~Number_Input() {}
};

//calculus class

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

    void addText() override {}
    

    ~Calculus() {}
};

//display class

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
        cout << "\nStep: " << step << endl;
    }

    void addText() override{}

    ~Display() {}
};

//text file class

class Text_File : public Step{

    private:
    string description;
    string fileName;
    string className = "Text File";
    string filePath;
    ofstream fileStream;

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

     void createFile() {
        filePath = "files/" + fileName; // Assuming the files are in a directory named "files"
        ofstream file_out(filePath.c_str());

        // Check if the file was successfully created
        if (!file_out) {
            throw std::runtime_error("File could not be created");
        }

        // Write to the file
        if (description != "") {
            file_out << "Description: " << description << endl;
        }
        file_out << "File name: " << fileName << endl;

        // Close the file
        file_out.close();
    }

    void addText() override {
        ofstream file_out(filePath.c_str(), std::ios_base::app); // Open in append mode

        if (!file_out) {
            throw std::runtime_error("File could not be opened for appending");
        }

        cout << "Enter text for the file (type 'exit' on a new line to finish):\n";
        string line;

        while (getline(cin, line) && line != "exit") {
            file_out << line << endl;
        }

        file_out.close();
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

//csv file class

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

    void addText() override {}

    ~CSV_File() {}
};

//output class

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
    
    void addText() override {}

    ~Output() {}
};

//end class

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

    void addText() override{}

    ~End() {}
};

//analytics class


class Analytics {
private:
    int flowStartedCount;
    int flowCompletedCount;
    std::unordered_map<std::string, int> screenSkippedCount;
    std::unordered_map<std::string, int> errorScreenCount;
    int totalErrors;
    int totalCompletedFlows;
    std::vector<Step*> steps; // Vector of Step pointers
    

public:
    Analytics() : flowStartedCount(0), flowCompletedCount(0), totalErrors(0), totalCompletedFlows(0) {}

    void getFlow(vector<Step*> steps) {

        this->steps = steps;

    }

    void flowStarted() {
        flowStartedCount++;
    }

    void flowCompleted(bool hasErrors) {
        flowCompletedCount++;
        totalCompletedFlows++;

        if (hasErrors) {
            totalErrors++;
        }
    }

    void screenSkipped(const std::string& screenName) {
        screenSkippedCount[screenName]++;
    }

    float errorScreenDisplayed() const{
        int totalErrors = 0;
        int numberSteps = 0;
        for(auto const element: steps){
           totalErrors += element->getcountErr();
        }
        
        numberSteps = static_cast<int>(steps.size());
        

        return(float)(totalErrors/numberSteps);
        
    }

    void displayAnalytics() const {
        cout << "\n\n ---------------------Analytics---------------------\n\n" << endl;
        std::cout << "Flow started count: " << flowStartedCount << std::endl;
        std::cout << "Flow completed count: " << flowCompletedCount << std::endl;
        std::cout << "Average number of errors per flow completed: " << errorScreenDisplayed() << std::endl;

        std::cout << "Screen skipped count:\n";
        for (const auto& entry : screenSkippedCount) {
            std::cout << entry.first << ": " << entry.second << std::endl;
        }

        std::cout << "Error screen count:\n";
        for (const auto& entry : errorScreenCount) {
            std::cout << entry.first << ": " << entry.second << std::endl;
        }
    }
};

//flow class

class Flow{
private:
    std::vector<Step*> steps; // Vector of Step pointers
    Analytics analytics;

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

    Analytics& getAnalytics() {
        return analytics;
    }

    const Analytics& getAnalytics() const {
        return analytics;
    }

    void executeFlow() {
        analytics.flowStarted(); // Increment flowStartedCount
        if (steps.empty()) {
            cout << "No steps available!" << endl;
            return;
        }

        do {
            cout << "\n\n ---------------------Flow---------------------\n\n" << endl;
            cout << "Available steps:\n";
            for (size_t i = 0; i < steps.size(); ++i) {
                cout << i + 1 << ". ";
                steps[i]->display();
            }

            int choice;
            cout << "\n" << endl;
            cout << "Choose a step (enter the step number): ";
            cin >> choice;

            if (choice > 0 && choice <= static_cast<int>(steps.size())) {
                cout << "Selected Step: " << choice << endl;
                // if(steps[choice - 1]->getClassName() == "Display" || steps[choice - 1]->getClassName() == "Calculus") {
                //     steps[choice - 1]->getFlow(steps);
                // }
                steps[choice - 1]->inputAttributes();
                steps[choice - 1]->displayAttributes();

                //analytics.screenSkipped(steps[choice - 1]->getClassName()); // Increment screenSkippedCount
               
            } else {
                cout << "Invalid choice!" << endl;
            }

            char character;
            cout << "Do you want to continue? Y/N" << endl;
            cin >> character;

            if (character == 'y' || character == 'Y'){
                continue;
            } else if (character == 'n' || character == 'N') {
                break; 
            }

        } while (true); 

        analytics.getFlow(steps);

        analytics.flowCompleted(false); // Assuming no errors for now
        analytics.displayAnalytics(); // Display analytics before exiting
    }
};


int main() {


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

    // Additional flows customized by users
    std::vector<Flow> customizedFlows;
    std::vector<Step*> steps;

    int numCustomFlows;
    cout << "---------------------Number of Flows---------------------\n\n" << endl;
    std::cout << "Enter the number of custom flows to create: ";
    std::cin >> numCustomFlows;
    cout << "\n\n" << endl;

    for (int i = 0; i < numCustomFlows; ++i) {
        Flow customFlow;

        int numSteps;
        cout << "---------------------Flow---------------------\n\n" << endl;
        std::cout << "Enter the number of steps for custom flow " << i + 1 << ": ";
        std::cin >> numSteps;
        cout << "\n\n" << endl;

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
        std::cout << "10. End\n\n\n";

        cout << "---------------------Step---------------------\n\n" << endl;

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

          // Display analytics for customized flows
        for (const Flow& customFlow : customizedFlows) {
            customFlow.getAnalytics().displayAnalytics();
        }

        // Store the custom flow in the vector of customized flows
        customizedFlows.push_back(customFlow);

    }


return 0;

}