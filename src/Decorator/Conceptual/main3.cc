#include <iostream>
#include <string>

using namespace std;

class Beverage{
public:
    Beverage(){}
    Beverage(string str):Description(str){}
    /*
    * we don't need to abstract it here becasue we don't want every subclass of it redefine it.
    * since description is already updated in the Description variable, we only redefine whereever it is needed.
    * 
    */
    virtual string getDescription(){
        return Description;
    }
    virtual float cost() = 0; // we are abstracting it so that each subclass needs to define it

protected:
    string Description;
};


/*
* you might not need ConcreateComponent as compared to VirtualComponent of main2 becasue you have already
* subclasses like Expresso, Decaf etc which inherits from Beverage. We can use this one while we Instantiate
* decoratory type obj which is needed so that we can wrap it later 
*/
// class ConcreateComponent: public Beverage{
// public:
//     ConcreateComponent():Beverage("concreateComponent"){}

//     string getDescription(){
//         cout<<Description<<endl;
//     }
// };

class Decorator: public Beverage{
public:

    Decorator(Beverage* beverage):_Beverage(beverage){}
    
    //we are going to require that the subclass of Decorator reimplement the getDescription method
    virtual string getDescription() = 0;
    virtual float cost() = 0;
protected:
    Beverage* _Beverage;
};


class Expresso: public Beverage{
public:
    Expresso():Beverage("Expresso"){}

    float cost() override{
        return 1.9;
    }
/*
* we don't want to repeat the following code, so we have not abstracted out getDescription() in Beverage.
*/
    // string getDescription() override{
    //     return Description;
    // }
};


class Decaf: public Beverage{
public:
    Decaf():Beverage("Decaf"){}

    float cost() override{
        return 2.1;
    }
};

class DarkRoast: public Beverage{
public:
    DarkRoast():Beverage("DarkRoast"){}

    float cost() override{
        return 0.9;
    }
};

class Mocha: public Decorator{
public:
    Mocha(Beverage* beverage):Decorator(beverage){}

    string getDescription() override{
        return _Beverage->getDescription() + " MOcha";
    }

    float cost() override{
        return _Beverage->cost() + .89; // .89 is Mocha's cost
    }
};

class Soy: public Decorator{
public:
    Soy(Beverage* beverage):Decorator(beverage){}

    string getDescription() override{
        return _Beverage->getDescription() + " Soy";
    }

    float cost() override{
        return _Beverage->cost() + .9; // .9 is soy's cost
    }
};

class Milk: public Decorator{
public:
    Milk(Beverage* beverage):Decorator(beverage){}

    string getDescription() override{
        return _Beverage->getDescription() + " Milk";
    }

    float cost() override{
        return _Beverage->cost() + .01; // .o1 is milk's cost
    }
};


void StarbuzzCoffee(Beverage* beverage)
{
    cout<< beverage->getDescription() + " $" << beverage->cost()<< endl;
}


int main ()
{
    Beverage*  beverage = new Expresso();  
    StarbuzzCoffee(beverage);

    // make a DarkRoast obj
    Beverage* beverage2 = new DarkRoast();
    
    // wrap it with Mocha
    beverage2 = new Mocha(beverage2);

    //wrap it with second mocha
    beverage2 = new Mocha(beverage2); 

    //wrap it with milk
    beverage2 = new Milk(beverage2); 

    StarbuzzCoffee(beverage2);
}

/*
* output:

    Expresso $1.9
    DarkRoast MOcha MOcha Milk $2.69
*/