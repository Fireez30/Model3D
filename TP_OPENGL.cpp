///////////////////////////////////////////////////////////////////////////////
// Imagina
// ----------------------------------------------------------------------------
// IN - Synthèse d'images - Modélisation géométrique
// Auteur : Gilles Gesquière
// ----------------------------------------------------------------------------
// Base du TP 1
// programme permettant de créer des formes de bases.
// La forme représentée ici est un polygone blanc dessiné sur un fond rouge
///////////////////////////////////////////////////////////////////////////////  

#include <stdio.h>      
#include <stdlib.h>     
#include <math.h>
#include <iostream>
#include <vector>

/* Dans les salles de TP, vous avez généralement accès aux glut dans C:\Dev. Si ce n'est pas le cas, téléchargez les .h .lib ...
Vous pouvez ensuite y faire référence en spécifiant le chemin dans visual. Vous utiliserez alors #include <glut.h>. 
Si vous mettez glut dans le répertoire courant, on aura alors #include "glut.h" 
*/

#include "GL/freeglut.h"
#include "CVector.h"
#include "CPoint.h"

using namespace std;

// Définition de la taille de la fenêtre
#define WIDTH  480

#define HEIGHT 480

// Définition de la couleur de la fenêtre
#define RED   0
#define GREEN 0
#define BLUE  0
#define ALPHA 1


// Touche echap (Esc) permet de sortir du programme
#define KEY_ESC 27
#define PRECISION 0.1
double nbM = 8;
double nbN = 8;

// Entêtes de fonctions
void init_scene();
void render_scene();
GLvoid initGL();
GLvoid window_display();
GLvoid window_reshape(GLsizei width, GLsizei height); 
GLvoid window_key(unsigned char key, int x, int y); 


int main(int argc, char **argv) 
{  
    // initialisation  des paramètres de GLUT en fonction
    // des arguments sur la ligne de commande
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA);

    // définition et création de la fenêtre graphique, ainsi que son titre
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Premier exemple : carré");

    // initialisation de OpenGL et de la scène
    initGL();
    init_scene();

    // choix des procédures de callback pour
    // le tracé graphique
    glutDisplayFunc(&window_display);
    // le redimensionnement de la fenêtre
    glutReshapeFunc(&window_reshape);
    // la gestion des événements clavier
    glutKeyboardFunc(&window_key);

    // la boucle prinicipale de gestion des événements utilisateur
    glutMainLoop();

    return 1;
}

// initialisation du fond de la fenêtre graphique : noir opaque
GLvoid initGL() 
{
    glClearColor(RED, GREEN, BLUE, ALPHA);
}

// Initialisation de la scene. Peut servir à stocker des variables de votre programme
// à initialiser
void init_scene()
{
}

// fonction de call-back pour l´affichage dans la fenêtre

GLvoid window_display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    // C'est l'endroit où l'on peut dessiner. On peut aussi faire appel
    // à une fonction (render_scene() ici) qui contient les informations
    // que l'on veut dessiner
    render_scene();

    // trace la scène grapnique qui vient juste d'être définie
    glFlush();
}

// fonction de call-back pour le redimensionnement de la fenêtre

GLvoid window_reshape(GLsizei width, GLsizei height)
{  
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // ici, vous verrez pendant le cours sur les projections qu'en modifiant les valeurs, il est
    // possible de changer la taille de l'objet dans la fenêtre. Augmentez ces valeurs si l'objet est
    // de trop grosse taille par rapport à la fenêtre.
    glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);


    // toutes les transformations suivantes s´appliquent au modèle de vue
    glMatrixMode(GL_MODELVIEW);
}

// fonction de call-back pour la gestion des événements clavier

GLvoid window_key(unsigned char key, int x, int y) 
{  
    switch (key) {
    case KEY_ESC:
        exit(1);
        break;

    case '+':
        nbM++;
        nbN++;
        glutPostRedisplay();
        break;

    case '-':
        if (nbM > 4) nbM--;
        if (nbN > 3) nbN--;
        glutPostRedisplay();
        break;

    default:
        printf ("La touche %d n´est pas active.\n", key);
        break;
    }
}
CPoint somme(vector<double> asum, vector<CPoint> point){
    double resultx = 0;
    double resulty = 0;
    double resultz = 0;

    CPoint final;

    for (int i = 0;i < asum.size(); i++){
        resultx+=asum[i]*point[i].getX();
        cout << resultx << endl;
        resulty+=asum[i]*point[i].getY();
        resultz+=asum[i]*point[i].getZ();
    }
    final.setX(resultx);
    final.setY(resulty);
    final.setZ(resultz);

    return final;
}

