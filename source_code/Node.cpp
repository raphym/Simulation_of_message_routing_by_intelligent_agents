#include "Node.h"

using namespace std;
static int next_id=0;

Node::Node(string type,string n,double x, double y) //ctor
{
        this->type=type;
        name = new string(n);
        locationX = x;
        locationY = y;
        id=next_id;
        next_id= next_id + 1;
        isBusy= false;
        isErased=false;
}

Node::~Node() //dtor
{
        delete name;
}
int Node::getId()
{
        return id;
}
string Node::getName()
{
        return *name;
}

double Node::getLocationX()
{
        return locationX;
}

double Node::getLocationY()
{
        return locationY;
}

string Node::getType()
{
        return type;
}

bool Node::checkIfBusy()
{
        return isBusy;
}

void Node::setIsBusy(bool b)
{
        isBusy=b;
}

bool Node::checkIfErased()
{
        return isErased;
}

void Node::erase()
{
        isErased=true;
}
void Node::send(int message,int idSource,int idDest)
{
        bool sent=false;
        int i=0;
        for(i=0; i<vecAvailableNodes.size(); i++)
        {
                if(this->vecAvailableNodes[i]->id == idDest  && this->isBusy==false)
                {
                        this->isBusy=true;
                        sent=true;
                        this->vecAvailableNodes[i]->receive(message,idSource,idDest);
                        break;
                }
        }

        if (sent == false)
        {
                cout << "Sorry ,there is no way for this moment. ";
                cout << "The node with id: "<< idSource << " cannot send any message ";
                cout << "to the node with the id: " << idDest <<endl;
        }
}

void Node::receive(int message,int idSource,int idDest)
{
        int i;
        if(this->id == idDest)
        {
                cout << "The node with id: "<< this->id << " receive message number "<<message;
                cout << " From the node with the id :" << idSource <<endl;

                for(i=0; i<vecAvailableNodes.size(); i++)
                {
                        if(vecAvailableNodes[i]->id==idSource)
                                vecAvailableNodes[i]->isBusy=false;
                }
        }
}


void Node::scanHotspots(vector<Node*> vecNodes)
{
  //the function check if a node is near to an another with a distance of 40 metters
  //I calculate according to the  Pythagorean theorem a^2+b^2 = c^2 < 40^2
        if (this->vecAvailableNodes.size()!=0)
                vecAvailableNodes.clear();

        double diffX=0;
        double diffY=0;
        double result=0;

        for(int i=0; i< vecNodes.size(); i++)
        {
                if(vecNodes[i]->checkIfErased()==true)
                        continue;
                diffX = abs(vecNodes[i]->getLocationX() - this->getLocationX());
                diffY = abs(vecNodes[i]->getLocationY() - this->getLocationY());
                result = sqrt( pow(diffX, 2) + pow(diffY, 2) );

                if(result <= 40 && this->getId() != vecNodes[i]->getId())
                        vecAvailableNodes.push_back(vecNodes[i]);
        }
}

// void Node::printAvailableNodes()
// {
//         if(vecAvailableNodes.size()==0)
//                 cout << "[]" << endl;
//         for(int i=0; i<vecAvailableNodes.size(); i++)
//         {
//                 if (i==0 && i == vecAvailableNodes.size()-1)
//                         cout << "[" <<  vecAvailableNodes[0]->getName()<< "(id:"<<vecAvailableNodes[0]->id<<")"<< "]" <<endl;
//
//                 else if (i==0)
//                         cout << "[" <<  vecAvailableNodes[0]->getName()<< "(id:"<<vecAvailableNodes[0]->id<<")"<< ",";
//
//                 else if (i==vecAvailableNodes.size() -1 )
//                         cout << vecAvailableNodes[i]->getName()<< "(id:"<<vecAvailableNodes[i]->id<<")"<< "]"<<endl;
//
//                 else
//                         cout << vecAvailableNodes[i]->getName()<< "(id:"<<vecAvailableNodes[i]->id<<")" << ",";
//         }
// }

void Node::printAvailableNodes()
{
        if(vecAvailableNodes.size()==0)
                cout << "[]" << endl;
        for(int i=0; i<vecAvailableNodes.size(); i++)
        {
                if (i==0 && i == vecAvailableNodes.size()-1)
                        cout << "[" <<  vecAvailableNodes[0]->getName()<< "]" <<endl;

                else if (i==0)
                        cout << "[" <<  vecAvailableNodes[0]->getName()<< ",";

                else if (i==vecAvailableNodes.size() -1 )
                        cout << vecAvailableNodes[i]->getName()<< "]"<<endl;

                else
                        cout << vecAvailableNodes[i]->getName() << ",";
        }
}

std::vector<Node*> Node::getVectAvailableNodes()
{
        return vecAvailableNodes;
}
