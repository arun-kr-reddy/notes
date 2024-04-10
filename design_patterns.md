# design patterns
- [introduction](#introduction)
- [creational](#creational)
  - [factory method](#factory-method)
  - [abstract factory](#abstract-factory)
  - [builder](#builder)
  - [prototype](#prototype)
  - [singleton](#singleton)
- [structural](#structural)
  - [adapter](#adapter)
  - [bridge](#bridge)
  - [composite](#composite)
  - [decorator](#decorator)
  - [facade](#facade)
  - [flyweight](#flyweight)
  - [proxy](#proxy)
- [behavioral](#behavioral)
  - [chain of responsibility](#chain-of-responsibility)
  - [command](#command)
  - [iterator](#iterator)
  - [interpreter](#interpreter)
  - [mediator](#mediator)
  - [memento](#memento)
  - [observer](#observer)
  - [state](#state)
  - [strategy](#strategy)
  - [template method](#template-method)
  - [visitor](#visitor)

## links  <!-- omit from toc -->
- [derek banas](https://www.youtube.com/playlist?list=PLF206E906175C7E07)
- [refactoring guru](https://refactoring.guru/design-patterns/catalog)

## todo  <!-- omit from toc -->

## introduction
- a class is a blueprint  
fields (instance variables) are what an object knows  
methods (functions) are what an object does
- abstract out features that are common for subclasses into the superclass, only override or extend methods that don't work  
fields and methods are already defined when you extend/inherit the superclass, you only define the changes/additions
  ```cpp
  class animalClass  // superclass
  {
  private:
      std::string name;
      uint32_t height;
      uint32_t weight;

  public:
      animalClass(){};
      ~animalClass(){};
      void eat(){};
      void move(){};
      void setName(){};
      void getName(){};
  };

  class birdClass : public animalClass  // subclass 1
  {
      void move() override{};  // override
  };

  class dogClass : public animalClass  // subclass 2
  {
      void digHole() override{};  // extend
  };
  ```
- `is a` principle to decide if a class should be extended/inherited, example: `dog` is a `animal`  
here most/all of the superclass methods are needed by the subclass, any change to superclass code is instantly reflected in subclasses  
`has a` principle to decide if something is a field, example: `dog` has a `height`

[continue](https://www.youtube.com/watch?v=yRJ1rRoMnIM&list=PLF206E906175C7E07&index=2)

## creational

### factory method

### abstract factory

### builder

### prototype

### singleton

## structural

### adapter

### bridge

### composite

### decorator

### facade

### flyweight

### proxy


## behavioral

### chain of responsibility

### command
- **command pattern:** turns a request into a stand-alone object that contains all information about the request, this transformation lets you pass requests as a method arguments, delay or queue a request’s execution, and support undoable operations

### iterator

### interpreter

### mediator

### memento

### observer

### state

### strategy

### template method

### visitor