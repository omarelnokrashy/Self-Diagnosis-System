#include <iostream>
#include <SFML/Graphics.hpp>
#include <String>
#include<fstream>

using namespace sf;
using namespace std;


RenderWindow window(VideoMode(1920, 1080), "Homepage", Style::Default);

Font font1;
Texture windowbackground, homepagebackground, texteditarea, lbutton, sbutton;//login
Texture window2background, lbutton2, cbutton, texteitor;//signup
Texture window3background, doctorpagebackground, Button5, Button1, Button2, Button3, Button4, HOMEBUTTON;//doctor
Texture window4background, Button9, Button6, Button7, Button8, HOMEBUTTON2;//patient

Texture swindow2, swindow3, swindow4, swindow5, swindow6, swindow8, swindow9, swindow10;
Texture  confirmbutton, Texteditarea2, Texteditarea3, texteditarea8, Texteditarea30;
Texture texteditarea4, texteditarea5, texteditarea6, button15, small_window, swindow20, main2_background, Button;
Texture new_Textarea, new_Textarea2, new_Textarea3, new_Textarea4, new_TextareaGEN, new_TextareaAge, new_TextareaFN;
Texture SMAIN1, SMAIN2, SIX, texteditarea75, backgroundedit;
Texture DoctorSearchback, TeditDcotorSearch, Confirmbutton, BACKground, Button11, Button13;

Mouse mouse;

bool Check = false, Doctorpage = false, Login = true, Signup = false, Signup2 = false, Patientpage = false, cursorVisible = false;
bool Swindow1 = false, Swindow2 = false, Swindow3 = false, Swindow4 = false, Logic_gate = false;
Clock cursorClock;
Time cursorTimer;

int numusers = 0;
//users creats

int numpatients = 0;
//number of patients 

int numdoctors = 0;
//number of doctors

int numdiseases = 0;
//number of diseases

int user_id = 0;
//the id of user who use program now

int current_disease = -1;

string sym[300];
int patient_with_disease[4] = { -1,-1,-1,-1 };
//syptoms of all diseases

int index_role = -1;
//Real Function Structs
//structs
struct user
{
	string role;
	string username;
	string password;
	int id;
};
user users[200];

struct patient
{
	string full_name;
	int id;
	int age;
	string info;
	string gender;
	int no_diagnosed_diseases = 0;
	string diseases_history[15];

};
patient patients[100];

struct doctor
{
	string full_name;
	int id;
	string gender;
	int age;
	string info;
	int num_of_added_diseases;
	string diseases_added[20];
};
doctor doctors[100];

struct disease
{
	int diseaseID;
	string disease_name;
	int num_of_symptoms = 0;
	string symptoms[10];
	string general_info;
	int no_tips = 0;
	string tips[10];
	int num_of_patients = 0;

	float diagnosis_percentage;
};
disease diseases[400];


//functions decleration
bool checklogin(user* users, string Username, string Password, bool& Check);
//void SignUp(string Username, string Password, bool role, int age, string fullname, string info, bool gender);
void search(string nobil[], int w);
void input_syptoms();
void search_for_certain_disease(string disease_name);
void search_for_patients_with_certain_disease(int search_term);
void editDiseaseInfo();
void add_disease();
void clearDiagnosisHistory();
//===========================================================================
//Read input from files
//=======================================================================
void user_files(int& numusers, int& numpatients, int& numdoctors)
{
	ifstream infile("accounts.txt");
	if (infile.fail())
	{
		cout << "Error while openning users file";
		exit(1);
	}

	while (getline(infile, users[numusers].username) && getline(infile, users[numusers].password) && getline(infile, users[numusers].role))
	{

		if (users[numusers].role == "doctor")
		{
			users[numusers].id = numdoctors;
			numdoctors++;
		}
		else if (users[numusers].role == "patient")
		{
			users[numusers].id = numpatients;
			numpatients++;
		}
		numusers++;
	}
	infile.close();
}
void patient_files()
{
	int num1 = 0;
	ifstream infile("patient.txt");
	if (infile.fail())
	{
		cout << "Error while openning patients file";
		exit(1);
	}

	while (getline(infile, patients[num1].full_name) && infile >> patients[num1].age && infile >> patients[num1].gender)
	{
		infile >> patients[num1].no_diagnosed_diseases;
		infile.ignore();
		for (int i = 0; i < patients[num1].no_diagnosed_diseases; i++)
		{
			getline(infile, patients[num1].diseases_history[i]);
		}
		num1++;
	}
	infile.close();
}
void doctor_files()
{
	int num2 = 0;
	ifstream infile("doctors.txt");
	if (infile.fail())
	{
		cout << "Error while openning doctors file";
		exit(1);
	}

	while (getline(infile, doctors[num2].full_name) && infile >> doctors[num2].age && getline(infile, doctors[num2].info))
	{
		infile >> doctors[num2].num_of_added_diseases;
		infile.ignore();
		for (int i = 0; i < doctors[num2].num_of_added_diseases; i++)
		{
			getline(infile, doctors[num2].diseases_added[i]);
		}
		num2++;
	}
	infile.close();
}
void disease_files(int& numdiseases)
{
	ifstream in_file("Diseases.txt");
	if (in_file.fail())
	{
		cout << "Error while openning diseases file";
		exit(1);
	}

	int test;
	int num3 = 0;
	while (!in_file.eof())
	{

		getline(in_file, diseases[num3].disease_name);
		in_file >> diseases[num3].num_of_symptoms;
		in_file.ignore();
		for (int i = 0; i < diseases[num3].num_of_symptoms; i++)
		{
			getline(in_file, diseases[num3].symptoms[i]);

		}
		getline(in_file, diseases[num3].general_info, '/');

		in_file >> diseases[num3].no_tips;
		in_file.ignore();
		for (int j = 0; j < diseases[num3].no_tips; j++)
		{
			getline(in_file, diseases[num3].tips[j]);

		}
		num3++;
		numdiseases++;

	}
	in_file.close();
}
void data(int& numusers, int& numpatients, int& numdoctors)
{
	//user_files(numusers, numpatients, numdoctors);
	//patient_files();
	//doctor_files();
	disease_files(numdiseases);
}
//==========================================================================
//Write output to files
//===========================================
void write_to_users_file()
{
	ofstream out_file("accounts.txt", ios::trunc);
	if (out_file.fail())
	{
		cout << "Error while openning accounts file";
		exit(1);
	}

	for (int i = 0; i < numusers; i++)
	{
		out_file << users[i].username << endl;
		out_file << users[i].password << endl;
		out_file << users[i].role << endl;
	}
	out_file.close();
}
void write_to_patients_file()
{
	ofstream out_file("patient.txt");
	if (out_file.fail())
	{
		cout << "Error while openning patients file";
		exit(1);
	}

	for (int i = 0; i < numpatients; i++)
	{
		out_file << patients[i].full_name << endl;
		out_file << patients[i].age << endl;
		out_file << patients[i].gender << endl;
		out_file << patients[i].no_diagnosed_diseases << endl;

		for (int j = 0; j < patients[i].no_diagnosed_diseases; j++)
		{
			out_file << patients[i].diseases_history[j] << endl;
		}
	}
	out_file.close();
}
void write_to_doctors_file()
{
	ofstream out_file("doctors.txt");
	if (out_file.fail())
	{
		cout << "Error while openning doctors file";
		exit(1);
	}

	for (int i = 0; i < numdoctors; i++)
	{
		out_file << doctors[i].full_name << endl;
		out_file << doctors[i].age << endl;
		out_file << doctors[i].info << endl;
		out_file << doctors[i].num_of_added_diseases << endl;

		for (int j = 0; j < doctors[i].num_of_added_diseases; j++)
		{
			if (doctors[i].diseases_added[j] == "\0")
				continue;
			else
				out_file << doctors[i].diseases_added[j] << endl;
		}
	}
	out_file.close();
}
void write_to_diseases_file()
{
	ofstream out_file("Diseases.txt", ios::trunc);
	if (out_file.fail())
	{
		cout << "Error while openning diseases file";
		exit(1);
	}

	for (int i = 0; i < numdiseases - 1; i++)
	{
		out_file << diseases[i].disease_name << endl;

		out_file << diseases[i].num_of_symptoms << endl;
		for (int j = 0; j < diseases[i].num_of_symptoms; j++)
		{
			out_file << diseases[i].symptoms[j] << endl;
		}

		out_file << diseases[i].general_info << "/" << endl;

		out_file << diseases[i].no_tips << endl;
		for (int k = 0; k < diseases[i].no_tips; k++)
		{
			out_file << diseases[i].tips[k] << endl;
		}
	}
	out_file.close();
}
//=========================================================================

//GUI Structs
struct Loginpage
{
	Sprite background, textbackgroundp, signupbutton, loginbutton, textbackgroundu;
	Text password, username;
};
struct SIGNUP
{
	Sprite confirmbutton1, loginbutton, texteditu, texteditp, New_back1, New_back2;
	Sprite confirmbutton2, Ftextarea, Dtextarea, Ptextarea, Mtextarea, General_info_back, Full_name_back, Age_back;

	Text password, username, Doctor, Patient;
	Text Full_name, Age, General_info_text, Male, Female;

};

struct DOCTORPAGE
{
	Sprite button1, button2, button3, button4, h1button, button5;
};
struct PATIENTPAGE
{
	Sprite button9, button6, button7, button8, h2button;
};
struct Wrong_login
{
	Sprite textarea;
	Text text;
};
struct Delete_history
{
	Text text;
};
struct View_info
{
	Sprite texteditarea1, texteditarea2, texteditarea3, texteditarea4;
	Text text1, text2, text3, text4, background, text5;
};
struct Edit_info
{
	Text text1, text2, text5;
	Sprite texteditarea1, texteditarea2, texteditarea5, button4;
}edit_info;
struct Search_for_disease
{
	Sprite texteditarea, confirmbutton, background;
	Text text;
}search_for_disease;
//===========================================================================


//===========================================================================
//GUI functions drawing
void info_Wrong_login(Wrong_login& wrong_login)
{
	wrong_login.textarea.setTexture(texteditarea);
	wrong_login.text.setFont(font1);
	wrong_login.text.setCharacterSize(30);
	wrong_login.text.setString("Your login info is wrong!!!!");
	wrong_login.text.setFillColor(Color::Black);

	wrong_login.textarea.setPosition(1373.48, 391.18);
	wrong_login.text.setPosition(1383.48, 200);
}
void draw_Wrong_login(Wrong_login wrong_login)
{
	//window.draw(wrong_login.textarea);
	window.draw(wrong_login.text);

}

void info_signup1(SIGNUP& signup)
{

	SMAIN1.loadFromFile("New_Signup/signup reg.png");
	signup.New_back1.setTexture(SMAIN1); //Draw with signup1 function
	signup.New_back1.setPosition(1267, 50.5);

	lbutton2.loadFromFile("Images_Signup/Asset 10.png");
	cbutton.loadFromFile("Images_Signup/Asset 8.png");
	texteitor.loadFromFile("Images_Signup/Asset 9.png");

	new_Textarea.loadFromFile("New_Signup/role.png");
	new_Textarea3.loadFromFile("New_Signup/role.png");


	signup.Dtextarea.setTexture(new_Textarea);
	signup.Dtextarea.setPosition(1378, 379);

	signup.Doctor.setFont(font1);
	signup.Doctor.setCharacterSize(30);
	signup.Doctor.setPosition(1385, 385);
	signup.Doctor.setFillColor(Color::Black);
	signup.Doctor.setString("DOCTOR");


	signup.Ptextarea.setTexture(new_Textarea3);
	signup.Ptextarea.setPosition(1632, 379);
	signup.Patient.setFont(font1);
	signup.Patient.setCharacterSize(30);
	signup.Patient.setPosition(1645, 385);
	signup.Patient.setFillColor(Color::Black);
	signup.Patient.setString("PATIENT");


	signup.loginbutton.setTexture(lbutton2);
	signup.loginbutton.setPosition(1426.9444, 922.f);
	signup.confirmbutton1.setTexture(cbutton);
	signup.confirmbutton1.setPosition(1368.9444, 747.f);

	signup.texteditu.setTexture(texteitor);
	signup.texteditu.setPosition(1326.f, 507.2442);

	signup.texteditp.setTexture(texteitor);
	signup.texteditp.setPosition(1326.f, 643.1767);

	signup.username.setFont(font1);
	signup.username.setPosition(1326 + 15, 517.2442);
	signup.username.setCharacterSize(37);
	signup.username.setString("");
	signup.username.setFillColor(Color::Black);

	signup.password.setFont(font1);
	signup.password.setPosition(1326 + 15, 653.1767);
	signup.password.setCharacterSize(65);
	signup.password.setString("");
	signup.password.setFillColor(Color::Black);

}
void info_signup2(SIGNUP& signup)
{
	SMAIN2.loadFromFile("New_Signup/ADD INFO PANEL.png");
	signup.New_back2.setTexture(SMAIN2); //Draw with signup2 function
	signup.New_back2.setPosition(1273, 28);


	new_Textarea4.loadFromFile("New_Signup/GENDER.png");
	new_Textarea2.loadFromFile("New_Signup/GENDER.png");
	new_TextareaGEN.loadFromFile("New_Signup/GENERAL INFO.png");
	new_TextareaAge.loadFromFile("Images_Login/textbox.png");
	new_TextareaFN.loadFromFile("Images_Login/textbox.png");

	signup.Full_name_back.setTexture(new_TextareaFN);
	signup.Full_name_back.setPosition(1306, 256);


	signup.Full_name.setFont(font1);
	signup.Full_name.setCharacterSize(40);
	signup.Full_name.setPosition(1306, 256);
	signup.Full_name.setFillColor(Color::Black);
	signup.Full_name.setString("");

	signup.Age_back.setTexture(new_TextareaAge);
	signup.Age_back.setPosition(1306, 394);

	signup.Age.setFont(font1);
	signup.Age.setCharacterSize(35);
	signup.Age.setPosition(1313, 412);
	signup.Age.setString("");
	signup.Age.setFillColor(Color::Black);

	signup.Mtextarea.setTexture(new_Textarea4);
	signup.Mtextarea.setPosition(1366, 570);
	signup.Ftextarea.setTexture(new_Textarea2);
	signup.Ftextarea.setPosition(1653, 570);

	signup.confirmbutton2.setTexture(cbutton);
	signup.confirmbutton2.setPosition(1362, 933);

	signup.Female.setFont(font1);
	signup.Female.setPosition(1670, 573);
	signup.Female.setCharacterSize(34);
	signup.Female.setString("Female");
	signup.Female.setFillColor(Color::Black);

	signup.Male.setFont(font1);
	signup.Male.setPosition(1403, 573);
	signup.Male.setCharacterSize(36);
	signup.Male.setString("Male");
	signup.Male.setFillColor(Color::Black);

	signup.General_info_back.setTexture(new_TextareaGEN);
	signup.General_info_back.setPosition(1306, 714);

	signup.General_info_text.setFont(font1);
	signup.General_info_text.setPosition(1306, 714);
	signup.General_info_text.setCharacterSize(30);
	signup.General_info_text.setString("GENERAL INFO");
	signup.General_info_text.setFillColor(Color::Black);

}
void draw_signup1(SIGNUP signup)
{
	window.draw(signup.New_back1);
	window.draw(signup.loginbutton);
	window.draw(signup.confirmbutton1);
	window.draw(signup.texteditp);
	window.draw(signup.texteditu);
	window.draw(signup.username);
	window.draw(signup.password);
	window.draw(signup.Dtextarea);
	window.draw(signup.Doctor);
	window.draw(signup.Ptextarea);
	window.draw(signup.Patient);
}
void draw_signup2(SIGNUP signup)
{
	window.draw(signup.New_back2);
	window.draw(signup.Age_back);
	window.draw(signup.Age);
	window.draw(signup.Ftextarea);
	window.draw(signup.Female);
	window.draw(signup.Mtextarea);
	window.draw(signup.Male);
	window.draw(signup.Full_name_back);
	window.draw(signup.Full_name);
	window.draw(signup.General_info_back);
	window.draw(signup.General_info_text);
	window.draw(signup.confirmbutton2);

}
void info_login(Loginpage& login)
{
	lbutton.loadFromFile("Images_Login/loginbut.png");
	sbutton.loadFromFile("Images_Login/signupbut.png");

	login.signupbutton.setTexture(sbutton);
	login.signupbutton.setPosition(1373.6, 844.f);
	login.loginbutton.setPosition(1422.f, 622.f);
	login.loginbutton.setTexture(lbutton);
	login.background.setTexture(windowbackground);

	texteditarea.loadFromFile("Images_Login/textbox.png");
	login.textbackgroundu.setTexture(texteditarea);
	login.textbackgroundu.setPosition(1373.48, 391.18);
	login.textbackgroundp.setTexture(texteditarea);
	login.textbackgroundp.setPosition(1373.48, 491.24);

	font1.loadFromFile("Font/font.ttf");


	login.username.setFont(font1);
	login.username.setPosition(1373.48 + 15, 400.18);
	login.username.setCharacterSize(36);
	login.username.setString(" ");
	login.username.setFillColor(Color::Black);

	login.password.setFont(font1);
	login.password.setPosition(1373.48 + 15, 500.18);
	login.password.setCharacterSize(65);
	login.password.setString(" ");
	login.password.setFillColor(Color::Black);
}
void draw_login(Loginpage login)
{
	window.draw(login.background);
	window.draw(login.textbackgroundp);
	window.draw(login.textbackgroundu);
	window.draw(login.signupbutton);
	window.draw(login.loginbutton);
	window.draw(login.password);
	window.draw(login.username);

}

