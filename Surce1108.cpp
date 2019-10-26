// Modification of the project_ex_11.06, program
// so that it replaces the abbreviations don't with do not words, 
// can't - cannot, etc .; Do not touch hyphens inside words; 
// convert all characters to lowercase.


#include "../std_lib_facilities.h"

void in_file_text(string& name_file, vector<string>& data);
void add_words_to_dict(vector<string>& dict, string& str);   // The function creates a dictionary from the words that make up the text of a multiline file.
string tolower(const string& s);                             // The function converts all characters of the string to lowercase.
string replaces_abbreviations_with_words(const string& str); // The function replaces abbreviations with words.
string Punctuation_for_spaces(const string& str);            // The function replaces punctuation marks (.,;? - ') 
                                                             //  with spaces (does not change characters between pairs
                                                             //  of double quotes (")).
                                                   
int main()
{
    string name_file;
    vector<string> data;
    cout << "Enter the name of the text file \n"
        << "for reading and compiling a dictionary from the words of this text:\n";
    cin >> name_file;
    in_file_text(name_file, data);
    vector<string> dictionary;
    for(string s: data)
    {
        add_words_to_dict(dictionary, s);
    }
    sort(dictionary.begin(), dictionary.end());
    for(string s: dictionary)
    {
        cout << s << '\n';
    }
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
        if(ch == '.' || ch == ';' || ch == ':' || ch == ',' || ch == '?' || ch == '"' || ch == '-')
            temp += ' ';
        else
            temp = temp + ch;
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

void add_words_to_dict(vector<string>& dict, string& str)
{
    vector<string> v_temp;
    istringstream is(replaces_abbreviations_with_words(tolower(Punctuation_for_spaces(str))));
    for(string s; is >> s;)
    {
        v_temp.push_back(s);
    }   
    sort(v_temp.begin(), v_temp.end());
    for(int i = 0; i < v_temp.size(); ++i)
    {
        bool flag = false;
        if(i == 0 || v_temp[i] != v_temp[i-1])
            {
                for(string s: dict)
                {
                    if(s == v_temp[i])
                        {
                            flag = true;
                            break;
                        }       
                }
                if(!flag)
                    dict.push_back(v_temp[i]);
                flag = false;
            }
    }
}

void in_file_text(string& name_file, vector<string>& data)
{
    ifstream ist(name_file);
    if(!ist) error("Unable to open input file ", name_file);
    ist.exceptions(ist.exceptions() | ios_base::badbit);
    string temp_str;
    for(string temp_str; getline(ist, temp_str);)
    {
        data.push_back(temp_str);
    }
}