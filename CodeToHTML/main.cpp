#include <iostream>
#include <vector>
#include <string>
#include <Windows.h>
using namespace std;

const size_t KeywordsSize = 5;
const string keywords[] = { "if", "else", "else if", "for", "while" };

// 다른 사람 코드 가져옴.
// http://www.cplusplus.com/forum/beginner/14349/
void toClipboard(const std::string &s) {
	OpenClipboard(0);
	EmptyClipboard();
	HGLOBAL hg = GlobalAlloc(GMEM_MOVEABLE, s.size());
	if (!hg) {
		CloseClipboard();
		return;
	}
	memcpy(GlobalLock(hg), s.c_str(), s.size());
	GlobalUnlock(hg);
	SetClipboardData(CF_TEXT, hg);
	CloseClipboard();
	GlobalFree(hg);
}

bool isOneLineKeyword(const string& str)
{
	for (int i = 0; i < KeywordsSize; ++i)
	{
		if (keywords[i] == str.substr(0, keywords[i].size()) && str[str.size() - 1] != '{' && str[str.size() - 1] != ';')
		{
			return true;
		}
	}
	return false;
}

int main()
{
	vector<string> codes;
	string line;
	int spacesTimes = 0;
	bool one_line = false;

	while (getline(cin, line))
	{
		/**
		 * line을 순회
		 * if(flag) -> &nbsp * 4 추가
		 * 꺽쇠 -> &lt; &gt;
		 * 문자열 마지막에 '\n' 추가
		 */
		for (size_t i = 0; i < line.size(); ++i)
		{
			if (line[i] == '<')
			{
				line.erase(i, 1);
				line.insert(i, "&lt;");
			}
			else if (line[i] == '>')
			{
				line.erase(i, 1);
				line.insert(i, "&gt;");
			}
		}

		if (line[0] == '}')
		{
			spacesTimes--;
		}

		if (one_line || spacesTimes)
		{
			if (one_line)
			{
				spacesTimes++;
			}
			for (int j = 0; j < 4 * spacesTimes; ++j)
			{
				line.insert(0, "&nbsp;");
			}
			if (one_line)
			{
				spacesTimes--;
				one_line = false;
			}
		}

		if (line.size() > 0 && line[line.size() - 1] == '{')
		{
			spacesTimes++;
		}
		if (isOneLineKeyword(line))
		{
			one_line = true;
		}

		line += '\n';
		codes.push_back(line);
	}

	system("cls");
	line = "";
	for (string i : codes)
	{
		line += i;
		cout << i;
	}
	toClipboard(line);
	return 0;
}