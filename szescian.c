//////////////////////////////////////////////////////////////////////////////////////////
//
// Program wyswietlajacy szescian w rzucie perspektywicznym. Dlugosc boku szescianu
// moze byc interaktywnie zmieniana za pomoca klwiszy '+' i '-'.
//
//////////////////////////////////////////////////////////////////////////////////////////
#include <glut.h>
#include <math.h>
#include <stdio.h>
// Definicja stalych
#define DLUGOSC_BOKU            5.0
GLfloat OBSERWATOR_ODLEGLOSC   = 20.0;
#define DEG2RAD(x) ((float)(x)*3.14/180.0)
#define OBSERWATOR_FOV_Y  30.0  
GLdouble OBSERWATOR_OBROT_Y     =  0.0;
GLdouble OBSERWATOR_OBROT_X    =  0.0;
GLdouble OBSERWATOR_OBROT_Z    = 0;
float X=4;
float N=4;
// Zmienne globalne
double  bok           = DLUGOSC_BOKU; // Dlugosc boku szescianu
int     szerokoscOkna = 800;
int     wysokoscOkna  = 600;

double aAlfa;
double bAlfa;
// Prototypy funkcji
void RysujSzescian(double a);
void UstawParametryWidoku(int szer, int wys);
void WyswietlObraz(void);
void ObslugaKlawiatury(unsigned char klawisz, int x, int y);

