/* 
 * File:   AP Physics Calculator.c
 * Author: Oscar Song
 * Status: DONE
 * Created on June 4, 2020, 2:40 PM
 */

#include <stdio.h>
#include <stdlib.h>
// include a math library in C to perform sqrt and trigonometric operations
#include <math.h>

// Global Variables

    const int NUM_OF_UNITS = 7;
    const int NUM_OF_UNIT_TOPICS = 3;
    const int NUM_OF_UNIT_TOPICS_CALCULATION = 4;
    const int NUM_OF_ABBREVIATIONS = 16;
    const int NUM_OF_UNCOVERED_TOPICS = 7;
    const int NUM_OF_QUANTITY_UNITS = 16;
    const double piApproximation = 3.14159265358979323846;
    const double universalGravitationalConstantApproximation = 0.0000000000667;

/*
 * Purpose: Display the units covered by this calculator
 * Parameters: unitChoice[]
 * Side Effect: NONE
 */
void displayUnits(char* const unitChoice[]){
    int unitNumber = 0;
    printf("\nThis calculator will cover the following units:");
    for (unitNumber = 0; unitNumber < NUM_OF_UNITS; unitNumber ++){
        printf("\n%d: %s ", unitNumber + 1, unitChoice[unitNumber]);
    }
}
/*
 * Purpose: Display the topics of a unit
 * Parameters: unitTopics[]
 * Side Effect: NONE
 */
void displayUnitTopics(char* const unitTopics[], int unitNumber){
    int topicNumber = 0;
    printf("\nUnit %d has the following topics: ", unitNumber);
    for (topicNumber = 0; topicNumber < NUM_OF_UNIT_TOPICS; topicNumber++){
        printf("\n%d: %s", topicNumber + 1, unitTopics[topicNumber]);
    }
}

/*
 * Purpose: Display the calculation choices for each topic of a unit
 * Parameters: unitTopicsCalculations[]
 * Side Effect: NONE
 */
void displayTopicChoice(char* const unitTopicsCalculations[], int topicNumber){
    int choiceNumber = 0;
    printf("\nTopic %d has the following calculations: ", topicNumber);
    for (choiceNumber = 0; choiceNumber < NUM_OF_UNIT_TOPICS_CALCULATION; choiceNumber++){
        printf("\n%d: %s", choiceNumber + 1, unitTopicsCalculations[choiceNumber]);
    }
}

/*
 * Purpose: Get menu choice from the user 
 * Parameters: int lowerBound, int upperBound, char* question (unit/calculations/topic)
 * Side Effect: NONE
 */
int getMenuChoice(int lowerBound, int upperBound, char* question){
    
    int usersChoice = 0;
    printf("\n\nPlease indicate the %s using the menu below [%d-%d]: ", question, lowerBound, upperBound);
    scanf("%d", &usersChoice);
    fgetc(stdin);
    
    while ((usersChoice < lowerBound) || (usersChoice > upperBound)) {
        printf("\nYour input of %d is invalid. Please input a valid choice: ", usersChoice);
        scanf("%d", &usersChoice);
        fgetc(stdin);
    }
    return usersChoice;
}

/*
 * Purpose: Get a vector quantity from the user
 * Parameters: char* vectorName
 * Side Effect: NONE
 */
double getVectorQuantity(char* vectorName){
    double vectorQuantity = 0.0;
    printf("\nPlease enter the %s: ", vectorName);
    scanf("%lf", &vectorQuantity);
    fgetc(stdin);
    
    return vectorQuantity;
   
}

/*
 * Purpose: Get a scalar quantity from the user
 * Parameters: char* scalarName
 * Side Effect: NONE
 */
double getScalarQuantity(char* scalarName){
    double scalarQuantity = 0.0;
    printf("\nPlease input the %s: ", scalarName);
    scanf("%lf", &scalarQuantity);
    fgetc(stdin);
    // scalar quantity must be greater than or equal to 0 (work is an exception but is treated differently later)
    while (scalarQuantity < 0){
        printf("\nYour input of %1.2lf is invalid. Please try again!", scalarQuantity);
        printf("\nPlease input the %s: ", scalarName);
        scanf("%lf", &scalarQuantity);
        fgetc(stdin);
    }
    return scalarQuantity;
}

/*
 * Purpose: To calculate the change in quantity
 * Parameters: double initialQuantity, double finalQuantity
 * Side Effect: NONE
 */ 
double calcChangeInQuantity(double initialQuantity, double finalQuantity){
    double changeInQuantity = 0.0;
    changeInQuantity = finalQuantity - initialQuantity;
    return changeInQuantity;
}

/*
 * Purpose: Figure out the variable that is not given
 * Parameters: char* variable (name of the variable)
 * Side Effect: NONE
 */
char getYesOrNoAnswer(char* variable){
    char yesOrNo = 'K';
    printf("\nAre you given the %s [y/Y/n/N]: ", variable);
    scanf("%c", &yesOrNo);
    fgetc(stdin);
    // check invalid input
    while ((yesOrNo != 'y') && (yesOrNo != 'Y') && (yesOrNo != 'n') && (yesOrNo != 'N')){
        printf("\nYour input of %c is invalid. Please try again!", yesOrNo);
        printf("\nAre you given the %s [y/Y/n/N]: ", variable);
        scanf("%c", &yesOrNo);
        fgetc(stdin);
    }
    return yesOrNo;
}

/*
 * Purpose: Figure out the variable that is not given from a list of choices 
 * Parameters: char variable1, char variable2, char variable3, char variable4, char variable5, char* prompt
 * Note: this is only used when there are five variables as a choice, other functions are used for other scenarios
 * Side Effect: NONE
 */
char getUnknownVariable(char variable1, char variable2, char variable3, char variable4, char variable5, char* prompt){
    char unknownVariable = 'K';
    
    printf("\nWhich variable [%c/%c/%c/%c/%c] is not given %s: ", variable1, variable2, variable3, variable4, variable5, prompt);
    scanf("%c", &unknownVariable);
    fgetc(stdin);
        
    while ((unknownVariable != variable1) && (unknownVariable != variable2) && (unknownVariable != variable3) && (unknownVariable != variable4) && (unknownVariable != variable5)){
        printf("\nYour input of %c is invalid. Please try again!", unknownVariable);
        printf("\nWhich variable [%c,%c,%c,%c,%c] is not given %s: ", variable1, variable2, variable3, variable4, variable5, prompt);
        scanf("%c", &unknownVariable);
        fgetc(stdin);
    }
    
    return unknownVariable;
}

/*
 * Purpose: determine the unknown variable
 * Parameters: char variable1, char variable2, char variable3, char variable4, char* prompt
 * Note: this is used only when there are 4 variables as a choice
 * Side Effect: NONE
 */
char getUnknownVariable3(char variable1, char variable2, char variable3, char variable4, char* prompt){
    char unknownVariable = 'K';
    printf("\nWhich variable [%c/%c/%c/%c] is not given %s: ", variable1, variable2, variable3, variable4, prompt);
    scanf("%c", &unknownVariable);
    fgetc(stdin);
    
    while ((unknownVariable != variable1) && (unknownVariable != variable2) && (unknownVariable != variable3) && (unknownVariable != variable4)){
        printf("\nYour input of %c is invalid. Please try again!", unknownVariable);
        printf("\nWhich variable [%c/%c/%c/%c] is not given %s: ", variable1, variable2, variable3, variable4, prompt);
        scanf("%c", &unknownVariable);
        fgetc(stdin);
    }
    return unknownVariable;
}

/*
 * Purpose: Tell the user that a variable is undefined
 * Parameters: char* quantity (name of the quantity)
 * Side Effect: NONE
 */
void undefinedNotice(char* quantity){
    printf("\nThe %s is undefined! Zero and i are special numbers - Mr. John Doma", quantity);
}

/*
 * Purpose: Calculate the discriminant (I generalized the function to calculate the value under the square root of any expression)
 * Parameters: double coefficient1, double coefficient2, double coefficient3
 * Side Effect: NONE
 */
double calcDiscriminant(double coefficient1, double coefficient2, double coefficient3){
    double discriminant = 0.0;
    discriminant = (coefficient2 * coefficient2) - 4*(coefficient1 * coefficient3);
    return discriminant;
}

/*
 * Purpose: Calculate the first root of a quadratic equation
 * Parameters: double coefficient1, double coefficient2, double coefficient3
 * Side Effect: NONE
 */
double calcRoot1(double coefficient1, double coefficient2, double coefficient3){
    double root1 = 0.0;
    
    root1 = ((coefficient2*(-1)) + sqrt((coefficient2 * coefficient2) - (4 * coefficient1 * coefficient3)))/(2*coefficient1);
    return root1; 
}

/*
 * Purpose: Calculate the second root of a quadratic equation
 * Parameters: double coefficient1, double coefficient2, double coefficient3
 * Side Effect: NONE
 */
double calcRoot2(double coefficient1, double coefficient2, double coefficient3){
    double root2 = 0.0;
    root2 = ((coefficient2*(-1)) - sqrt((coefficient2 * coefficient2) - (4 * coefficient1 * coefficient3)))/(2*coefficient1);
    return root2; 
    
}

/*
 * Purpose: Determine the unknown variable 
 * Parameters: char variable1, char variable2, char variable3
 * Note: this function is used when there's 3 unknown variables only
 * Side Effect: NONE
 */