void DrawCurve(vector<CPoint> TabPoint){
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i < TabPoint.size(); i++){
        glVertex3f(TabPoint[i].getX(),TabPoint[i].getY(),TabPoint[i].getZ());
    }
    glEnd();
}
unsigned fact(unsigned x){
    if (x==0) return 1;
    return x*fact(x-1);
}
vector<CPoint> HermiteCubicCurve(CPoint p0,CPoint p1, CVector v0, CVector v1, long nbU){

    vector<CPoint> Pointst;

    for (int i = 0; i < nbU; i++){
        CPoint tmp;

        double j = (double) i/nbU;

        float F1 = 2*pow(j,3)-3*pow(j,2)+1;
        float F2 = -2*pow(j,3)+3*pow(j,2);
        float F3 = pow(j,3)-2*pow(j,2)+j;
        float F4 = pow(j,3)-pow(j,2);

        tmp.setX(F1*p0.getX()+F2*p1.getX()+F3*v0.getX()+F4*v1.getX());
        tmp.setY(F1*p0.getY()+F2*p1.getY()+F3*v0.getY()+F4*v1.getY());
        tmp.setZ(F1*p0.getZ()+F2*p1.getZ()+F3*v0.getZ()+F4*v1.getZ());

        cout << tmp.getX() << tmp.getY() << tmp.getZ() << endl;

        Pointst.push_back(tmp);
    }

    return Pointst;

}
vector<CPoint> BezierCurveByBernstein(vector<CPoint> tabControl,long nbU){
    vector<CPoint> final;
    for (int i = 0; i < nbU; i++){
        double k = (double) i/nbU;
        vector<double> polynomes;
        for (int j = 0; j < tabControl.size(); j++){
            double f1 = (double) fact(tabControl.size()-1)/(fact(j)*fact(tabControl.size()-1 -j));
            double f2 = (double) pow(1-k,tabControl.size()-1 -j);

            double tmp = f1*pow(k,j)*f2;
            cout << tmp << endl;
            polynomes.push_back(tmp);
        }

        CPoint x;
        x = somme(polynomes,tabControl);
        final.push_back(x);
    }

    return final;
}

vector<CPoint> BezierCurveByCasteljau(vector<CPoint> points,long nbu)
{
    vector<CPoint> bezierPoints;

    for(double t = 0 ; t < nbu ; t++)
    {
        double k = (double) t/nbu;

        vector<CPoint> tmp1 = points;

        while(tmp1.size()>1)
        {
            vector<CPoint> tmp2;

            for(int i = 0 ; i<tmp1.size()-1 ; i++)
            {
                CPoint Ptmp1 = tmp1[i];
                CPoint Ptmp2 = tmp1[i+1];

                CPoint tmp = CPoint(Ptmp1.getX() * (1-k) + Ptmp2.getX() * k,Ptmp1.getY() * (1-k) + Ptmp2.getY() * k,0);
                tmp.drawPoint();
                tmp2.push_back(tmp);
            }

            tmp1 = tmp2;
        }

        bezierPoints.push_back(tmp1[0]);
    }

    return bezierPoints;
}
vector<vector<CPoint> > traceSurfaceCylindrique(vector<CPoint> points, CVector v1, long nbv,long nbu){
    vector<vector<CPoint> > result;
    vector<CPoint> cptmp;

    vector<CPoint> bezier = BezierCurveByBernstein(points,nbu);

    for (int j = 0; j < bezier.size(); j++){
        CPoint tmp1 = CPoint(bezier[j].getX()+v1.getX(),bezier[j].getY()+v1.getY(),0);
        cptmp.push_back(bezier[j]);
        cptmp.push_back(tmp1);
        result.push_back(cptmp);
        cptmp.clear();
    }

    vector<CPoint> copy = points;

    double range = (double) 1/nbv;
    for (int i = 0; i < nbv; i++){
        bezier = BezierCurveByBernstein(copy,nbu);
        for (int l = 0; l < copy.size(); l++){
            copy[l].setX(copy[l].getX()+range);
            copy[l].setY(copy[l].getX()+range);
        }

        result.push_back(bezier);
        bezier.clear();
    }

    return result;
}

double rand_float(double a, double b) {
    return ((double)rand() / RAND_MAX) * (b - a) + a;
}

