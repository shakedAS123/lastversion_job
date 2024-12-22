#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <ctime>
#include <algorithm>

using namespace std;

#define CANDIDATEFILE "candidate.txt"
#define EMPLOYERFILE "employers.txt"


string trim(const string& str)
/*remaining spaces
get: string that need trimming
return string after trimming */
{
    size_t first = str.find_first_not_of(' ');
    size_t last = str.find_last_not_of(' ');
    return (first == string::npos || last == string::npos) ? "" : str.substr(first, last - first + 1);
}


bool idExists(const string& fileName, const string& id) //get the file name and id and return true if we have user with the same type with that id
{
    ifstream file(fileName);//file handling
    if (!file.is_open()) 
	{
        return false;
    }
    string line;
    while (getline(file, line)) //while file not empty
	{
        if (line.empty()) continue; // Skip empty lines
        istringstream iss(line);
        string fileId;
        iss >> fileId; // put data to fileID until read space 
        if (fileId == id) //if we have the same id as in file
		{
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}



void registerUser(const string& fileName) //get file name based on user type and make new user
{
    ofstream file(fileName, ios::app);
    if (!file.is_open()) //file handling
	{
        cout << "Error opening the file for registration.\n";
        return;
    }
    string id, password, firstName, lastName, email, dob, phone;//dob (day of birth)
    cout << "Enter ID: ";
    cin >> id;
    cout << "Enter Password: ";
    cin >> password;
    cout << "Enter First Name: ";
    cin >> firstName;
    cout << "Enter Last Name: ";
    cin >> lastName;
    cout << "Enter Email: ";
    cin >> email;
    cout << "Enter Date of Birth (DD/MM/YYYY): ";
    cin >> dob;
    cout << "Enter Phone: ";
    cin >> phone;
    // Check if ID already exists and exit in case of that
    if (idExists(fileName, id)) 
	{
        cout << "This ID already exists. Please try a different one.\n";
        file.close();
        return;
    }
    file << id << " " << password << " " << firstName << " " << lastName << " " << email << " " << dob << " " << phone << endl;//insert to file
    cout << "Registration successful!\n";
    file.close();//close file
}

bool loginUser(const string& fileName, const string& id, const string& password) 
/*return if the id and password are matching to file
get: file to look on, id of user, password
return: true if they match */
{
    ifstream file(fileName);
    if (!file.is_open())//fill handling
	{
        cout << "Error opening the file for login.\n";
        return false;
    }
    string line;
    while (getline(file, line)) 
	{
        if (line.empty()) continue; // Skip empty lines
        istringstream iss(line); //read from file a line
        string fileId, filePassword;
        iss >> fileId >> filePassword;//fileID get from start until space and filePassword after until space
        if (fileId == id && filePassword == password)//match
		{
            file.close();
            return true;
        }
    }
    file.close();
    return false;//no match
}

void enterCandidateExpectations(const string& candidateId) 
/*make candidate profile and save all in file named candidate_expectations
get: id of user
return: */
{
    string degree, employmentType, location; 
    int age;
    float expectedSalary;
	//get data from user
    cout << endl <<"--- Enter Your Expectations ---" <<endl;
    cout << "Enter your university degree name: ";
    cin.ignore(); // clear buffer
    getline(cin, degree);
    cout << "Enter your age: ";
    cin >> age;
    cout << "Enter your expected salary: ";
    cin >> expectedSalary;
    cout << "Are you willing to work full-time or part-time? (full/part): ";
    cin >> employmentType;
    cout << "Enter your location (city or region): ";
    cin.ignore(); // clear buffer
    getline(cin, location);
    // confirm all data are right
    cout << endl<<"--- Your Expectations ---" <<endl;
    cout << "Degree: " << degree << endl;
    cout << "Age: " << age << endl;
    cout << "Expected Salary: " << expectedSalary << endl;
    cout << "Employment Type: " << employmentType << endl;
    cout << "Location: " << location << endl;
	//need confirmation from user
    cout << "\nDo you want to save these expectations? (yes/no): ";
    string confirmation;
    cin >> confirmation;
    if (confirmation == "yes" || confirmation == "Yes") {
        // save data to file
        ofstream expectationsFile("candidate_expectations.txt", ios::app);//try to open
        if (!expectationsFile.is_open()) //file handling
		{
            cout << "Error opening the file for saving expectations.\n";
            return;
        }
		//put data in file
        expectationsFile << "Candidate ID: " << candidateId
                         << " | Degree: " << degree
                         << " | Age: " << age
                         << " | Expected Salary: " << expectedSalary
                         << " | Employment Type: " << employmentType
                         << " | Location: " << location << endl;
        expectationsFile.close();
        cout << "Your expectations have been saved successfully!\n";
    } else {
        cout << "Expectations were not saved. Returning to menu...\n";
    }
}

void viewAndEditProfile(const string& fileName, const string& id) 
/* let user option to edit the basic information
get: file to see profile, id of user
return: */
{
	ifstream file(fileName);
    ofstream tempFile("temp.txt");
    string fileId, password, firstName, lastName, email, dob, phone, line; //bod = day of birth
    bool found = false;
    while (getline(file, line))//read while file have data 
	{
        istringstream iss(line);
        iss >> fileId >> password >> firstName >> lastName >> email >> dob >> phone; //put data and separate by spaces in file
        if (fileId == id)//if we have match id show all the data that match the id
		{
            found = true;
            cout << endl << "--- Current Profile Details ---"<<endl;
            cout << "First Name: " << firstName << endl;
            cout << "Last Name: " << lastName << endl;
            cout << "Email: " << email << endl;
            cout << "Date of Birth: " << dob << endl;
            cout << "Phone: " << phone << endl;
            cout << endl<<"Do you want to edit your profile? (yes/no): ";
            string editChoice;
            cin >> editChoice;
            if (editChoice == "yes" || editChoice == "Yes") //ask user for updated confirm
			{
                //updated the new data user enter
				cout << endl<<"--- Edit Profile ---"<<endl;
                cout << "Enter new First Name (or press Enter to keep current): ";
                string newFirstName;
                cin.ignore();
                getline(cin, newFirstName);
                if (!newFirstName.empty()) firstName = newFirstName;
                cout << "Enter new Last Name (or press Enter to keep current): ";
                string newLastName;
                getline(cin, newLastName);
                if (!newLastName.empty()) lastName = newLastName;
                cout << "Enter new Email (or press Enter to keep current): ";
                string newEmail;
                getline(cin, newEmail);
                if (!newEmail.empty()) email = newEmail;
                cout << "Enter new Date of Birth (or press Enter to keep current): ";
                string newDob;
                getline(cin, newDob);
                if (!newDob.empty()) dob = newDob;
                cout << "Enter new Phone (or press Enter to keep current): ";
                string newPhone;
                getline(cin, newPhone);
                if (!newPhone.empty()) phone = newPhone;
                cout <<endl<< "--- Updated Profile ---" <<endl;
                cout << "First Name: " << firstName << endl;
                cout << "Last Name: " << lastName << endl;
                cout << "Email: " << email << endl;
                cout << "Date of Birth: " << dob << endl;
                cout << "Phone: " << phone << endl;
                cout << endl<<"Do you want to save these changes? (yes/no): "; //ask for confirmation
                string confirmation;
                cin >> confirmation;
                if (confirmation == "yes" || confirmation == "Yes")//updated profile
				{
                    tempFile << fileId << " " << password << " " << firstName << " " << lastName << " " << email << " " << dob << " " << phone << "\n";
                    cout << "Profile updated successfully!" <<endl;
                } else {
                    tempFile << line << endl;
                    cout << "Changes discarded."<<endl;
                }
            } else {
                tempFile << line << endl;
                cout << "Returning to the candidate menu..." <<endl;
            }
        } else {
            tempFile << line << endl;
        }
    }

    file.close();
    tempFile.close();

    if (found) //updated profile if we have match by id
	{
        remove(fileName.c_str());
        rename("temp.txt", fileName.c_str()); //updated file by changes temp and the candidate file
    } else {
        cout << "Profile not found." <<endl;
        remove("temp.txt");
    }
}

void filterJobs(const string& fileName)
/*print all jobs after sort by filter
get: file to read from (jobs.txt)
return:  */
{
    ifstream file(fileName);//file handling
    if (!file.is_open()) 
	{
        cout << "Error opening jobs file.\n";
        return;
    }
	//job string vector
    vector<string> jobs;
    string line;
    while (getline(file, line)) //read from file and push to vector
	{
        jobs.push_back(line);
    }
    file.close();
    if (jobs.empty()) //if file was empty print and exit
	{
        cout << "No jobs available." <<endl;
        return;
    }
	//print filter menu 
    cout << endl<<"--- Available Filters ---" <<endl;
    cout << "1. Salary (High to Low)"<<endl;
    cout << "2. Experience (High to Low)"<<endl;
    cout << "3. Degree (Show 'No' First)"<<endl;
    cout << "Enter your choice: ";
    int choice;
    cin >> choice;
    if (choice == 1)//show jobs sorted by salary high to low
	{
        sort(jobs.begin(), jobs.end(), [](const string& a, const string& b)//sort data in vector by salary
		{
            istringstream issA(a), issB(b);
            string salaryA, salaryB;
			//ignor 
            getline(issA, salaryA, '|'); // id
            getline(issA, salaryA, '|'); // name
            getline(issA, salaryA, '|'); // salary
            getline(issB, salaryB, '|'); // id
            getline(issB, salaryB, '|'); // name
            getline(issB, salaryB, '|'); // salary

            return stof(trim(salaryA)) > stof(trim(salaryB));
        });
    } else if (choice == 2) //show jobs sorted by years of exp high to low
	{
        sort(jobs.begin(), jobs.end(), [](const string& a, const string& b) {
            istringstream issA(a), issB(b);
            string expA, expB;
			//ignor
            getline(issA, expA, '|'); // id
            getline(issA, expA, '|'); // name
            getline(issA, expA, '|'); // salary
            getline(issA, expA, '|'); // exp
            getline(issB, expB, '|'); // id
            getline(issB, expB, '|'); // name
            getline(issB, expB, '|'); // salary
            getline(issB, expB, '|'); // exp

            return stof(trim(expA)) > stof(trim(expB));
        });
    } else if (choice == 3)//show first jobs that dont need degree
	{
        stable_sort(jobs.begin(), jobs.end(), [](const string& a, const string& b) {
            istringstream issA(a), issB(b);
            string degreeA, degreeB;
			//ignor
            for (int i = 0; i < 4; ++i) getline(issA, degreeA, '|');
            for (int i = 0; i < 4; ++i) getline(issB, degreeB, '|');
			//put degree string
            degreeA = trim(degreeA);
            degreeB = trim(degreeB);
            return degreeA == "no" && degreeB != "no"; 
        });
    } else //wrong input and exit
	{
        cout << "Invalid choice. Returning to menu." <<endl;
        return;
    }
    // print all jobs after sort
    cout <<endl<< "--- Filtered Jobs ---"<<endl;
    for (const auto& job : jobs) 
	{
        cout << job << endl;
    }
}

void displayJobs(const string& fileName, const string& candidateId) 
/*let candidate see jobs, sort the jobs by option , submit to job and send massage to employer 
get: jobs.txt file to open, id of candidate
return:  */
{
    while (true) 
	{
        ifstream file(fileName);//file handling
        if (!file.is_open()) {
            cout << "Error opening jobs file." <<endl;
            return;
        }
        vector<string> jobs;//make vector of string holding jobs data
        string line;
        cout << endl<<"--- Available Jobs ---" <<endl;
        while (getline(file, line)) 
		{
            istringstream iss(line);
            string employerId, jobName, salary, experience, degree, jobType, postDate, applicantCount, existingIds;
			//read from file and put to var
            getline(iss, employerId, '|');
            getline(iss, jobName, '|');
            getline(iss, salary, '|');
            getline(iss, experience, '|');
            getline(iss, degree, '|');
            getline(iss, jobType, '|');
            getline(iss, postDate, '|');
            getline(iss, applicantCount, '|');
            getline(iss, existingIds, '|');
			//print to user
            cout << employerId << " | " << jobName << " | " << salary << " | "
                 << experience << " | " << degree << " | " << jobType << " | "
                 << postDate << " | " << applicantCount << endl;
            jobs.push_back(line);// put line to vector
        }
        file.close();
        if (jobs.empty()) //chack if vector is empty and if so print and exit
		{
            cout << "No jobs available." <<endl;
            return;
        }
		//option for user for search
        cout << endl<<"What would you like to do?"<<endl;
        cout << "1. Filter Jobs"<<endl;
        cout << "2. Select a Job"<< endl;
        cout << "3. Save a Job" <<endl;
        cout << "4. Exit to Candidate Menu" <<endl;
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;

        if (choice == 1) //filter jobs 
		{
            filterJobs(fileName);
        } else if (choice == 2) //show job by the job number and give option to submit
		{
            cout << "Enter the number of the job you want to select: ";
            int jobNumber;
            cin >> jobNumber;
            if (jobNumber < 1 || jobNumber > jobs.size()) //chack if job number valid
			{
                cout << "Invalid job number. Please try again."<<endl;
            } else //number of job was valid
			{
                istringstream iss(jobs[jobNumber - 1]);
                string employerId, jobName, salary, experience, degree, jobType, postDate, applicantCount, existingIds;
                //read from vector by the number of job
				getline(iss, employerId, '|');
                getline(iss, jobName, '|');
                getline(iss, salary, '|');
                getline(iss, experience, '|');
                getline(iss, degree, '|');
                getline(iss, jobType, '|');
                getline(iss, postDate, '|');
                getline(iss, applicantCount, '|');
                getline(iss, existingIds, '|');
				//print the job user enter
                cout << endl<<"The job you selected is: " << jobName << endl;
                cout << "The salary offered is: " << salary << endl;
                cout << "Advantage for candidates with: " << experience << " years of experience"<<endl;
                cout << "The job type is: " << jobType << endl;
                cout << "The job was posted on: " << postDate << endl;
                cout << "Current Applicants: " << (existingIds.empty() ? "None" : existingIds) << endl;
				//candidate get option to submitted to job
                cout << endl<<"Would you like to add a free text for this job application? (yes/no): ";
                string freeTextChoice;
                cin >> freeTextChoice;				
                string freeText = "Candidate did not provide any text.";
                if (freeTextChoice == "yes" || freeTextChoice == "Yes") // candidate want to submit to job
				{
                    cin.ignore(); // Clear the input buffer
                    cout << "Enter your text: ";
                    getline(cin, freeText);
                }
                ofstream freeTextFile("textt.txt", ios::app);
                if (freeTextFile.is_open()) //add the candidate submit
				{
                    static int textCounter = 0; // Counter for text entries
                    freeTextFile << "| Job Name: " << jobName
                                 << " | " << freeText
                                 << " | Candidate's ID: " << candidateId
                                 << " | Employer's ID: " << employerId
                                 << " | Counter: " << textCounter << endl;
                    textCounter++;
                    freeTextFile.close();
                    cout << "Your text has been saved successfully."<<endl;
                } else {
                    cout << "Error saving your text."<<endl;
                }

                cout << endl<< "Would you like to apply for this job? (yes/no): ";
                string applyChoice;
                cin >> applyChoice;

                if (applyChoice == "yes" || applyChoice == "Yes") {
                    // Update the existing IDs only
                    if (!existingIds.empty()) {
                        existingIds += "," + candidateId;
                    } else {
                        existingIds = candidateId;
                    }

                    // Update the selected job entry
                    jobs[jobNumber - 1] = employerId + "|" + jobName + "|" + salary + "|" +
                                          experience + "|" + degree + "|" + jobType + "|" +
                                          postDate + "|" + applicantCount + "|" + existingIds;

                    // Write the updated job list back to the file
                    ofstream outFile(fileName);
                    if (outFile.is_open()) {
                        for (const auto& job : jobs) {
                            outFile << job << endl;
                        }
                        outFile.close();
                        cout << "Your application has been submitted successfully!" <<endl;
                    } else 
					{
                        cout << "Error writing to the jobs file." <<endl;
                    }
                } else 
				{
                    cout << "Returning to the candidate menu..." <<endl;
                }
            }
        } else if (choice == 3) // Add candidate ID to the saved job entry
		{
            cout << "Enter the number of the job you want to save: ";
            int jobNumber;
            cin >> jobNumber;

            if (jobNumber < 1 || jobNumber > jobs.size()) //chack for valid input
			{
                cout << "Invalid job number. Please try again.\n";
            } else {
                string selectedJob = jobs[jobNumber - 1];
                // Add candidate ID to the saved job entry
                ofstream savedJobsFile("saved_jobs.txt", ios::app);
                if (savedJobsFile.is_open()) {
                    savedJobsFile << "Candidate ID: " << candidateId << " | " << selectedJob << endl;
                    savedJobsFile.close();
                    cout << "Job saved successfully!"<<endl;
                } else {
                    cout << "Error saving the job."<<endl;
                }
            }
        } else if (choice == 4)//exit this menu
			{
            cout << "Returning to the candidate menu..."<<endl;
            return;
        } else 
		{
            cout << "Invalid choice. Please try again."<<endl;
        }
    }
}

void showCandidateHistory(const string& fileName, const string& candidateId) 
/*  print relevant and unrelevant jobs by application on tham
get:file name (jobs.txt), and id of candidate
return: */
{
    ifstream file(fileName);//file handling
    if (!file.is_open()) {
        cout << "Error opening jobs file.\n";
        return;
    }
	//we will sort to relevant and unrelevant jobs
    vector<string> relevantJobs;    
    vector<string> nonRelevantJobs; 
    string line;

    while (getline(file, line)) //read will file have data
	{
        istringstream iss(line);
        string employerId, jobName, salary, experience, degree, jobType, postDate, applicantCountStr, existingIds;
        getline(iss, employerId, '|');
        getline(iss, jobName, '|');
        getline(iss, salary, '|');
        getline(iss, experience, '|');
        getline(iss, degree, '|');
        getline(iss, jobType, '|');
        getline(iss, postDate, '|');
        getline(iss, applicantCountStr, '|');
        getline(iss, existingIds, '|');
        int applicantCount = stoi(applicantCountStr); //counter for application on that job
        if (existingIds.find(candidateId) != string::npos) //chak for match of id of candidate and submisson
		{
            ostringstream jobDetails;
            jobDetails << "Job Name: " << jobName << endl
                       << "Salary: " << salary << endl
                       << "Experience: " << experience << " years"<<endl
                       << "Degree: " << degree << endl
                       << "Job Type: " << jobType << endl
                       << "Posted On: " << postDate << endl
                       << "Employer ID: " << employerId << endl;
            // add to relevant vector by number of application
            if (applicantCount > 0) 
			{
                relevantJobs.push_back(jobDetails.str());
            } else if (applicantCount == 0)
				{
                nonRelevantJobs.push_back(jobDetails.str());
            }
        }
    }
    file.close();
    // print relevant jobs
    cout << endl<<"--- Relevant Jobs ---" <<endl;
    if (relevantJobs.empty()) 
	{
        cout << "No relevant jobs found."<<endl;
    } else {
        for (const auto& job : relevantJobs) {
            cout << job << "\n";
        }
    }
    // print unrelevant jobs
    cout << endl<<"--- Non-Relevant Jobs ---"<<endl;
    if (nonRelevantJobs.empty()) {
        cout << "No non-relevant jobs found."<<endl;
    } else {
        for (const auto& job : nonRelevantJobs) {
            cout << job << endl;
        }
    }
}

void viewSavedJobs(const string& candidateId) 
/* print all the jobs saved from the candidate with this id
get: Candidate id
return:   */
{
    ifstream savedJobsFile("saved_jobs.txt");//file handling
    if (!savedJobsFile.is_open()) {
        cout << "No saved jobs found or error opening the saved jobs file." <<endl;
        return;
    }
    string line;
    bool hasSavedJobs = false;

    cout << endl<<"--- Saved Jobs ---"<<endl;
    while (getline(savedJobsFile, line)) //read file while file have data
	{
        if (line.find("Candidate ID: " + candidateId) != string::npos) //chack for match in id
		{
            istringstream iss(line);
            string candidateIdField, jobDetails;
            // Skip Candidate ID
            getline(iss, candidateIdField, '|');
            // Extract job details
            getline(iss, jobDetails);
            // Clean job details remove unnecessary parts
            size_t employerIdPos = jobDetails.find('|');
            size_t lastSeparatorPos = jobDetails.find_last_of('|');
            if (employerIdPos != string::npos && lastSeparatorPos != string::npos) // Clean job details remove unnecessary parts
			{
                jobDetails = jobDetails.substr(employerIdPos + 1, lastSeparatorPos - employerIdPos - 1);
            }
			//print data after cleaning
            cout << jobDetails << endl;
            hasSavedJobs = true;
        }
    }

    if (!hasSavedJobs) 
	{
        cout << "You have no saved jobs."<<endl;
    }

    savedJobsFile.close();
}

string getCurrentDate() 
/*
return the current date
get:  
return:string of date in format of "YYYY-MM-DD" */
{
    time_t now = time(0); //using ctime
    tm *ltm = localtime(&now);
    stringstream dateStream;
    dateStream << 1900 + ltm->tm_year << "-" << 1 + ltm->tm_mon << "-" << ltm->tm_mday;
    return dateStream.str();
}

void postNewJob(const string& jobsFileName, const string& employerId) 
/* let employer to add new job
get: the file jobs.txt to add to, id of employer
return:  */
{
    ofstream file(jobsFileName, ios::app);//file handling
    if (!file.is_open()) 
	{
        cout << "Error opening jobs file.";
        return;
    }
	//let employer to add information for new job
    string jobName, salary, experience, degree, jobType;
    cout << "Enter job name: ";
    cin.ignore();//cleaning buffer
    getline(cin, jobName);
    cout << "Enter salary offered: ";
    getline(cin, salary);
    cout << "Enter years of experience required: ";
    getline(cin, experience);
    cout << "Enter the required adjective (if not required enter no): ";
    getline(cin, degree);
    cout << "Is it a full-time or part-time job? ";
    getline(cin, jobType);
    string postDate = getCurrentDate(); //add the date
    int applicantCount = 0;
    cout << "Do you want to post this job? (yes/no): ";//give option to post 
    string confirmation;
    cin >> confirmation;
    if (confirmation == "yes" || confirmation == "Yes")//add job to file if employer want to submit
	{
        file << employerId << " | " << jobName << " | " << salary << " | " << experience << " | " << degree << " | " << jobType << " | " << postDate << " | " << applicantCount << "\n";
        cout << "Job posted successfully!" << endl;
    } else {
        cout << "Job posting canceled. Returning to employer menu..."<< endl;
    }

    file.close();
}



vector<string> getEmployerJobs(const string& jobsFileName, const string& employerId) 
/* search for all the jobs the employer with this id added
get: job file name, id of employer
return: vector of all jobs from employer
*/
{
    ifstream file(jobsFileName);//file + vector handling
    vector<string> employerJobs;
    if (!file.is_open()) 
	{
        cout << "Error opening jobs file." <<endl;
        return employerJobs;
    }
    string line;
    while (getline(file, line)) //chack if line start with employer id
	{
        if (line.find(employerId + " | ") == 0 || (line.find(employerId + "  | ")) == 0) //if start with employer id return the vector
		{
            employerJobs.push_back(line);
        }
    }
    file.close();
    return employerJobs;// return all the jobs the employer add
}

void displayJobs(const vector<string>& employerJobs) 
/* print all jobs from the vector 
get: vector of jobs
return: */
{
    cout << endl<< "--- Published Jobs ---"<<endl;

    for (size_t i = 0; i < employerJobs.size(); ++i) //print all the jobs in the vector
	{
        istringstream iss(employerJobs[i]);
        string jobId, jobName, salary, experience, degree, jobType, postDate, applicantCount, existingIds;

        getline(iss, jobId, '|');         // ID 
        getline(iss, jobName, '|');      // job name
        getline(iss, salary, '|');       // salary
        getline(iss, experience, '|');   // experience
        getline(iss, degree, '|');       // degree
        getline(iss, jobType, '|');      // full-time /part-time
        getline(iss, postDate, '|');     // date of posting
        getline(iss, applicantCount, '|'); // number of candidates
        getline(iss, existingIds, '|');  // list of candidates id

        
        int candidateCount = 0;
        if (!existingIds.empty()) //count candidate
		{
            candidateCount = count(existingIds.begin(), existingIds.end(), ',') + 1;
        }

        cout << i + 1 << ". Job Name: " << jobName << endl;
        cout << "   Posted Date: " << postDate <<endl;
        cout << "   Number of Applicants: " << candidateCount << endl;
    }
}

void displayApplicantDetails(const string& candidatesFile, const string& applicantId)
/* print the details safe to print of candidate
get: file of candidates , id of candidate that send applicant
return:  */
 {
    ifstream candidatesFileStream(candidatesFile);
    string candidateLine;
    bool candidateFound = false;

    while (getline(candidatesFileStream, candidateLine)) //read all the file
	{
        if (candidateLine.find(applicantId) == 0) //search for matching id 
		{
            istringstream candidateStream(candidateLine);
            string candidateId, firstName, lastName, email, dob, phone;
            candidateStream >> candidateId; // id
            string dummyPassword;           // skip password
            candidateStream >> dummyPassword;
            candidateStream >> firstName >> lastName >> email >> dob >> phone;
            cout << "Applicant ID: " << candidateId << endl;
            cout << "Name: " << firstName << " " << lastName <<endl;
            cout << "Email: " << email << endl;
            cout << "Date of Birth: " << dob << endl;
            cout << "Phone: " << phone << endl;
            candidateFound = true;
            break;
        }
    }

    if (!candidateFound) //we didnt get candidate with this id details
	{
        cout << "No details found for applicant ID: " << applicantId << "\n";
    }
}

void displayApplicants(const string& jobDetails, const string& candidatesFile) 
/* print all the applicant for jobs from employer and give option to mark as relevant or not
get:item from employerJobs vector, candidate file to read from
return:    */
{
    istringstream iss(jobDetails);
    string jobId, jobName, salary, experience, degree, jobType, postDate, applicantCount, existingIds;

    // get data of the job
    getline(iss, jobId, '|');
    getline(iss, jobName, '|');
    getline(iss, salary, '|');
    getline(iss, experience, '|');
    getline(iss, degree, '|');
    getline(iss, jobType, '|');
    getline(iss, postDate, '|');
    getline(iss, applicantCount, '|');
    getline(iss, existingIds, '|');
    if (existingIds.empty()) //chack if we have applicant for that job
	{
        cout << "No applicants for this job: " << jobName << endl;
        return;
    }
    cout << endl<<"--- Applicants for Job: " << jobName << endl;
	//new vectors
    vector<string> generalApplicants;
    vector<string> relevantApplicants;
    stringstream ss(existingIds);//what we need
    string applicantId;

    while (getline(ss, applicantId, ',')) //put unrelevant candidate in vector
	{
        generalApplicants.push_back(applicantId);
    }
    while (true)
	{
        if (!generalApplicants.empty()) //print general applicant and count tham
		{
            cout << endl<<"--- General Applicants ---"<<endl;
            int count = 1;
            for (const auto& id : generalApplicants) 
			{
                cout << count++ << ". ";
                displayApplicantDetails(candidatesFile, id);//print candidate information
                cout << endl;
            }
        } else {
            cout << endl<<"No more general applicants."<<endl;
        }
        if (!relevantApplicants.empty()) //chack if we have relevant applicant than print tham and count
		{
            cout << endl<<"--- Relevant Applicants ---" <<endl;
            int count = 1;
            for (const auto& id : relevantApplicants) 
			{
                cout << count++ << ". ";
                displayApplicantDetails(candidatesFile, id);//print candidate information
                cout << endl;
            }
        } else {
            cout << endl<<"No relevant applicants yet."<<endl;
        }
        cout << endl<<"Select an applicant by number from general applicants (or 0 to exit): "; //pick candidate by number
        int choice;
        cin >> choice;
        if (choice == 0) //exit option
		{
            cout << "Returning to job menu..."<<endl;
            break;
        }
        if (choice < 1 || choice > generalApplicants.size()) //out of range
		{
            cout << "Invalid choice. Please try again."<<endl;
        } else {//let employer to select if he want this candidate
            string selectedApplicantId = generalApplicants[choice - 1];
            cout << endl<<"--- Selected Applicant ---"<<endl;
            displayApplicantDetails(candidatesFile, selectedApplicantId);////print candidate information
            cout <<endl<< "Is this applicant relevant for the job? (yes/no): ";
            string relevanceChoice;
            cin >> relevanceChoice;

            if (relevanceChoice == "yes" || relevanceChoice == "Yes") {//employer found this candidate good for the job
                cout << "You marked applicant " << selectedApplicantId << " as relevant.\n";
                relevantApplicants.push_back(selectedApplicantId);
                generalApplicants.erase(generalApplicants.begin() + choice - 1);
            } else if (relevanceChoice == "no" || relevanceChoice == "No") {//not relevant for job
                cout << "You marked applicant " << selectedApplicantId << " as not relevant.\n";
            } else {
                cout << "Invalid input. Returning to applicant menu.\n";
            }
        }
    }
}

void viewPublishedJobs(const string& jobsFileName, const string& candidatesFile, const string& employerId) 
/* 
get: jobs.txt , candidate.txt files name, id of employer
return:  */
{
    vector<string> employerJobs = getEmployerJobs(jobsFileName, employerId);//search for all the jobs the employer with this id added

    if (employerJobs.empty()) 
	{
        cout << "No jobs found for your ID." <<endl;
        return;
    }
	
    displayJobs(employerJobs);//print jobs from the vector of this employer jobs

    while (true) 
	{
        cout << "Choose an option:"<<endl;//menu
        cout << "1. Select a job by number to see candidates details"<<endl;
        cout << "2. Exit to Employer Menu"<<endl;
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;
        if (choice == 1) //see candidate details by number of job
		{
            cout << "Enter the job number to see the candidates' resumes: ";
            int jobNumber;
            cin >> jobNumber;
            if (jobNumber < 1 || jobNumber > employerJobs.size()) //wrong number
			{
                cout << "Invalid job number. Please try again."<<endl;
            } else 
			{                
                displayApplicants(employerJobs[jobNumber - 1], candidatesFile);//display candidates aplication for jobs and mark relevant
                cout<<endl;
            }
        } else if (choice == 2) //exit this menu
		{
            cout << "Returning to the Employer Menu..."<<endl;
            break;
        } else {
            cout << "Invalid choice. Please try again."<<endl;
        }
    }
}

void displayAllCandidates(const string& candidateExpectationsFile, const string& jobsFileName, const string& employerId)
/*display and filter candidate job profile
get:name of the file of candidate job profile, the name of the file of jobs employer post, id of employer
return:     */
{
    ifstream file(candidateExpectationsFile);//file handling
    if (!file.is_open()) 
	{
        cout << "Error opening the candidate expectations file."<<endl;
        return;
    }
    vector<string> candidates;
    string line;
	//put in vector all the profiles of candidate that updated them
    cout << "\n--- Registered Candidates ---\n";
    while (getline(file, line)) {
        candidates.push_back(line);
    }
    file.close();
    if (candidates.empty()) //print if we dont have candidates profiles
	{
        cout << "No candidates are registered in the system.\n";
        return;
    }
    int count = 1;
    for (const auto& candidate : candidates) //print from vector all the profiles of candidate that updated them with serial number
	{
        istringstream iss(candidate);
        string candidateId, degree, age, salary, jobType, location;
        getline(iss, candidateId, '|');
        getline(iss, degree, '|');
        getline(iss, age, '|');
        getline(iss, salary, '|');
        getline(iss, jobType, '|');
        getline(iss, location, '|');
        candidateId = candidateId.substr(candidateId.find(":") + 1);
        degree = degree.substr(degree.find(":") + 1);
        age = age.substr(age.find(":") + 1);
        salary = salary.substr(salary.find(":") + 1);
        jobType = jobType.substr(jobType.find(":") + 1);
        location = location.substr(location.find(":") + 1);
        cout << count++ << ". Candidate ID: " << candidateId << "\n";
        cout << "   Degree: " << degree << "\n";
        cout << "   Age: " << age << "\n";
        cout << "   Expected Salary: " << salary << "\n";
        cout << "   Employment Type: " << jobType << "\n";
        cout << "   Location: " << location << "\n\n";
    }

    while (true) 
	{
        cout << "--- Menu ---\n";//print menu
        cout << "1. Select a Candidate\n";
        cout << "2. Filter Candidates by Criteria\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;

        if (choice == 1) {
            cout << "Enter the number of the candidate you want to select: "; //serial number prom the print 
            int candidateNumber;
            cin >> candidateNumber;
            if (candidateNumber < 1 || candidateNumber > candidates.size()) //out of range
			{
                cout << "Invalid candidate number. Please try again.\n";
            } else 
			{
                string selectedCandidate = candidates[candidateNumber - 1];
                string candidateId = selectedCandidate.substr(selectedCandidate.find("ID: ") + 4, selectedCandidate.find('|') - (selectedCandidate.find("ID: ") + 4));

                cout << "\n--- Selected Candidate ---\n";//print the selected candidate
                cout << selectedCandidate << "\n";
                ifstream jobsFile(jobsFileName);//job file handling
                if (!jobsFile.is_open()) {
                    cout << "Error opening the jobs file.\n";
                    return;
                }
                vector<string> employerJobs;//enter to vector jobs that employer with this id published
                string jobLine;
                while (getline(jobsFile, jobLine)) 
				{
                    if (jobLine.find(employerId + " | ") == 0) {
                        employerJobs.push_back(jobLine);
                    }
                }
                jobsFile.close();
                if (employerJobs.empty()) //no job was published
				{
                    cout << "No jobs found for your ID.\n";
                    return;
                }
				//print all job published that match id
                cout << "\n--- Your Published Jobs ---\n";
                for (size_t i = 0; i < employerJobs.size(); ++i) {
                    cout << i + 1 << ". " << employerJobs[i] << "\n";
                }
				//let employer send to candidate job they posted
                cout << "Enter the number of the job you want to send to the candidate: ";
                int jobNumber;
                cin >> jobNumber;
                if (jobNumber < 1 || jobNumber > employerJobs.size()) //out of range
				{
                    cout << "Invalid job number. Returning to menu.\n";
                } else //send candidate job
				{
                    cout << "\nThe job was successfully sent to the candidate!\n";
                }
            }
        } else if (choice == 2) //filter candidates
		{
            cout << "--- Filter Options ---\n";//menu
            cout << "1. Filter by Degree\n";
            cout << "2. Filter by Age (Descending)\n";
            cout << "3. Filter by Expected Salary (Descending)\n";
            cout << "4. Filter by Employment Type\n";
            cout << "5. Filter by Location\n";
            cout << "Enter your choice: ";
            int filterChoice;
            cin >> filterChoice;
            if (filterChoice == 1) //filter by degree
			{
                cout << "Enter degree to filter: ";
                string degree;
                cin.ignore();
                getline(cin, degree);
                cout << "\n--- Candidates with Degree '" << degree << "' ---\n";
                for (const auto& candidate : candidates) 
				{
                    if (candidate.find("Degree: " + degree) != string::npos)//print all the candidates with that degree
					{
                        cout << candidate << "\n";
                    }
                }
            } else if (filterChoice == 2) //print candidate by age from high to low
			{
                cout << "\n--- Candidates by Age (Descending) ---\n";
                sort(candidates.begin(), candidates.end(), [](const string& a, const string& b) //sort by age in descending order
				{
                    int ageA = stoi(a.substr(a.find("Age: ") + 5, a.find('|', a.find("Age: ")) - (a.find("Age: ") + 5)));
                    int ageB = stoi(b.substr(b.find("Age: ") + 5, b.find('|', b.find("Age: ")) - (b.find("Age: ") + 5)));
                    return ageA > ageB;
                });
                for (const auto& candidate : candidates) //print after sort
				{
                    cout << candidate << "\n";
                }
            } else if (filterChoice == 3) //print candidate by salary from high to low
			{
                cout << "\n--- Candidates by Expected Salary (Descending) ---\n";
                sort(candidates.begin(), candidates.end(), [](const string& a, const string& b) {
                    int salaryA = stoi(a.substr(a.find("Expected Salary: ") + 17, a.find('|', a.find("Expected Salary: ")) - (a.find("Expected Salary: ") + 17)));
                    int salaryB = stoi(b.substr(b.find("Expected Salary: ") + 17, b.find('|', b.find("Expected Salary: ")) - (b.find("Expected Salary: ") + 17)));
                    return salaryA > salaryB;
                });
                for (const auto& candidate : candidates)//print after sort
				{
                    cout << candidate << "\n";
                }
            } else if (filterChoice == 4) //print candidate by full-time / part-time job
			{
                cout << "Enter employment type to filter (full/part): ";
                string jobType;
                cin.ignore();
                getline(cin, jobType);
                cout << "\n--- Candidates for Employment Type '" << jobType << "' ---\n";
                for (const auto& candidate : candidates) //print all matching candidate to the employmentType
				{
                    if (candidate.find("Employment Type: " + jobType) != string::npos) {
                        cout << candidate << "\n";
                    }
                }
            } else if (filterChoice == 5) //print candidates that match the area of job
			{
                cout << "Enter location to filter: ";
                string location;
                cin.ignore();
                getline(cin, location);
                cout << "\n--- Candidates in Location '" << location << "' ---\n";
                for (const auto& candidate : candidates) //print all matching location
				{
                    if (candidate.find("Location: " + location) != string::npos) {
                        cout << candidate << "\n";
                    }
                }
            } else {
                cout << "Invalid filter choice. Returning to menu.\n";
            }
        } else if (choice == 3) //exit
		{
            cout << "Exiting...\n";
            break;
        } else {
            cout << "Invalid choice. Please try again.\n";
        }
    }
}

void recoverAccount(const string& fileName) 
/* to many login failure send mail with password
get: file of the user try to login
return:   */
{
    string id, fileId, filePassword, fileFirstName, fileLastName, fileEmail, fileDob, filePhone;

    while (true) {
        cout << "Too many failed attempts. Please enter your ID: ";
        cin >> id;

        ifstream file(fileName);
        bool idFound = false;

        while (file >> fileId >> filePassword >> fileFirstName >> fileLastName >> fileEmail >> fileDob >> filePhone) {
            if (fileId == id) {
                idFound = true;
                cout << "A recovery code has been sent to your email (" << fileEmail << "). Please check your inbox.\n";
                return;
            }
        }

        if (!idFound) {
            cout << "ID not found in the system. Please try again.\n";
        }
    }
}

void displayAllJobsExceptEmployer(const string& jobsFileName, const string& employerId) 
/* 
get:job txt file, id of employer
return:    */
{
    ifstream file(jobsFileName);
    if (!file.is_open()) //file handling
	{
        cout << "Error opening the jobs file.\n";
        return;
    }
    vector<string> jobs;
    string line;
    while (getline(file, line)) // push to vector all jobs not prom that employer
	{
        if (line.find(employerId + " | ") != 0) {
            jobs.push_back(line);
        }
    }
    file.close();
    if (jobs.empty()) //no jobs from anther employer
	{
        cout << "No jobs found except your own.\n";
        return;
    }
	//print all jobs from other employers
    cout << "\n--- All Jobs (Excluding Your Own) ---\n";
    for (size_t i = 0; i < jobs.size(); ++i) {
        cout << i + 1 << ". " << jobs[i] << "\n";
    }
    while (true) //filter jobs 
	{
        cout << "\n--- Filter Menu ---\n";
        cout << "1. Filter by Salary\n";
        cout << "2. Filter by Job Name\n";
        cout << "3. Filter by Years of Experience\n";
        cout << "4. Filter by Required Degree\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;

        if (choice == 5) //exit job display
		{
            cout << "Exiting filter menu...\n";
            break;
        }
        vector<string> filteredJobs;//vector for jobs after filtering
        if (choice == 1) //push to vector all the jobs with salary equal or grater than input
		{
            cout << "Enter minimum salary: ";
            float minSalary;
            cin >> minSalary;
            cout << "\n--- Jobs with Salary >= " << minSalary << " ---\n";
            for (const auto& job : jobs) {
                istringstream iss(job);
                string employerId, jobName, salary, experience, degree, jobType, postDate, applicantCount;

                getline(iss, employerId, '|');
                getline(iss, jobName, '|');
                getline(iss, salary, '|');
                getline(iss, experience, '|');
                getline(iss, degree, '|');
                getline(iss, jobType, '|');
                getline(iss, postDate, '|');
                getline(iss, applicantCount, '|');

                if (stof(salary) >= minSalary) 
				{
                    filteredJobs.push_back(job);
                }
            }
        } else if (choice == 2) {
            cout << "Enter job name to filter by: ";
            cin.ignore();
            string jobNameFilter;
            getline(cin, jobNameFilter);

            cout << "\n--- Jobs with Name '" << jobNameFilter << "' ---\n";
            for (const auto& job : jobs) {
                if (job.find(jobNameFilter) != string::npos) {
                    filteredJobs.push_back(job);
                }
            }
        } else if (choice == 3) {
            cout << "Enter minimum years of experience: ";
            int minExperience;
            cin >> minExperience;

            cout << "\n--- Jobs with Experience >= " << minExperience << " Years ---\n";
            for (const auto& job : jobs) {
                istringstream iss(job);
                string employerId, jobName, salary, experience, degree, jobType, postDate, applicantCount;

                getline(iss, employerId, '|');
                getline(iss, jobName, '|');
                getline(iss, salary, '|');
                getline(iss, experience, '|');
                getline(iss, degree, '|');
                getline(iss, jobType, '|');
                getline(iss, postDate, '|');
                getline(iss, applicantCount, '|');

                if (stoi(experience) >= minExperience) {
                    filteredJobs.push_back(job);
                }
            }
        } else if (choice == 4) { // Filter by Required Degree
            cout << "Enter required degree to filter by: ";
            cin.ignore();
            string degreeFilter;
            getline(cin, degreeFilter);
            degreeFilter = trim(degreeFilter); //trimming 
            transform(degreeFilter.begin(), degreeFilter.end(), degreeFilter.begin(), ::tolower);

            cout << "\n--- Jobs Requiring Degree '" << degreeFilter << "' ---\n";
            for (const auto& job : jobs) {
                istringstream iss(job);
                string employerId, jobName, salary, experience, degree, jobType, postDate, applicantCount;

                getline(iss, employerId, '|');
                getline(iss, jobName, '|');
                getline(iss, salary, '|');
                getline(iss, experience, '|');
                getline(iss, degree, '|'); 
                getline(iss, jobType, '|');
                getline(iss, postDate, '|');
                getline(iss, applicantCount, '|');

                
                degree = trim(degree);//triming
                transform(degree.begin(), degree.end(), degree.begin(), ::tolower);

                if (degree == degreeFilter) //chack for match in dagre name
				{
                    cout << job << "\n";
                }
            }
        }  else {
            cout << "Invalid choice. Please try again.\n";
            continue;
        }

        if (filteredJobs.empty()) //no job match filter
		{
            cout << "No jobs matched the selected filter.\n";
        } else //print the vector of jobs after filtering
		{
            for (size_t i = 0; i < filteredJobs.size(); ++i) {
                cout << i + 1 << ". " << filteredJobs[i] << "\n";
            }
        }
    }
}

void editOrDeleteJob(const string& jobsFileName, const string& employerId) 
/* let you edit jobs as employer
get:name of jobs file, id of employer
return:   */
{
    ifstream file(jobsFileName);//file handling
    if (!file.is_open()) {
        cout << "Error opening jobs file.\n";
        return;
    }
    vector<string> employerJobs;
    string line;
    while (getline(file, line)) //reed from file and put to vector if have the same id
	{
        if (line.find(employerId + " | ") == 0) {
            employerJobs.push_back(line);
        }
    }
    file.close();
    if (employerJobs.empty()) //employer didnt post any job
	{
        cout << "No jobs found for your ID.\n";
        return;
    }
    while (true) 
	{
        cout << endl<<"--- Your Published Jobs ---\n";
        for (size_t i = 0; i < employerJobs.size(); ++i) //print jobs with serial number 
		{
            cout << i + 1 << ". " << employerJobs[i] << "\n";
		}
        cout << endl<<"Choose an option:"<<endl;//menu
        cout << "1. Edit a Job"<<endl;
        cout << "2. Delete a Job\n";
        cout << "3. Exit to Employer Menu" <<endl;
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;
        if (choice == 1) //edit job
		{
            cout << "\nEnter the number of the job you want to edit: ";
            size_t jobNumber;
            cin >> jobNumber;

            if (jobNumber < 1 || jobNumber > employerJobs.size()) //chack if in range
			{
                cout << "Invalid job number. Returning to menu.\n";
                continue;
            }
			
            string selectedJob = employerJobs[jobNumber - 1];
            cout << "\nSelected Job: " << selectedJob << endl;
            string jobName, salary, experience, degree, jobType;
            stringstream ss(selectedJob);
            string employerIdFromFile, postDate, applicantCount;
			//work on string from employer vector
            getline(ss, employerIdFromFile, '|');
            getline(ss, jobName, '|');
            getline(ss, salary, '|');
            getline(ss, experience, '|');
            getline(ss, degree, '|');
            getline(ss, jobType, '|');
            getline(ss, postDate, '|');
            getline(ss, applicantCount, '|');
			//give employer option to updated or not any filed
            cout << "\n--- Edit Job Details ---\n";
            cout << "Current Job Name: " << jobName << "\nEnter new Job Name (or press Enter to keep current): ";
            cin.ignore();
            string newJobName;
            getline(cin, newJobName);
            if (!newJobName.empty()) jobName = newJobName;
            cout << "Current Salary: " << salary << "\nEnter new Salary (or press Enter to keep current): ";
            string newSalary;
            getline(cin, newSalary);
            if (!newSalary.empty()) salary = newSalary;
            cout << "Current Experience: " << experience << "\nEnter new Experience (or press Enter to keep current): ";
            string newExperience;
            getline(cin, newExperience);
            if (!newExperience.empty()) experience = newExperience;
            cout << "Current Degree: " << degree << "\nEnter new Degree (or press Enter to keep current): ";
            string newDegree;
            getline(cin, newDegree);
            if (!newDegree.empty()) degree = newDegree;
            cout << "Current Job Type: " << jobType << "\nEnter new Job Type (or press Enter to keep current): ";
            string newJobType;
            getline(cin, newJobType);
            if (!newJobType.empty()) jobType = newJobType;
			//print the updated data
            cout << "\n--- Updated Job Details ---\n";
            cout << "Job Name: " << jobName << "\n";
            cout << "Salary: " << salary << "\n";
            cout << "Experience: " << experience << "\n";
            cout << "Degree: " << degree << "\n";
            cout << "Job Type: " << jobType << "\n";
			//give option not to changes 
            cout << "\nDo you want to save these changes? (yes/no): ";
            string confirmation;
            cin >> confirmation;
			//updated after confirm
            if (confirmation == "yes" || confirmation == "Yes") {
                employerJobs[jobNumber - 1] = employerIdFromFile + "| " + jobName + " | " + salary + " | " +
                                              experience + " | " + degree + " | " + jobType + " | " +
                                              postDate + " | " + applicantCount;
                cout << "Job updated successfully!\n";
            } else {
                cout << "Changes discarded. Returning to menu.\n";
            }
        } else if (choice == 2)//delete this job
		{
            cout << endl<<"Enter the number of the job you want to delete: ";
            size_t jobNumber;
            cin >> jobNumber;
            if (jobNumber < 1 || jobNumber > employerJobs.size())//out of range
			{
                cout << "Invalid job number. Returning to menu."<<endl;
                continue;
            }
			//make sure employer want to delete this job
            cout << endl<<"Selected Job: " << employerJobs[jobNumber - 1] << endl;
            cout << "Are you sure you want to delete this job? (yes/no): ";
            string confirmation;
            cin >> confirmation;
			//delete after confirm
            if (confirmation == "yes" || confirmation == "Yes") 
			{
                employerJobs.erase(employerJobs.begin() + jobNumber - 1);
                cout << "Job deleted successfully!"<<endl;
            } else {
                cout << "Deletion canceled. Returning to menu."<<endl;
            }
        } else if (choice == 3)//exit this menu
		{
            cout << "Returning to Employer Menu..."<<endl;
            break;
        } else {
            cout << "Invalid choice. Please try again."<<endl;
        }
    }
    //updated file
    ofstream outFile(jobsFileName, ios::trunc);
    if (!outFile.is_open()) {
        cout << "Error saving updates to jobs file.\n";
        return;
    }

    for (const auto& job : employerJobs) {
        outFile << job << endl;
    }

    outFile.close();
}

void loginFlow(const string& userType, const string& fileName)
/*work on all the login for user from both types
after login continue with the program
get: user type candidate/ employer , file to read from candidate file/ employer file
return:
*/
{
    string id, password;
    int attempts = 3;

    while (attempts > 0) 
	{
        cout << "Enter ID: ";
        cin >> id;
        cout << "Enter Password: ";
        cin >> password;
        if (loginUser(fileName, id, password)) //chack for match with id and password to file
		{
            cout << "Login successful! Welcome!" << endl;//login done
            if (userType == "Candidate")//candidate login screen
			{
                while (true) 
				{
                    cout << endl << "--- Candidate Menu ---" << endl; //candidate menu
                    cout << "1. My requirements" << endl;
                    cout << "2. Access Profile" <<endl;
                    cout << "3. View All Jobs" <<endl;
                    cout << "4. View Application History" <<endl;
                    cout << "5. View Saved Jobs" <<endl;
                    cout << "6. Logout" <<endl;
                    cout << "Enter your choice:";
                    int choice;
                    cin >> choice;
                    if (choice == 1)//add profile for candidate
					{
                        enterCandidateExpectations(id);
                    } else if (choice == 2) //view the profile
					{
                        viewAndEditProfile(fileName, id);
                    } else if (choice == 3)//print all the jobs
					{
                        displayJobs("jobs.txt", id);
                    } else if (choice == 4) //print relevant and unrelevant jobs by application on tham
					{
                        showCandidateHistory("jobs.txt", id);
                    } else if (choice == 5) //print all the jobs saved from the candidate with this id
					{
                        viewSavedJobs(id);
                    } else if (choice == 6) //exiting
					{
                        cout << "Logging out..."<<endl;
                        break;
                    } else {
                        cout << "Invalid choice. Please try again."<<endl;
                    }
                }
            } else if (userType == "Employer") 
			{
                while (true) 
				{
                    cout << endl<<"--- Employer Menu ---"<<endl;//employer menu
                    cout << "1. Post New Job"<<endl;
                    cout << "2. View Published Jobs"<<endl;
                    cout << "3. Edit a Specific Job"<<endl;
                    cout << "4. Candidate search"<<endl;
                    cout << "5. Search Similar Jobs"<<endl;
                    cout << "6. Logout"<<endl;
                    cout << "Enter your choice: ";
                    int choice;
                    cin >> choice;

                    if (choice == 1) //add new job
					{
                        postNewJob("jobs.txt", id);
                    } else if (choice == 2) //see all relevant information about job employer post and applicant from candidates
					{
                        viewPublishedJobs("jobs.txt", "candidates.txt", id);
                    } else if (choice == 3) //edit and delete of jobs 
					{
                        editOrDeleteJob("jobs.txt", id);
                        cout << "Logging out...\n";
                    } else if (choice==4)// show all candidates job profile and let you filter tham
					{
                        displayAllCandidates("candidate_expectations.txt","jobs.txt",id);
                    } else if(choice == 5) {
                        displayAllJobsExceptEmployer("jobs.txt", id);
                    } else if (choice == 6){
                        break;
                    }
                }
            }
            return;
        } else {
            attempts--;
            cout << "Invalid ID or Password. Attempts remaining: " << attempts << "\n";
        }
    }
    recoverAccount(fileName);
}

int main()
{
	while (true) 
	{
        int userTypeChoice;
        cout << "Are you a: " << endl <<"1. Candidate"<<endl << "2. Employer" << endl <<"3. Exit" << endl << "Choose an option: " << endl;
        cin >> userTypeChoice;

        if (userTypeChoice == 3) //user chose exit
		{
            cout << "Goodbye!" <<endl;
            break;
        }
		
		string fileName = (userTypeChoice == 1) ? CANDIDATEFILE : EMPLOYERFILE; //if user enter 1 candidate else employers
        string userType = (userTypeChoice == 1) ? "Candidate" : "Employer";
		
		int actionChoice;
        cout << "Do you want to:" <<endl <<"1. Login" << endl << "2. Register" << endl<< "Choose an option: " <<endl;
        cin >> actionChoice;
		if (actionChoice == 1) //star login based on user input as candidate or employers
		{
            loginFlow(userType, fileName); //login based on user type
		}
		else
		{
			if(actionChoice == 2) // register file name depand on typeof user
			{
				registerUser(fileName); //file by user type
			}
			else //wrong input
			{
				cout << "Invalid choice. Returning to main menu." <<endl;
			}
		}
	}
}