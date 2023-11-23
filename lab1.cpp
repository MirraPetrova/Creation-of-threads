#include <windows.h>
#include <iostream>
//#include <process.h>
#include <vector>
using namespace std;
volatile UINT sum;
volatile DWORD dwCount;
DWORD WINAPI Worker(LPVOID Mas)
{
	//sum = 0;
	vector<long>* m = reinterpret_cast<vector<long>*>(Mas);
	for (int i = 0; i < m->size(); i++)
	{
		sum += (*m)[i] * (*m)[i];
		cout << "Intermediate result: " << sum << endl;
		Sleep(120);
	}
	return 0;
}

int main()
{
	srand((int)time(NULL));
	int n;
	cout << "Enter size of array: ";
	cin >> n;
	vector<long> mas(n);
	for (int i = 0; i < n; i++)
		mas[i] = rand() % 10;
	for (int i = 0; i < n; i++)
		cout << mas[i] << " ";

	HANDLE	hThread;
	DWORD	IDThread;
	//UINT	IDThread;
	char str;
	

	hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Worker, (LPVOID)&mas, 0, &IDThread);
	/*hThread = (HANDLE)
		_beginthreadex(NULL, 0, (LPTHREAD_START_ROUTINE)Worker, &mas, 0, &IDThread);*/
	if (hThread == NULL)
		return GetLastError();
	for (; ; )
	{
		cout << endl << "Choose :" << endl;
		cout << "\t'1' - show result" << endl;
		cout << "\t'2' - suspend thread" << endl;
		cout << "\t'3' - resume thread" << endl;
		cout << "\t'4' - exit" << endl;
		cin >> str;
		switch (str)
		{
		case '1':

			cout << "sum = " << sum << endl;
			break;
		case '2':

			dwCount = SuspendThread(hThread);
			cout << "Thread suspend count = " << dwCount << endl;
			break;
		case '3':

			dwCount = ResumeThread(hThread);
			cout << "Thread suspend count = " << dwCount << endl;
			break;
		case '4':
			CloseHandle(hThread);
			return 0;
		}
	}
	//WaitForSingleObject(hThread, INFINITE);
	CloseHandle(hThread);

	return 0;
}
