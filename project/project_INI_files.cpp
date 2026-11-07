#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <stdexcept>
#include <type_traits>

using namespace std;

class ini_exception : public runtime_error
{
public:
    using runtime_error::runtime_error;
};

class ini_parser
{
public:
    explicit ini_parser(const string &filename)
    {
        ifstream file(filename);
        if (!file.is_open())
            throw ini_exception("cannot open file: " + filename);

        string line;
        int line_number = 0;
        string current_section;

        while (getline(file, line))
        {
            ++line_number;
            string trimmed = trim(line);

            if (trimmed.empty() || trimmed[0] == ';')
                continue;

            if (trimmed[0] == '[')
            {
                auto close = trimmed.find(']');
                if (close == string::npos)
                    throw ini_exception("line " + to_string(line_number) + ": missing ']'");

                string name = trim(trimmed.substr(1, close - 1));
                if (name.empty())
                    throw ini_exception("line " + to_string(line_number) + ": empty section name");

                current_section = name;
                data[current_section];
            }
            else
            {
                auto eq = trimmed.find('=');
                if (eq == string::npos)
                    throw ini_exception("line " + to_string(line_number) + ": missing '='");

                string name = trim(trimmed.substr(0, eq));
                string value = trimmed.substr(eq + 1);

                auto comment = value.find(';');
                if (comment != string::npos)
                    value = value.substr(0, comment);
                value = trim(value);

                if (name.empty())
                    throw ini_exception("line " + to_string(line_number) + ": empty variable name");
                if (current_section.empty())
                    throw ini_exception("line " + to_string(line_number) + ": variable outside section");

                data[current_section][name] = value;
            }
        }
    }

    template <class T>
    T get_value(const string &path) const
    {
        auto dot = path.find('.');
        if (dot == string::npos)
            throw ini_exception("invalid path: " + path);

        string section = path.substr(0, dot);
        string var = path.substr(dot + 1);

        auto sec_it = data.find(section);
        if (sec_it == data.end())
            throw ini_exception("section not found: " + section);

        auto var_it = sec_it->second.find(var);
        if (var_it == sec_it->second.end())
        {
            string msg = "variable '" + var + "' not found in section '" + section + "'";
            if (!sec_it->second.empty())
            {
                msg += ". Available variables: ";
                bool first = true;
                for (const auto &pair : sec_it->second)
                {
                    if (!first)
                        msg += ", ";
                    msg += pair.first;
                    first = false;
                }
            }
            throw ini_exception(msg);
        }

        return convert<T>(var_it->second);
    }

private:
    map<string, map<string, string>> data;

    template <typename T>
    static T convert(const string &value)
    {
        if constexpr (is_same_v<T, string>)
        {
            return value;
        }
        else
        {
            istringstream ss(value);
            T result;
            ss >> result;
            if (ss.fail())
                throw ini_exception("cannot convert '" + value + "' to requested type");
            return result;
        }
    }

    static string trim(const string &s)
    {
        size_t start = s.find_first_not_of(" \t\r\n");
        if (start == string::npos)
            return "";
        size_t end = s.find_last_not_of(" \t\r\n");
        return s.substr(start, end - start + 1);
    }
};

int main()
{
    try
    {
        ini_parser parser("config.ini");

        auto i = parser.get_value<int>("Section2.var1");
        auto d = parser.get_value<double>("Section1.var1");
        auto s = parser.get_value<string>("Section1.var2");

        cout << i << '\n';
        cout << d << '\n';
        cout << s << '\n';

        parser.get_value<int>("Section1.var2");
    }
    catch (const exception &e)
    {
        cerr << "error: " << e.what() << '\n';
    }
}