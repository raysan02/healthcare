#include<iostream.h>
#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fstream.h>
#include<process.h>
#include<dos.h>
#define fileName "Record.txt"
#define tempfile "temp.txt"

//admin section
//only admin can enter, add, update and search record of all healthcare workers
class Admin
{
     int id;
     long int salary;
     char firstname[50], lastname[50], designation[30], qualification[30], phone[10], email[50], birthdate[10], address[100], city[50], state[50], experience[3], startdate[10], allergies[50], religion[20], maritalstatus[20], bloodgroup[5];
     char gender;

     public:
         void input_Record();
         void print_Record();
		 void add_Record();
		 void view_Record();
		 void update_Record();
		 char search_Record(int);
		 void delete_Record();

};

//doctor section
//doctor can view all records and add medication
class Doctor : public Admin
{
     int med_id, quantity;
     char med_name[100];

     public:
     void view_Doc()
     {
         Admin::view_Record();
     }

     void input_Med();
     void print_Med();
     void add_Med();
     void view_Med();
};

//pharmacy can only view the medicine records that are added by doctor
class Pharmacy: public Doctor
{
	 public:
	 
	 void view_Pharm()
	 {
		 Doctor::view_Med(); 
	 }
};


//staff can only view the worker records that are added by admin
class Staff: public Admin
{
	 public:
	 
	 void view_Staff()
	 {
		 Admin::view_Record(); 
	 }
};


//function to input worker information
void Admin::input_Record()
{
     cout<<"Input ID:"; cin>>id;
	 cout<<"Input First name:"; cin>>firstname;
     cout<<"Input Last name:"; cin>>lastname;	 
	 cout<<"Input Designation:"; cin>>designation;
	 cout<<"Input Qualifications:"; cin>>qualification;
	 cout<<"Input Email:"; cin>>email;
	 cout<<"Input Birthdate (format: DD/MM/YYYY):"; cin>>birthdate;
	 cout<<"Input Full Address:"; cin>>address;
	 cout<<"Input City:"; cin>>city;
	 cout<<"Input State:"; cin>>state;
	 cout<<"Input Experience:"; cin>>experience;
	 cout<<"Input Salary:"; cin>>salary;
	 cout<<"Input Gender (format: M/F/O): "; cin>>gender;
	 cout<<"Input Work Starting date (format: DD/MM/YYYY):"; cin>>startdate;
	 cout<<"Input Allergies:"; cin>>allergies;
	 cout<<"Input Religion:"; cin>>religion;
	 cout<<"Input Marital status:"; cin>>maritalstatus;
	 cout<<"Input Blood group:"; cin>>bloodgroup;
	 
	 cout<<endl;
}


//function to input medicine information
void Doctor::input_Med()
{
     cout<<"Input Medicine ID:"; cin>>med_id;
	 cout<<"Input Medicine name:"; cin>>med_name;
	 cout<<"Input Quaintiy:"; cin>>quantity;
	 
	 cout<<endl;
}

//function to print worker information
void Admin::print_Record()
{
	cout<<"\t"<<id<<"\t"<<firstname<<"\t"<<lastname<<"\t"<<designation<<"\t"<<qualification<<"\t"<<email<<"\t"<<birthdate<<"\t"<<address<<"\t"<<city<<"\t"<<state<<"\t"<<experience<<"\t"<<salary<<"\t"<<gender<<"\t"<<startdate<<"\t"<<allergies<<"\t"<<religion<<"\t"<<maritalstatus<<"\t"<<bloodgroup<<endl;
} 


//function to print medicine information
void Doctor::print_Med()
{
	cout<<"\t"<<med_id<<"\t"<<med_name<<"\t"<<quantity<<endl;
}


//function to add records into the file
void Admin::add_Record()
{
	 fstream fs;
	 Admin Admi;
	 fs.open(fileName , ios::app);
	 Admi.input_Record();
	 fs.write((char *)&Admi, sizeof(Admi));
	 cout<<endl<<"Successfully added! \n\n";
	 getch();
	 fs.close();
}


//function to add medicine into the file
void Doctor::add_Med()
{
	 fstream fs3;
	 Doctor Doc;
	 fs3.open("Medicine.txt" , ios::app);
	 Doc.input_Med();
	 fs3.write((char *)&Doc, sizeof(Doc));
	 cout<<endl<<"Successfully added! \n\n";
	 getch();
	 fs3.close();
}

//function to show records thats stored into the file
void Admin::view_Record()
{
	 fstream fs;
	 Admin Admi;
	 fs.open(fileName , ios::in);
	 fs.read((char *)&Admi, sizeof(Admi));
	 while(!fs.eof())
	 {
	     Admi.print_Record();
		 fs.read((char *)&Admi, sizeof(Admi));
	 }
	 getch();
	 fs.close();
}


