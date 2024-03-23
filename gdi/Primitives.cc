#include <node.h>
#include <windows.h>
#include <objidl.h>
#include <gdiplus.h>
#include <map>

using namespace Gdiplus;
#pragma comment(lib, "Gdiplus.lib")

namespace NodeGDI
{
    using v8::Exception;
    using v8::FunctionCallbackInfo;
    using v8::Isolate;
    using v8::Local;
    using v8::Number;
    using v8::Object;
    using v8::String;
    using v8::Value;

    class DrawObject
    {
    protected:
        int X;
        int Y;
        int Width;
        int Heigth;

    public:
        void Draw(HDC hdc){};
        DrawObject(int x = 0, int y = 0, int width = 50, int height = 50)
        {
            this->X = x;
            this->Y = y;
            this->Width = width;
            this->Heigth = height;
        }
        void SetLocation(int x, int y)
        {
            this->X = x;
            this->Y = y;
        }
    };

    class Rectangle : public DrawObject
    {
    protected:
        int X;
        int Y;
        int Width;
        int Heigth;

    public:
        Rectangle(int x = 0, int y = 0, int width = 50, int height = 50)
        {
            this->X = x;
            this->Y = y;
            this->Width = width;
            this->Heigth = height;
        }
        void Draw(HDC hdc)
        {
            Graphics graphics(hdc);
            Pen pen(Color(255, 0, 0, 255));
            graphics.DrawRectangle(&pen, this->X, this->Y, this->Width, this->Heigth);
        }
    };
}