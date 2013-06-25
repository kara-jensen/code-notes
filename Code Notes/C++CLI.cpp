//////////////////////////////////////////////////////////////////////////////
//C++/CLI NOTES
//////////////////////////////////////////////////////////////////////////////
/*

VALUE-TYPE VARIABLES
� Can be both class/struct
� Can't have user-defined destructors, constructors, ass.operators
� Can't define default constructor- values zero-ed automatically
� Can only derive from interfaces as it inherits rom System::valutype

REFERENCE-TYPE VARIABLES
� Can be both class/struct
� Support all contructors including static constructors
� Only uses public inheritance

INHERITANCE
� No support for Multiple Inheritance/Base Classes, use multiple interfaces instead
� If no base class derived from, auto assumes System::Object is base

HANDLES
� Uses ^ to references objects on CLI heap
� Uses gcnew(), doesn't need delete as garbage collection takes care of it
� Track objects; if object moves due to garbage collection, address referred to is changed to stay with object
� Can't convert to or from void^
� No handle arithmatic
� Dereferences using * and ->

GCNEW
� Returns handle ^ to newly created object on CLR heap
� Has no array/placement form
� Can't be overloaded
� Throws System::OutOfMemoryException if can't allocate
� Creates two objects; one on managed stack and one on managed heap
� Managed stack object is boxed to a reference object

BOXING/UNBOXING HANDLES
� Conversion of a value (MyClass, int, float etc.) to an Object^ on the CLR heap
� Involves a bitwise copy of the original object
� Boxing is implicit, Unboxing is reverse and explicit
� Boxed copy is seperated entity from original value (copy of original)
� UnBoxed is also copied from the boxed entity
� Boxed object remembers original value, unboxing to wrong type throws exception

*/
//////////////////////////////////////////////////////////////////////////////
//CLASSES
//////////////////////////////////////////////////////////////////////////////

int main(array<System::String^> ^args){} //main entry point

//REFERENCE TYPES
ref class MyClass {};   //Methods default to private
ref struct MyStruct {}; //Methods default to public

//VALUE TYPES
value class MyClass {};   //Methods default to private
value struct MyStruct {}; //Methods default to public

//INTERFACE TYPES
interface class MyClass {};  //Methods default public
interface class MyStruct {}; //Methods default public

//ABSTRACT CLASS
//Must mark class as abstract if has any abstract methods
ref class MyClass abstract
{
public:
    virtual void Func() abstract;
};

//SEALED CLASS
//Stops class from being derived from
//Statically resolves any virtual methods as no derived classes
ref class MyClass sealed
{
};

//ABSTRACT SEALED CLASS
//Can only have static functions
ref class MyClass abstract sealed
{
public:
    static void Func();
}

//////////////////////////////////////////////////////////////////////////////
//FUNCTIONS
//////////////////////////////////////////////////////////////////////////////

//DEFAULT CONSTRUCTOR
//Implicitly created for ref/value types
ref class MyClass
{
    MyClass();
}

//STATIC CONSTRUCTOR
//Ref classes/structs only, no parameters, 
//work on static members, Private and auto called
ref class MyClass
{
    static MyClass();
}

//COPY CONSTRUCTOR
//Not implicitly created
MyClass obj2;

MyClass^ obj1 = gcnew MyClass(%obj2); //visible to native/managed
MyClass(const MyClass^ o); 

MyClass^ obj1 = gcnew MyClass(obj2); //only visible to native
MyClass(const MyClass% o);

//ASSIGNMENT OPERATOR
//Not implicitly created, only visible to native
MyClass% operator=(const MyClass% o)
{
    this->x = o.x; //copy values from o to this
    return *this;
}

//////////////////////////////////////////////////////////////////////////////
//INHERITANCE
//////////////////////////////////////////////////////////////////////////////

//REF TYPES
ref class Derived : Base {};
ref class Derived : public Base {};

//VALUE TYPES
value class Derived : MyInterface {};

//////////////////////////////////////////////////////////////////////////////
//HANDLES
//////////////////////////////////////////////////////////////////////////////

System::String^ str = "hello";   //Handle to string object on CLI heap
MyClass^ obj = nullptr;          //Set to null
MyClass^ obj = gcnew MyClass();  //Create new object (don't need delete)
obj->MyFunction();               //Calling function

//TRACKING REFERENCES (%)
//� Reference to a handler; *& in C++
MyClass^ obj = gcnew MyClass();
MyClass% obj2 = *obj; //Dereferencing gives tracking reference
MyClass^ obj3 = %obj2; //???

//PASSING HANDLES BY-REF
//without the % it would be by-val
void ChangeString(System::String^% str); 

//GCNEW
MyClass^ obj = gcnew MyClass(); 

//BOXING/UNBOXING HANDLES
Object^ boxed = 100; //int 100 implicity boxed into Object^
int i = *safe_cast<int^>(boxed) //explictly unboxed, safe_cast throws System Invalid Cast Excption if not valid

//ASSIGNING NULL
Object^ = nullptr; //must use nullptr
Object^ = 0; //doesn't set to null, implicitly boxes to int^

//BOXED PREFERENCES
[1] void MyFunction(int x);
[2] void MyFunction(double x); //and any other implicit conversions
[3] void MyFunction(int^ x); //boxing is given last preference
MyFunction(static_cast<int^>(100)); //if want boxing version, must use cast

//////////////////////////////////////////////////////////////////////////////
//EXCEPTIONS
//////////////////////////////////////////////////////////////////////////////

try
{
}
catch (Exception^)
{
}