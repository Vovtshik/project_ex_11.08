// Modification of the project_ex_11.06, program
// so that it replaces the abbreviations don't with do not words, 
// can't - cannot, etc .; Do not touch hyphens inside words; 
// convert all characters to lowercase.


#include "../std_lib_facilities.h"

string tolower(const string& s);                             // The function converts all characters of the string to lowercase.
string replaces_abbreviations_with_words(const string& str); // The function replaces abbreviations with words.
string Punctuation_for_spaces(const string& str);            // The function replaces punctuation marks (.,;? - ') 
                                                             //  with spaces (does not change characters between pairs
                                                             //  of double quotes (")).
                                                   
int main()
{
    string str = " - don't use the \"as-if\" rule. \n - don't use the as-if rule. \n I don't know it; \n He doesn't speak English, \n I won't see it - \n I didn't see it: \n You haven't known it. \n \"She hasn't called you.\" \n";
    cout << "Original line: \n" << str << '\n';
    cout << "Changed line (punctuation characters replaced by spaces): \n"
        << Punctuation_for_spaces(str) << '\n';
    cout << "Changed string (all letters are lowercase): \n"
        << tolower(str) << '\n';
    cout << "Changed line (abbreviations replaced by full words): \n"
        << replaces_abbreviations_with_words(str) << '\n';
    cout << "A line to which all three changes apply: \n"
        << replaces_abbreviations_with_words(tolower(Punctuation_for_spaces(str))) << '\n';
    return 0;
}

string tolower(const string& s)
{
    string temp{s};
    for(char& x : temp)
    {
        x = tolower(x);
    }
    return temp;
}

string Punctuation_for_spaces(const string& str)
{
    string temp;
    char ch_t;
    bool flag = false;
    stringstream ss(str);
    for(char ch; ss.get(ch);)
    {
        ch_t = ch;
        if(ch == '"')
        {
            flag = flag?false : true;
            temp = temp + '"';
        }
        else if(flag)
            temp = temp + ch;
        else if(!flag)
        {
            if(ch == '.' || ch == ';' || ch == ':' || ch == ',' || ch == '?')
                temp = temp + ' ';
            else if(ch == '-')
                {
                    if(ch_t != ' ' && ss.peek() != ' ')
                        temp += '-';
                    else
                        temp += ' ';
                }
            else
                temp = temp + ch;
        }  
    }
    return temp;
}

string replaces_abbreviations_with_words(const string& str)
{
    string rez = "";
    stringstream ss(str);
    for(string temp; ss >> temp;)
    {
        if(temp == "don't")
            rez = rez + " do not";
        else if(temp == "doesn't")
            rez += " does not";
        else if(temp == "haven't")
            rez += " have not";
        else if(temp == "hasn't")
            rez += " has not";
        else if(temp == "won't")
            rez += " will not";
        else if(temp == "didn't")
            rez += " did not";
        else
            rez = rez + ' ' + temp;
    }
    return rez + '\n';
}