#include <iostream>
#include <conio.h>
#include <string>
using namespace std;
char replacechar(char a)
{
	int checker;
	checker = a - 97;
	char replacer[26];
	for (int i = 0; i < 26; i++)
	{
		replacer[i] = 'z' - i;
	}
	a = replacer[checker];
	return a;
}
string decrypter(string a)
{
	for (int i = 0; i < a.length(); i++)
	{
		if (a[i] >= 'a' && a[i] <= 'z')
		{
			// replcing the letter with the opposite from the z side.
			a[i] = replacechar(a[i]);
		}
		else
			continue;
	}
	return a;
}
int main()
{
	string cipheredtext;
	cout << "enter the text that you want to code. " << endl;
	getline(cin, cipheredtext);
	cout << decrypter(cipheredtext);
	return 0;
}