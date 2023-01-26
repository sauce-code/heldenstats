#ifndef _DATUM_HPP_
#define _DATUM_HPP_
const int Monate[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

class Datum
{
private:
	int t, m, j;
	int Daysto0;
public :
	Datum(int tt, int mm, int jj);
	Datum(){t=0; m=0; j=0; Daysto0 = 0;}
	void SetDate(int tt, int mm, int jj){t=tt; m=mm; j=jj; CalcDaysto0();}
	void SetToNull(){t=0; m=0; j=0;Daysto0=0;}
	bool IsNull(){return t == 0 && m == 0 && j == 0;}
	int DaysToNull();
	int operator-(Datum &datum);
	int CalcDaysto0();
	~Datum(){}
};

class Zeit
{
private:
	int h, m, s;
	int Sekunden;
public :
	Zeit(int hh, int mm, int ss);
	Zeit(){h=0; m=0; s=0;}
	~Zeit(){}
	int Seconds();
	int operator-(Zeit &zeit);
	bool IsNull(){return h == 0 && m == 0 && s == 0;}
	void AddHours(int Hours);
	void SetToNull(){h=0; m=0; s=0;Sekunden=0;}
	void SetTime(int hh, int mm, int ss){h=hh; m=mm; s=ss; CalcSekunden();}
	void SetHour(int hh){h=hh;CalcSekunden();}
	void SetMinute(int mm){m=mm;CalcSekunden();}
	void SetSecond(int ss){s=ss;CalcSekunden();}
	int CalcSekunden();
};
#endif
