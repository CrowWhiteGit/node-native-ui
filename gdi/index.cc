#include <node.h>
#include <windows.h>
#include <objidl.h>
#include <gdiplus.h>
#include <map>

#include "Primitives.cc"

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

    std::map<std::string, Rectangle> drawObjects;
    HWND hWnd;

    VOID
    OnPaint(HDC hdc)
    {
        Graphics graphics(hdc);
        Pen pen(Color(255, 0, 0, 255));
        graphics.DrawLine(&pen, 0, 0, 200, 100);
        for (auto const &drawObject : drawObjects)
        {
            Rectangle(drawObject.second).Draw(hdc);
        }
    }

    LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

    // INT WINAPI OpenWindow(HINSTANCE hInstance, HINSTANCE, PSTR, INT iCmdShow)
    void WINAPI OpenWindow(const FunctionCallbackInfo<Value> &args)
    {
        Isolate *isolate = args.GetIsolate();

        HINSTANCE hInstance = GetModuleHandle(NULL);
        INT iCmdShow = 1;

        MSG msg;
        WNDCLASS wndClass;
        GdiplusStartupInput gdiplusStartupInput;
        ULONG_PTR gdiplusToken;

        // Initialize GDI+.
        GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

        wndClass.style = CS_HREDRAW | CS_VREDRAW;
        wndClass.lpfnWndProc = WndProc;
        wndClass.cbClsExtra = 0;
        wndClass.cbWndExtra = 0;
        wndClass.hInstance = hInstance;
        wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
        wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
        wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
        wndClass.lpszMenuName = NULL;
        wndClass.lpszClassName = TEXT("GettingStarted");

        RegisterClass(&wndClass);

        hWnd = CreateWindow(
            TEXT("GettingStarted"),  // window class name
            TEXT("Getting Started"), // window caption
            WS_OVERLAPPEDWINDOW,     // window style
            CW_USEDEFAULT,           // initial x position
            CW_USEDEFAULT,           // initial y position
            CW_USEDEFAULT,           // initial x size
            CW_USEDEFAULT,           // initial y size
            NULL,                    // parent window handle
            NULL,                    // window menu handle
            hInstance,               // program instance handle
            NULL);                   // creation parameters

        ShowWindow(hWnd, iCmdShow);
        UpdateWindow(hWnd);

        // GdiplusShutdown(gdiplusToken);
    }

    void ProcessMessages(const FunctionCallbackInfo<Value> &args)
    {
        MSG msg;

        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    void AddElement(const FunctionCallbackInfo<Value> &args)
    {
        Isolate *isolate = args.GetIsolate();
        v8::String::Utf8Value _id(isolate, args[0]);
        std::string id(*_id);
        int type = args[1].As<Number>()->Value();

        if (type == 1)
        {
            Rectangle newObject;
            drawObjects[id] = newObject;
        }
        else if (type == 2)
        {
        }
        else if (type == 3)
        {
        }
        else
        {
        }

        InvalidateRect(hWnd, NULL, TRUE);
    }

    void RemoveElement(const FunctionCallbackInfo<Value> &args)
    {
        Isolate *isolate = args.GetIsolate();
        v8::String::Utf8Value str(isolate, args[0]);
        std::string id(*str);
        drawObjects.erase(id);
        InvalidateRect(hWnd, NULL, TRUE);
    }

    LRESULT CALLBACK WndProc(HWND hWnd, UINT message,
                             WPARAM wParam, LPARAM lParam)
    {
        HDC hdc;
        PAINTSTRUCT ps;

        switch (message)
        {
        case WM_PAINT:
            hdc = BeginPaint(hWnd, &ps);
            OnPaint(hdc);
            EndPaint(hWnd, &ps);
            return 0;
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }

    void Init(Local<Object> exports)
    {
        NODE_SET_METHOD(exports, "AddElement", AddElement);
        NODE_SET_METHOD(exports, "RemoveElement", RemoveElement);
        NODE_SET_METHOD(exports, "OpenWindow", OpenWindow);
        NODE_SET_METHOD(exports, "ProcessMessages", ProcessMessages);
    }

    NODE_MODULE(NODE_GYP_MODULE_NAME, Init)
}