/*    /lib/clean_time.c
 *    Returns a human readable friendly timestamp string;
 *    Created by Umbrella Wizard 07/03/15
 */

string clean_time(string tz);

string clean_time(string tz)
{
    string date, min_sec, offset_time, foo;
    int hour;

    if(!tz || tz == "") foo = timestamp();
    else foo = timestamp(tz);
    sscanf(foo,"%s-%d.%s", date, hour, min_sec);
    date = replace_string(date, ".", "/", 0);
    hour += 6;
    min_sec = replace_string(min_sec, ".", ":", 1);
    min_sec = replace_string(min_sec, ",", ":", 1);
    
    if(hour>23) hour -= 23;
    if(hour>10 && hour<23) 
    {
        hour -= 11;
        if(hour==0) hour = 12;
        offset_time = hour + ":" + min_sec + " PM";
    }
    else 
    {
        if(hour==23) hour = 12;
        offset_time = hour + ":" + min_sec + " AM";
    }
    return date + " " + sprintf("%'0'11s", offset_time);
}