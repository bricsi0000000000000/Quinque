#include "pch.h"
#include <iostream>
#include <Windows.h>
#include <cstdlib>
#include <string>
#define SZELESSEG 11
#define MAGASSAG 7

using namespace std;

#pragma region SZINEK
HANDLE szinezes = GetStdHandle(STD_OUTPUT_HANDLE);
int sotetKek = 1;
int sotetZold = 2;
int sotetCyan = 3;
int sotetPiros = 4;
int sotetRozsaszin = 5;
int sotetSarga = 6;
int sotetFeher = 7;
int szurke = 8;
int kek = 9;
int zold = 10;
int cyan = 11;
int piros = 12;
int rozsaszin = 13;
int sarga = 14;
int feher = 15;
#pragma endregion

enum Iranyok { BAL, FEL, JOBB, LE };

#pragma region fuggvenyek
void PalyaRajzol();
void UresHelyekUjElem(int sorszam, int x, int y);
void MozgatHelyekUjElem(int x, int y);
void LancElemekUjElem(int x, int y);
bool SorszamVizsgal(string sorszam);
bool AbcdVizsgal(string sorszam, string abcd);
void UresHelyVizsgal(int x, int y);
void UresHelyekKeres();
void MozgatKeres(int sorszam);
void Mozgat(Iranyok irany);
int SzamotCsinal(string atalakitandoSzam);
bool MozgatHelyekVizsgalAtloban(int x, int y);
void LancCsinal();
void JatekVegeVizsgal();
void JatekVegeVizszintesVizsgal(int melyikJatekos);
void JatekVegeFuggolegesVizsgal(int melyikJatekos);
void JatekVegeAtloVizsgal(int melyikJatekos);
void UjJatek();
void JatekMehet();
void JatekosCsere();
#pragma endregion

int melyikJatekos = 1;
bool elsoKor = true;
int akcio = 1;
int lapkakSzama = 5;
int elsoJatekosErnyokDb = 18;
int masodikJatekosErnyokDb = 18;
bool passz = false;

#pragma region sorszamok
struct sorszamElem {
	bool a = false;
	bool b = false;
	bool c = false;
	bool d = false;
	int aMelyik;
	int bMelyik;
	int cMelyik;
	int dMelyik;
	int xKoordinata;
	int yKoordinata;
	int sorszam;
};

int sorszamokHossz = 0;
sorszamElem* sorszamok = new sorszamElem[sorszamokHossz];
int sorszamokIndex = 0;
int ujSorszamIndex = 1;
#pragma endregion

struct hely {
	int xKoordinata;
	int yKoordinata;
	int sorszam;
};

#pragma region uresHelyek
int uresHelyekHossz = 0;
hely* uresHelyek = new hely[uresHelyekHossz];
int uresHelyekIndex = 0;
int uresSorszamIndex = 65;
#pragma endregion

#pragma region mozgatHelyek
int mozgatHelyekHossz = 0;
hely* mozgatHelyek = new hely[mozgatHelyekHossz];
int mozgatHelyekIndex = 0;
#pragma endregion

#pragma region lancElemek
int lancElemekHossz = 0;
hely * lancElemek = new hely[lancElemekHossz];
int lancElemIndex = 0;
int lancElemSorszam = 0;
#pragma endregion

bool mozgat = false;
int mozgatHonnanSorszam;
int mozgatHonnanX;
int mozgatHonnanY;

int aktualisKorbenRakottSorszam = 0;

#pragma region karakterek
char vizszintes = (char)196;
char fuggoleges = (char)179;
char balFelsoSarok = (char)218;
char balAlsoSarok = (char)192;
char jobbFelsoSarok = (char)191;
char jobbAlsoSarok = (char)217;
char kereszt = (char)197;
char forditottT = (char)193;
char simaT = (char)194;
char jobbraT = (char)180;
char balraT = (char)195;
char also = (char)220;
char felso = (char)223;
char egesz = (char)219;
#pragma endregion

bool jatekVegeElsoJatekos = false;
bool jatekVegeMasodikJatekos = false;
bool jatekVege = false;
bool jatekTotalisVege = false;

int main()
{
	do {
		SetConsoleTextAttribute(szinezes, feher);

		JatekMehet();

		while (!jatekVege)
		{
			if (lapkakSzama <= 0) {
				uresHelyekHossz = 0;
				hely * ujUresHelyek = new hely[uresHelyekHossz];
				delete[] uresHelyek;
				uresHelyek = ujUresHelyek;
			}

			PalyaRajzol();
			JatekVegeVizsgal();
			if (!jatekVege) {
				string betu_sorszam_abcd = "";
				string eleje = ""; //sorszam vagy betu
				string vege = ""; //abcd

				do {
					SetConsoleTextAttribute(szinezes, szurke);
					betu_sorszam_abcd = "";
					eleje = "";
					vege = "";
					if (elsoKor) {
						cout << endl << "\tBetu majd szokozzel | 'a' | 'b' | 'c' | 'd' | pl.:(A b): ";
					}
					else {
						if (akcio == 1) {
							cout << endl << "\tBetu vagy sorszam majd szokozzel | 'a' | 'b' | 'c' | 'd' | pl.:(A b) vagy (1 d): ";
						}
						else if (akcio == 2) {
							if (!mozgat) {
								cout << endl << "\tMozgatni kivant sorszam: ";
							}
							else {
								cout << endl << "\tHova szeretned mozgatni: ";
							}
						}
					}
					while (betu_sorszam_abcd == "") {
						getline(cin, betu_sorszam_abcd);
					}

					bool elejeB = true;

					for (int i = 0; i < betu_sorszam_abcd.length(); i++)
					{
						if (betu_sorszam_abcd[i] == ' ') {
							elejeB = false;
							i++;
						}
						if (elejeB) {
							eleje += betu_sorszam_abcd[i];
						}
						else {
							vege += betu_sorszam_abcd[i];
						}
					}

					if (!elsoKor) {
						if (betu_sorszam_abcd == "a") {
							Mozgat(Iranyok::BAL);
						}
						else if (betu_sorszam_abcd == "w") {
							Mozgat(Iranyok::FEL);
						}
						else if (betu_sorszam_abcd == "d") {
							Mozgat(Iranyok::JOBB);
						}
						else if (betu_sorszam_abcd == "s") {
							Mozgat(Iranyok::LE);
						}
					}

				} while (SorszamVizsgal(eleje) || (AbcdVizsgal(eleje, vege) && akcio == 1));

				if (akcio == 1) {
					if (elsoJatekosErnyokDb > 0 || masodikJatekosErnyokDb > 0) {
						if ((int)eleje[0] >= 65 && (int)eleje[0] <= 90) {
							sorszamElem * ujSorszamok = new sorszamElem[sorszamokHossz + 1];
							for (int i = 0; i < sorszamokHossz; i++)
							{
								ujSorszamok[i].sorszam = sorszamok[i].sorszam;
								ujSorszamok[i].xKoordinata = sorszamok[i].xKoordinata;
								ujSorszamok[i].yKoordinata = sorszamok[i].yKoordinata;

								ujSorszamok[i].a = sorszamok[i].a;
								ujSorszamok[i].b = sorszamok[i].b;
								ujSorszamok[i].c = sorszamok[i].c;
								ujSorszamok[i].d = sorszamok[i].d;

								ujSorszamok[i].aMelyik = sorszamok[i].aMelyik;
								ujSorszamok[i].bMelyik = sorszamok[i].bMelyik;
								ujSorszamok[i].cMelyik = sorszamok[i].cMelyik;
								ujSorszamok[i].dMelyik = sorszamok[i].dMelyik;
							}
							sorszamokHossz++;

							ujSorszamok[sorszamokIndex].sorszam = ujSorszamIndex;
							aktualisKorbenRakottSorszam = ujSorszamIndex;

							if (vege == "a") {
								ujSorszamok[sorszamokIndex].a = true;
								ujSorszamok[sorszamokIndex].aMelyik = melyikJatekos;
							}
							else if (vege == "b") {
								ujSorszamok[sorszamokIndex].b = true;
								ujSorszamok[sorszamokIndex].bMelyik = melyikJatekos;
							}
							else if (vege == "c") {
								ujSorszamok[sorszamokIndex].c = true;
								ujSorszamok[sorszamokIndex].cMelyik = melyikJatekos;
							}
							else if (vege == "d") {
								ujSorszamok[sorszamokIndex].d = true;
								ujSorszamok[sorszamokIndex].dMelyik = melyikJatekos;
							}

							for (int j = 0; j < uresHelyekHossz; j++)
							{
								if (SzamotCsinal(eleje) == uresHelyek[j].sorszam) {
									ujSorszamok[sorszamokIndex].xKoordinata = uresHelyek[j].xKoordinata;
									ujSorszamok[sorszamokIndex].yKoordinata = uresHelyek[j].yKoordinata;
								}
							}

							delete[] sorszamok;
							sorszamok = ujSorszamok;

							sorszamokIndex++;
							ujSorszamIndex++;

							lapkakSzama--;
						}
						else if ((int)eleje[0] >= 48 && (int)eleje[0] <= 57) {
							aktualisKorbenRakottSorszam = SzamotCsinal(eleje);

							for (int i = 0; i < sorszamokHossz; i++)
							{
								if (SzamotCsinal(eleje) == sorszamok[i].sorszam) {
									if (vege == "a") {
										sorszamok[i].a = true;
										sorszamok[i].aMelyik = melyikJatekos;
									}
									else if (vege == "b") {
										sorszamok[i].b = true;
										sorszamok[i].bMelyik = melyikJatekos;
									}
									else if (vege == "c") {
										sorszamok[i].c = true;
										sorszamok[i].cMelyik = melyikJatekos;
									}
									else if (vege == "d") {
										sorszamok[i].d = true;
										sorszamok[i].dMelyik = melyikJatekos;
									}
								}
							}
						}

						if (melyikJatekos == 1) {
							elsoJatekosErnyokDb--;
						}
						else if (melyikJatekos == 2) {
							masodikJatekosErnyokDb--;
						}

						if (!elsoKor) {
							akcio = 2;
							mozgat = false;
						}
					}
				}
				else if (akcio == 2) {
					if (eleje != "p") {
						if (mozgat) {
							//csere
							for (int i = 0; i < sorszamokHossz; i++)
							{
								if (mozgatHonnanSorszam == sorszamok[i].sorszam) {
									for (int j = 0; j < mozgatHelyekHossz; j++)
									{
										if (SzamotCsinal(eleje) == mozgatHelyek[j].sorszam) {
											sorszamok[i].xKoordinata = mozgatHelyek[j].xKoordinata;
											sorszamok[i].yKoordinata = mozgatHelyek[j].yKoordinata;
										}
									}
								}
							}

							mozgatHelyekHossz = 0;
							hely * ujmozgatHelyek = new hely[mozgatHelyekHossz];
							delete[] mozgatHelyek;
							mozgatHelyek = ujmozgatHelyek;

							akcio = 1;
							mozgat = false;

							JatekosCsere();

							UresHelyekKeres();
						}
						mozgat = true;
					}
					else if (eleje == "p") {
						mozgatHelyekHossz = 0;
						hely * ujmozgatHelyek = new hely[mozgatHelyekHossz];
						delete[] mozgatHelyek;
						mozgatHelyek = ujmozgatHelyek;

						akcio = 1;
						mozgat = false;

						JatekosCsere();

						UresHelyekKeres();
					}
				}

				if (elsoKor) {
					UresHelyekKeres();

					JatekosCsere();
					elsoKor = false;
				}
			}
		}

		PalyaRajzol();

		SetConsoleTextAttribute(szinezes, feher);
		cout << "\n\tNYERTES: ";
		if (jatekVegeElsoJatekos) {
			SetConsoleTextAttribute(szinezes, cyan);
			cout << "ELSO JATEKOS";
		}
		else if (jatekVegeMasodikJatekos) {
			SetConsoleTextAttribute(szinezes, rozsaszin);
			cout << "MASODIK JATEKOS";
		}
		else if (!jatekVegeElsoJatekos && !jatekVegeMasodikJatekos) {
			SetConsoleTextAttribute(szinezes, sarga);
			cout << "DONTETLEN";
		}

		SetConsoleTextAttribute(szinezes, sarga);
		cout << endl << "\n\tSzeretned ujrakezdeni? i/n ";

		char beker;
		cin >> beker;
		if (beker == 'i') {
			UjJatek();
		}
		else if ('n') {
			jatekTotalisVege = true;
		}
	} while (!jatekTotalisVege);
}

