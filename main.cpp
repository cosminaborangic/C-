#include "UI.h"
#include "GUI.h"
#include <iostream>
#include <filesystem>

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include "OOPLab1011QT.h"
#include <QtWidgets/QApplication>

using std::cout;
using std::endl;





void test_all() {
	teste_domain();
	cout << "Au trecut toate testele din domain." << endl;
	teste_repo();
	cout << "Au trecut toate testele din repo." << endl;
	teste_srv();
	cout << "Au trecut toate testele din service." << endl;
	teste_program();
	cout << "Au trecut toate testele din program." << endl;
}

//void start() {
//	ActivitateRepoFile repo{ "activities.txt" };
//	//ActivitateRepository repo;
//	ActivitateValidator val;
//	Program program;
//	ActivitateStore srv{ repo, val,program };
//	Console ui{ srv };
//	ui.run();
//}

//int main() {
//	_CrtDumpMemoryLeaks();
//	test_all();
//	start();
//}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	ActivitateRepoFile repo{ "activities.txt" };
	//ActivitateRepository repo;
	ActivitateValidator val;
	Program program;
	ActivitateStore srv{ repo, val,program };
	ConsoleGUI gui{ srv };
    gui.show();

	ConsoleGUIProgram guiProgram{ srv };
	guiProgram.show();

    return a.exec();
}