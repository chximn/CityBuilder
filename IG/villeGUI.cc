#include "villeGUI.hh"

MaisonGUI::MaisonGUI(int x, int y, int z): m_orientation(0){
  m_position.x=x; m_position.y=y; m_position.z=z;
  m_couleur = QColor(255,0,0);
  imageMaison = QPixmap("../IG/IMG/Maison.png");
  maskStructure = imageMaison.createMaskFromColor(QColor(0, 0, 0),Qt::MaskOutColor);
  maskNeutre = imageMaison.createMaskFromColor(QColor(255, 0, 0),Qt::MaskOutColor);
  maskClair = imageMaison.createMaskFromColor(QColor(255, 51, 51),Qt::MaskOutColor);
  maskSombre = imageMaison.createMaskFromColor(QColor(170, 0, 0),Qt::MaskOutColor);
}

void MaisonGUI::setCouleur(int r,int v,int b){
  m_couleur = QColor(r,v,b);
}

RouteGUI::RouteGUI(int x1, int y1, int z1, int x2, int y2, int z2){ 
    m1_pos.x=x1; m1_pos.y=y1; m1_pos.z=z1; m2_pos.x=x2; m2_pos.y=y2; m2_pos.z=z2;
} 

VilleGUI::VilleGUI(unsigned int r, QWidget * parent, Qt::WindowFlags flags):QWidget(parent,flags), v_radius(r) {
  this->setFixedSize(1000,1000);
}

int toX(int x,int y,int z){
  return x; 
}

int toY(int x,int y,int z){
  return z+(x-(x&1))/2;
}

MaisonGUI* VilleGUI::getMaison(int x,int y,int z){
    for (auto it : maisons) {
        if ((it->getPosition().x==x) && (it->getPosition().y==y) && (it->getPosition().z==z)) return it;
    }
    return nullptr;
}

void VilleGUI::detruireMaison(int x, int y, int z){
    for (auto it = maisons.begin(); it != maisons.end(); ++it) {
        if (((*it)->getPosition().x==x) && ((*it)->getPosition().y==y) && ((*it)->getPosition().z==z)) {maisons.erase(it); return;}
    }
}

RouteGUI* VilleGUI::getRoute(int x1, int y1, int z1, int x2, int y2, int z2){
    for (auto it : routes) {
        if ((it->getPositionOrigine().x==x1) && (it->getPositionOrigine().y==y1) && (it->getPositionOrigine().z==z1) && (it->getPositionDestination().x==x2) && (it->getPositionDestination().y==y2) && (it->getPositionDestination().z==z2)) return it;
    }
    return nullptr;
}

void VilleGUI::detruireRoute(int x1, int y1, int z1, int x2, int y2, int z2){
    for (auto it = routes.begin(); it != routes.end(); ++it) {
        if (((*it)->getPositionOrigine().x==x1) && ((*it)->getPositionOrigine().y==y1) && ((*it)->getPositionOrigine().z==z1) && ((*it)->getPositionDestination().x==x2) && ((*it)->getPositionDestination().y==y2) && ((*it)->getPositionDestination().z==z2)) {routes.erase(it); return;}
    }
}

void VilleGUI::drawMap(QPainter& p, unsigned int radius) {
  p.save();
  float size = radius * 2 +1;
  size = this->height()/size;
  v_tileWidth = size*2/(sqrt(3));
  v_tileHeight = size;
  drawHexagon(p, 0, 0, 0);
  for (int r = 1; r <= (int)radius; ++r){
    for (int i = -r; i<0; ++i) {
      drawHexagon(p, r, -r-i , i);
      drawHexagon(p, -i, -r , r+i);
      drawHexagon(p, -r-i, i, r);
      drawHexagon(p, -r , r+i , -i); 
      drawHexagon(p, i, r, -r-i);      
      drawHexagon(p, r+i, -i , -r); 
      }
  }
  p.restore();
}

void VilleGUI::drawHouse(QPainter& p, MaisonGUI* M){
  float x = (this->width()/2) + toX(M->getPosition().x,M->getPosition().y,M->getPosition().z)*v_tileWidth*3.0/4;
  float y;
  if (toX(M->getPosition().x,M->getPosition().y,M->getPosition().z)%2) y = (this->height()/2) + toY(M->getPosition().x,M->getPosition().y,M->getPosition().z)*v_tileHeight + v_tileHeight/2; 
  else y = (this->height()/2) + toY(M->getPosition().x,M->getPosition().y,M->getPosition().z)*v_tileHeight; 
  p.translate(x,y);
	p.rotate(M->getOrientation());
  p.drawPixmap(QRect(-v_tileWidth/2,-v_tileHeight/2,v_tileWidth,v_tileHeight), M->getImageMaison() );
  p.setPen(M->getColor());
	p.drawPixmap(QRect(-v_tileWidth/2,-v_tileHeight/2,v_tileWidth,v_tileHeight),M->getNeutre());  
  p.setPen(M->getColor().darker());
	p.drawPixmap(QRect(-v_tileWidth/2,-v_tileHeight/2,v_tileWidth,v_tileHeight),M->getSombre());  
  p.setPen(M->getColor().lighter());
	p.drawPixmap(QRect(-v_tileWidth/2,-v_tileHeight/2,v_tileWidth,v_tileHeight),M->getClair());  
  p.rotate(-M->getOrientation());
  p.translate(-x,-y);
}