void info_doctorpage(DOCTORPAGE& doctorpage)
{
	HOMEBUTTON.loadFromFile("Images_Doctorpage/Asset 25.png");
	Button1.loadFromFile("Images_Doctorpage/Asset 20.png");
	Button2.loadFromFile("Images_Doctorpage/Asset 22.png");
	Button3.loadFromFile("Images_Doctorpage/Asset 26.png");
	Button4.loadFromFile("Images_Doctorpage/Asset 21.png");
	Button5.loadFromFile("Images_Doctorpage/Asset 24.png");


	doctorpage.button1.setTexture(Button1);
	doctorpage.button1.setPosition(474.6, 325.5);

	doctorpage.button2.setTexture(Button2);
	doctorpage.button2.setPosition(471.5, 479.6);

	doctorpage.button3.setTexture(Button3);
	doctorpage.button3.setPosition(471.4, 632.f);

	doctorpage.button4.setTexture(Button4);
	doctorpage.button4.setPosition(625.5, 325.5);

	doctorpage.button5.setTexture(Button5);
	doctorpage.button5.setPosition(622.7, 479.6);

	doctorpage.h1button.setTexture(HOMEBUTTON);
	doctorpage.h1button.setPosition(622.5, 632);
}
void draw_doctorpage(DOCTORPAGE doctorpage)
{
	window.draw(doctorpage.button1);
	window.draw(doctorpage.button2);
	window.draw(doctorpage.button3);
	window.draw(doctorpage.button4);
	window.draw(doctorpage.h1button);
	window.draw(doctorpage.button5);
}

void info_patientpage(PATIENTPAGE& patientpage)
{
	HOMEBUTTON2.loadFromFile("Images_Patientpage/log out.png");
	Button9.loadFromFile("Images_Patientpage/find your disease.png");
	Button6.loadFromFile("Images_Patientpage/delete diagnosis history.png");
	Button7.loadFromFile("Images_Patientpage/view info.png");
	Button8.loadFromFile("Images_Patientpage/edit info.png");

	patientpage.button9.setTexture(Button9);
	patientpage.button9.setPosition(527, 354 - 60);

	patientpage.button6.setTexture(Button6);
	patientpage.button6.setPosition(828, 354 - 60);

	patientpage.button7.setTexture(Button7);
	patientpage.button7.setPosition(527, 544 - 60);

	patientpage.button8.setTexture(Button8);
	patientpage.button8.setPosition(828, 544 - 60);

	patientpage.h2button.setTexture(HOMEBUTTON2);
	patientpage.h2button.setPosition(680, 706 - 60);
}
void draw_patientpage(PATIENTPAGE patientpage)
{
	window.draw(patientpage.button6);
	window.draw(patientpage.button9);
	window.draw(patientpage.button7);
	window.draw(patientpage.button8);
	window.draw(patientpage.h2button);
}

void info_delete_history(Delete_history& delete_history)
{
	delete_history.text.setFont(font1);
	delete_history.text.setFillColor(Color::Black);
	delete_history.text.setCharacterSize(38);
	delete_history.text.setPosition(450, 70);
	delete_history.text.setString("Your Disease history has been deleted!!!!! ");
}
void draw_delete_history(Delete_history delete_history)
{
	window.draw(delete_history.text);
}

//Main 4 pages done 
// 
/////////////////////////////////////////////////////

//patient
void info_view_info(View_info& view_info, patient* patients)
{


	texteditarea4.loadFromFile("PATIENT_VIEW_INFO/te.png");
	view_info.texteditarea1.setTexture(texteditarea4);
	view_info.texteditarea1.setPosition(396, 62 + 93 * 0);

	view_info.texteditarea2.setTexture(texteditarea4);
	view_info.texteditarea2.setPosition(396, 62 + 93 * 1);

	view_info.texteditarea3.setTexture(texteditarea4);
	view_info.texteditarea3.setPosition(396, 62 + 93 * 2);

	view_info.texteditarea4.setTexture(texteditarea4);
	view_info.texteditarea4.setPosition(396, 62 + 93 * 3);

	view_info.text1.setFont(font1);
	view_info.text1.setCharacterSize(30);
	view_info.text1.setFillColor(Color::Black);
	view_info.text1.setPosition(396 + 20, 65 + 93 * 0);
	view_info.text1.setString(patients[user_id].full_name);

	view_info.text2.setFont(font1);
	view_info.text2.setCharacterSize(30);
	view_info.text2.setFillColor(Color::Black);
	view_info.text2.setPosition(396 + 20, 65 + 93 * 1);
	view_info.text2.setString(to_string(patients[user_id].age));

	view_info.text3.setFont(font1);
	view_info.text3.setCharacterSize(30);
	view_info.text3.setFillColor(Color::Black);
	view_info.text3.setPosition(396 + 20, 65 + 93 * 2);
	view_info.text3.setString(patients[user_id].gender);

	view_info.text4.setFont(font1);
	view_info.text4.setCharacterSize(30);
	view_info.text4.setFillColor(Color::Black);
	view_info.text4.setPosition(396 + 20, 65 + 93 * 3);
	view_info.text4.setString(to_string(user_id));

}
void info_edit_info(Edit_info& edit_info)
{
	Button11.loadFromFile("EDIT_INFO/Asset 4.png");

	edit_info.button4.setTexture(Button11);
	edit_info.button4.setPosition(275, 788);

	texteditarea6.loadFromFile("EDIT_INFO/Asset 7.png");
	texteditarea8.loadFromFile("EDIT_INFO/GENERAL INFO.png");

	edit_info.texteditarea1.setTexture(texteditarea6);
	edit_info.texteditarea1.setPosition(45, 222);

	edit_info.texteditarea2.setTexture(texteditarea6);
	edit_info.texteditarea2.setPosition(45, 374);

	edit_info.texteditarea5.setTexture(texteditarea8);
	edit_info.texteditarea5.setPosition(45, 540);

	edit_info.text1.setFont(font1);
	edit_info.text1.setCharacterSize(40);
	edit_info.text1.setPosition(55, 230);
	edit_info.text1.setString("");
	edit_info.text1.setFillColor(Color::Black);

	edit_info.text2.setFont(font1);
	edit_info.text2.setCharacterSize(42);
	edit_info.text2.setPosition(55, 385);
	edit_info.text2.setString("");
	edit_info.text2.setFillColor(Color::Black);

	edit_info.text5.setFont(font1);
	edit_info.text5.setCharacterSize(30);
	edit_info.text5.setPosition(55, 545);
	edit_info.text5.setString("");
	edit_info.text5.setFillColor(Color::Black);
}
//change text entered

