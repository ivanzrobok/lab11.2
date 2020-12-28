//Рівень А).Сформувати файл структур, що містять інформацію про : прізвище
//студента, курс, спеціальність(для представлення спеціальності використовувати переліки, а
//	для представлення курсу – цілі числа) та оцінки з фізики, математики, інформатики.//

//Варіант 9.
//1. Обчислити кількість оцінок «відмінно» з кожного предмету.
//2. Обчислити кількість студентів, які отримали з фізики і математики оцінки «5».

#include <iostream>
#include <fstream>
#include<clocale>
using namespace std;

enum Group { COMPUTERSINCE, INFORMATIC, MATHANDECONOMIC, FISICSNDINFORMATIC, TUTISIONWORK };
string Namegrup[] = { "комп. науки","Інформатика","Мат. та економіка","Фізика та інф.","«Трудове навчання" };

struct student
{
	char prizv[100];
	unsigned curs;
	Group group;
	int firstmark;
	int secondmark;
	union 
	{
		int prog;
		int chmesod;
		int workjob;
	};
};
void inputBIN(char* fname);
void printBIN(char* fname);

int main()
{
	setlocale(LC_CTYPE, "rus");
	char fname[60];
	cout << "enter name file : ";
	cin >> fname;
	
	int menuitem;
	do
	{
		cin.get();
		cin.sync();
		
		cout << "[1]-entet data and save "<<endl;
		cout << "[2]-print spedship whith date " << endl;
		cout << "[0]-exit with program " << endl;
		cout << "Enter figure: "; cin >> menuitem;

		switch (menuitem)
		{
		case 1:
			inputBIN(fname);
			break;
		case 2:
			printBIN(fname);
			break;
		case 0:
			exit(1);
			break;
		default:
			cout << "Error input! ";
			break;
		}
		
	} while (menuitem !=0);
}
void printBIN(char* fname)
{
	ifstream fin(fname, ios::binary);
	if (!fin) {
		cerr << "Error oopen file '" << fname << "'";
		return;
	}
	student Students;
	while (fin.read((char*)&Students, sizeof(student)))
	{
		cout << endl;
		cout << "name: " << Students.prizv << endl;
		cout << "------------------------------------"<<endl;
		cout << "cours: " << Students.curs << endl;
		cout << "------------------------------------" << endl;
		cout << "group: " << Students.group << endl;
		cout << "------------------------------------" << endl;
		cout << "first mark: " << Students.firstmark << endl;
		cout << "------------------------------------" << endl;
		cout << "second mark: " << Students.secondmark << endl;
		cout << "------------------------------------" << endl;
		cout << "third mark: " << Students.chmesod << endl;
		cout << "===================================="<<endl;
		cout << endl;
	}

}
void inputBIN(char* fname)
{
	ofstream file(fname, ios::binary);
	if (!file)
	{
		cerr << "Error open file '" << fname << "'";
		return;
	}
	student Students;
	char ch;
	int groupN;
	
	do
	{
		
		cin.get(); // очищуємо буфер клавіатури – бо залишаються символи
		cin.sync(); // "кінець рядка", які не дають ввести наступний літерний рядок
		
		cout << " прізвище: "; cin >> Students.prizv;
		cout << " курс "; cin >> Students.curs;

		cout << " група (0 - компютерні науки, 1 - інформатика, 2 - математика і економіка, 3 - фізика і математика, 4 - трудове навчання): ";
		cin >> groupN;
		cout << " оцінка з фізики "; cin >> Students.firstmark;
		cout << " оцінка з математики "; cin >> Students.secondmark;
		Students.group = (Group)groupN;
		switch (Students.group)
		{
		case COMPUTERSINCE:
			cout << "оцінка з програмування"; cin >> Students.prog;
			break;
		case INFORMATIC:
			cout << "оцінка з чисельних методів "; cin >> Students.chmesod;

			break;
		case MATHANDECONOMIC:
		case FISICSNDINFORMATIC:
		case TUTISIONWORK:
			cout << "оцінка з педагогіки "; cin >> Students.workjob;
			break;
		}
		cout << endl;
		if (!file.write((char*)&Students, sizeof(student)))
		{
			cerr << "Error writing file." << endl;
		}
		cout << "Continue? (Y/N) "; cin >> ch;
	} while (ch=='y'|| ch=='Y');
	
}