int SzamotCsinal(string atalakitandoSzam) {
	int szam = 0;
	if ((int)atalakitandoSzam[0] >= 48 && (int)atalakitandoSzam[0] <= 57) {
		if (atalakitandoSzam.length() == 2) {
			szam += 10 * ((int)atalakitandoSzam[0] - 48);
			szam += (int)atalakitandoSzam[1] - 48;
		}
		else if (atalakitandoSzam.length() == 1) {
			szam += (int)atalakitandoSzam[0] - 48;
		}
	}
	else if ((int)atalakitandoSzam[0] >= 65 && (int)atalakitandoSzam[0] <= 90) {
		szam = (int)atalakitandoSzam[0];
	}
	return szam;
}

void Mozgat(Iranyok irany) {
	switch (irany)
	{
	case BAL:
		for (int i = 0; i < sorszamokHossz; i++)
		{
			sorszamok[i].yKoordinata--;
		}
		for (int i = 0; i < mozgatHelyekHossz; i++)
		{
			mozgatHelyek[i].yKoordinata--;
		}
		break;
	case FEL:
		for (int i = 0; i < sorszamokHossz; i++)
		{
			sorszamok[i].xKoordinata--;
		}
		for (int i = 0; i < mozgatHelyekHossz; i++)
		{
			mozgatHelyek[i].xKoordinata--;
		}
		break;
	case JOBB:
		for (int i = 0; i < sorszamokHossz; i++)
		{
			sorszamok[i].yKoordinata++;
		}
		for (int i = 0; i < mozgatHelyekHossz; i++)
		{
			mozgatHelyek[i].yKoordinata++;
		}
		break;
	case LE:
		for (int i = 0; i < sorszamokHossz; i++)
		{
			sorszamok[i].xKoordinata++;
		}
		for (int i = 0; i < mozgatHelyekHossz; i++)
		{
			mozgatHelyek[i].xKoordinata++;
		}
		break;
	}

	UresHelyekKeres();
	PalyaRajzol();
}

