#include <iostream>
#include <string>

using namespace std;

class VisualComponent{
public:
    VisualComponent(){}

    virtual void Draw() = 0;
    // virtual void Resize();
    // ...
};

// you need to have this concretecompoenent because you need the obj to pass to concreateDecorator later
class ConcreteComponent: public VisualComponent{
public:
    void Draw() override{ //you don't need virtual Draw() here because no subclass will be created out of it
        cout<<"ConcreteCompent: Draw called"<<endl;
    }
};

class Decorator: public VisualComponent{
public:
    Decorator(VisualComponent* component): _component(component){}
    virtual void Draw();
    // virtual void Resize();

private:
    VisualComponent* _component;

};

// decorator decorates the VisualComponent referenced by the _component instance variable, which is
// initialized in the constructor. For each operation in VisualComponent's interface, Decorator defines
// a default implementation that passes the request on to _component.

void Decorator::Draw(){ //this is delegation.. (IMP)
    _component->Draw();  //this is the default behaviour
}

// void Decorator::Resize(){
//     _component->Resize(); //this is the default behaviour
// }

// Subclasses of Decorator defines specific decorations. For example, the class BoarderDecorator
// adds a border to its enclosing component. BoarderDecorator is a subclass of Decorator that overrides
// the Draw operation to draw the border. BoarderDecorator also defines a private DrawBoarder helper
// operation that does the drawing. The subclass inherits all the other operation implementation from
// Decorator.

class BoarderDecorator: public Decorator{
public:
    BoarderDecorator(VisualComponent* component, int boarderwidth): Decorator(component), _width(boarderwidth){} 

    virtual void Draw();

private:
    void DrawBoader(int);
    int _width;
};

void BoarderDecorator::Draw(){
    Decorator::Draw();
    DrawBoader(_width);
}

void BoarderDecorator::DrawBoader(int boarder){
    cout<<" boarder drawn of width: "<<boarder<<endl;
}

class ScrollDecorator: public Decorator{
public:
    ScrollDecorator(VisualComponent* component, int scrollPosition): Decorator(component), _scrollPosition(scrollPosition){} 

    virtual void Draw();

private:
    void ScrollTo(int);
    int _scrollPosition;
};

void ScrollDecorator::Draw(){
    Decorator::Draw();
    ScrollTo(_scrollPosition);
}

void ScrollDecorator::ScrollTo(int Scrollto){
    cout<<"scorlled to: "<< _scrollPosition<<endl;
}


// the client code only knows about VisualCompent type, what it gets called really depends on the object it holds
void ClientCode(VisualComponent* content){
    content->Draw();
}


int main(){
    // you are getting one simple obj here so that you can wrap it around

    VisualComponent* simple = new ConcreteComponent(); 

    // now you are decorating this simple obj. OR say wrapping simple object with more functionality
    VisualComponent* obj1 = new BoarderDecorator(simple, 4);

    //now you are wrapping up obj1 with new functionality
    VisualComponent* obj2 = new ScrollDecorator(obj1, 5); 

    VisualComponent* obj3 = new ScrollDecorator(obj2, 8);

    // ClientCode(simple);
    // ClientCode(obj1);
    // ClientCode(obj2);
    ClientCode(obj3);
}