vector<vector<CPoint> > drawCylindre(){
    double hauteur = 20.0;
    double rayon = 10.0;
    int nbMeridiens = 10;

    vector<CPoint> tmp1;
    vector<CPoint> tmp2;
    vector<vector<CPoint> > result;

    for(double i = 0.0; i < nbMeridiens; i++){
        double omega = 2.0 * M_PI *  i / nbMeridiens;

        double x = rayon * sin(omega);
        double y = rayon * cos(omega);
        double z = 0.0;
        double zb = hauteur;

        CPoint b = CPoint(x,y,z);
        CPoint b2 = CPoint(x,y,zb);

        tmp1.push_back(b);
        tmp2.push_back(b2);


    }
    result.push_back(tmp1);

    result.push_back(tmp2);

    for (int i = 0; i < result[0].size() - 1 ; i++){
        glColor3f(rand_float(0.0,1.0), rand_float(0.0,1.0), rand_float(0.0,1.0));
        glBegin(GL_POLYGON);
        result[0][i].drawPoint();
        result[1][i].drawPoint();
        result[1][i+1].drawPoint();
        result[0][i+1].drawPoint();
        glEnd();

    }

    glBegin(GL_POLYGON);
    result[0][0].drawPoint();
    result[0][result[0].size() - 1].drawPoint();
    result[1][result[0].size() - 1].drawPoint();
    result[1][0].drawPoint();
    glEnd();

    glColor3f(rand_float(0.0,1.0), rand_float(0.0,1.0), rand_float(0.0,1.0));
    glBegin(GL_POLYGON);
    for (int i = 0; i < result[0].size(); i++){
        result[0][i].drawPoint();
    }

    glEnd();
    glBegin(GL_POLYGON);
    result[0][0].drawPoint();
    result[0][result.size()- 1].drawPoint();
    result[0][result.size()- 2].drawPoint();
    glEnd();


    return result;

}

vector<CPoint> drawCone(int n){
    int rayon = 15;
    int hauteur = 20;

    vector<CPoint> result;
    result.push_back(CPoint(0,0,20));

    for(double i = 0.0; i < n; i++){
        double omega = 2.0 * M_PI *  i / n;

        double x = rayon * sin(omega);
        double y = rayon * cos(omega);
        double z = 20+hauteur;

        CPoint b = CPoint(x,y,z);

        result.push_back(b);
    }

    for (int i = 0; i < result.size() - 1 ; i++){
        glColor3f(rand_float(0.0,1.0), rand_float(0.0,1.0), rand_float(0.0,1.0));
        glBegin(GL_POLYGON);
        result[0].drawPoint();
        result[i].drawPoint();
        result[i+1].drawPoint();
        glEnd();
    }

    glColor3f(rand_float(0.0,1.0), rand_float(0.0,1.0), rand_float(0.0,1.0));
    glBegin(GL_POLYGON);
    result[0].drawPoint();
    result[1].drawPoint();
    result[result.size() -1].drawPoint();
    glEnd();


    return result;
}
vector<vector<CPoint>> drawSphere(int rayon, double nbMeridiens, double nbParallelles){
    vector<vector<CPoint>> result;

    CPoint nord = CPoint(0,rayon,0);
    CPoint sud = CPoint(0,- rayon,0);
    glBegin(GL_POINTS);
    glColor3f(rand_float(0.0,1.0), rand_float(0.0,1.0), rand_float(0.0,1.0));
    glColor3f(rand_float(0.0,1.0), rand_float(0.0,1.0), rand_float(0.0,1.0));
    sud.drawPoint();
    glColor3f(1.0,1.0,1.0);
    glEnd();
    /* vector<CPoint> tmpnord;
    tmpnord.push_back(nord);
    result.push_back(tmpnord);*/


    for (int i = 0; i < nbParallelles; i++){
        double phi =  M_PI * i / nbParallelles;
        vector<CPoint> tmp1;
        for (int j = 0; j < nbMeridiens; j++){
            double the = 2 * M_PI * j / nbMeridiens;
            double x = rayon * sin(phi) * cos(the);
            double z = rayon * sin(phi) * sin(the);
            double y = rayon * cos(phi);
            CPoint t = CPoint(x,y,z);
            glBegin(GL_POINTS);
            t.drawPoint();
            glEnd();
            tmp1.push_back(t);
        }
        result.push_back(tmp1);
        tmp1.clear();
    }
    /*  vector<CPoint> tmpsud;
    tmpsud.push_back(sud);
    result.push_back(tmpsud);*/

    for (int i = 0; i < result.size() -1 ; i++){
        for (int j = 0;j < result[i].size() - 1 ; j++){
            glColor3f(rand_float(0.0,1.0), rand_float(0.0,1.0), rand_float(0.0,1.0));
            glBegin(GL_POLYGON);
            result[i][j].drawPoint();
            result[i+1][j].drawPoint();
            result[i+1][j+1].drawPoint();
            result[i][j+1].drawPoint();
            glEnd();
        }

    glColor3f(rand_float(0.0,1.0), rand_float(0.0,1.0), rand_float(0.0,1.0));
    glBegin(GL_POLYGON);
    result[i][0].drawPoint();
    result[i+1][0].drawPoint();
    result[i+1][nbM - 1].drawPoint();
    result[i][nbM - 1].drawPoint();
    glEnd();
    }

    for (int i = 0; i < nbMeridiens ; i++){
        glColor3f(rand_float(0.0,1.0), rand_float(0.0,1.0), rand_float(0.0,1.0));
        glBegin(GL_POLYGON);
        nord.drawPoint();
        result[0][i].drawPoint();
        result[0][i+1].drawPoint();
        glEnd();
    }

    glBegin(GL_POLYGON);
    nord.drawPoint();
    result[0][0].drawPoint();
    result[0][nbParallelles -1 ].drawPoint();
    glEnd();

    for (int i = 0; i < nbMeridiens ; i++){
        glColor3f(rand_float(0.0,1.0), rand_float(0.0,1.0), rand_float(0.0,1.0));
        glBegin(GL_POLYGON);
        sud.drawPoint();
        result[nbParallelles - 1][i].drawPoint();
        result[nbParallelles - 1][i+1].drawPoint();
        glEnd();
    }
    glBegin(GL_POLYGON);
    sud.drawPoint();
    result[nbParallelles -1 ][0].drawPoint();
    result[nbParallelles -1 ][nbMeridiens - 1].drawPoint();
    glEnd();

    return result;
}