void PalyaRajzol() {
	system("cls");
	SetConsoleTextAttribute(szinezes, sarga);

	cout << endl;

	cout << "\t\t   " << also << felso << felso << felso << felso << also;
	for (int i = 0; i < 6; i++)
	{
		cout << " ";
	}
	cout << felso;

	cout << "\n\t\t   " << egesz << " " << " " << " " << " " << egesz << " " << egesz << " " << " " << egesz << " " << egesz << " " << egesz << felso
		<< felso << also << " " << also << felso << felso << egesz << " " << egesz << " " << " " << egesz << " " << also << egesz << egesz << egesz;

	cout << "\n\t\t   " << felso << also << also << egesz << also << felso << " " << felso << also << also << egesz << " " << egesz << " " << egesz << " "
		<< " " << egesz << " " << felso << also << also << egesz << " " << felso << also << also << egesz << " " << felso << also << also << also;

	cout << "\n\t\t   " << " " << " " << " " << " " << felso << felso;
	for (int i = 0; i < 16; i++)
	{
		cout << " ";
	}
	cout << egesz;

	cout << endl;

	int sorszamIndex = 1;
	bool abIndex = false;
	bool cdIndex = false;
	int sorIndex = 0;
	int oszlopIndex = 0;

	int rakasSorIndex = 2;
	int rakasAbSorIndex = 1;
	int rakasCdSorIndex = 3;
	int abcdSorIndex = -1;
	int abcdSorRakIndex = 0;

	int rakasOszlopIndex = 2;
	int rakasOszlopSzunetIndex = 2;
	int rakasOszlopAbIndex = 1;
	bool oszlopAbValt = false;
	int rakasOszlopCdIndex = 1;
	bool oszlopCdValt = false;
	int oszlopAbcdIndex = 0;
	int abcdOszlopIndex = -1;

	for (int sor = 0; sor < MAGASSAG * 4 + 1; sor++)
	{
		oszlopIndex = 0;
		rakasOszlopIndex = 2;
		rakasOszlopSzunetIndex = 2;
		rakasOszlopAbIndex = 1;
		oszlopAbValt = false;
		rakasOszlopCdIndex = 1;
		oszlopCdValt = false;
		oszlopAbcdIndex = 0;
		abcdOszlopIndex = -1;
		bool volt = false;
		bool nagy = false;

		cout << "\t";

		for (int oszlop = 0; oszlop < SZELESSEG * 5 + 1; oszlop++)
		{
			if (sor % 4 == 0) {
				SetConsoleTextAttribute(szinezes, sotetFeher);
				if (sor == 0 && oszlop == 0) {
					cout << balFelsoSarok;
				}
				else if (sor == 0 && oszlop == SZELESSEG * 5) {
					cout << jobbFelsoSarok;
				}
				else if (sor == MAGASSAG * 4 && oszlop == 0) {
					cout << balAlsoSarok;
				}
				else if (sor == MAGASSAG * 4 && oszlop == SZELESSEG * 5) {
					cout << jobbAlsoSarok;
				}
				else if (sor % 4 == 0 && oszlop == 0) {
					cout << balraT;
				}
				else if (sor % 4 == 0 && oszlop == SZELESSEG * 5) {
					cout << jobbraT;
				}
				else if (sor == 0 && oszlop % 5 == 0) {
					cout << simaT;
				}
				else if (sor == MAGASSAG * 4 && oszlop % 5 == 0) {
					cout << forditottT;
				}
				else if (sor % 4 == 0 && oszlop % 5 == 0) {
					cout << kereszt;
				}
				else {
					cout << vizszintes;
				}
				SetConsoleTextAttribute(szinezes, szurke);
			}
			else if (oszlop % 5 == 0) {
				SetConsoleTextAttribute(szinezes, sotetFeher);

				cout << fuggoleges;
				nagy = false;

				SetConsoleTextAttribute(szinezes, szurke);
			}
			else if (sor == rakasSorIndex) {
				if (oszlop == rakasOszlopIndex) {
					volt = false;
					nagy = false;

					for (int i = 0; i < sorszamokHossz; i++)
					{
						if (!volt) {
							if (sorIndex == sorszamok[i].xKoordinata && oszlopIndex == sorszamok[i].yKoordinata) {
								SetConsoleTextAttribute(szinezes, sarga);
								if (sorszamok[i].sorszam >= 10) {
									cout << sorszamok[i].sorszam << " ";
									nagy = true;
								}
								else {
									cout << sorszamok[i].sorszam;
								}
								volt = true;
								SetConsoleTextAttribute(szinezes, szurke);
							}
						}
					}
					if (akcio == 1) {
						for (int i = 0; i < uresHelyekHossz; i++)
						{
							if (!volt) {
								if (sorIndex == uresHelyek[i].xKoordinata && oszlopIndex == uresHelyek[i].yKoordinata) {
									SetConsoleTextAttribute(szinezes, piros);
									cout << (char)uresHelyek[i].sorszam;
									SetConsoleTextAttribute(szinezes, szurke);
									volt = true;
								}
							}
						}
					}
					else if (akcio == 2) {
						for (int i = 0; i < mozgatHelyekHossz; i++)
						{
							if (!volt) {
								if (sorIndex == mozgatHelyek[i].xKoordinata && oszlopIndex == mozgatHelyek[i].yKoordinata) {
									SetConsoleTextAttribute(szinezes, zold);
									cout << (char)mozgatHelyek[i].sorszam;
									SetConsoleTextAttribute(szinezes, szurke);
									volt = true;
								}
							}
						}
					}

					if (!volt) {
						if (!nagy) {
							cout << " ";
						}
					}
					oszlopIndex++;
				}
				else if (oszlop == rakasOszlopSzunetIndex) {
					if (!nagy) {
						cout << " ";
					}
				}
				else {
					if (!nagy) {
						cout << " ";
					}
				}
			}
			else if (sor == rakasAbSorIndex) {
				if (oszlop == rakasOszlopAbIndex) {
					bool rakott = false;
					for (int i = 0; i < sorszamokHossz; i++)
					{
						if (abcdSorIndex == sorszamok[i].xKoordinata && abcdOszlopIndex == sorszamok[i].yKoordinata) {
							if (!abIndex) {
								if (sorszamok[i].a) {
									if (sorszamok[i].aMelyik == 1) {
										SetConsoleTextAttribute(szinezes, cyan);
										cout << "X";
										SetConsoleTextAttribute(szinezes, szurke);
										rakott = true;
									}
									else if (sorszamok[i].aMelyik == 2) {
										SetConsoleTextAttribute(szinezes, rozsaszin);
										cout << "O";
										SetConsoleTextAttribute(szinezes, szurke);
										rakott = true;
									}
								}
								else {
									cout << "a";
									rakott = true;
								}
							}
							else {
								if (sorszamok[i].b) {
									if (sorszamok[i].bMelyik == 1) {
										SetConsoleTextAttribute(szinezes, cyan);
										cout << "X";
										SetConsoleTextAttribute(szinezes, szurke);
										rakott = true;
									}
									else if (sorszamok[i].bMelyik == 2) {
										SetConsoleTextAttribute(szinezes, rozsaszin);
										cout << "O";
										SetConsoleTextAttribute(szinezes, szurke);
										rakott = true;
									}
								}
								else {
									cout << "b";
									rakott = true;
								}
							}

						}
					}
					if (!rakott) {
						if (akcio == 1) {
							for (int i = 0; i < uresHelyekHossz; i++)
							{
								if (abcdSorIndex == uresHelyek[i].xKoordinata && abcdOszlopIndex == uresHelyek[i].yKoordinata) {
									if (!abIndex) {
										SetConsoleTextAttribute(szinezes, sotetPiros);
										cout << "a";
										SetConsoleTextAttribute(szinezes, szurke);
										rakott = true;
									}
									else {
										SetConsoleTextAttribute(szinezes, sotetPiros);
										cout << "b";
										rakott = true;
										SetConsoleTextAttribute(szinezes, szurke);
									}
								}
							}
						}
						else if (akcio == 2) {
							for (int i = 0; i < mozgatHelyekHossz; i++)
							{
								if (abcdSorIndex == mozgatHelyek[i].xKoordinata && abcdOszlopIndex == mozgatHelyek[i].yKoordinata) {
									if (!abIndex) {
										SetConsoleTextAttribute(szinezes, sotetZold);
										cout << " ";
										SetConsoleTextAttribute(szinezes, szurke);
										rakott = true;
									}
									else {
										SetConsoleTextAttribute(szinezes, sotetZold);
										cout << " ";
										SetConsoleTextAttribute(szinezes, szurke);
										rakott = true;
									}
								}
							}
						}
					}

					if (!rakott) {
						cout << " ";
					}

					abIndex = !abIndex;
				}
				else {
					cout << " ";
				}
			}
			else if (sor == rakasCdSorIndex) {
				if (oszlop == rakasOszlopCdIndex) {
					bool rakott = false;
					for (int i = 0; i < sorszamokHossz; i++)
					{
						if (abcdSorIndex == sorszamok[i].xKoordinata && abcdOszlopIndex == sorszamok[i].yKoordinata) {
							if (!cdIndex) {
								if (sorszamok[i].c) {
									if (sorszamok[i].cMelyik == 1) {
										SetConsoleTextAttribute(szinezes, cyan);
										cout << "X";
										SetConsoleTextAttribute(szinezes, szurke);
										rakott = true;
									}
									else if (sorszamok[i].cMelyik == 2) {
										SetConsoleTextAttribute(szinezes, rozsaszin);
										cout << "O";
										SetConsoleTextAttribute(szinezes, szurke);
										rakott = true;
									}
								}
								else {
									cout << "c";
									rakott = true;
								}
							}
							else {
								if (sorszamok[i].d) {
									if (sorszamok[i].dMelyik == 1) {
										SetConsoleTextAttribute(szinezes, cyan);
										cout << "X";
										SetConsoleTextAttribute(szinezes, szurke);
										rakott = true;
									}
									else if (sorszamok[i].dMelyik == 2) {
										SetConsoleTextAttribute(szinezes, rozsaszin);
										cout << "O";
										SetConsoleTextAttribute(szinezes, szurke);
										rakott = true;
									}
								}
								else {
									cout << "d";
									rakott = true;
								}
							}
						}
					}
					if (!rakott) {
						if (akcio == 1) {
							for (int i = 0; i < uresHelyekHossz; i++)
							{
								if (abcdSorIndex == uresHelyek[i].xKoordinata && abcdOszlopIndex == uresHelyek[i].yKoordinata) {
									if (!cdIndex) {
										SetConsoleTextAttribute(szinezes, sotetPiros);
										cout << "c";
										SetConsoleTextAttribute(szinezes, szurke);
										rakott = true;
									}
									else {
										SetConsoleTextAttribute(szinezes, sotetPiros);
										cout << "d";
										SetConsoleTextAttribute(szinezes, szurke);
										rakott = true;
									}
								}
							}
						}
						else if (akcio == 2) {
							for (int i = 0; i < mozgatHelyekHossz; i++)
							{
								if (abcdSorIndex == mozgatHelyek[i].xKoordinata && abcdOszlopIndex == mozgatHelyek[i].yKoordinata) {
									if (!cdIndex) {
										SetConsoleTextAttribute(szinezes, sotetZold);
										cout << " ";
										SetConsoleTextAttribute(szinezes, szurke);
										rakott = true;
									}
									else {
										SetConsoleTextAttribute(szinezes, sotetZold);
										cout << " ";
										SetConsoleTextAttribute(szinezes, szurke);
										rakott = true;
									}
								}
							}
						}
					}

					if (!rakott) {
						cout << " ";
					}

					cdIndex = !cdIndex;
				}
				else {
					cout << " ";
				}
			}
			else {
				cout << " ";
			}

			if (oszlop == 2 || oszlop == rakasOszlopIndex) {
				rakasOszlopIndex += 5;
			}
			if (oszlop == 1 || oszlop == rakasOszlopSzunetIndex) {
				rakasOszlopSzunetIndex += 5;
			}

			if (oszlop == rakasOszlopAbIndex) {
				if (!oszlopAbValt) {
					rakasOszlopAbIndex += 3;
				}
				else {
					rakasOszlopAbIndex += 2;
				}
				oszlopAbValt = !oszlopAbValt;

			}
			if (oszlop == rakasOszlopCdIndex) {
				if (!oszlopCdValt) {
					rakasOszlopCdIndex += 3;
				}
				else {
					rakasOszlopCdIndex += 2;
				}
				oszlopCdValt = !oszlopCdValt;
			}
			if (oszlop == oszlopAbcdIndex) {
				oszlopAbcdIndex += 5;
				abcdOszlopIndex++;
			}
		}

		if (sor == rakasSorIndex) {
			rakasSorIndex += 4;
			sorIndex++;
		}
		if (sor == 1 || sor == rakasAbSorIndex) {
			rakasAbSorIndex += 4;
		}
		if (sor == 3 || sor == rakasCdSorIndex) {
			rakasCdSorIndex += 4;
		}
		if (sor == abcdSorRakIndex) {
			abcdSorRakIndex += 4;
			abcdSorIndex++;
		}

		if (sor == 10) {
			cout << "\tLapkak szama: " << lapkakSzama;
		}
		if (sor == 11) {
			cout << "\tElso jatekos ernyoi: " << elsoJatekosErnyokDb;
		}
		if (sor == 12) {
			cout << "\tMasodik jatekos ernyoi: " << masodikJatekosErnyokDb;
		}

		cout << endl;
	}

	if (!jatekVege) {
		if (melyikJatekos == 1) {
			SetConsoleTextAttribute(szinezes, cyan);
			cout << "\tELSO jatekos kovetkezik! 'X'\n" << endl;
		}
		else {
			SetConsoleTextAttribute(szinezes, rozsaszin);
			cout << "\tMASODIK jatekos kovetkezik! 'O'\n" << endl;
		}
		SetConsoleTextAttribute(szinezes, szurke);

		if (!elsoKor) {
			SetConsoleTextAttribute(szinezes, szurke);
			cout << "\tPalya mozgatasa (wasd)\n" << endl;
			if (akcio == 1) {
				if (lapkakSzama > 0) {
					cout << "\tTudsz rakni ernyot lent levore vagy uj lapkara\n";
				}
				else {
					cout << "\tElfogytak a lapkak!\nCsak lent levo lapkara tudsz ernyot rakni\n";
				}
			}
			else if (akcio == 2) {
				cout << "\tMozgatsz vagy passzolsz: 'p'\n";
			}
		}
		else {
			cout << "\tRakj egy uj lapkat!\n";
		}
	}
}