void info_and_draw_SEARCH_FOR_DISEASE()
{
	Text DoctorSearch, Swindowtext1, Swindowtext2[10], Swindowtext3, Swindowtext4[4], Swindow2text[4][4];
	Sprite ConfirmButton, DOCTORSEARCHTEDIT;

	Texture swindow2back, swindow2textarea, swindow2textarea2;
	swindow2back.loadFromFile("ALL_IN_ONE/view patient with disease/Back.png");
	swindow2textarea.loadFromFile("ALL_IN_ONE/view patient with disease/text area.png");
	swindow2textarea2.loadFromFile("ALL_IN_ONE/view patient with disease/text area.png");

	Sprite Swindow2back, Swindow2textarea, Swindow2textarea2[4];

	Swindow2back.setTexture(swindow2back);
	Swindow2textarea.setTexture(swindow2textarea);
	Swindow2textarea.setPosition(20, 20);


	for (int counter = 0; counter < 4; counter++)
	{
		Swindow2textarea2[counter].setTexture(swindow2textarea2);
		Swindow2textarea2[counter].setPosition(20, (450 * counter) + 28);
	}


	for (int counter = 0; counter < 4; counter++)
	{
		for (int counter2 = 0; counter2 < 4; counter2++)
		{

			Swindow2text[counter][counter2].setFont(font1);
			Swindow2text[counter][counter2].setCharacterSize(40);
			Swindow2text[counter][counter2].setFillColor(Color::Black);
			Swindow2text[counter][0].setPosition(270, (450 * (counter)) + 76);
			Swindow2text[counter][1].setPosition(270, (450 * (counter)) + 76 + 65);
			Swindow2text[counter][2].setPosition(270, (450 * (counter)) + 76 + 65 + 65);
			Swindow2text[counter][3].setPosition(270, (450 * (counter)) + 76 + 65 + 65 + 65);

			Swindow2text[counter][0].setString("");
			Swindow2text[counter][1].setString("");
			Swindow2text[counter][2].setString("");
			Swindow2text[counter][3].setString("");

		}
	}

	Texture swindowback, swindowtextarea, viewbutton;
	swindowback.loadFromFile("ALL_IN_ONE/disease info/back.png");
	swindowtextarea.loadFromFile("ALL_IN_ONE/disease info/Asset 9.png");
	viewbutton.loadFromFile("ALL_IN_ONE/disease info/Asset 8.png");

	Sprite Swindowback, Swindowtextarea, Viewbutton;

	Swindowback.setTexture(swindowback);
	Swindowtextarea.setTexture(swindowtextarea);
	Swindowtextarea.setPosition(45, 45);

	Viewbutton.setTexture(viewbutton);
	Viewbutton.setPosition(1175, 750);

	Swindowtext1.setFont(font1);
	Swindowtext1.setFillColor(Color::Black);
	Swindowtext1.setCharacterSize(24);
	Swindowtext1.setPosition(60, 50);
	Swindowtext1.setString("");
	for (int m = 0; m < 8; m++) {
		Swindowtext2[m].setFont(font1);
		Swindowtext2[m].setFillColor(Color::Black);
		Swindowtext2[m].setCharacterSize(22);
		Swindowtext2[m].setPosition(50, 98 + (40 * m));
		Swindowtext2[m].setString("");
	}

	Swindowtext3.setFont(font1);
	Swindowtext3.setFillColor(Color::Black);
	Swindowtext3.setCharacterSize(22);
	Swindowtext3.setPosition(50, 420);
	Swindowtext3.setString("");

	for (int m = 0; m < 4; m++) {
		Swindowtext4[m].setFont(font1);
		Swindowtext4[m].setFillColor(Color::Black);
		Swindowtext4[m].setCharacterSize(22);
		Swindowtext4[m].setPosition(50, 620 + (m * 50));
		Swindowtext4[m].setString("");
	}

	string text_info = "";
	string var = "";

	DoctorSearchback.loadFromFile("ALL_IN_ONE/search for disease/back.png");
	Confirmbutton.loadFromFile("ALL_IN_ONE/search for disease/Asset 11.png");
	TeditDcotorSearch.loadFromFile("ALL_IN_ONE/search for disease/Asset 12.png");

	ConfirmButton.setTexture(Confirmbutton);
	ConfirmButton.setPosition(240, 705);

	DOCTORSEARCHTEDIT.setTexture(TeditDcotorSearch);
	DOCTORSEARCHTEDIT.setPosition(30, 560);

	DoctorSearch.setFont(font1);
	DoctorSearch.setCharacterSize(55);
	DoctorSearch.setFillColor(Color::Black);
	DoctorSearch.setString("");
	DoctorSearch.setPosition(35, 565);

	RenderWindow window3(VideoMode(1635, 920), "well-known Info about disease", Style::Default);
	Sprite DOCTORSEARCHBACK;
	DOCTORSEARCHBACK.setTexture(DoctorSearchback);
	//string text= "";
	int counter5 = 0;

	while (window3.isOpen())
	{
		RectangleShape mouseshadow(Vector2f(15, 15));
		RectangleShape cursor(Vector2f(5, 0));
		cursor.setFillColor(Color::Black);

		mouseshadow.setPosition(mouse.getPosition().x - 140, mouse.getPosition().y - 100);
		mouseshadow.setFillColor(Color::Black);


		DoctorSearch.setString(var);
		Event event3;
		while (window3.pollEvent(event3))
		{
			if (event3.type == Event::Closed)
			{

				for (int i = 0; i < 4; i++) {
					patient_with_disease[i] = -1;
				}
				Swindow1 = false;
				Swindow2 = false;
				current_disease = -1;
				window3.close();
			}
			if (event3.type == Event::TextEntered && event3.key.code != Keyboard::BackSpace)
			{
				var += static_cast<char>(event3.text.unicode);

			}
			if (Keyboard::isKeyPressed(Keyboard::Backspace) && var.size() > 0 && Keyboard::isKeyPressed(Keyboard::BackSpace))
			{
				var.resize(var.size() - 1);
			}

			if (Mouse::isButtonPressed(Mouse::Left) && mouseshadow.getGlobalBounds().intersects(ConfirmButton.getGlobalBounds()) && Doctorpage == true)
			{
				search_for_certain_disease(var);
				Swindow1 = true;
				if (current_disease != -1) {
					Swindowtext1.setString(diseases[current_disease].disease_name);
					for (int m = 0; m < 8; m++) {

						Swindowtext2[m].setString(diseases[current_disease].symptoms[m]);
					}
					int te = -1;
					for (int i = 0; i < diseases[current_disease].general_info.size(); i++) {
						if (diseases[current_disease].general_info[i] == ' ') {
							te = i;
						}
						Swindowtext3.setString(diseases[current_disease].general_info.substr(0, i));
						if (Swindowtext3.getLocalBounds().width > 840 && te != -1) {
							diseases[current_disease].general_info[te] = '\n';
							i = te;
							te = -1;
						}
					}
					for (int m = 0; m < 4; m++) {
						int lastSpace = -1;
						for (int i = 0; i < diseases[current_disease].tips[m].size(); i++) {
							if (diseases[current_disease].tips[m][i] == ' ') {
								lastSpace = i;
							}
							Swindowtext4[m].setString(diseases[current_disease].tips[m].substr(0, i));
							if (Swindowtext4[m].getLocalBounds().width > 840 && lastSpace != -1) {
								diseases[current_disease].tips[m][lastSpace] = '\n';
								i = lastSpace;
								lastSpace = -1;
							}
						}

						Swindowtext4[m].setString(diseases[current_disease].tips[m]);
					}
					search_for_patients_with_certain_disease(current_disease);
					for (int counter = 0; counter < 4; counter++)
					{
						if (patient_with_disease[counter] == -1) {
							break;
						}
						else {
							Swindow2text[counter][0].setString(patients[patient_with_disease[counter]].full_name);
							Swindow2text[counter][1].setString(to_string(patients[patient_with_disease[counter]].age));
							Swindow2text[counter][2].setString(patients[patient_with_disease[counter]].gender);
							Swindow2text[counter][3].setString(patients[patient_with_disease[counter]].info);
						}

					}
				}
				else {
					Swindowtext1.setString("There is no corresponding disease");
				}

			}
			if (Mouse::isButtonPressed(Mouse::Left) && mouseshadow.getGlobalBounds().intersects(DOCTORSEARCHTEDIT.getGlobalBounds()) && Doctorpage == true)
			{
				counter5 = 100;
			}
			if (counter5 == 100 && event3.type == Event::TextEntered && Doctorpage == true && event3.text.unicode != Keyboard::BackSpace)
			{
				var += static_cast<char>(event3.text.unicode);

				if (Keyboard::BackSpace && var.size() > 0)
				{
					var.resize(var.size() - 1);
				}
			}
			if (Swindow1 == true && mouseshadow.getGlobalBounds().intersects(Swindowtextarea.getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left))
			{
				counter5 = 101;
			}
			if (Swindow1 == true && mouseshadow.getGlobalBounds().intersects(Viewbutton.getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left))
			{
				Swindow1 = false;
				Swindow2 = true;
			}
			if (event3.type == Event::MouseWheelScrolled && Swindow2 == true && Swindow1 == false)
			{
				for (int counter = 0; counter < 4; counter++)
				{

					if (event3.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
					{
						Swindow2textarea2[counter].move(0.f, event3.mouseWheelScroll.delta * 30.f);
						Swindow2text[counter][0].move(0.f, event3.mouseWheelScroll.delta * 30.f);
						Swindow2text[counter][1].move(0.f, event3.mouseWheelScroll.delta * 30.f);
						Swindow2text[counter][2].move(0.f, event3.mouseWheelScroll.delta * 30.f);
						Swindow2text[counter][3].move(0.f, event3.mouseWheelScroll.delta * 30.f);
					}

				}
			}


		}


		if (cursorClock.getElapsedTime().asMilliseconds() >= 500)
		{
			cursorVisible = !cursorVisible;
			cursorClock.restart();
		}

		if (event3.type == Event::MouseButtonReleased && mouseshadow.getGlobalBounds().intersects(DOCTORSEARCHTEDIT.getGlobalBounds()))
		{
			counter5 = 100;
			cursorVisible = true;
		}
		if (cursorVisible == true && counter5 == 100)
		{
			cursor.setSize(Vector2f(2, DOCTORSEARCHTEDIT.getLocalBounds().height * 0.6));
			cursor.setPosition(DoctorSearch.getPosition().x + DoctorSearch.getLocalBounds().width + 15, DoctorSearch.getPosition().y + 16);
		}

		if (Doctorpage == true && Check == true && Swindow1 == false && Swindow2 == false)
		{
			window3.clear(Color::Blue);
			window3.draw(DOCTORSEARCHBACK);
			window3.draw(ConfirmButton);
			window3.draw(DOCTORSEARCHTEDIT);;
			window3.draw(DoctorSearch);
			window3.draw(cursor);
			window3.draw(mouseshadow);
			window3.display();
		}
		if (Swindow1 == true && Doctorpage == true && Check == true && Swindow2 == false)
		{
			window3.clear(Color::Black);
			window3.draw(Swindowback);
			window3.draw(Swindowtextarea);
			window3.draw(Viewbutton);
			window3.draw(Swindowtext1);
			for (int m = 0; m < 10; m++) {
				window3.draw(Swindowtext2[m]);
			}

			window3.draw(Swindowtext3);
			for (int c = 0; c < 4; c++) {
				window3.draw(Swindowtext4[c]);
			}
			window3.draw(mouseshadow);
			window3.display();
		}
		if (Swindow2 == true && Doctorpage == true && Check == true && Swindow1 == false)
		{
			window3.clear(Color::Green);
			window3.draw(Swindow2back);
			//window3.draw(Swindow2textarea);
			for (int counter4 = 0; counter4 < 4; counter4++)
			{
				window3.draw(Swindow2textarea2[counter4]);
			}
			for (int counter = 0; counter < 4; counter++)
			{
				for (int counter2 = 0; counter2 < 4; counter2++)
				{
					window3.draw(Swindow2text[counter][counter2]);
				}

			}
			window3.draw(mouseshadow);
			window3.display();
		}
	}
	/*if (Swindow1 == true)
	{
		Texture back1, text_area_small, patientsbutton;
		Sprite Back1, Text_area_small, Patientsbutton;
		back1.loadFromFile("ALL_IN_ONE/disease info/back.png");
		Back1.setTexture(back1);

		text_area_small.loadFromFile("ALL_IN_ONE/disease info/Asset 9.png");
		Text_area_small.setTexture(text_area_small);
		Text_area_small.setPosition(40, 40);

		patientsbutton.loadFromFile("ALL_IN_ONE/disease info/Asset 8.png");
		Patientsbutton.setTexture(patientsbutton);
		Patientsbutton.setPosition(460, 795);

		RenderWindow swindow990(VideoMode(1920, 1080), "test", Style::Default);
		while (swindow990.isOpen())
		{
			RectangleShape mouseshadow(Vector2f(15, 15));
			mouseshadow.setPosition(mouse.getPosition().x - 145, mouse.getPosition().y - 100);
			mouseshadow.setFillColor(Color::Black);

			Event sevent;
			while (swindow990.pollEvent(sevent))
			{
				if (sevent.type == Event::Closed)
				{
					swindow990.close();

				}
			}
			swindow990.clear(Color::Blue);
			swindow990.draw(Back1);
			swindow990.draw(Text_area_small);
			swindow990.draw(Patientsbutton);
			swindow990.display();

		}
	}*/
}

void draw_find_your_disease()
{
	Texture small_window_3, Tedit;
	Sprite window3back, Background;
	Text  Swindowtext1, Swindowtext2[10], Swindowtext3, Swindowtext4[4], Swindow2text[10];


	Tedit.loadFromFile("FIND_YOUR_DISEASE/dd.png");
	Background.setTexture(Tedit);
	Background.setPosition(43, 43);

	small_window_3.loadFromFile("FIND_YOUR_DISEASE/Asset 4.png");
	window3back.setTexture(small_window_3);

	///////////////////
	Swindowtext1.setFont(font1);
	Swindowtext1.setFillColor(Color::Black);
	Swindowtext1.setCharacterSize(24);
	Swindowtext1.setPosition(60, 50);
	Swindowtext1.setString("");
	for (int m = 0; m < 8; m++) {
		Swindowtext2[m].setFont(font1);
		Swindowtext2[m].setFillColor(Color::Black);
		Swindowtext2[m].setCharacterSize(22);
		Swindowtext2[m].setPosition(50, 98 + (40 * m));
		Swindowtext2[m].setString("");
	}

	Swindowtext3.setFont(font1);
	Swindowtext3.setFillColor(Color::Black);
	Swindowtext3.setCharacterSize(22);
	Swindowtext3.setPosition(50, 420);
	Swindowtext3.setString("");

	for (int m = 0; m < 4; m++) {
		Swindowtext4[m].setFont(font1);
		Swindowtext4[m].setFillColor(Color::Black);
		Swindowtext4[m].setCharacterSize(22);
		Swindowtext4[m].setPosition(50, 620 + (m * 50));
		Swindowtext4[m].setString("");
	}

	RectangleShape mouseshadow(Vector2f(15, 15));
	RenderWindow window2(VideoMode(1635, 920), "Find your disease");
	window2.setPosition(Vector2i(0, 0));
	mouseshadow.setPosition(mouse.getPosition().x - 140, mouse.getPosition().y - 100);
	mouseshadow.setFillColor(Color::Black);

	swindow2.loadFromFile("FIND_YOUR_DISEASE/find your disease window.png");
	Texteditarea2.loadFromFile("FIND_YOUR_DISEASE/Tarea.png");

	Text textitem[150];
	for (int counter = 0; counter < 150; counter++)
	{
		textitem[counter].setFont(font1);
		textitem[counter].setCharacterSize(30);
		textitem[counter].setString(sym[counter]);
		textitem[counter].setFillColor(Color::Black);
		textitem[counter].setPosition(1052, (counter * 83) + 53);
	}
	Sprite sbackground2;
	sbackground2.setTexture(swindow2);

	Sprite rect_search[150];
	Text rect_result[20];
	Sprite button;


	confirmbutton.loadFromFile("FIND_YOUR_DISEASE/confirm.png");
	button.setTexture(confirmbutton);
	button.setPosition(672, 713);

	string send[20];

	int counter2 = 0;
	for (int counter = 0; counter < 150; counter++)
	{
		rect_search[counter].setTexture(Texteditarea2);
		rect_search[counter].setPosition(1032, (counter * 83) + 40);
	}

	for (int counter = 0; counter < 20; counter++)
	{
		rect_result[counter].setFont(font1);
		rect_result[counter].setPosition(90, (counter * 47) + 530);
		rect_result[counter].setString("");
		rect_result[counter].setCharacterSize(30);
		rect_result[counter].setFillColor(Color::Black);
	}
	while (window2.isOpen())
	{
		RectangleShape mouseshadow(Vector2f(15, 15));
		mouseshadow.setPosition(mouse.getPosition().x - 140, mouse.getPosition().y - 100);
		mouseshadow.setFillColor(Color::Black);
		Event event2;
		while (window2.pollEvent(event2))
		{
			if (event2.type == Event::Closed)
			{
				window2.close();
			}
			if (event2.type == Event::MouseWheelScrolled)
			{

				for (int counter = 0; counter < 150; counter++) {
					if (event2.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
					{
						rect_search[counter].move(0.f, event2.mouseWheelScroll.delta * 40.f);
						textitem[counter].move(0.f, event2.mouseWheelScroll.delta * 40.f);
					}
				}
			}

			if (Mouse::isButtonPressed(Mouse::Left))
			{
				for (int counter = 0; counter < 150; counter++)
				{

					FloatRect var = textitem[counter].getGlobalBounds();
					if (var.contains(event2.mouseButton.x, event2.mouseButton.y))
					{

						rect_result[counter2].setString(textitem[counter].getString());
						counter2++;

					}

				}
			}
			if (Mouse::isButtonPressed(Mouse::Left) && mouseshadow.getGlobalBounds().intersects(button.getGlobalBounds()))
			{
				Logic_gate = true;
				for (int i = 0; i < 20; i++)
				{
					send[i] = rect_result[i].getString();
				}
				search(send, counter2);
				if (current_disease != -1) {
					patients[user_id].diseases_history[patients[user_id].no_diagnosed_diseases] = diseases[current_disease].disease_name;
					patients[user_id].no_diagnosed_diseases++;
					Swindowtext1.setString(diseases[current_disease].disease_name);
					for (int m = 0; m < 8; m++) {

						Swindowtext2[m].setString(diseases[current_disease].symptoms[m]);
					}
					int te = -1;
					for (int i = 0; i < diseases[current_disease].general_info.size(); i++) {
						if (diseases[current_disease].general_info[i] == ' ') {
							te = i;
						}
						Swindowtext3.setString(diseases[current_disease].general_info.substr(0, i));
						if (Swindowtext3.getLocalBounds().width > 840 && te != -1) {
							diseases[current_disease].general_info[te] = '\n';
							i = te;
							te = -1;
						}
					}
					for (int m = 0; m < 4; m++) {
						int lastSpace = -1;
						for (int i = 0; i < diseases[current_disease].tips[m].size(); i++) {
							if (diseases[current_disease].tips[m][i] == ' ') {
								lastSpace = i;
							}
							Swindowtext4[m].setString(diseases[current_disease].tips[m].substr(0, i));
							if (Swindowtext4[m].getLocalBounds().width > 840 && lastSpace != -1) {
								diseases[current_disease].tips[m][lastSpace] = '\n';
								i = lastSpace;
								lastSpace = -1;
							}
						}

						Swindowtext4[m].setString(diseases[current_disease].tips[m]);
					}
				}
				else {
					Swindowtext1.setString("There is no corresponding disease");
				}

			}


		}
		if (Patientpage == true && Logic_gate == false)
		{
			window2.clear(Color::White);
			window2.draw(sbackground2);

			for (int counter = 0; counter < 150; counter++)
			{
				window2.draw(rect_search[counter]);
				window2.draw(textitem[counter]);
			}
			for (int counter = 0; counter < 20; counter++)
			{
				window2.draw(rect_result[counter]);
			}

			window2.draw(button);
			window2.display();
		}
		if (Logic_gate == true && Patientpage == true)
		{
			window2.clear(Color::Cyan);
			window2.draw(window3back);
			window2.draw(Background);
			window2.draw(Swindowtext1);
			for (int m = 0; m < 10; m++) {
				window2.draw(Swindowtext2[m]);
			}

			window2.draw(Swindowtext3);
			for (int c = 0; c < 4; c++) {
				window2.draw(Swindowtext4[c]);
			}
			window2.display();



		}

	}



}

void info_view_draw_info_doctor()
{
	Texture Area[4];
	Sprite BACKGROUND99;
	Texture GenArea;
	Sprite TextEditArea[4], GenEditArea;
	Text TextInput[4];
	string info[4];
	info[0] = doctors[user_id].full_name;
	info[1] = to_string(doctors[user_id].age);
	info[2] = doctors[user_id].gender;
	info[3] = to_string(user_id);

	for (int counter = 0; counter < 4; counter++)
	{
		Area[counter].loadFromFile("ALL_IN_ONE/view doctor info/Asset 31.png");

		TextEditArea[counter].setTexture(Area[counter]);
		TextEditArea[counter].setPosition(200, (93 * counter) + 57);

		TextInput[counter].setFont(font1);
		TextInput[counter].setCharacterSize(30);
		TextInput[counter].setPosition(48, (93 * counter) + 65);
		TextInput[counter].setString(info[counter]);
		TextInput[counter].setFillColor(Color::Black);
	}
	Text TextInputG;
	TextInputG.setFont(font1);
	TextInputG.setCharacterSize(30);
	TextInputG.setPosition(48, 532);
	TextInputG.setString(doctors[user_id].info);

	GenArea.loadFromFile("ALL_IN_ONE/view doctor info/general info.png");
	GenEditArea.setTexture(GenArea);
	GenEditArea.setPosition(40, 532);
	BACKground.loadFromFile("ALL_IN_ONE/view doctor info/edit info back.png");
	BACKGROUND99.setTexture(BACKground);

	RenderWindow window9(VideoMode(1635, 920), "Edit info", Style::Default);
	while (window9.isOpen())
	{
		RectangleShape mouseshadow(Vector2f(15, 15));
		mouseshadow.setPosition(mouse.getPosition().x - 140, mouse.getPosition().y - 100);
		mouseshadow.setFillColor(Color::Black);
		Event event9;
		while (window9.pollEvent(event9))
		{
			if (event9.type == Event::Closed)
			{
				window9.close();
			}

		}
		window9.clear();
		window9.draw(BACKGROUND99);
		for (int counter = 0; counter < 4; counter++)
		{
			window9.draw(TextEditArea[counter]);
			window9.draw(TextInput[counter]);
		}
		window9.draw(GenEditArea);
		window9.draw(TextInputG);
		window9.display();
	}


}
void info_edit_draw_info_doctor()
{
	Texture GArea, AArea, NArea, Button, BACK;
	Text Gtext, Atext, Ntext;


	Sprite Garea, Aarea, Narea, Confirm, Back;

	BACK.loadFromFile("ALL_IN_ONE/edit doctor info/edit info back.png");
	Back.setTexture(BACK);
	GArea.loadFromFile("ALL_IN_ONE/edit doctor info/general info.png");
	Garea.setTexture(GArea);
	Garea.setPosition(40, 532);
	AArea.loadFromFile("ALL_IN_ONE/edit doctor info/Asset 31.png");
	Aarea.setTexture(AArea);
	Aarea.setPosition(40, 360);
	NArea.loadFromFile("ALL_IN_ONE/edit doctor info/Asset 31.png");
	Narea.setTexture(NArea);
	Narea.setPosition(40, 208);
	Button.loadFromFile("ALL_IN_ONE/edit doctor info/Asset 27.png");
	Confirm.setTexture(Button);
	Confirm.setPosition(366, 792);

	Gtext.setFont(font1);
	Gtext.setCharacterSize(40);
	Gtext.setFillColor(Color::Black);
	Gtext.setString(doctors[0].info);
	Gtext.setPosition(50, 540);

	Atext.setFont(font1);
	Atext.setCharacterSize(44);
	Atext.setFillColor(Color::Black);
	Atext.setString("");
	Atext.setPosition(50, 372);

	Ntext.setFont(font1);
	Ntext.setCharacterSize(44);
	Ntext.setFillColor(Color::Black);
	Ntext.setString("");
	Ntext.setPosition(50, 222);

	int counter4 = 0;

	RenderWindow window6(VideoMode(1635, 920), "Edit info", Style::Default);

	string temp = to_string(doctors[user_id].age);

	while (window6.isOpen())
	{
		RectangleShape cursor(Vector2f(5, 0));
		cursor.setFillColor(Color::Black);

		Ntext.setString(doctors[user_id].full_name);

		Atext.setString(temp);

		Gtext.setString(doctors[user_id].info);

		RectangleShape mouseshadow(Vector2f(15, 15));
		mouseshadow.setPosition(mouse.getPosition().x - 140, mouse.getPosition().y - 100);
		mouseshadow.setFillColor(Color::Black);

		Event event6;
		while (window6.pollEvent(event6))
		{
			if (event6.type == Event::Closed)
			{
				doctors[user_id].age = stoi(temp);
				window6.close();
			}
			if (Mouse::isButtonPressed(Mouse::Left) && mouseshadow.getGlobalBounds().intersects(Narea.getGlobalBounds()))
			{
				counter4 = 50;
			}

			if (counter4 == 50 && event6.type == Event::TextEntered && event6.key.code != Keyboard::BackSpace)
			{
				doctors[user_id].full_name += static_cast<char>(event6.text.unicode);
			}
			if (Keyboard::isKeyPressed(Keyboard::Backspace) && counter4 == 50 && doctors[user_id].full_name.size() > 0)
			{
				doctors[user_id].full_name.resize(doctors[user_id].full_name.size() - 1);
			}
			if (Mouse::isButtonPressed(Mouse::Left) && mouseshadow.getGlobalBounds().intersects(Aarea.getGlobalBounds()))
			{
				counter4 = 51;
			}
			if (event6.type == Event::TextEntered && event6.key.code != Keyboard::BackSpace && counter4 == 51)
			{
				if (isdigit(event6.text.unicode))
				{
					temp += static_cast<char>(event6.text.unicode);
					to_string(doctors[user_id].age) = stoi(temp);
				}
			}
			if (Keyboard::isKeyPressed(Keyboard::Backspace) && counter4 == 51 && temp.size() > 0)
			{
				temp.resize(temp.size() - 1);

			}
			if (Mouse::isButtonPressed(Mouse::Left) && mouseshadow.getGlobalBounds().intersects(Garea.getGlobalBounds()))
			{
				counter4 = 52;
			}
			if (counter4 == 52 && event6.type == Event::TextEntered && event6.key.code != Keyboard::BackSpace)
			{
				doctors[user_id].info += static_cast<char>(event6.text.unicode);
			}
			if (event6.type == Event::TextEntered && counter4 == 52 && Keyboard::isKeyPressed(Keyboard::Enter))
			{
				doctors[user_id].info += '\n';

			}
			if (Keyboard::isKeyPressed(Keyboard::Backspace) && counter4 == 52 && doctors[user_id].info.size() > 0)
			{
				doctors[user_id].info.resize(doctors[0].info.size() - 1);
			}
			if (event6.type == Event::MouseButtonReleased && mouseshadow.getGlobalBounds().intersects(Confirm.getGlobalBounds()))
			{
				doctors[user_id].age = stoi(temp);
				window6.close();
				break;
			}
			if (Keyboard::isKeyPressed(Keyboard::Escape))
			{
				doctors[user_id].age = stoi(temp);
				window6.close();
			}

		}
		if (cursorClock.getElapsedTime().asMilliseconds() >= 500)
		{
			cursorVisible = !cursorVisible;
			cursorClock.restart();
		}
		if (event6.type == Event::MouseButtonReleased && Mouse::Left && mouseshadow.getGlobalBounds().intersects(Narea.getGlobalBounds()))
		{
			counter4 = 50;
			cursorVisible = true;
		}
		if (cursorVisible == true && counter4 == 50)
		{
			cursor.setSize(Vector2f(2, Narea.getLocalBounds().height * 0.5));
			cursor.setPosition(Ntext.getPosition().x + Ntext.getLocalBounds().width + 5, Ntext.getPosition().y + 4);

		}
		if (event6.type == Event::MouseButtonReleased && Mouse::Left && mouseshadow.getGlobalBounds().intersects(Aarea.getGlobalBounds()))
		{
			counter4 = 51;
			cursorVisible = true;
		}
		if (cursorVisible == true && counter4 == 51)
		{
			cursor.setSize(Vector2f(2, Aarea.getLocalBounds().height * 0.5));
			cursor.setPosition(Atext.getPosition().x + Atext.getLocalBounds().width + 5, Atext.getPosition().y + 4);

		}
		if (event6.type == Event::MouseButtonReleased && Mouse::Left && mouseshadow.getGlobalBounds().intersects(Garea.getGlobalBounds()))
		{
			counter4 = 52;
			cursorVisible = true;
		}
		if (cursorVisible == true && counter4 == 52)
		{
			cursor.setSize(Vector2f(2, Garea.getLocalBounds().height * 0.2));
			cursor.setPosition(Gtext.getPosition().x + Gtext.getLocalBounds().width + 5, Gtext.getPosition().y + 4);

		}


		window6.clear();
		window6.draw(Back);
		window6.draw(Garea);
		window6.draw(Aarea);
		window6.draw(Narea);
		window6.draw(Atext);
		window6.draw(Ntext);
		window6.draw(Gtext);
		window6.draw(Confirm);
		window6.draw(mouseshadow);
		window6.draw(cursor);
		window6.display();
	}
}
//general info dont work

void info_add_disease()
{
	Texture AREA1, AREA2, AREA3, AREA4, ButtonButton2, background;
	Sprite Area1, Area2, Area3, Area4, Add_button, Confirm_button, Background;
	Text Input1, Input2[10], Input3, Input4, Input_General[10];


	background.loadFromFile("ALL_IN_ONE/add disease/back.png");
	Background.setTexture(background);

	Button.loadFromFile("ALL_IN_ONE/add disease/Asset 21.png");
	Add_button.setTexture(Button);
	Add_button.setPosition(790, 269);

	Button13.loadFromFile("ALL_IN_ONE/add disease/Asset 18.png");
	Confirm_button.setTexture(Button13);
	Confirm_button.setPosition(358, 787);

	AREA1.loadFromFile("ALL_IN_ONE/add disease/Asset 16.png");
	Area1.setTexture(AREA1);
	Area1.setPosition(46, 96.5);

	AREA2.loadFromFile("ALL_IN_ONE/add disease/Asset 16.png");
	Area2.setTexture(AREA2);
	Area2.setPosition(46, 254);

	AREA3.loadFromFile("ALL_IN_ONE/add disease/Asset 17.png");
	Area3.setTexture(AREA3);
	Area3.setPosition(46, 394);

	AREA4.loadFromFile("ALL_IN_ONE/add disease/Asset 17.png");
	Area4.setTexture(AREA4);
	Area4.setPosition(46, 608);

	Input1.setFont(font1);
	Input1.setCharacterSize(40);
	Input1.setString("");
	Input1.setFillColor(Color::Black);
	Input1.setPosition(50, 104.5);
	for (int j = 0; j < 10; j++)
	{
		Input2[j].setFont(font1);
		Input2[j].setCharacterSize(40);
		Input2[j].setString("");
		Input2[j].setFillColor(Color::Black);
		Input2[j].setPosition(50, 260);
	}
	Input3.setFont(font1);
	Input3.setCharacterSize(40);
	Input3.setString("");
	Input3.setFillColor(Color::Black);
	Input3.setPosition(50, 404);

	Input4.setFont(font1);
	Input4.setCharacterSize(35);
	Input4.setString("");
	Input4.setFillColor(Color::Black);
	Input4.setPosition(50, 612);
	for (int counter = 0; counter < 10; counter++)
	{
		Input_General[counter].setFont(font1);
		Input_General[counter].setCharacterSize(30);
		Input_General[counter].setPosition(1100, 408 + (counter * 40));
		Input_General[counter].setFillColor(Color::Black);
		Input_General[counter].setString("");
	}


	string text1 = "", text2 = "", text3 = "", text4 = "";
	int index = 0;
	RenderWindow window5(VideoMode(1635, 920), "Add disease", Style::Default);
	int counter = 0;
	while (window5.isOpen())
	{
		RectangleShape cursor(Vector2f(5, 0));
		cursor.setFillColor(Color::Black);
		RectangleShape mouseshadow(Vector2f(15, 15));
		mouseshadow.setPosition(mouse.getPosition().x - 140, mouse.getPosition().y - 100);
		mouseshadow.setFillColor(Color::Black);
		string disease_symptoms[10];
		Input1.setString(text1);
		for (int x = 0; x < 10; x++)
		{
			Input2[x].setString(text2);
		}
		Input3.setString(text3);
		Input4.setString(text4);


		Event event5;
		while (window5.pollEvent(event5))
		{

			if (event5.type == Event::Closed)
			{
				window5.close();
			}
			if (mouseshadow.getGlobalBounds().intersects(Area1.getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left))
			{
				counter = 101;
			}
			if (counter == 101 && event5.type == Event::TextEntered && event5.text.unicode != Keyboard::Backspace)
			{
				text1 += static_cast<char>(event5.text.unicode);
			}
			if (counter == 101 && Keyboard::isKeyPressed(Keyboard::BackSpace) && text1.size() > 0)
			{
				text1.resize(text1.size() - 1);
			}

			if (mouseshadow.getGlobalBounds().intersects(Area2.getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left))
			{
				counter = 102;
			}
			if (counter == 102 && event5.type == Event::TextEntered && event5.text.unicode != Keyboard::Backspace)
			{
				text2 += static_cast<char>(event5.text.unicode);
			}
			if (counter == 102 && Keyboard::isKeyPressed(Keyboard::BackSpace) && text2.size() > 0)
			{
				text2.resize(text2.size() - 1);
			}

			if (mouseshadow.getGlobalBounds().intersects(Area3.getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left))
			{
				counter = 103;
			}
			if (counter == 103 && event5.type == Event::TextEntered && event5.text.unicode != Keyboard::Backspace)
			{
				text3 += static_cast<char>(event5.text.unicode);
				if (counter == 103 && Keyboard::isKeyPressed(Keyboard::Enter))
				{
					text3 += '\n';
				}
			}
			if (counter == 103 && Keyboard::isKeyPressed(Keyboard::BackSpace) && text3.size() > 0)
			{
				text3.resize(text3.size() - 1);
			}

			if (mouseshadow.getGlobalBounds().intersects(Area4.getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left))
			{
				counter = 104;
			}
			if (counter == 104 && event5.type == Event::TextEntered && event5.text.unicode != Keyboard::Backspace)
			{
				text4 += static_cast<char>(event5.text.unicode);
				if (counter == 104 && Keyboard::isKeyPressed(Keyboard::Enter))
				{
					text4 += '\n';
				}
			}
			if (counter == 104 && Keyboard::isKeyPressed(Keyboard::BackSpace) && text4.size() > 0)
			{
				text4.resize(text4.size() - 1);
			}

			if (Mouse::isButtonPressed(Mouse::Left) && mouseshadow.getGlobalBounds().intersects(Add_button.getGlobalBounds()))
			{
				if (Input2[index].getString() != "\0" && index < 10) {
					Input_General[index].setString(Input2[index].getString());
					text2 = "";
					Input2[index].setString("");
					index++;
				}
			}
			if (mouseshadow.getGlobalBounds().intersects(Confirm_button.getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left))
			{
				diseases[numdiseases].disease_name = text1;
				diseases[numdiseases].general_info = text3;
				diseases[numdiseases].tips[0] = text4;
				diseases[numdiseases].num_of_symptoms = index;
				for (int i = 0; i < index; i++) {
					diseases[numdiseases].symptoms[i] = Input_General[i].getString();
				}
				doctors[user_id].diseases_added[doctors[user_id].num_of_added_diseases] = text1;
				doctors[user_id].num_of_added_diseases++;
				numdiseases++;
				input_syptoms();
				window5.close();
				event5.type == Event::Closed();
				break;
			}
			for (int counter = 0; counter < 10; counter++)
			{
				if (mouseshadow.getGlobalBounds().intersects(Input_General[counter].getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left))
				{
					Input_General[counter].setString("");
					counter = index;
				}

			}

		}
		if (cursorClock.getElapsedTime().asMilliseconds() >= 500)
		{
			cursorVisible = !cursorVisible;
			cursorClock.restart();
		}
		if (Doctorpage == true)
		{
			if (event5.type == Event::MouseButtonReleased && mouseshadow.getGlobalBounds().intersects(Area1.getGlobalBounds()))
			{
				counter = 101;
				cursorVisible = true;
			}
			if (cursorVisible == true && counter == 101 && Doctorpage == true)
			{
				cursor.setSize(Vector2f(2, Area1.getLocalBounds().height * 0.5));
				cursor.setPosition(Input1.getPosition().x + Input1.getLocalBounds().width + 10, Input1.getPosition().y + 10);
			}
			if (event5.type == Event::MouseButtonReleased && mouseshadow.getGlobalBounds().intersects(Area2.getGlobalBounds()))
			{
				counter = 102;
				cursorVisible = true;
			}
			if (cursorVisible == true && counter == 102 && Doctorpage == true)
			{
				for (int counter2 = 0; counter2 < 10; counter2++)
				{
					cursor.setSize(Vector2f(2, Area2.getLocalBounds().height * 0.5));
					cursor.setPosition(Input2[counter2].getPosition().x + Input2[counter2].getLocalBounds().width + 10, Input2[counter2].getPosition().y + 8);
				}

			}
			if (event5.type == Event::MouseButtonReleased && mouseshadow.getGlobalBounds().intersects(Area3.getGlobalBounds()))
			{
				counter = 103;
				cursorVisible = true;
			}
			if (cursorVisible == true && counter == 103 && Doctorpage == true)
			{
				cursor.setSize(Vector2f(2, Area3.getLocalBounds().height * 0.2));
				cursor.setPosition(Input3.getPosition().x + Input3.getLocalBounds().width + 10, Input3.getPosition().y + 10);
			}
			if (event5.type == Event::MouseButtonReleased && mouseshadow.getGlobalBounds().intersects(Area4.getGlobalBounds()))
			{
				counter = 104;
				cursorVisible = true;
			}
			if (cursorVisible == true && counter == 104 && Doctorpage == true)
			{
				cursor.setSize(Vector2f(2, Area4.getLocalBounds().height * 0.2));
				cursor.setPosition(Input4.getPosition().x + Input4.getLocalBounds().width + 10, Input4.getPosition().y + 2);
			}


		}
		window5.clear();
		window5.draw(Background);
		window5.draw(Area1);
		window5.draw(Area2);
		window5.draw(Area3);
		window5.draw(Area4);
		window5.draw(Add_button);
		window5.draw(Confirm_button);
		window5.draw(Input1);
		window5.draw(Input3);
		window5.draw(Input4);
		window5.draw(cursor);
		for (int counter = 0; counter < 10; counter++)
		{
			window5.draw(Input2[counter]);
			window5.draw(Input_General[counter]);
		}
		//window5.draw(mouseshadow);
		window5.display();
	}

}
void info_edit_disease_doctor()
{
	Texture AREA1, AREA2, AREA3, AREA4, ButtonButton2, background;
	Sprite Area1, Area2, Area3, Area4, Add_button, Confirm_button, Background;
	Text Input1, Input3, Input4, Input_General[10], InputNew;

	background.loadFromFile("ALL_IN_ONE/add disease/back.png");
	Background.setTexture(background);

	Button.loadFromFile("ALL_IN_ONE/add disease/Asset 21.png");
	Add_button.setTexture(Button);
	Add_button.setPosition(790, 269);

	Button13.loadFromFile("ALL_IN_ONE/add disease/Asset 18.png");
	Confirm_button.setTexture(Button13);
	Confirm_button.setPosition(358, 787);

	AREA1.loadFromFile("ALL_IN_ONE/add disease/Asset 16.png");
	Area1.setTexture(AREA1);
	Area1.setPosition(46, 96.5);

	AREA2.loadFromFile("ALL_IN_ONE/add disease/Asset 16.png");
	Area2.setTexture(AREA2);
	Area2.setPosition(46, 254);

	AREA3.loadFromFile("ALL_IN_ONE/add disease/Asset 17.png");
	Area3.setTexture(AREA3);
	Area3.setPosition(46, 394);

	AREA4.loadFromFile("ALL_IN_ONE/add disease/Asset 17.png");
	Area4.setTexture(AREA4);
	Area4.setPosition(46, 608);

	Input1.setFont(font1);
	Input1.setCharacterSize(40);
	Input1.setString("");
	Input1.setFillColor(Color::Black);
	Input1.setPosition(50, 104.5);


	Input3.setFont(font1);
	Input3.setCharacterSize(20);
	Input3.setString("");
	Input3.setFillColor(Color::Black);
	Input3.setPosition(50, 404);

	InputNew.setFont(font1);
	InputNew.setCharacterSize(20);
	InputNew.setString("");
	InputNew.setFillColor(Color::Black);
	InputNew.setPosition(50, 250);


	Input4.setFont(font1);
	Input4.setCharacterSize(20);
	Input4.setString("");
	Input4.setFillColor(Color::Black);
	Input4.setPosition(50, 612);
	for (int counter = 0; counter < 10; counter++)
	{
		Input_General[counter].setFont(font1);
		Input_General[counter].setCharacterSize(30);
		Input_General[counter].setPosition(1100, 408 + (counter * 40));
		Input_General[counter].setFillColor(Color::Black);
		Input_General[counter].setString("");
	}

	RenderWindow window3(VideoMode(1635, 920), "Edit disease");
	Texture Editbutton2;
	swindow2.loadFromFile("ALL_IN_ONE/edit added disease/back.png");
	Texteditarea30.loadFromFile("ALL_IN_ONE/edit added disease/Asset 25.png");

	Text textitem3[10];
	for (int counter = 0; counter < 10; counter++)
	{
		textitem3[counter].setFont(font1);
		textitem3[counter].setCharacterSize(30);
		textitem3[counter].setString(doctors[0].diseases_added[counter]);
		textitem3[counter].setFillColor(Color::Black);
		textitem3[counter].setPosition(995, (counter * 84) + 40);
	}
	Sprite sbackground2;
	sbackground2.setTexture(swindow2);

	Sprite rect_search3[10];
	Text rect_result3;
	Sprite button2, RESULTAREA;
	Texture resultarea;
	resultarea.loadFromFile("ALL_IN_ONE/edit added disease/Asset 16.png");
	RESULTAREA.setTexture(resultarea);
	RESULTAREA.setPosition(20, 680);

	Editbutton2.loadFromFile("ALL_IN_ONE/edit added disease/Asset 26.png");
	button2.setTexture(Editbutton2);
	button2.setPosition(290, 787);


	int counter2 = 0, counter = 0;
	for (int counter = 0; counter < 10; counter++)
	{
		rect_search3[counter].setTexture(Texteditarea30);
		rect_search3[counter].setPosition(995, (counter * 84) + 40);
	}

	rect_result3.setFont(font1);
	rect_result3.setPosition(250, 680);
	rect_result3.setString("");
	rect_result3.setCharacterSize(30);
	rect_result3.setFillColor(Color::Black);

	int index;
	string text1 = "", text2 = "", text3 = "", text4 = "";

	while (window3.isOpen())
	{

		RectangleShape mouseshadow(Vector2f(15, 15));
		RectangleShape cursor(Vector2f(5, 0));
		cursor.setFillColor(Color::Black);

		InputNew.setString(text2);

		mouseshadow.setPosition(mouse.getPosition().x - 140, mouse.getPosition().y - 100);
		mouseshadow.setFillColor(Color::Black);

		Event event3;
		while (window3.pollEvent(event3))
		{
			if (event3.type == Event::Closed)
			{
				window3.close();
			}
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				for (int counter = 0; counter < 10; counter++)
				{

					FloatRect var = textitem3[counter].getGlobalBounds();
					if (var.contains(event3.mouseButton.x, event3.mouseButton.y))
					{
						rect_result3.setString(textitem3[counter].getString());
					}
				}
			}
			if (Mouse::isButtonPressed(Mouse::Left) && mouseshadow.getGlobalBounds().intersects(button2.getGlobalBounds()))
			{
				string send;
				send = rect_result3.getString();
				search_for_certain_disease(send);

				index = diseases[current_disease].num_of_symptoms;

				Input1.setString(diseases[current_disease].disease_name);
				Input4.setString(diseases[current_disease].tips[0]);
				int te;
				for (int i = 0; i < diseases[current_disease].general_info.size(); i++) {
					if (diseases[current_disease].general_info[i] == ' ') {
						te = i;
					}
					Input3.setString(diseases[current_disease].general_info.substr(0, i));
					if (Input3.getLocalBounds().width > 840 && te != -1) {
						diseases[current_disease].general_info[te] = '\n';
						i = te;
						te = -1;
					}
				}
				int lastSpace = -1;
				for (int i = 0; i < diseases[current_disease].tips[0].size(); i++) {
					if (diseases[current_disease].tips[0][i] == ' ') {
						lastSpace = i;
					}
					Input4.setString(diseases[current_disease].tips[0].substr(0, i));
					if (Input4.getLocalBounds().width > 840 && lastSpace != -1) {
						diseases[current_disease].tips[0][lastSpace] = '\n';
						i = lastSpace;
						lastSpace = -1;
					}
				}

				Input4.setString(diseases[current_disease].tips[0]);

				Swindow4 = true;
				Swindow3 = false;

				for (int j = 0; j < diseases[current_disease].num_of_symptoms; j++)
				{
					Input_General[j].setString(diseases[current_disease].symptoms[j]);
				}
			}
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				for (int counter = 0; counter < 10; counter++)
				{

					FloatRect var = Input_General[counter].getGlobalBounds();
					if (var.contains(event3.mouseButton.x, event3.mouseButton.y))
					{
						Input_General[counter].setString("");
					}
				}
			}
			if (mouseshadow.getGlobalBounds().intersects(Confirm_button.getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left) && Swindow4 == true)
			{
				Swindow4 = false;
				Swindow3 = false;
				window3.close();
			}
			if (Swindow4 == true && mouseshadow.getGlobalBounds().intersects(Area1.getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left))
			{
				counter = 101;
			}
			if (Swindow4 == true && counter == 101 && event3.type == Event::TextEntered && event3.text.unicode != Keyboard::Backspace)
			{
				diseases[current_disease].disease_name += static_cast<char>(event3.text.unicode);
				Input1.setString(diseases[current_disease].disease_name);
			}


			if (Swindow4 == true && mouseshadow.getGlobalBounds().intersects(Area2.getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left))
			{
				counter = 102;
			}
			if (Swindow4 == true && counter == 102 && event3.type == Event::TextEntered && event3.text.unicode != Keyboard::Backspace)
			{
				text2 += static_cast<char>(event3.text.unicode);
			}
			if (Swindow4 == true && counter == 102 && Keyboard::isKeyPressed(Keyboard::BackSpace) && text2.size() > 0)
			{
				text2.resize(text2.size() - 1);
			}
			if (Swindow4 == true && mouseshadow.getGlobalBounds().intersects(Add_button.getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left))
			{
				if (text2 != "\0" && index < 10)
				{
					Input_General[index].setString(text2);
					text2 = "";
					index++;
				}

			}
			if (Swindow4 == true && mouseshadow.getGlobalBounds().intersects(Area3.getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left))
			{
				counter = 103;
			}
			if (Swindow4 == true && counter == 103 && event3.type == Event::TextEntered && event3.text.unicode != Keyboard::Backspace)
			{
				text3 += static_cast<char>(event3.text.unicode);
				if (Swindow4 == true && counter == 103 && Keyboard::isKeyPressed(Keyboard::Enter))
				{
					text3 += '\n';
				}
			}
			if (Swindow4 == true && counter == 103 && Keyboard::isKeyPressed(Keyboard::BackSpace) && text3.size() > 0)
			{
				text3.resize(text3.size() - 1);
			}

			if (Swindow4 == true && mouseshadow.getGlobalBounds().intersects(Area4.getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left))
			{
				counter = 104;
			}
			if (Swindow4 == true && counter == 104 && event3.type == Event::TextEntered && event3.text.unicode != Keyboard::Backspace)
			{
				text4 += static_cast<char>(event3.text.unicode);
				if (Swindow4 == true && counter == 104 && Keyboard::isKeyPressed(Keyboard::Enter))
				{
					text4 += '\n';
				}
			}
			if (Swindow4 == true && counter == 104 && Keyboard::isKeyPressed(Keyboard::BackSpace) && text4.size() > 0)
			{
				text4.resize(text4.size() - 1);
			}
			if (Swindow4 == true && counter == 101 && Keyboard::isKeyPressed(Keyboard::BackSpace) && diseases[current_disease].disease_name.size() > 0)
			{
				diseases[current_disease].disease_name.resize(diseases[current_disease].disease_name.size() - 1);
				Input1.setString(diseases[current_disease].disease_name);
			}

		}
		if (cursorClock.getElapsedTime().asMilliseconds() >= 500)
		{
			cursorVisible = !cursorVisible;
			cursorClock.restart();
		}
		if (Swindow4 == true && Doctorpage == true)
		{
			if (event3.type == Event::MouseButtonReleased && mouseshadow.getGlobalBounds().intersects(Area1.getGlobalBounds()) && Swindow4 == true)
			{
				counter = 101;
				cursorVisible = true;
			}
			if (Swindow4 == true && cursorVisible == true && counter == 101 && Doctorpage == true)
			{
				cursor.setSize(Vector2f(2, Area1.getLocalBounds().height * 0.5));
				cursor.setPosition(Input1.getPosition().x + Input1.getLocalBounds().width + 10, Input1.getPosition().y + 10);
			}
			if (Swindow4 == true && event3.type == Event::MouseButtonReleased && mouseshadow.getGlobalBounds().intersects(Area2.getGlobalBounds()))
			{
				counter = 102;
				cursorVisible = true;
			}
			if (Swindow4 == true && event3.type == Event::MouseButtonReleased && mouseshadow.getGlobalBounds().intersects(Area3.getGlobalBounds()))
			{
				counter = 103;
				cursorVisible = true;
			}
			if (Swindow4 == true && cursorVisible == true && counter == 103 && Doctorpage == true)
			{
				cursor.setSize(Vector2f(2, Area3.getLocalBounds().height * 0.2));
				cursor.setPosition(Input3.getPosition().x + Input3.getLocalBounds().width + 10, Input3.getPosition().y + 10);
			}
			if (Swindow4 == true && event3.type == Event::MouseButtonReleased && mouseshadow.getGlobalBounds().intersects(Area4.getGlobalBounds()))
			{
				counter = 104;
				cursorVisible = true;
			}
			if (Swindow4 == true && cursorVisible == true && counter == 104 && Doctorpage == true)
			{
				cursor.setSize(Vector2f(2, Area4.getLocalBounds().height * 0.2));
				cursor.setPosition(Input4.getPosition().x + Input4.getLocalBounds().width + 10, Input4.getPosition().y + 2);
			}
		}
		if (Swindow3 == true && Swindow4 == false)
		{
			window3.clear(Color::White);
			window3.draw(sbackground2);
			window3.draw(button2);
			for (int counter = 0; counter < 10; counter++)
			{

				window3.draw(rect_search3[counter]);
				window3.draw(textitem3[counter]);
			}
			window3.draw(RESULTAREA);
			window3.draw(rect_result3);
			window3.display();
		}
		if (Swindow4 == true && Swindow3 == false)
		{
			window3.clear();
			window3.draw(Background);
			window3.draw(Area1);
			window3.draw(Area2);
			window3.draw(Area3);
			window3.draw(Area4);
			window3.draw(Add_button);
			window3.draw(Confirm_button);
			window3.draw(Input1);
			window3.draw(Input3);
			window3.draw(Input4);
			window3.draw(InputNew);
			window3.draw(cursor);
			for (int counter = 0; counter < 10; counter++)
			{
				window3.draw(Input_General[counter]);
			}
			window3.draw(cursor);
			//window3.draw(mouseshadow);
			window3.display();
		}
	}
	Swindow4 = false;
	Swindow3 = false;
	Swindow1 = false;
	Swindow2 = false;

}

