string cap_string(string input);

string cap_string(string input) 
{
    string *elems = explode(input, " ");
    string output = "";

    foreach(string elem in elems)
    {
        output += capitalize(lower_case(elem)) + " ";
    }

    output = truncate(output,1);
    return output;
}