void UresHelyekUjElem(int sorszam, int x, int y) {
	hely * ujUresHelyek = new hely[uresHelyekHossz + 1];

	for (int i = 0; i < uresHelyekHossz; i++)
	{
		ujUresHelyek[i].sorszam = uresHelyek[i].sorszam;
		ujUresHelyek[i].xKoordinata = uresHelyek[i].xKoordinata;
		ujUresHelyek[i].yKoordinata = uresHelyek[i].yKoordinata;
	}
	uresHelyekHossz++;

	ujUresHelyek[uresHelyekIndex].sorszam = sorszam;
	ujUresHelyek[uresHelyekIndex].xKoordinata = x;
	ujUresHelyek[uresHelyekIndex].yKoordinata = y;

	delete[] uresHelyek;
	uresHelyek = ujUresHelyek;

	uresHelyekIndex++;
	uresSorszamIndex++;
}

bool SorszamVizsgal(string sorszam) {
	if (sorszam == "p") {
		if (akcio == 2) {
			return false;
		}
	}
	else {
		if ((int)sorszam[0] >= 65 && (int)sorszam[0] <= 90) { //betu
			if (lapkakSzama > 0) {
				for (int i = 0; i < uresHelyekHossz; i++)
				{
					if (uresHelyek[i].sorszam == (int)sorszam[0]) {
						return false;
					}
				}
			}
			else {
				return false;
			}
		}
		else if ((int)sorszam[0] >= 48 && (int)sorszam[0] <= 57) { //szam
			if (akcio == 1) {
				for (int i = 0; i < sorszamokHossz; i++)
				{
					if (sorszamok[i].sorszam == SzamotCsinal(sorszam)) {
						return false;
					}
				}
			}
			else if (akcio == 2) {
				if (SzamotCsinal(sorszam) == aktualisKorbenRakottSorszam) {
					return true;
				}
				for (int i = 0; i < sorszamokHossz; i++)
				{
					if (sorszamok[i].sorszam == SzamotCsinal(sorszam)) {
						bool elsoSzomszed = true;
						bool masodikSzomszed = true;
						bool harmadikSzomszed = true;
						bool negyedikSzomszed = true;
						for (int j = 0; j < sorszamokHossz; j++) {
							if (sorszamok[i].xKoordinata + 1 == sorszamok[j].xKoordinata &&sorszamok[i].yKoordinata == sorszamok[j].yKoordinata) {
								elsoSzomszed = false;
							}
							if (sorszamok[i].xKoordinata - 1 == sorszamok[j].xKoordinata &&sorszamok[i].yKoordinata == sorszamok[j].yKoordinata) {
								masodikSzomszed = false;
							}
							if (sorszamok[i].xKoordinata == sorszamok[j].xKoordinata &&sorszamok[i].yKoordinata + 1 == sorszamok[j].yKoordinata) {
								harmadikSzomszed = false;
							}
							if (sorszamok[i].xKoordinata == sorszamok[j].xKoordinata &&sorszamok[i].yKoordinata - 1 == sorszamok[j].yKoordinata) {
								negyedikSzomszed = false;
							}
							if (!elsoSzomszed && !masodikSzomszed && !harmadikSzomszed && !negyedikSzomszed) {
								return true;
							}
						}
					}
				}

				MozgatKeres(SzamotCsinal(sorszam));

				//csere
				int alapX, alapY;
				bool mehet = true;
				for (int i = 0; i < sorszamokHossz; i++)
				{
					if (sorszamok[i].sorszam == SzamotCsinal(sorszam)) {
						for (int j = 0; j < mozgatHelyekHossz; j++)
						{
							alapX = sorszamok[i].xKoordinata;
							alapY = sorszamok[i].yKoordinata;
							sorszamok[i].xKoordinata = mozgatHelyek[j].xKoordinata;
							sorszamok[i].yKoordinata = mozgatHelyek[j].yKoordinata;

							LancCsinal();

							sorszamok[i].xKoordinata = alapX;
							sorszamok[i].yKoordinata = alapY;

							if (lancElemekHossz < sorszamokHossz) {
								mozgatHelyek[j].xKoordinata = -1;
								mozgatHelyek[j].yKoordinata = -1;
							}
						}
					}
				}
				int db = 0;
				for (int i = 0; i < mozgatHelyekHossz; i++)
				{
					if (mozgatHelyek[i].xKoordinata != -1 && mozgatHelyek[i].yKoordinata != -1) {
						db++;
					}
				}
				if (db == 0) {
					return true;
				}
				else {
					return false;
				}
			}
		}
	}
	return true;
}

void LancCsinal() {
	lancElemekHossz = 0;
	lancElemIndex = 0;

	if (lancElemekHossz == 0) {
		LancElemekUjElem(sorszamok[0].xKoordinata, sorszamok[0].yKoordinata);
	}

	for (int i = 0; i < lancElemekHossz; i++)
	{
		for (int j = 0; j < sorszamokHossz; j++)
		{
			if (lancElemek[i].xKoordinata - 1 == sorszamok[j].xKoordinata && lancElemek[i].yKoordinata == sorszamok[j].yKoordinata) {
				LancElemekUjElem(sorszamok[j].xKoordinata, sorszamok[j].yKoordinata);
			}
			if (lancElemek[i].xKoordinata + 1 == sorszamok[j].xKoordinata && lancElemek[i].yKoordinata == sorszamok[j].yKoordinata) {
				LancElemekUjElem(sorszamok[j].xKoordinata, sorszamok[j].yKoordinata);
			}
			if (lancElemek[i].xKoordinata == sorszamok[j].xKoordinata && lancElemek[i].yKoordinata - 1 == sorszamok[j].yKoordinata) {
				LancElemekUjElem(sorszamok[j].xKoordinata, sorszamok[j].yKoordinata);
			}
			if (lancElemek[i].xKoordinata == sorszamok[j].xKoordinata && lancElemek[i].yKoordinata + 1 == sorszamok[j].yKoordinata) {
				LancElemekUjElem(sorszamok[j].xKoordinata, sorszamok[j].yKoordinata);
			}
		}
	}
}

