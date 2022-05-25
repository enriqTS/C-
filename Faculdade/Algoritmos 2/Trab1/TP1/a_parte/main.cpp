#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <list>
#define MAX_CHAR 256
using namespace std;

class SuffixTrieNode
{
private:
    SuffixTrieNode *children[MAX_CHAR];
    list<int> *indexes;
    list<char> *words;

public:
    SuffixTrieNode()
    {
        words = new list<char>;
        indexes = new list<int>;
        for (int i = 0; i < MAX_CHAR; i++)
            children[i] = NULL;
    }

    void insertSuffix(string suffix, int index, char word);
    list<int> *search(string pat);
    list<char> *display(string pat);
};

class SuffixTrie
{
private:
    SuffixTrieNode root;

public:
    SuffixTrie(string txt)
    {
        for (int i = 0; i < txt.length(); i++)
            root.insertSuffix(txt.substr(i), i, txt[i]);
    }

    string search(string pat);
    string display(string pat);
    void showInd(string text);
};

void SuffixTrieNode::insertSuffix(string s, int index, char word)
{
    indexes->push_back(index);
    words->push_back(word);

    if (s.length() > 0)
    {
        char cIndex = s.at(0);
        if (children[cIndex] == NULL)
            children[cIndex] = new SuffixTrieNode();
        children[cIndex]->insertSuffix(s.substr(1), index + 1, s[word + 1]);
    }
}

list<int> *SuffixTrieNode::search(string s)
{
    if (s.length() == 0)
        return indexes;
    if (children[s.at(0)] != NULL)
        return (children[s.at(0)])->search(s.substr(1));
    else
        return NULL;
}

string SuffixTrie::search(string pat)
{
    list<int> *result = root.search(pat);

    string aux = "";

    if (result == NULL)
    {
        return "";
    }

    else
    {
        list<int>::iterator i;
        int patLen = pat.length();
        for (i = result->begin(); i != result->end(); ++i)
            aux += to_string(*i - patLen) + ",";
    }
    aux.pop_back();
    return aux;
}

string SuffixTrie::display(string pat)
{
    list<int> *result = root.search(pat);

    string aux = "";

    if (result == NULL)
    {
        cout << "Palavra não encontrada"
             << endl;
        return "";
    }

    else
    {
        string aux2;
        list<int>::iterator i;
        int patLen = pat.length();
        for (i = result->begin(); i != result->end(); ++i)
        {
            aux2 = *i - patLen;
            aux += to_string(*i - patLen);
        }
    }
    aux.pop_back();
    return aux;
}

void ConvertToLowerCase(string &text)
{
    for (int i = 0; i < text.length(); i++)
    {
        text[i] = tolower(text[i]);
    }
}

void RemoveTextSigns(string &text)
{
    for (int i = 0; i < text.length(); i++)
    {
        if (ispunct(text[i]))
            text[i] = ' ';
    }
}

void HighlightText(string positions, string text, int sizeWord)
{
    int numP = 0;
    positions += ",";
    int i;
    for (i = 0; i < positions.length(); i++)
    {
        if (positions[i] == ',')
        {
            numP++;
        }
    }
    int is[numP];
    int j = 0;

    string aux = "";
    for (int i = 0; i < positions.length(); i++)
    {
        if (positions[i] == ',')
        {
            is[j] = stoi(aux);
            aux = "";
            j++;
        }
        else
        {
            aux += positions[i];
        }
    }

    j = 0;

    for (i = 0; i < text.length(); i++)
    {
        if (is[j] != i)
        {
            cout << text[i];
        }
        else
        {
            printf("\033[31m");
            for (int k = 0; k < sizeWord; k++)
            {
                cout << text[i];
                i++;
            }
            printf("\033[0m");
            if (is[j + 1] != i)
            {
                cout << text[i];
            }
            j++;
        }
    }
    cout << endl;
}

string showIndex(string text, SuffixTrie S)
{
    string aux = "";
    string indexs = "";
    // string result = S.search(text);

    for (int i = 0; i < text.length(); i++)
    {
        if (text[i] == ',')
        {
            if (indexs.find(aux) >= indexs.length())
            {
                indexs += aux + ", " + S.search(aux) + "\n";
            }
            i++;
            aux = "";
        }
        if (text[i] != '\n')
        {
            aux += text[i];
        }
    }

    return indexs;
}

void SepareWords(string &text)
{
    for (int i = 0; i < text.length(); i++)
    {
        if ((text[i] == ' ' || text[i + 1] == '\n') && text[i - 1] != ',')
        {
            text[i] = ',';
        }
    }
    text += ',';
}

void OneLine(string &text)
{
    for (int i = 0; i < text.length(); i++)
    {
        if ((int)text[i] == 10 || (int)text[i] == 13)
        {
            text[i] = 'E';
        }
    }
    text.erase(std::remove(text.begin(), text.end(), 'E'), text.end());
}

int main()
{
    ifstream ifs;
    ifs.open("test.txt");
    string text;
    text.assign((istreambuf_iterator<char>(ifs)), (istreambuf_iterator<char>()));

    ConvertToLowerCase(text);
    RemoveTextSigns(text);

    SuffixTrie S(text);

    int choice = -1;

    while (choice != 0)
    {
        cout << "** Menu **" << endl;
        cout << "Digite 1 para a construção dos índices" << endl;
        cout << "Digite 2 para consultar uma palavra" << endl;
        cout << "Digite 3 para consultar parte do texto" << endl;
        cout << "Digite 4 para sair" << endl;
        cout << endl;

        cin >> choice;
        cout << endl;

        if (choice == 1)
        {
            cout << "Indices: " << endl;
            string aux = text;
            OneLine(aux);
            SepareWords(aux);
            cout << showIndex(aux, S);
            cout << "\n\n";
        }
        else if (choice == 2)
        {
            string word;

            cout << "Digite a palavra que deseja pesquisar: ";
            cin >> word;

            string result = S.search(word);
            if (result != "")
            {
                HighlightText(result, text, word.length());
            }
            cout << endl;
        }
        else if (choice == 3)
        {
        }
        else if (choice == 4)
        {
            return 0;
        }
    }

    return 0;
}