void display_all_diseases_doctor()
{
	Text DoctorSearch, Swindowtext1, Swindowtext2[10], Swindowtext3, Swindowtext4[4], Swindow2text[4][4];
	Sprite ConfirmButton, DOCTORSEARCHTEDIT;
	Texture swindow2back, swindow2textarea, swindow2textarea2;
	swindow2back.loadFromFile("ALL_IN_ONE/view patient with disease/Back.png");
	swindow2textarea.loadFromFile("ALL_IN_ONE/view patient with disease/text area.png");
	swindow2textarea2.loadFromFile("ALL_IN_ONE/view patient with disease/text area.png");

	Sprite Swindow2back, Swindow2textarea, Swindow2textarea2[4];

	Swindow2back.setTexture(swindow2back);
	Swindow2textarea.setTexture(swindow2textarea);
	Swindow2textarea.setPosition(20, 20);


	for (int counter = 0; counter < 4; counter++)
	{
		Swindow2textarea2[counter].setTexture(swindow2textarea2);
		Swindow2textarea2[counter].setPosition(20, (450 * counter) + 28);
	}


	for (int counter = 0; counter < 4; counter++)
	{
		for (int counter2 = 0; counter2 < 4; counter2++)
		{

			Swindow2text[counter][counter2].setFont(font1);
			Swindow2text[counter][counter2].setCharacterSize(40);
			Swindow2text[counter][counter2].setFillColor(Color::Black);
			Swindow2text[counter][0].setPosition(270, (450 * (counter)) + 76);
			Swindow2text[counter][1].setPosition(270, (450 * (counter)) + 76 + 65);
			Swindow2text[counter][2].setPosition(270, (450 * (counter)) + 76 + 65 + 65);
			Swindow2text[counter][3].setPosition(270, (450 * (counter)) + 76 + 65 + 65 + 65);

			Swindow2text[counter][0].setString("");
			Swindow2text[counter][1].setString("");
			Swindow2text[counter][2].setString("");
			Swindow2text[counter][3].setString("");

		}
	}
	Texture swindowback, swindowtextarea, viewbutton;
	swindowback.loadFromFile("ALL_IN_ONE/disease info/back.png");
	swindowtextarea.loadFromFile("ALL_IN_ONE/disease info/Asset 9.png");
	viewbutton.loadFromFile("ALL_IN_ONE/disease info/Asset 8.png");

	Sprite Swindowback, Swindowtextarea, Viewbutton;

	Swindowback.setTexture(swindowback);
	Swindowtextarea.setTexture(swindowtextarea);
	Swindowtextarea.setPosition(45, 45);

	Viewbutton.setTexture(viewbutton);
	Viewbutton.setPosition(1175, 750);

	Swindowtext1.setFont(font1);
	Swindowtext1.setFillColor(Color::Black);
	Swindowtext1.setCharacterSize(24);
	Swindowtext1.setPosition(60, 50);
	Swindowtext1.setString("");
	for (int m = 0; m < 8; m++) {
		Swindowtext2[m].setFont(font1);
		Swindowtext2[m].setFillColor(Color::Black);
		Swindowtext2[m].setCharacterSize(22);
		Swindowtext2[m].setPosition(50, 98 + (40 * m));
		Swindowtext2[m].setString("");
	}

	Swindowtext3.setFont(font1);
	Swindowtext3.setFillColor(Color::Black);
	Swindowtext3.setCharacterSize(22);
	Swindowtext3.setPosition(50, 420);
	Swindowtext3.setString("");

	for (int m = 0; m < 4; m++) {
		Swindowtext4[m].setFont(font1);
		Swindowtext4[m].setFillColor(Color::Black);
		Swindowtext4[m].setCharacterSize(22);
		Swindowtext4[m].setPosition(50, 620 + (m * 50));
		Swindowtext4[m].setString("");
	}

	string text_info = "";

	DoctorSearchback.loadFromFile("ALL_IN_ONE/search for disease/back.png");
	Confirmbutton.loadFromFile("ALL_IN_ONE/search for disease/Asset 11.png");
	TeditDcotorSearch.loadFromFile("ALL_IN_ONE/search for disease/Asset 12.png");

	ConfirmButton.setTexture(Confirmbutton);
	ConfirmButton.setPosition(240, 705);

	DOCTORSEARCHTEDIT.setTexture(TeditDcotorSearch);
	DOCTORSEARCHTEDIT.setPosition(30, 560);

	DoctorSearch.setFont(font1);
	DoctorSearch.setCharacterSize(55);
	DoctorSearch.setFillColor(Color::Black);
	DoctorSearch.setString("");
	DoctorSearch.setPosition(35, 565);


	///////////////////////////////////////////////////////////////////////////////////
	RenderWindow window2(VideoMode(1635, 920), "Display all disease");

	swindow2.loadFromFile("ALL_IN_ONE/display all disease/back.png");
	Texteditarea2.loadFromFile("ALL_IN_ONE/display all disease/Asset 3.png");

	Text textitem2[100];
	for (int counter = 0; counter < 100; counter++)
	{
		textitem2[counter].setFont(font1);
		textitem2[counter].setCharacterSize(30);
		textitem2[counter].setString(diseases[counter].disease_name);
		textitem2[counter].setFillColor(Color::Black);
		textitem2[counter].setPosition(1010, (counter * 84) + 49);
	}
	Sprite sbackground2;
	sbackground2.setTexture(swindow2);

	Sprite rect_search2[100];
	Text rect_result2;
	Sprite button;

	confirmbutton.loadFromFile("ALL_IN_ONE/search for disease/Asset 11.png");
	button.setTexture(confirmbutton);
	button.setPosition(290, 787);


	int counter2 = 0;
	for (int counter = 0; counter < 100; counter++)
	{
		rect_search2[counter].setTexture(Texteditarea2);
		rect_search2[counter].setPosition(995, (counter * 84) + 40);
	}

	rect_result2.setFont(font1);
	rect_result2.setPosition(285 + 20, 690);
	rect_result2.setString("");
	rect_result2.setCharacterSize(38);
	rect_result2.setFillColor(Color::Black);

	while (window2.isOpen())
	{
		RectangleShape mouseshadow(Vector2f(15, 15));
		mouseshadow.setPosition(mouse.getPosition().x - 140, mouse.getPosition().y - 100);
		mouseshadow.setFillColor(Color::Black);


		Event event2;
		while (window2.pollEvent(event2))
		{
			if (event2.type == Event::Closed)
			{

				for (int i = 0; i < 4; i++) {
					patient_with_disease[i] = -1;
				}
				Swindow1 == false;
				Swindow2 == false;
				current_disease = -1;
				window2.close();
			}
			if (event2.type == Event::MouseWheelScrolled)
			{

				for (int counter = 0; counter < 100; counter++) {
					if (event2.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
					{
						rect_search2[counter].move(0.f, event2.mouseWheelScroll.delta * 30.f);
						textitem2[counter].move(0.f, event2.mouseWheelScroll.delta * 30.f);
					}
				}
			}

			if (Mouse::isButtonPressed(Mouse::Left))
			{
				for (int counter = 0; counter < 100; counter++)
				{

					FloatRect var = textitem2[counter].getGlobalBounds();
					if (var.contains(event2.mouseButton.x, event2.mouseButton.y))
					{
						rect_result2.setString(textitem2[counter].getString());
					}
				}
			}

			if (Mouse::isButtonPressed(Mouse::Left) && mouseshadow.getGlobalBounds().intersects(button.getGlobalBounds()))
			{
				Swindow1 = true;
				Swindow2 = false;
				string send;
				send = rect_result2.getString();
				search_for_certain_disease(send);
				if (current_disease != -1) {
					search_for_patients_with_certain_disease(current_disease);

					Swindowtext1.setString(diseases[current_disease].disease_name);
					for (int m = 0; m < 8; m++) {

						Swindowtext2[m].setString(diseases[current_disease].symptoms[m]);
					}
					int te = -1;
					for (int i = 0; i < diseases[current_disease].general_info.size(); i++) {
						if (diseases[current_disease].general_info[i] == ' ') {
							te = i;
						}
						Swindowtext3.setString(diseases[current_disease].general_info.substr(0, i));
						if (Swindowtext3.getLocalBounds().width > 840 && te != -1) {
							diseases[current_disease].general_info[te] = '\n';
							i = te;
							te = -1;
						}
					}
					for (int m = 0; m < 4; m++) {
						int lastSpace = -1;
						for (int i = 0; i < diseases[current_disease].tips[m].size(); i++) {
							if (diseases[current_disease].tips[m][i] == ' ') {
								lastSpace = i;
							}
							Swindowtext4[m].setString(diseases[current_disease].tips[m].substr(0, i));
							if (Swindowtext4[m].getLocalBounds().width > 840 && lastSpace != -1) {
								diseases[current_disease].tips[m][lastSpace] = '\n';
								i = lastSpace;
								lastSpace = -1;
							}
						}

						Swindowtext4[m].setString(diseases[current_disease].tips[m]);
					}
					search_for_patients_with_certain_disease(current_disease);
					for (int counter = 0; counter < 4; counter++)
					{
						if (patient_with_disease[counter] == -1) {
							break;
						}
						else {
							Swindow2text[counter][0].setString(patients[patient_with_disease[counter]].full_name);
							Swindow2text[counter][1].setString(to_string(patients[patient_with_disease[counter]].age));
							Swindow2text[counter][2].setString(patients[patient_with_disease[counter]].gender);
							Swindow2text[counter][3].setString(patients[patient_with_disease[counter]].info);
						}

					}
				}
				else {
					Swindowtext1.setString("There is no corresponding disease");
				}


			}
			if (Swindow1 == true && mouseshadow.getGlobalBounds().intersects(Viewbutton.getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left))
			{
				Swindow1 = false;
				Swindow2 = true;
			}
			if (event2.type == Event::MouseWheelScrolled && Swindow2 == true && Swindow1 == false)
			{
				for (int counter = 0; counter < 4; counter++)
				{

					if (event2.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
					{
						Swindow2textarea2[counter].move(0.f, event2.mouseWheelScroll.delta * 30.f);
						Swindow2text[counter][0].move(0.f, event2.mouseWheelScroll.delta * 30.f);
						Swindow2text[counter][1].move(0.f, event2.mouseWheelScroll.delta * 30.f);
						Swindow2text[counter][2].move(0.f, event2.mouseWheelScroll.delta * 30.f);
						Swindow2text[counter][3].move(0.f, event2.mouseWheelScroll.delta * 30.f);
					}

				}
			}

		}


		if (Swindow2 == false && Swindow1 == false && Swindow3 == false && Swindow4 == false)
		{
			window2.clear(Color::White);
			window2.draw(sbackground2);
			window2.draw(button);
			for (int counter = 0; counter < 100; counter++)
			{

				window2.draw(rect_search2[counter]);
				window2.draw(textitem2[counter]);
			}
			window2.draw(rect_result2);
			//window2.draw(mouseshadow);
			window2.display();
		}

		if (Swindow2 == false && Swindow1 == true && Doctorpage == true)
		{
			window2.clear(Color::Black);
			window2.draw(Swindowback);
			window2.draw(Swindowtextarea);
			window2.draw(Viewbutton);
			window2.draw(Swindowtext1);
			for (int m = 0; m < 10; m++)
			{
				window2.draw(Swindowtext2[m]);
			}

			window2.draw(Swindowtext3);
			for (int c = 0; c < 4; c++)
			{
				window2.draw(Swindowtext4[c]);
			}
			//window2.draw(mouseshadow);
			window2.display();
		}
		if (Swindow1 == false && Swindow2 == true)
		{
			window2.clear(Color::Green);
			window2.draw(Swindow2back);
			for (int counter4 = 0; counter4 < 4; counter4++)
			{
				window2.draw(Swindow2textarea2[counter4]);
			}
			for (int counter = 0; counter < 4; counter++)
			{
				for (int counter2 = 0; counter2 < 4; counter2++)
				{
					window2.draw(Swindow2text[counter][counter2]);
				}

			}
			//window2.draw(mouseshadow);
			window2.display();
		}
	}

}

//==========================================================================

//System functions 
bool checklogin(user* users, string Username, string Password, bool& Check)
{
	for (int i = 0; i < numusers; i++) {
		if (users[i].username == Username && users[i].password == Password)
		{
			user_id = users[i].id;
			index_role = i;
			Check = true;
			return true;
		}
	}
	return false;
}
void SignUp(user* users, string username, string password, string role, int& numusers,int& numpatients,int& numdoctors) {
	users[numusers].username = username;
	users[numusers].password = password;
	users[numusers].role = role;
	if (role == "doctor") {
		
		numdoctors++;
		numusers++;

	}
	else if (role == "patient") {
		numpatients++;
		numusers++;

	}

	/*	ofstream out_file("accounts.txt", ios::app);
		out_file << users[numusers].username << endl;
		out_file << users[numusers].password << endl;
		out_file << users[numusers].role << endl;
		out_file.close()*/
}
void signup2(doctor* doctors, patient* patients, string name, string info, string gender, int age,string R) {
	if (R == "doctor")
	{
		doctors[numdoctors - 1].full_name = name;
		doctors[numdoctors - 1].age = age;
		doctors[numdoctors - 1].gender = gender;
		doctors[numdoctors - 1].info = info;
		users[numusers - 1].id = numdoctors-1;

		//write_to_doctors_file();
	}
	else if (R == "patient")
	{
		patients[numpatients - 1].full_name = name;
		patients[numpatients - 1].age = age;
		patients[numpatients - 1].gender = gender;
		patients[numpatients - 1].info = info;
		users[numusers - 1].id = numpatients-1;


		//write_to_patients_file();
	}
}
void input_syptoms() {
	for (int i = 0; i < numdiseases; i++)
	{
		diseases[i].diagnosis_percentage = 0;
	}
	int symCount = 0;
	for (int i = 0; i < numdiseases; i++)
	{
		for (int j = 0; j < diseases[i].num_of_symptoms; j++)
		{
			int k = 0;
			for (; k < symCount; k++)
			{
				if (diseases[i].symptoms[j] == sym[k])
					break;
			}
			if (k < symCount)
				continue;
			else
			{
				sym[symCount] = diseases[i].symptoms[j];
				symCount++;
			}

		}
	}
}
void search(string nobil[], int w)
{
	string flu;

	int arr2[20] = { 0 };



	for (int g = 0; g < numdiseases; g++)
	{
		for (int h = 0; h < diseases[g].num_of_symptoms; h++)
		{
			for (int k = 0; k < w; k++)
			{
				if (diseases[g].symptoms[h] == nobil[k])
				{
					diseases[g].diagnosis_percentage++;
					break; // break out of the loop once a match is found
				}
			}
		}
	}

	bool z;
	for (int g = 0; g < numdiseases; g++)
	{
		if (diseases[g].diagnosis_percentage / diseases[g].num_of_symptoms >= 0.6)
		{
			z = true;
			current_disease = g;
			break;
		}
		else
		{
			z = false;
		}
	}
	if (z == false) {
		current_disease = -1;
	}
	/*
	while (z == true)
	{
		int g = 0;
		if (g < numdiseases) {

			if (diseases[g].diagnosis_percentage / diseases[g].num_of_symptoms >= 0.6)
			{

				flu = diseases[g].disease_name;
				cout << "you have: " << diseases[g].disease_name << endl;
				cout << endl;

				cout << "Symptoms :" << endl;
				for (int j = 0; j < diseases[g].num_of_symptoms; j++)
				{
					if (diseases[g].symptoms[j] == "\0")
					{
						continue;
					}
					cout << "#" << diseases[g].symptoms[j] << endl;
				}
				cout << endl;

				cout << "General info : " << endl << diseases[g].general_info << endl;
				cout << endl;

				cout << "Some tips : " << endl;
				for (int k = 0; k < diseases[g].no_tips; k++)
				{
					if (diseases[g].tips[k] == "\0")
					{
						continue;
					}
					cout << "#" << diseases[g].tips[k] << endl;
				}
				cout << endl;
				cout << "\t" << "***************" << endl;
				break;

			}
			g++;
		}

	}

	int g = 0;
	while (z == false && g < numdiseases)
	{
		double max_value = 0;

		if (diseases[g].diagnosis_percentage > max_value)
		{
			max_value = diseases[g].diagnosis_percentage;
			flu = diseases[g].disease_name;

		}

		if (max_value != 0)
		{
			cout << "You have " << flu << " By persentage of: " << (max_value / diseases[g].num_of_symptoms) * 100 << "%" << endl;
			g++;
			continue;
		}

		for (int i = 0; i < numdiseases; i++)
		{
			if (diseases[i].diagnosis_percentage / diseases[g].num_of_symptoms == 0.6)
			{
				cout << "Your symptoms match none of the existing diseases";
			}
		}
		g++;
	}
	*/

	//write_to_patients_file();
}
void search_for_certain_disease(string disease_name)
{
	bool a = false;
	for (int i = 0; i < numdiseases; i++)
	{
		if (disease_name == diseases[i].disease_name)
		{
			a = true;
			current_disease = i;
			/*
			a = true;
			cout << "Disease name : " << diseases[i].disease_name << endl;
			cout << endl;
			cout << "Symptoms :" << endl;
			for (int j = 0; j < diseases[i].num_of_symptoms; j++)
			{
				if (diseases[i].symptoms[j] == "\0")
				{
					continue;
				}
				cout << "#" << diseases[i].symptoms[j] << endl;
			}
			cout << endl;
			cout << "General info : " << endl << diseases[i].general_info << endl;
			cout << endl;
			cout << "Some tips : " << endl;
			for (int k = 0; k < diseases[i].no_tips; k++)
			{
				if (diseases[i].tips[k] == "\0")
				{
					continue;
				}
				cout << "#" << diseases[i].tips[k] << endl;
			}
			break;
			*/
		}
		else
		{
			continue;
		}

	}
	if (a == false) {
		current_disease = -1;
	}
}
void search_for_patients_with_certain_disease(int search_term)
{
	int b = 0;
	for (int i = 0; i < numpatients; i++)
	{
		if (b == 3)
		{
			break;
		}
		for (int j = 0; j < patients[i].no_diagnosed_diseases; j++)
		{
			if (patients[i].diseases_history[j] == diseases[search_term].disease_name)
			{
				patient_with_disease[b] = i;
				cout << i << endl;
				b++;
			}
		}
	}

}
void editDiseaseInfo()
{
	cout << "***********************************************" << endl;
	int size = 0;
	int size2 = 0;
	// Display added diseases as choices
	int n;
	cout << "Choose a disease to edit:\n";
	for (int i = 0; i < doctors[user_id].num_of_added_diseases; i++)
	{
		if (doctors[user_id].diseases_added[i] != "\0")
		{
			cout << i + 1 << ". " << doctors[user_id].diseases_added[i] << endl;
		}
	}

	// Get user's choice of disease to edit
	int choice;
	cout << "Enter the number of the disease you want to edit: ";
	cin >> choice;

	// Search for the chosen disease in the diseases array
	if (doctors[user_id].diseases_added[choice - 1] == "\0")
	{
		cout << "Invalid choice. Please choose a valid disease number.\n";
		int ans = 0;
		cout << "1. Continue to edit\n";
		cout << "Enter your choice : ";
		while (ans != 1 && ans != 2)
		{
			cin >> ans;
			if (ans == 1)
				editDiseaseInfo();

			else
				cout << "Invalid choice. Enter another choice";
		}
	}

	for (int j = 0; j < numdiseases; j++)
	{
		if (doctors[user_id].diseases_added[choice - 1] == diseases[j].disease_name)
		{
			// Display the disease's current information
			n = j;
			cout << "Current information for " << doctors[user_id].diseases_added[choice - 1] << ":\n";
			cout << endl;
			cout << "Symptoms: ";
			for (int l = 0; l < diseases[n].num_of_symptoms; l++)
			{
				if (diseases[n].symptoms[l] != "\0")
				{
					cout << diseases[n].symptoms[l] << endl;
				}
			}
			cout << endl;
			cout << "General info: " << diseases[j].general_info << endl;
			cout << endl;
			cout << "tips: " << endl;
			for (int o = 0; o < diseases[n].no_tips; o++)
			{
				cout << diseases[n].tips[o] << endl;
			}
			cout << endl;
			break;
		}
	}


	// Ask the user what they want to edit
	int editChoice;
	cout << "\nWhat do you want to edit?\n";
	cout << "1. Symptoms\n";
	cout << "2. General info\n";
	cout << "3. tips\n";
	cout << "Enter the number of your choice: ";
	cin >> editChoice;

	// Get the new value from the user and update the disease struct
	string newValue;
	switch (editChoice)
	{

	case 1:
		cout << "Enter new symptoms (up to 10): " << endl;
		cin.ignore();
		for (int i = 0; i < diseases[n].num_of_symptoms; i++)
		{
			diseases[n].symptoms[i] = "\0";
		}


		while (true)
		{
			cout << "Enter the symptom number " << size + 1 << ": ";
			getline(cin, diseases[n].symptoms[size]);
			cout << "Enter another syptome?(press y to continue/any other key to cancel)" << endl;
			char answer;
			cin >> answer;
			cin.ignore();
			if (answer == 'y' || answer == 'Y')
			{
				size++;
				continue;
			}
			else
				break;
		}
		diseases[n].num_of_symptoms = size + 1;
		break;
	case 2:
		cout << "Enter new general information: ";
		cin.ignore();
		getline(cin, newValue, '/');
		diseases[n].general_info = newValue;
		break;
	case 3:
		for (int i = 0; i < 10; i++)
		{
			diseases[n].tips[i] = "\0";
		}
		cout << "Enter new tips: ";
		cin.ignore();


		while (true)
		{
			cout << "Enter tip number " << size2 + 1 << ": ";
			cin.ignore();
			getline(cin, diseases[n].tips[size2]);
			cout << "Enter another tip?(press y to continue/any other key to cancel)\n";
			char answer;
			cin >> answer;
			if (answer == 'y' || answer == 'Y')
			{
				size2++;
				continue;
			}
			else
				break;
		}
		diseases[n].no_tips = size2 + 1;
		break;
	default:
		cout << "Invalid choice. No changes made.\n";
		int ans2 = 0;
		cout << "1. Continue to edit" << endl;
		cout << "Enter your choice : ";
		while (ans2 != 1 && ans2 != 2)
		{
			cin >> ans2;
			if (ans2 == 1)
				editDiseaseInfo();
			else
				cout << "Invalid choice. Enter another choice";
		}
		break;
	}

	// Confirm the edit and display the updated information
	cout << "\n" << diseases[n].disease_name << " has been updated with the following information:\n";
	cout << "Symptoms: " << endl;
	for (int i = 0; i < diseases[n].num_of_symptoms; i++)
	{
		cout << diseases[n].symptoms[i] << endl;
	}
	cout << endl;
	cout << "General info: " << diseases[n].general_info << endl;
	cout << endl;
	cout << "tips: " << endl;
	for (int i = 0; i < diseases[n].no_tips; i++)
	{
		cout << diseases[n].tips[i] << endl;
	}
	write_to_diseases_file();

}
void clearDiagnosisHistory()
{
	for (int i = 0; i < 15; i++)
	{
		patients[user_id].diseases_history[i] = "";
	}
	patients[user_id].no_diagnosed_diseases = 0;
}
void add_disease()
{
	cout << "******************************************************" << endl;
	string new_disease_name;
	int size = 0;
	string symptoms[30];
	string general_info;
	int size2 = 0;
	string tips[15];

	cin.ignore();
	cout << "Enter disease name : ";
	getline(cin, new_disease_name);

	for (int i = 0; i < numdiseases - 1; i++)      //check if the disease exists or not
	{
		if (new_disease_name == diseases[i].disease_name)
		{
			cout << "This disease alredy exists\n";
			cout << "Do you want to enter another disease?(press y to continue/any other key to cancel) : ";
			char answer;
			cin >> answer;
			if (answer == 'y' || answer == 'Y')
			{
				add_disease();
			}

		}
	}

	cout << "Enter the symptoms of this disease: " << endl;
	while (true)
	{
		cout << "Enter the symptom number " << size + 1 << ": ";
		getline(cin, symptoms[size]);
		cout << "Enter another syptome?(press y to continue/any other key to cancel) : ";
		char answer;
		cin >> answer;
		cin.ignore();
		if (answer == 'y' || answer == 'Y')
		{
			size++;
			continue;
		}
		else
			break;
	}
	cout << "Enter some general information about this disease" << endl;
	getline(cin, general_info, '/');

	cout << "Enter some tips for the patients" << endl;
	while (true)
	{
		cout << "Enter the tip number " << size2 + 1 << ": ";
		cin.ignore();
		getline(cin, tips[size2]);
		cout << "Enter another tip?(press y to continue/any other key to cancel) : ";
		char answer;
		cin >> answer;
		if (answer == 'y' || answer == 'Y')
		{
			size2++;
			continue;
		}
		else
			break;
	}
	cout << "Disease added successfully." << endl;

	diseases[numdiseases - 1].diseaseID = numdiseases;

	diseases[numdiseases - 1].disease_name = new_disease_name;

	diseases[numdiseases - 1].num_of_symptoms = size + 1;
	for (int i = 0; i <= size; i++)
	{
		diseases[numdiseases - 1].symptoms[i] = symptoms[i];
	}

	diseases[numdiseases - 1].general_info = general_info;

	diseases[numdiseases - 1].no_tips = size2 + 1;
	for (int i = 0; i <= size2; i++)
	{
		diseases[numdiseases - 1].tips[i] = tips[i];
	}
	numdiseases++;
	write_to_diseases_file();

	doctors[user_id].diseases_added[doctors[user_id].num_of_added_diseases] = new_disease_name;
	doctors[user_id].num_of_added_diseases++;

	write_to_doctors_file();

}
//============================================================================
int main()
{
	numusers = 2;
	numpatients = 1;
	numdoctors = 1;
	//******************************************************
	users[0].username = "patient";
	users[0].password = "123";
	users[0].role = "patient";
	users[0].id = 0;
	patients[0].full_name = "first patient";
	patients[0].gender = "male";
	patients[0].age = 20;
	patients[0].info = "heart disease patient";
	patients[0].no_diagnosed_diseases = 1;
	patients[0].diseases_history[0] = "COVID-19";
	//******************************************************
	users[1].username = "doctor";
	users[1].password = "123";
	users[1].role = "doctor";
	users[1].id = 0;
	doctors[0].full_name = "first doctor";
	doctors[0].age = 44;
	doctors[0].num_of_added_diseases = 1;
	doctors[0].info = "doctor in mental health";
	doctors[0].id = 0;
	doctors[0].diseases_added[0] = "COVID-19";
	doctors[0].gender = "male";
	//*******************************************************

	data(numusers, numpatients, numdoctors);
	Loginpage login;
	SIGNUP signup;
	DOCTORPAGE doctorpage;
	PATIENTPAGE patientpage;
	Wrong_login wrong_login;
	Delete_history delete_history;
	View_info view_info;
	Edit_info edit_info;

	Sprite background;
	Sprite background2;
	Sprite background3;
	Sprite background4;
	Sprite sbackground2, sbackground3, sbackground4, sbackground5, sbackground6, sbackground7, sbackground8, sbackground9, sbackground10;
	Sprite SIX_BACK;

	info_login(login);
	info_signup1(signup);
	info_signup2(signup);
	info_doctorpage(doctorpage);
	info_patientpage(patientpage);
	info_Wrong_login(wrong_login);
	info_delete_history(delete_history);
	info_view_info(view_info, patients);
	info_edit_info(edit_info);

	windowbackground.loadFromFile("Images_Login/loginpageback.png");
	background.setTexture(windowbackground);
	window2background.loadFromFile("New_Signup/back.png");
	background2.setTexture(window2background);
	window3background.loadFromFile("Images_Doctorpage/NEW.png");
	background3.setTexture(window3background);
	window4background.loadFromFile("Images_Patientpage/backpatient.png");
	background4.setTexture(window4background);
	SIX.loadFromFile("PATIENT_VIEW_INFO/Asset 4.png");
	SIX_BACK.setTexture(SIX);
	texteditarea75.loadFromFile("PATIENT_VIEW_INFO/Asset 3.png");
	Sprite bigback;
	bigback.setTexture(texteditarea75);
	bigback.setPosition(63, 537);
	backgroundedit.loadFromFile("EDIT_INFO/NEW BACK.png");
	Sprite Bigback;
	Bigback.setTexture(backgroundedit);

	string input_text_username = "";

	string input_text_password = "";
	string real_input_text_password = "";

	string input_text_username_signup = "";
	string input_text_fullname_signup = "";

	string input_text_password_signup = "";
	string real_input_text_password_signup = "";

	string input_text_Age = "";
	string input_text_FN = "";
	string input_text_GI = "";
	string Text1 = "", Text2 = "", Text5 = "";

	int counter = 0;
	//=====================
	//for sign up data 
	string UN, PW, FN, GI;
	string MF;
	string R = "";
	int AG = 0;
	//=====================

	//window.clear();
	//window.draw(background);
	//draw_login(login);
	//window.display();

	while (window.isOpen())
	{
		RectangleShape mouseshadow(Vector2f(10, 30));
		RectangleShape cursor(Vector2f(5, 0));
		cursor.setFillColor(Color::Black);
		mouseshadow.setFillColor(Color::Black);
		mouseshadow.setPosition(mouse.getPosition().x - 10.f, mouse.getPosition().y - 40.f);


		login.username.setString(input_text_username);
		login.password.setString(string(real_input_text_password.length(), '*'));


		signup.password.setString(string(real_input_text_password_signup.length(), '*'));
		signup.username.setString(input_text_username_signup);

		signup.Age.setString(input_text_Age);
		signup.Full_name.setString(input_text_FN);
		signup.General_info_text.setString(input_text_GI);

		Event event;

		while (window.pollEvent(event))
		{
			if (Login == true)
			{
				window.draw(background);
				draw_login(login);
				window.display();
			}
			if (Mouse::isButtonPressed(Mouse::Left) && mouseshadow.getGlobalBounds().intersects(login.signupbutton.getGlobalBounds()))
			{
				Signup = true;
				Login = false;
				Signup2 = false;
			}
			if (Signup == true && Signup2 == false)
			{
				window.clear();
				window.draw(background2);
				draw_signup1(signup);
				window.display();
			}

			if (event.type == Event::Closed)
			{
				window.close();
			}

			//    LOGIN AND SIGNUP fUNCTIONALITY COMPLETE DON'T TOUCH!!!!!!!!!

			if (event.type == Event::TextEntered && counter == 1 && Login == true && event.type != Keyboard::Enter)
			{
				input_text_username += static_cast<char>(event.text.unicode);
			}
			//if (counter == 1 && Keyboard::isKeyPressed(Keyboard::Enter))
			//{
			//	counter = 2;
			//	input_text_password.resize(0);
			//	input_text_password = "";
			//	real_input_text_password.resize(0);
			//	real_input_text_password = "";
			//}
			if (event.type == Event::TextEntered && counter == 2 && Login == true && event.type != Keyboard::Enter)
			{
				input_text_password += static_cast<char>(event.text.unicode);
				real_input_text_password += static_cast<char>(event.text.unicode);
			}
			//login
			bool chicken = false;

			if (Mouse::isButtonPressed(Mouse::Left) && mouseshadow.getGlobalBounds().intersects(login.loginbutton.getGlobalBounds()) && Login == true)
			{

				if (input_text_username.size() > 0 && real_input_text_password.size() > 0)
				{
					chicken = checklogin(users, input_text_username, real_input_text_password, Check);

				}

				input_text_username.resize(0);
				input_text_password.resize(0);
				real_input_text_password.resize(0);
				input_text_username = "";
				input_text_password = "";
				real_input_text_password = "";

				login.username.setString(input_text_username);
				login.password.setString(real_input_text_password);

				if (chicken == true && users[index_role].role == "doctor")
				{
					Check = true;
					Doctorpage = true;
					Patientpage = false;
					Login = false;
					Signup = false;
					Signup2 = false;
				}
				else if (chicken == true && users[index_role].role == "patient")
				{
					Check = true;
					Doctorpage = false;
					Patientpage = true;
					Login = false;
					Signup = false;
					Signup2 = false;

				}
				if (chicken == false)
				{
					Time Seconds = seconds(2);
					Clock clock;
					clock.restart();

					while (clock.getElapsedTime() < Seconds)
					{
						window.clear();
						window.draw(background);
						draw_login(login);
						draw_Wrong_login(wrong_login);
						window.display();

						if (clock.getElapsedTime() >= Seconds)
						{
							break;
						}
					}
				}

				if (Check == true && Doctorpage == true)
				{
					Login = false;
					Signup = false;
					Signup2 = false;
					window.clear();
					window.draw(background3);
					draw_doctorpage(doctorpage);
					window.display();
				}
				else if (Patientpage == true && Check == true)
				{
					Login = false;
					Signup = false;
					Signup2 = false;
					window.clear();
					window.draw(background4);
					draw_patientpage(patientpage);
					window.display();
				}

			}

			if (Mouse::isButtonPressed(Mouse::Left) && mouseshadow.getGlobalBounds().intersects(signup.loginbutton.getGlobalBounds()))
			{
				Signup = false;
				Signup2 = false;
				Login = true;
			}
			if (Signup2 == true && Login == false)
			{
				window.clear();
				window.draw(background2);
				draw_signup2(signup);
				window.display();
			}
			if (event.type == Event::TextEntered && counter == 4 && Signup == true && event.key.code != Keyboard::BackSpace)
			{
				input_text_password_signup += static_cast<char>(event.text.unicode);
				real_input_text_password_signup += static_cast<char>(event.text.unicode);
				PW = real_input_text_password_signup;
			}
			if (event.type == Event::TextEntered && counter == 5 && Signup == true && event.key.code != Keyboard::BackSpace)
			{
				input_text_username_signup += static_cast<char>(event.text.unicode);
				UN = input_text_username_signup;
			}

			if (Mouse::isButtonPressed(Mouse::Left) && Signup == true && mouseshadow.getGlobalBounds().intersects(signup.Dtextarea.getGlobalBounds()))
			{
				signup.Doctor.setFillColor(Color::Red);
				R = "doctor";
				Doctorpage = true;
				Patientpage = false;
				signup.Patient.setFillColor(Color::Black);
			}
			if (Mouse::isButtonPressed(Mouse::Left) && Signup == true && mouseshadow.getGlobalBounds().intersects(signup.Ptextarea.getGlobalBounds()))
			{
				signup.Patient.setFillColor(Color::Red);
				R = "patient";
				Doctorpage = false;
				Patientpage = true;
				signup.Doctor.setFillColor(Color::Black);
			}
			if (event.type == Event::MouseButtonReleased && mouseshadow.getGlobalBounds().intersects(signup.confirmbutton1.getGlobalBounds()))
			{
				SignUp(users, UN, PW, R, numusers,numpatients,numdoctors);
				if (input_text_username_signup != "" && input_text_password_signup != "")
				{
					Signup2 = true;
					Signup = false;
					Login == false;
				}

			}
			if (Mouse::isButtonPressed(Mouse::Left) && mouseshadow.getGlobalBounds().intersects(signup.loginbutton.getGlobalBounds()))
			{
				input_text_password_signup = "";
				input_text_username_signup = "";
				real_input_text_password_signup = "";
				input_text_Age = "";

				input_text_password_signup.resize(0);
				input_text_username_signup.resize(0);
				input_text_Age.resize(0);

				signup.username.setString("");
				signup.password.setString("");
				signup.Age.setString("");


				Signup = false;
				Signup2 = false;
				Login = true;
				window.clear(Color::White);
				window.draw(background);
				draw_login(login);
				window.display();
			}
			//signup2
			if (Mouse::isButtonPressed(Mouse::Left) && Signup2 == true && mouseshadow.getGlobalBounds().intersects(signup.Ftextarea.getGlobalBounds()))
			{
				signup.Female.setFillColor(Color::Blue);
				MF = "Female";
				signup.Male.setFillColor(Color::Black);
			}
			if (Mouse::isButtonPressed(Mouse::Left) && Signup2 == true && mouseshadow.getGlobalBounds().intersects(signup.Mtextarea.getGlobalBounds()))
			{
				signup.Male.setFillColor(Color::Blue);
				MF = "Male";
				signup.Female.setFillColor(Color::Black);
			}
			if (Mouse::isButtonPressed(Mouse::Left) && mouseshadow.getGlobalBounds().intersects(signup.Age_back.getGlobalBounds()) && Signup2 == true)
			{
				counter = 6;

			}
			if (event.type == Event::TextEntered && event.key.code != Keyboard::BackSpace && counter == 6)
			{
				if (isdigit(event.text.unicode))
				{
					input_text_Age += static_cast<char>(event.text.unicode);
					AG = stoi(input_text_Age);

				}

			}
			if (Mouse::isButtonPressed(Mouse::Left) && mouseshadow.getGlobalBounds().intersects(signup.Full_name_back.getGlobalBounds()) && Signup2 == true)
			{
				counter = 7;

			}
			if (event.type == Event::TextEntered && event.key.code != Keyboard::BackSpace && counter == 7)
			{
				input_text_FN += static_cast<char>(event.text.unicode);
				FN = input_text_FN;

			}
			if (Mouse::isButtonPressed(Mouse::Left) && mouseshadow.getGlobalBounds().intersects(signup.General_info_back.getGlobalBounds()) && Signup2 == true)
			{
				counter = 8;

			}
			if (event.type == Event::TextEntered && event.text.unicode != Keyboard::BackSpace && counter == 8)
			{
				input_text_GI += static_cast<char>(event.text.unicode);
				GI = input_text_GI;

			}
			if (event.key.code == Keyboard::Enter && counter == 8)
			{
				input_text_GI += '\n';
			}
			if (Mouse::isButtonPressed(Mouse::Left) && mouseshadow.getGlobalBounds().intersects(signup.confirmbutton2.getGlobalBounds()))
			{
				//show to sayed in order to send info before nulling
				signup2(doctors, patients, FN, GI, MF, AG, R);
				
			//	else
			//	{
			//		window.clear();
			//		window.draw(background);
			//		draw_login(login);
			//		draw_Wrong_login(wrong_login);
			//		window.display();
			//	}

				signup.Doctor.setFillColor(Color::Black);
				signup.Patient.setFillColor(Color::Black);
				signup.Female.setFillColor(Color::Black);
				signup.Male.setFillColor(Color::Black);

				input_text_FN = "";
				input_text_Age = "";
				input_text_GI = "";


				GI = input_text_GI;
				FN = input_text_FN;


				Signup = false;
				Signup2 = false;
				Login = true;
				//sign up fun
			}
			if (Mouse::isButtonPressed(Mouse::Left) && Check == true && Doctorpage == true && mouseshadow.getGlobalBounds().intersects(doctorpage.button1.getGlobalBounds()))
			{
				Swindow1 = false;
				Swindow2 = false;
				info_and_draw_SEARCH_FOR_DISEASE();
			}
			if (Mouse::isButtonPressed(Mouse::Left) && Check == true && Doctorpage == true && mouseshadow.getGlobalBounds().intersects(doctorpage.button2.getGlobalBounds()))
			{
				Swindow3 = true;
				info_edit_disease_doctor();
			}
			if (Mouse::isButtonPressed(Mouse::Left) && Check == true && Doctorpage == true && mouseshadow.getGlobalBounds().intersects(doctorpage.button3.getGlobalBounds()))
			{
				Swindow1 = false;
				Swindow2 = false;
				display_all_diseases_doctor();
			}
			if (Mouse::isButtonPressed(Mouse::Left) && Check == true && Doctorpage == true && mouseshadow.getGlobalBounds().intersects(doctorpage.button4.getGlobalBounds()))
			{
				info_add_disease();
			}
			if (Mouse::isButtonPressed(Mouse::Left) && Check == true && Doctorpage == true && mouseshadow.getGlobalBounds().intersects(doctorpage.button5.getGlobalBounds()))
			{
				info_edit_draw_info_doctor();
			}
			if (Mouse::isButtonPressed(Mouse::Left) && Check == true && Doctorpage == true && mouseshadow.getGlobalBounds().intersects(doctorpage.h1button.getGlobalBounds()))
			{
				Doctorpage = false;
				chicken = false;
				Check = false;
				Login = true;
			}
			if (Mouse::isButtonPressed(Mouse::Left) && Check == true && Patientpage == true && mouseshadow.getGlobalBounds().intersects(patientpage.button6.getGlobalBounds()))
			{
				Time Seconds2 = seconds(2);
				Clock clock2;
				clock2.restart();

				while (clock2.getElapsedTime() < Seconds2)
				{
					window.clear();
					clearDiagnosisHistory();
					window.draw(background4);
					draw_patientpage(patientpage);
					draw_delete_history(delete_history);
					window.display();


					if (clock2.getElapsedTime() >= Seconds2)
					{
						window.clear();
						clearDiagnosisHistory();
						window.draw(background4);
						draw_patientpage(patientpage);
						//draw_delete_history(delete_history);
						window.display();

					}

				}

			}
			if (Mouse::isButtonPressed(Mouse::Left) && Check == true && Patientpage == true && mouseshadow.getGlobalBounds().intersects(patientpage.button7.getGlobalBounds()))
			{
				RenderWindow window5(VideoMode(1635, 920), "View Info", Style::Default);

				while (window5.isOpen())
				{
					Event event5;

					window5.clear();
					window5.draw(SIX_BACK);
					window5.draw(bigback);
					window5.draw(view_info.texteditarea1);
					window5.draw(view_info.texteditarea2);
					window5.draw(view_info.texteditarea3);
					window5.draw(view_info.texteditarea4);

					view_info.text1.setString(patients[user_id].full_name);
					view_info.text2.setString(to_string(patients[user_id].age));
					view_info.text3.setString(patients[user_id].gender);
					view_info.text4.setString(to_string(user_id));

					Text text5[15];
					int var = 1;

					for (int counter = 0; counter < 15; counter++)
					{

						if (counter >= 0 && counter <= 4)
						{
							text5[counter].setFont(font1);
							text5[counter].setCharacterSize(30);
							text5[counter].setFillColor(Color::Black);
							text5[counter].setPosition(50 + 20, 65 + (93 * 6 + (var * 30)) - 40);

							var++;
						}
						if (counter >= 5 && counter <= 9)
						{
							text5[counter].setFont(font1);
							text5[counter].setCharacterSize(30);
							text5[counter].setFillColor(Color::Black);
							text5[counter].setPosition(50 + 300, 65 + (93 * 6 + (var * 30)) - 40);
							var++;
						}
						if (counter >= 10 && counter <= 14)
						{
							text5[counter].setFont(font1);
							text5[counter].setCharacterSize(30);
							text5[counter].setFillColor(Color::Black);
							text5[counter].setPosition(50 + 650, 65 + (93 * 6 + (var * 30)) - 40);
							var++;
						}
						if (var == 5)
						{
							var = 0;
						}
						text5[counter].setString(patients[user_id].diseases_history[counter]);

					}
					window5.draw(view_info.text1);
					window5.draw(view_info.text2);
					window5.draw(view_info.text3);
					window5.draw(view_info.text4);
					for (int counter2 = 0; counter2 < 14; counter2++)
					{
						window5.draw(text5[counter2]);
					}
					window5.display();
					while (window5.pollEvent(event5))
					{
						if (event5.type == Event::Closed)
						{
							window5.close();
						}
					}
				}

			}
			if (Mouse::isButtonPressed(Mouse::Left) && Check == true && Patientpage == true && mouseshadow.getGlobalBounds().intersects(patientpage.button8.getGlobalBounds()))
			{

				int counter3 = 0;
				string temp = to_string(patients[user_id].age);

				RenderWindow window6(VideoMode(1635, 920), "Edit info", Style::Default);
				while (window6.isOpen())
				{
					bool open = true;

					RectangleShape mouseshadow(Vector2f(10, 30));
					mouseshadow.setFillColor(Color::Black);
					mouseshadow.setPosition(mouse.getPosition().x - 120, mouse.getPosition().y - 130);

					RectangleShape cursor(Vector2f(5, 0));
					cursor.setFillColor(Color::Black);

					Text1 = patients[user_id].full_name;
					Text5 = patients[user_id].info;

					edit_info.text1.setString(Text1);
					edit_info.text2.setString(temp);
					edit_info.text5.setString(Text5);

					Event event6;
					while (window6.pollEvent(event6))
					{
						if (event6.type == Event::Closed)
						{
							window6.close();
							patients[user_id].age = stoi(temp);
							open = false;
						}
						if (event6.type == Event::MouseButtonReleased && mouseshadow.getGlobalBounds().intersects(edit_info.button4.getGlobalBounds()))
						{

							window6.close();
							patients[user_id].age = stoi(temp);
							open = false;
						}
						if (Mouse::isButtonPressed(Mouse::Left) && mouseshadow.getGlobalBounds().intersects(edit_info.texteditarea1.getGlobalBounds()))
						{
							counter3 = 1;
						}
						if (counter3 == 1 && event6.type == Event::TextEntered && event6.text.unicode != Keyboard::BackSpace)
						{
							Text1 += static_cast<char>(event6.text.unicode);
							patients[user_id].full_name = Text1;
						}
						if (Keyboard::isKeyPressed(Keyboard::BackSpace) && counter3 == 1 && Text1.size() > 0)
						{
							Text1.resize(Text1.size() - 1);
							patients[user_id].full_name = Text1;
						}
						if (Mouse::isButtonPressed(Mouse::Left) && mouseshadow.getGlobalBounds().intersects(edit_info.texteditarea2.getGlobalBounds()))
						{
							counter3 = 2;
						}
						if (event6.type == Event::TextEntered && event6.key.code != Keyboard::BackSpace && counter3 == 2)
						{
							if (isdigit(event6.text.unicode))
							{
								temp += static_cast<char>(event6.text.unicode);
								to_string(patients[user_id].age) = stoi(temp);
							}
						}
						if (Keyboard::isKeyPressed(Keyboard::Backspace) && counter3 == 2 && temp.size() > 0)
						{
							temp.resize(temp.size() - 1);

						}
						if (Mouse::isButtonPressed(Mouse::Left) && mouseshadow.getGlobalBounds().intersects(edit_info.texteditarea5.getGlobalBounds()))
						{
							counter3 = 5;
						}
						if (counter3 == 5 && event6.type == Event::TextEntered && event6.text.unicode != Keyboard::BackSpace)
						{
							Text5 += static_cast<char>(event6.text.unicode);
							patients[user_id].info = Text5;
						}
						if (Keyboard::isKeyPressed(Keyboard::BackSpace) && counter3 == 5 && Text5.size() > 0)
						{
							Text5.resize(Text5.size() - 1);
							patients[user_id].info = Text5;
						}
					}
					if (counter3 == 1 && event6.type == Event::MouseButtonReleased && mouseshadow.getGlobalBounds().intersects(edit_info.texteditarea1.getGlobalBounds()))
					{
						cursorVisible = true;
					}
					if (cursorVisible && counter3 == 1)
					{
						cursor.setSize(Vector2f(2, edit_info.texteditarea1.getLocalBounds().height * 0.55));
						cursor.setPosition(edit_info.text1.getPosition().x + edit_info.text1.getLocalBounds().width + 5, edit_info.text1.getPosition().y + 7);

					}
					if (counter3 == 2 && event6.type == Event::MouseButtonReleased && mouseshadow.getGlobalBounds().intersects(edit_info.texteditarea2.getGlobalBounds()))
					{
						cursorVisible = true;
					}
					if (cursorVisible && counter3 == 2)
					{
						cursor.setSize(Vector2f(2, edit_info.texteditarea2.getLocalBounds().height * 0.55));
						cursor.setPosition(edit_info.text2.getPosition().x + edit_info.text2.getLocalBounds().width + 5, edit_info.text2.getPosition().y + 5);

					}
					if (counter3 == 5 && event6.type == Event::MouseButtonReleased && mouseshadow.getGlobalBounds().intersects(edit_info.texteditarea5.getGlobalBounds()))
					{
						cursorVisible = true;
					}
					if (cursorVisible && counter3 == 5)
					{
						cursor.setSize(Vector2f(2, edit_info.texteditarea5.getLocalBounds().height * 0.15));
						cursor.setPosition(edit_info.text5.getPosition().x + edit_info.text5.getLocalBounds().width + 5, edit_info.text5.getPosition().y + 4);

					}
					if (cursorClock.getElapsedTime().asMilliseconds() >= 500)
					{
						cursorVisible = !cursorVisible;
						cursorClock.restart();
					}
					window6.clear();
					window6.draw(Bigback);
					window6.draw(edit_info.texteditarea1);
					window6.draw(edit_info.texteditarea2);
					window6.draw(edit_info.texteditarea5);
					window6.draw(edit_info.text1);
					window6.draw(edit_info.text2);
					window6.draw(edit_info.text5);
					window6.draw(edit_info.button4);
					window6.draw(cursor);
					window6.draw(mouseshadow);
					window6.display();

				}

			}
			if (Mouse::isButtonPressed(Mouse::Left) && Check == true && Patientpage == true && mouseshadow.getGlobalBounds().intersects(patientpage.button9.getGlobalBounds()))
			{
				Logic_gate = false;
				input_syptoms();
				draw_find_your_disease();
			}
			if (Mouse::isButtonPressed(Mouse::Left) && Check == true && Patientpage == true && mouseshadow.getGlobalBounds().intersects(patientpage.h2button.getGlobalBounds()))
			{
				Patientpage = false;
				chicken = false;
				Login = true;

			}

			if (Keyboard::isKeyPressed(Keyboard::Backspace))
			{
				if (input_text_password_signup.size() > 0 && counter == 4)
				{
					input_text_password_signup.resize(input_text_password_signup.size() - 1);
					real_input_text_password_signup.resize(real_input_text_password_signup.size() - 1);
				}
				else if (counter == 5 && input_text_username_signup.size() > 0)
				{
					input_text_username_signup.resize(input_text_username_signup.size() - 1);
				}
				else if (input_text_password.size() > 0 && counter == 2 && Login == true)
				{
					input_text_password.resize(input_text_password.size() - 1);
					real_input_text_password.resize(real_input_text_password.size() - 1);
				}
				else if (input_text_username.size() > 0 && counter == 1 && Login == true)
				{
					input_text_username.resize(input_text_username.size() - 1);
				}
				else if (input_text_Age.size() > 0 && Signup2 == true && counter == 6)
				{
					input_text_Age.resize(input_text_Age.size() - 1);
				}
				else if (input_text_FN.size() > 0 && counter == 7)
				{
					input_text_FN.resize(input_text_FN.size() - 1);
				}
				else if (input_text_GI.size() > 0 && counter == 8)
				{
					input_text_GI.resize(input_text_GI.size() - 1);
				}
			}

		}
		if (cursorClock.getElapsedTime().asMilliseconds() >= 500)
		{
			cursorVisible = !cursorVisible;
			cursorClock.restart();
		}
		// Common cursor handling code
		if (Mouse::isButtonPressed(Mouse::Left) && mouseshadow.getGlobalBounds().intersects(login.textbackgroundu.getGlobalBounds()) && Login == true && Signup == false && Signup2 == false)
		{
			counter = 1;
			cursorVisible = true;
		}

		if (cursorVisible && counter == 1)
		{
			cursor.setSize(Vector2f(2, login.textbackgroundu.getLocalBounds().height * 0.52));
			cursor.setPosition(login.username.getPosition().x + login.username.getLocalBounds().width + 5, login.username.getPosition().y + 6);
		}

		// Page-specific cursor handling
		if (Login == true && Signup == false && Signup2 == false)
		{
			if (Mouse::isButtonPressed(Mouse::Left) && mouseshadow.getGlobalBounds().intersects(login.textbackgroundp.getGlobalBounds()))
			{
				counter = 2;
				cursorVisible = true;
			}

			if (cursorVisible && counter == 2)
			{
				cursor.setSize(Vector2f(2, login.textbackgroundp.getLocalBounds().height * 0.5));
				cursor.setPosition(login.password.getPosition().x + login.password.getLocalBounds().width + 5, login.password.getPosition().y + 8);
			}

			window.clear();
			window.draw(background);
			draw_login(login);
			window.draw(cursor);
			window.display();
		}
		if (Signup == true && Signup2 == false && Login == false)
		{
			if (Mouse::isButtonPressed(Mouse::Left) && mouseshadow.getGlobalBounds().intersects(signup.texteditp.getGlobalBounds()) && Signup == true)
			{
				counter = 4;
				cursorVisible = true;
			}

			if (cursorVisible && counter == 4)
			{
				cursor.setSize(Vector2f(2, signup.texteditp.getLocalBounds().height * 0.5));
				cursor.setPosition(signup.password.getPosition().x + signup.password.getLocalBounds().width + 5, signup.password.getPosition().y + 4);
			}
			if (Mouse::isButtonPressed(Mouse::Left) && mouseshadow.getGlobalBounds().intersects(signup.texteditu.getGlobalBounds()) && Signup == true)
			{
				counter = 5;
				cursorVisible = true;
			}
			if (cursorVisible && counter == 5 && Signup == true)
			{
				cursor.setSize(Vector2f(2, signup.texteditu.getLocalBounds().height * 0.5));
				cursor.setPosition(signup.username.getPosition().x + signup.username.getLocalBounds().width + 5, signup.username.getPosition().y + 4);
			}

		}
		if (Signup == false && Login == false && Signup2 == true)
		{
			if (Mouse::isButtonPressed(Mouse::Left) && mouseshadow.getGlobalBounds().intersects(signup.Age_back.getGlobalBounds()))
			{
				counter = 6;
				cursorVisible = true;
			}
			if (cursorVisible && counter == 6 && Signup2 == true)
			{
				cursor.setSize(Vector2f(2, signup.Age_back.getLocalBounds().height * 0.5));
				cursor.setPosition(signup.Age.getPosition().x + signup.Age.getLocalBounds().width + 5, signup.Age.getPosition().y + 2);
			}
			if (Mouse::isButtonPressed(Mouse::Left) && mouseshadow.getGlobalBounds().intersects(signup.Ftextarea.getGlobalBounds()))
			{
				counter = 7;
				cursorVisible = true;
			}
			if (cursorVisible && counter == 7 && Signup2 == true)
			{
				cursor.setSize(Vector2f(2, signup.Ftextarea.getLocalBounds().height * 0.7));
				cursor.setPosition(signup.Full_name.getPosition().x + signup.Full_name.getLocalBounds().width + 5, signup.Full_name.getPosition().y + 13);
			}
			if (Mouse::isButtonPressed(Mouse::Left) && mouseshadow.getGlobalBounds().intersects(signup.General_info_back.getGlobalBounds()))
			{
				counter = 8;
				cursorVisible = true;
			}
			if (cursorVisible && counter == 8 && Signup2 == true && Signup == false)
			{
				cursor.setSize(Vector2f(2, signup.General_info_back.getLocalBounds().height * 0.15));
				cursor.setPosition(signup.General_info_text.getPosition().x + signup.General_info_text.getLocalBounds().width + 5, signup.General_info_text.getPosition().y + 8);
			}
		}
		if (Signup == true && Signup2 == false && Login == false)
		{
			window.clear();
			window.draw(background2);
			draw_signup1(signup);
			window.draw(cursor);
			window.display();
		}
		if (Signup2 == true && Signup == false && Login == false)
		{
			window.clear();
			window.draw(background2);
			draw_signup2(signup);
			window.draw(cursor);
			window.display();
		}
	}

	return 0;
}
