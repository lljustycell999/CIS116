#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

using namespace std;

// Name: Justyce Countryman
// Due Date: Monday, December 14, 2020
// Project Name: Laboratory 10

/* Project Description: Write a program that produces a daily weather summary from a data file generated by a weather station. The
 * station logs the time, air temperature, wind speed, wind direction, humidity, and barometric pressure. The
 * station logs this data every ten minutes.
 * The program must initially get the date and data file name from the user. A report heading should show the
 * date entered along with column headings for each piece of data to be listed. Next, it processes each log entry in
 * the file. This processing includes getting the entry, updating totals, converting time from military to standard
 * time, and displaying the data. Finally, the program should compute the different averages and appened them to
 * another file.
 * The time is stored in military time and should be displayed in standard format (ie. 13:20 is 1:20pm). Display the
 * summary in a columnar format. The program should process any and all entries in the file.
 * Use formatted output for ALL output. Use and reuse a single function that accepts a sum and a number of items
 * in order to calculate an average. This one function is helpful for computing average air temperature, average
 * wind speed, average humidity, and average barometric pressure.
 */
// Project Number: Project 10

int main(void) {
    
    char fileName[80];
    char date[80];
    ifstream weatherFile;
    int hours, minutes;
    double temp, windSpeed, humidity, barPressure;
    char windDirection[80];
    string timeConversion;
    double totalTemp, totalWindSpeed, totalHumidity, totalBarPressure;
    int numEntries;
    double avgTemp, avgWindSpeed, avgHumidity, avgBarPressure;
    ofstream weatherStoringFile;
    
    totalTemp = 0;
    totalWindSpeed = 0;
    totalHumidity = 0;
    totalBarPressure = 0;
    numEntries = 0;
    avgTemp = 0;
    avgWindSpeed = 0;
    avgHumidity = 0;
    avgBarPressure = 0;
    
    //Get File Name
    cout << "Enter Name of File: "; //to user
    cin.getline(fileName, 80); //from user
    
    //Get Date
    cout << "Enter Today's Date: "; //to user
    cin.getline(date, 80); //from user
    
    //Display Headings
    cout << "Date: " << date << endl << endl; //to user
    cout << "Time" << setw(13) << "Air Temp" << setw(16) << "Wind Speed" << setw(18) << "Wind Direction" << setw(12) << "Humidity" << setw(16) << "Bar Pressure" << endl; //to user
    
    //Get Weather Information
    weatherFile.open(fileName);
    while(weatherFile >> hours >> minutes >> temp >> windSpeed >> windDirection >> humidity >> barPressure){
    
        //Convert Time
        if(hours >= 12){
            hours = hours - 12;
            timeConversion = "PM";
        }
        else{
            timeConversion = "AM";
        }
        if(hours == 0){
            hours = 12;
        }

        //Display Weather Summary
        cout << fixed << setprecision(2) << hours << ":" << (minutes < 10? "0":"") << minutes << timeConversion << setw(10) << temp << setw(16) << windSpeed << setw(18) << windDirection << setw(12) << humidity << setw(16) << barPressure << endl; //to user
        
        //Update Totals
        totalTemp = totalTemp + temp;
        totalWindSpeed = totalWindSpeed + windSpeed;
        totalHumidity = totalHumidity + humidity;
        totalBarPressure = totalBarPressure + barPressure;
        numEntries = numEntries + 1;     
    }
    weatherFile.close();
    
    //Compute Averages
    avgTemp = totalTemp / numEntries;
    avgWindSpeed = totalWindSpeed / numEntries;
    avgHumidity = totalHumidity / numEntries;
    avgBarPressure = totalBarPressure / numEntries;
    
    //Store Average Summary
    weatherStoringFile.open("weatherStoring.txt", ios::app);
    weatherStoringFile << "Date: " << date << endl;
    weatherStoringFile << "Avg. Air Temp" << setw(20) << "Avg. Wind Speed" << setw(18) << "Avg. Humidity" << setw(22) << "Avg. Bar Pressure" << endl;
    weatherStoringFile << fixed << setprecision(2) << setw(13) << avgTemp << setw(20) << avgWindSpeed << setw(18) << avgHumidity << setw(22) << avgBarPressure << endl;
    weatherStoringFile.close();
       
    return 0;
}