bool AbcdVizsgal(string sorszam, string abcd) {
	if (akcio == 1) {
		if ((int)sorszam[0] >= 48 && (int)sorszam[0] <= 57) {
			if (abcd == "a" || abcd == "b" || abcd == "c" || abcd == "d") {
				for (int i = 0; i < sorszamokHossz; i++)
				{
					if (sorszamok[i].sorszam == SzamotCsinal(sorszam)) {
						if (sorszamok[i].a && abcd == "a") {
							return true;
						}
						else if (sorszamok[i].b && abcd == "b") {
							return true;
						}
						else if (sorszamok[i].c  && abcd == "c") {
							return true;
						}
						else if (sorszamok[i].d  && abcd == "d") {
							return true;
						}

					}
				}
			}
			else {
				return true;
			}
		}
		else if ((int)sorszam[0] >= 65 && (int)sorszam[0] <= 90) {
			if (abcd == "a" || abcd == "b" || abcd == "c" || abcd == "d") {
				return false;
			}
			else {
				return true;
			}
		}
	}
	return false;
}

void UresHelyVizsgal(int x, int y) {
	bool igen = true;

	for (int j = 0; j < uresHelyekHossz; j++)
	{
		if (x == uresHelyek[j].xKoordinata && y == uresHelyek[j].yKoordinata) {
			igen = false;
		}
	}
	for (int j = 0; j < sorszamokHossz; j++)
	{
		if (x == sorszamok[j].xKoordinata && y == sorszamok[j].yKoordinata) {
			igen = false;
		}
	}
	if (igen) {
		UresHelyekUjElem(uresSorszamIndex, x, y);
	}
}

void UresHelyekKeres() {
	if (lapkakSzama > 0) {
		uresHelyekHossz = 0;
		uresHelyekIndex = 0;
		uresSorszamIndex = 65;
		for (int sorIndex = 0; sorIndex < MAGASSAG; sorIndex++)
		{
			for (int oszlopIndex = 0; oszlopIndex < SZELESSEG; oszlopIndex++)
			{
				for (int i = 0; i < sorszamokHossz; i++)
				{
					if (sorIndex == sorszamok[i].xKoordinata - 1 && oszlopIndex == sorszamok[i].yKoordinata) {
						UresHelyVizsgal(sorszamok[i].xKoordinata - 1, sorszamok[i].yKoordinata);
					}
					else if (sorIndex == sorszamok[i].xKoordinata && oszlopIndex == sorszamok[i].yKoordinata + 1) {
						UresHelyVizsgal(sorszamok[i].xKoordinata, sorszamok[i].yKoordinata + 1);
					}
					else if (sorIndex == sorszamok[i].xKoordinata + 1 && oszlopIndex == sorszamok[i].yKoordinata) {
						UresHelyVizsgal(sorszamok[i].xKoordinata + 1, sorszamok[i].yKoordinata);
					}
					else if (sorIndex == sorszamok[i].xKoordinata && oszlopIndex == sorszamok[i].yKoordinata - 1) {
						UresHelyVizsgal(sorszamok[i].xKoordinata, sorszamok[i].yKoordinata - 1);
					}
				}
			}
		}
	}
	else {

	}
}

void MozgatKeres(int sorszam) {
	uresSorszamIndex = 65;
	mozgatHelyekHossz = 0;
	mozgatHelyekIndex = 0;
	int sor = 0, oszlop = 0;
	for (int i = 0; i < sorszamokHossz; i++) //lehetne while-al
	{
		if (sorszam == sorszamok[i].sorszam) { //megvan melyiket akarom mozgatni
			mozgatHonnanX = sorszamok[i].xKoordinata;
			mozgatHonnanY = sorszamok[i].yKoordinata;
			mozgatHonnanSorszam = sorszamok[i].sorszam;
			sor = sorszamok[i].xKoordinata; //megvan melyik sor a vizszintes
			oszlop = sorszamok[i].yKoordinata; //megvan melyik oszlop a fuggoleges
		}
	}

	for (int i = 0; i < sorszamokHossz; i++)
	{
#pragma region VIZSZINTES
		if (sor == sorszamok[i].xKoordinata) {
			if (oszlop != sorszamok[i].yKoordinata) {
				bool mehet = true;

				for (int j = 0; j < sorszamokHossz; j++)
				{
					if (sorszamok[i].yKoordinata - 1 == sorszamok[j].yKoordinata) {
						mehet = false;
					}
				}
				if (mehet) {
					if (mozgatHelyekHossz == 0) {
						MozgatHelyekUjElem(sor, sorszamok[i].yKoordinata - 1);
					}
					else {
						bool megintMehet = true;
						for (int u = 0; u < mozgatHelyekHossz; u++)
						{
							if (sorszamok[i].yKoordinata - 1 == mozgatHelyek[u].yKoordinata) {
								megintMehet = false;
							}
						}
						if (megintMehet) {
							MozgatHelyekUjElem(sor, sorszamok[i].yKoordinata - 1);
						}
					}
				}

				mehet = true;
				for (int j = 0; j < sorszamokHossz; j++)
				{
					if (sorszamok[i].yKoordinata + 1 == sorszamok[j].yKoordinata) {
						mehet = false;
					}
				}
				if (mehet) {
					if (mozgatHelyekHossz == 0) {
						MozgatHelyekUjElem(sor, sorszamok[i].yKoordinata + 1);
					}
					else {
						bool megintMehet = true;
						for (int u = 0; u < mozgatHelyekHossz; u++)
						{
							if (sorszamok[i].yKoordinata + 1 == mozgatHelyek[u].yKoordinata) {
								megintMehet = false;
							}
						}
						if (megintMehet) {
							MozgatHelyekUjElem(sor, sorszamok[i].yKoordinata + 1);
						}
					}
				}
			}
		}
		else if (sor - 1 == sorszamok[i].xKoordinata) {
			if (oszlop != sorszamok[i].yKoordinata) {
				bool mehet = true;

				for (int j = 0; j < sorszamokHossz; j++)
				{
					if (sorszamok[i].xKoordinata + 1 == sorszamok[j].xKoordinata && sorszamok[i].xKoordinata + 1 != mozgatHonnanX) {
						mehet = false;
					}
				}
				if (mehet) {
					if (mozgatHelyekHossz == 0) {
						MozgatHelyekUjElem(sorszamok[i].xKoordinata + 1, sorszamok[i].yKoordinata);
					}
					else {
						bool megintMehet = true;
						for (int u = 0; u < mozgatHelyekHossz; u++)
						{
							if (sorszamok[i].xKoordinata + 1 == mozgatHelyek[u].xKoordinata&& sorszamok[i].yKoordinata == mozgatHelyek[u].yKoordinata) {
								megintMehet = false;
							}
						}
						if (megintMehet) {
							MozgatHelyekUjElem(sorszamok[i].xKoordinata + 1, sorszamok[i].yKoordinata);
						}
					}
				}
			}
		}
		else if (sor + 1 == sorszamok[i].xKoordinata) {
			if (oszlop != sorszamok[i].yKoordinata) {
				bool mehet = true;

				for (int j = 0; j < sorszamokHossz; j++)
				{
					if (sorszamok[i].xKoordinata - 1 == sorszamok[j].xKoordinata && sorszamok[i].xKoordinata - 1 != mozgatHonnanX) {
						mehet = false;
					}
				}
				if (mehet) {
					if (mozgatHelyekHossz == 0) {
						MozgatHelyekUjElem(sorszamok[i].xKoordinata - 1, sorszamok[i].yKoordinata);
					}
					else {
						bool megintMehet = true;
						for (int u = 0; u < mozgatHelyekHossz; u++)
						{
							if (sorszamok[i].xKoordinata - 1 == mozgatHelyek[u].xKoordinata && sorszamok[i].yKoordinata == mozgatHelyek[u].yKoordinata) {
								megintMehet = false;
							}
						}
						if (megintMehet) {
							MozgatHelyekUjElem(sorszamok[i].xKoordinata - 1, sorszamok[i].yKoordinata);
						}
					}
				}
			}
		}
#pragma endregion

#pragma region FUGGOLEGES
		if (oszlop == sorszamok[i].yKoordinata) {
			if (sor != sorszamok[i].xKoordinata) {
				bool mehet = true;

				for (int j = 0; j < sorszamokHossz; j++)
				{
					if (sorszamok[i].xKoordinata - 1 == sorszamok[j].xKoordinata) {
						mehet = false;
					}
				}
				if (mehet) {
					if (mozgatHelyekHossz == 0) {
						MozgatHelyekUjElem(sorszamok[i].xKoordinata - 1, oszlop);
					}
					else {
						bool megintMehet = true;
						for (int u = 0; u < mozgatHelyekHossz; u++)
						{
							if (sorszamok[i].xKoordinata - 1 == mozgatHelyek[u].xKoordinata) {
								megintMehet = false;
							}
						}
						if (megintMehet) {
							MozgatHelyekUjElem(sorszamok[i].xKoordinata - 1, oszlop);
						}
					}
				}

				mehet = true;
				for (int j = 0; j < sorszamokHossz; j++)
				{
					if (sorszamok[i].xKoordinata + 1 == sorszamok[j].xKoordinata) {
						mehet = false;
					}
				}
				if (mehet) {
					if (mozgatHelyekHossz == 0) {
						MozgatHelyekUjElem(sorszamok[i].xKoordinata + 1, oszlop);
					}
					else {
						bool megintMehet = true;
						for (int u = 0; u < mozgatHelyekHossz; u++)
						{
							if (sorszamok[i].xKoordinata + 1 == mozgatHelyek[u].xKoordinata) {
								megintMehet = false;
							}
						}
						if (megintMehet) {
							MozgatHelyekUjElem(sorszamok[i].xKoordinata + 1, oszlop);
						}
					}
				}
			}
		}
		else if (oszlop - 1 == sorszamok[i].yKoordinata) {
			if (sor != sorszamok[i].xKoordinata) {
				bool mehet = true;

				for (int j = 0; j < sorszamokHossz; j++)
				{
					if (sorszamok[i].yKoordinata + 1 == sorszamok[j].yKoordinata && sorszamok[i].yKoordinata + 1 != mozgatHonnanY) {
						mehet = false;
					}
				}
				if (mehet) {
					if (mozgatHelyekHossz == 0) {
						MozgatHelyekUjElem(sorszamok[i].xKoordinata, sorszamok[i].yKoordinata + 1);
					}
					else {
						bool megintMehet = true;
						for (int u = 0; u < mozgatHelyekHossz; u++)
						{
							if (sorszamok[i].yKoordinata + 1 == mozgatHelyek[u].yKoordinata&& sorszamok[i].xKoordinata == mozgatHelyek[u].xKoordinata) {
								megintMehet = false;
							}
						}
						if (megintMehet) {
							MozgatHelyekUjElem(sorszamok[i].xKoordinata, sorszamok[i].yKoordinata + 1);
						}
					}
				}
			}
		}
		else if (oszlop + 1 == sorszamok[i].yKoordinata) {
			if (sor != sorszamok[i].xKoordinata) {
				bool mehet = true;

				for (int j = 0; j < sorszamokHossz; j++)
				{
					if (sorszamok[i].yKoordinata - 1 == sorszamok[j].yKoordinata && sorszamok[i].yKoordinata - 1 != mozgatHonnanY) {
						mehet = false;
					}
				}
				if (mehet) {
					if (mozgatHelyekHossz == 0) {
						MozgatHelyekUjElem(sorszamok[i].xKoordinata, sorszamok[i].yKoordinata - 1);
					}
					else {
						bool megintMehet = true;
						for (int u = 0; u < mozgatHelyekHossz; u++)
						{
							if (sorszamok[i].yKoordinata - 1 == mozgatHelyek[u].yKoordinata && sorszamok[i].xKoordinata == mozgatHelyek[u].xKoordinata) {
								megintMehet = false;
							}
						}
						if (megintMehet) {
							MozgatHelyekUjElem(sorszamok[i].xKoordinata, sorszamok[i].yKoordinata - 1);
						}
					}
				}
			}
		}
#pragma endregion

		//ATLO
#pragma region KOZEP -> JOBB ALUL
		if (sor == sorszamok[i].xKoordinata && oszlop == sorszamok[i].yKoordinata) {
			bool van = true;
			int x = sor;
			int y = oszlop;
			while (van)
			{
				x++;
				y++;

				if (MozgatHelyekVizsgalAtloban(x, y)) {
					bool mehet = true;
					for (int i = 0; i < mozgatHelyekHossz; i++)
					{
						if (x == mozgatHelyek[i].xKoordinata && y == mozgatHelyek[i].yKoordinata) {
							mehet = false;
						}
					}
					if (mehet) {
						MozgatHelyekUjElem(x, y);
					}
				}
				else {
					van = false;
				}
			}
		}
#pragma endregion

#pragma region KOZEP -> BAL FELUL
		if (sor == sorszamok[i].xKoordinata && oszlop == sorszamok[i].yKoordinata) {
			bool van = true;
			int x = sor;
			int y = oszlop;
			while (van)
			{
				x--;
				y--;

				if (MozgatHelyekVizsgalAtloban(x, y)) {
					bool mehet = true;
					for (int i = 0; i < mozgatHelyekHossz; i++)
					{
						if (x == mozgatHelyek[i].xKoordinata && y == mozgatHelyek[i].yKoordinata) {
							mehet = false;
						}
					}
					if (mehet) {
						MozgatHelyekUjElem(x, y);
					}
				}
				else {
					van = false;
				}
			}
		}
#pragma endregion

#pragma region KOZEP -> JOBB FELUL
		if (sor == sorszamok[i].xKoordinata && oszlop == sorszamok[i].yKoordinata) {
			bool van = true;
			int x = sor;
			int y = oszlop;
			while (van)
			{
				x--;
				y++;

				if (MozgatHelyekVizsgalAtloban(x, y)) {
					bool mehet = true;
					for (int i = 0; i < mozgatHelyekHossz; i++)
					{
						if (x == mozgatHelyek[i].xKoordinata && y == mozgatHelyek[i].yKoordinata) {
							mehet = false;
						}
					}
					if (mehet) {
						MozgatHelyekUjElem(x, y);
					}
				}
				else {
					van = false;
				}
			}
		}
#pragma endregion

#pragma region KOZEP -> BAL ALUL
		if (sor == sorszamok[i].xKoordinata && oszlop == sorszamok[i].yKoordinata) {
			bool van = true;
			int x = sor;
			int y = oszlop;
			while (van)
			{
				x++;
				y--;

				if (MozgatHelyekVizsgalAtloban(x, y)) {
					bool mehet = true;
					for (int i = 0; i < mozgatHelyekHossz; i++)
					{
						if (x == mozgatHelyek[i].xKoordinata && y == mozgatHelyek[i].yKoordinata) {
							mehet = false;
						}
					}
					if (mehet) {
						MozgatHelyekUjElem(x, y);
					}
				}
				else {
					van = false;
				}
			}
		}
#pragma endregion
	}
}