//////////////////////////////////////////////////////////////////////////////////////////
// Funkcja rysujaca szescian o boku "a" w trybie GL_QUAD_STRIP.
// Srodek szescianu znajduje siê w punkcie (0,0,0).
void RysujSzescian(double a)
{
	int i,z;
	//double dAlfa=360/55;
	aAlfa=90.0/X;
	// = 360.0 / N;
	glBegin(GL_LINES);

  // Os X
  glColor3f(1.0, 0.0, 0.0);
  glVertex3f(-40.0, 0.0, 0.0);
  glVertex3f(40.0, 0.0, 0.0);

  // Os Y
  glColor3f(0.0,1.0,0.0);
  glVertex3f(0.0, -20.0, 0.0);
  glVertex3f(0.0, 20.0, 0.0);

  // Os Z
  glColor3f(0.0,0.0,1.0);
  glVertex3f(0.0, 0.0, -20.0);
  glVertex3f(0.0, 0.0, 20.0);

  // Koniec tworzenia ukladu wspolrzednych
  glEnd();
  
  //podstawa
 /* glBegin(GL_TRIANGLE_FAN);
  glColor3f(0,0.5,0);
  glVertex3f(0,0,0);

  for(i=0;i*aAlfa<=360;i++){
	  glVertex3f(2*cos(DEG2RAD(i*aAlfa)),0.0,2*sin(DEG2RAD(i*aAlfa)));
		

  }
  glEnd();
  glBegin(GL_TRIANGLE_FAN);
 
  
   glVertex3f(0,20.0,0);
  for(i=0;i*aAlfa<=360;i++){
	  glVertex3f(10*cos(DEG2RAD(i*aAlfa)),20.0,10*sin(DEG2RAD(i*aAlfa)));
		
  }

  glEnd();

  glBegin(GL_QUAD_STRIP);
	for(i=0;i*aAlfa<=360.0;i++){
glVertex3f(2*cos(DEG2RAD(i*aAlfa)),0.0,2*sin(DEG2RAD(i*aAlfa)));
	glVertex3f(10*cos(DEG2RAD(i*aAlfa)),20.0,10*sin(DEG2RAD(i*aAlfa)));

  }
  glEnd();
  */
  

  //ZADANIE INDYWIDUALNE 7/15
  glBegin(GL_TRIANGLE_STRIP);
  glColor3f(0,0.5,0);
  

  for(i=0;i*aAlfa<=90;i++){//podstawa
	  glVertex3f(0,0,0);
	  glVertex3f(5*cos(DEG2RAD(i*aAlfa)),0.0,5*sin(DEG2RAD(i*aAlfa)));
  }
  glEnd();

   glBegin(GL_TRIANGLE_STRIP);
  for(i=0;i*aAlfa<=90;i++){ //podzal pionowy
	  glVertex3f(0,5.0,0);
	glVertex3f(5*cos(DEG2RAD(i*aAlfa)),0,5*sin(DEG2RAD(i*aAlfa)));
  }
  glEnd();

	 //podzial poziomy

	
	for(z=0;z<N;z++)
	{
		for (i = 0;i*aAlfa <= 90.0;i++) {
		 glBegin(GL_TRIANGLE_STRIP);
		 glVertex3f(0,5,0);
		 if ((i + 1)*aAlfa <= 90.0) {
			 glVertex3f((5.0 - 5.0 / N * z)*cos(DEG2RAD(i*aAlfa)), 5.0 / N * z, (5.0 - 5.0 / N * z)*sin(DEG2RAD(i*aAlfa)));
			 glVertex3f((5.0 - 5.0 / N * z)*cos(DEG2RAD((i + 1)*aAlfa)), 5.0 / N * z, (5.0 - 5.0 / N * z)*sin(DEG2RAD((i + 1)*aAlfa)));
		 }
		glEnd();
		}
	}
 //podzialy bokow
	//poziome
	for (int i = 0;i < N;i++) {
		glBegin(GL_TRIANGLE_STRIP);
		glVertex3f(0, 5, 0);
		glVertex3f(0, 5.0/N*i, 0);
		glVertex3f(0, 5.0 / N * i, 5.0- 5.0 / N * i);
		glEnd();
	}

	for (int i = 0;i < N;i++) {
		glBegin(GL_TRIANGLE_STRIP);
		glVertex3f(0, 5, 0);
		glVertex3f(0, 5.0 / N * i, 0);
		glVertex3f(5.0-5.0 / N * i, 5.0 / N * i, 0);
		glEnd();
	}
	//pionowe
	for (int i = 0;i < X;i++) {
		glBegin(GL_TRIANGLE_STRIP);
		glVertex3f(0, 5, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 0, 5.0 - 5.0 / X * i);
		glEnd();
	}
	for (int i = 0;i < N;i++) {
		glBegin(GL_TRIANGLE_STRIP);
		glVertex3f(0, 5, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(5.0 - 5.0 / N * i, 0, 0);
		glEnd();
	}






  glTranslatef(15,0,0);


  glBegin(GL_QUAD_STRIP); 
    glVertex3f(a/2.0, a/2.0, a/2.0);
    glVertex3f(a/2.0, -a/2.0, a/2.0);
    glVertex3f(a/2.0, a/2.0, -a/2.0);
    glVertex3f(a/2.0, -a/2.0, -a/2.0);

    glVertex3f(-a/2.0, a/2.0, -a/2.0);
    glVertex3f(-a/2.0, -a/2.0, -a/2.0);

    glVertex3f(-a/2.0, a/2.0, a/2.0);
    glVertex3f(-a/2.0, -a/2.0, a/2.0);

    glVertex3f(a/2.0, a/2.0, a/2.0);
    glVertex3f(a/2.0, -a/2.0, a/2.0);
  glEnd(); 

  // Gorna sciana
  glBegin(GL_QUAD_STRIP); 
    glVertex3f(-a/2.0, a/2.0, a/2.0);
    glVertex3f(a/2.0, a/2.0, a/2.0);
    glVertex3f(-a/2.0, a/2.0, -a/2.0);
    glVertex3f(a/2.0, a/2.0, -a/2.0);
  glEnd();

  // Dolna sciana
  glBegin(GL_QUAD_STRIP); 
    glVertex3f(-a/2.0, -a/2.0, a/2.0);
    glVertex3f(a/2.0, -a/2.0, a/2.0);
    glVertex3f(-a/2.0, -a/2.0, -a/2.0);
    glVertex3f(a/2.0, -a/2.0, -a/2.0);
  glEnd();

}

//////////////////////////////////////////////////////////////////////////////////////////
// Funkcja ustawiajaca parametry rzutu perspektywicznego i rozmiary viewportu. Powinna
// byæ wywolywana kazdorazowo po zmianie rozmiarow okna programu.
void UstawParametryWidoku(int szer, int wys)
{
  // Zapamietanie wielkosci widoku
  szerokoscOkna = szer;
  wysokoscOkna  = wys;

  // Ustawienie parametrow viewportu
  glViewport(0, 0, szerokoscOkna, wysokoscOkna);

  // Przejscie w tryb modyfikacji macierzy rzutowania
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(OBSERWATOR_FOV_Y, (float)szerokoscOkna/(float)wysokoscOkna, 1.0, 1000.0);
}


//////////////////////////////////////////////////////////////////////////////////////////
// Funkcja wyswietlajaca pojedyncza klatke animacji
void WyswietlObraz(void)
{
  // Wyczyszczenie bufora koloru i bufora glebokosci
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

  // Przejscie w tryb modyfikacji macierzy przeksztalcen geometrycznych
  glMatrixMode(GL_MODELVIEW);

  // Zastapienie aktywnej macierzy macierza jednostkowa
  glLoadIdentity();
  glPushMatrix();
  // Ustalenie polozenia obserwatora
  glTranslatef(0, 0, -OBSERWATOR_ODLEGLOSC);
  glRotatef(OBSERWATOR_OBROT_X, 1, 0, 0);
  glRotatef(OBSERWATOR_OBROT_Y, 0, 1, 0);
  glRotatef(OBSERWATOR_OBROT_Z,0,0,1);
  // Narysowanie szescianu
  RysujSzescian(bok);
  glPopMatrix();
  // Przelaczenie buforow ramki
  glutSwapBuffers();
}


//////////////////////////////////////////////////////////////////////////////////////////
// Funkcja obslugi klawiatury
void ObslugaKlawiatury(unsigned char klawisz, int x, int y)
{
  if(klawisz == '+')
      bok *= 2.0;
  else if (klawisz == '-')
      bok /= 2.0;
  else if (klawisz == 27)
      exit(0);
  else if(klawisz=='a')
	  OBSERWATOR_OBROT_Y+=-1;
  else if(klawisz=='d')
	  OBSERWATOR_OBROT_Y+=1;
  else if(klawisz=='w')
	  OBSERWATOR_OBROT_X+=1;
  else if(klawisz=='s')
	  OBSERWATOR_OBROT_X+=-1;
  else if(klawisz=='z')
	  OBSERWATOR_OBROT_Z+=1;
  else if(klawisz=='x')
	  OBSERWATOR_OBROT_Z+=-1;
   else if(klawisz=='1')
	  OBSERWATOR_ODLEGLOSC+=-1;
   else if(klawisz=='2')
	  OBSERWATOR_ODLEGLOSC+=1;
   else if(klawisz =='t'){
	   if(X<64)
		   X++;
   }
	   else if(klawisz =='n'){
	   if(N<64)
		  N++;
	   }
	   else if(klawisz =='m'){
	   if(N>4)
		   N--;
	   }
   else if(klawisz =='y')
	   if(X>4)
		   X--;
}


//////////////////////////////////////////////////////////////////////////////////////////
// Glowna funkcja programu
int  main(int argc, char **argv)
{
  // Zainicjowanie biblioteki GLUT
  glutInit(&argc, argv);

  // Ustawienie trybu wyswietlania
  glutInitDisplayMode (GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);

  // Ustawienie polozenia dolenego lewego rogu okna
  glutInitWindowPosition(100, 100);

  // Ustawienie rozmiarow okna
  glutInitWindowSize(szerokoscOkna, wysokoscOkna);

  // Utworzenie okna
  glutCreateWindow("Szescian");

  // Odblokowanie bufora glebokosci
  glEnable(GL_DEPTH_TEST);

  // Ustawienie wartosci czyszczacej zawartosc bufora glebokosci
  glClearDepth(1000.0);

  // Ustawienie koloru czyszczenia bufora ramki
  glClearColor (0.0f, 0.0f, 0.0f, 0.0f);

  // Wlaczenie wyswietlania wielokatow w postaci obrysow (przydatne w celach diagnostycznych).
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  
  // Zarejestrowanie funkcji (callback) odpowiedzialnej za 
  glutDisplayFunc(WyswietlObraz);

  // Zarejestrowanie funkcji (callback) wywolywanej za kazdym razem kiedy
  // zmieniane sa rozmiary okna
  glutReshapeFunc(UstawParametryWidoku);

  // Zarejestrowanie funkcji wykonywanej gdy okno nie obsluguje
  // zadnych zadan
  glutIdleFunc(WyswietlObraz);

  // Zarejestrowanie funkcji obslugi klawiatury
  glutKeyboardFunc(ObslugaKlawiatury);

  // Obsluga glownej petli programu (wywolywanie zarejestrowanych callbackow
  // w odpowiedzi na odbierane zdarzenia lub obsluga stanu bezczynnosci)
  glutMainLoop();

  return 0;
}
