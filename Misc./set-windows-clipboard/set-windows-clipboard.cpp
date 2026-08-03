#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include <string_view>
#include <format>

/* NOTE:
 *   this file used to depend on a shim that only implemented read_file
 *   i did not pull it in because it was machinegoduim
 */
#define SLURP_IMPLEMENTATION
#include "slurp-windows.h"

using namespace std;

struct clipboard_html_format_t {
  public:
    string header;
    string fragment;
    string payload;

    clipboard_html_format_t(string fragment_) {
        fragment = fragment_;

        do {
            constexpr string_view payload_template =
                "<html><body><!--StartFragment-->"
                "{}"
                "<!--EndFragment--></body></html>"
            ;
            payload = format(payload_template, fragment);
        } while (0);

        do {
            constexpr string_view header_template =
                "Version:0.9\r\n"
                "StartHTML:{:08}\r\n"
                "EndHTML:{:08}\r\n"
                "StartFragment:{:08}\r\n"
                "EndFragment:{:08}\r\n"
            ;
            int start_html = 105; // Standard header length
            int start_frag = start_html + strlen("<html><body><!--StartFragment-->"); // XXX redundancy
            int end_frag   = start_frag + fragment.size();
            int end_html   = start_html + payload.size();
            header = format(header_template,
                start_html,
                end_html,
                start_frag,
                end_frag
            );
        } while (0);
    }

    string to_string(void) const {
        return header + payload;
    }
};

int set_clipboard(const clipboard_html_format_t data) {
    UINT cf_html = RegisterClipboardFormatA("HTML Format");

    if (!OpenClipboard(NULL)) {
        return 1;
    }

    EmptyClipboard();

    string raw_data = data.to_string();
    
    HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, raw_data.size() + 1);
    if (hMem) {
        memcpy(GlobalLock(hMem), raw_data.c_str(), raw_data.size() + 1);
        GlobalUnlock(hMem);
        SetClipboardData(cf_html, hMem);
    }
    
    CloseClipboard();

    return 0;
}

int set_clipboard_html(const string s) {
    const auto d = clipboard_html_format_t(s);
    return set_clipboard(d);
}

int main(const int argc, const char * argv[]) {
    const char * my_arg;
    if (argc < 2) {
        my_arg = "<span style='color:red;'>Machinegod Logic</span>";
    } else {
        //my_arg = argv[1];
        my_arg = read_file(argv[1]);
    }

    set_clipboard_html(my_arg);

    return 0;
}

/*
what is wrong with C++s conception of a constnat?
            constexpr char a[] = "aaa";
            format(a);

            constexpr string b("bbb");
            format(b);

+/13.2.0/string:43,
                 from set-clipboard.cpp:4:
C:/Users/z005b1yk/Downloads/strawberry-perl/c/include/c++/13.2.0/bits/allocator.h: In constructor 'clipboard_html_format_t::clipboard_html_format_t(std::string)':
C:/Users/z005b1yk/Downloads/strawberry-perl/c/include/c++/13.2.0/bits/allocator.h:195:52: error: 'std::__cxx11::basic_string<char>(((const char*)"<html><body><!--StartFragment-->{}<!--EndFragment--></body></html>"), std::allocator<char>())' is not a constant expression because it refers to a result of 'operator new'
  195 |             return static_cast<_Tp*>(::operator new(__n));
      |                                      ~~~~~~~~~~~~~~^~~~~
set-clipboard.cpp:25:19: error: 'std::basic_format_string<char>{std::basic_string_view<char>{3, ((const char*)(& a))}}' is not a constant expression
   25 |             format(a);
      |             ~~~~~~^~~
set-clipboard.cpp:25:19: error: 'std::basic_format_string<char>(a)' is not a constant expression because it refers to an incompletely initialized variable
set-clipboard.cpp:27:37: error: 'std::string{std::__cxx11::basic_string<char>::_Alloc_hider{((char*)(& b.std::__cxx11::basic_string<char>::<anonymous>.std::__cxx11::basic_string<char>::<unnamed union>::_M_local_buf))}, 3, std::__cxx11::basic_string<char>::<unnamed union>{char [16]{'b', 'b', 'b', 0, '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000'}}}' is not a constant expression
   27 |             constexpr string b("bbb");
      |                                     ^
set-clipboard.cpp:27:37: error: 'std::__cxx11::basic_string<char>(((const char*)"bbb"), std::allocator<char>())' is not a constant expression because it refers to an incompletely initialized variable



*/