bool MozgatHelyekVizsgalAtloban(int x, int y) {
	int j = 0;
	bool vanSzomszed = false;
	while (j < sorszamokHossz && !vanSzomszed)
	{
		if (x - 1 == sorszamok[j].xKoordinata && y == sorszamok[j].yKoordinata ||
			x + 1 == sorszamok[j].xKoordinata && y == sorszamok[j].yKoordinata ||
			y - 1 == sorszamok[j].yKoordinata && x == sorszamok[j].xKoordinata ||
			y + 1 == sorszamok[j].yKoordinata && x == sorszamok[j].xKoordinata) {
			vanSzomszed = true;
		}
		j++;
	}

	return vanSzomszed;
}

void MozgatHelyekUjElem(int x, int y) {
	bool mehet = true;

	for (int i = 0; i < sorszamokHossz; i++)
	{
		if (sorszamok[i].xKoordinata == x && sorszamok[i].yKoordinata == y) {
			mehet = false;
		}
	}

	if (mehet) {
		hely * ujMozgatHelyek = new hely[mozgatHelyekHossz + 1];

		for (int i = 0; i < mozgatHelyekHossz; i++)
		{
			ujMozgatHelyek[i].sorszam = mozgatHelyek[i].sorszam;
			ujMozgatHelyek[i].xKoordinata = mozgatHelyek[i].xKoordinata;
			ujMozgatHelyek[i].yKoordinata = mozgatHelyek[i].yKoordinata;
		}
		mozgatHelyekHossz++;

		ujMozgatHelyek[mozgatHelyekIndex].sorszam = uresSorszamIndex;
		ujMozgatHelyek[mozgatHelyekIndex].xKoordinata = x;
		ujMozgatHelyek[mozgatHelyekIndex].yKoordinata = y;

		delete[] mozgatHelyek;
		mozgatHelyek = ujMozgatHelyek;

		mozgatHelyekIndex++;
		uresSorszamIndex++;
	}
}

void LancElemekUjElem(int x, int y) {
	bool mehet = true;
	for (int i = 0; i < lancElemekHossz; i++)
	{
		if (lancElemek[i].xKoordinata == x && lancElemek[i].yKoordinata == y) {
			mehet = false;
		}
	}

	if (mehet) {
		hely * ujLancElemek = new hely[lancElemekHossz + 1];

		for (int i = 0; i < lancElemekHossz; i++)
		{
			ujLancElemek[i].sorszam = lancElemek[i].sorszam;
			ujLancElemek[i].xKoordinata = lancElemek[i].xKoordinata;
			ujLancElemek[i].yKoordinata = lancElemek[i].yKoordinata;
		}
		lancElemekHossz++;

		ujLancElemek[lancElemIndex].sorszam = lancElemSorszam;
		ujLancElemek[lancElemIndex].xKoordinata = x;
		ujLancElemek[lancElemIndex].yKoordinata = y;

		delete[] lancElemek;
		lancElemek = ujLancElemek;

		lancElemIndex++;
		lancElemSorszam++;
	}
}

