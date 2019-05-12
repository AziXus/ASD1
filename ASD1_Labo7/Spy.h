#ifndef Spy_h
#define Spy_h

#include <iostream>

class Spy {
    friend std::ostream& operator<<(std::ostream& os, const Spy& I);

protected:
    int _i;

public:
    static bool verbose;
    static int constructorBombValue;
    static int affectationBombValue;

    Spy();
    Spy(int i);
    Spy(const Spy& I);
    Spy(Spy&& I);
    virtual ~Spy();
    Spy& operator=(const Spy& I);
    Spy& operator=(Spy&& I);
};

class Unmovable {
    friend std::ostream& operator<<(std::ostream& os, const Unmovable& I);
private:
    Spy spy;
public:
    Unmovable() = default;
    Unmovable(int i) : spy(i) {};
    Unmovable(const Unmovable& m)  = default;
    Unmovable& operator=(const Unmovable& m) = default;
};

class Movable {
    friend std::ostream& operator<<(std::ostream& os, const Movable& I);
private:
    Spy spy;
public:
    Movable() = default;
    Movable(int i) : spy(i) {};
    Movable(const Movable& m)  = default;
    Movable(Movable&& m)  = default;
    Movable& operator=(const Movable& m) = default;
    Movable& operator=(Movable&& I) = default;
};

std::ostream& operator<<(std::ostream& os, const Spy& I);
std::ostream& operator<<(std::ostream& os, const Movable& I);
std::ostream& operator<<(std::ostream& os, const Unmovable& I);

#endif