unsigned int VilleGUI::housesDistance(PositionGUI P1, PositionGUI P2){
  unsigned int x = abs(P1.x - P2.x);
  unsigned int y = abs(P1.y - P2.y);
  unsigned int z = abs(P1.z - P2.z);
  return std::max(std::max(x,y),z);
}

PositionGUI cube_round(PositionGUIF P){
    PositionGUI P2; 
    P2.x = round(P.x);
    P2.y = round(P.y);
    P2.z = round(P.z);

    int x_diff = abs(P2.x - P.x);
    int y_diff = abs(P2.y - P.y);
    int z_diff = abs(P2.z - P.z);

    if ((x_diff > y_diff) and (x_diff > z_diff))
        P2.x = -P2.y-P2.z;
    else if (y_diff > z_diff)
        P2.y = -P2.x-P2.z;
    else
        P2.z = -P2.x-P2.y;

    return P2;
}

float lerp(float a, float b, float t){ 
    return a + (b - a) * t;
}

PositionGUIF cube_lerp(PositionGUI a, PositionGUI b, float t) {
    PositionGUIF P;
    P.x = lerp(a.x, b.x, t);
    P.y = lerp(a.y, b.y, t);
    P.z = lerp(a.z, b.z, t);
    return P;
}

void VilleGUI::drawRoad(QPainter& p, RouteGUI* R){
  unsigned int distance = housesDistance(R->getPositionOrigine(),R->getPositionDestination());
  std::vector<PositionGUI> chemin;
  for (unsigned int i = 0 ; i<=distance; ++i){
    chemin.push_back(cube_round(cube_lerp(R->getPositionOrigine(),R->getPositionDestination(), 1.0/distance*i)));
  }  
  for (unsigned int i = 0; i<chemin.size()-1; ++i) {
    if (i==0) {
      drawRoadIn(p,chemin[i],chemin[i+1],true,false);
    }
    else if (i==chemin.size()-2){
      drawRoadIn(p,chemin[i],chemin[i+1],false,true);
      drawRoundAbout(p,chemin[i].x,chemin[i].y,chemin[i].z);
    }
    else {
      drawRoadIn(p,chemin[i],chemin[i+1],false,false);
      drawRoundAbout(p,chemin[i].x,chemin[i].y,chemin[i].z);
    }
  }
}

void VilleGUI::drawRoadIn(QPainter& p, PositionGUI P1, PositionGUI P2, bool start, bool end){
  float startx = (this->width()/2) + toX(P1.x,P1.y,P1.z)*v_tileWidth*3.0/4;
  float starty;
  if (toX(P1.x,P1.y,P1.z)%2) starty = (this->height()/2) + toY(P1.x,P1.y,P1.z)*v_tileHeight + v_tileHeight/2; 
  else starty = (this->height()/2) + toY(P1.x,P1.y,P1.z)*v_tileHeight;
  float endx = (this->width()/2) + toX(P2.x,P2.y,P2.z)*v_tileWidth*3.0/4;
  float endy;
  if (toX(P2.x,P2.y,P2.z)%2) endy = (this->height()/2) + toY(P2.x,P2.y,P2.z)*v_tileHeight + v_tileHeight/2; 
  else endy = (this->height()/2) + toY(P2.x,P2.y,P2.z)*v_tileHeight;
  
  int x = P2.x-P1.x;
  int y = P2.y-P1.y;
  int z = P2.z-P1.z;
  float newstartx, newstarty, newendx, newendy;
  if (x==1 and z==-1) {//NE
    newstartx = startx;
    newendx = endx,
    newstarty = starty-v_tileWidth/16;
    newendy = endy-v_tileWidth/16;
  }
  if (x==1 and y==-1) {//SE
    newstartx = startx;
    newendx = endx,
    newstarty = starty-v_tileWidth/16;
    newendy = endy-v_tileWidth/16;
  }
  if (z==1 and y==-1) {//S
    newstartx = startx-v_tileWidth/16;
    newendx = endx-v_tileWidth/16,
    newstarty = starty;
    newendy = endy;
  }
  if (z==1 and x==-1) {//SW
    newstartx = startx;
    newendx = endx,
    newstarty = starty+v_tileWidth/16;
    newendy = endy+v_tileWidth/16;
  }
  if (y==1 and x==-1) {//NW
    newstartx = startx;
    newendx = endx,
    newstarty = starty+v_tileWidth/16;
    newendy = endy+v_tileWidth/16;
  }
  if (y==1 and z==-1) {//N
    newstartx = startx+v_tileWidth/16;
    newendx = endx+v_tileWidth/16,
    newstarty = starty;
    newendy = endy;
  } 
  p.setPen(QPen(QColor(30,30,30),v_tileWidth/8));
  p.drawLine(newstartx,newstarty,newendx,newendy);
  if (v_radius>0) p.setPen(QPen(QColor(255,255,255),1));
  p.drawLine(startx,starty,endx,endy);
  if (v_radius>0) p.setPen(QPen(QColor(255,255,255),4/v_radius+1,Qt::DashLine));
  p.drawLine(newstartx,newstarty,newendx,newendy);
  p.setPen(Qt::NoPen);
}