void JatekVegeVizsgal() {

	if (elsoJatekosErnyokDb <= 0 && masodikJatekosErnyokDb <= 0) {
		jatekVege = true;
	}

	JatekVegeVizszintesVizsgal(1);
	JatekVegeVizszintesVizsgal(2);

	JatekVegeFuggolegesVizsgal(1);
	JatekVegeFuggolegesVizsgal(2);

	JatekVegeAtloVizsgal(1);
	JatekVegeAtloVizsgal(2);
}

void JatekVegeVizszintesVizsgal(int melyikJatekos) {
	for (int i = 0; i < sorszamokHossz; i++)
	{
		if (sorszamok[i].aMelyik == melyikJatekos && sorszamok[i].bMelyik == melyikJatekos) {
			for (int j = 0; j < sorszamokHossz; j++)
			{
				if (sorszamok[i].xKoordinata == sorszamok[j].xKoordinata && sorszamok[i].yKoordinata + 1 == sorszamok[j].yKoordinata) {
					if (sorszamok[j].aMelyik == melyikJatekos && sorszamok[j].bMelyik == melyikJatekos) {
						for (int u = 0; u < sorszamokHossz; u++)
						{
							if (sorszamok[i].xKoordinata == sorszamok[u].xKoordinata && sorszamok[i].yKoordinata + 2 == sorszamok[u].yKoordinata) {
								if (sorszamok[u].aMelyik == melyikJatekos) {
									if (melyikJatekos == 1) {
										jatekVegeElsoJatekos = true;
									}
									else if (melyikJatekos == 2) {
										jatekVegeMasodikJatekos = true;
									}
									jatekVege = true;
								}
							}
							else if (sorszamok[i].xKoordinata == sorszamok[u].xKoordinata && sorszamok[i].yKoordinata - 1 == sorszamok[u].yKoordinata) {
								if (sorszamok[u].bMelyik == melyikJatekos) {
									if (melyikJatekos == 1) {
										jatekVegeElsoJatekos = true;
									}
									else if (melyikJatekos == 2) {
										jatekVegeMasodikJatekos = true;
									}
									jatekVege = true;
								}
							}
						}
					}
				}
			}
		}
		if (sorszamok[i].cMelyik == melyikJatekos && sorszamok[i].dMelyik == melyikJatekos) {
			for (int j = 0; j < sorszamokHossz; j++)
			{
				if (sorszamok[i].xKoordinata == sorszamok[j].xKoordinata && sorszamok[i].yKoordinata + 1 == sorszamok[j].yKoordinata) {
					if (sorszamok[j].cMelyik == melyikJatekos && sorszamok[j].dMelyik == melyikJatekos) {
						for (int u = 0; u < sorszamokHossz; u++)
						{
							if (sorszamok[i].xKoordinata == sorszamok[u].xKoordinata && sorszamok[i].yKoordinata + 2 == sorszamok[u].yKoordinata) {
								if (sorszamok[u].cMelyik == melyikJatekos) {
									if (melyikJatekos == 1) {
										jatekVegeElsoJatekos = true;
									}
									else if (melyikJatekos == 2) {
										jatekVegeMasodikJatekos = true;
									}
									jatekVege = true;
								}
							}
							else if (sorszamok[i].xKoordinata == sorszamok[u].xKoordinata && sorszamok[i].yKoordinata - 1 == sorszamok[u].yKoordinata) {
								if (sorszamok[u].dMelyik == melyikJatekos) {
									if (melyikJatekos == 1) {
										jatekVegeElsoJatekos = true;
									}
									else if (melyikJatekos == 2) {
										jatekVegeMasodikJatekos = true;
									}
									jatekVege = true;
								}
							}
						}
					}
				}
			}
		}
	}
}

void JatekVegeFuggolegesVizsgal(int melyikJatekos) {
	for (int i = 0; i < sorszamokHossz; i++)
	{
		if (sorszamok[i].aMelyik == melyikJatekos && sorszamok[i].cMelyik == melyikJatekos) {
			for (int j = 0; j < sorszamokHossz; j++)
			{
				if (sorszamok[i].xKoordinata + 1 == sorszamok[j].xKoordinata && sorszamok[i].yKoordinata == sorszamok[j].yKoordinata) {
					if (sorszamok[j].aMelyik == melyikJatekos && sorszamok[j].cMelyik == melyikJatekos) {
						for (int u = 0; u < sorszamokHossz; u++)
						{
							if (sorszamok[i].xKoordinata + 2 == sorszamok[u].xKoordinata && sorszamok[i].yKoordinata == sorszamok[u].yKoordinata) {
								if (sorszamok[u].aMelyik == melyikJatekos) {
									if (melyikJatekos == 1) {
										jatekVegeElsoJatekos = true;
									}
									else if (melyikJatekos == 2) {
										jatekVegeMasodikJatekos = true;
									}
									jatekVege = true;
								}
							}
							else if (sorszamok[i].xKoordinata - 1 == sorszamok[u].xKoordinata && sorszamok[i].yKoordinata == sorszamok[u].yKoordinata) {
								if (sorszamok[u].cMelyik == melyikJatekos) {
									if (melyikJatekos == 1) {
										jatekVegeElsoJatekos = true;
									}
									else if (melyikJatekos == 2) {
										jatekVegeMasodikJatekos = true;
									}
									jatekVege = true;
								}
							}
						}
					}
				}
			}
		}
		if (sorszamok[i].bMelyik == melyikJatekos && sorszamok[i].dMelyik == melyikJatekos) {
			for (int j = 0; j < sorszamokHossz; j++)
			{
				if (sorszamok[i].xKoordinata + 1 == sorszamok[j].xKoordinata && sorszamok[i].yKoordinata == sorszamok[j].yKoordinata) {
					if (sorszamok[j].bMelyik == melyikJatekos && sorszamok[j].dMelyik == melyikJatekos) {
						for (int u = 0; u < sorszamokHossz; u++)
						{
							if (sorszamok[i].xKoordinata + 2 == sorszamok[u].xKoordinata && sorszamok[i].yKoordinata == sorszamok[u].yKoordinata) {
								if (sorszamok[u].bMelyik == melyikJatekos) {
									if (melyikJatekos == 1) {
										jatekVegeElsoJatekos = true;
									}
									else if (melyikJatekos == 2) {
										jatekVegeMasodikJatekos = true;
									}
									jatekVege = true;
								}
							}
							else if (sorszamok[i].xKoordinata - 1 == sorszamok[u].xKoordinata && sorszamok[i].yKoordinata == sorszamok[u].yKoordinata) {
								if (sorszamok[u].dMelyik == melyikJatekos) {
									if (melyikJatekos == 1) {
										jatekVegeElsoJatekos = true;
									}
									else if (melyikJatekos == 2) {
										jatekVegeMasodikJatekos = true;
									}
									jatekVege = true;
								}
							}
						}
					}
				}
			}
		}
	}
}