char getUnknownVariable2(char variable1, char variable2, char variable3){
    char unknownVariable = 'K';
    printf("\nWhich variable [%c/%c/%c] are you asked to find: ", variable1, variable2, variable3);
    scanf("%c", &unknownVariable);
    fgetc(stdin);
    
    while ((unknownVariable != variable1)&&(unknownVariable != variable2)&&(unknownVariable != variable3)){
        printf("\nYour input of %c is invalid. Please try again!", unknownVariable);
        printf("\nWhich variable [%c/%c/%c] are you asked to find: ", variable1, variable2, variable3);
        scanf("%c", &unknownVariable);
        fgetc(stdin);
    }
    return unknownVariable;
}
void displayAnswer(char* answerTopic, double answer){
    printf("\nThe %s is %1.2lf", answerTopic, answer);
}

/*
 * Purpose: Get the angle from the user in degrees
 * Parameters: char* angleLocation
 * Note: this function is tweaked slightly to better suit the physics context with certain restrictions on the angle
 * Side Effect: NONE
 */

double getAngleInDegrees(char* angleLocation){
    double angle = 0;
    printf("\nPlease enter the %s in degrees (counter clock wise is positive): ", angleLocation);
    scanf("%lf", &angle);
    fgetc(stdin);
    
    while ((angle<-180)||(angle>180)){
        printf("\nYou input of %1.2lf degrees is invalid in this context.", angle);
        printf("\nPlease enter the %s in degrees (counter clock wise is positive): ", angleLocation);
        scanf("%lf", &angle);
        fgetc(stdin);
    }
    return angle;

}

/*
 * Purpose: Get the angle from the user in radians
 * Parameters: char* angleLocation
 * Note: this function is tweaked slightly to better suit the physics context with certain restrictions on the angle
 * Side Effect: NONE
 */
double getAngleInRadians(char* angleLocation){
    double angle = 0;
    printf("\nPlease enter the %s in radians (counter clock wise is positive): ", angleLocation);
    scanf("%lf", &angle);
    fgetc(stdin);
    
    while ((angle < piApproximation*(-1)) || (angle > piApproximation)){
        printf("\nYou input of %1.2lf radians is invalid in this context.", angle);
        printf("\nPlease enter the %s in radians (counter clock wise is positive): ", angleLocation);
        scanf("%lf", &angle);
        fgetc(stdin);
    }
    return angle;
}

/*
 * Purpose: Convert an angle from degrees to radians
 * Parameters: double angleInDegrees
 * Side Effect: NONE
 */
double convertToRadians(double angleInDegrees){
    double angleInRadians = 0.0;
    double conversionFactor = 0.0;
    conversionFactor = (piApproximation/180);
    angleInRadians = angleInDegrees * conversionFactor;
    return angleInRadians;
    
}

/*
 * Purpose: Calculate the kinetic energy of an object
 * Parameters: char* timeFrame (time the object's quantities are observed)
 * Side Effect: NONE
 */
double calcKineticEnergy(char* timeFrame){
    printf("\nPlease enter the following information about the object %s.\n", timeFrame);
    double kineticEnergy = 0.0;
    double mass = 0.0;
    double constantVelocity = 0.0;
    mass = getScalarQuantity("mass of object");
    constantVelocity = getVectorQuantity("velocity of object");
    kineticEnergy = mass * (constantVelocity * constantVelocity);
    return kineticEnergy;
    
}

/*
 * Purpose: Calculate the gravitational potential energy of an object
 * Parameters: char* timeFrame (time the object's quantities are observed)
 * Side Effect: NONE
 */

double calcGravitationalPotentialEnergy(char* timeFrame){
    printf("\nPlease enter the following information about the object %s.\n", timeFrame);
    double gravitationalPotentialEnergy = 0.0;
    double mass = 0.0;
    double maxHeight = 0.0;
    mass = getScalarQuantity("mass of object");
    maxHeight = getScalarQuantity("potential change in height of object (h)");
    gravitationalPotentialEnergy = (mass * maxHeight * 9.8);
    return gravitationalPotentialEnergy;
}

/*
 * Purpose: Calculate the elastic potential energy of an object
 * Parameters: char* timeFrame (time the object's quantities are observed)
 * Side Effect: NONE
 */
double calcElasticPotentialEnergy(char* timeFrame){
    printf("\nPlease enter the following information about the spring %s.\n", timeFrame);
    double elasticPotentialEnergy = 0.0;
    double springConstant = 0.0;
    double displacement = 0.0;
    springConstant = getScalarQuantity("spring constant");
    displacement = getVectorQuantity("maximum spring displacement");
    elasticPotentialEnergy = 0.5*springConstant*(displacement*displacement);
    return elasticPotentialEnergy;
}

/*
 * Purpose: Calculate the work done by/on an object
 * Parameters: NONE
 * Side Effect: NONE
 */
