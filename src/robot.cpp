

#include "robot.hpp"

Robot::Robot() :
_corp(sf::Vector2f(400,290)),
_roueGauche(sf::Vector2f(60,110)),
_roueDroite(sf::Vector2f(60,110)),
_bumper(30)
{
  _color= sf::Color(217,49,53,255);
  setupGraphics();
}

Robot::~Robot(){
}

void Robot::draw (sf::RenderTarget &target, sf::RenderStates states) const
{
  states.transform *= getTransform();
  target.draw(_corp,states);
  target.draw(_roueGauche,states);
  target.draw(_roueDroite,states);
  target.draw(_bumper,states);
}

void Robot::setupGraphics()
{
  _corp.setFillColor(_color);
  _corp.setOutlineColor(sf::Color(127,127,127,200));
  //_corp.setOutlineThickness(30);
  _roueGauche.setFillColor(sf::Color(30,30,30,255));
  _roueGauche.setOutlineColor(sf::Color(127,127,127,200));
  //_roueGauche.setOutlineThickness(10);
  _roueDroite.setFillColor(sf::Color(30,30,30,255));
  _roueDroite.setOutlineColor(sf::Color(127,127,127,200));
  //_roueDroite.setOutlineThickness(10);
  _bumper.setFillColor(sf::Color(50,50,50,255) + _color);
  _bumper.setOutlineColor(sf::Color(127,127,127,255));
  //_bumper.setOutlineThickness(10);
  
  
  _corp.setOrigin(_corp.getSize()*0.5f);
  _roueGauche.setOrigin(sf::Vector2f(_corp.getSize().x*0.5f+_roueGauche.getSize().x*0.8f
                                     ,_roueGauche.getSize().y*0.5f));                                
                                     
  _roueDroite.setOrigin(sf::Vector2f(-_corp.getSize().x*0.5f+_roueDroite.getSize().x*0.2f
                                     ,_roueDroite.getSize().y*0.5f));
                                                                      
  _bumper.setOrigin(sf::Vector2f(_bumper.getRadius(),-(_corp.getSize().y/2)+2*_bumper.getRadius()));
}

AbstractRobot* AbstractRobot::createFromName(std::string name)
{
	if (name=="EchecCritique")
    return new EchecCritique();
	return new Robot();
}

bool AbstractRobot::extract(sf::Packet& packet)
{
	sf::Int16 x,y;
	sf::Int16 theta;
	if (! (packet >> _state)) return false; //uint8
	if (! (packet >> x)) return false;      //int16
	if (! (packet >> y)) return false;      //int16
	if (! (packet >> theta)) return false;  //int16
	if (! (packet >> _color.r)) return false;  //uint8
	if (! (packet >> _color.g)) return false;  //uint8
	if (! (packet >> _color.b)) return false;  //uint8
	
	this->setPosition(sf::Vector2f(x,y)); //en millimetres
	this->setRotation(theta/10.f);        //en dixiemes de degrés
	
	if (!( this->extractExtraInfos(packet))) return false;//selon le robot
	
	this->setupGraphics();
	return true;
}


EchecCritique::EchecCritique() :
_corp(8),
_roueGauche(sf::Vector2f(28,65)),
_roueDroite(sf::Vector2f(28,65)),
_bumper(12.5)
{
  _corp.setPoint(0, sf::Vector2f(37, 0));
  _corp.setPoint(1, sf::Vector2f(400-37, 0));
  _corp.setPoint(2, sf::Vector2f(400, 37));
  _corp.setPoint(3, sf::Vector2f(400, 175));
  _corp.setPoint(4, sf::Vector2f(400-115, 290));
  _corp.setPoint(5, sf::Vector2f(115, 290));
  _corp.setPoint(6, sf::Vector2f(0, 175));
  _corp.setPoint(7, sf::Vector2f(0, 37));
  _color= sf::Color(192,195,195,50);
  setupGraphics();
}

EchecCritique::~EchecCritique(){
}

void EchecCritique::draw (sf::RenderTarget &target, sf::RenderStates states) const
{
  states.transform *= getTransform();
  target.draw(_roueGauche,states);
  target.draw(_roueDroite,states);
  target.draw(_corp,states);
  target.draw(_bumper,states);
}

void EchecCritique::setupGraphics()
{
  this->setScale(sf::Vector2f(1.f,-1.f));
  _corp.setFillColor(_color);
  _corp.setOutlineColor(sf::Color(127,127,127,255));
  _corp.setOutlineThickness(10);
  _roueGauche.setFillColor(sf::Color(30,30,30,255));
  _roueGauche.setOutlineColor(sf::Color(127,127,127,200));
  //_roueGauche.setOutlineThickness(10);
  _roueDroite.setFillColor(sf::Color(30,30,30,255));
  _roueDroite.setOutlineColor(sf::Color(127,127,127,200));
  //_roueDroite.setOutlineThickness(10);
  _bumper.setFillColor(sf::Color(250,50,50,255));
  _bumper.setOutlineColor(sf::Color(127,127,127,255));
  //_bumper.setOutlineThickness(10);
  
  
  _corp.setOrigin(sf::Vector2f(400*0.5f,290*0.5f));
  _roueGauche.setOrigin(sf::Vector2f(400*0.5f+_roueGauche.getSize().x*0.8f
                                     ,_roueGauche.getSize().y*0.5f));                                
                                     
  _roueDroite.setOrigin(sf::Vector2f(-100+_roueDroite.getSize().x*0.5f,
                                      _roueDroite.getSize().y*0.5f));
  _roueGauche.setOrigin(sf::Vector2f(100+_roueGauche.getSize().x*0.5f,
                                     _roueGauche.getSize().y*0.5f));
                                                                      
  _bumper.setOrigin(sf::Vector2f(_bumper.getRadius(),-(290/2)+2*_bumper.getRadius()));
}