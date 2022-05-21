#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

// trie

const int ALPHABET_SIZE = 26;

struct TrieNode
{
    struct TrieNode *children[ALPHABET_SIZE];

    bool isEndOfWord;
};

struct TrieNode *getNode(void)
{
    struct TrieNode *pNode = new TrieNode;

    pNode->isEndOfWord = false;

    for (int i = 0; i < ALPHABET_SIZE; i++)
        pNode->children[i] = NULL;

    return pNode;
}

void insert(struct TrieNode *root, string key)
{
    struct TrieNode *pCrawl = root;

    for (int i = 0; i < key.length(); i++)
    {
        int index = key[i] - 'a';
        if (!pCrawl->children[index])
            pCrawl->children[index] = getNode();

        pCrawl = pCrawl->children[index];
    }

    pCrawl->isEndOfWord = true;
}

bool search(struct TrieNode *root, string key)
{
    struct TrieNode *pCrawl = root;

    for (int i = 0; i < key.length(); i++)
    {
        int index = key[i] - 'a';
        if (!pCrawl->children[index])
            return false;

        pCrawl = pCrawl->children[index];
    }

    return (pCrawl->isEndOfWord);
}

// trie

void ConvertToLowerCase(string &text)
{
    for (int i = 0; i < text.length(); i++)
    {
        text[i] = tolower(text[i]);
    }
}

void RemoveTextSigns(string &text)
{
    string textSigns = "#!?,.:;(-)_[]";

    for (int i = 0; i < text.length(); i++)
    {
        for (int j = 0; j < textSigns.length(); j++)
        {
            if (textSigns[j] == text[i])
            {
                text[i] = ' ';
            }
        }
    }
}

// void Replace(string &text, string el)
// {
//     int positionBefore = text.find(el) - 1;

//     text.erase(text.find(el), 2);

//     char auxAnt = text[positionBefore];

//     char elF;

//     if (el == "ã" || el == "á" || el == "â")
//     {
//         elF = 'a';
//     }
//     else if (el == "ó" || el == "ố" || el == "õ")
//     {
//         elF = 'o';
//     }
//     else if (el == "ê" || el == "é")
//     {
//         elF = 'e';
//     }
//     else if (el == "í")
//     {
//         elF = 'i';
//     }
//     else if (el == "ú")
//     {
//         elF = 'u';
//     }

//     char auxPos = text[positionBefore + 1];

//     if (auxPos)
//     {
//         text[positionBefore + 1] = elF;
//         int i = positionBefore + 2;
//         while (auxPos)
//         {

//             if (text[i])
//             {
//                 char ant = text[i];
//                 text[i] = auxPos;
//                 auxPos = text[i++];
//             }
//             else
//             {
//                 text = text + auxPos;
//                 break;
//             }
//         }
//     }
//     else
//     {
//         text = text + elF;
//     }
// }

// void RemoveWordSigns(string &text)
// {
//     const int NUMCHARACTERS = 11;
//     string charactersWithSigns[NUMCHARACTERS] = {"ã", "á", "â", "ó", "ố", "é", "õ", "í", "ê", "ú", "ç"};
//     for (int i = 0; i < NUMCHARACTERS; i++)
//     {
//         if (text.find(charactersWithSigns[i]) < text.length())
//         {
//             Replace(text, charactersWithSigns[i]);
//         }
//     }
// }

string ForcaBruta(string T, int n, string P, int m)
{
    int i, j, k;
    string positionC = "";
    for (int i = 1; i <= (n); i++)
    {
        k = i;
        j = 1;
        while (T[k - 1] == P[j - 1] && j <= m)
        {
            j++;
            k++;
        }
        if (j > m)
        {
            positionC += to_string(i - 1) + ",";
        }
    }
    if (!(positionC == ""))
    {
        positionC.pop_back();
    }
    return positionC;
}

string SeparateIntoUniqueWords(string text)
{
    int i = 0, j = 0;
    string words = "";
    string aux = "";

    while (i < text.length())
    {
        while (text[j] != ' ' && text[j] != '\n' && j < text.length())
        {
            aux += text[j];
            j++;
        }

        if ((aux != "" || words != ""))
        {
            if ((ForcaBruta(words, words.length(), aux, aux.length()) == ""))
            {
                words += aux + ",";
            }
        }
        aux = "";

        i = j++;
    }
    words.pop_back();

    return words;
}
int CountWords(string words)
{
    int count = 0;
    for (int i = 0; i < words.length(); i++)
    {
        if (words[i] == ',')
        {
            count++;
        }
    }
    return count;
}

void MakeInd(string words, string text)
{
    string aux = "";
    string aux2 = "";
    for (int i = 0; i < words.length(); i++)
    {
        if (words[i] == ',')
        {
            aux2 += aux + " " + ForcaBruta(text, text.length(), aux, aux.length()) + "\n";
            i++;
            aux = "";
        }
        aux += words[i];
    }
    cout << aux2 << endl;
}

int main()
{

    string text = "Rato,Bicicleta,carro.\nCasa!Bico,rato;Carro?\nCarro:bicicleta.";

    ConvertToLowerCase(text);
    RemoveTextSigns(text);
    // RemoveWordSigns(text);

    string words = SeparateIntoUniqueWords(text);
    MakeInd(words, text);

    int numWords = CountWords(words);
    string aux = "";
    string keys[numWords];
    int j = 0;
    for (int i = 0; i < words.length(); i++)
    {
        if (words[i] == ',')
        {
            keys[j] = aux;
            j++;
            i++;
            aux = "";
        }
        aux += words[i];
    }
    // Input keys (use only 'a' through 'z'
    //     // and lower case)
    //     string keys[] = {"the", "a", "there",
    //                      "answer", "any", "by",
    //                      "bye", "their"};

    struct TrieNode *root = getNode();

    //     // Construct trie
    for (int i = 0; i < numWords; i++)
    {
        insert(root, keys[i]);
    }

    //     // Search for different keys
        search(root, "rat") ? cout << "Yes\n" : cout << "No\n";
    //     search(root, "these") ? cout << "Yes\n" : cout << "No\n";
    //     search(root, "their") ? cout << "Yes\n" : cout << "No\n";
    //     search(root, "thaw") ? cout << "Yes\n" : cout << "No\n";
    //     return 0;
    return 0;
}