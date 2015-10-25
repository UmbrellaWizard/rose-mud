#include <lib.h>
inherit LIB_CLEAN_TIME;

int get_idle(int pos, string last_seen);
int month_calc(int month, int year);

int get_idle(int pos, string last_seen) 
{
    int days_idle, this_year, this_month, this_day, year, month, day, days, tdays, i;
    string today = clean_time(this_player()->GetProperty("timezone"));

    i = sscanf(last_seen, "%d/%d/%d", year, month, day);
    if(i != 3) return -1;

    days = day + (year*365) + month_calc(month, year);

    this_year = to_int(first(today, 4));
    this_month = to_int(last(first(today, 7), 2));
    this_day = to_int(last(first(today, 10), 2));

    tdays = this_day + (this_year*365) + month_calc(this_month, this_year);

    days_idle = tdays - days;
    return days_idle;
}

int month_calc(int month, int year)
{
    int amt = 0;

    if(month>=2) amt = 31;
    if(month>=3) 
    {
         if(year%4 == 0) amt = amt + 29;
         else amt = amt + 28;
    }
    if(month >= 4 && month <= 8) amt = (((month-3)/2)*30) + (((month-2)/2)*31) + amt;
    if(month > 8) amt = (((month-4)/2)*30) + (((month-1)/2)*31) + amt;

    return amt;
}