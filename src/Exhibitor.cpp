#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>

#define SIZE 500
#define MAX_MEMB 4
#define MAX_NAME 20
#define MAX_DESC 120
#define MAX_KEYS 20
#define MAX_DATE 10
#define MAX_LINK 255

using namespace std;

class Project {
	private:
		//>>>Record data<<<
		char buf[SIZE];
		char prj_name[MAX_NAME * 2], prj_memb[4][MAX_NAME], prj_date[MAX_DATE], prj_desc[MAX_DESC], prj_link[MAX_LINK];
		int n_memb;

		//>>>Index data<<<
		char keys[MAX_KEYS][MAX_NAME];
		int recAddr[MAX_KEYS];
		int n_keys;

		void pack();
		void unpack();
	public:
		Project();
		~Project();
		void menu();
		void add();
		void ins(char [MAX_NAME], int);
		void disp();
		void src();
		int find(char [MAX_NAME]);
		void mod();
		void del();
		void rem(char [MAX_NAME]);
};

Project::Project() {
	int i=0;
	ifstream fin;

	fin.open("Prj.index", ios::in);

	while(!fin.eof()) {
		fin.getline(keys[i], MAX_NAME * 2, '\t');
		fin >> recAddr[i];
		if(fin.fail())
			break;
		i++;
	}
	n_keys=i;

	fin.close();
}

Project::~Project() {
	int i;
	ofstream fout;

	fout.open("Prj.index", ios::out);

	for (i=0; i < n_keys; i++) {
		fout << keys[i] << "\t" << recAddr[i] << endl;
	}

	fout.close();
}

void Project::pack() {
	int i;
	char *temp = new char[2];

	sprintf(temp,"%d", n_memb);
	strcpy(buf, prj_name);
	strcat(buf, "|");
	strcat(buf, temp);
	strcat(buf, "|");
	for (i=0; i < n_memb; i++) {
		strcat(buf, prj_memb[i]);
		strcat(buf, "|");
	}
	strcat(buf, prj_date);
	strcat(buf, "|");
	strcat(buf, prj_desc);
        strcat(buf, "|");
        strcat(buf, prj_link);
	strcat(buf, "#");
}

void Project::unpack() {
	int i;
	char *temp=new char[2];

	strcpy(prj_name, strtok(buf, "|"));
	strcpy(temp, strtok(NULL, "|"));
	n_memb = atoi(temp);
	for (i=0; i < n_memb; i++)
		strcpy(prj_memb[i], strtok(NULL, "|"));
	strcpy(prj_date, strtok(NULL, "|"));
	strcpy(prj_desc, strtok(NULL, "|"));
	strcpy(prj_link, strtok(NULL, "#"));
}

void Project::add() {
	int i;
	int pos;
	ofstream fout;

	fout.open("Prj.dat", ios::app);

	cout << "Enter the Project Name : ";
	cin.ignore(256, '\n');
	cin.getline(prj_name, MAX_NAME * 2);
	do {
		cout << "Enter the number of Team Members (1 - 4): ";
		cin  >> n_memb;
	}while(n_memb < 1 || n_memb > MAX_MEMB);
	cin.ignore(256, '\n');
	for (i=0; i < n_memb; i++) {
		cout << "Enter Member " << i+1 << "'s Name : ";
		cin.getline(prj_memb[i], MAX_NAME);
	}

	cout << "Enter the Project Date (yyyy-mm-dd) : ";
	cin.getline(prj_date, 11);
	cout << "Enter the Project Description : ";
	cin.getline(prj_desc, MAX_DESC);
	cout << "Enter the Project Link : ";
	cin.getline(prj_link, MAX_LINK);

	pos = (int)fout.tellp();
	pack();
	fout << buf << "\n";
	ins(prj_name, pos);
	cout << "Record added!\n";

	fout.close();
}

void Project::ins(char key[MAX_NAME], int pos) {
	int i;
	int index = find(key);

	if(index >= 0) {
		cout << "Record Exists!\n";
		return;
	}
	if(n_keys == MAX_KEYS) {
		cout << "Index is FULL!\n";
		return;
	}
	for(i=n_keys-1; i >= 0; i--) {
		if(strcmp(key, keys[i]) < 0) {
			strcpy(keys[i+1], keys[i]);
			recAddr[i+1]=recAddr[i];
		}else {
			break;
		}
	}
	strcpy(keys[i+1], key);
	recAddr[i+1]=pos;
	n_keys++;
}

void Project::disp() {
	int i;
	ifstream fin;

	fin.open("Prj.dat", ios::in);

	cout << "Record File : Prj.dat\n\n";

	while(!fin.eof()) {
		fin.getline(buf, SIZE);
		if(fin.fail())
			break;
		unpack();
		cout << "\tProject Name : " << prj_name << endl;
		for (i=0; i < n_memb; i++)
			cout << "\tProject Member " << i+1 << "'s Name : " << prj_memb[i] << endl;
		cout << "\tProject Date : " << prj_date << endl;
		cout << "\tProject Description : " << prj_desc << endl << endl;
		cout << "\tProject Link : " << prj_link << endl << endl;
	}

	fin.close();

	cout << "Index File : Prj.index\n\n";

	for(i=0; i < n_keys; i++)
		cout << keys[i] << "\t" << recAddr[i] << "\n";
}

void Project::src() {
	
}

int Project::find(char key[MAX_NAME]) {
	for(int i=0; i < n_keys; i++) {
		if(strcmp(keys[i], key)==0)
			return i;
	}
	return -1;
}

void Project::mod() {
	
}

void Project::del() {
	
}

void Project::rem(char key[MAX_NAME]) {
	
}

void Project::menu() {
	while(1) {
		int ch;

		cout << "FS Weblink to Exhibitor\n\n";
		cout << "\t1) Add Record\n";
		cout << "\t2) Display Records\n";
		cout << "\t3) Search Record\n";
		cout << "\t4) Modify Record\n";
		cout << "\t5) Delete Record\n";
		cout << "\t6) Exit\n";
		cout << ">>> ";
		cin >> ch;
		cout << "\n\n";

		switch(ch) {
			case 1:
				add();
			break;
			case 2:
				disp();
			break;
			case 3:
				src();
			break;
			case 4:
				mod();
			break;
			case 5:
				del();
			break;
			case 6:
				return;
			break;
			default:
			break;
		}
	}
}

int main() {
	Project p;
	p.menu();
	return 0;
}