/*
vector<vector<CPoint>> drawCercle(int nbP,int nbM){
    int rayon = 10;
    int hauteur = 20;

    vector<vector<CPoint>> result;
    for(double a = 0; a < 2*M_PI; a+=1/nbP){
    int x = hauteur+result[0].getX()+sin(a);
    int y = hauteur+result[0].getY()+cos(a);
    int z = 0;

    result[0].push_back(CPoint(x,y,z));
    }

    for(double a = 0; a < 2*M_PI; a+=1/nbP){
    int x = hauteur+result[0].getX()+sin(a);
    int y = hauteur+result[0].getY()+cos(a);
    int z = 0;

    result[1].push_back(CPoint(x,y,z));

    //
    pas oulié les poles

    phi = - 1 * M_PI /2
    omega = -1 * M_PI

    phi t = phi + 2 *M_PI * i / nbParallle
    omega _ t  = + 2 *M_PI  * i / nbMeriidien

    x = r * sin(phi t) * cos omega t
    y = r * cos phi t
    z = r * sin phi t * sin omega t
}   
}
*/

//////////////////////////////////////////////////////////////////////////////////////////
// Fonction que vous allez modifier afin de dessiner
/////////////////////////////////////////////////////////////////////////////////////////
void render_scene()
{

    // Exercice 1

    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glColor3f(1.0, 1.0, 1.0);
    glOrtho(-51.0,51.0,-51.0,51.0,-51.0,51.0);
    gluLookAt(15.0,20.0,15.0,0,10,0,0,1,0);
    vector<vector<CPoint> > cylindre;
    vector<CPoint> cone;
    vector<vector<CPoint>> sphere;
    //cylindre = drawCylindre();
    //cone = drawCone(10);
    sphere = drawSphere(20,nbM,nbN);
    /* glBegin(GL_LINE_STRIP);
    for (int i = 0; i < cercles[0].size() - 2; i++){
        glVertex3f(cercles[0][i].getX(),cercles[0][i].getY(),cercles[0][i].getZ());
        glVertex3f(cercles[0][i+1].getX(),cercles[0][i+1].getY(),cercles[0][i+1].getZ());
    }
    glEnd();


    glBegin(GL_LINE_STRIP);
    for (int i = 0; i < cercles[0].size() - 2; i++){
        glVertex3f(cercles[1][i].getX(),cercles[1][i].getY(),cercles[1][i].getZ());
        glVertex3f(cercles[1][i+1].getX(),cercles[1][i+1].getY(),cercles[1][i+1].getZ());
    }
    glEnd();


    glBegin(GL_LINE_STRIP);
    for (int i = 0; i < cercles[0].size() - 2; i++){
        glVertex3f(cercles[0][i].getX(),cercles[0][i].getY(),cercles[0][i].getZ());
        glVertex3f(cercles[1][i].getX(),cercles[1][i].getY(),cercles[1][i].getZ());
    }
    glEnd();

*/
    //---------------------------------------------------------------------
    //Définition de la couleur
    
    /* Exo 2

    glColor3f(1.0, 1.0, 1.0);
    glOrtho(-4.0,4.0,-4.0,4.0,-4.0,4.0);

    int nbM = 10;

    vector<CPoint> points;
    points = drawCone(nbM);

    glBegin(GL_LINE_STRIP);
    for (int i =0; i < points.size(); i++){
        glVertex3f(points[0].getX(),points[0].getY(),points[0].getZ());
        glVertex3f(points[i].getX(),points[i].getY(),points[i].getZ());
    }
    glEnd();

    glBegin(GL_LINE_STRIP);
    for (int i = 1; i < points.size() - 1; i++){
        glVertex3f(points[i].getX(),points[i].getY(),points[i].getZ());
        glVertex3f(points[i+1].getX(),points[i+1].getY(),points[i+1].getZ());
    }
    glEnd();
    
    */


}
