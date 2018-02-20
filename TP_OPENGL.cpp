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

#include "GL/glut.h" 
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
vector<vector<CPoint>> traceSurfaceCylindrique(vector<CPoint> points, CVector v1, long nbv,long nbu){
    vector<vector<CPoint>> result;
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

vector<vector<CPoint>> drawCylindre(){
    int hauteur = 20;
    int rayon = 10;
    int nbMeridiens = 10;

    vector<CPoint> result;

    for(double a = 0; a < 2*M_PI; a+=1/10){
    int x = sin(a);
    int y = cos(a);
    int z = 0;

    result.push_back(CPoint(x,y,z));

}

   for(double a = 0; a < 2*M_PI; a+=1/10){
    int x = hauteur+sin(a);
    int y = hauteur+cos(a);
    int z = 0;

    result.push_back(CPoint(x,y,z));
}


return result;

}

vector<CPoint> drawCone(int n){
    int rayon = 15;
    int hauteur = 20;

    vector<CPoint> result;
    result.push_back(CPoint(0,0,20));


  for(double a = 0; a < 2*M_PI; a+=1/n){
    int x = hauteur+result[0].getX()+sin(a);
    int y = hauteur+result[0].getY()+cos(a);
    int z = 0;

    result.push_back(CPoint(x,y,z));
}    

}

//////////////////////////////////////////////////////////////////////////////////////////
// Fonction que vous allez modifier afin de dessiner
/////////////////////////////////////////////////////////////////////////////////////////
void render_scene()
{

    /*    Exercice 1 
    glOrtho(-4.0,4.0,-4.0,4.0,-4.0,4.0);
    
    vector<vector<CPoint>> cercles;
    cercles = drawCylindre();

    glBegin(GL_LINE_STRIP);
    for (int i = 0; i < cercles.size() - 1; i++){
        glVertex3f(cercles[0].get(i).getX(),cercles[0].get(i).getY(),cercles[0].get(i).getZ());
        glVertex3f(cercles[0].get(i+1).getX(),cercles[0].get(i+1).getY(),cercles[0].get(i+1).getZ());
    }
    glEnd();


    glBegin(GL_LINE_STRIP);
    for (int i = 0; i < cercles.size() - 1; i++){
        glVertex3f(cercles[1].get(i).getX(),cercles[1].get(i).getY(),cercles[1].get(i).getZ());
        glVertex3f(cercles[1].get(i+1).getX(),cercles[1].get(i+1).getY(),cercles[1].get(i+1).getZ());
    }
    glEnd();


    glBegin(GL_LINE_STRIP);
    for (int i = 0; i < cercles.size() - 1; i++){
        glVertex3f(cercles[0].get(i).getX(),cercles[0].get(i).getY(),cercles[0].get(i).getZ());
        glVertex3f(cercles[1].get(i).getX(),cercles[1].get(i).getY(),cercles[1].get(i).getZ());
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

    
    glColor3f(1.0, 1.0, 1.0);
    glOrtho(-4.0,4.0,-4.0,4.0,-4.0,4.0);
}