double calcWork(){
    double appliedForce = 0.0;
    double displacement = 0.0;
    char radians = 'K';
    double angleInRadians = 0.0;
    double angleInDegrees = 0.0;
    double work = 0.0;
    appliedForce = getScalarQuantity("magnitude of applied force");
    displacement = getScalarQuantity("magnitude of displacement");
                        
    radians = getYesOrNoAnswer("angle radians");
                        // get angle in radians
    if ((radians == 'Y')||(radians == 'y')){
        angleInRadians = getAngleInRadians("angle between F and d");
    }
    else{
        angleInDegrees = getAngleInDegrees("angle between F and d");
        angleInRadians = convertToRadians(angleInDegrees);
        }
    work = (appliedForce * displacement) * cos(angleInRadians);
    return work;
    
}
int main(int argc, char** argv){
    
    // define variables
    int usersUnitChoice = 100;
    int usersTopicChoice = 0;
    int usersCalcChoice = 0;
    char* unitChoice[NUM_OF_UNITS] = { "One Dimensional Motion", "Dynamics", "Circular Motion", "Work, Energy, and Power", "Linear and Angular Momentum, Torque, Linear and Angular Impulse", "Simple Harmonic Oscillators", "Newton's Laws of Gravitation, Rotational Inertia, Rolling Motion" };
    char* unitTopics[NUM_OF_UNIT_TOPICS]= { "Calculating fundamental vector quantities (d,v,a)", "Motion with constant acceleration (Big 5 Equation problems)", "Object in Free fall" };
    char* unitTopicsCalculations [NUM_OF_UNIT_TOPICS_CALCULATION] = { "Displacement", "Average Velocity", "Average Acceleration", "Average Speed" };
    int unitNumber = 0;
    int topicNumber = 0;
    double position1 = 0.0;
    double position2 = 0.0;
    double displacement = 0.0;
    int givenDisplacement = 0;
    double averageVelocity = 0.0;
    double changeInTime = 0.0;
    double averageAcceleration = 0.0;
    double changeInVelocity = 0.0;
    int givenChangeInVelocity = 0;
    double initialVelocity = 0.0;
    double finalVelocity = 0.0;
    double distanceTraveled = 0.0;
    double mass = 0.0;
    double netForce = 0.0;
    double averageSpeed = 0.0;
    char unknownVariable = 'K';
    char askedVariable = 'K';
    double v1 = 0.0;
    double v2 = 0.0;
    double d = 0.0;
    double t = 0.0;
    double a = 0.0;
    double discriminant = 0.0;
    double coefficient1 = 0.0;
    double coefficient2 = 0.0;
    double coefficient3 = 0.0;
    double time1 = 0.0;
    double time2 = 0.0;
    char staticFriction = 'K';
    double normalForce = 0.0;
    double coefficientOfFriction = 0.0;
    double frictionForce = 0;
    int radians = 0;
    double angleInRadians = 0;
    double angleInDegrees = 0;
    char* angleType = "K";
    double piApproximation = 3.14159265358979323846;
    double maxHeight = 0.0;
    double horizontalRange = 0.0;
    double angularDisplacement = 0.0;
    double angularVelocity = 0.0;
    double initialAngularPosition = 0.0;
    double finalAngularPosition = 0.0;
    double initialAngularVelocity = 0.0;
    double finalAngularVelocity = 0.0;
    double angularAcceleration = 0.0;
    char givenAngularDisplacement = 'K';
    char givenDeltaAngularVelocity = 'K';
    double changeInAngularVelocity = 0.0;
    char givenAngularVelocity = 'K';
    double radius = 0.0;
    double centripetalAcceleration = 0.0;
    double tangentialVelocity = 0.0;
    double speed = 0.0;
    double distance = 0.0;
    double tangentialAcceleration = 0.0;
    double centripetalForce = 0.0;
    double appliedForce = 0.0;
    double work = 0.0;
    double constantVelocity = 0.0;
    double kineticEnergy = 0.0;
    char* objectName = "K";
    double gravitationalPotentialEnergy = 0.0;
    double springConstant = 0.0;
    double elasticPotentialEnergy = 0.0;
    double initialKineticEnergy1 = 0.0;
    double initialPotentialEnergy1 = 0.0;
    double finalKineticEnergy1 = 0.0;
    double finalPotentialEnergy1 = 0.0;
    double initialElasticPotentialEnergy1 = 0.0;
    double nonConservativeWork = 0.0;
    char givenWork = 'K';
    double power = 0.0;
    double momentum = 0.0;
    double givenSpeed = 0.0;
    double angularMomentum = 0.0;
    char givenI = 'K';
    double rotationalInertia = 'K';
    double torque = 0.0;
    double linearImpulse = 0.0;
    double angularImpulse = 0.0;
    double restorativeForce = 0.0;
    double period = 0.0;
    double lengthOfString = 0.0;
    double objectMass1 = 0.0;
    double objectMass2 = 0.0;
    double gravitationalForce = 0.0;
    double gravitationalPotentialEnergyBeyondEarth = 0.0;
    double rotationalKineticEnergy = 0.0;
    int counter = 0;
    char givenUnits = 'K';
    char* abbreviations[NUM_OF_ABBREVIATIONS] = {"a: acceleration", "v: initial velocity", "V: final velocity", "d: displacement", 
    "t: change in time", "m: mass", "F: net/restorative spring force", "N: normal force", "f: force of friction", "u: coefficient of friction",
    "y/Y: yes", "n/N: no", "H: maximum height", "R: horizontal range(projectile motion)/radius(rotational motion)", "I: rotational inertia",
    "k: spring constant"};
    char* uncoveredTopics[NUM_OF_UNCOVERED_TOPICS] = {"Problem Solving with Newton's 2nd Law", "Tension Problems", "Collision and Reaction Time Problems", 
    "Conservation of Energy Application", "Conservation of Momentum Application", "Conservation of Angular Momentum Application", "Center of Mass Calculations"};
    char* units[NUM_OF_QUANTITY_UNITS] = {"Mass: Kg", "v/V: m/s", "a: m/s/s", "d: m", "t: s", "F/f/N: Newton", "u: Unitless", "Period: s", "Torque: Nm", "Work: J", 
    "Horizontal Range: m", "Radius: m", "Spring Constant: N/m or Kg/s/s", "Rotational Inertia: kg/m^2", "Kinetic/Potential/Elastic Energy: J or Kg m^2/s^2", "Power: Watt"};

    while (usersUnitChoice != 0){
        // welcome statement
        printf("\n---------------------------AP PHYSICS MASTER-------------------------------\n");//I added this line to prevent confusion and make it 
        // it clear where the start of the program is as it would be hard to tell once the looping starts.
        printf("\nWelcome to the AP Physics I 2020 Master Word Problem Calculator!\n\n");
        printf("Please note that this calculator will cover all essential topics\n");
        printf("that will help you calculate all essential quantities in AP Physics 1\n");
        printf("2020.\n\n");

        // state abbreviations
        printf("For simplicity and uniformity, this program uses the following abbreviations:\n");
        
        for (counter = 0; counter < NUM_OF_ABBREVIATIONS; counter++){
            printf("  - %s\n", abbreviations[counter]);
        }
        // reset counter
        counter = 0;
        // state uncovered topics
        printf("\nThe program does NOT cover explicitly the following concepts:\n");

        for (counter = 0; counter < NUM_OF_UNCOVERED_TOPICS; counter++){
            printf("  - %s\n", uncoveredTopics[counter]);
        }

        // specify to user that units are not provided 
        printf("\nThe program does not specify the units of calculation due to the large\n");
        printf("variety of possible units for each physical concept. Please refer to\n");
        printf("the ultimate unit list at the end of program for common units!\n\n");
        printf("KEY TO REMEMBER: Units must be CONSISTENT!!\n");

        // display the units
        displayUnits(unitChoice);

        // get users choice of unit
        printf("\n\nIf you want to quit the program, enter 0, otherwise choose a unit.");
        usersUnitChoice = getMenuChoice(0,7, "unit or quit");

        // user chooses the first unit (one dimensional motion)
        if (usersUnitChoice == 1){ 

            // display the topics of unit 1
            unitNumber = 1; 
            displayUnitTopics(unitTopics, unitNumber);
            // get users choice 
            usersTopicChoice = getMenuChoice(1, 3, "topic");
            // the user chooses the first topic for unit 1 (basic vector quantity computations)
            if (usersTopicChoice == 1){
                // display the quantities that can be calculated for topic 1
                topicNumber = 1; 
                displayTopicChoice(unitTopicsCalculations, topicNumber);
                // get users choice of which quantity they want to calculate
                usersCalcChoice = getMenuChoice(1, 4, "calculation");   
                // user chooses to calculate displacement
                if (usersCalcChoice == 1){
                    // get initial and final position
                    position1 = getVectorQuantity("initial position");
                    position2 = getVectorQuantity("final position");
                    // calculate displacement
                    displacement = calcChangeInQuantity(position1, position2);
                    // print out answer
                    displayAnswer("displacement of the object", displacement);
                }

                else{
                    // user chooses to calculate average velocity
                    if (usersCalcChoice == 2){
                        // ask if user is given displacement
                        givenDisplacement = getYesOrNoAnswer("displacement");

                        // user is already given displacement
                        if ((givenDisplacement == 'Y') || (givenDisplacement == 'Y')){
                            displacement = getVectorQuantity("displacement");
                        }
                        else{
                            // user is not given displacement but given final and initial position
                            position1 = getVectorQuantity("initial position");
                            position2 = getVectorQuantity("final position");
                            // calculate displacement
                            displacement = calcChangeInQuantity(position1, position2);

                        }
                        // get the change in time
                        changeInTime = getScalarQuantity("change in time");

                        if (changeInTime == 0){
                            // average velocity is not defined if change in time is 0
                            undefinedNotice("average velocity");
                            }

                        else{
                            // calculate average velocity
                            averageVelocity = displacement/changeInTime;
                            displayAnswer("average velocity of the object", averageVelocity);
                            }
                    }
                    else{
                        // user choose to calculate average acceleration
                        if (usersCalcChoice == 3){
                            // ask if user is given change in velocity
                            givenChangeInVelocity = getYesOrNoAnswer("change in velocity");
                            // user is given change in velocity
                            if ((givenChangeInVelocity == 'Y') || (givenChangeInVelocity == 'y')){
                                changeInVelocity = getVectorQuantity("change in velocity");
                            }

                            else{
                                // user is not given change in velocity: calculate it first
                                initialVelocity = getVectorQuantity("initial velocity");
                                finalVelocity = getVectorQuantity("final velocity");
                                changeInVelocity = calcChangeInQuantity(initialVelocity, finalVelocity);
                            }
                            // get change in time
                            changeInTime = getScalarQuantity("change in time");

                            // average acceleration is undefined
                            if (changeInTime == 0){
                                undefinedNotice("average acceleration");
                            }
                            // average acceleration is defined
                            else{
                                // calculate average acceleration
                                averageAcceleration = changeInVelocity/changeInTime;
                                displayAnswer("average acceleration of the object", averageAcceleration);
                            }   
                        }
                        // user wants to calculate average speed
                        else{
                            // get distance traveled and change in time from user
                            distanceTraveled = getScalarQuantity("distance traveled");
                            changeInTime = getScalarQuantity("change in time");

                            // average speed is undefined
                            if (changeInTime == 0){
                                undefinedNotice("average speed");
                            }
                            // average speed is defined
                            else{
                                // calculate average speed
                                averageSpeed = distanceTraveled/changeInTime;
                                displayAnswer("The average speed of the object", averageSpeed);
                            }
                        }    
                    }
                }
            }  
            else{
                // user chooses topic 2 (kinematic equations) or 3 (free fall with kinematic equations)
                if ((usersTopicChoice == 2)||(usersTopicChoice == 3)){
                    // remind user the acceleration in all free fall scenarios

                    if (usersTopicChoice == 2){
                        // get the variable that is not included in the question
                        unknownVariable = getUnknownVariable('a', 'v', 'V', 'd', 't', "and not asked to find");
                        // ask for the variable that is not given but is asked by the question
                        askedVariable = getUnknownVariable('a', 'v', 'V', 'd', 't', "but asked to find");

                    }
                    else{
                        printf("\nThe acceleration in all free fall problems is -9.81 m/s squared!");
                        unknownVariable = getUnknownVariable3('v', 'V', 'd', 't', "and not asked to find");
                        askedVariable = getUnknownVariable3('v', 'V', 'd', 't', "but asked to find");
                    }

                    // displacement is not relevant in the question
                    if (unknownVariable == 'd'){

                        // the user is required to find the final velocity
                        if (askedVariable == 'V'){
                            // get the other essential quantities
                            v1 = getVectorQuantity("initial velocity");
                            a = getVectorQuantity("acceleration");
                            t = getScalarQuantity("change in time");
                            // calculate final velocity
                            v2 = v1+a*t;
                            displayAnswer("final velocity", v2);
                        }
                        else{
                            // the user is asked to find initial velocity
                            if (askedVariable == 'v'){ 
                                // get other essential quantities
                                v2 = getVectorQuantity("final velocity");
                                a = getVectorQuantity("acceleration");
                                t = getScalarQuantity("change in time");
                                // calculate initial velocity
                                v1 = v2 - a*t;
                                displayAnswer("initial velocity", v1);                
                            }
                            else{
                                // the user is asked to find the acceleration
                                if (askedVariable == 'a'){
                                    // get other essential quantities
                                    v2 = getVectorQuantity("final velocity");
                                    v1 = getVectorQuantity("initial velocity");
                                    t = getScalarQuantity("change in time");
                                    // undefined acceleration if dividing by 0
                                    if (t == 0){
                                        undefinedNotice("acceleration");
                                    }
                                    else{
                                        // defined: calculate acceleration
                                        a = (v2-v1)/t;
                                        displayAnswer("acceleration", a);
                                    }
                                }
                                else{
                                    // the user is being asked to find the change in time
                                    v2 = getVectorQuantity("final velocity");
                                    v1 = getVectorQuantity("initial velocity");
                                    a = getVectorQuantity("acceleration");
                                    // a = 0: change in time is undefined
                                    if (a == 0){
                                        undefinedNotice("change in time");
                                    }
                                    else{
                                        // a is non zero, calculate change in time
                                        t = (v2-v1)/a; 
                                    }
                                    // change in time is negative: does not make physical sense
                                    if (t<0){
                                        printf("\nChange in time cannot be negative!");
                                        printf("\nPlease check the values of each variable!");
                                    }
                                    // change in time is positive: plausible answer
                                    else{
                                        displayAnswer("change in time", t);
                                    }
                                }
                            }
                        }  
                    }
                    else{
                        // acceleration is not involved in problem
                        if (unknownVariable == 'a'){
                            // user is asked to find displacement
                            if (askedVariable == 'd'){
                                // get essential quantities
                                v1 = getVectorQuantity("initial velocity");
                                v2 = getVectorQuantity("final velocity");                   
                                t = getScalarQuantity("change in time");
                                // calculate displacement
                                d = ((v1+v2)/2)*t;
                                displayAnswer("displacement", d);                       
                            } 
                            else{
                                // user is asked to find initial velocity
                                if (askedVariable == 'v'){
                                    // get essential quantities
                                    v2 = getVectorQuantity("final velocity");                   
                                    t = getScalarQuantity("change in time");
                                    d = getVectorQuantity("displacement");
                                    // calculate the initial velocity
                                    v1 = ((d/t)*2)-v2; 
                                    displayAnswer("initial velocity", v1);                                                      
                                }
                                else{
                                    // user is asked to find final velocity
                                    if (askedVariable == 'V'){
                                        // find initial quantity
                                        v1 = getVectorQuantity("initial velocity");            
                                        t = getScalarQuantity("change in time");
                                        d = getVectorQuantity("displacement");
                                        // find the final quantity
                                        v2 = ((d/t)*2)-v1; 
                                        displayAnswer("final velocity", v2);                                
                                    }
                                    else{
                                        // user is asked to find the change in time
                                        if (askedVariable == 't'){
                                            // get the essential quantities
                                            v1 = getVectorQuantity("initial velocity");            
                                            v2 = getVectorQuantity("final velocity");               
                                            d = getVectorQuantity("displacement");

                                            // change in time is not defined if v1+V2 is zero
                                            if ((v1+v2) == 0){
                                                undefinedNotice("change in time");
                                            }
                                            else{
                                                // calculate the change in time
                                                t = (2*d)/(v1+v2);
                                                displayAnswer("change in time", t);
                                            }   
                                        }
                                    }
                                }
                            }
                        }
                        else{
                            // the final velocity is not involved in problem
                            if (unknownVariable == 'V'){
                                // user is asked to find displacement
                                if (askedVariable == 'd'){
                                    // get essential quantities
                                    v1 = getVectorQuantity("initial velocity");                             
                                    a = getVectorQuantity("acceleration");
                                    t = getScalarQuantity("change in time");
                                    // calculate displacement
                                    d = v1*t+0.5*a*(t*t);
                                    displayAnswer("displacement", d);
                                }
                                else{
                                    // the initial velocity is not included in problem
                                    if (askedVariable == 'v'){
                                        // get essential quantities
                                        d = getVectorQuantity("displacement");
                                        a = getVectorQuantity("acceleration");
                                        t = getScalarQuantity("change in time");

                                        // change in time is zero: undefined
                                        if (t == 0){
                                            undefinedNotice("initial velocity");
                                        }
                                        else{
                                            // calculate initial velocity
                                            v1 = d-(0.5*a*(t*t));
                                            v1 = v1/t;
                                            displayAnswer("initial velocity", v1);
                                        }
                                    }
                                    else{
                                        // user is asked to find the acceleration
                                        if (askedVariable == 'a'){
                                            // get essential quantities
                                            v1 = getVectorQuantity("initial velocity");                             
                                            d = getVectorQuantity("displacement");
                                            t = getScalarQuantity("change in time");
                                            // the denominator when calculator is undefined: acceleration is undefined
                                            if ((t*t)==0){
                                                undefinedNotice("acceleration");
                                            }
                                            // calculate acceleration if acceleration is defined
                                            else{
                                                a = 2*(d-v1*t);
                                                a = a/(t*t);
                                                displayAnswer("acceleration", a);
                                            }

                                        }
                                        // user is asked to find the change in time
                                        else{
                                            // get essential quantity
                                            v1 = getVectorQuantity("initial velocity");                             
                                            d = getVectorQuantity("displacement");
                                            a = getVectorQuantity("acceleration");
                                            // find the coefficients of the quadratic expression involving t
                                            coefficient1 = 0.5*a;
                                            coefficient2 = v1;
                                            coefficient3 = d*(-1);
                                            // calculate the discriminant to see if there are solutions first
                                            discriminant = calcDiscriminant(coefficient1, coefficient2, coefficient3);
                                            // discriminant is negative, thus no real solutions
                                            if (discriminant < 0){
                                                undefinedNotice("change in time");
                                            }
                                            // discriminant is positive or zero, thus we can calculate
                                            else{
                                                // calculate the two times 
                                                time1 = calcRoot1(coefficient1, coefficient2, coefficient3);
                                                time2 = calcRoot2(coefficient1, coefficient2, coefficient3);

                                                // if time 1 is positive and time 2 is negative then output time 1
                                                // or if time 1 and time 2 are equal and both positive
                                                if (((time1 > 0)&&(time2 < 0))|| ((time1 > 0)&&(time1 == time2))){
                                                    displayAnswer("change in time", time1);                                            
                                                }
                                                else{
                                                    // if time 2 is positive and time 1 is negative output time 2
                                                    if ((time1 < 0)&&(time2 > 0)){
                                                        displayAnswer("change in time", time2);                                                  
                                                    }
                                                    else{
                                                        // if both times are negative: no solution
                                                        if ((time1 < 0)&&(time2 < 0)){
                                                            printf("\nThere is no possible change in time!");
                                                        }

                                                        else{
                                                            // if both times are positive, the solution is indetermiaent by the program
                                                            // the program will output both possible solutions for user to choose from
                                                            // based on context of the problem
                                                            printf("\nThe two possible times are t = %1.2lf and t = %1.2lf\n", time1, time2);
                                                            printf("Please pick the most appropriate time according to scenario.");
                                                        }
                                                    }
                                                }   
                                            }
                                        }
                                    }
                                }
                            }
                            else{
                                // the initial velocity is not involved in the problem
                                if (unknownVariable == 'v'){
                                    // asked to find displacement
                                    if (askedVariable == 'd'){
                                        // get essential quantities
                                        v2 = getVectorQuantity("final velocity");                           
                                        a = getVectorQuantity("acceleration");
                                        t = getScalarQuantity("change in time");
                                        // calculate displacement
                                        d = (v2*t) - 0.5*a*(t*t);
                                        displayAnswer("displacement", d);                               
                                    }

                                    else{
                                        // asked to find final velocity
                                        if (askedVariable == 'V'){
                                            // get essential quantities
                                            d = getVectorQuantity("displacement");                          
                                            a = getVectorQuantity("acceleration");
                                            t = getScalarQuantity("change in time");     

                                            // if change in time is zero: final velocity is undefined
                                            if (t==0){
                                                undefinedNotice("final velocity");
                                            }
                                            else{
                                                // if final velocity is defined, calculate final velocity
                                                v2 = d + 0.5*a*(t*t);
                                                v2 = v2/t;
                                                displayAnswer("final velocity", v2);                                          
                                            } 
                                        }
                                        else{
                                            // asked to find the acceleration
                                            if (askedVariable == 'a'){
                                                // get essential quantities
                                                d = getVectorQuantity("displacement");                          
                                                v2 = getVectorQuantity("final velocity");        
                                                t = getScalarQuantity("change in time"); 
                                                // change in time is 0: final velocity is undefined
                                                if (t==0){
                                                undefinedNotice("final velocity");
                                                }
                                                else{
                                                    // final velocity is defined: find it
                                                    a = (-2)*(d - v2*t);
                                                    a = a/(t*t);
                                                    displayAnswer("acceleration", a);
                                                }

                                            }
                                            // asked to find change in time
                                            else{
                                                // get essential quantities
                                                v2 = getVectorQuantity("final velocity");                             
                                                d = getVectorQuantity("displacement");
                                                a = getVectorQuantity("acceleration");
                                                // calculate coefficients of the quadratic equation terms involving time
                                                coefficient1 = 0.5*a;
                                                coefficient2 = v2*(-1);
                                                coefficient3 = d;
                                                // calculate the discriminant to determine if there are solutions (Real)
                                                discriminant = calcDiscriminant(coefficient1, coefficient2, coefficient3);

                                                // discriminant is negative, so change in time is not defined
                                                if (discriminant < 0){
                                                    undefinedNotice("change in time");
                                                }
                                                else{
                                                    // change in time is defined for real numbers: calculate the two solutions (or two equal solution)
                                                    time1 = calcRoot1(coefficient1, coefficient2, coefficient3);
                                                    time2 = calcRoot2(coefficient1, coefficient2, coefficient3);

                                                    // time 1 is positive and time 2 is negative: output time 1
                                                    if (((time1 > 0)&&(time2 < 0)) || ((time1 > 0)&&(time1 == time2))){
                                                        displayAnswer("change in time", time1);   
                                                    }
                                                    else{
                                                        // time 1 is negative and time 2 is positive: output time 2
                                                        if ((time1 < 0)&&(time2 > 0)){
                                                            displayAnswer("change in time", time2);
                                                        }
                                                        else{
                                                            // time 1 and time 2 are both negative: not defined
                                                            if ((time1 < 0)&&(time2 < 0)){
                                                                printf("\nThere is no possible change in time!");
                                                            }
                                                            else{
                                                                // both times are positive: requires user to pick best answer base don context
                                                                printf("\nThe two possible times are t = %1.2lf and t = %1.2lf\n", time1, time2);
                                                                printf("Please pick the most appropriate time according to scenario.");
                                                        }
                                                    }
                                                }   
                                            }
                                        }
                                    }
                                }        
                            }
                                else{
                                    // user is asked to find final velocity
                                    if (askedVariable == 'V'){
                                        // get necessary quantities
                                        v1 = getScalarQuantity("initial velocity");                               
                                        d = getVectorQuantity("displacement");
                                        a = getVectorQuantity("acceleration");
                                        // calculate the discriminant
                                        discriminant = (v1*v1)+(2*a*d);
                                        // expression under square root (I call it discriminant for simplicity sake) is less than 0: 
                                        // no real solutions
                                        if (discriminant < 0){
                                            undefinedNotice("final velocity");
                                        }

                                        else{
                                            // final velocity is defined, so calculate it
                                            v2 = sqrt(discriminant);
                                            displayAnswer("final velocity", v2);                                   
                                        }
                                    }
                                    else{
                                        // asked to find initial velocity
                                        if (askedVariable == 'v'){
                                            // get necessary quantities
                                            v2 = getScalarQuantity("final velocity");                               
                                            d = getVectorQuantity("displacement");
                                            a = getVectorQuantity("acceleration");
                                            // determine discriminant (expression under square root in this case)
                                            discriminant = (v2*v2) - (2*a*d);
                                            // initial velocity is not defined (no real solution)
                                            if (discriminant < 0){
                                                undefinedNotice("initial velocity");
                                            }
                                            else{
                                                // initial velocity is defined: find it
                                                v1 = sqrt(discriminant);
                                                displayAnswer("initial velocity", v1); 
                                            }
                                        }
                                        else{
                                            // asked to find acceleration
                                            if (askedVariable == 'a'){
                                                // get necessary quantities
                                                v2 = getScalarQuantity("final velocity");                               
                                                d = getVectorQuantity("displacement");
                                                v1 = getScalarQuantity("initial velocity");  

                                                // acceleration is not defined
                                                if (d == 0){
                                                    undefinedNotice("acceleration");
                                                }
                                                else{
                                                    // find acceleration
                                                    a = (v2*v2)-(v1*v1);
                                                    a = a/(2*d);
                                                    displayAnswer("acceleration", a);                               
                                                }    
                                            }
                                            else{
                                                // asked to find displacement
                                                if (askedVariable == 'd'){
                                                    // get necessary quantities
                                                    v2 = getScalarQuantity("final velocity");                               
                                                    a = getVectorQuantity("acceleration");
                                                    v1 = getScalarQuantity("initial velocity"); 
                                                    // displacement is not defined
                                                    if (a == 0){
                                                        undefinedNotice("displacement");
                                                    }
                                                    else{
                                                        // calculate displacement
                                                        d = (v2*v2)-(v1*v1);
                                                        d = d/(2*a);
                                                        displayAnswer("displacement", d);
                                                    }
                                                }
                                            }
                                        }
                                    }   
                                }
                            }
                        }
                    }   
                }
            }
        } 
        else{
            // User chooses the second unit: dynamics
            if (usersUnitChoice == 2){
                // change unit number
                unitNumber = 2;
                // modify the array
                unitTopics[0] = "Newton's Second Law";
                unitTopics[1] = "Static and Kinetic Friction";
                unitTopics[2] = "Projectile Motion";
                displayUnitTopics(unitTopics, unitNumber);
                // get the user to choose the topic
                usersTopicChoice = getMenuChoice(1, 3, "topic");

                // user chooses Newton's 2nd Law as topic
                if (usersTopicChoice == 1){
                    // ask for the unknown but asked to find variable
                    askedVariable = getUnknownVariable2('F', 'a', 'm');
                    // user is asked to find net force
                    if (askedVariable == 'F'){
                        // get necessary quantities
                        a = getVectorQuantity("acceleration");
                        mass = getScalarQuantity("mass");
                        // calculate net force
                        netForce = mass * a;
                        displayAnswer("net force", netForce);
                    }
                    else{
                        // user is being asked to find acceleration
                        if (askedVariable == 'a'){
                            // get necessary  quantities
                            mass = getScalarQuantity("mass");
                            netForce = getVectorQuantity("net force");
                            // calculate acceleration
                            a = netForce/mass;
                            displayAnswer("acceleration", a);
                        }
                        else{
                            // user is being asked to find mass
                            // get necessary quantities
                            netForce = getVectorQuantity("net force");
                            a = getVectorQuantity("acceleration");
                            // calculate mass
                            mass = netForce/a;
                            displayAnswer("mass", mass);
                        }
                    }
                }
                else{
                    // user chooses questions involving kinetic and static friction
                    if (usersTopicChoice == 2){
                        // ask if it is static friction problems
                        staticFriction = getYesOrNoAnswer("static friction situation");

                        // ask for the variable that is unknown
                        askedVariable = getUnknownVariable2('N', 'f', 'u');
                        // force of friction is unknown
                        if (askedVariable == 'f'){
                            // get necessary quantities
                            normalForce = getVectorQuantity("normal force");
                            coefficientOfFriction = getScalarQuantity("coefficient of friction (u)");
                            // calculate force of friction
                            frictionForce = normalForce * coefficientOfFriction;

                            // display answer
                            if ((staticFriction == 'y')||(staticFriction == 'Y')){
                                displayAnswer("force of static friction", frictionForce);                            
                            }
                            else{
                                displayAnswer("force of kinetic friction", frictionForce);
                            }
                        }
                        else{
                            // asked to find normal force
                            if (askedVariable == 'N'){
                                // get necessary quantities
                                frictionForce = getVectorQuantity("force of friction");
                                coefficientOfFriction = getScalarQuantity("coefficient of friction (u)");
                                // calculate normal force
                                normalForce = frictionForce/coefficientOfFriction;

                                displayAnswer("normal force", normalForce);

                            }
                            else{
                                // asked to find the coefficient of friction
                                frictionForce = getVectorQuantity("force of friction");
                                normalForce = getVectorQuantity("normal force");
                                // calculate coefficient of friction
                                coefficientOfFriction = frictionForce/normalForce;
                                // display answer
                                if ((staticFriction == 'y')||(staticFriction == 'Y')){
                                    displayAnswer("coefficient of static friction", coefficientOfFriction);                            
                                }
                                else{
                                    displayAnswer("coefficient of kinetic friction", frictionForce);
                                }
                            }
                        }

                    }
                    // user chooses projectile motion calculations
                    else{
                        printf("\nAll projectile motion problems will be assumed to be launched\n");
                        printf("on earth with a gravitational field of g = 9.8 m/s/s.\n");
                        // modify array to include calculation choices for projectile motion
                        unitTopicsCalculations[0] = "Time of Flight (t)";
                        unitTopicsCalculations[1] = "Maximum height reached (H)";
                        unitTopicsCalculations[2] = "Horizontal range (R)";
                        unitTopicsCalculations[3] = "Final vertical velocity (V)";
                        // display and get the user choice of calculation variable
                        displayTopicChoice(unitTopicsCalculations, 3);
                        usersCalcChoice = getMenuChoice(1, 4, "calculation");   
                        // user chooses to calculate time of flight
                        if (usersCalcChoice == 1){
                            // get necessary quantities
                            v1 = getVectorQuantity("initial velocity");
                            radians = getYesOrNoAnswer("angle in radians");
                            // get the angle in radians
                            if ((radians == 'Y')||(radians == 'y')){
                                angleInRadians = getAngleInRadians("angle to the horizontal");
                            }
                            else{
                                angleInDegrees = getAngleInDegrees("angle to the horizontal");
                                angleInRadians = convertToRadians(angleInDegrees);
                            }
                            // calculate the time of flight and display answer
                            t = (2*v1*sin(angleInRadians))/9.81;
                            displayAnswer("time of flight", t);
                        }
                        else{
                            // user chooses to calculate maximum height
                            if (usersCalcChoice == 2){
                                // get necessary quantities
                                v1 = getVectorQuantity("initial velocity");
                                // ask if answer is in radians
                                radians = getYesOrNoAnswer("angle radians");
                                // get angle in radians
                                if ((radians == 'Y')||(radians == 'y')){
                                    angleInRadians = getAngleInRadians("angle to the horizontal");
                                }
                                else{
                                    angleInDegrees = getAngleInDegrees("angle to the horizontal");
                                    angleInRadians = convertToRadians(angleInDegrees);
                                }
                                // calculate maximum height and display answer
                                maxHeight = (v1 * v1) * (sin(angleInRadians) * sin(angleInRadians));
                                maxHeight = maxHeight/(2*9.8);
                                displayAnswer("max height", maxHeight);
                            }
                            else{
                                // user chooses to calculate the horizontal displacement/range
                                if (usersCalcChoice == 3){
                                    // get necessary quantity
                                    v1 = getVectorQuantity("initial velocity");
                                    // ask if user have angle in radians or degrees
                                    radians = getYesOrNoAnswer("angle in radians");
                                    // get angle in radians
                                    if ((radians == 'Y')||(radians == 'y')){
                                        angleInRadians = getAngleInRadians("angle to the horizontal");
                                    }
                                    else{
                                        angleInDegrees = getAngleInDegrees("angle to the horizontal");
                                        angleInRadians = convertToRadians(angleInDegrees);
                                    }
                                    // calculate horizontal range and display answer
                                    horizontalRange = (v1 * v1) * (sin(angleInRadians) * sin(angleInRadians));
                                    horizontalRange = horizontalRange/9.8;
                                    displayAnswer("horizontal range", horizontalRange);
                                }
                                // user chooses to calculate final vertical velocity
                                else{

                                    // get necessary quantity
                                    v1 = getVectorQuantity("initial velocity");
                                    t = getScalarQuantity("time of flight");
                                    // ask if user's angle is in degree/radians
                                    radians = getYesOrNoAnswer("angle in radians");
                                    // get angle in radians
                                    if ((radians == 'Y')||(radians == 'y')){
                                        angleInRadians = getAngleInRadians("angle to the horizontal");
                                    }
                                    else{
                                        angleInDegrees = getAngleInDegrees("angle to the horizontal");
                                        angleInRadians = convertToRadians(angleInDegrees);
                                    }
                                    // calculate final vertical velocity
                                    v2 = (v1*sin(angleInRadians)) - (9.8*t);
                                    displayAnswer("final vertical velocity", v2); 
                                } 
                            }
                        }
                    }
                }   
            }
            else{
                // user chooses the 3rd unit (circular motion)
                if (usersUnitChoice == 3){

                    // modify array to include the topics of the unit
                    unitTopics[0] = "Basic Angular Quantities";
                    unitTopics[1] = "Centripetal Acceleration";
                    unitTopics[2] = "Angular to Linear Quantity Conversion";
                    // display the menu
                    displayUnitTopics(unitTopics, 3);
                    // get topic choice of user
                    usersTopicChoice = getMenuChoice(1, 3, "topic");

                    // user chooses the first topic (basic angular quantities)
                    if (usersTopicChoice == 1){
                        // modify calculation choices to fit the topic
                        unitTopicsCalculations[0] = "angular displacement";
                        unitTopicsCalculations[1] = "angular velocity";
                        unitTopicsCalculations[2] = "angular acceleration";
                        unitTopicsCalculations[3] = "Centripetal Force";
                        // display and get menu choice
                        displayTopicChoice(unitTopicsCalculations, 1);
                        usersCalcChoice = getMenuChoice(1, 4, "calculation"); 
                        // user chooses to calculate angular displacement
                        if (usersCalcChoice == 1){
                            // get necessary quantities
                            initialAngularPosition = getVectorQuantity("initial angular position in radians");
                            finalAngularPosition = getVectorQuantity("final angular position in radians");
                            // calculate and print out angular displacement
                            angularDisplacement = calcChangeInQuantity(initialAngularPosition, finalAngularPosition);
                            displayAnswer("angular displacement", angularDisplacement);

                        }
                        else{
                            // user chooses to calculate angular velocity
                            if (usersCalcChoice == 2){
                                // check and find angular displacement
                                givenAngularDisplacement = getYesOrNoAnswer("angular displacement");
                                if ((givenAngularDisplacement == 'Y')||(givenAngularDisplacement == 'y')){
                                    angularDisplacement = getVectorQuantity("angular displacement in radians");
                                }
                                else{
                                    initialAngularPosition = getVectorQuantity("initial angular position in radians");
                                    finalAngularPosition = getVectorQuantity("final angular position in radians");
                                    angularDisplacement = calcChangeInQuantity(initialAngularPosition, finalAngularPosition);
                                }
                                // get change in time
                                changeInTime = getScalarQuantity("change in time");

                                // check if angular velocity is undefined, if not, print out answer
                                if (changeInTime == 0){
                                    undefinedNotice("angular velocity");
                                }
                                else{
                                    angularVelocity = angularDisplacement/changeInTime;
                                    displayAnswer("angular velocity", angularVelocity); 
                                }
                            }
                            else{
                                // user chooses to calculate angular acceleration
                                if (usersCalcChoice == 3){
                                    // check/ask/find angular velocity
                                    givenDeltaAngularVelocity = getYesOrNoAnswer("change in angular velocity");
                                    if ((givenDeltaAngularVelocity == 'y')||(givenDeltaAngularVelocity == 'Y')){
                                        changeInAngularVelocity = getVectorQuantity("change in angular velocity");
                                    }
                                    else{
                                        initialAngularVelocity = getVectorQuantity("initial angular velocity");
                                        finalAngularVelocity = getVectorQuantity("final angular velocity");
                                        changeInAngularVelocity = calcChangeInQuantity(initialAngularVelocity, finalAngularVelocity);
                                    }
                                    // get change in time
                                    changeInTime = getScalarQuantity("change in time");

                                    // check if angular acceleration is undefined, if not print the answer
                                    if (changeInTime == 0){
                                        undefinedNotice("angular acceleration");
                                    }
                                    else{
                                        angularAcceleration = changeInVelocity/changeInTime;
                                        displayAnswer("angular acceleration", angularAcceleration);
                                    } 
                                }
                                else{
                                    // user wants to find the centripetal force
                                    // find the necessary quantities
                                    mass = getScalarQuantity("mass");
                                    // calculate and state centripetal force
                                    centripetalAcceleration = getVectorQuantity("centripetal acceleration");
                                    centripetalForce = mass * centripetalAcceleration;
                                    displayAnswer("centripetal force", centripetalForce);
                                }

                            }
                        }

                    }
                    // user chooses to calculate centripetal acceleration
                    else{
                        if (usersTopicChoice == 2){
                            // get necessary quantities
                            radius = getScalarQuantity("length of the radius (R)"); 
                            givenAngularVelocity = getYesOrNoAnswer("angular velocity");
                            // check and get angular velocity and calculate centripetal acceleration with the appropriate formula
                            if ((givenAngularVelocity == 'Y')||(givenAngularVelocity == 'y')){
                                angularVelocity = getVectorQuantity("angular velocity");
                                centripetalAcceleration = radius * (angularVelocity * angularVelocity);
                            }
                            else{
                                tangentialVelocity = getVectorQuantity("velocity");
                                centripetalAcceleration =  (tangentialVelocity * tangentialVelocity)/radius;
                            }
                            displayAnswer("centripetal acceleration", centripetalAcceleration);
                        }
                        // user chooses to convert between linear and angular variables
                        else{
                            // modify calculations choice array to fit topic
                            unitTopicsCalculations[0] = "Converting Angular Displacement to Distance";
                            unitTopicsCalculations[1] = "Converting Angular Velocity to Speed";
                            unitTopicsCalculations[2] = "Converting Angular Acceleration to Tangential Acceleration";
                            unitTopicsCalculations[3] = "Tangential vs Centripetal Acceleration";
                            // display and get menu choice
                            displayTopicChoice(unitTopicsCalculations, 3);
                            usersCalcChoice = getMenuChoice(1,4,"calculation/explanation");

                            // user wants to convert angular displacement to distance traveled
                            if (usersCalcChoice == 1){
                                // get necessary quantities and convert
                                angularDisplacement = getScalarQuantity("magnitude of angular displacement");
                                radius = getScalarQuantity("radius");
                                distance = radius * angularDisplacement;
                                displayAnswer("distance traveled", distance);

                            }
                            // user wants to convert angular velocity to linear speed  
                            else{
                                if (usersCalcChoice == 2){
                                    // get necessary quantity and convert
                                    angularVelocity = getScalarQuantity("magnitude of angular velocity");
                                    radius = getScalarQuantity("radius");
                                    speed = radius * angularVelocity;
                                    displayAnswer("tangential speed", speed);
                                }
                                else{
                                    // user wants to convert angular acceleration to tangential acceleration 
                                    if (usersCalcChoice == 3){
                                        // get necessary quantities and convert
                                        angularAcceleration = getScalarQuantity("magnitude of angular acceleration");
                                        radius = getScalarQuantity("radius");
                                        tangentialAcceleration = radius * angularAcceleration;
                                        displayAnswer("tangential acceleration", tangentialAcceleration);
                                    }
                                    else{
                                        // user wants general concept of centripetal acceleration and linear acceleration
                                        printf("\nCentripetal acceleration is directed inward towards the center of rotation.\n");
                                        printf("Linear speed and acceleration is directed tangential to the circular path!");       
                                    }
                                }
                            }
                        }
                    }
                }
                else{
                    // user chooses the 4th unit on work, energy, and power
                    if (usersUnitChoice == 4){
                        // modify the array to include the topics relevant to this unit
                        unitTopics[0] = "Work";
                        unitTopics[1] = "Energy";
                        unitTopics[2] = "Power";

                        // display and get menu choice
                        displayUnitTopics(unitTopics, 4);
                        usersTopicChoice = getMenuChoice(1,3, "topic");
                        // user chooses to calculate work
                        if (usersTopicChoice == 1){
                            work = calcWork();
                            displayAnswer("work done/change in energy on the object", work);
                        }
                        else{
                            // user chooses to calculate a type of energy
                            if (usersTopicChoice == 2){
                                // modify calculations array to include the possible energy calculations
                                unitTopicsCalculations[0] = "Kinetic Energy";
                                unitTopicsCalculations[1] = "Gravitational Potential Energy";
                                unitTopicsCalculations[2] = "Elastic Potential Energy";
                                unitTopicsCalculations[3] = "Conservation of Energy";
                                // display and get menu choice
                                displayTopicChoice(unitTopicsCalculations, 2);
                                usersCalcChoice = getMenuChoice(1,4, "calculation");
                                // user wants to calculate kinetic energy
                                if (usersCalcChoice == 1){
                                    kineticEnergy = calcKineticEnergy("at the specific given time");
                                    displayAnswer("kinetic energy of the object", kineticEnergy );
                                }
                                else{
                                    // user wants to calculate gravitational potential energy
                                    if (usersCalcChoice == 2){
                                        gravitationalPotentialEnergy = calcGravitationalPotentialEnergy("at the specific given time");
                                        displayAnswer("gravitational potential energy of the object",  gravitationalPotentialEnergy);
                                    }
                                    else{
                                        // user wants to calculate elastic potential energy
                                        if (usersCalcChoice == 3){
                                            elasticPotentialEnergy = calcElasticPotentialEnergy("at the specific given time");
                                            displayAnswer("elastic potential energy", elasticPotentialEnergy);
                                        }
                                        else{
                                            // user wants to illustrate a conservation of energy equation
                                            if (usersCalcChoice == 4){
                                                // modify calculations/illustrations array to include the necessary scenarios of conservation of energy
                                                unitTopicsCalculations[0] = "Conservation of Total Mechanical Energy";
                                                unitTopicsCalculations[1] = "Conservation of Energy Involving Spring Motion";
                                                unitTopicsCalculations[2] = "Conservation of Energy Involving a Non-Conservative Force";
                                                unitTopicsCalculations[3] = "Calculating Work By Non-Conservative Forces";
                                                // display and get menu choice
                                                displayTopicChoice(unitTopicsCalculations, 4);
                                                usersCalcChoice = getMenuChoice(1,4, "calculation");
                                                // user chooses to illustrate situation where ME is conserved
                                                if (usersCalcChoice == 1){
                                                    // get necessary quantities
                                                    initialKineticEnergy1 = calcKineticEnergy("initially");
                                                    initialPotentialEnergy1 = calcGravitationalPotentialEnergy("initially");
                                                    finalKineticEnergy1 = calcKineticEnergy("finally");
                                                    finalPotentialEnergy1 = calcGravitationalPotentialEnergy("finally");
                                                    // print out the equation 
                                                    printf("\nThe conservation of energy equation in this situation is:\n");
                                                    printf("(%1.2lf) + (%1.2lf) = (%1.2lf) + (%1.2lf)", initialKineticEnergy1, initialPotentialEnergy1, finalKineticEnergy1, finalPotentialEnergy1 );
                                                }
                                                else{
                                                    // user chooses to illustrate situation where energy of springs are involved
                                                    if (usersCalcChoice == 2){
                                                        // get necessary energy quantities
                                                        initialElasticPotentialEnergy1 = calcElasticPotentialEnergy("initially");
                                                        finalKineticEnergy1 = calcKineticEnergy("initially");
                                                        // print out the equation
                                                        printf("\nThe conservation of energy equation in this situation is:\n");
                                                        printf("(%1.2lf) = (%1.2lf)", initialElasticPotentialEnergy1, finalKineticEnergy1);
                                                    }
                                                    else{
                                                        // user chooses to calculate situation where non conservative forces are at play
                                                        if (usersCalcChoice == 3){
                                                            // get necessary energy quantities and work done by non conservative force
                                                            initialKineticEnergy1 = calcKineticEnergy("initially");
                                                            initialPotentialEnergy1 = calcGravitationalPotentialEnergy("initially");
                                                            finalKineticEnergy1 = calcKineticEnergy("finally");
                                                            finalPotentialEnergy1 = calcGravitationalPotentialEnergy("finally");
                                                            nonConservativeWork = calcWork();
                                                            // print out equation
                                                            printf("\nThe conservation of energy equation in this situation is:\n");
                                                            printf("(%1.2lf) + (%1.2lf) + (%1.2lf) = (%1.2lf) + (%1.2lf)", initialKineticEnergy1, initialPotentialEnergy1, nonConservativeWork, finalKineticEnergy1, finalPotentialEnergy1);
                                                        }
                                                        else{
                                                            // user simply wants to calculate non conservative work that is involved
                                                            nonConservativeWork = calcWork();
                                                            displayAnswer("work done by non-conservative forces", nonConservativeWork);
                                                        }
                                                    }
                                                } 
                                            }
                                        }
                                    }
                                }
                            }
                            //  user wants to calculate power
                            else{
                                // get the work done on object/person
                                givenWork = getYesOrNoAnswer("work done by person/object");
                                if ((givenWork == 'y')||(givenWork == 'Y')){
                                    work = getVectorQuantity("work");
                                    // get change in time
                                    changeInTime = getScalarQuantity("change in time");
                                    // calculate power and display or state undefined if time = 0
                                    if (changeInTime == 0){
                                        undefinedNotice("power");
                                    }
                                    else{
                                        power = work/changeInTime;
                                        displayAnswer("power", power);
                                    }
                                }
                                // use the other formula for power (P = FVcos theta)
                                else{
                                    // get necessary quantities
                                    netForce = getScalarQuantity("magnitude of the force applied");
                                    speed = getScalarQuantity("speed of object");
                                    radians = getYesOrNoAnswer("angle in radians");
                                    // get angle in radians
                                    if ((radians == 'Y')||(radians == 'y')){
                                        angleInRadians = getAngleInRadians("angle between the speed and force");
                                    }
                                    else{
                                        angleInDegrees = getAngleInDegrees("angle between the speed and force");
                                        angleInRadians = convertToRadians(angleInDegrees);
                                    }
                                    // calculate power
                                    power = netForce * speed * cos(angleInRadians);
                                    displayAnswer("power", power);
                                }
                            } 
                        }
                    }
                    else{

                        // user chooses to explore unit 5 calculations (momentum,torque, and impulse)
                        if (usersUnitChoice == 5){

                            // modify array to include relevant topics
                            unitTopics[0] = "Linear and Angular Momentum";
                            unitTopics[1] = "Torque";
                            unitTopics[2] = "Linear and Angular Impulse";
                            // display and get topi menu choice
                            displayUnitTopics(unitTopics, 5);
                            usersTopicChoice = getMenuChoice(1, 3, "topic");
                            // users chooses to calculate linear and angular momentum
                            if (usersTopicChoice == 1){
                                printf("\nTopic 1 has the following choices: ");
                                printf("\n1: Linear Momentum");
                                printf("\n2: Angular Momentum");
                                // get menu choice from the two calculations options above
                                usersCalcChoice = getMenuChoice(1,2, "calculation");

                                // user chooses to calculate linear momentum
                                if (usersCalcChoice == 1){
                                    // get necessary quantities
                                    mass = getScalarQuantity("mass");
                                    constantVelocity = getVectorQuantity("velocity");
                                    // calculate
                                    momentum = mass * constantVelocity;
                                    displayAnswer("linear momentum", momentum);

                                }
                                else{
                                    // user chooses to calculate angular momentum
                                    if (usersCalcChoice == 2){
                                        // choose the formula that is necessary 
                                        // ask if speed is given
                                        givenSpeed = getYesOrNoAnswer("average speed of object");
                                        if ((givenSpeed == 'y')||(givenSpeed == 'Y')){
                                            // speed is given so use l = mvr
                                            mass = getScalarQuantity("mass");
                                            radius = getScalarQuantity("length of radius (R)");
                                            speed = getScalarQuantity("speed");
                                            angularMomentum = mass * radius * speed;
                                            displayAnswer("angular momentum", angularMomentum);
                                        }
                                        // speed is not given
                                        else{
                                            // see if rotational inertia is given
                                            givenI = getYesOrNoAnswer("rotational inertia (I) of object");
                                            // given rotational inertia: use l = Iw
                                            if ((givenI == 'y')||(givenI == 'Y')){
                                                angularVelocity = getVectorQuantity("angular velocity");
                                                rotationalInertia = getScalarQuantity("rotational inertia (I)");
                                                angularMomentum = rotationalInertia * angularVelocity;
                                                displayAnswer("angular momentum", angularMomentum);
                                            }
                                            // rotational inertia is not given
                                            else{
                                                // use l = mwr^2
                                                angularVelocity = getVectorQuantity("angular velocity");
                                                radius = getScalarQuantity("length of radius (R)");
                                                mass = getScalarQuantity("mass");
                                                angularMomentum = mass * (radius * radius) * angularVelocity;
                                                displayAnswer("angular momentum", angularMomentum);
                                            }
                                        }
                                    }
                                }
                            }
                            else{
                                // user chooses to calculate torque
                                if (usersTopicChoice == 2){
                                    // get necessary information
                                    netForce = getVectorQuantity("net force");
                                    radius = getScalarQuantity("radius");
                                    radians = getYesOrNoAnswer("angle in radians");
                                    // get angle in radians
                                    if ((radians == 'Y')||(radians == 'y')){
                                        angleInRadians = getAngleInRadians("angle between the net force and radius");
                                    }
                                    else{
                                        angleInDegrees = getAngleInDegrees("angle between the net force and radius");
                                        angleInRadians = convertToRadians(angleInDegrees);
                                    }
                                    // calculate torque: there's only one formula to calculate
                                    torque = netForce * radius * sin(angleInRadians);
                                    displayAnswer("torque", torque); 
                                }
                                // user wants to calculate impulse
                                else{
                                    // display the two types of impulses
                                    printf("\nThere are two types of impulse: ");
                                    printf("\n1: Linear Impulse");
                                    printf("\n2: Angular Impulse");
                                    // get user to choose the type to calculate
                                    usersCalcChoice = getMenuChoice(1,2, "calculation");
                                    // user chooses to calculate linear impulse
                                    if (usersCalcChoice == 1){
                                        // ask and calculate with necessary quantities
                                        netForce = getVectorQuantity("net force");
                                        changeInTime = getScalarQuantity("change in time");
                                        linearImpulse = netForce * changeInTime;
                                        displayAnswer("linear impulse", linearImpulse);
                                    }
                                    // user chooses to calculate angular impulse
                                    else{
                                        // user chooses to calculate angular impulse
                                        torque = getVectorQuantity("net torque");
                                        changeInTime = getScalarQuantity("change in time");
                                        angularImpulse = torque * changeInTime;
                                        displayAnswer("angular impulse", angularImpulse);
                                    }
                                }
                            }
                        }
                        // user chooses unit 6: Simple Harmonic Oscillators
                        else{
                            if (usersUnitChoice == 6){
                                // modify topics array to again suit the porpose and unit
                                unitTopics[0] = "Hooks Law";
                                unitTopics[1] = "Spring Mass Oscillator";
                                unitTopics[2] = "Simple Pendulum";
                                // display and get topic menu choice
                                displayUnitTopics(unitTopics, 6);
                                usersTopicChoice = getMenuChoice(1,3, "topic");
                                // user wants to find a variable in Hooks Law
                                if (usersTopicChoice == 1){
                                    // ask for the variable (didn't make a function as this is done only one times)
                                    printf("\nWhich variable are you asked to find [F/k/d]: ");
                                    scanf("%c", &unknownVariable);
                                    fgetc(stdin);

                                    while ((unknownVariable != 'F') && (unknownVariable != 'k') && (unknownVariable != 'd')){
                                    printf("\nYour input of %c is invalid. Please try again!\n", unknownVariable);
                                    printf("Which variable are you asked to find [F/k/d]: ");
                                    scanf("%c", &unknownVariable);
                                    fgetc(stdin);
                                    }
                                    // wants to find restorative force
                                    if (unknownVariable == 'F'){
                                        // get other quantities and calculate
                                        springConstant = getScalarQuantity("spring constant");
                                        displacement = getVectorQuantity("displacement");
                                        restorativeForce = (springConstant * displacement) * (-1);
                                        displayAnswer("restorative force", restorativeForce);
                                    }
                                    else{
                                        // wants to find spring constant
                                        if (unknownVariable == 'k'){
                                            // get other quantities and calculate
                                            restorativeForce = getVectorQuantity("restorative force");
                                            displacement = getVectorQuantity("displacement");
                                            springConstant = (restorativeForce/displacement)*(-1);
                                            if (springConstant >= 0){
                                                displayAnswer("spring constant", springConstant);   
                                            }
                                            else{
                                                printf("\nThe spring constant CANNOT be negative! Please\n");
                                                printf("double check your answer!");
                                            }
                                            
                                        }
                                        // wants to find the displacement of the spring
                                        else{
                                            // get other quantities and calculate
                                            restorativeForce = getVectorQuantity("restorative force");
                                            springConstant = getScalarQuantity("spring constant");
                                            displacement = (restorativeForce/springConstant)*(-1);
                                            displayAnswer("displacement of the spring", displacement);
                                        }
                                    }

                                }
                                else{
                                    // user wants to do calculations/topics around spring mass oscillators
                                    if (usersTopicChoice == 2){
                                        // display the two choices
                                        printf("\nPlease choose one of the options below to calculate/express:\n");
                                        printf("1: Period of Spring Mass Oscillator\n");
                                        printf("2: Sinusoidal Representation");
                                        // get users calculations choice
                                        usersCalcChoice = getMenuChoice(1,2, "calculation/representation");
                                        // user wants to calculate period
                                        if (usersCalcChoice == 1){
                                            // get necessary quantities and calculate
                                            mass = getScalarQuantity("mass of the object");
                                            springConstant = getScalarQuantity("spring constant");
                                            period = (sqrt(mass/springConstant))*(2*piApproximation);
                                            displayAnswer("period of the spring mass system", period);
                                        }
                                        // user wants to express an equation for oscillator
                                        else{
                                            // get amplitude, and period and then write into sinusoidal equation
                                            displacement = getScalarQuantity("maximum displacement (magnitude)");
                                            period = getScalarQuantity("period of the oscillator");
                                            printf("\nThe equation is x(t) = %1.2lfcos((2pi/%1.2lf)t)", displacement, period);
                                        }

                                    }
                                    // uses wants to do calculations with pendulum
                                    else{
                                        // display the options below
                                        printf("\nPlease choose one of the options below to calculate/express:\n");
                                        printf("1: Period of Simple Pendulum\n");
                                        printf("2: Sinusoidal Representation");
                                        // get user to choose calculation 
                                        usersCalcChoice = getMenuChoice(1,2, "calculation/representation");
                                        // user wants to calculate period of the pendulum
                                        if (usersCalcChoice == 1){
                                            // get necessary quantities and calculate
                                            lengthOfString = getScalarQuantity("length of string");
                                            period = (2*piApproximation) * sqrt(lengthOfString/9.81);
                                            displayAnswer("period of the simple pendulum", period);
                                        }
                                        // user wants to express the motion of simple pendulum
                                        else{
                                            // get max angular displacement and period and write equation
                                            angularDisplacement = getVectorQuantity("maximum angular displacement (magnitude in radians)");
                                            period = getScalarQuantity("period of the simple pendulum");
                                            printf("\nThe equation is x(t) = %1.2lfcos((2pi/%1.2lf)t)", angularDisplacement, period);
                                        }
                                    }
                                }
                            }
                            // user chooses the last unit: Newton's Laws of Gravitation, and Rolling objects
                            else{
                                if (usersUnitChoice == 7){
                                    // modify unit topic arrays to include relevant topics
                                    unitTopics[0] = "Newton's Law of Gravitation";
                                    unitTopics[1] = "Rotational Inertia";
                                    unitTopics[2] = "Rolling Motion";

                                    // display and get topic choice
                                    displayUnitTopics(unitTopics, 7);
                                    usersTopicChoice = getMenuChoice(1,3, "topic");
                                    // chooses to calculate gravitational force or Potential energy using Newton's law of gravitation
                                    if (usersTopicChoice == 1){
                                        // display the two applications
                                        printf("\nNewton's other Laws are cool! Please choose one law to explore!\n");
                                        printf("1: Gravitational force\n");
                                        printf("2: Gravitational Potential Energy Away From Earth");
                                        // get user to choose application
                                        usersCalcChoice = getMenuChoice(1,2, "calculation");
                                        // user chooses to calculate gravitational force
                                        if (usersCalcChoice == 1){
                                            // get necessary quantities
                                            objectMass1 = getScalarQuantity("mass of object 1");
                                            objectMass2 = getScalarQuantity("mass of object 2");
                                            distance = getScalarQuantity("distance from the two objects' center of mass");
                                            // calculate gravitational force
                                            gravitationalForce = (universalGravitationalConstantApproximation * (objectMass1 * objectMass2))/(distance * distance);
                                            // since number is too small I will use a common scientific notation sort format to display answer
                                            gravitationalForce = gravitationalForce * 1000000000;
                                            printf("\nThe gravitational force (Fg) is approximately %1.2lf x 10^(-9)", gravitationalForce);
                                        }
                                        // user chooses to calculate gravitational potential energy
                                        else{
                                            // get necessary quantities
                                            objectMass1 = getScalarQuantity("mass of object 1");
                                            objectMass2 = getScalarQuantity("mass of object 2");
                                            distance = getScalarQuantity("distance from the two objects' center of mass");
                                            // same method as before: use a general scientific notation to simplify output
                                            gravitationalPotentialEnergyBeyondEarth = (-1)*((objectMass1 * objectMass2)/distance);
                                            gravitationalPotentialEnergyBeyondEarth = gravitationalPotentialEnergyBeyondEarth * 1000000000;
                                            printf("\nThe gravitational potential energy(Ug) is approximately %1.2lf x 10^(-9)", gravitationalPotentialEnergyBeyondEarth);

                                        }
                                    }
                                    else{
                                        // user chooses to calculate rotational inertia of an object
                                        if (usersTopicChoice == 2){
                                            // get necessary quantities and calculate
                                            mass = getScalarQuantity("mass of the object");
                                            radius = getScalarQuantity("radius of the object");
                                            rotationalInertia = mass * (radius*radius);
                                            displayAnswer("rotational inertia (I)", rotationalInertia);
                                        }
                                        // user chooses to calculate quantities describing rolling objects
                                        else{
                                            // display possible choices
                                            printf("\nWe see rolling objects everyday! How do we describe them? Choose one below!\n");
                                            printf("1: Rotational Kinetic Energy\n");
                                            printf("2: Rolling without Slipping (Speed of Center of Mass)");
                                            // get users calculation choice
                                            usersCalcChoice = getMenuChoice(1,2, "calculation");

                                            // user chooses to calculate rotational kinetic energy
                                            if (usersCalcChoice == 1){
                                                // get necessary quantities and calculate
                                                rotationalInertia = getScalarQuantity("rotational inertia of the object");
                                                angularVelocity = getVectorQuantity("angular velocity of the object");
                                                rotationalKineticEnergy = 0.5 * ((rotationalInertia) * (angularVelocity * angularVelocity));
                                                displayAnswer("rotational kinetic energy", rotationalKineticEnergy);                           
                                            }
                                            // user choose to calculate speed of center of mass of an object that is rolling without slipping
                                            else{
                                                // get necessary quantities and calculate
                                                radius = getScalarQuantity("radius of the object");
                                                angularVelocity = getScalarQuantity("angular velocity of the object (magnitude)");
                                                speed = radius * angularVelocity;
                                                displayAnswer("speed at center of mass of the object rolling", speed);
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        // ask if users are given the unit of their final answer
        if (usersUnitChoice != 0){

        printf("\n");
        givenUnits = getYesOrNoAnswer("unit of the solved quantity");

        // user is not given the unit: give them some common units
        if ((givenUnits == 'n') || (givenUnits == 'N')){
            printf("\nHere are a list of common/standard units for each physical quantity:\n");
            counter = 0;
            for (counter = 0; counter < NUM_OF_QUANTITY_UNITS; counter++){
                printf("  - %s\n", units[counter]);
            }
            // print ending statement after user finishes calculating
            printf("\nHopefully you found your unit! Thank you for using this\n");
            printf("legendary Master Calculator!");
        }
        else{
            printf("\nLucky you, you don't need to search through the list! Thank you \n");
            printf("for using our calculator!\n");
        }
    }   
}
    // print ending statement if user chooses to quit
    printf("\nYou have successfully quitted the program! Thank you for using the\n");
    printf("Master AP Physics 1 2020 Calculator!\n");
    return (EXIT_SUCCESS);
}