//function to show medicine thats stored into the file
void Doctor::view_Med()
{
	 fstream fs3;
	 Doctor Doc;
	 fs3.open("Medicine.txt" , ios::in);
	 fs3.read((char *)&Doc, sizeof(Doc));
	 while(!fs3.eof())
	 {
	     Doc.print_Med();
		 fs3.read((char *)&Doc, sizeof(Doc));
	 }
	 getch();
	 fs3.close();
}


//searches record through id if record found returns yes or else returns no
char Admin::search_Record(int id)
{
	 if(id == this->id)
	     return 'y';
	 else
		 return 'n';
}

//if the worker id is found that the information is updated
void Admin::update_Record()
{
	 clrscr();
	 Admin admi;
	 int workerId;
	 cout<<endl<<"Enter Worker ID to update: "; cin>>workerId;
	 fstream fs;
	 fs.open(fileName, ios::in | ios::out);
	 long int position;
	 char reply = 'n';
	 fs.read((char *)&admi, sizeof(admi));
	 while(!fs.eof())
	 {
		 reply = admi.search_Record(workerId);
		 if (reply == 'y')
		 {
			 position = fs.tellp();
			 break;
		 }
		 fs.read((char *)&admi, sizeof(admi));
	 }
	 if (reply == 'n')
	 	 cout <<endl<<"Record of worker not found..!!";
	 else
	 {
		 admi.print_Record();
		 cout<<endl<<"New Record: "<<endl;
		 admi.input_Record();
		 fs.seekp(position-sizeof(admi), ios::beg);
		 fs.write((char *)&admi, sizeof(admi));
		 cout<<"Record updated..!!";
	 }
	 getch();
	 fs.close();
}

//if the record is found and it deletes the record
void Admin::delete_Record()
{
	 int workerDelete;
	 Admin admi;
	 cout<<"Enter Worker ID to delete: "; cin>>workerDelete;
	 fstream fs1;
	 fs1.open(fileName, ios::in);
	 fstream fs2;
	 fs2.open(tempfile, ios::out);
	 char reply;
	 fs1.read((char *)&admi, sizeof(admi));
	 while(!fs1.eof())
	 {
		 reply = admi.search_Record(workerDelete);
		 if(reply == 'n')
		 {
			 fs2.write((char *)&admi, sizeof(admi));
		 }
		 fs1.read((char *)&admi, sizeof(admi));
	 }
	 fs1.close();
	 fs2.close();
	 cout<<"Record deleted!!!";
	 getch();
	 remove(fileName);
	 rename(tempfile, fileName);
}


//header to show worker record details
void header()
{
	 cout<<endl;
	 cout<<"        ~~~~~~~~~~~~~~~~    Worker Record Details    ~~~~~~~~~~~~~~~~          "<<endl<<endl;
	 cout<<"ID \tFirst Name \tLast Name \tDesgnation \tQualifications"<<endl;
	 cout<<"Email \tBirth Date \tAddress \tCity \tState"<<endl;
	 cout<<"Experience \tSalary \tGender \tWork Start Data"<<endl;
	 cout<<"Allergies \tReligion \tMarital Status \tBlood group"<<endl;
	 cout<<endl;
}


//header to show medicine details
void header_Med()
{
	 cout<<endl;
	 cout<<"        ~~~~~~~~~~~~~~~~    Medicine Details    ~~~~~~~~~~~~~~~~          "<<endl<<endl;
	 cout<<"Medicine ID \tMedicine Name \tQuantity"<<endl;
	 cout<<endl;
}


//menu for admin side section
void admin_Menu()
{
	 int choice,n,i;
	 Admin a[100];
	 clrscr();
	 do{
		 clrscr();
		 cout<<"1) Add Worker Records"<<endl;
		 cout<<"2) Show Worker Records"<<endl;
		 cout<<"3) Update A Record"<<endl;
		 cout<<"4) Delete A Record"<<endl;
		 cout<<"5) Exit"<<endl;
		 cout<<"Press 5 to exit!"<<endl;
		 cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl<<endl;
		 cout<<"Input your choice[1-5]: ";
		 cin>>choice;
		 switch(choice)
		 {
			 case 1:
			     clrscr();
				 cout<<"Enter number of record you want to add: ";
					 cin>>n;
					 for(i=0; i<n; i++)
					 {
					  	 a[i].add_Record();
					 }
				 break;
				 
			 case 2:
				 clrscr();
				 header();
				 cout<<endl;
				 a[i].view_Record();
				 break;
				 
			 case 3:
				 clrscr();
				 a[i].update_Record();
				 break;
				 
			 case 4:
				 clrscr();
				 a[i].delete_Record();
				 break;
					
			 default:
				 break;
		 }
	 }while(choice<5);
	 getch();
}