void VilleGUI::drawRoundAbout(QPainter& p, int x, int y, int z){
  float startx = (this->width()/2) + toX(x,y,z)*v_tileWidth*3.0/4;
  float starty;
  if (toX(x,y,z)%2) starty = (this->height()/2) + toY(x,y,z)*v_tileHeight + v_tileHeight/2; 
  else starty = (this->height()/2) + toY(x,y,z)*v_tileHeight; 
  p.setBrush(QBrush(QColor(30,30,30)));
  p.drawEllipse(QRect(startx-v_tileWidth/4,starty-v_tileHeight/4,v_tileWidth/2,v_tileHeight/2));
  p.setBrush(QBrush(QColor(0,100,0)));
  p.drawEllipse(QRect(startx-v_tileWidth/10,starty-v_tileHeight/10,v_tileWidth/5,v_tileHeight/5)); 
  p.setBrush(Qt::NoBrush);
  QPen pen = QPen(QColor(255,255,255));
  if (v_radius>0) pen.setWidth(5/v_radius+1);
  p.setPen(pen); 
  p.drawArc(QRect(startx-v_tileWidth/6,starty-v_tileHeight/6,v_tileWidth/3,v_tileHeight/3), 345*16, 30*16); 
  p.drawArc(QRect(startx-v_tileWidth/6,starty-v_tileHeight/6,v_tileWidth/3,v_tileHeight/3), 45*16, 30*16); 
  p.drawArc(QRect(startx-v_tileWidth/6,starty-v_tileHeight/6,v_tileWidth/3,v_tileHeight/3), 105*16, 30*16); 
  p.drawArc(QRect(startx-v_tileWidth/6,starty-v_tileHeight/6,v_tileWidth/3,v_tileHeight/3), 165*16, 30*16); 
  p.drawArc(QRect(startx-v_tileWidth/6,starty-v_tileHeight/6,v_tileWidth/3,v_tileHeight/3), 225*16, 30*16); 
  p.drawArc(QRect(startx-v_tileWidth/6,starty-v_tileHeight/6,v_tileWidth/3,v_tileHeight/3), 285*16, 30*16); 
  p.setPen(Qt::NoPen); 
}

void VilleGUI::drawHexagon(QPainter& p, int x, int y, int z){
//Préparation de la zone de dessin 
  float h = v_tileHeight;
  float w = v_tileWidth;
  float startx = toX(x,y,z)*w*3.0/4 + this->width()/2;
  float starty;
  if (x%2) starty = toY(x,y,z)*h + this->height()/2 + h/2;
  else starty = toY(x,y,z)*h + this->height()/2;
  
	p.drawLine(startx-w/2,starty,startx-w/4,starty+h/2);
  p.drawLine(startx-w/4,starty+h/2,startx+w/4,starty+h/2);
  p.drawLine(startx+w/4,starty+h/2,startx+w/2,starty);
  p.drawLine(startx+w/2,starty,startx+w/4,starty-h/2);
  p.drawLine(startx+w/4,starty-h/2,startx-w/4,starty-h/2);
  p.drawLine(startx-w/4,starty-h/2,startx-w/2,starty);
}

void VilleGUI::drawRoads(QPainter& p){
  for (auto it:routes){
    p.save();
    drawRoad(p,it);
    p.restore();
  }
}

void VilleGUI::drawHouses(QPainter& p){
  for (auto it:maisons){
    p.save();
    drawHouse(p,it);
    p.restore();
  }
}

void VilleGUI::paintEvent(QPaintEvent *){
    QPainter p(this);
    drawMap(p,v_radius);
    drawRoads(p);
    drawHouses(p);
    p.end();
}

