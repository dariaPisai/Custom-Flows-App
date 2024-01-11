 int main() {
    
    std::vector<Flow> flows;
    char addAnotherFlow;
  do {
        Flow newFlow;

        std::cout << "Creating predefined steps for the new flow...\n";

        // Creating instances of Step1, Step2, etc.

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


        // Adding steps to the flow
        newFlow.addStep(step1);
        newFlow.addStep(step2);
        newFlow.addStep(step3);
        newFlow.addStep(step4);
        newFlow.addStep(step5);
        newFlow.addStep(step6);
        newFlow.addStep(step7);
        newFlow.addStep(step8);
        newFlow.addStep(step9);
        newFlow.addStep(step10);

        cout << "Predefined steps added to the new flow. Now creating steps...\n";

    // User-defined steps for each flow

        cout << "How many steps do you want to add to this flow? ";
        int numSteps;
        cin >> numSteps;
        cin.ignore(); // Clear the input buffer

        for (int i = 0; i < numSteps; ++i) {
            Step* step = new Step();
            newFlow.addStep(step);
        }

        cout << "Steps created for the new flow. Now reorder the steps:\n";
        newFlow.executeFlow();

        flows.push_back(newFlow);

        cout << "Do you want to add another flow? (Y/N): ";
        cin >> addAnotherFlow;
        cin.ignore(); // Clear the input buffer

    } while (addAnotherFlow == 'Y' || addAnotherFlow == 'y');

    return 0;
 }