void JatekVegeAtloVizsgal(int melyikJatekos) {
	for (int i = 0; i < sorszamokHossz; i++)
	{
		if (sorszamok[i].aMelyik == melyikJatekos && sorszamok[i].dMelyik == melyikJatekos) {
			for (int j = 0; j < sorszamokHossz; j++)
			{
				if (sorszamok[i].xKoordinata + 1 == sorszamok[j].xKoordinata && sorszamok[i].yKoordinata + 1 == sorszamok[j].yKoordinata) {
					if (sorszamok[j].aMelyik == melyikJatekos && sorszamok[j].dMelyik == melyikJatekos) {
						for (int u = 0; u < sorszamokHossz; u++)
						{
							if (sorszamok[i].xKoordinata + 2 == sorszamok[u].xKoordinata && sorszamok[i].yKoordinata + 2 == sorszamok[u].yKoordinata) {
								if (sorszamok[u].aMelyik == melyikJatekos) {
									if (melyikJatekos == 1) {
										jatekVegeElsoJatekos = true;
									}
									else if (melyikJatekos == 2) {
										jatekVegeMasodikJatekos = true;
									}
									jatekVege = true;
								}
							}
							else if (sorszamok[i].xKoordinata - 1 == sorszamok[u].xKoordinata && sorszamok[i].yKoordinata - 1 == sorszamok[u].yKoordinata) {
								if (sorszamok[u].dMelyik == melyikJatekos) {
									if (melyikJatekos == 1) {
										jatekVegeElsoJatekos = true;
									}
									else if (melyikJatekos == 2) {
										jatekVegeMasodikJatekos = true;
									}
									jatekVege = true;
								}
							}
						}
					}
				}
			}
		}
		if (sorszamok[i].bMelyik == melyikJatekos && sorszamok[i].cMelyik == melyikJatekos) {
			for (int j = 0; j < sorszamokHossz; j++)
			{
				if (sorszamok[i].xKoordinata - 1 == sorszamok[j].xKoordinata && sorszamok[i].yKoordinata + 1 == sorszamok[j].yKoordinata) {
					if (sorszamok[j].bMelyik == melyikJatekos && sorszamok[j].cMelyik == melyikJatekos) {
						for (int u = 0; u < sorszamokHossz; u++)
						{
							if (sorszamok[i].xKoordinata - 2 == sorszamok[u].xKoordinata && sorszamok[i].yKoordinata + 2 == sorszamok[u].yKoordinata) {
								if (sorszamok[u].cMelyik == melyikJatekos) {
									if (melyikJatekos == 1) {
										jatekVegeElsoJatekos = true;
									}
									else if (melyikJatekos == 2) {
										jatekVegeMasodikJatekos = true;
									}
									jatekVege = true;
								}
							}
							else if (sorszamok[i].xKoordinata + 1 == sorszamok[u].xKoordinata && sorszamok[i].yKoordinata - 1 == sorszamok[u].yKoordinata) {
								if (sorszamok[u].bMelyik == melyikJatekos) {
									if (melyikJatekos == 1) {
										jatekVegeElsoJatekos = true;
									}
									else if (melyikJatekos == 2) {
										jatekVegeMasodikJatekos = true;
									}
									jatekVege = true;
								}
							}
						}
					}
				}
			}
		}
		if (sorszamok[i].bMelyik == melyikJatekos) {
			for (int j = 0; j < sorszamokHossz; j++)
			{
				if (sorszamok[i].xKoordinata == sorszamok[j].xKoordinata && sorszamok[i].yKoordinata + 1 == sorszamok[j].yKoordinata) {
					if (sorszamok[j].cMelyik == melyikJatekos) {
						for (int u = 0; u < sorszamokHossz; u++)
						{
							if (sorszamok[i].xKoordinata + 1 == sorszamok[u].xKoordinata && sorszamok[i].yKoordinata + 1 == sorszamok[u].yKoordinata) {
								if (sorszamok[u].bMelyik == melyikJatekos) {
									for (int z = 0; z < sorszamokHossz; z++)
									{
										if (sorszamok[i].xKoordinata + 1 == sorszamok[z].xKoordinata && sorszamok[i].yKoordinata + 2 == sorszamok[z].yKoordinata) {
											if (sorszamok[z].cMelyik == melyikJatekos) {
												for (int t = 0; t < sorszamokHossz; t++)
												{
													if (sorszamok[i].xKoordinata + 2 == sorszamok[t].xKoordinata && sorszamok[i].yKoordinata + 2 == sorszamok[t].yKoordinata) {
														if (sorszamok[t].bMelyik == melyikJatekos) {
															if (melyikJatekos == 1) {
																jatekVegeElsoJatekos = true;
															}
															else if (melyikJatekos == 2) {
																jatekVegeMasodikJatekos = true;
															}
															jatekVege = true;
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
		if (sorszamok[i].cMelyik == melyikJatekos) {
			for (int j = 0; j < sorszamokHossz; j++)
			{
				if (sorszamok[i].xKoordinata == sorszamok[j].xKoordinata && sorszamok[i].yKoordinata + 1 == sorszamok[j].yKoordinata) {
					if (sorszamok[j].bMelyik == melyikJatekos) {
						for (int u = 0; u < sorszamokHossz; u++)
						{
							if (sorszamok[i].xKoordinata + 1 == sorszamok[u].xKoordinata && sorszamok[i].yKoordinata + 1 == sorszamok[u].yKoordinata) {
								if (sorszamok[u].cMelyik == melyikJatekos) {
									for (int z = 0; z < sorszamokHossz; z++)
									{
										if (sorszamok[i].xKoordinata + 1 == sorszamok[z].xKoordinata && sorszamok[i].yKoordinata + 2 == sorszamok[z].yKoordinata) {
											if (sorszamok[z].bMelyik == melyikJatekos) {
												for (int t = 0; t < sorszamokHossz; t++)
												{
													if (sorszamok[i].xKoordinata + 2 == sorszamok[t].xKoordinata && sorszamok[i].yKoordinata + 2 == sorszamok[t].yKoordinata) {
														if (sorszamok[t].cMelyik == melyikJatekos) {
															if (melyikJatekos == 1) {
																jatekVegeElsoJatekos = true;
															}
															else if (melyikJatekos == 2) {
																jatekVegeMasodikJatekos = true;
															}
															jatekVege = true;
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
		if (sorszamok[i].aMelyik == melyikJatekos) {
			for (int j = 0; j < sorszamokHossz; j++)
			{
				if (sorszamok[i].xKoordinata == sorszamok[j].xKoordinata && sorszamok[i].yKoordinata - 1 == sorszamok[j].yKoordinata) {
					if (sorszamok[j].dMelyik == melyikJatekos) {
						for (int u = 0; u < sorszamokHossz; u++)
						{
							if (sorszamok[i].xKoordinata + 1 == sorszamok[u].xKoordinata && sorszamok[i].yKoordinata - 1 == sorszamok[u].yKoordinata) {
								if (sorszamok[u].aMelyik == melyikJatekos) {
									for (int z = 0; z < sorszamokHossz; z++)
									{
										if (sorszamok[i].xKoordinata + 1 == sorszamok[z].xKoordinata && sorszamok[i].yKoordinata - 2 == sorszamok[z].yKoordinata) {
											if (sorszamok[z].dMelyik == melyikJatekos) {
												for (int t = 0; t < sorszamokHossz; t++)
												{
													if (sorszamok[i].xKoordinata + 2 == sorszamok[t].xKoordinata && sorszamok[i].yKoordinata - 2 == sorszamok[t].yKoordinata) {
														if (sorszamok[t].aMelyik == melyikJatekos) {
															if (melyikJatekos == 1) {
																jatekVegeElsoJatekos = true;
															}
															else if (melyikJatekos == 2) {
																jatekVegeMasodikJatekos = true;
															}
															jatekVege = true;
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
		if (sorszamok[i].dMelyik == melyikJatekos) {
			for (int j = 0; j < sorszamokHossz; j++)
			{
				if (sorszamok[i].xKoordinata == sorszamok[j].xKoordinata && sorszamok[i].yKoordinata - 1 == sorszamok[j].yKoordinata) {
					if (sorszamok[j].aMelyik == melyikJatekos) {
						for (int u = 0; u < sorszamokHossz; u++)
						{
							if (sorszamok[i].xKoordinata + 1 == sorszamok[u].xKoordinata && sorszamok[i].yKoordinata - 1 == sorszamok[u].yKoordinata) {
								if (sorszamok[u].dMelyik == melyikJatekos) {
									for (int z = 0; z < sorszamokHossz; z++)
									{
										if (sorszamok[i].xKoordinata + 1 == sorszamok[z].xKoordinata && sorszamok[i].yKoordinata - 2 == sorszamok[z].yKoordinata) {
											if (sorszamok[z].aMelyik == melyikJatekos) {
												for (int t = 0; t < sorszamokHossz; t++)
												{
													if (sorszamok[i].xKoordinata + 2 == sorszamok[t].xKoordinata && sorszamok[i].yKoordinata - 2 == sorszamok[t].yKoordinata) {
														if (sorszamok[t].dMelyik == melyikJatekos) {
															if (melyikJatekos == 1) {
																jatekVegeElsoJatekos = true;
															}
															else if (melyikJatekos == 2) {
																jatekVegeMasodikJatekos = true;
															}
															jatekVege = true;
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
}

void JatekMehet() {
	melyikJatekos = 1;
	elsoKor = true;
	akcio = 1;
	lapkakSzama = 16;
	elsoJatekosErnyokDb = 18;
	masodikJatekosErnyokDb = 18;
	passz = false;

	sorszamokHossz = 0;
	sorszamokIndex = 0;
	ujSorszamIndex = 1;

	uresHelyekHossz = 0;
	uresHelyekIndex = 0;
	uresSorszamIndex = 65;

	mozgatHelyekHossz = 0;
	mozgatHelyekIndex = 0;

	lancElemekHossz = 0;
	lancElemIndex = 0;
	lancElemSorszam = 0;

	mozgat = false;
	jatekVegeElsoJatekos = false;
	jatekVegeMasodikJatekos = false;
	jatekVege = false;

	hely * ujUresHelyek = new hely[uresHelyekHossz + 1];
	uresHelyekHossz++;
	ujUresHelyek[0].xKoordinata = MAGASSAG / 2;
	ujUresHelyek[0].yKoordinata = SZELESSEG / 2;
	ujUresHelyek[0].sorszam = 65;
	delete[] uresHelyek;
	uresHelyek = ujUresHelyek;
}

void UjJatek() {
	JatekMehet();
}

void JatekosCsere() {
	if (!jatekVegeElsoJatekos) {
		if (melyikJatekos == 1) {
			melyikJatekos = 2;
		}
		else if (melyikJatekos == 2) {
			melyikJatekos = 1;
		}
	}
}