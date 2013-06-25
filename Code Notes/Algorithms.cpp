﻿///////////////////////////////////////////////////////////////////////////////////////////////////////
//CHANGING RANGES
///////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T>
T ChangeRange(T value, T currentRangeInner, T currentRangeOuter, T newRangeInner, T newRangeOuter)
{
    return ((value-currentRangeInner)*((newRangeOuter-newRangeInner)/
        (currentRangeOuter-currentRangeInner)))+newRangeInner;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
//CONVERT STRINGS
/////////////////////////////////////////////////////////////////////////////////////////////////////// 

template<typename T>
std::string StringCast(const T& value)
{
    std::ostringstream stream;
    stream << value;
    return stream.str();
}

char buffer[256];
sprintf_s(buffer,"%i hello",5);
string str = buffer;

// Inline conversion
static_cast<std::stringstream&>(std::stringstream() << myInt).str()

// convert wide/strings
std::string str(wstr.begin(),  wstr.end());
std::wstring wstr(nstr.begin(), nstr.end());

///////////////////////////////////////////////////////////////////////////////////////////////////////
//CAPS A VALUE BETWEEN MIN/MAX
///////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T>T CapValue(T value, T minValue, T maxValue)
{
    value = std::min(value, maxValue);
    value = std::max(value, minValue);
    return value;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
//REVERSE LETTERS IN A STRING
///////////////////////////////////////////////////////////////////////////////////////////////////////

char test[] = "this is a test";
char saved;
int l = strlen(test);
for(int i = 0; i < l/2; ++i)
{
    saved = test[i];
    test[i] = test[l-i-1];
    test[l-i-1] = saved;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
//GET 1D INDEX FROM 2D COORD
///////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T>
int GetIndex(T MaxCols, T RowNumber, T ColNumber){ return int((MaxCols*RowNumber)+ColNumber); }

for(int c = 0; c < MaxCols; ++c)
{
    for(int r = 0; r < MaxRows; ++r)
    {
        int index = (MaxCols*r)+c;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
//CREATE 2D GRID
/////////////////////////////////////////////////////////////////////////////////////////////////////// 

for(int r = 0; r < Rows; r++)
{
    for(int c = 0; c < Cols; c++)
    {
        FLOAT3 position;
        position.x = x + (r*w);
        position.z = z + (c*h);
        postions.push_back(position);
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
//ANGLES CONVERSION
///////////////////////////////////////////////////////////////////////////////////////////////////////

#define _USE_MATH_DEFINES
#include <math.h>

float PolarPHI(float z, float length){ return (asin(z/length)); }
float PolarTHETA(float x, float y){ return (atan(y/x)); }
float CartesianX(float length, float phi, float theta){ return (length*cos(phi)*cos(theta)); }
float CartesianY(float length, float phi, float theta){ return (length*cos(phi)*sin(theta)); }
float CartesianZ(float length, float phi){ return (length*sin(phi)); }

/**
* Converts degrees to radians
*/
template<typename T> T DegToRad(T degrees)
{
    return static_cast<T>(M_PI/180.0)*degrees;
}
/**
* Converts radians to degrees
*/
template<typename T> T RadToDeg(T radians)
{
    return static_cast<T>(180.0/M_PI)*radians;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
//RESETTING BAD CONSOLE INPUT
///////////////////////////////////////////////////////////////////////////////////////////////////////

while(!(cin >> x))
{
    cout << "Bad input. Please enter a number: ";
    cin.clear();
    while (cin.get() != '\n')
        continue;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
//TIMER DELAY LOOP
///////////////////////////////////////////////////////////////////////////////////////////////////////

clock_t delay = NoOfSeconds * CLOCKS_PER_SEC; 
clock_t start = clock(); //set the start of the time
while ((clock() - start) < delay ) // calculate the difference
    continue;

///////////////////////////////////////////////////////////////////////////////////////////////////////
//GETTING COLOR COMPONENTS VIA BIT SHIFTING
///////////////////////////////////////////////////////////////////////////////////////////////////////

unsigned int c;
int r = c & 0xFF;
int g = (c>>8) & 0xFF;
int b = (c>>16) & 0xFF;
int a = (c>>24) & 0xFF;

///////////////////////////////////////////////////////////////////////////////////////////////////////
//WINDOWS ERROR MESSAGE POPUP
///////////////////////////////////////////////////////////////////////////////////////////////////////

MessageBox(nullptr, TEXT(error), TEXT("ERROR"), MB_OK);

///////////////////////////////////////////////////////////////////////////////////////////////////////
//BOOST GET VALUE FROM PTREE
///////////////////////////////////////////////////////////////////////////////////////////////////////

/**
* Gets the correct value depending on if it exists in the tree
* @param the tree to check 
* @param the default value to use if name is not found
* @param the name of the node to search
* @return the chosen value from either the tree or defaultValue
*/
template<typename T>
T GetValue(boost::property_tree::ptree::iterator& it, 
    T defaultValue, char* node);

template<typename T> 
T LightEditor::GetValue(boost::property_tree::ptree::iterator& it, T defaultValue, char* node)
{
    int count = it->second.count(node);
    if(count > 0)
    {
        if(count > 1)
        {
            Logger::LogInfo(std::string("Warning: node ") + node + " is duplicated");
        }
        return boost::lexical_cast<T>(it->second.get_child(node).data());
    }
    return defaultValue;
}