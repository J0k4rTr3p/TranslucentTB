#pragma once
#include "arch.h"
#include <functional>
#include <string>
#include <unordered_map>
#include <windef.h>
#include <WinUser.h>

class Window; // Forward declare to avoid circular deps

class WindowClass {
private:
	using callback_t = std::function<LRESULT(Window, UINT, WPARAM, LPARAM)>;
	ATOM m_Atom;
	WNDCLASSEX m_ClassStruct;
	static std::unordered_map<ATOM, callback_t> m_CallbackMap;
	static LRESULT CALLBACK RawWindowProcedure(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

public:
	WindowClass(callback_t callback, const std::wstring &className, const wchar_t *iconResource, unsigned int style = 0, HINSTANCE hInstance = GetModuleHandle(NULL), HBRUSH brush = reinterpret_cast<HBRUSH>(COLOR_BACKGROUND), HCURSOR cursor = LoadCursor(NULL, IDC_ARROW));
	inline LPCWSTR atom() const { return reinterpret_cast<LPCWSTR>(MAKELPARAM(m_Atom, 0)); }
	~WindowClass();

	inline WindowClass(const WindowClass &) = delete;
	inline WindowClass &operator =(const WindowClass &) = delete;
};