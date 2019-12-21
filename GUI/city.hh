#include <iostream>
#include <vector>
#include <cmath>
#include <QtGui>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QLayout>


struct CouleurGUI {
    int rouge;
    int vert;
    int bleu;
};

struct PositionGUI {
    int x;
    int y;
    int z;
};

struct PositionGUIF {
    float x;
    float y;
    float z;
};

class MaisonGUI {
private:
    PositionGUI m_position;
    int m_orientation;
    QColor m_couleur;
		QPixmap imageMaison;
		QBitmap maskStructure;
		QBitmap maskSombre;
		QBitmap maskClair;
		QBitmap maskNeutre;

public:
    MaisonGUI(int x, int y, int z);
    ~MaisonGUI() {}
    void setCouleur(int r,int v,int b); 
    CouleurGUI getCouleur() {CouleurGUI C; C.rouge = m_couleur.red(); C.vert = m_couleur.green(); C.bleu = m_couleur.blue();  return C;}
    QColor getColor() {return m_couleur;}
    void setOrientation(int o) {m_orientation=o;}
    int getOrientation() {return m_orientation;}
    void setPosition(int x, int y, int z) {m_position.x=x; m_position.y=y; m_position.z=z;}
    PositionGUI getPosition() {return m_position;}
    QPixmap getImageMaison() {return imageMaison;}
    QBitmap getStructure() {return maskStructure;}
    QBitmap getSombre() {return maskSombre;}
    QBitmap getClair() {return maskClair;}
    QBitmap getNeutre() {return maskNeutre;}
};

class RouteGUI {
private:
    PositionGUI m1_pos;
    PositionGUI m2_pos;

public:
    RouteGUI(int i, int j, int k, int x, int y, int z);
    ~RouteGUI() {}
    void setDestination(int x, int y, int z) {m2_pos.x = x; m2_pos.y = y; m2_pos.z = z;}
    PositionGUI getPositionDestination() {return m2_pos;}
    void setOrigine(int x, int y, int z) {m1_pos.x = x; m1_pos.y = y; m1_pos.z = z;}
    PositionGUI getPositionOrigine() {return m1_pos;}
};



class VilleGUI:public QWidget {
    Q_OBJECT
private:
    unsigned int v_radius;
    float v_tileHeight;
    float v_tileWidth;
    std::vector<MaisonGUI*> maisons;
    std::vector<RouteGUI*> routes;

protected:
    void paintEvent(QPaintEvent *event) override;

public:
    VilleGUI(unsigned int r=5, QWidget * parent=0, Qt::WindowFlags flags=0);
    ~VilleGUI() {}

    void setRadius(unsigned int r) {v_radius = r;}
    unsigned int getRadius() {return v_radius;}
    void construireMaison(int x, int y, int z) {maisons.push_back(new MaisonGUI(x,y,z));}
    void construireRoute(int x1, int y1, int z1, int x2, int y2, int z2) {routes.push_back(new RouteGUI(x1,y1,z1,x2,y2,z2));}
    void detruireMaison(int x, int y, int z);
    void detruireRoute(int x1, int y1, int z1, int x2, int y2, int z2);
    MaisonGUI* getMaison(int x, int y, int z);
    RouteGUI* getRoute(int x1, int y1, int z1, int x2, int y2, int z2);
    CouleurGUI getCouleur(int x, int y, int z) {return getMaison(x, y, z)->getCouleur();}
    void setCouleur(int x, int y, int z, int r, int g, int b) {getMaison(x, y, z)->setCouleur(r,g,b);}
    int getOrientation(int x, int y, int z) {return getMaison(x, y, z)->getOrientation();}
    void setOrientation(int x, int y, int z, int o) {getMaison(x, y, z)->setOrientation(o);}
    unsigned int getRayon() {return v_radius;}
    void setRayon(unsigned int r) {v_radius = r;}

    //DRAWING
    unsigned int housesDistance(PositionGUI P1, PositionGUI P2);
    void drawHexagon(QPainter& p, int x, int y, int z);
    void drawHouses(QPainter& p);
    void drawRoads(QPainter& p);
    void drawHouse(QPainter& p, MaisonGUI* M);
    void drawRoad(QPainter& p, RouteGUI* R);
    void drawRoadIn(QPainter& p, PositionGUI P1, PositionGUI P2, bool start, bool end);
    void drawRoundAbout(QPainter& p, int x, int y, int z);
    void drawMap(QPainter& p, unsigned int r);      
};
