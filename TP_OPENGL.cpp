///////////////////////////////////////////////////////////////////////////////
// Imagina
// ----------------------------------------------------------------------------
// IN - Synth�se d'images - Mod�lisation g�om�trique
// Auteur : Gilles Gesqui�re
// ----------------------------------------------------------------------------
// Base du TP 1
// programme permettant de cr�er des formes de bases.
// La forme repr�sent�e ici est un polygone blanc dessin� sur un fond rouge
///////////////////////////////////////////////////////////////////////////////  

#include <stdio.h>      
#include <stdlib.h>     
#include <math.h>
#include <iostream>
#include <vector>

/* Dans les salles de TP, vous avez g�n�ralement acc�s aux glut dans C:\Dev. Si ce n'est pas le cas, t�l�chargez les .h .lib ...
Vous pouvez ensuite y faire r�f�rence en sp�cifiant le chemin dans visual. Vous utiliserez alors #include <glut.h>. 
Si vous mettez glut dans le r�pertoire courant, on aura alors #include "glut.h" 
*/

#include "GL/glut.h" 
#include "CVector.h"
#include "CPoint.h"

using namespace std;

// D�finition de la taille de la fen�tre
#define WIDTH  480

#define HEIGHT 480

// D�finition de la couleur de la fen�tre
#define RED   0
#define GREEN 0
#define BLUE  0
#define ALPHA 1


// Touche echap (Esc) permet de sortir du programme
#define KEY_ESC 27
#define PRECISION 0.1

// Ent�tes de fonctions
void init_scene();
void render_scene();
GLvoid initGL();
GLvoid window_display();
GLvoid window_reshape(GLsizei width, GLsizei height); 
GLvoid window_key(unsigned char key, int x, int y); 


int main(int argc, char **argv) 
{  
    // initialisation  des param�tres de GLUT en fonction
    // des arguments sur la ligne de commande
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA);

    // d�finition et cr�ation de la fen�tre graphique, ainsi que son titre
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Premier exemple : carr�");

    // initialisation de OpenGL et de la sc�ne
    initGL();
    init_scene();

    // choix des proc�dures de callback pour
    // le trac� graphique
    glutDisplayFunc(&window_display);
    // le redimensionnement de la fen�tre
    glutReshapeFunc(&window_reshape);
    // la gestion des �v�nements clavier
    glutKeyboardFunc(&window_key);

    // la boucle prinicipale de gestion des �v�nements utilisateur
    glutMainLoop();

    return 1;
}

// initialisation du fond de la fen�tre graphique : noir opaque
GLvoid initGL() 
{
    glClearColor(RED, GREEN, BLUE, ALPHA);
}

// Initialisation de la scene. Peut servir � stocker des variables de votre programme
// � initialiser
void init_scene()
{
}

// fonction de call-back pour l�affichage dans la fen�tre

GLvoid window_display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    // C'est l'endroit o� l'on peut dessiner. On peut aussi faire appel
    // � une fonction (render_scene() ici) qui contient les informations
    // que l'on veut dessiner
    render_scene();

    // trace la sc�ne grapnique qui vient juste d'�tre d�finie
    glFlush();
}

// fonction de call-back pour le redimensionnement de la fen�tre

GLvoid window_reshape(GLsizei width, GLsizei height)
{  
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // ici, vous verrez pendant le cours sur les projections qu'en modifiant les valeurs, il est
    // possible de changer la taille de l'objet dans la fen�tre. Augmentez ces valeurs si l'objet est
    // de trop grosse taille par rapport � la fen�tre.
    glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);

    // toutes les transformations suivantes s�appliquent au mod�le de vue
    glMatrixMode(GL_MODELVIEW);
}

// fonction de call-back pour la gestion des �v�nements clavier

GLvoid window_key(unsigned char key, int x, int y) 
{  
    switch (key) {
    case KEY_ESC:
        exit(1);
        break;

    default:
        printf ("La touche %d n�est pas active.\n", key);
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

//////////////////////////////////////////////////////////////////////////////////////////
// Fonction que vous allez modifier afin de dessiner
/////////////////////////////////////////////////////////////////////////////////////////
void render_scene()
{


    glOrtho(-4.0,4.0,-4.0,4.0,-4.0,4.0);
    CPoint p0,p1,p2,p3,p4;

    double nbu = 20;

    p0 = CPoint(0,0,0);
    p1 = CPoint(1,1,0);
    p2 = CPoint(2,1,0);
    p3 = CPoint(3,0,0);
    p4 = CPoint(4,3,0);

    vector<CPoint> points;
    points.push_back(p0);
    points.push_back(p1);
    points.push_back(p2);
    points.push_back(p3);
    points.push_back(p4);

    for (int i = 0; i < points.size(); i++)
        cout << points[i].getX() << "." << points[i].getY() << "." << points[i].getZ() << endl;

    glColor3f(1.0,0.0,0.0);
    DrawCurve(points);

    glColor3f(1.0,1.0,1.0);
    vector<CPoint> result;
    result = BezierCurveByCasteljau(points,nbu);

    DrawCurve(result);



    //---------------------------------------------------------------------

    /* tp3 exo 1

    glOrtho(-3.5,3.5,-3.5,3.5,-3.5,3.5);
    CPoint p0,p1,p2,p3,p4;

    double nbu = 40;

    p0 = CPoint(0,0,0);
    p1 = CPoint(1,1,0);
    p2 = CPoint(2,1,0);
    p3 = CPoint(3,0,0);
    p4 = CPoint(4,3,0);

    vector<CPoint> points;
    points.push_back(p0);
    points.push_back(p1);
    points.push_back(p2);
    points.push_back(p3);
    points.push_back(p4);

    for (int i = 0; i < points.size(); i++)
        cout << points[i].getX() << "." << points[i].getY() << "." << points[i].getZ() << endl;

    glColor3f(1.0,1.0,1.0);

    CVector v = CVector(2,-1,0);
    v.drawLine(p0.getX(), p0.getY(), p0.getZ());

    vector<vector<CPoint>> courbes;

    courbes = traceSurfaceCylindrique(points,v,nbu,nbu);
    for(int i = 0; i < courbes.size(); i++){
        DrawCurve(courbes[i]);
    }
*/
    //---------------------------------------------------------------------
    //D�finition de la couleur
    glColor3f(1.0, 1.0, 1.0);

    //  Nous cr�ons ici un polygone. Nous pourrions aussi cr�er un triangle ou des lignes. Voir ci-dessous les parties
    // en commentaires (il faut commenter le bloc qui ne vous int�resse pas et d�commenter celui que vous voulez tester.

    // Cr�ation de deux lignes
    /*glColor3f(0,1.0,0);
    glBegin(GL_LINES);
        glVertex3f(-1, -1, 0);
        glVertex3f(1, 1, 0);
        glVertex3f(1, -1, 0);
        glVertex3f(-1, 1, 0);
    glEnd();
  */
    // cr�ation d'un polygone
    /*	glBegin(GL_POLYGON);
        glVertex3f(-1, -1, 0);
        glVertex3f(1, -1, 0);
        glVertex3f(1, 1, 0);
        glVertex3f(-1, 1, 0);
    glEnd();
*/


    /*
// cr�ation d'un triangle
    glBegin(GL_TRIANGLES);
        glVertex3f(-1, -1, 0);
        glVertex3f(1, -1, 0);
        glVertex3f(1, 1, 0);
    glEnd();
*/



}