//menu for doc side section
void doctor_Menu()
{
	 int choice,n,i;
	 Doctor d[100];
	 clrscr();
	 do{
		 clrscr();
		 cout<<"1) Show Worker Records"<<endl;
		 cout<<"2) Add Medicine Records"<<endl;
		 cout<<"3) View Medicine Record"<<endl;
		 cout<<"4) Exit"<<endl;
		 cout<<"Press 4 to exit!"<<endl;
		 cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl<<endl;
		 cout<<"Input your choice[1-4]: ";
		 cin>>choice;
		 switch(choice)
		 {
			 case 1:
				 clrscr();
				 header();
				 cout<<endl;
				 d[i].view_Doc();
				 break;
				 
			 case 2:
			     clrscr();
				 cout<<"Enter number of medicine you want to add: ";
					 cin>>n;
					 for(i=0; i<n; i++)
					 {
					  	 d[i].add_Med();
					 }
				 break;
				 
			 case 3:
				 clrscr();
				 header_Med();
				 cout<<endl;
				 d[i].view_Med();
				 break;
					
			 default:
				 break;
		 }
	 }while(choice<4);
	 getch();
}


//menu for pharmacy side section
void pharmacy_Menu()
{
	 int choice,n,i;
	 Pharmacy p[100];
	 clrscr();
	 do{
		 clrscr();
		 cout<<"1) View Medicine Record"<<endl;
		 cout<<"2) Exit"<<endl;
		 cout<<"Press 2 to exit!"<<endl;
		 cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl<<endl;
		 cout<<"Input your choice[1-2]: ";
		 cin>>choice;
		 switch(choice)
		 {	 
			 case 1:
				 clrscr();
				 header_Med();
				 cout<<endl;
				 p[i].view_Pharm();
				 break;
					
			 default:
				 break;
		 }
	 }while(choice<2);
	 getch();
}


//menu for staff side section
void staff_Menu()
{
	 int choice,n,i;
	 Staff s[100];
	 clrscr();
	 do{
		 clrscr();
		 cout<<"1) View WorkerRecord"<<endl;
		 cout<<"2) Exit"<<endl;
		 cout<<"Press 2 to exit!"<<endl;
		 cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl<<endl;
		 cout<<"Input your choice[1-2]: ";
		 cin>>choice;
		 switch(choice)
		 {	 
			 case 1:
				 clrscr();
				 header();
				 cout<<endl;
				 s[i].view_Staff();
				 break;
					
			 default:
				 break;
		 }
	 }while(choice<2);
	 getch();
}


//main menu 
void main_Menu()
{
	 int ch;
	 clrscr();
	 do{
		 clrscr();
		 cout<<"        ~~~~~~~~~~~~~~~~    Health Care Worker Database    ~~~~~~~~~~~~~~~~          "<<endl<<endl;
		 cout<<"        ~~~~~~~~~~~~~~~~            Main Menu           ~~~~~~~~~~~~~~~~          "<<endl<<endl;
		 cout<<"1) Admin Menu"<<endl;
		 cout<<"2) Doctor Menu"<<endl;
		 cout<<"3) Pharmacy Menu"<<endl;
		 cout<<"4) Staff Menu"<<endl;
		 cout<<"5) Exit"<<endl;
		 cout<<"choice[1-5]: "; 
		 cin>>ch;
		 switch(ch)
		 {
		 	 case 1: clrscr(); admin_Menu(); break;
			 case 2: clrscr(); doctor_Menu(); break;
			 case 3: clrscr(); pharmacy_Menu(); break;
			 case 4: clrscr(); staff_Menu(); break;
			 default: break;
		 }
	 }while(ch<5);
}


//login secion
void Login()
{
     char username[30], password[30];
	 
	 cout<<"        ~~~~~~~~~~~~~~~~    Health Care Worker Database    ~~~~~~~~~~~~~~~~          "<<endl<<endl;
	 
	 cout<<"Input Username: "; cin>>username;
	 cout<<"Input Password: "; cin>>password;
	 
	 if(strcmp(username, "rutisha") == 0)
	 {
		 if(strcmp(password, "rutisha2202") == 0)
		 {
			 cout<<"Login Successful!"<<endl;
			 getch();
			 main_Menu();
		 }
		 
		 else
		 {
			 cout<<"Login Unsuccessful!"<<endl;
		 }
	 }
	 
	 else
		 {
			 cout<<"Login Unsuccessful!"<<endl;
		 }	 
}

//main section
void main()
{
     clrscr();
	 Login();
	 getch();
}
